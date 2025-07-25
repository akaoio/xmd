# 📚 XMD Examples Collection

This directory contains practical, real-world examples demonstrating XMD's capabilities across different use cases and industries.

## 🗂️ Example Categories

### 🚀 [DevOps Automation](devops/)
Infrastructure monitoring, deployment reports, and operational dashboards
- Server health monitoring
- Deployment status reports  
- Infrastructure overviews
- Incident response runbooks

### 📡 [API Documentation](api-docs/)
Self-updating API documentation and service monitoring
- Live API status dashboards
- Interactive API explorers
- Service dependency mapping
- API changelog generation

### 📊 [System Monitoring](monitoring/)
Real-time system metrics and performance tracking
- Resource usage dashboards
- Application monitoring
- Log analysis reports
- Performance benchmarks

### 📈 [Data Reports](reports/)
Dynamic data analysis and business reporting
- Sales analytics
- User engagement metrics
- Financial summaries
- Operational KPIs

### 🔄 [CI/CD Integration](ci-cd/)
Build pipelines, deployment automation, and release management
- Build status reports
- Test result summaries
- Deployment pipelines
- Release notes generation

## 🚀 Quick Start

1. **Choose an example** that matches your use case
2. **Review the README** in each directory for setup instructions
3. **Configure** any required settings or API endpoints
4. **Run XMD** to generate your first dynamic document

```bash
# Try the server health example
cd devops/
xmd process server-health.md -o output.html

# Watch for changes and auto-update
xmd watch api-docs/api-status.md -o dashboard.html
```

## 📋 Example Structure

Each example includes:

- **README.md**: Setup instructions and configuration details
- **Example files**: Ready-to-use XMD templates
- **Configuration**: Sample config files and environment setup
- **Documentation**: Usage patterns and customization options

## 🛠️ Customization

All examples are designed to be easily customized:

1. **Variables**: Modify settings at the top of each file
2. **Commands**: Adapt system commands for your environment
3. **Styling**: Add CSS/HTML for custom presentation
4. **Integration**: Connect to your existing tools and APIs

## 🔒 Security Considerations

Before using examples in production:

1. **Review all commands** - Ensure they're safe for your environment
2. **Configure permissions** - Use XMD's security features to limit access
3. **Validate inputs** - Sanitize any external data sources
4. **Use read-only access** - Prefer monitoring over system modification
5. **Test thoroughly** - Run examples in development first

## 💡 Contributing Examples

Have a great XMD use case? We'd love to see it!

1. Fork the repository
2. Create a new directory under the appropriate category
3. Include a README with clear setup instructions
4. Add example files with comments explaining key concepts
5. Submit a pull request

### Example Template Structure
```
examples/your-category/your-example/
├── README.md              # Setup and usage instructions
├── example.md             # Main XMD template
├── config/                # Configuration files
│   └── settings.json
└── output/                # Sample output (optional)
    └── example.html
```

## 🎯 Use Case Ideas

Looking for inspiration? Here are some popular XMD applications:

- **Documentation**: Auto-updating technical docs
- **Dashboards**: Real-time operational views
- **Reports**: Scheduled business analytics
- **Monitoring**: System health checks
- **Notifications**: Alert summaries
- **Runbooks**: Interactive troubleshooting guides
- **Status Pages**: Public service status
- **Changelogs**: Automated release notes

## 📞 Support

Need help with an example?

- 📖 Check the [main documentation](../docs/)
- 💬 Join our [Discord community](https://discord.gg/xmd)
- 🐛 Report issues on [GitHub](https://github.com/akaoio/xmd/issues)
- 💡 Discuss ideas in [GitHub Discussions](https://github.com/akaoio/xmd/discussions)

---

<div align="center">

**Start with any example above and adapt it to your needs!**

*Made with ❤️ using XMD*

</div>