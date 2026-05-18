using Microsoft.EntityFrameworkCore;
using RequirementsApp.Models;

namespace RequirementsApp.Data;

public class AppDbContext : DbContext
{
    public AppDbContext(DbContextOptions<AppDbContext> options) : base(options) { }

    public DbSet<User> Users => Set<User>();
    public DbSet<Requirement> Requirements => Set<Requirement>();
    public DbSet<RequirementVersion> RequirementVersions => Set<RequirementVersion>();
    public DbSet<Approval> Approvals => Set<Approval>();
    public DbSet<Comment> Comments => Set<Comment>();
    public DbSet<Attachment> Attachments => Set<Attachment>();
    public DbSet<RequirementApprover> RequirementApprovers => Set<RequirementApprover>();

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<RequirementApprover>()
            .HasKey(ra => new { ra.RequirementId, ra.UserId });

        modelBuilder.Entity<Requirement>()
            .HasOne(r => r.CurrentVersion)
            .WithMany()
            .HasForeignKey(r => r.CurrentVersionId)
            .OnDelete(DeleteBehavior.SetNull);

        modelBuilder.Entity<Approval>()
            .HasOne(a => a.Version)
            .WithMany(v => v.Approvals)
            .HasForeignKey(a => a.VersionId);

        // Начальные данные: 3 пользователя для теста
        modelBuilder.Entity<User>().HasData(
            new User { Id = 1, FullName = "Иван Петров", Email = "ivan@company.ru" },
            new User { Id = 2, FullName = "Елена Смирнова", Email = "elena@company.ru" },
            new User { Id = 3, FullName = "Алексей Иванов", Email = "alex@company.ru" }
        );
    }
}