# Processor Test - Markdown Integration

Testing variable persistence in markdown:

```xmd
set title "XMD Processor Test"
set version "1.0"
```

The title is: {{title}}
The version is: {{version}}

## Multiple Variables Test

```xmd
set a 5
set b 10
set c a + b
```

Result: {{a}} + {{b}} = {{c}}