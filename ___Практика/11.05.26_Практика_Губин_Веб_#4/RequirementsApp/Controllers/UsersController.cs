using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RequirementsApp.Data;
using Microsoft.AspNetCore.Authorization;

namespace RequirementsApp.Controllers;

[ApiController]
[Route("api/[controller]")][Authorize]
public class UsersController : ControllerBase
{
    private readonly AppDbContext _db;
    public UsersController(AppDbContext db) => _db = db;

    [HttpGet]
    public async Task<IActionResult> GetAll()
    {
        var users = await _db.Users.ToListAsync();
        return Ok(users);
    }
}