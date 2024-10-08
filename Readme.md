## What

(2024-10..)

Experimental library for strings. AVR. Arduino.


## Details

### What "me_String" does

It allows you to print values of basic types without thinking of their
representation. They will be represented in some consistent way
and you'd better love the way they are represented. Or modify
implementation to suit your taste.

### Growth directions

Most likely I'll need concatenation at some time. Maybe trimming.
Possibly hex representation.


## Sample output

```
[me_String] Okay, we are here.
Test [03.14 15].
+00123
ABCDEF
[me_String] Done.
```

## Code

* [Example][Example]
* [Interface][Interface]
* Implementation
  * [Class][Implementation]
  * [Freetown][Freetown]

## See also

* [My other embedded C++ libraries][Embedded]
* [My other repositories][Repos]

[Example]: examples/me_String/me_String.ino
[Interface]: src/me_String.h
[Implementation]: src/me_String.cpp
[Freetown]: src/me_String_Freetown.cpp

[Embedded]: https://github.com/martin-eden/Embedded_Crafts/tree/master/Parts
[Repos]: https://github.com/martin-eden/contents
