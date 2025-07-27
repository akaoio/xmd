# 1: This is my tree, directly print with out set var:

<!-- xmd:
exec tree /data/data/com.termux/files/home/xmd/src/
-->

---

# 2: set var from exec call

And this is another way to use it, with set var, <!-- xmd:
set mytree = exec tree /data/data/com.termux/files/home/xmd/src/
-->and it just works:

{{mytree}}

---

# 3: print var

And this should also work too:

<!-- xmd:
print(mytree)
-->
