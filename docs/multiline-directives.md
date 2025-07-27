# 🎨 Multiline Directives Guide

XMD supports both single-line and multiline directive syntax, giving you flexibility and improved readability for complex configurations.

## 📝 Basic Multiline Syntax

### Single Comment Block

```markdown
<!-- xmd:
set name="Alice"
set role="admin"
set permissions=["read", "write", "admin"]
set config={"theme": "dark", "lang": "en"}
-->

Welcome {{name}}! You have {{role}} access.
```

This is equivalent to:

```markdown
<!-- xmd:set name="Alice" -->
<!-- xmd:set role="admin" -->
<!-- xmd:set permissions=["read", "write", "admin"] -->
<!-- xmd:set config={"theme": "dark", "lang": "en"} -->

Welcome {{name}}! You have {{role}} access.
```

## 🔄 Cross-Comment Control Flow

### Conditionals Across Comments

```markdown
<!-- xmd:
set environment="production"
set features=["auth", "logging", "monitoring"]
-->

# Application Status

<!-- xmd:if environment == "production" -->
## 🚀 Production Environment
System is running in production mode with enhanced monitoring.

<!-- xmd:for feature in features -->
- ✅ {{feature}}: Active
<!-- xmd:endfor -->
<!-- xmd:else -->
## 🔧 Development Environment
Running in development mode with debug features enabled.
<!-- xmd:endif -->
```

### Nested Loops and Conditions

```markdown
<!-- xmd:
set environments=["dev", "staging", "prod"]
set services=["api", "database", "cache"]
-->

# Infrastructure Status

<!-- xmd:for env in environments -->
## {{env|upper}} Environment

<!-- xmd:if env == "prod" -->
### 🔒 Production Services (Enhanced Monitoring)
<!-- xmd:else -->
### 🔧 {{env}} Services
<!-- xmd:endif -->

<!-- xmd:for service in services -->
- **{{service}}**: 
  <!-- xmd:exec curl -sf https://{{service}}.{{env}}.example.com/health && echo "🟢 Healthy" || echo "🔴 Down" -->
<!-- xmd:endfor -->

<!-- xmd:endfor -->
```

## 📊 Advanced Multiline Patterns

### Configuration Blocks

```markdown
<!-- xmd:
set database={
  "host": "localhost",
  "port": 5432,
  "name": "app_db",
  "ssl": true
}
set redis={
  "host": "cache.internal",
  "port": 6379,
  "cluster": true
}
set monitoring={
  "enabled": true,
  "endpoints": ["/health", "/metrics", "/status"],
  "alerts": ["email", "slack", "pagerduty"]
}
-->

# System Configuration

## Database Configuration
- Host: {{database.host}}:{{database.port}}
- Database: {{database.name}}
- SSL: {{database.ssl}}

## Cache Configuration  
- Redis Host: {{redis.host}}:{{redis.port}}
- Cluster Mode: {{redis.cluster}}

<!-- xmd:if monitoring.enabled -->
## Monitoring Endpoints
<!-- xmd:for endpoint in monitoring.endpoints -->
- {{endpoint}}: <!-- xmd:exec curl -sf localhost:8080{{endpoint}} && echo "✅" || echo "❌" -->
<!-- xmd:endfor -->
<!-- xmd:endif -->
```

### Data Processing Workflows

```markdown
<!-- xmd:
set servers=[
  {"name": "web-01", "ip": "10.0.1.10", "role": "frontend"},
  {"name": "web-02", "ip": "10.0.1.11", "role": "frontend"}, 
  {"name": "db-01", "ip": "10.0.2.10", "role": "database"},
  {"name": "cache-01", "ip": "10.0.3.10", "role": "cache"}
]
set roles=["frontend", "database", "cache"]
-->

# Infrastructure Overview

<!-- xmd:for role in roles -->
## {{role|upper}} Servers

<!-- xmd:for server in servers -->
<!-- xmd:if server.role == role -->
### {{server.name}} ({{server.ip}})
- Status: <!-- xmd:exec ping -c1 -W1 {{server.ip}} >/dev/null 2>&1 && echo "🟢 Online" || echo "🔴 Offline" -->
- Load: <!-- xmd:exec ssh -o ConnectTimeout=2 {{server.ip}} "uptime | awk '{print \$(NF-2)}'" 2>/dev/null || echo "N/A" -->
- Memory: <!-- xmd:exec ssh -o ConnectTimeout=2 {{server.ip}} "free -h | awk 'NR==2{print \$3\"/\"\$2}'" 2>/dev/null || echo "N/A" -->
<!-- xmd:endif -->
<!-- xmd:endfor -->

<!-- xmd:endfor -->
```

## 🔧 Best Practices

### 1. Group Related Settings

```markdown
<!-- xmd:
# Application configuration
set app_name="MyApp"
set app_version="1.2.0"
set app_env="production"

# Database settings
set db_host="prod-db.internal"
set db_name="myapp_prod"
set db_ssl=true

# Feature flags
set features={
  "new_ui": true,
  "beta_api": false,
  "analytics": true
}
-->
```

### 2. Use Comments Within Multiline Blocks

```markdown
<!-- xmd:
# User configuration
set user="admin"
set permissions=["read", "write", "delete"]

# Environment settings
set debug=false
set log_level="info"

# External services
set api_base="https://api.example.com"
set timeout=30
-->
```

### 3. Organize Complex Data Structures

```markdown
<!-- xmd:
set monitoring_config={
  "alerts": {
    "email": ["admin@example.com", "ops@example.com"],
    "slack": "#alerts",
    "pagerduty": "PXXXXXX"
  },
  "thresholds": {
    "cpu": 80,
    "memory": 85,
    "disk": 90
  },
  "intervals": {
    "check": 60,
    "report": 300,
    "cleanup": 3600
  }
}
-->
```

## 🚫 Common Pitfalls

### Avoid Mixing Syntax Styles

❌ **Don't mix single-line and multiline in the same block:**

```markdown
<!-- xmd:
set name="Alice"
<!-- xmd:set role="admin" -->  <!-- Wrong! -->
set permissions=["read", "write"]
-->
```

✅ **Use consistent syntax:**

```markdown
<!-- xmd:
set name="Alice"
set role="admin"
set permissions=["read", "write"]
-->
```

### Mind the Indentation

The content inside multiline blocks should not be indented relative to the comment markers:

✅ **Correct:**
```markdown
<!-- xmd:
set name="Alice"
set role="admin"
-->
```

❌ **Incorrect:**
```markdown
<!-- xmd:
    set name="Alice"
    set role="admin"
-->
```

## 🎯 Performance Considerations

Multiline directives are processed efficiently:

- **Single pass parsing**: All directives in a block are parsed together
- **Memory efficient**: No additional overhead compared to single-line syntax
- **Cache friendly**: Better locality for related settings

Multiline syntax is recommended for:
- Complex configuration blocks
- Related variable groups
- Better code organization and readability

Single-line syntax is still preferred for:
- Simple, standalone variables
- Inline processing commands
- Quick variable assignments