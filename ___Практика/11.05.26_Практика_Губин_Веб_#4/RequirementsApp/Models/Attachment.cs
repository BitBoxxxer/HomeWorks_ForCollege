namespace RequirementsApp.Models;

public class Attachment
{
    public int Id { get; set; }
    public int VersionId { get; set; }
    public RequirementVersion Version { get; set; } = null!;
    public string FileName { get; set; } = string.Empty;
    public string FilePath { get; set; } = string.Empty;
    public DateTime UploadedDate { get; set; } = DateTime.UtcNow;
}