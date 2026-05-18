using Microsoft.EntityFrameworkCore;
using RequirementsApp.Data;
using RequirementsApp.Models;

namespace RequirementsApp.Services;

public class FileService
{
    private readonly AppDbContext _db;
    private readonly IWebHostEnvironment _env;

    public FileService(AppDbContext db, IWebHostEnvironment env)
    {
        _db = db;
        _env = env;
    }

    public async Task<Attachment> UploadAsync(int versionId, IFormFile file)
    {
        var version = await _db.RequirementVersions.FindAsync(versionId)
            ?? throw new InvalidOperationException("Версия не найдена");

        var folder = Path.Combine(_env.ContentRootPath, "Uploads", versionId.ToString());
        Directory.CreateDirectory(folder);

        var uniqueName = Guid.NewGuid().ToString() + Path.GetExtension(file.FileName);
        var filePath = Path.Combine(folder, uniqueName);

        using var stream = new FileStream(filePath, FileMode.Create);
        await file.CopyToAsync(stream);

        var attachment = new Attachment
        {
            VersionId = versionId,
            FileName = file.FileName,
            FilePath = filePath,
            UploadedDate = DateTime.UtcNow
        };
        _db.Attachments.Add(attachment);
        await _db.SaveChangesAsync();
        return attachment;
    }

    public async Task<(byte[] Data, string FileName)> DownloadAsync(int attachmentId)
    {
        var att = await _db.Attachments.FindAsync(attachmentId)
            ?? throw new InvalidOperationException("Файл не найден");
        var data = await File.ReadAllBytesAsync(att.FilePath);
        return (data, att.FileName);
    }
}