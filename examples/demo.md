# XMD Demo Document

This is a demonstration of XMD (eXtended MarkDown) capabilities.

## Basic Markdown

This is **bold** text and *italic* text.

- List item 1
- List item 2
- List item 3

## XMD Features

<!-- xmd:set name="World" -->
Hello, {{name}}!

### Code Block

```bash
echo "XMD is working!"
```

## Advanced Features

<!-- xmd:if name == "World" -->
This will be displayed because name is "World".
<!-- xmd:endif -->

<!-- xmd:for i in [1, 2, 3] -->
Item {{i}}
<!-- xmd:endfor -->

## End

This concludes the XMD demo.