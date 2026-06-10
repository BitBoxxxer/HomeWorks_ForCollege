namespace RequirementsApp.DTOs;

public class EditRequirementDto
{
    public string? Title { get; set; }
    public string? Description { get; set; }
    public string? Priority { get; set; }
    public string? Department { get; set; }
    public string? Resource { get; set; }
    public string? AccessType { get; set; }
    public DateTime? ExpirationDate { get; set; }
}