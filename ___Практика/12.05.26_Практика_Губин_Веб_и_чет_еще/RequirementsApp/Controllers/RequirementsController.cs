using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RequirementsApp.Data;
using RequirementsApp.DTOs;
using RequirementsApp.Models;
using RequirementsApp.Services;

namespace RequirementsApp.Controllers;

[ApiController]
[Route("api/[controller]")]
public class RequirementsController : ControllerBase
{
    private readonly AppDbContext _db;
    private readonly RequirementService _service;

    public RequirementsController(AppDbContext db, RequirementService service)
    {
        _db = db;
        _service = service;
    }

    [HttpGet]
    public async Task<IActionResult> GetAll([FromQuery] string? search, [FromQuery] string? status, [FromQuery] string? priority)
    {
        var query = _db.Requirements
            .Include(r => r.Author)
            .Include(r => r.CurrentVersion)
            .AsQueryable();

        if (!string.IsNullOrEmpty(search))
            query = query.Where(r => r.Title.Contains(search) || r.Description.Contains(search));
        if (!string.IsNullOrEmpty(status) && Enum.TryParse<RequirementStatus>(status, out var st))
            query = query.Where(r => r.Status == st);
        if (!string.IsNullOrEmpty(priority))
            query = query.Where(r => r.Priority == priority);

        return Ok(await query.ToListAsync());
    }

    [HttpGet("{id}")]
    public async Task<IActionResult> Get(int id)
    {
        var req = await _db.Requirements
            .Include(r => r.Author)
            .Include(r => r.CurrentVersion)
            .Include(r => r.Versions).ThenInclude(v => v.Approvals).ThenInclude(a => a.User)
            .Include(r => r.Versions).ThenInclude(v => v.Comments).ThenInclude(c => c.User)
            .Include(r => r.Versions).ThenInclude(v => v.Attachments)
            .Include(r => r.Approvers).ThenInclude(a => a.User)
            .FirstOrDefaultAsync(r => r.Id == id);

        return req == null ? NotFound() : Ok(req);
    }

    [HttpPost]
    public async Task<IActionResult> Create([FromBody] CreateRequirementDto dto)
    {
        var req = await _service.CreateAsync(dto.Title, dto.Description, dto.Priority, dto.AuthorId, dto.ApproverIds);
        return CreatedAtAction(nameof(Get), new { id = req.Id }, req);
    }

    [HttpPut("{id}")]
    public async Task<IActionResult> Edit(int id, [FromBody] EditRequirementDto dto)
    {
        try
        {
            var version = await _service.EditRequirementAsync(id, dto.Title, dto.Description, dto.Priority);
            return Ok(version);
        }
        catch (InvalidOperationException ex)
        {
            return BadRequest(ex.Message);
        }
    }

    [HttpPost("version/{versionId}/send-for-approval")]
    public async Task<IActionResult> SendForApproval(int versionId)
    {
        await _service.SendForApprovalAsync(versionId);
        return Ok();
    }

    [HttpPost("version/{versionId}/approve")]
    public async Task<IActionResult> Approve(int versionId, [FromBody] ApproveDto dto)
    {
        try
        {
            await _service.ApproveVersionAsync(versionId, dto.UserId, dto.IsApproved, dto.Comment);
            return Ok();
        }
        catch (InvalidOperationException ex)
        {
            return BadRequest(ex.Message);
        }
    }

    [HttpPost("version/{versionId}/comment")]
    public async Task<IActionResult> AddComment(int versionId, [FromBody] CommentDto dto)
    {
        await _service.AddCommentAsync(versionId, dto.UserId, dto.Text);
        return Ok();
    }
}