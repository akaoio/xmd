# Dual Syntax Test - HTML Comments vs Native XMD

This file tests both syntaxes to verify the dispatcher routing.

## HTML Comment Syntax (Legacy)

<!-- xmd set legacy_name="Legacy System" -->
<!-- xmd set legacy_score=100 -->

Legacy Test: {{legacy_name}} with score {{legacy_score}}

<!-- xmd if legacy_score >= 90 -->
Legacy: Excellent!
<!-- xmd endif -->

## Native XMD Syntax (Genesis Vision)

```xmd
set native_name "Native XMD"
set native_score 100

print "Native Test: " + native_name + " with score " + native_score

if native_score >= 90
    print "Native: Excellent!"
```

## Mixed Usage Test

<!-- xmd set shared_var="Shared between systems" -->

```xmd
print "Can native access HTML var? " + shared_var
```

## Expected Results

1. Both syntaxes should work independently
2. The dispatcher should route correctly based on syntax
3. Variable sharing between systems needs clarification
4. Native XMD should follow Genesis's mobile-first vision