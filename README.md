# console 库 / console Library

[![C++11](https://img.shields.io/badge/C++-11-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![No Dependencies](https://img.shields.io/badge/dependencies-none-brightgreen.svg)]()

一个轻量级、零依赖的 C++11 控制台工具库，提供简洁的 API 用于输入输出、日志记录、时间测量、随机数生成、字符串处理、文件操作等常见任务。

A lightweight, zero-dependency C++11 console utility library providing simple APIs for common tasks including I/O, logging, time measurement, random number generation, string manipulation, file operations, and more.

## 特性 / Features

- 🚀 **兼容 C++11** - 完全基于 C++11 标准
- 📦 **零外部依赖** - 仅使用 C++ 标准库
- 🎯 **简洁 API** - 直观易用的接口设计
- 🎨 **彩色输出** - 支持终端颜色和样式
- 📝 **日志系统** - 多级别日志，支持时间戳
- ⏱️ **时间工具** - 高精度计时和休眠
- 🔢 **随机数** - 便捷的随机数生成接口
- 📄 **文件操作** - 简单的文件读写封装
- 🎭 **动态类型** - 类似 Python 的异构容器

## 模块 / Modules

### 1. 输出 (output.h)

提供类似 Python 的 print 功能和 STL 容器输出支持。

Provides Python-like print functionality and STL container output support.

```cpp
namespace console {
    // STL 容器输出支持 / STL container output support
    template<class T> ostream& operator<<(ostream&, const vector<T>&);
    template<class T, size_t N> ostream& operator<<(ostream&, const array<T, N>&);
    template<class T, class U> ostream& operator<<(ostream&, const pair<T, U>&);
    template<class K, class V> ostream& operator<<(ostream&, const map<K, V>&);
    template<class T> ostream& operator<<(ostream&, const set<T>&);

    // C 数组转换辅助 / C array conversion helpers
    template<class T, size_t N> array<T, N> to_array(const T (&ar)[N]);
    template<class T, size_t N> vector<T> to_vector(const T (&ar)[N]);

    // 类似 Python 的 print / Python-like print
    class Output {
        void operator()();                                   // 打印结束符
        template<class T> void operator()(const T& t);      // 打印单个值
        template<class T, class... Args> void operator()(const T& t, const Args&... args); // 打印多个值
    };
    extern Output print;  // 全局 print 对象 / global print object
}
```

**示例 / Example**:
```cpp
vector<int> vec = {1, 2, 3, 4};
print("Vector:", vec);  // 输出: Vector: [1, 2, 3, 4]

int arr[] = {5, 6, 7};
auto arr2 = to_array(arr);  // C数组转 std::array
```

### 2. 输入 (input.h)

类型安全的控制台输入函数，带错误处理。

Type-safe console input functions with error handling.

```cpp
namespace console {
    struct InputSettings {
        ostream& os;  // 输出流
        istream& is;  // 输入流
    };
    extern InputSettings inputSettings;

    // 通用输入 / Generic input
    template<class T = string> T input(const string& prompt = "", const InputSettings& is = inputSettings);

    // 便捷输入函数 / Convenience input functions
    long double inputNumber(const string& prompt = "Type a number: ", const InputSettings& is = inputSettings);
    string inputLine(const string& prompt = "Type a line string: ", const InputSettings& is = inputSettings);
    bool inputYesOrNo(const string& prompt = "Type yes or no: ", const InputSettings& is = inputSettings);
    long double inputWithRange(const string& prompt, long double min, long double max, const InputSettings& is = inputSettings);
    char inputChar(const string& prompt = "Type a character: ", const InputSettings& is = inputSettings);
}
```

**示例 / Example**:
```cpp
int age = input<int>("Enter your age: ");
string name = inputLine("Enter your name: ");
if (inputYesOrNo("Continue? (yes/no): ")) {
    // ...
}
```

### 3. 时间 (time.h)

高精度时间测量和格式化输出。

High-precision time measurement and formatted output.

```cpp
namespace console {
    struct TimerResult {
        double ns, us, ms, s;  // 纳秒、微秒、毫秒、秒
        operator double() const;  // 转换为纳秒
        friend ostream& operator<<(ostream&, const TimerResult);  // 自动选择合适单位
    };

    TimerResult now();  // 获取当前时间点

    // 测量函数执行时间 / Measure function execution time
    template<class F, class... Args> TimerResult timer(F&& f, Args&&... args);

    void sleep(double s);  // 休眠指定秒数
    void sleep(const TimerResult& tr);  // 根据 TimerResult 休眠

    string datetime(const string& fmt = "%Y-%m-%d %H:%M:%S");  // 获取格式化时间
}
```

**示例 / Example**:
```cpp
auto duration = timer([]{
    // 耗时操作 / time-consuming operation
    sleep(0.5);  // 休眠0.5秒
});
print("Execution time:", duration);  // 输出: Execution time: 500ms

print("Current time:", datetime());  // 输出: Current time: 2024-01-01 12:34:56
```

### 4. 随机数 (random.h)

基于 Mersenne Twister 的随机数生成器。

Mersenne Twister based random number generator.

```cpp
namespace console {
    // 获取全局随机数生成器 / Get global random number generator
    mt19937& GEN();

    // 随机整数 / Random integer
    template<class T = int> T randint(T min = 0, T max = 32767, mt19937& gen = GEN());

    // 随机浮点数 / Random floating point
    template<class T = double> T uniform(T min = 0.0, T max = 1.0, mt19937& gen = GEN());

    // 从容器随机选择 / Random choice from container
    template<class T> auto choice(T&& t, mt19937& gen = GEN()) -> decltype(*begin(t));

    // 打乱容器 / Shuffle container
    template<class T> void shuffle(T&& t, mt19937& gen = GEN());
}
```

**示例 / Example**:
```cpp
int dice = randint(1, 6);           // 1-6随机数
double prob = uniform();            // 0-1随机浮点数

vector<int> vec = {1, 2, 3, 4, 5};
int selected = choice(vec);         // 随机选择一个元素
shuffle(vec);                       // 打乱顺序
```

### 5. 字符串处理 (strpp.h)

全面的字符串操作函数。

Comprehensive string manipulation functions.

```cpp
namespace console {
    // 修剪 / Trimming
    template<class F> string ltrim(string str, F&& f = [](unsigned char c){ return !isspace(c); });
    template<class F> string rtrim(string str, F&& f = [](unsigned char c){ return !isspace(c); });
    template<class F> string trim(string str, F&& f = [](unsigned char c){ return !isspace(c); });

    // 大小写转换 / Case conversion
    string upper(string str);
    string lower(string str);
    string title(string str);

    // 分割与连接 / Split and join
    struct PartitionResult { string left, middle, right; };
    PartitionResult partition(const string& text, const string& sep);
    vector<string> split(string text, const string& sep = " ");
    template<class T> string join(const vector<T>& vec, const string& sep = "");

    // 通用类型转字符串 / Universal to string conversion
    template<class T> string uniToStr(T&& t);
    string uniToStr(const string& str);
    string uniToStr(const char* str);
    string uniToStr(int16_t num);  // 各种数值类型重载 / overloads for numeric types
    string uniToStr(bool b);  // "true"/"false"

    // 字符串格式化 (类似 Python % 运算符) / String formatting (like Python % operator)
    template<class T> string operator%(const string& str, const T& t);
}
```

**示例 / Example**:
```cpp
string str = "  Hello World  ";
print(trim(str));                    // 输出: Hello World
print(upper(str));                    // 输出:   HELLO WORLD  

vector<string> parts = split("a,b,c", ",");  // ["a", "b", "c"]
string joined = join(parts, "-");            // "a-b-c"

string formatted = "Hello, {}!" % "World";   // "Hello, World!"
```

### 6. 颜色输出 (colorful.h)

ANSI 转义序列颜色常量。

ANSI escape sequence color constants.

```cpp
namespace console::color {
    // 前景色 / Foreground colors
    extern const char *Black, *Red, *Green, *Yellow, *Blue, *Magenta, *Cyan, *White;
    extern const char *BrightBlack, *BrightRed, *BrightGreen, *BrightYellow;
    extern const char *BrightBlue, *BrightMagenta, *BrightCyan, *BrightWhite;

    // 背景色 / Background colors
    extern const char *BgBlack, *BgRed, *BgGreen, *BgYellow, *BgBlue, *BgMagenta, *BgCyan, *BgWhite;
    extern const char *BgBrightBlack, *BgBrightRed, *BgBrightGreen, *BgBrightYellow;
    extern const char *BgBrightBlue, *BgBrightMagenta, *BgBrightCyan, *BgBrightWhite;

    // 文本样式 / Text styles
    extern const char *Bold, *Dim, *Italic, *Underline, *Blink, *Reverse, *Hidden, *Strikethrough;
    extern const char *Reset;  // 重置所有样式
}
```

**示例 / Example**:
```cpp
cout << color::Red << "Error message" << color::Reset << endl;
cout << color::Bold << color::Blue << "Bold blue text" << color::Reset << endl;
```

### 7. 日志记录 (logging.h)

多级别日志系统，支持彩色输出和时间戳。

Multi-level logging system with color support and timestamps.

```cpp
namespace console {
    class Logging {
    public:
        enum class Level { DEBUG, INFO, WARN, ERROR, FATAL };

        Logging(ostream& os = cout, bool colorful = false, Level lvl = Level::INFO);

        void set(Level minLevel);              // 设置最低日志级别
        void set(bool debug, bool info, bool warn, bool error, bool fatal);  // 单独设置每个级别

        template<class... Args> void debug(const Args&... args);
        template<class... Args> void info(const Args&... args);
        template<class... Args> void warn(const Args&... args);
        template<class... Args> void error(const Args&... args);
        template<class... Args> void fatal(const Args&... args);  // 会抛出 fatal_logging 异常
    };

    extern Logging logger;  // 全局 logger 对象
}
```

**示例 / Example**:
```cpp
logger.info("Application started");
logger.debug("Debug value:", 42);

try {
    // ...
} catch (const exception& e) {
    logger.error("Caught exception:", e.what());
}
```

### 8. 进度条 (jdt.h)

可自定义样式的进度条。

Customizable progress bar.

```cpp
namespace console {
    struct JdtSettings {
        int len;           // 进度条长度
        const char *lch;   // 左边界符
        const char *rch;   // 右边界符
        const char *fch;   // 已填充字符
        const char *ech;   // 未填充字符
        const char *Ech;   // 结尾字符 (通常为 \r)
        ostream& os;       // 输出流
    };

    // 预设样式 / Preset styles
    extern const JdtSettings normalSettings;      // [##########          ]   50%
    extern const JdtSettings simpleSettings;      // ==========----------   50%
    extern const JdtSettings beautifulSettings;   // ▕██████████░░░░░░░░░░▏   50%

    extern JdtSettings defaultSettings;  // 默认样式，可修改

    void jdt(int percent, const JdtSettings& js = defaultSettings);
}
```

**示例 / Example**:
```cpp
for (int i = 0; i <= 100; i += 10) {
    jdt(i, beautifulSettings);
    sleep(0.1);
}
cout << endl;
```

### 9. 文件操作 (file.h)

简单的文件读写封装。

Simple file I/O wrapper.

```cpp
namespace console {
    class Path {
    public:
        using bytes = vector<unsigned char>;

        Path(const string& str);  // 路径字符串，Windows下自动转换分隔符

        friend Path operator/(const Path& p1, const Path& p2);  // 路径拼接

        string read_text();        // 读取文本文件
        bytes read_binary();       // 读取二进制文件
        vector<string> read_lines();  // 按行读取

        void write_text(const string& text);     // 写入文本
        void write_binary(const bytes& bts);     // 写入二进制
        void write_lines(const vector<string>& lines);  // 按行写入
    };
}
```

**示例 / Example**:
```cpp
Path file("data.txt");
string content = file.read_text();           // 读取整个文件
vector<string> lines = file.read_lines();    // 按行读取

Path newFile = Path("backup") / "data.txt";  // 路径拼接
newFile.write_lines(lines);                  // 写入文件
```

### 10. 动态类型容器 (box.h)

类似 Python 列表的异构容器。

Heterogeneous container similar to Python list.

```cpp
namespace console {
    class Item {  // 可存储任意类型的包装类 / Type-erased wrapper
    public:
        Item();                         // 空 Item
        template<typename T> Item(const T& value);  // 存储任意类型
        Item(const Item& other);        // 拷贝构造
        Item(Item&& other) noexcept;    // 移动构造

        template<typename T> T& get();  // 获取存储的值（类型安全）
    };

    class Box : public vector<Item> {  // 异构容器 / Heterogeneous container
    public:
        template<class... Args> Box(Args&&... args);  // 可变参数构造

        template<class T> T& get(size_t index);       // 获取指定索引的元素

        template<class... Args> void unpack(Args&&... args);  // 解包到变量
    };
}
```

**示例 / Example**:
```cpp
Box box(42, 3.14, "Hello", vector{1, 2, 3});

int i = box.get<int>(0);              // 42
double d = box.get<double>(1);        // 3.14
string s = box.get<string>(2);        // "Hello"

// 解包到变量 / Unpack to variables
int a; double b; string c;
box.unpack(a, b, c);                  // a=42, b=3.14, c="Hello"
```

### 11. 异常类 (csexc.h)

自定义异常类。

Custom exception classes.

```cpp
namespace console {
    class fatal_logging : public runtime_error;        // 致命日志错误
    class jdt_range_error : public invalid_argument;   // 进度条范围错误
    class bad_format : public invalid_argument;        // 字符串格式错误
    class file_not_found_error : public runtime_error; // 文件未找到
    class bad_get : public invalid_argument;           // Item 类型获取错误
}
```

## 快速开始 / Quick Start

```cpp
#include "all.h"
using namespace console;

int main() {
    // 输出 / Output
    print("Hello, World!");

    // 输入 / Input
    string name = inputLine("What's your name? ");
    print("Nice to meet you,", name);

    // 随机数 / Random
    int num = randint(1, 100);
    print("Random number:", num);

    // 时间测量 / Time measurement
    auto t = timer([]{
        sleep(0.1);
    });
    print("Slept for:", t);

    // 日志 / Logging
    logger.info("Program finished");

    return 0;
}
```

## 编译要求 / Build Requirements

- C++11 兼容的编译器 / C++11 compatible compiler
- 仅需标准库 / Standard library only

## 许可证 / License

MIT License[LICENSE](LICENSE)

---

**console 库** - 让 C++ 控制台编程更简单 / Making C++ console programming simpler