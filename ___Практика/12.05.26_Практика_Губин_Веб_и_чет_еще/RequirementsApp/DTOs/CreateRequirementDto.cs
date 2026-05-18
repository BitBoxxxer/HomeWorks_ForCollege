namespace RequirementsApp.DTOs;

public class CreateRequirementDto
{
    public string Title { get; set; } = string.Empty;
    public string Description { get; set; } = string.Empty;
    public string Priority { get; set; } = "Средний";
    public int AuthorId { get; set; }
    public List<int> ApproverIds { get; set; } = new();
}