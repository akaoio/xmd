# API Documentation Examples

These examples show how to create self-updating API documentation that stays synchronized with your live services.

## Examples in this Directory

### 1. API Status Dashboard (`api-status.md`)
Real-time API health monitoring with endpoint testing and response time tracking.

### 2. Interactive API Explorer (`api-explorer.md`)
Live API documentation with executable examples and real responses.

### 3. Service Dependencies (`service-deps.md`)
Automatically generated service dependency maps and health checks.

### 4. API Changelog (`api-changelog.md`)
Version tracking with automated diff detection and breaking change alerts.

## Configuration

Create a `config/api.json` file:

```json
{
  "base_url": "https://api.example.com",
  "version": "v1",
  "endpoints": [
    {"path": "/health", "method": "GET", "description": "Health check"},
    {"path": "/users", "method": "GET", "description": "List users"},
    {"path": "/users", "method": "POST", "description": "Create user"}
  ],
  "auth": {
    "type": "bearer",
    "token": "your-api-token"
  }
}
```

## Usage Examples

```bash
# Generate API documentation
xmd process api-status.md -v base_url="https://api.myapp.com"

# Monitor API in real-time
xmd watch api-status.md -o public/api-status.html

# Generate documentation for different environments
xmd process api-explorer.md -v environment=staging -o docs/staging-api.html
xmd process api-explorer.md -v environment=production -o docs/prod-api.html
```

## Integration with CI/CD

Add to your CI pipeline:

```yaml
# .github/workflows/api-docs.yml
- name: Update API Documentation
  run: |
    xmd process examples/api-docs/api-explorer.md -o docs/api.html
    git add docs/api.html
    git commit -m "Update API documentation" || true
```

## Security Notes

- Store API tokens in environment variables
- Use read-only API keys for documentation
- Implement rate limiting awareness
- Consider using API mocking for sensitive endpoints