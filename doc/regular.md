---
title: This will be used as the title-tag of the page head
---


## Concept: Regular

A *regular type* is one that can be used, to an extent, like an `int`.
Regular types can be default constructed, moved, copied, and compared
for equality. They are not however, required to be [Ordered](ordered.html).

```
template<typename T>
concept bool Regular()
```

