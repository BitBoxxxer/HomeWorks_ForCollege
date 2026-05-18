using System.Text.Json.Serialization;

namespace RequirementsApp.Models;

public enum RequirementStatus { Draft, InApproval, Approved, Rejected, Archived }

public class Requirement
{
    public int Id { get; set; }
    public string Title { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string Priority { get; set; } = "Средний";
    public int AuthorId { get; set; }
    public User? Author { get; set; }
    public DateTime CreatedDate { get; set; } = DateTime.UtcNow;
    public RequirementStatus Status { get; set; } = RequirementStatus.Draft;

    public int? CurrentVersionId { get; set; }
    public RequirementVersion? CurrentVersion { get; set; }

    public List<RequirementVersion> Versions { get; set; } = new();
    public List<RequirementApprover> Approvers { get; set; } = new();
}

public class RequirementApprover
{
    public int RequirementId { get; set; }
    public Requirement Requirement { get; set; } = null!;
    public int UserId { get; set; }
    public User User { get; set; } = null!;
}