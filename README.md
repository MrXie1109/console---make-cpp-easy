# console – Make C++ Easy / 让 C++ 变简单

A header‑only C++11 library that brings Python‑like productivity to C++.
**一个纯头文件、兼容 C++11 的现代 C++ 库，让你写得像 Python 一样痛快。**

📖 Documentation / 文档: [mrxie1109.github.io/console---make-cpp-easy](https://mrxie1109.github.io/console---make-cpp-easy)

---

## Quick Index / 快速索引

- [Core Utilities / 核心工具](#core-utilities)
- [String Processing / 字符串处理](#string-processing)
- [Input & Output / 输入与输出](#input--output)
- [Console Styling / 控制台样式](#console-styling)
- [Logging / 日志](#logging)
- [Time & Timing / 时间与计时](#time--timing)
- [Random Numbers / 随机数](#random-numbers)
- [Regular Expressions / 正则表达式](#regular-expressions)
- [File System / 文件系统](#file-system)
- [Progress Bar / 进度条](#progress-bar)
- [Multi‑dimensional Arrays / 多维数组](#multi-dimensional-arrays)
- [Optional Value / 可选值](#optional-value)
- [Heterogeneous Container / 异构容器](#heterogeneous-container)
- [Rational Numbers / 有理数](#rational-numbers)
- [Views & Iterators / 视图与迭代器](#views--iterators)
- [Functional Comprehension / 函数式推导](#functional-comprehension)
- [Cursor Pointer / 游标指针](#cursor-pointer)
- [User‑defined Literals / 自定义字面量](#user-defined-literals)
- [Win32 MIDI / Win32 MIDI 音乐](#win32-midi)

---

## Core Utilities / 核心工具

**std.h** includes almost all C++ standard headers (C++11 and up).
**std.h** 帮你一次性包含几乎所有标准库头文件，从 C++11 开始全支持。

**csexc.h** defines exception classes derived from `std::runtime_error` (`file_error`, `bad_get`, `bad_maybe_access`, etc.).
**csexc.h** 定义了继承自 `std::runtime_error` 的异常体系（比如文件错误、类型获取错误、空 Maybe 访问等）。

**sfinae.h** provides compile‑time type traits: `is_container`, `is_printable`, `is_string`, `is_char`, `has_subscript` and more.
**sfinae.h** 提供编译期类型检测：是不是容器？能不能打印？是不是字符串？有没有下标访问？全都帮你判断好。

---

## String Processing / 字符串处理

**strpp.h** gives you Python‑style string tools:
**strpp.h** 提供 Python 风格的字符串处理：

- `trim` / `ltrim` / `rtrim` (remove whitespace or custom characters)
  去除空白或自定义字符
- `upper` / `lower` / `title` – case conversion
  大小写转换、标题格式
- `split` / `join` / `partition`
  分割、连接、三分区
- `uni_to_str(...)` – convert any arguments to string
  将任意数量、任意类型的参数拼接成字符串
- `f_string` – format with `{}` placeholder: `"Hello {}"_f % "world"`
  用 `{}` 占位符格式化字符串

---

## Input & Output / 输入与输出

**output.h** gives `console::print` (works like Python’s `print`), and a customizable `Output` class.
**output.h** 提供了 `console::print`，用法和 Python 的 `print` 一模一样，还可以自定义分隔符、结尾符和是否刷新。

All common STL containers (`vector`, `list`, `map`, `set`, `tuple`, `pair`, `valarray`, …) can be printed directly – no extra code.
所有常见 STL 容器（`vector`、`list`、`map`、`set`、`tuple`、`pair`、`valarray` ……）都支持直接输出，不需要写任何循环。

**repr.h** generates readable representations (like Python’s `repr`) and demangles type names.
**repr.h** 可以生成对象的可读表示（类似 Python 的 `repr`），还能输出经过 demangle 的类型名。

**input.h** provides type‑safe input: `input<T>("prompt")`, `inputLine`, `inputNumber`, `inputYesOrNo`, and `inputAll`.
**input.h** 提供类型安全的输入：`input<T>`、整行读取、数字输入、问 yes/no、读取所有内容等。

---

## Console Styling / 控制台样式

**colorful.h** contains ANSI escape codes for foreground/background colors and text styles (bold, italic, underline, blink, etc.).
**colorful.h** 提供了 ANSI 转义码，可以设置前景色、背景色、粗体、斜体、下划线、闪烁等样式。

Just output `color::Red << "text" << color::Reset`.
直接输出 `color::Red << "文本" << color::Reset` 就能带颜色。

---

## Logging / 日志

**logging.h** offers a multilevel logger (`DEBUG`, `INFO`, `WARN`, `ERROR`, `FATAL`) with automatic timestamps, optional colors, and stream output.
**logging.h** 是一个多级别日志器，自带时间戳、可选彩色输出，支持流式输出。

You can set the minimum level or enable/disable each level individually. `FATAL` throws a `fatal_logging` exception.
可以设置最低级别，也可以单独开关每个级别。`FATAL` 级别会抛出异常。

A global instance `console::logger` is ready to use.
全局实例 `console::logger` 开箱即用。

---

## Time & Timing / 时间与计时

**time.h** defines a `Time` class that stores nanoseconds, with conversions to `us`, `ms`, `s`, `min`, `hr`.
**time.h** 定义了 `Time` 类，内部用纳秒存储，可以方便地转换成微秒、毫秒、秒、分、小时。

- `now()` returns the current time point.
  获取当前时间点
- `timer(func, args...)` measures execution time.
  测量函数执行时间
- `sleep(Time)` sleeps for the given duration.
  睡眠指定时长
- `datetime()` returns a formatted local time string.
  返回格式化的本地时间字符串

**literals.h** adds user‑defined literals like `1_s`, `500_ms`, `3_min` (both integer and floating‑point).
**literals.h** 提供了自定义字面量：`1_s`、`500_ms`、`3_min`，整数和浮点数都支持。

---

## Random Numbers / 随机数

**random.h** provides a seeded Mersenne Twister engine.
**random.h** 提供了一个以真随机数种子初始化的梅森旋转引擎。

- `randint<T>(min, max)` – uniform integer
  均匀整数
- `uniform<T>(min, max)` – uniform floating‑point
  均匀浮点数
- `choice(container)` – pick a random element
  随机选择元素
- `shuffle(container)` – Fisher‑Yates shuffle
  随机打乱

---

## Regular Expressions / 正则表达式

**re.h** emulates Python’s `re` module.
**re.h** 模仿了 Python 的 `re` 模块。

- `Regex` class (compiled pattern) with methods: `search`, `match`, `fullmatch`, `findall`, `finditer`, `split`, `sub`, `subn`.
  `Regex` 类（编译后的模式）支持搜索、全匹配、查找全部、分割、替换等。
- Namespace `re` provides functional versions: `re::search`, `re::sub`, etc.
  命名空间 `re` 提供了函数式接口，用起来和 Python 基本一样。
- `re::escape` escapes regex metacharacters.
  自动转义特殊字符。

```cpp
auto m = re::search(R"(\d+)", "price: 123");
if (m) cout << m.group();   // "123"
```

---

## File System / 文件系统

**file.h** provides a `Path` class with automatic path separator conversion on Windows.
**file.h** 提供了 `Path` 类，在 Windows 上会自动转换路径分隔符。

- `read_text()` / `write_text()` – text mode
  文本读写
- `read_binary()` / `write_binary()` – binary mode
  二进制读写
- `read_lines()` / `write_lines()` – line‑oriented
  按行读写
- `read_POD<T>()` / `write_POD()` – read/write trivially copyable types (with `static_assert` safety)
  读写平凡可复制类型，编译时检查类型安全性
- `exists()`, `touch()`, `ensure()` – file existence and creation utilities
  检查存在、创建空文件、确保文件存在

All I/O operations throw `file_error` on failure.
所有文件操作失败都会抛出 `file_error`。

---

## Progress Bar / 进度条

**progress.h** lets you wrap any container and automatically display a progress bar while iterating.
**progress.h** 可以包装任何容器，在遍历时自动显示进度条。

Customizable appearance: width, fill character, empty character, prefix/suffix, percentage on/off.
可以自定义宽度、填充字符、空字符、前缀后缀、是否显示百分比。

Pre‑defined styles: `ProgressStyle::normal()`, `simple()`, `beautiful()` (uses Unicode block characters).
内置了几种风格：常规、简洁、美观（使用 Unicode 方块字符）。

```cpp
for (auto& x : progress(my_vector)) {
    // your code
}
```

---

## Multi‑dimensional Arrays / 多维数组

**multiarray.h** provides `MultiArray<T, Dims...>` – a fixed‑size multidimensional array built from recursive `std::array`.
**multiarray.h** 提供了 `MultiArray<T, Dims...>`，一个编译期固定维度的多维数组，内部递归继承自 `std::array`。

- Bounds‑checked access with `operator()`.
  用 `operator()` 进行带边界检查的访问
- Element‑wise arithmetic, comparison, logical, bitwise operators (array‑array and array‑scalar).
  支持逐元素的算术、比较、逻辑、位运算，既可以是两个数组，也可以是数组和标量。
- `flatten()`, `fbegin()`, `fend()` for linear iteration.
  可以将多维数组展平为一维迭代。
- **matools.h** provides statistics (`mean`, `variance`, `stddev`), linear algebra (`dot`, `norm`, `matmul`, `transpose`, `cross`), trigonometry, exponent/log, random initialization, convolution, and more.
  **matools.h** 提供了大量数学工具：统计、线性代数、三角函数、指数对数、随机初始化、卷积等。

```cpp
MultiArray<int, 3, 4> mat;
mat(1,2) = 42;
auto sum = console::sum(mat);
```

---

## Optional Value / 可选值

**maybe.h** gives `Maybe<T>` (similar to `std::optional`).
**maybe.h** 提供了 `Maybe<T>`，类似 `std::optional`。

- `nothing` tag to represent empty state.
  用 `nothing` 表示空状态。
- `value()` (throws `bad_maybe_access`), `value_or()`, `reset()`.
  获取值（空时抛异常）、提供默认值、重置。
- Stream I/O is supported: reading an invalid value sets the `Maybe` to `nothing`.
  支持流输入输出：输入失败时自动置为 `nothing`。

---

## Heterogeneous Container / 异构容器

**box.h** provides `Item` (type‑erased wrapper) and `Box` (a vector of `Item`).
**box.h** 提供了 `Item`（类型擦除包装器）和 `Box`（`Item` 的向量）。

- `Item` can store any copyable type; `get<T>()` safely retrieves the value with type checking; `unsafe_get<T>` skips checks.
  `Item` 可以存储任意可拷贝类型；`get<T>()` 会检查类型是否匹配；`unsafe_get<T>` 不做检查。
- `Box` can be constructed from mixed types, like `Box(1, "hello", 3.14)`.
  `Box` 可以用多种不同类型的值直接构造，例如 `Box(1, "hello", 3.14)`。
- `unpack` extracts values into variables (type‑safe).
  `unpack` 可以把 `Box` 里的值按顺序解包到变量中，类型安全。
- Printing a `Box` looks like a tuple: `(1, hello, 3.14)`.
  输出 `Box` 就像元组：`(1, hello, 3.14)`。

---

## Rational Numbers / 有理数

**rational.h** defines `BasicRational<T>` (requires signed integral `T`).
**rational.h** 定义了 `BasicRational<T>`，要求 `T` 是有符号整数类型。

- Arithmetic operators (`+`, `-`, `*`, `/`) with automatic reduction.
  四则运算，自动约分。
- Comparison operators.
  比较运算。
- Stream I/O (reads `a/b` or `a`).
  支持流输入输出（可读 `a/b` 或 `a`）。
- Predefined aliases: `Rational` (`intmax_t`), `Rational_32`, `Rational_64`, etc.
  预定义了常用别名，例如 `Rational`（用 `intmax_t`）、`Rational_32`、`Rational_64` 等。

---

## Views & Iterators / 视图与迭代器

**view.h** provides a non‑owning `View<Container>` representing a contiguous slice.
**view.h** 提供了非拥有视图 `View<Container>`，表示容器的一个连续区间。

- `size()`, `operator[]`, `at()` (bounds‑checked), `collect()` to copy into a new container.
  支持大小、下标访问（带越界检查的 `at`）、`collect()` 复制到新容器。
- Factory `make_view` works with containers, iterator pairs, and raw pointers.
  工厂函数 `make_view` 可以从容器、迭代器对、原生指针创建视图。
- Special printing for `View<string>` prints the concatenated string.
  `View<string>` 的输出会直接拼接所有字符串，不加中括号。

**iter.h** provides `zip(c1, c2)` for parallel iteration (stops at the shorter sequence).
**iter.h** 提供了 `zip(c1, c2)`，可以同时遍历两个容器，在较短者结束时自动停止。

- `IteratorPair` helps adapt iterator ranges for range‑based for loops.
  `IteratorPair` 可以把迭代器对包装成支持范围 for 循环的对象。

```cpp
vector<int> a{1,2,3};
vector<string> b{"a","b","c"};
for (auto [x, y] : zip(a, b)) {
    // x is int, y is string
}
```

---

## Functional Comprehension / 函数式推导

**compre.h** gives `Comprehension<T>` – a container wrapper that supports `map`, `filter`, and conversion to other containers.
**compre.h` 提供了 `Comprehension<T>`，这是一个容器包装器，支持 `map`、`filter` 等操作，并可以转换成其他容器。

- Construct from any container, iterator pair, initializer list.
  可以从任何容器、迭代器对、初始化列表构造。
- `map(function)` applies transformation and returns a new `Comprehension`.
  `map` 对每个元素做变换，返回新的 `Comprehension`。
- `filter(predicate)` keeps elements satisfying the condition.
  `filter` 筛选符合条件的元素。
- `to<Container>()` moves elements into a new container (using move iterators).
  `to<Container>()` 将内部元素移动构造到目标容器。
- `make()` copies elements.
  `make()` 拷贝元素到目标容器。

```cpp
auto result = compre(vec)
                .map([](int x){ return x*2; })
                .filter([](int x){ return x>5; })
                .to<vector<int>>();
```

---

## Cursor Pointer / 游标指针

**cursor_ptr.h** defines `cursor_ptr<T>` – a dual‑pointer smart pointer.
**cursor_ptr.h** 定义了一个“双指针”智能指针 `cursor_ptr<T>`。

- `original_ptr` owns the memory (deleted in destructor).
  `original_ptr` 持有内存所有权，析构时释放。
- `current_ptr` points to the current position and supports pointer arithmetic.
  `current_ptr` 指向当前位置，支持指针运算。
- Copy constructor/assignment **do not** transfer ownership (only copy `current_ptr`).
  拷贝构造/赋值**不转移所有权**，只复制 `current_ptr`。
- Move transfers ownership.
  移动会转移所有权。
- Specialization for `T[]` uses `delete[]`.
  对数组特化，使用 `delete[]`。

Useful when you need separate ownership and view semantics.
适合需要分离所有权和游标访问的场景。

---

## User‑defined Literals / 自定义字面量

**literals.h** – inside `namespace console::literals`:

- Time literals: `_ns`, `_us`, `_ms`, `_s`, `_min`, `_hr` (both integer and floating‑point overloads).
  时间字面量：纳秒、微秒、毫秒、秒、分钟、小时，整数和浮点数都支持。
- Format string literal: `"Hello {}"_f` returns an `f_string` that can be formatted with `%`.
  格式化字符串字面量：返回 `f_string` 对象，可以用 `%` 替换 `{}` 占位符。

```cpp
using namespace console::literals;
Time t = 500_ms;
auto msg = "Value: {}"_f % 42;
```

---

## Win32 MIDI / Win32 MIDI 音乐

**win/melody.h** (Windows only, requires linking `winmm`).
**win/melody.h**（仅 Windows，需要链接 `winmm` 库）。

- `Instrument` enum (128 GM instruments).
  枚举了 128 种 GM 标准乐器。
- `pitches` namespace provides MIDI note numbers (C4 = 60, etc.) and `REST`.
  `pitches` 命名空间提供了 MIDI 音高常量（中央 C 是 60，还有休止符 `REST`）。
- `Note` structure: pitch, duration (in quarter beats), velocity.
  `Note` 结构体：音高、时值（以四分音符为单位）、力度。
- `MIDI` class: open device, set instrument/volume/BPM, play notes (synchronous `play` or asynchronous `nplay`).
  `MIDI` 类：打开设备、切换乐器、调节音量和速度、播放音符（同步 `play` 或异步 `nplay`）。
- Asynchronous play spawns a detached thread – be careful about object lifetime.
  异步播放会启动分离线程，注意 MIDI 对象的生命周期要覆盖播放时间。

```cpp
MIDI midi(Instrument::AcousticGrandPiano, 120);
Note tune[] = {{pitches::C4, 1.0}, {pitches::E4, 1.0}, {pitches::G4, 2.0}};
midi.play(tune);
```

---

## Requirements / 要求

- **C++11** or later.
  需要 C++11 或更高版本。
- **Header‑only** – just include what you need.
  纯头文件，包含即用。
- **Cross‑platform** (MIDI part is Windows‑only, everything else works on Linux/macOS as well).
  跨平台（MIDI 仅 Windows，其他模块在 Linux/macOS 也能用）。

---

## License / 许可证

MIT © MrXie1109

For complete documentation, examples, and migration guides, visit:
完整文档、示例和迁移指南请访问：
👉 [mrxie1109.github.io/console---make-cpp-easy](https://mrxie1109.github.io/console---make-cpp-easy)
