namespace RequirementsApp.Models;

public class LoginAudit
{
    public int Id { get; set; }
    public int? UserId { get; set; }
    public User? User { get; set; }
    public string Email { get; set; } = string.Empty;
    public DateTime AttemptTime { get; set; } = DateTime.UtcNow;
    public bool Success { get; set; }
    public string? IpAddress { get; set; }
}