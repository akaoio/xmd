# Complex Template Test
<!-- xmd:set env="production" -->
<!-- xmd:set region="us-east" -->
<!-- xmd:set app_name="MyApp" -->

Environment: {{env}}
Region: {{region}}
Application: {{app_name}}

<!-- xmd:if env == "production" -->
**Production Configuration:**
- Database: {{app_name}}-prod-db.{{region}}.amazonaws.com
- Cache: {{app_name}}-prod-cache.{{region}}.amazonaws.com
<!-- xmd:else -->
**Development Configuration:**
- Database: {{app_name}}-dev-db.localhost
- Cache: {{app_name}}-dev-cache.localhost
<!-- xmd:endif -->

<!-- xmd:for i in 1..3 -->
Server {{i}}: {{app_name}}-{{env}}-{{i}}.{{region}}.com
<!-- xmd:endfor -->