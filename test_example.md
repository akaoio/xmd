# Test XMD Installation

<!-- xmd:set user="Termux User" -->
<!-- xmd:set platform="Android" -->

Hello {{user}}! 👋

## System Info
- Platform: {{platform}}
- Time: <!-- xmd:exec date "+%Y-%m-%d %H:%M:%S" -->
- User: <!-- xmd:exec whoami -->

<!-- xmd:if platform == "Android" -->
## You're running on Android!
Perfect for mobile development.
<!-- xmd:endif -->