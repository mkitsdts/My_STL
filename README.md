# My_STL

A lightweight educational reimplementation of selected components of the C++ Standard Library (based on C++17).  
Focus: understanding allocator design, container invariants, basic algorithms, and iterator semantics.

## Features

Implemented (core parts):
- Custom small-block memory allocator (Alloc)
- Containers:
  - My_Vector
  - My_List (doubly linked list)
  - My_Deque (EXPERIMENTAL: still buggy, see Status)
  - My_Set (based on red-black tree)
  - RBTree (standalone)
  - HashTable (basic separate chaining or bucket-style implementation depending on your code)
  - My_String (simple dynamic string)
  - My_Shared_Ptr (simple)
  - My_Unique_Ptr (simple)
- Algorithms (partial):
  - swap
  - sort (hybrid quick sort / small-range optimization placeholder)
  - quick_sort / shell_sort / heap_sort (educational)
  - simple integer log
- Iterators for custom containers

## Status

| Component  | State            | Notes |
| ---------- | ---------------- | ----- |
| Allocator  | Stable (single-threaded) | No thread safety; no memory pool release |
| Vector     | Usable           | Lacks exception guarantees |
| List       | Usable           | Check edge cases in splice (if added) |
| Deque      | BUGGY            | Iterator arithmetic & block reallocation need fixes |
| Set / RBTree | Usable        | Insert / iteration OK; erase needs more tests |
| HashTable  | Basic            | No rehash shrinking; load factor handling minimal |
| String     | Usable (basic)   | No SSO; no full std::string API |
| Algorithms | Incomplete       | sort comparator overload needs refinement |

## Design Highlights

### Alloc (Small-Object Allocator)
- Size classes up to 128 bytes in 8-byte alignment buckets.
- Free lists per size class.
- Chunk allocation strategy: exponential growth + leftover recycling.
- No thread safety / no coalescing / no deallocation of large chunks back to OS.

### RBTree / Set
- Standard red-black properties maintained on insert.
- Iterator provides in-order traversal.
- Color fix-up logic separated for clarity.

### Vector
- Doubling growth strategy (assumed).
- Raw pointer + manual construction (placement new if adopted in your code).

### Deque (Issues To Fix)
Common problems to address:
- Block map expansion when pushing at front.
- Iterator increment/decrement across block boundaries.
- Correct calculation of begin()/end() when first block becomes empty.
- Consistent size vs capacity bookkeeping.

### HashTable
- Simple bucket-based.
- Basic insert / erase / count.
- Rehash condition minimal (improve load factor strategy).

## Build

### 1. Using xmake (recommended)
```
xmake f -m debug
xmake
xmake run
```

Generate compile_commands.json for better IDE integration:
```
xmake project -k compile_commands
```

### 2. Manual (Apple Clang)
```
xcrun clang++ -std=c++17 $(find src -name "*.cpp") -I src -O0 -g -o build/app
./build/app
```

### 3. Homebrew LLVM (if installed)
```
clang++ -std=c++17 $(find src -name "*.cpp") -I src -stdlib=libc++ -O0 -g -o build/app
```

### VS Code (Suggested)
- tasks.json: run build command (clang or xmake)
- launch.json: point program to build/app or xmake output
- c_cpp_properties.json: set compilerPath and (optionally) compileCommands

## Quick Usage Example

```cpp
#include "container/my_vector.hpp"
#include <iostream>
int main() {
    STL::My_Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    for (auto &x : v) std::cout << x << " ";
    std::cout << "\n";
}
```

## Planned Improvements (Roadmap)

- Fix My_Deque block/iterator model
- Add copy/move semantics completeness across containers
- Provide allocator-aware container integration
- Add unit tests (GoogleTest or Catch2)
- Exception safety audits
- Expand algorithm set (merge_sort, stable_sort, lower_bound, etc.)
- Optional thread-safe allocator variant

## Known Limitations

- No exception safety guarantees (strong/commit semantics) in most operations
- No thread safety
- Memory is never returned to OS (small allocator)
- HashTable lacks iterators + advanced policies
- String missing many std::string APIs

Feel free to open an issue for clarification or enhancement discussions.