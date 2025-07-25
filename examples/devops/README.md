# DevOps Automation Examples

These examples demonstrate how XMD can be used for DevOps automation, infrastructure monitoring, and operational reporting.

## Examples in this Directory

### 1. Server Health Dashboard (`server-health.md`)
Real-time server monitoring with status checks, resource usage, and service health.

### 2. Deployment Report (`deployment-report.md`)
Automated deployment status reporting with rollback information and environment details.

### 3. Infrastructure Overview (`infrastructure.md`)
Complete infrastructure status dashboard with multi-environment support.

### 4. Incident Response Runbook (`incident-response.md`)
Interactive runbook that adapts based on current system state and incident type.

## Quick Start

```bash
# Process a single dashboard
xmd process server-health.md -o output/server-health-$(date +%Y%m%d-%H%M).html

# Watch for changes and auto-update
xmd watch infrastructure.md -o public/infrastructure.html

# Generate daily reports
xmd process deployment-report.md -v environment=production -o reports/prod-$(date +%Y-%m-%d).md
```

## Configuration

Most examples expect configuration files in a `config/` directory:

```bash
mkdir -p config
echo '{"servers": ["web1", "web2", "db1"], "environments": ["dev", "staging", "prod"]}' > config/infrastructure.json
```

## Security Considerations

These examples include system commands for demonstration. In production:

1. Use XMD's security configuration to limit command access
2. Run with restricted user permissions
3. Validate all inputs and environment variables
4. Consider using read-only monitoring approaches

## Integration

These examples work well with:
- **Cron Jobs**: Schedule regular report generation
- **CI/CD Pipelines**: Include in build/deployment processes  
- **Monitoring Systems**: Generate alerts from XMD output
- **Dashboards**: Serve processed files via web server