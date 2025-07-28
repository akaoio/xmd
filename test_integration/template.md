<!-- xmd:
set title = "XMD Documentation"
set version = "v1.1.0"
set sections = ["test_integration/docs/intro.md", "test_integration/docs/features.md", "test_integration/docs/examples.md"]
set toc = "# Table of Contents\n\n"
set content = ""
set counter = ""
for section in sections
    counter += "x"
    toc += "- Section " + counter + "\n"
    content += "## Section " + counter + "\n\n"
    content += import section + "\n\n"
-->

# {{title}} {{version}}

{{toc}}

{{content}}

---
Generated automatically with XMD.
