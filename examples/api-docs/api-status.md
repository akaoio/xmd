# 🚀 API Status Dashboard

<!-- xmd:set api_base="${base_url:-https://api.example.com}" -->
<!-- xmd:set api_version="${version:-v1}" -->
<!-- xmd:set full_url="${api_base}/${api_version}" -->

**API Base URL:** `{{full_url}}`  
**Status Check Time:** <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S %Z" -->  
**Report ID:** `<!-- xmd:exec echo $RANDOM | md5sum | cut -c 1-8 -->`

---

## 🔍 Quick Health Check

### Overall API Status
<!-- xmd:set health_url="${full_url}/health" -->

**Endpoint:** `{{health_url}}`  
**Status:** <!-- xmd:exec curl -s -w "%{http_code}" -o /tmp/health_response.json "{{health_url}}" --connect-timeout 10 --max-time 30 | grep -E '^(200|201|204)$' >/dev/null && echo "🟢 Healthy" || echo "🔴 Unhealthy" -->  
**Response Time:** <!-- xmd:exec curl -s -w "%{time_total}s" -o /dev/null "{{health_url}}" --connect-timeout 10 --max-time 30 -->

<!-- xmd:if curl -s "{{health_url}}" --connect-timeout 5 >/dev/null 2>&1 -->
**Health Response:**
```json
<!-- xmd:exec curl -s "{{health_url}}" 2>/dev/null | jq . 2>/dev/null || curl -s "{{health_url}}" 2>/dev/null || echo "Unable to fetch response" -->
```
<!-- xmd:else -->
⚠️ **Unable to connect to health endpoint**
<!-- xmd:endif -->

---

## 📊 Endpoint Status

<!-- xmd:set endpoints='[
  {"path": "/health", "method": "GET", "description": "Health check"},
  {"path": "/version", "method": "GET", "description": "API version info"},
  {"path": "/users", "method": "GET", "description": "List users"},
  {"path": "/auth/login", "method": "POST", "description": "User authentication"},
  {"path": "/metrics", "method": "GET", "description": "API metrics"}
]' -->

<!-- xmd:for endpoint in endpoints -->
### {{endpoint.method}} {{endpoint.path}}

**Description:** {{endpoint.description}}  
**Full URL:** `{{full_url}}{{endpoint.path}}`

<!-- xmd:if endpoint.method == "GET" -->
**Status:** <!-- xmd:exec curl -s -w "%{http_code}" -o /dev/null "{{full_url}}{{endpoint.path}}" --connect-timeout 5 --max-time 15 | grep -E '^(200|201|204|404|401)$' >/dev/null && echo "🟢 Accessible" || echo "🔴 Error" -->  
**Response Time:** <!-- xmd:exec curl -s -w "%{time_total}s" -o /dev/null "{{full_url}}{{endpoint.path}}" --connect-timeout 5 --max-time 15 -->

<!-- xmd:try -->
**Sample Response:**
```json
<!-- xmd:exec curl -s "{{full_url}}{{endpoint.path}}" --connect-timeout 5 --max-time 10 | head -20 | jq . 2>/dev/null || echo "Unable to fetch or parse response" -->
```
<!-- xmd:catch -->
*Response not available or not in JSON format*
<!-- xmd:endtry -->

<!-- xmd:else -->
**Status:** POST/PUT endpoints require authentication - testing connection only  
**Connection:** <!-- xmd:exec curl -s -w "%{http_code}" -o /dev/null -X {{endpoint.method}} "{{full_url}}{{endpoint.path}}" --connect-timeout 5 --max-time 10 | grep -E '^(200|201|204|400|401|403|404|405)$' >/dev/null && echo "🟢 Reachable" || echo "🔴 Unreachable" -->
<!-- xmd:endif -->

---
<!-- xmd:endfor -->

## 📈 Performance Metrics

### Response Time Analysis
<!-- xmd:for i in [1,2,3,4,5] -->
**Test {{i}}:** <!-- xmd:exec curl -s -w "%{time_total}s" -o /dev/null "{{health_url}}" --connect-timeout 5 --max-time 15 -->
<!-- xmd:endfor -->

