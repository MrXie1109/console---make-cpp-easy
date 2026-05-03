# Console – Make C++ Easy / 让 C++ 变简单

A header‑only C++11 library that brings Python‑like productivity to C++.
**一个纯头文件、兼容 C++11 的现代 C++ 库，让你写得像 Python 一样痛快。**

📖 Documentation / 文档: [mrxie1109.github.io/console---make-cpp-easy](https://mrxie1109.github.io/console---make-cpp-easy)

---

## Quick Index / 快速索引

- [Core Utilities / 核心工具](#-core-utilities--核心工具)
- [String Processing / 字符串处理](#-string-processing--字符串处理)
- [Input & Output / 输入与输出](#-input--output--输入与输出)
- [Console Styling / 控制台美化](#-console-styling--控制台美化)
- [File System / 文件系统](#-file-system--文件系统)
- [Time & Timing / 时间与计时](#-time--timing--时间与计时)
- [Random Numbers / 随机数](#-random-numbers--随机数)
- [Progress Bar / 进度条](#-progress-bar--进度条)
- [Logging / 日志系统](#-logging--日志系统)
- [Regular Expressions / 正则表达式](#-regular-expressions--正则表达式)
- [Keyboard & Graphics / 键盘与图形](#-keyboard--graphics--键盘与图形)
- [Multi-dimensional Arrays & Math / 多维数组与数学计算](#-multi-dimensional-arrays--math--多维数组与数学计算)
- [Optional & Heterogeneous Container / 可选值与异构容器](#-optional--heterogeneous-container--可选值与异构容器)
- [Views & Iterators / 视图与迭代器](#-views--iterators--视图与迭代器)
- [Functional Programming / 函数式编程](#-functional-programming--函数式编程)
- [MIDI Music (Windows) / MIDI 音乐（Windows）](#-midi-music-windows--midi-音乐windows)

---

## 🔧 Core Utilities / 核心工具

**`std.h`** – Includes almost all C++ standard headers (C++11 to C++23).
**`std.h`** – 包含几乎所有 C++ 标准库头文件（C++11 到 C++23）。

**`csexc.h`** – Exception hierarchy derived from `std::runtime_error`.
**`csexc.h`** – 继承自 `std::runtime_error` 的异常体系。

**`sfinae.h`** – Compile-time type traits (`is_container`, `is_printable`, `is_string`, etc.).
**`sfinae.h`** – 编译期类型检测（容器、可打印、字符串等）。

**`info.h`** – Library version, license, platform and compiler info.
**`info.h`** – 库版本、许可证、平台和编译器信息。

```cpp
console::version();    // "console version 4.6.0 (2026-05-03)"
console::platform();   // "Windows" / "Linux" / "macOS"
console::compiler();   // "GCC 13.2" / "MSVC 1930"
```

---

## 🧵 String Processing / 字符串处理

**`strpp.h`** – Python‑style string utilities.
**`strpp.h`** – Python 风格的字符串工具。

**`literals.h`** – User‑defined literals for time and formatting.
**`literals.h`** – 时间和格式化的自定义字面量。

```cpp
using namespace console::literals;

trim("  hello  ");               // "hello"
upper("hello");                  // "HELLO"
split("a,b,c", ",");             // ["a", "b", "c"]
join(vec, ", ");                 // "a, b, c"

"Hello, {}"_f % "world";         // "Hello, world"
1_s; 2_min; 500_ms;              // Time literals
```

**`repr.h`** – Readable object representation (like Python's `repr`).
**`repr.h`** – 对象的可读表示（类似 Python 的 `repr`）。

---

## 📥 Input & Output / 输入与输出

**`output.h`** – `console::print` works like Python's `print`; all STL containers are printable.
**`output.h`** – `console::print` 用法同 Python `print`；所有 STL 容器直接输出。

**`input.h`** – Type‑safe input with prompts and validation.
**`input.h`** – 带提示和验证的类型安全输入。

**`outfwd.h`** – Forward declarations for STL container stream operators.
**`outfwd.h`** – STL 容器流运算符的前向声明。

```cpp
print("Hello", "world");         // "Hello world\n"

int x = input<int>("Enter number: ");
std::string s = inputLine("Name: ");
bool ok = inputYesOrNo("Continue? ");

std::vector<int> v{1, 2, 3};
std::cout << v;                  // "[1, 2, 3]"
```

---

## 🎨 Console Styling / 控制台美化

**`colorful.h`** – ANSI escape codes for colors and text styles.
**`colorful.h`** – 颜色和文本样式的 ANSI 转义码。

```cpp
std::cout << color::Red << "Error!" << color::Reset;
std::cout << color::BgBlue << color::BrightYellow << "Warning" << color::Reset;
std::cout << color::Bold << "Bold" << color::Reset;
```

16 foreground colors / 16 background colors / 9 text styles.
16 种前景色 / 16 种背景色 / 9 种文本样式。

---

## 📁 File System / 文件系统

**`file.h`** – `Path` class with automatic path separator conversion (Windows).
**`file.h`** – `Path` 类，Windows 上自动转换路径分隔符。

```cpp
Path p("data/config.txt");
std::string text = p.read_text();
p.write_text("new content");

Path dir("folder");
Path file = dir / "sub" / "data.txt";  // Path concatenation

p.exists(); p.touch(); p.ensure();
```

All operations throw `file_error` on failure.
所有操作失败时抛出 `file_error`。

---

## ⏱️ Time & Timing / 时间与计时

**`time.h`** – `Time` class (nanosecond precision), timing utilities.
**`time.h`** – `Time` 类（纳秒精度），计时工具。

```cpp
Time t = 500_ms;
std::cout << t;                  // "500ms"

auto elapsed = timer([] { heavy_computation(); });
sleep(1_s);

datetime();                      // "2026-05-03 14:30:00"
fps(60);                         // Frame rate limiter
```

---

## 🎲 Random Numbers / 随机数

**`random.h`** – Seeded Mersenne Twister, random selection, shuffling.
**`random.h`** – 真随机种子梅森旋转引擎，随机选择，打乱。

```cpp
int dice = randint(1, 6);
double prob = uniform(0.0, 1.0);
auto elem = choice(vec);
shuffle(vec);
```

---

## 📊 Progress Bar / 进度条

**`progress.h`** – Automatic progress bar for container iteration.
**`progress.h`** – 遍历容器时自动显示进度条。

```cpp
for (auto& x : progress(my_vector)) {
    process(x);  // Progress bar auto-updates
}
```

Styles / 样式: `normal()`, `simple()`, `beautiful()` (Unicode blocks).

---

## 📝 Logging / 日志系统

**`logging.h`** – Multi‑level logger with timestamps and colors.
**`logging.h`** – 带时间戳和彩色的多级别日志器。

```cpp
console::logger.info("Started");
console::logger.warn("Low memory");
console::logger.error("File not found");
console::logger.fatal("Crash!");  // throws fatal_logging
```

Levels / 级别: `DEBUG`, `INFO`, `WARN`, `ERROR`, `FATAL`.

---

## 🔍 Regular Expressions / 正则表达式

**`re.h`** – Python‑style regex module.
**`re.h`** – Python 风格的正则表达式模块。

```cpp
auto m = re::search(R"(\d+)", "price: 123");
if (m) std::cout << m.group();   // "123"

auto result = re::sub(R"(\s+)", "_", "hello   world");
// "hello_world"

auto parts = re::split(R"[\s,]+", "a,b c,d");
```

---

## ⌨️ Keyboard & Graphics / 键盘与图形

**`kb.h`** – Non‑blocking keyboard input (cross‑platform).
**`kb.h`** – 非阻塞键盘输入（跨平台）。

**`screen.h`** – Braille‑based console graphics (UTF‑8, block characters).
**`screen.h`** – 基于盲文的控制台图形（UTF‑8，方块字符）。

```cpp
Keyboard kb;
Key k = kb.get();      // Non‑blocking
Key k2 = kb.wait();    // Blocking

Screen<80, 40> screen;
screen.point(10, 10, true);
screen.line(0, 0, 79, 39, true);
screen.update();
```

---

## 📐 Multi-dimensional Arrays & Math / 多维数组与数学计算

**`multiarray.h`** – Compile‑time fixed‑size multi‑dimensional array.
**`multiarray.h`** – 编译期固定大小的多维数组。

**`matools.h`** – Statistics, linear algebra, elemwise ops, random init.
**`matools.h`** – 统计、线性代数、逐元素运算、随机初始化。

```cpp
MultiArray<int, 3, 4> mat;
mat(1, 2) = 42;

auto sum = console::sum(mat);
auto mean = console::mean(mat);

auto product = mat * mat;        // Element‑wise
auto result = matmul(A, B);      // Matrix multiplication
```

---

## 📦 Optional & Heterogeneous Container / 可选值与异构容器

**`maybe.h`** – `Maybe<T>` like `std::optional`.
**`maybe.h`** – `Maybe<T>` 类似 `std::optional`。

**`box.h`** – `Item` (type‑erased) and `Box` (vector of `Item`).
**`box.h`** – `Item`（类型擦除）和 `Box`（`Item` 的向量）。

**`rational.h`** – `BasicRational<T>` for fractions.
**`rational.h`** – 分数的 `BasicRational<T>`。

```cpp
Maybe<int> m = 42;
if (m) std::cout << *m;

Box box(1, "hello", 3.14);
int a; std::string b; double c;
box.unpack(a, b, c);

Rational r(1, 2);  // 1/2
auto sum = r + Rational(1, 3);  // 5/6
```

---

## 👁️ Views & Iterators / 视图与迭代器

**`view.h`** – Non‑owning container views.
**`view.h`** – 非拥有容器视图。

**`iter.h`** – `zip()` for parallel iteration, `IteratorPair`.
**`iter.h`** – `zip()` 并行迭代，`IteratorPair`。

```cpp
auto slice = make_view(vec, 1, 4);
for (auto& x : slice) { ... }

for (auto [a, b] : zip(vec1, vec2)) {
    // Parallel iteration
}
```

---

## 🔄 Functional Programming / 函数式编程

**`compre.h`** – `Comprehension<T>` with `map` and `filter`.
**`compre.h`** – 支持 `map` 和 `filter` 的 `Comprehension<T>`。

**`cursor_ptr.h`** – Dual‑pointer smart pointer (ownership + cursor).
**`cursor_ptr.h`** – 双指针智能指针（所有权 + 游标）。

```cpp
auto result = compre(vec)
    .map([](int x) { return x * 2; })
    .filter([](int x) { return x > 5; })
    .to<std::vector<int>>();
```

---

## 🎵 MIDI Music (Windows) / MIDI 音乐（Windows）

**`win/melody.h`** – Windows MIDI output (requires `winmm`).
**`win/melody.h`** – Windows MIDI 输出（需链接 `winmm`）。

```cpp
MIDI midi(Instrument::AcousticGrandPiano, 120);
midi.play(Note(pitches::C4, 1.0));
```

---

## ⚙️ Build Requirements / 构建要求

- **C++11** or later / 或更高版本
- **Header‑only** – just include / 纯头文件，包含即用
- **Cross‑platform** (MIDI: Windows only) / 跨平台（MIDI 仅 Windows）

---

## 📄 License / 许可证

MIT © MrXie1109
