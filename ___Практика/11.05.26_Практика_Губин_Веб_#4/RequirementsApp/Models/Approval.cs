namespace RequirementsApp.Models;

public class Approval
{
    public int Id { get; set; }
    public int VersionId { get; set; }
    public RequirementVersion Version { get; set; } = null!;
    public int UserId { get; set; }
    public User User { get; set; } = null!;
    public bool? IsApproved { get; set; }
    public string? Comment { get; set; }
    public DateTime? DecidedDate { get; set; }
}