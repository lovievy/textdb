# textdb

A simple key-value store library that maps string keys to string values. All data is stored in a single file assigned by the Open method. The latest key-value data will be appended to the end of the file. When querying the value corresponding to a key, the search will start from the end of the file and return the first matching result found.

![image](https://user-images.githubusercontent.com/41776735/231473945-7aca7d90-2f00-4b9c-bf4d-6137f946c91a.png)

## Build & Install

```bash
mkdir -p build && cd build
cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build .
```

```bash
cmake --install .
```

```bash
xargs rm < install_manifest.txt # uninstall
```


## Examples

```cpp
#include <textdb/db.h>

int main() {
    auto db = textdb::DB("store.textdb");

    db.Put("k1", "v1");
    db.Put("k2", "v2");
    std::cout << db.Get("k1") << std::endl;
    std::cout << db.Get("k2") << std::endl;

    db.Close();
    return 0;
}
```

## Benchmark

```
Run on (12 X 2592.01 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 256 KiB (x6)
  L3 Unified 12288 KiB (x1)
Load Average: 0.24, 0.10, 0.10
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
DB_Put                  3980 ns         3999 ns       171484
DB_Get                 10938 ns        10943 ns        64261
DB_GetNonexistent     256633 ns       256631 ns         2585
```