**Average Response Time:** <!-- xmd:exec for i in {1..5}; do curl -s -w "%{time_total}\n" -o /dev/null "{{health_url}}" --connect-timeout 5 --max-time 10; done | awk '{sum+=$1} END {printf "%.3fs\n", sum/NR}' 2>/dev/null || echo "Unable to calculate" -->

### DNS Resolution
**DNS Lookup Time:** <!-- xmd:exec curl -s -w "%{time_namelookup}s" -o /dev/null "{{api_base}}" --connect-timeout 5 --max-time 10 -->

### SSL Certificate
<!-- xmd:if echo "{{api_base}}" | grep -q "https" -->
**SSL Status:** <!-- xmd:exec echo | openssl s_client -servername $(echo "{{api_base}}" | sed 's|https://||' | cut -d'/' -f1) -connect $(echo "{{api_base}}" | sed 's|https://||' | cut -d'/' -f1):443 2>/dev/null | grep -q "Verify return code: 0" && echo "🟢 Valid" || echo "🔴 Invalid" -->
**Certificate Expiry:** <!-- xmd:exec echo | openssl s_client -servername $(echo "{{api_base}}" | sed 's|https://||' | cut -d'/' -f1) -connect $(echo "{{api_base}}" | sed 's|https://||' | cut -d'/' -f1):443 2>/dev/null | openssl x509 -noout -dates 2>/dev/null | grep notAfter | cut -d= -f2 -->
<!-- xmd:else -->
**SSL:** Not applicable (HTTP endpoint)
<!-- xmd:endif -->

---

## 🔧 Service Information

<!-- xmd:try -->
### Version Info
<!-- xmd:exec curl -s "{{full_url}}/version" --connect-timeout 5 | jq . 2>/dev/null -->
<!-- xmd:catch -->
Version endpoint not available or not in JSON format
<!-- xmd:endtry -->

<!-- xmd:try -->
### Server Headers
```
<!-- xmd:exec curl -s -I "{{health_url}}" --connect-timeout 5 | head -10 -->
```
<!-- xmd:catch -->
Unable to fetch server headers
<!-- xmd:endtry -->

---

## 🚨 Status Summary

<!-- xmd:set total_endpoints=5 -->
<!-- xmd:set healthy_count=$(for endpoint in /health /version /users /auth/login /metrics; do curl -s -w "%{http_code}" -o /dev/null "${full_url}${endpoint}" --connect-timeout 3 --max-time 8 | grep -E '^(200|201|204|401|404)$' >/dev/null && echo "1" || echo "0"; done | grep "1" | wc -l) -->

**Endpoints Tested:** {{total_endpoints}}  
**Healthy/Accessible:** {{healthy_count}}  
**Health Percentage:** <!-- xmd:exec echo "scale=1; {{healthy_count}} * 100 / {{total_endpoints}}" | bc -->%

<!-- xmd:if healthy_count >= 4 -->
### ✅ System Status: **HEALTHY**
All critical endpoints are responding normally.
<!-- xmd:elif healthy_count >= 2 -->
### ⚠️ System Status: **DEGRADED**
Some endpoints are experiencing issues. Monitor closely.
<!-- xmd:else -->
### 🚨 System Status: **CRITICAL**
Multiple endpoints are failing. Immediate attention required.
<!-- xmd:endif -->

---

## 📱 Monitoring Integration

### Uptime Check Commands
```bash
# Simple health check
curl -f "{{health_url}}" || echo "API_DOWN"

# Detailed check with timeout
curl -s -w "HTTP_%{http_code}_TIME_%{time_total}s" "{{health_url}}" --max-time 30

# JSON response validation
curl -s "{{health_url}}" | jq .status | grep -q "ok" || echo "UNHEALTHY"
```

### Alert Thresholds
- **Response Time**: > 2.0s (Warning), > 5.0s (Critical)
- **HTTP Status**: Non-2xx codes (Warning), Connection failures (Critical)
- **Uptime**: < 99.5% (Warning), < 99.0% (Critical)

---

<small>
**Dashboard generated by XMD** • 
**Last updated:** <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" --> • 
**Monitoring from:** <!-- xmd:exec hostname --> • 
**Public IP:** <!-- xmd:exec curl -s -m 5 ifconfig.me 2>/dev/null || echo "Unknown" -->
</small>