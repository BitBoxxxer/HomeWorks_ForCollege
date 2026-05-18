namespace RequirementsApp.Models;

public enum VersionStatus { Draft, InApproval, Approved, Rejected }

public class RequirementVersion
{
    public int Id { get; set; }
    public int RequirementId { get; set; }
    public Requirement Requirement { get; set; } = null!;
    public int VersionNumber { get; set; }
    public string Title { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string Priority { get; set; } = "Средний";
    public VersionStatus Status { get; set; } = VersionStatus.Draft;
    public DateTime CreatedDate { get; set; } = DateTime.UtcNow;
    public DateTime? ApprovedDate { get; set; }

    public List<Approval> Approvals { get; set; } = new();
    public List<Attachment> Attachments { get; set; } = new();
    public List<Comment> Comments { get; set; } = new();
}