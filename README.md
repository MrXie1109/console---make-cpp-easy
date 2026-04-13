# console 库 / console Library
[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![C++17](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![C++20](https://img.shields.io/badge/C++-20-blue.svg)](https://img.shields.io/badge/C++-20-blue.svg)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![No Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen.svg)]()
一个轻量级、零依赖的 C++ 控制台工具库，提供简洁的 API 用于输入输出、日志记录、时间测量、随机数生成、字符串处理、文件操作、多维数组、正则表达式等常见任务。
A lightweight, zero-dependency C++ console utility library providing simple APIs for common tasks including I/O, logging, time measurement, random number generation, string manipulation, file operations, multidimensional arrays, regular expressions, and more.

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
- 🔷 **多维数组** - 编译期定长多维数组（MultiArray），优化初始化逻辑，支持逐元素运算
- 👁️ **容器视图** - 非拥有式容器视图（View），优化常量迭代器
- 🧵 **字符串处理** - 全面的字符串操作（修剪、大小写、分割、格式化）
- 📊 **进度条** - 可自定义样式的进度条
- 🧩 **列表推导** - 类似 Python 的列表推导式
- 🔍 **SFINAE 工具** - 编译期类型检测，支持字符/可打印类型判断
- 🔤 **正则表达式** - Python 风格的正则表达式封装
- 🧰 **标准库头文件** - 一站式包含所有标准库头文件
- ℹ️ **系统信息** - 获取平台、编译器、版本和许可证信息
- ✨ **空值包装** - 安全的空值包装类型（Maybe），避免空指针异常
- 🛠️ **工具扩展** - 新增 matools 工具集，增强库内通用能力
- 🎵 **MIDI 功能** - Windows 平台专属简洁 MIDI 播放能力

## 模块 / Modules
### 1. 标准库头文件 (std.h) ~
一站式包含所有 C++ 标准库头文件，根据 C++ 版本条件编译。

One-stop inclusion of all C++ standard library headers, conditionally compiled based on C++ version.
```cpp
#include "std.h"  // 自动包含当前 C++ 版本支持的所有标准库头文件
```

### 2. 输出 (output.h)  ~
提供类似 Python 的 print 功能和 STL 容器输出支持，优化字符串/字符输出格式。
容器输出通过独立的 `outfwd.h` 头文件提供前置声明，保证编译效率。

Provides Python-like print functionality and STL container output support with optimized string/char formatting.
Container output uses separate `outfwd.h` header for forward declarations to ensure compilation efficiency.
```cpp
namespace console {
    // STL 容器输出 / STL container output
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

### 3. 输入 (input.h)   ~
新增 `inputAll` 函数，支持读取全部输入流内容
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
    bool cont = inputYesOrNo("Continue? (y/n): ");
    // 新增：读取全部输入 / New: Read all input
    string all_input = inputAll("Input anything: ");
}
```

### 4. 时间 (time.h)    ~
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

### 5. 随机数 (random.h)    ~
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

### 6. 字符串处理 (strpp.h) ~
全面的字符串操作函数，包括格式化字符串类。

Comprehensive string manipulation functions, including formatted string class.
```cpp
namespace console {
    // 修剪 / Trimming
    string s = trim("  Hello World  ");          // "Hello World"
    string s2 = ltrim(",,,Hello", ",");          // "Hello"
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
    string str = uni_to_str(3.14159);                // "3.14159"
}
```

### 7. 颜色输出 (colorful.h)    ~
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

### 8. 日志记录 (logging.h) ~
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

### 9. 进度条 (progress.h)   Re
可自定义样式的进度条，支持 Unicode 字符。

Customizable progress bar with Unicode support.
```cpp
namespace console {
    // 预设样式 / Preset styles
    static const Config& normal();      // [##########          ] 50%
    static const Config& simple();      // ==========---------- 50%
    static const Config& beautiful();   // ▕██████████░░░░░░░░░░▏ 50%

    // 自定义样式 / Custom style
    Config myConfig{std::cout, 30, "=", "-", "|", "|", true};

    // 使用进度条 / Using progress bar
    std::vector<int> data(100);
    for (int n : progress(data, ProgressStyle::beautiful())) {
        // 处理数据...
    }
}
```

### 10. 文件操作 (file.h)   ~
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

### 11. 动态类型容器 (box.h)    ~
类型安全的异构容器，类似 Python 列表。

Type-safe heterogeneous container similar to Python list.
```cpp
namespace console {
    // 创建异构容器 / Create heterogeneous container
    Box box(42, 3.14, "Hello", vector{1, 2, 3});
    // 类型安全访问 / Type-safe access
    int i = box.get<int>(0);                // 42
    double d = box.get<double>(1);          // 3.14
    string s = box.get<string>(2);          // "Hello"
    // 解包到变量 / Unpack to variables
    int a; double b; string c;
    box.unpack(a, b, c);                    // a=42, b=3.14, c="Hello"
    // 输出 / Output
    print(box);                              // (42, 3.14, "Hello", [1, 2, 3])
}
```

### 12. 编译期多维数组 (multiarray.h)   ~
编译期定长多维数组，优化初始化列表构造实现，支持逐元素算术、逻辑、位运算，扁平化访问。

Compile-time fixed-size multidimensional array with optimized initializer_list construction, element-wise arithmetic, logic, and bit operations, flat access support.
```cpp
namespace console {
    // 创建多维数组 / Create multidimensional array
    MultiArray<int, 2, 3> arr;                // 2x3 数组
    MultiArray<double, 3, 3, 3> mat;          // 3x3x3 三维数组
    // 初始化方式 / Initialization methods
    MultiArray<int, 2, 2> a1(42);              // 全部填充 42
    MultiArray<int, 2, 2> a2({1, 2, 3, 4});    // 从初始化列表初始化
    // 访问元素 / Element access
    arr[0][1] = 100;                          // 链式下标
    int val = arr[1][2];
    int val3 = arr(0, 1);                      // 带检查的访问
    // 形状操作 / Shape operations
    print(arr.rank());                        // 2
    print(arr.size());                        // 6
    // 算术运算 / Arithmetic operations
    auto sum = arr + 10;                       // 标量加法
    auto prod = arr * arr;                      // 逐元素乘法
    arr += 5;                                   // 原位运算
    // 扁平化访问 / Flat access
    auto flat_begin = arr.fbegin();
    // 输出 / Output
    MultiArray<int, 2, 2> mat2{{1, 2}, {3, 4}};
    print(mat2);                                // [[1, 2], [3, 4]]
    // 转化 / Cast
    auto ma1 = multiarray_cast<6>(mat);         // 在同一类型，大小不变下重塑数组并返回
    auto ma2 = unsafe_multiarray_cast<float, 3, 2>(arr);         // 霸道的重解释内存
}
```

### 13. 双指针游标 (cursor_ptr.h)   ~
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

### 14. 字面量 (literals.h) ~
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
    Time t5 = 0.5_min;                       // 0.5分钟
    Time t6 = 4_hr;                          // 4小时
    // 格式化字符串字面量 / Format string literal
    auto fmt = "Value: {}"_f;                 // f_string
    string result = fmt % 42;                  // "Value: 42"
}
```

### 15. 容器视图 (view.h)   ~
非拥有式容器视图，支持子区间，优化常量迭代器。

Non-owning container views with subrange support, optimized const iterators.
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
    View<const vector<int>> cv(cvec);            // 只读视图
    // 字符串视图特化 / String view specialization
    string str = "Hello World";
    View<string> sv(str, 0, 5);
    print(sv);                                   // Hello
}
```

### 16. 列表推导式 (compre.h)   ~
类似 Python 的列表推导式功能。

Python-like list comprehension functionality.
```cpp
namespace console {
    // 从任意范围创建 Comprehension
    auto c1 = make_compre(vector{1, 2, 3, 4, 5, 6, 7, 8, 9});
    auto c2 = make_compre(list{"a", "b", "c"});
    auto c3 = make_compre({1.1, 2.2, 3.3});           // 初始化列表
    auto c4 = make_compre(arr, 1, 4);                  // 子范围
    // 链式操作：筛选 + 变换
    auto result = make_compre({1, 2, 3, 4, 5, 6, 7, 8, 9})
        .filter([](int x) { return x & 1; })           // 保留奇数
        .map([](int x) { return x * x; });              // 平方
    // 转换为标准容器
    list<int> lst = result.make<list<int>>();           // 复制转换
    vector<int> vec = result.to<vector<int>>();        // 移动转换
}
```

### 17. SFINAE 工具 (sfinae.h)  ~
编译期类型检测工具，支持字符/可打印类型判断。

Compile-time type detection tools with char/printable type checks.
```cpp
namespace console {
    // 检测是否为容器 / Check if type is container
    static_assert(is_container<vector<int>>::value);
    static_assert(!is_container<int>::value);
    // 检测是否为可调用对象 / Check if type is callable
    static_assert(is_callable<decltype(randint), int>::value);
    // 检测是否为迭代器 / Check if type is iterator
    static_assert(is_iterator<vector<int>::iterator>::value);
    // 检测是否为字符串 / Check if type is string
    static_assert(is_string<string>::value);
    static_assert(is_string<const char*>::value);
    // 检测是否为字符 / Check if type is char
    static_assert(is_char<char>::value);
    // 检测是否可打印 / Check if type is printable
    static_assert(is_printable<int>::value);
}
```

### 18. 正则表达式 (re.h)   ~
重写迭代器与遍历逻辑，新增迭代器对封装，优化遍历使用方式
Python 风格的正则表达式封装。

Python-style regular expression wrapper.
```cpp
namespace console {
    // 编译正则表达式 / Compile regex
    Regex re(R"(\\d+)");
    // 搜索 / Search
    auto match = re.search("abc123def");
    if (match) {
        print(match.group());              // "123"
    }
    // 匹配 / Match (从头开始)
    auto m2 = re.match("123abc");
    // 查找所有 / Find all
    auto all = re.findall("a1b2c3d4");      // ["1", "2", "3", "4"]
    // 遍历匹配结果（优化后）/ Iterate matches (optimized)
    for (auto m : re.finditer("a1b2c3")) {
        print(m.group());
    }
    // 分割 / Split
    auto parts = Regex(R"(\s+)").split("a b  c   d"); // ["a", "b", "c", "d"]
    // 替换 / Substitute
    string result = re.sub("X", "abc123def");  // "abcXdef"
}
```

### 19. 异常类 (csexc.h)    ~
自定义异常类体系。

Custom exception class hierarchy.
```cpp
namespace console {
    // 所有异常可在需要时捕获
    try {
        // ...
    } catch (const bad_get& e) {               // Item 类型错误
        logger.error("Type mismatch:", e.what());
    } catch (const multiarray_error& e) {      // 多维数组错误
        logger.error("Array error:", e.what());
    } catch (const index_error& e) {           // 索引越界
        logger.error("Index out of range:", e.what());
    } catch (const file_error& e) {            // 文件错误
        logger.error("File error:", e.what());
    } catch (const fatal_logging& e) {         // 致命日志
        logger.fatal("Fatal:", e.what());
    } catch (const bad_format& e) {            // 格式化错误
        logger.error("Format error:", e.what());
    } catch (const bad_maybe_access& e) {      // Maybe 空值访问
        logger.error("Maybe access error:", e.what());
    }
}
```

### 20. 系统信息 (info.h)   ±
获取平台、编译器、版本和许可证信息。

Get platform, compiler, version, and license information.
```cpp
namespace console {
    // 获取许可证信息 / Get license information
    print(license());
    // 获取平台信息 / Get platform information
    print("Platform:", platform());           // Windows/Linux/macOS/Unknown
    // 获取编译器信息 / Get compiler information
    print("Compiler:", compiler());           // GCC 12.2/MSVC 1934/Clang
    // 获取版本信息 / Get version information
    print(version());                         // console v3.11.3 (By MrXie1109)
}
```

### 21. 空值包装 (maybe.h)  ~
安全的空值包装类型，避免空指针异常，支持值访问与默认值。

Safe nullable wrapper type to avoid null pointer exceptions, support value access and default value.
```cpp
namespace console {
    Maybe<int> m1;                            // 空值
    Maybe<int> m2(42);                        // 有值
    Maybe<string> m3 = nothing;               // 空值
    // 值访问
    if (m2) {
        print(m2.value());                    // 42
    }
    // 默认值
    int val = m1.value_or(0);                 // 0
    // 输出
    print(m1);                                 // (nothing)
    print(m2);                                 // 42
}
```

### 22. 容器输出前置声明 (outfwd.h) ~
为所有 STL 容器提供 `operator<<` 的前置声明，优化编译速度，避免重复定义。

Provides forward declarations for `operator<<` of all STL containers to optimize compilation speed and avoid duplicate definitions.
```cpp
// 无需手动包含，由 output.h 自动引入
#include "outfwd.h"
```

### 23. 格式化输出工具 (repr.h) ~
专门用于容器输出格式化的工具库，提供统一的类型格式化输出功能，仅在打印容器时内部使用。

Specialized utility library for container output formatting, providing unified type formatting output functionality, only used internally when printing containers.
核心功能：
- 字符串类型输出带双引号
- 字符类型输出带单引号
- 布尔值输出 `true`/`false`
- 函数指针输出内存地址
- 不可打印类型输出可读的类型名称

### 24. 扩展工具集 (matools.h)  ~
 MultiArray 专用工具集，提供多维数组数值计算、线性代数、统计分析、随机初始化等配套功能，强化 MultiArray 运算能力与使用便捷性。

MultiArray-specific toolset providing multi-dimensional array numerical calculation, linear algebra, statistical analysis, random initialization and other supporting functions, enhancing the computing power and usability of MultiArray.
```cpp
namespace console {
    // 多维数组统计函数
    auto sum = sum(arr);            // 数组所有元素求和
    auto avg = mean(arr);           // 计算数组均值
    auto var = variance(arr);       // 计算方差
    auto dev = stddev(arr);         // 计算标准差
    print_stats(arr);               // 打印完整统计信息
    // 线性代数运算
    auto product = dot(arr1, arr2); // 向量点积
    auto length = norm(arr);        // 向量L2范数
    auto sim = cosine(arr1, arr2);  // 余弦相似度
    // 数组初始化与操作
    linspace(arr, 0, 10);          // 线性等分填充
    randomize(arr, 0, 100);        // 均匀随机初始化
    auto res = clamp(arr, 0, 50);  // 数值截断
}
```

## 拓展模块 / Extension Modules
警告：拓展模块不会被自动包含于 `all.h` ！你必须手动包含它们！

Warning: Extension modules are not automatically included in `all.h`! You must manually include them!

### Windows
#### MIDI库 (win/melody.h)  ~
仅Windows操作系统可用的MIDI渲染器，支持乐器切换、音量控制、异步播放
MIDI Renderer Available Only on Windows Operating System
```cpp
namespace console {
    // 创建 MIDI 实例
    MIDI midi(Instrument::AcousticGrandPiano, 120, 100);
    // 播放单音
    midi.play(Note(pitches::C4, 1));
    // 异步播放（不阻塞）
    midi.nplay(Note(pitches::D4, 0.5));
    // 播放乐谱数组
    Note melody[] = {
        {pitches::C4, 1}, {pitches::D4, 1},
        {pitches::E4, 1}, {pitches::REST, 0.5}
    };
    midi.play(melody);
    // 切换乐器
    midi.set_instrument(Instrument::Violin);
    // 调整音量
    midi.set_volume(80);
}
```

## 快速开始 / Quick Start
```cpp
#include "console/all.h"
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
    // 正则表达式 / Regular expression
    auto match = re::search(R"(\d+)", msg);
    if (match) print("Found number:", match.group());
    // 多维数组 / Multidimensional array
    MultiArray<int, 2, 2> mat{{1, 2}, {3, 4}};
    print("Matrix:", mat);
    // 文件操作 / File operations
    Path("output.txt").write_text(msg);
    // 空值包装 / Maybe
    Maybe<int> m = 42;
    print("Maybe value:", m);
    // 系统信息 / System information
    print("Version:", version());
    print("Platform:", platform());
    print("Compiler:", compiler());
    return 0;
}
```

## 版本更新说明 / Version Update

- **v3.11.3**
  - 紧急修复了 Progress 迭代器不前进的恶性 Bug

- **v3.11.2**
  - 为 Progress 实现了 Throttling
  - 修复多处已知 Bug

- **v3.11.1**
  - 移除了无用的 `jdt_range_error` 异常
  - 修复多处已知 Bug

- **v3.11.0**
  - 再一次重写了 `progress.h`
  - 修复多处已知 Bug

## 编译要求 / Build Requirements
- C++11 兼容的编译器（支持 C++11/14/17/20/23 新特性可选）
- 仅需标准库，无外部依赖
- 使用 MIDI 功能需链接 `winmm` 库（Windows）

## 许可证 / License
MIT License [LICENSE](LICENSE)

---
**console 库** - 让 C++ 控制台编程更简单 / Making C++ console programming simpler
