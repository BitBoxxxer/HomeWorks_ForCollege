using System.Text.Json;
using Microsoft.AspNetCore.Builder;
using Microsoft.Extensions.Hosting;
using Microsoft.AspNetCore.Http;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text.Json;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

string dbPath = Path.Combine(app.Environment.ContentRootPath, "..", "some_bd.json");
const int maxRecords = 10;

List<TemperatureRecord> ReadFromFile()
{
    if (!File.Exists(dbPath))
        return new List<TemperatureRecord>();
    
    string json = File.ReadAllText(dbPath);
    if (string.IsNullOrWhiteSpace(json))
        return new List<TemperatureRecord>();
    
    try
    {
        return JsonSerializer.Deserialize<List<TemperatureRecord>>(json) ?? new List<TemperatureRecord>();
    }
    catch (JsonException)
    {
        return new List<TemperatureRecord>();
    }
}

void WriteToFile(List<TemperatureRecord> records)
{
    var last10 = records.TakeLast(maxRecords).ToList();
    var json = JsonSerializer.Serialize(last10, new JsonSerializerOptions { WriteIndented = true });
    File.WriteAllText(dbPath, json);
}

void AddRecord(TemperatureRecord record)
{
    var records = ReadFromFile();
    records.Add(record);
    WriteToFile(records);
}

app.UseStaticFiles(new StaticFileOptions
{
    FileProvider = new Microsoft.Extensions.FileProviders.PhysicalFileProvider(
        Path.Combine(app.Environment.ContentRootPath, "..", "web")),
    RequestPath = ""
});

app.MapPost("/api/temperature", async (HttpContext context) =>
{
    using var reader = new StreamReader(context.Request.Body);
    var body = await reader.ReadToEndAsync();
    var record = JsonSerializer.Deserialize<TemperatureRecord>(body);
    if (record == null || record.Temperature < -50 || record.Temperature > 100)
    {
        context.Response.StatusCode = 400;
        return;
    }
    AddRecord(record);
    context.Response.StatusCode = 200;
});

app.MapGet("/api/temperature", () =>
{
    var records = ReadFromFile();
    return records.OrderByDescending(r => r.Timestamp).ToList();
});

app.MapGet("/", async context =>
{
    context.Response.Redirect("/index.html");
});

app.Run();

public record TemperatureRecord(
    [property: System.Text.Json.Serialization.JsonPropertyName("temperature")] double Temperature,
    [property: System.Text.Json.Serialization.JsonPropertyName("timestamp")] DateTime Timestamp
);