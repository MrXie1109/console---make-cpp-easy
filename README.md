# console 库 / console Library

[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![C++20](https://img.shields.io/badge/C++-20-blue.svg)](https://en.cppreference.com/w/cpp/20)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![No Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen.svg)]()

一个轻量级、零依赖的 C++ 控制台工具库，提供简洁的 API 用于输入输出、日志记录、时间测量、随机数生成、字符串处理、文件操作、多维数组等常见任务。

A lightweight, zero-dependency C++ console utility library providing simple APIs for common tasks including I/O, logging, time measurement, random number generation, string manipulation, file operations, multidimensional arrays, and more.

## 特性 / Features

- 🚀 **多标准支持** - 兼容 C++11/14/17/20/23（条件编译）
- 📦 **零外部依赖** - 仅使用 C++ 标准库
- 🎯 **简洁 API** - 直观易用的接口设计
- 🎨 **彩色输出** - 支持终端颜色和样式
- 📝 **日志系统** - 多级别日志，支持时间戳和彩色输出
- ⏱️ **时间工具** - 高精度计时、休眠和日期时间格式化
- 🔢 **随机数** - 便捷的随机数生成接口（Mersenne Twister）
- 📄 **文件操作** - 简单的文件读写封装，跨平台路径处理
- 🎭 **动态类型** - 类型安全的异构容器（Box）
- 🔷 **多维数组** - 类似 NumPy 的多维数组（ndarray）
- 👁️ **容器视图** - 非拥有式容器视图（View/ConstView）
- 🧵 **字符串处理** - 全面的字符串操作（修剪、大小写、分割、格式化）
- 📊 **进度条** - 可自定义样式的进度条
- 🧩 **列表推导** - 类似 Python 的列表推导式
- 🔍 **SFINAE 工具** - 编译期类型检测

## 模块 / Modules

### 1. 输出 (output.h)

提供类似 Python 的 print 功能和 STL 容器输出支持。

Provides Python-like print functionality and STL container output support.

```cpp
namespace console {
    // STL 容器输出支持 / STL container output support
    vector<int> vec = {1, 2, 3};
    cout << vec;                    // [1, 2, 3]
    
    map<string, int> mp = {{"a", 1}, {"b", 2}};
    cout << mp;                     // {a: 1, b: 2}
    
    tuple<int, string, double> t{42, "hello", 3.14};
    cout << t;                      // (42, hello, 3.14)

    // C 数组转换辅助 / C array conversion helpers
    int arr[] = {1, 2, 3};
    auto arr2 = to_array(arr);       // std::array<int, 3>
    auto vec2 = to_vector(arr);      // std::vector<int>

    // 类似 Python 的 print / Python-like print
    print("Value:", 42, vec);        // Value: 42 [1, 2, 3]
    print();                          // 只输出换行
}
```

### 2. 输入 (input.h)

类型安全的控制台输入函数，带错误处理。

Type-safe console input functions with error handling.

```cpp
namespace console {
    // 通用输入 / Generic input
    int age = input<int>("Enter your age: ");
    double price = input<double>("Price: ");
    
    // 便捷输入函数 / Convenience input functions
    string name = inputLine("Your name: ");
    double num = inputWithRange("Number (0-100): ", 0, 100);
    char ch = inputChar("Type a character: ");
    
    if (inputYesOrNo("Continue? (y/n): ")) {
        // ...
    }
}
```

### 3. 时间 (time.h)

高精度时间测量、休眠和日期时间格式化。

High-precision time measurement, sleep, and datetime formatting.

```cpp
namespace console {
    // Time 结构体，自动选择合适单位显示
    Time t1 = now();                  // 当前时间点
    Time t2 = 1.5_s;                  // 1.5秒（使用字面量）
    
    // 测量函数执行时间 / Measure function execution time
    auto duration = timer([]{
        sleep(100_ms);                 // 休眠100毫秒
    });
    print("Took:", duration);          // Took: 100ms
    
    // 日期时间格式化 / Datetime formatting
    print(datetime());                  // 2024-01-01 12:34:56
    print(datetime("%Y/%m/%d"));        // 2024/01/01
}
```

### 4. 随机数 (random.h)

基于 Mersenne Twister 的随机数生成器。

Mersenne Twister based random number generator.

```cpp
namespace console {
    // 随机整数 / Random integer
    int dice = randint(1, 6);           // 1-6
    size_t idx = randint<size_t>(0, vec.size() - 1);
    
    // 随机浮点数 / Random floating point
    double prob = uniform();             // 0.0-1.0
    double temp = uniform(-10.0, 40.0);  // -10.0-40.0
    
    // 从容器随机选择 / Random choice from container
    vector<int> vec = {1, 2, 3, 4, 5};
    int selected = choice(vec);          // 随机选择一个
    int picked = choice({1, 2, 3, 4});   // 从初始化列表选择
    
    // 打乱容器 / Shuffle container
    shuffle(vec);                         // 打乱顺序
}
```

### 5. 字符串处理 (strpp.h)

全面的字符串操作函数，包括格式化字符串类。

Comprehensive string manipulation functions, including formatted string class.

```cpp
namespace console {
    // 修剪 / Trimming
    string s = trim("  Hello World  ");          // "Hello World"
    string s2 = ltrim(",,,Hello", [](char c) { return c != ','; }); // "Hello"
    
    // 大小写转换 / Case conversion
    print(upper("hello"));                       // HELLO
    print(lower("WORLD"));                       // world
    print(title("hello world"));                  // Hello World
    
    // 分割与连接 / Split and join
    auto parts = split("a,b,c", ",");             // ["a", "b", "c"]
    auto joined = join(parts, "-");               // "a-b-c"
    
    // 分区操作 / Partition
    auto [left, mid, right] = partition("key=value", "=");
    // left="key", mid="=", right="value"
    
    // 格式化字符串类 / Formatted string class
    f_string fmt = "{} + {} = {}";
    string result = fmt % 1 % 2 % 3;               // "1 + 2 = 3"
    
    // 通用类型转字符串 / Universal to string conversion
    string str = uniToStr(3.14159);                // "3.14159"
}
```

### 6. 颜色输出 (colorful.h)

ANSI 转义序列颜色常量。

ANSI escape sequence color constants.

```cpp
namespace console::color {
    // 使用颜色常量 / Using color constants
    cout << color::Red << "Error" << color::Reset << endl;
    cout << color::Bold << color::Blue << "Bold blue" << color::Reset << endl;
    cout << color::BgYellow << color::Black << "Warning" << color::Reset << endl;
}
```

### 7. 日志记录 (logging.h)

多级别日志系统，支持彩色输出和时间戳。

Multi-level logging system with color support and timestamps.

```cpp
namespace console {
    // 全局 logger 对象 / Global logger object
    extern Logging logger;  // 默认彩色输出，级别 INFO
    
    // 配置日志级别 / Configure log levels
    logger.set(Logging::Level::DEBUG);           // 设置最低级别
    logger.set(true, true, false, false, false); // 只开启 DEBUG 和 INFO
    
    // 使用日志 / Using logger
    logger.debug("Debug value:", 42);
    logger.info("Application started");
    logger.warn("Low disk space");
    logger.error("File not found:", filename);
    
    try {
        logger.fatal("Fatal error occurred");     // 抛出 fatal_logging 异常
    } catch (const fatal_logging& e) {
        // 处理致命错误
    }
}
```

### 8. 进度条 (jdt.h)

可自定义样式的进度条，支持 Unicode 字符。

Customizable progress bar with Unicode support.

```cpp
namespace console {
    // 预设样式 / Preset styles
    extern const JdtSettings normalSettings;      // [##########          ]   50%
    extern const JdtSettings simpleSettings;      // ==========----------   50%
    extern const JdtSettings beautifulSettings;   // ▕██████████░░░░░░░░░░▏   50%
    
    // 自定义样式 / Custom style
    JdtSettings mySettings{30, "|", "|", "=", "-", "\r", cout};
    defaultSettings = beautifulSettings;          // 修改默认样式
    
    // 使用进度条 / Using progress bar
    for (int i = 0; i <= 100; i += 5) {
        jdt(i);                                    // 使用默认样式
        this_thread::sleep_for(50ms);
    }
    cout << endl;
}
```

### 9. 文件操作 (file.h)

简单的文件读写封装，跨平台路径处理。

Simple file I/O wrapper with cross-platform path handling.

```cpp
namespace console {
    // 路径操作 / Path operations
    Path file("data.txt");
    Path backup = Path("backup") / "data.txt";    // 路径拼接
    
    // 读取文件 / Read file
    string content = file.read_text();
    vector<string> lines = file.read_lines();
    auto bytes = file.read_binary();
    
    // 写入文件 / Write file
    file.write_text("Hello, World!");
    file.write_lines(lines);
    
    // 检查与创建 / Check and create
    if (!file.exists()) {
        file.touch();                               // 创建空文件
        file.ensure();                              // 确保文件存在
    }
}
```

### 10. 动态类型容器 (box.h)

类型安全的异构容器，类似 Python 列表。

Type-safe heterogeneous container similar to Python list.

```cpp
namespace console {
    // 创建异构容器 / Create heterogeneous container
    Box box(42, 3.14, "Hello", vector{1, 2, 3}, Point{10, 20});
    
    // 类型安全访问 / Type-safe access
    int i = box.get<int>(0);                // 42
    double d = box.get<double>(1);          // 3.14
    string s = box.get<string>(2);          // "Hello"
    
    // 解包到变量 / Unpack to variables
    int a; double b; string c;
    box.unpack(a, b, c);                    // a=42, b=3.14, c="Hello"
    
    // 输出 / Output
    print(box);                              // (42, 3.14, Hello, [1, 2, 3], (10, 20))
}
```

### 11. 多维数组 (ndarray.h)

类似 NumPy 的多维数组，支持任意维度。

NumPy-like multidimensional array with arbitrary dimensions.

```cpp
namespace console {
    // 创建多维数组 / Create multidimensional array
    ndarray<int> arr({2, 3});                // 2x3 数组
    ndarray<double> mat({3, 3, 3});          // 3x3x3 三维数组
    
    // 初始化方式 / Initialization methods
    ndarray<int> a1({2, 2}, 42);              // 全部填充 42
    ndarray<int> a2({2, 2}, vector{1, 2, 3, 4}); // 从容器初始化
    ndarray<int> a3({2, 2}, randint, 0, 100); // 用函数生成
    
    // 访问元素 / Element access
    arr[0][1] = 100;                          // 链式下标
    int val = arr[1][2];
    int val2 = arr.at(0, 1);                   // 带边界检查
    
    // 形状操作 / Shape operations
    print(arr.shape());                        // [2, 3]
    arr.reshape(3, 2);                         // 重塑为 3x2
    
    // 算术运算 / Arithmetic operations
    auto sum = arr + 10;                       // 标量加法
    auto prod = arr * arr;                      // 逐元素乘法
    arr += 5;                                   // 原位运算
    
    // 输出 / Output
    ndarray<int> mat2{{1, 2}, {3, 4}};
    print(mat2);                                // [[1, 2], [3, 4]]
}
```

### 12. 容器视图 (view.h)

非拥有式容器视图，支持子区间。

Non-owning container views with subrange support.

```cpp
namespace console {
    vector<int> vec = {0, 1, 2, 3, 4, 5};
    
    // 创建视图 / Create view
    View v1(vec);                               // 整个容器
    View v2(vec, 1, 4);                         // 索引[1,4)区间
    View v3(vec.begin() + 2, vec.end());        // 迭代器区间
    
    // 使用视图 / Using view
    for (auto x : v2) {                         // 遍历: 1, 2, 3
        print(x);
    }
    
    int val = v2[1];                            // 2
    int val2 = v2.at(2);                        // 3（带边界检查）
    
    // 常量视图 / Constant view
    const vector<int> cvec = {1, 2, 3};
    ConstView cv(cvec);                          // 只读视图
    
    // 字符串视图特化 / String view specialization
    string str = "Hello World";
    View<string> sv(str, 0, 5);
    print(sv);                                   // Hello
}
```

### 13. 列表推导 (compre.h)

类似 Python 的列表推导式功能。

Python-like list comprehension functionality.

```cpp
namespace console {
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    
    // 映射+过滤 / Map + filter
    auto squares = compre_mf<vector<int>>(
        [](int x) { return x * x; },            // 表达式
        nums,                                    // 范围
        [](int x) { return x % 2 == 0; }        // 条件
    );  // 结果: [4, 16, 36]
    
    // 仅映射 / Map only
    auto doubled = compre_m<vector<int>>(
        [](int x) { return x * 2; },
        nums
    );  // 结果: [2, 4, 6, 8, 10, 12]
    
    // 仅过滤 / Filter only
    auto evens = compre_f<vector<int>>(
        nums,
        [](int x) { return x % 2 == 0; }
    );  // 结果: [2, 4, 6]
    
    // 仅复制 / Copy only
    auto copy = compre_c<vector<int>>(nums);    // 结果: [1, 2, 3, 4, 5, 6]
}
```

### 14. 双指针游标 (cursor_ptr.h)

分离所有权与访问位置的智能指针。

Smart pointer separating ownership and access position.

```cpp
namespace console {
    // 单个对象 / Single object
    cursor_ptr<int> p1(new int(42));
    cursor_ptr<int> p2 = p1;                     // p2 共享游标位置，不拥有所有权
    auto p3 = p1 + 1;                             // 指针运算
    
    // 数组对象 / Array object
    cursor_ptr<int[]> arr(new int[10]{0,1,2,3,4,5,6,7,8,9});
    for (int i = 0; i < 5; ++i) {
        print(*arr);                               // 0, 1, 2, 3, 4
        ++arr;                                      // 移动游标
    }
    
    // 比较操作 / Comparison operations
    if (arr == arr + 5) { /* ... */ }
    
    // 移动语义 / Move semantics
    cursor_ptr<int[]> arr2 = std::move(arr);       // 转移所有权
    // arr 现在为空，arr2 拥有数组
}
```

### 15. 字面量 (literals.h)

用户定义字面量，提供便捷语法。

User-defined literals for convenient syntax.

```cpp
namespace console::literals {
    // 字符串字面量 / String literal
    auto str = "hello"s;                    // std::string
    
    // 时间字面量 / Time literals
    Time t1 = 100_ns;                        // 100纳秒
    Time t2 = 2.5_us;                        // 2.5微秒
    Time t3 = 500_ms;                        // 500毫秒
    Time t4 = 1.5_s;                         // 1.5秒
    
    // 格式化字符串字面量 / Format string literal
    auto fmt = "Value: {}"_f;                 // f_string
    string result = fmt % 42;                  // "Value: 42"
}
```

### 16. 异常类 (csexc.h)

自定义异常类体系。

Custom exception class hierarchy.

```cpp
namespace console {
    // 所有异常可在需要时捕获
    try {
        // ...
    } catch (const bad_get& e) {               // Item 类型错误
        logger.error("Type mismatch:", e.what());
    } catch (const ndarray_error& e) {         // 多维数组错误
        logger.error("Array error:", e.what());
    } catch (const index_error& e) {           // 索引越界
        logger.error("Index out of range:", e.what());
    } catch (const file_not_found_error& e) {  // 文件未找到
        logger.error("File error:", e.what());
    } catch (const fatal_logging& e) {         // 致命日志
        logger.fatal("Fatal:", e.what());
    }
}
```

### 17. SFINAE 工具 (sfinae.h)

编译期类型检测工具。

Compile-time type detection tools.

```cpp
namespace console {
    // 这些工具主要用于库内部实现
    // 但也可以在用户代码中使用
    
    // 检测是否为容器 / Check if type is container
    static_assert(is_container<vector<int>>::value);
    static_assert(!is_container<int>::value);
    
    // 检测是否为可调用对象 / Check if type is callable
    static_assert(is_callable<decltype(randint), int>::value);
    
    // 检测是否为迭代器 / Check if type is iterator
    static_assert(is_iterator<vector<int>::iterator>::value);
    
    // 检测是否支持下标操作 / Check if type supports subscript
    static_assert(has_subscript<vector<int>, int>::value);
}
```

## 快速开始 / Quick Start

```cpp
#include "all.h"
using namespace console;
using namespace console::literals;

int main() {
    // 输出 / Output
    print("Hello, World!");
    
    // 输入 / Input
    string name = inputLine("What's your name? ");
    int age = input<int>("How old are you? ");
    
    // 日志 / Logging
    logger.info("User:", name, "age:", age);
    
    // 时间测量 / Time measurement
    auto t = timer([]{
        sleep(500_ms);
    });
    print("Slept for:", t);
    
    // 随机数 / Random
    int lucky = randint(1, 100);
    print("Your lucky number:", lucky);
    
    // 字符串格式化 / String formatting
    string msg = f_string("Hello, {}! You are {} years old.") % name % age;
    print(msg);
    
    // 多维数组 / Multidimensional array
    ndarray<int> mat{{2, 2}, {1, 2, 3, 4}};
    print("Matrix:", mat);
    
    // 文件操作 / File operations
    Path("output.txt").write_text(msg);
    
    return 0;
}
```

## 编译要求 / Build Requirements

- C++11 兼容的编译器（支持 C++11/14/17/20/23 新特性可选）
- 仅需标准库，无外部依赖

## 许可证 / License

MIT License [LICENSE](LICENSE)

---

**console 库** - 让 C++ 控制台编程更简单 / Making C++ console programming simpler