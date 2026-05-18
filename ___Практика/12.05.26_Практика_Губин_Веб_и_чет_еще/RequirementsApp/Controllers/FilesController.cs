using Microsoft.AspNetCore.Mvc;
using RequirementsApp.Services;

namespace RequirementsApp.Controllers;

[ApiController]
[Route("api/[controller]")]
public class FilesController : ControllerBase
{
    private readonly FileService _fileService;

    public FilesController(FileService fileService) => _fileService = fileService;

    [HttpPost("upload/{versionId}")]
    public async Task<IActionResult> Upload(int versionId, IFormFile file)
    {
        if (file == null || file.Length == 0)
            return BadRequest("Файл не выбран");
        var attachment = await _fileService.UploadAsync(versionId, file);
        return Ok(attachment);
    }

    [HttpGet("download/{attachmentId}")]
    public async Task<IActionResult> Download(int attachmentId)
    {
        var (data, fileName) = await _fileService.DownloadAsync(attachmentId);
        return File(data, "application/octet-stream", fileName);
    }
}