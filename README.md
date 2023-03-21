# Bitmap2D++

**A C++ library for two-dimensional bit sets**

This library implements a class to store, manipulate and query 2D bit sets.
By default the data is stored in `size_t`, but this base type can be any other unsigned integral type like `unsigned char` or `unsigned short`.

## Build

This is a header-only library, so there's no need to build any binary.

Just `#include "bitmap2d.hpp"` and you're done.

Access to rows and columns is bounds checked by default.
If you want to disable bounds checking, e.g. to increase performance, place `#define BITMAP_UNCHECKED` right before the above `#include` directive.

## Usage

```cpp
#include "bitmap2d.hpp"

// create a bitmap with 64 rows and 1024 columns
bitmap2d<64, 1024> b;

// set a bit in row 23, column 42
b.set(23, 42);
// or
b.set(23, 42, true);

// clear a bit in row 23, column 42
b.unset(23, 42);
// or
b.set(23, 42, false);

// get bit in row 23, column 42
bool bit = b.get(23, 42);

// tell bitmap2d to use a std::array<uint8_t, ...> for data storage
bitmap2d<5, 23, uint8_t> b8;
```

--- 
--- 

_Copyright ©️ 2023 [Oliver Lau](mailto:oliver@ersatzworld.net)_

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
