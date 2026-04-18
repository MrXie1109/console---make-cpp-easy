# console 库 / console Library

[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![C++14](https://img.shields.io/badge/C++-14-blue.svg)](https://en.cppreference.com/w/cpp/14)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![C++20](https://img.shields.io/badge/C++-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![C++23](https://img.shields.io/badge/C++-23-blue.svg)](https://en.cppreference.com/w/cpp/23)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![No Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen.svg)]()

**console** 是一个轻量级、零外部依赖的 C++ 控制台工具库，提供简洁的 API 用于输入输出、日志记录、时间测量、随机数、字符串处理、文件操作、多维数组等常见任务。所有组件位于 `namespace console`，核心模块可通过 `#include "console/all.h"` 一键引入。

**console** is a lightweight, zero‑dependency C++ console utility library offering simple APIs for common tasks. All components are inside `namespace console`; include via `#include "console/all.h"`.

---

## 目录

1. [特性](#特性)
2. [模块概览](#模块概览)
3. [快速开始](#快速开始)
4. [详细使用指南](#详细使用指南)
   - [输出](#输出-outputh)
   - [输入](#输入-inputh)
   - [日志](#日志-loggingh)
   - [时间](#时间-timeh)
   - [随机数](#随机数-randomh)
   - [字符串处理](#字符串处理-strpph)
   - [颜色](#颜色-colorfulh)
   - [进度条](#进度条-progressh)
   - [文件操作](#文件操作-fileh)
   - [异构容器](#异构容器-boxh)
   - [多维数组](#多维数组-multiarrayh)
   - [双指针游标](#双指针游标-cursor_ptrh)
   - [字面量](#字面量-literalsh)
   - [容器视图](#容器视图-viewh)
   - [列表推导](#列表推导-compreh)
   - [SFINAE 工具](#sfinae-工具-sfinae-h)
   - [正则表达式](#正则表达式-reh)
   - [系统信息](#系统信息-infoh)
   - [可选值](#可选值-maybeh)
   - [数学工具](#数学工具-matoolsh)
   - [异常类](#异常类-csexch)
   - [格式化表示](#格式化表示-reprh)
   - [Windows MIDI](#windows-midi-winmelodyh)
5. [编译要求](#编译要求)
6. [许可证](#许可证)

---

## 特性

| 特性 | 说明 |
|------|------|
| 🚀 **多标准支持** | 兼容 C++11/14/17/20/23 |
| 📦 **零外部依赖** | 仅使用 C++ 标准库 |
| 🎯 **简洁 API** | 直观命名，减少样板代码 |
| 🎨 **彩色输出** | ANSI 颜色常量，支持样式 |
| 📝 **日志系统** | 5 级别，时间戳，彩色，FATAL 抛异常 |
| ⏱️ **时间工具** | `Time` 类自动单位，计时器 `timer()`，休眠 `sleep()`，日期格式化 |
| 🔢 **随机数** | Mersenne Twister，`randint`, `uniform`, `choice`, `shuffle` |
| 📄 **文件操作** | `Path` 类，文本/二进制/POD 读写，路径拼接 |
| 🎭 **类型擦除** | `Item` 存储任意类型，`Box` 异构容器 |
| 🔷 **多维数组** | `MultiArray<T, Dims...>`，连续存储，逐元素运算，统计函数 |
| 👁️ **容器视图** | `View<Container>` 非拥有视图，切片，边界检查 |
| 🧵 **字符串处理** | 修剪、大小写、分割、连接、`f_string` 格式化 |
| 📊 **进度条** | `Progress` 迭代器包装，自动显示，节流刷新 |
| 🧩 **列表推导** | `Comprehension<T>`，`map`/`filter` 链式操作 |
| 🔍 **SFINAE 工具** | 类型特征：`is_container`, `is_callable`, `is_printable` 等 |
| 🔤 **正则表达式** | `Regex` 类，类似 Python `re` 模块 |
| ℹ️ **系统信息** | `version()`, `platform()`, `compiler()` |
| ✨ **可选值** | `Maybe<T>`，类似 `std::optional` |
| 🛠️ **数学工具** | 统计、线性代数、元素级函数、卷积等 |
| 🎵 **MIDI 播放** | Windows 专用，封装 winmm，支持 GM 乐器 |
| 🧰 **一站式头文件** | `std.h` 聚合标准库，`all.h` 包含全部模块 |

---

## 模块概览

| 头文件 | 功能 |
|--------|------|
| `output.h` | STL 容器输出、`print` 函数 |
| `input.h` | 类型安全输入、范围检查 |
| `time.h` | 时间量、计时、休眠、日期时间 |
| `random.h` | 随机数生成、选择、打乱 |
| `strpp.h` | 字符串处理、`f_string` 格式化 |
| `colorful.h` | ANSI 颜色常量 |
| `logging.h` | 多级别日志 |
| `progress.h` | 进度条显示 |
| `file.h` | 跨平台文件路径和 I/O |
| `box.h` | 异构容器 `Item` / `Box` |
| `multiarray.h` | 编译期多维数组 |
| `cursor_ptr.h` | 双指针智能指针 |
| `literals.h` | 用户定义字面量 |
| `view.h` | 容器非拥有视图 |
| `compre.h` | 列表推导式 |
| `sfinae.h` | 编译期类型特征 |
| `re.h` | 正则表达式 |
| `info.h` | 系统信息 |
| `maybe.h` | 可选值包装 |
| `matools.h` | 多维数组数学工具 |
| `csexc.h` | 自定义异常 |
| `repr.h` | 值的字符串表示 |
| `win/melody.h` | Windows MIDI 播放 |

---

## 快速开始

```cpp
#include "console/all.h"
using namespace console;
using namespace console::literals;

int main() {
    print("Hello, World!");

    std::string name = inputLine("Your name? ");
    int age = input<int>("Age? ");
    logger.info("User:", name, "age:", age);

    auto t = timer([]{ sleep(500_ms); });
    print("Slept for:", t);   // 自动输出 "500ms"

    int lucky = randint(1, 100);
    print("Lucky:", lucky);

    std::string msg = f_string("Hello, {}!") % name;
    print(msg);

    auto match = re::search(R"(\d+)", msg);
    if (match) print("Found number:", match.group());

    MultiArray<int, 2, 2> mat{{1,2},{3,4}};
    print("Matrix:", mat);

    Path("output.txt").write_text(msg);

    Maybe<int> m = 42;
    print("Maybe:", m);

    print("Version:", version());
    return 0;
}
```

---

## 详细使用指南

### 输出 (output.h)

重载 STL 容器 `operator<<`，提供 `print` 函数（默认空格分隔，换行，自动刷新）。

```cpp
std::vector<int> vec = {1,2,3};
std::cout << vec;                     // [1, 2, 3]
print("Value:", 42, vec);             // Value: 42 [1, 2, 3]

Output err(std::cerr, "", "\n", true); // 自定义输出
err("Error:", "msg");

int carr[] = {10,20,30};
auto arr = to_array(carr);            // std::array<int,3>
auto v = to_vector(carr);             // std::vector<int>
```

### 输入 (input.h)

类型安全输入，自动重试。

```cpp
std::string s = input("Enter: ");
int age = input<int>("Age: ");
double temp = inputWithRange("Temp (-50~50): ", -50.0, 50.0);
char ch = inputChar("Press any key: ");
bool ok = inputYesOrNo("Continue? ");
std::string line = inputLine("Line: ");
std::string all = inputAll("Input (EOF to end):\n");
```

### 日志 (logging.h)

5 个级别，全局 `logger`。

```cpp
logger.set(Logging::Level::DEBUG);
logger.debug("Debug:", 42);
logger.info("Started");
logger.warn("Low disk");
logger.error("File not found");
try { logger.fatal("Critical"); } catch (const fatal_logging& e) {}
```

### 时间 (time.h)

`Time` 类，纳秒存储，自动选择单位。字面量 `_ns`, `_us`, `_ms`, `_s`, `_min`, `_hr`。

```cpp
Time t1 = 100_ns, t2 = 2.5_us, t3 = 500_ms;
std::cout << t1 << ", " << t2 << ", " << t3; // 100ns, 2.5μs, 500ms
sleep(200_ms);
auto elapsed = timer([]{ sleep(1_s); });
print(datetime());              // 2026-04-18 12:34:56
print(datetime("%Y年%m月%d日"));
```

### 随机数 (random.h)

全局 Mersenne Twister 引擎。

```cpp
int dice = randint(1, 6);
double prob = uniform();        // [0.0, 1.0]
double temp = uniform(-10.0, 40.0);
int selected = choice({10,20,30});
std::vector<int> vec = {1,2,3,4,5};
shuffle(vec);
```

### 字符串处理 (strpp.h)

```cpp
trim("  hello  ");               // "hello"
upper("Hello");                  // "HELLO"
lower("Hello");                  // "hello"
title("hello world");            // "Hello World"
split("a,b,c", ",");             // ["a","b","c"]
join(parts, "-");                // "a-b-c"
auto [l,m,r] = partition("key=value", "=");
uni_to_str(42, " + ", 3.14);     // "42 + 3.14"

f_string fmt = "Hello, {}!"_f;
std::string result = fmt % name;
```

### 颜色 (colorful.h)

```cpp
using namespace console::color;
std::cout << Red << "Error" << Reset << std::endl;
std::cout << Bold << Blue << "Bold blue" << Reset;
```

### 进度条 (progress.h)

```cpp
std::vector<int> data(100);
for (auto& x : progress(data, ProgressStyle::normal())) {
    // 处理，自动刷新进度条
}
// 内置样式：normal(), beautiful() (Unicode块)
```

### 文件操作 (file.h)

`Path` 类，自动处理 Windows 分隔符。

```cpp
Path file("data.txt");
file.write_text("Hello");
std::string s = file.read_text();
file.write_lines({"line1","line2"});
auto lines = file.read_lines();
file.write_binary({0x01,0x02});
auto bin = file.read_binary();
struct Point { int x,y; };
file.write_POD(Point{10,20});
auto p = file.read_POD<Point>();
Path backup = Path("backup") / "data.txt";
if (!file.exists()) file.touch();
```

### 异构容器 (box.h)

`Item` 擦除类型，`Box` 是 `vector<Item>`。

```cpp
Box box(42, 3.14, "hello");
int i = box.get<int>(0);        // 42，类型不匹配抛 bad_get
double d = box.get<double>(1);
int a; double b; std::string c;
box.unpack(a, b, c);            // 解包
std::cout << box;               // (42, 3.14, "hello")
```

### 多维数组 (multiarray.h)

`MultiArray<T, Dims...>` 编译期固定维度，连续存储。

```cpp
MultiArray<int, 2, 2> mat{1,2,3,4};   // [[1,2],[3,4]]
mat[0][1] = 99;
int val = mat(1,1);                    // 边界检查
for (auto it = mat.fbegin(); it != mat.fend(); ++it) *it *= 2;
auto sum = mat + mat;                  // 逐元素
auto cmp = mat == 42;                  // MultiArray<bool,2,2>
int total = sum(mat);
int minv = min(mat);
auto flat = multiarray_cast<4>(mat);   // 形状转换
```

### 双指针游标 (cursor_ptr.h)

管理单个对象或数组，拥有原始指针和游标指针。

```cpp
cursor_ptr<int> p(new int(42));
*p = 100;
cursor_ptr<int[]> arr(new int[5]{10,20,30,40,50});
for (int i=0; i<5; ++i) std::cout << *arr++ << ' ';
arr -= 5;   // 复位
```

### 字面量 (literals.h)

```cpp
using namespace console::literals;
auto t = 100_ns;          // Time
auto fmt = "Value: {}"_f; // f_string
```

### 容器视图 (view.h)

非拥有视图，保存迭代器对，支持切片和 `at()` 边界检查。

```cpp
std::vector<int> vec = {0,1,2,3,4,5};
View v_all(vec);
View v_sub(vec, 1, 4);     // 索引 1,2,3
std::cout << v_sub[2];     // 3
std::cout << v_sub.at(10); // 抛 index_error
auto new_vec = v_sub.collect(); // 复制到 vector
```

### 列表推导 (compre.h)

`Comprehension<T>` 包装 `vector`，支持 `map`/`filter` 立即求值。

```cpp
auto result = compre({1,2,3,4,5,6,7,8,9})
    .filter([](int x){ return x%2==1; })
    .map([](int x){ return x*x; });
std::vector<int> squares = result.to<std::vector<int>>();
```

### SFINAE 工具 (sfinae.h)

编译期类型特征。

```cpp
is_container<std::vector<int>>::value;      // true
is_callable<decltype([](int){}), int>::value;
is_string<std::string>::value;              // true
is_printable<int>::value;
enable_if_string<T> foo(T&& s);             // 只接受字符串
```

### 正则表达式 (re.h)

`Regex` 类，接口类似 Python `re`。

```cpp
Regex re(R"(\d+)");
auto m = re.search("abc123def");
if (m) std::cout << m.group();           // "123"
auto all = re.findall("a1b2c3");         // ["1","2","3"]
for (auto match : re.finditer("a1b2c3")) { /* ... */ }
auto parts = Regex(R"(\s+)").split("a b  c");  // ["a","b","c"]
std::string replaced = re.sub("X", "abc123def"); // "abcXdef"
using namespace re;
auto m2 = search(R"(\d+)", "hello 42");
```

### 系统信息 (info.h)

```cpp
version();   // "console v3.12.4"
platform();  // "Windows", "Linux", "macOS"
compiler();  // "GCC 12.2", "MSVC 1934"
license();   // MIT 许可证文本
```

### 可选值 (maybe.h)

`Maybe<T>` 类似 `std::optional`。

```cpp
Maybe<int> m1;              // 空
Maybe<int> m2(42);
if (m2) std::cout << m2.value();
int y = m1.value_or(0);
m1 = nothing;               // 清空
std::cout << m1;            // "(nothing)"
std::cin >> m2;
```

### 数学工具 (matools.h)

为 `MultiArray` 提供统计、线性代数、元素级函数等。

```cpp
MultiArray<double, 3> vec = {1,2,3};
double s = sum(vec);           // 6
double m = mean(vec);          // 2
double dp = dot(vec, vec);     // 14
double norm_v = norm(vec);     // sqrt(14)
auto unit = normalize(vec);
MultiArray<double, 2,2> A = {1,2,3,4};
auto I = identity<double, 2>(); // 单位矩阵
auto At = transpose(A);
auto C = matmul(A, A);
auto clipped = clamp(vec, 1.0, 2.0);
randomize(A, 0, 100);           // 均匀随机整数
randomize_normal(A, 0.0, 1.0);  // 正态分布
linspace(vec, 0.0, 10.0);
auto conv = convolve1d(vec, MultiArray<double,3>{1,0,-1});
```

### 异常类 (csexc.h)

所有异常继承自 `console_error`（派生自 `std::runtime_error`）。

```cpp
try {
    Box().get<int>(0);
} catch (const bad_get& e) {
} catch (const multiarray_error& e) {
} catch (const file_error& e) {
} catch (const console_error& e) {
}
```

### 格式化表示 (repr.h)

```cpp
repr(42);          // "42"
repr("hello");     // "hello" (带引号)
repr('a');         // 'a'
repr(nullptr);     // "nullptr"
tiname<int>();     // 可读类型名
```

### Windows MIDI (win/melody.h)

需链接 `winmm`。

```cpp
MIDI midi(Instrument::AcousticGrandPiano, 120, 100);
midi.play(Note(pitches::C4, 1.0));      // 同步
midi.nplay(Note(pitches::E4, 0.5));     // 异步
midi.set_instrument(Instrument::Violin);
midi.set_volume(80);
midi.set_bpm(140);
```

---

## 编译要求

- 编译器：C++11 或更高（GCC 5+, Clang 3.6+, MSVC 2015+）
- 仅依赖 C++ 标准库
- Windows MIDI 需要链接 `winmm`（如 `-lwinmm`）

---

## 许可证

MIT License © 2026 MrXie1109

完整文档：[console 库文档](https://mrxie1109.github.io/console---make-cpp-easy/)
