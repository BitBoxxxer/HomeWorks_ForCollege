namespace RequirementsApp.Models;

public class Comment
{
    public int Id { get; set; }
    public int VersionId { get; set; }
    public RequirementVersion Version { get; set; } = null!;
    public int UserId { get; set; }
    public User User { get; set; } = null!;
    public string Text { get; set; } = string.Empty;
    public DateTime CreatedDate { get; set; } = DateTime.UtcNow;
}