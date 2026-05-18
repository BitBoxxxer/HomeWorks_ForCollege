namespace RequirementsApp.DTOs;

public class ApproveDto
{
    public int UserId { get; set; }
    public bool IsApproved { get; set; }
    public string? Comment { get; set; }
}