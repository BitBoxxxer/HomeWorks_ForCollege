using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Authentication.Cookies;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RequirementsApp.Data;
using RequirementsApp.Models;
using System.Security.Claims;

namespace RequirementsApp.Controllers;

[ApiController]
[Route("api/[controller]")]
public class AuthController : ControllerBase
{
    private readonly AppDbContext _db;

    public AuthController(AppDbContext db) => _db = db;

    [HttpPost("login")]
    public async Task<IActionResult> Login([FromBody] LoginDto dto)
    {
        var user = await _db.Users.FirstOrDefaultAsync(u => u.Email == dto.Email);
        bool success = user != null && BCrypt.Net.BCrypt.Verify(dto.Password, user.PasswordHash);

        // аудит
        _db.LoginAudits.Add(new LoginAudit
        {
            UserId = user?.Id,
            Email = dto.Email,
            Success = success,
            IpAddress = HttpContext.Connection.RemoteIpAddress?.ToString()
        });
        await _db.SaveChangesAsync();

        if (!success)
            return Unauthorized("Неверный email или пароль");

        var claims = new List<Claim>
        {
            new Claim(ClaimTypes.NameIdentifier, user!.Id.ToString()),
            new Claim(ClaimTypes.Email, user.Email),
            new Claim(ClaimTypes.Name, user.FullName)
        };
        var identity = new ClaimsIdentity(claims, CookieAuthenticationDefaults.AuthenticationScheme);
        await HttpContext.SignInAsync(new ClaimsPrincipal(identity));

        return Ok(new { fullName = user.FullName });
    }

    [HttpPost("logout")]
    public async Task<IActionResult> Logout()
    {
        await HttpContext.SignOutAsync();
        return Ok();
    }

    [HttpGet("current")]
    public IActionResult CurrentUser()
    {
        if (User.Identity?.IsAuthenticated != true) return Unauthorized();
        return Ok(new
        {
            id = User.FindFirstValue(ClaimTypes.NameIdentifier),
            fullName = User.Identity.Name
        });
    }
}

public class LoginDto
{
    public string Email { get; set; } = string.Empty;
    public string Password { get; set; } = string.Empty;
}