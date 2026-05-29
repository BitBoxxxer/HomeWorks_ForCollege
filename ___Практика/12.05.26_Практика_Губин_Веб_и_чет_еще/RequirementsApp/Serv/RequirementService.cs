using Microsoft.EntityFrameworkCore;
using RequirementsApp.Data;
using RequirementsApp.Models;

namespace RequirementsApp.Services;

public class RequirementService
{
    private readonly AppDbContext _db;
    public RequirementService(AppDbContext db) => _db = db;

    public async Task<Requirement> CreateAsync(string title, string description, string priority,
        string department, string resource, string accessType, DateTime? expirationDate,
        int authorId, List<int> approverIds)
    {
        var requirement = new Requirement
        {
            Title = title,
            Description = description,
            Priority = priority,
            Department = department,
            Resource = resource,
            AccessType = accessType,
            ExpirationDate = expirationDate,
            AuthorId = authorId,
            CreatedDate = DateTime.UtcNow,
            Status = RequirementStatus.Draft
        };

        foreach (var userId in approverIds)
            requirement.Approvers.Add(new RequirementApprover { UserId = userId });

        _db.Requirements.Add(requirement);
        await _db.SaveChangesAsync();

        // Первая версия тоже должна хранить эти поля (чтобы история была полной)
        var version = new RequirementVersion
        {
            RequirementId = requirement.Id,
            Title = title,
            Description = description,
            Priority = priority,
            Department = department,
            Resource = resource,
            AccessType = accessType,
            ExpirationDate = expirationDate,
            VersionNumber = 1,
            Status = VersionStatus.Draft,
            CreatedDate = DateTime.UtcNow
        };
        _db.RequirementVersions.Add(version);
        await _db.SaveChangesAsync();

        requirement.CurrentVersionId = version.Id;
        await _db.SaveChangesAsync();

        return await _db.Requirements
            .Include(r => r.Author)
            .Include(r => r.CurrentVersion)
            .Include(r => r.Versions)
            .Include(r => r.Approvers).ThenInclude(a => a.User)
            .FirstAsync(r => r.Id == requirement.Id);
    }

    public async Task<RequirementVersion> EditRequirementAsync(int requirementId,
        string? newTitle, string? newDescription, string? newPriority,
        string? newDepartment, string? newResource, string? newAccessType, DateTime? newExpirationDate)
    {
        var req = await _db.Requirements
            .Include(r => r.Versions)
            .FirstOrDefaultAsync(r => r.Id == requirementId)
            ?? throw new InvalidOperationException("Требование не найдено");

        if (newTitle != null) req.Title = newTitle;
        if (newDescription != null) req.Description = newDescription;
        if (newPriority != null) req.Priority = newPriority;
        if (newDepartment != null) req.Department = newDepartment;
        if (newResource != null) req.Resource = newResource;
        if (newAccessType != null) req.AccessType = newAccessType;
        req.ExpirationDate = newExpirationDate; // может быть null, это допустимо

        if (req.Status == RequirementStatus.Approved || req.Status == RequirementStatus.Archived)
        {
            // Создаём новую версию, копируя текущие данные требования
            var lastVersion = req.Versions.OrderByDescending(v => v.VersionNumber).First();
            var newVersion = new RequirementVersion
            {
                RequirementId = req.Id,
                Title = req.Title,
                Description = req.Description,
                Priority = req.Priority,
                Department = req.Department,
                Resource = req.Resource,
                AccessType = req.AccessType,
                ExpirationDate = req.ExpirationDate,
                VersionNumber = lastVersion.VersionNumber + 1,
                Status = VersionStatus.Draft,
                CreatedDate = DateTime.UtcNow
            };
            req.Versions.Add(newVersion);
            req.Status = RequirementStatus.Draft;
            req.CurrentVersion = null;
            req.CurrentVersionId = null;
            await _db.SaveChangesAsync();
            return newVersion;
        }
        else
        {
            // последний черновик
            var currentDraft = req.Versions
                .Where(v => v.Status == VersionStatus.Draft)
                .OrderByDescending(v => v.VersionNumber)
                .First();

            currentDraft.Title = req.Title;
            currentDraft.Description = req.Description;
            currentDraft.Priority = req.Priority;
            currentDraft.Department = req.Department;
            currentDraft.Resource = req.Resource;
            currentDraft.AccessType = req.AccessType;
            currentDraft.ExpirationDate = req.ExpirationDate;
            await _db.SaveChangesAsync();
            return currentDraft;
        }
    }

    public async Task SendForApprovalAsync(int versionId)
    {
        var version = await _db.RequirementVersions
            .Include(v => v.Requirement)
            .FirstOrDefaultAsync(v => v.Id == versionId)
            ?? throw new InvalidOperationException("Версия не найдена");

        version.Status = VersionStatus.InApproval;
        version.Requirement.Status = RequirementStatus.InApproval;

        var req = await _db.Requirements
            .Include(r => r.Approvers)
            .FirstAsync(r => r.Id == version.RequirementId);

        foreach (var approver in req.Approvers)
        {
            if (!version.Approvals.Any(a => a.UserId == approver.UserId))
                version.Approvals.Add(new Approval
                {
                    UserId = approver.UserId,
                    IsApproved = null
                });
        }
        await _db.SaveChangesAsync();
    }

    public async Task ApproveVersionAsync(int versionId, int userId, bool isApproved, string? comment)
    {
        var approval = await _db.Approvals
            .FirstOrDefaultAsync(a => a.VersionId == versionId && a.UserId == userId)
            ?? throw new InvalidOperationException("Согласующий не найден");

        approval.IsApproved = isApproved;
        approval.Comment = comment;
        approval.DecidedDate = DateTime.UtcNow;

        var version = await _db.RequirementVersions
            .Include(v => v.Approvals)
            .Include(v => v.Requirement)
            .FirstAsync(v => v.Id == versionId);

        if (version.Approvals.All(a => a.IsApproved != null))
        {
            if (version.Approvals.All(a => a.IsApproved == true))
            {
                version.Status = VersionStatus.Approved;
                version.ApprovedDate = DateTime.UtcNow;
                version.Requirement.CurrentVersion = version;
                version.Requirement.CurrentVersionId = version.Id;
                version.Requirement.Title = version.Title;
                version.Requirement.Description = version.Description;
                version.Requirement.Priority = version.Priority;
                version.Requirement.Status = RequirementStatus.Approved;
            }
            else
            {
                version.Status = VersionStatus.Rejected;
                version.Requirement.Status = RequirementStatus.Rejected;
            }
        }
        await _db.SaveChangesAsync();
    }

    public async Task AddCommentAsync(int versionId, int userId, string text)
    {
        _db.Comments.Add(new Comment
        {
            VersionId = versionId,
            UserId = userId,
            Text = text,
            CreatedDate = DateTime.UtcNow
        });
        await _db.SaveChangesAsync();
    }
}