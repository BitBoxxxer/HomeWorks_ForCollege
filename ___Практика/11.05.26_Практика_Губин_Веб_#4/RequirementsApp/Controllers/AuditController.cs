using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RequirementsApp.Data;
using System.Security.Claims;

namespace RequirementsApp.Controllers;

[ApiController]
[Route("api/[controller]")]
[Authorize]
public class AuditController : ControllerBase
{
    private readonly AppDbContext _db;
    public AuditController(AppDbContext db) => _db = db;

    [HttpGet]
    public async Task<IActionResult> GetAudit()
    {
        var userId = int.Parse(User.FindFirstValue(ClaimTypes.NameIdentifier)!);
        if (userId != 1) return Forbid();

        var audits = await _db.LoginAudits
            .Include(a => a.User)
            .OrderByDescending(a => a.AttemptTime)
            .Take(100)
            .ToListAsync();

        return Ok(audits.Select(a => new
        {
            a.Id,
            a.Email,
            a.Success,
            a.IpAddress,
            a.AttemptTime,
            UserName = a.User?.FullName
        }));
    }
}