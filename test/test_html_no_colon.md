# Test HTML Comment Without Colon

This tests the new HTML comment syntax without requiring a colon.

<!-- xmd set name "World" -->

Hello, {{name}}!

<!-- xmd
set greeting "Hi"
set user "Genesis"
-->

{{greeting}}, {{user}}!

## Inline Test

Testing inline: Hello <!-- xmd print "everyone" -->!

## Variable Test

<!-- xmd set count 42 -->
The answer is {{count}}.