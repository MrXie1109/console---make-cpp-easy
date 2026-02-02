# console - C++交互式开发工具库

> Make C++ Great Again! (MCGA) 🚀

**让C++写起来像Python一样顺手，但保留C++的性能和类型安全。**

## 📦 特性
- **头文件库** - 包含即用，无需编译安装
- **跨平台** - Windows/WSL/Linux 验证通过
- **纯C++11** - 零外部依赖，仅需标准库
- **Python式API** - 熟悉的使用体验

## 🚀 快速开始

```cpp
#include "console/all.h"  // 一个头文件包含所有功能
using namespace console;   // 可选，简化调用

int main() {
    print("Hello", "World", 123, 45.6);      // 自动拼接输出
    logger.info("程序启动");                 // 结构化日志
    jdt(75, beautifulSettings);              // 美观进度条
    return 0;
}
```

编译（C++11或更高）：
```bash
g++ -std=c++11 your_program.cpp -o program
```

---

## 📚 API 参考

### 🖨️ 输出系统 (`output.h`)

#### **核心类**
```cpp
class Output;  // 输出引擎，支持自定义分隔符、结束符
Output print;   // 全局实例，默认输出到cout
```

#### **函数原型**
```cpp
// 1. 容器美化输出（重载operator<<）
template<class T> ostream& operator<<(ostream&, const vector<T>&);
template<class T, size_t N> ostream& operator<<(ostream&, const array<T,N>&);
template<class K, class V> ostream& operator<<(ostream&, const map<K,V>&);
template<class T> ostream& operator<<(ostream&, const set<T>&);
template<class T, class U> ostream& operator<<(ostream&, const pair<T,U>&);

// 2. print对象使用
print(args...);                    // 使用默认配置
Output(os, sep, end, flush)(args...); // 自定义输出

// 3. 转换函数
template<class T> string uniToStr(T&& value);  // 任意类型转字符串
array<T,N> to_array(const T (&arr)[N]);        // C数组转std::array
vector<T> to_vector(const T (&arr)[N]);        // C数组转std::vector
```

#### **用途示例**
```cpp
vector<int> nums{1, 2, 3};
map<string, int> scores{{"Alice", 95}, {"Bob", 87}};

print("数组:", nums);              // 输出: 数组: [1, 2, 3]
print("成绩:", scores);            // 输出: 成绩: {Alice: 95, Bob: 87}

// 自定义输出
Output(cout, "|", "\n", true)("a", "b", "c");  // 输出: a|b|c

string str = uniToStr(nums);       // "[1, 2, 3]"
```

---

### ⌨️ 输入系统 (`input.h`)

#### **配置结构**
```cpp
struct InputSettings {
    ostream& os;  // 提示信息输出流
    istream& is;  // 输入流
} inputSettings{cout, cin};  // 全局默认配置
```

#### **函数原型**
```cpp
// 1. 基础输入
template<class T>
T input(const string& prompt = "", 
        const InputSettings& is = inputSettings);  // 泛型输入

// 2. 专用输入函数
string inputLine(const string& prompt = "Type a line string: ",
                 const InputSettings& is = inputSettings);  // 整行输入
long double inputNumber(const string& prompt = "Type a number: ",
                        const InputSettings& is = inputSettings);  // 数字输入
bool inputYesOrNo(const string& prompt = "Type yes or no: ",
                  const InputSettings& is = inputSettings);  // 是/否输入
char inputChar(const string& prompt = "Type a character: ",
               const InputSettings& is = inputSettings);  // 单字符输入

// 3. 带验证的输入
long double inputWithRange(const string& prompt = "Type yes or no: ",
                           long double min = DBL_MIN,
                           long double max = DBL_MAX,
                           const InputSettings& is = inputSettings);  // 范围验证

// 4. 菜单选择
template<class T>
T& inputChoice(const vector<T>& options,
               const string& prompt = "Type your choice: ",
               const InputSettings& is = inputSettings);  // 返回引用

template<class T>
const T& inputChoice(const vector<T>& options,  // const重载版
                     const string& prompt = "Type your choice: ",
                     const InputSettings& is = inputSettings);
```

#### **用途示例**
```cpp
auto name = input<string>("请输入姓名: ");
auto age = input<int>("年龄: ");
auto height = inputWithRange("身高(cm): ", 50.0, 250.0);
auto confirm = inputYesOrNo("确认提交? (y/n): ");

vector<string> menu{"开始游戏", "设置", "退出"};
auto& choice = inputChoice(menu, "请选择: ");  // 返回选中项的引用
```

---

### ⏱️ 时间工具 (`time.h`)

#### **结构体**
```cpp
struct TimerResult {
    double ns, us, ms, s;  // 各时间单位
    operator double() const;  // 隐式转换为纳秒
    friend ostream& operator<<(ostream&, const TimerResult&);  // 自动选单位
};
```

#### **函数原型**
```cpp
TimerResult now();  // 当前时间戳
template<class F, class... Args>
TimerResult timer(F func, const Args&... args);  // 测量函数执行时间

template<class T, class F, class... Args>
TimerResult timer(T& result, F func, const Args&... args);  // 测量并保存结果

void sleep(double seconds);  // 休眠指定秒数
void sleep(const TimerResult& tr);  // 按TimerResult休眠

string datetime(const string& format = "%Y-%m-%d %H:%M:%S");  // 格式化时间
```

#### **用途示例**
```cpp
auto start = now();

auto time = timer([]{
    sort(data.begin(), data.end());
});  // 自动选择单位输出，如"3.072μs"

sleep(1.5);  // 休眠1.5秒

print("当前时间:", datetime());  // "2024-01-31 21:02:01"
```

---

### 🎲 随机工具 (`random.h`)

#### **函数原型**
```cpp
mt19937& GEN();  // 获取随机数生成器（单例）

int64_t randint(int64_t min = 0, 
                int64_t max = 32767,
                mt19937& gen = GEN());  // 随机整数

long double uniform(double min = 0.0,
                    double max = 1.0,
                    mt19937& gen = GEN());  // 随机浮点数

template<class T>
auto choice(T&& container,
            mt19937& gen = GEN()) -> decltype(*begin(container));  // 随机选择元素
```

#### **用途示例**
```cpp
auto num = randint(1, 100);  // 1~100随机整数
auto prob = uniform(0.0, 1.0);  // 0~1随机小数

vector<string> items{"苹果", "香蕉", "橙子"};
auto& selected = choice(items);  // 随机选择一个
```

---

### 📝 字符串处理 (`strpp.h`)

#### **函数原型**
```cpp
// 1. 修剪
string ltrim(string str);   // 左修剪
string rtrim(string str);   // 右修剪
string trim(string str);    // 两侧修剪

// 2. 大小写
string upper(string str);   // 全大写（ASCII）
string lower(string str);   // 全小写（ASCII）
string title(string str);   // 标题化（首字母大写）

// 3. 分割与连接
struct PartitionResult { string left, middle, right; };  // 分割结果
PartitionResult partition(const string& text, const string& sep);  // 三部分分割

vector<string> split(string text, const string& sep = " ");  // 分割字符串

template<class T>
string join(const vector<T>& vec, const string& sep = "");  // 连接字符串
```

#### **用途示例**
```cpp
string text = "  Hello World!  ";
print("原文本: '", text, "'");
print("修剪后: '", trim(text), "'");        // "Hello World!"
print("大写: '", upper(text), "'");         // "  HELLO WORLD!  "

auto parts = split("a,b,c", ",");           // ["a", "b", "c"]
auto joined = join(parts, "->");            // "a->b->c"

auto pr = partition("hello/world/end", "/");  // left="hello", middle="/", right="world/end"
```

---

### 🎨 颜色常量 (`colorful.h`)

#### **常量定义**
```cpp
namespace color {
    // 前景色
    const char *Black, *Red, *Green, *Yellow, *Blue, *Magenta, *Cyan, *White;
    const char *BrightBlack, *BrightRed, *BrightGreen, *BrightYellow;
    const char *BrightBlue, *BrightMagenta, *BrightCyan, *BrightWhite;
    const char *Reset;  // 重置颜色
    
    // 背景色
    const char *BgBlack, *BgRed, *BgGreen, *BgYellow, *BgBlue;
    const char *BgMagenta, *BgCyan, *BgWhite;
    const char *BgBrightBlack, *BgBrightRed, *BgBrightGreen;
    const char *BgBrightYellow, *BgBrightBlue, *BgBrightMagenta;
    const char *BgBrightCyan, *BgBrightWhite;
    
    // 样式
    const char *Bold, *Dim, *Italic, *Underline;
    const char *Blink, *Reverse, *Hidden, *Strikethrough;
}
```

#### **用途示例**
```cpp
print(color::Red, "错误: ", color::Reset, "文件不存在");
print(color::BgBlue, color::Bold, "重要提示", color::Reset);
```

---

### 📋 日志系统 (`logging.h`)

#### **核心类**
```cpp
class Logging {
public:
    enum class Level : int8_t { DEBUG, INFO, WARN, ERROR, FATAL };
    
    // 构造函数
    Logging(ostream& os = cout, 
            bool colorful = false,
            Level level = Level::INFO);
    
    // 日志方法
    template<class... Args> void debug(const Args&... args);
    template<class... Args> void info(const Args&... args);
    template<class... Args> void warn(const Args&... args);
    template<class... Args> void error(const Args&... args);
    template<class... Args> [[noreturn]] void fatal(const Args&... args);  // 会抛异常
    
    // 级别控制
    void set(Level minLevel);  // 设置最低显示级别
    void set(bool debug, bool info, bool warn, bool error, bool fatal);  // 精细控制
};

Logging logger(cout, true, Logging::Level::INFO);  // 全局实例
```

#### **用途示例**
```cpp
logger.set(Logging::Level::DEBUG);  // 显示所有级别

logger.debug("调试信息:", variable);
logger.info("用户登录:", username);
logger.warn("内存不足:", free_memory, "MB");
logger.error("连接失败:", err_code);

try {
    logger.fatal("致命错误: 数据库崩溃");
} catch (const fatal_logging& e) {
    // fatal会抛异常，可以捕获处理
}
```

---

### 📊 进度条 (`jdt.h`)

#### **配置结构**
```cpp
struct JdtSettings {
    int len;                  // 进度条长度
    const char *lch, *rch;    // 左右边界字符
    const char *fch, *ech;    // 填充和空白字符  
    const char *Ech;          // 结束字符（通常"\r"）
    ostream &os;              // 输出流
};

// 预设样式
const JdtSettings defaultSettings{50, "[", "]", "#", " ", "\r", cout};
const JdtSettings simpleSettings{50, "", "", "=", "-", "\r", cout};
const JdtSettings beautifulSettings{50, "▕", "▏", "█", "░", "\r", cout};
```

#### **函数原型**
```cpp
void jdt(int percent, const JdtSettings& js = defaultSettings);
// 注意：percent应在0-100之间，否则抛jdt_range_error异常
```

#### **用途示例**
```cpp
// 简单使用
for (int i = 0; i <= 100; i++) {
    jdt(i);
    sleep(0.01);
}
print();  // 完成后换行

// 使用预设
jdt(75, beautifulSettings);  // Unicode风格
jdt(75, simpleSettings);     // 简约风格

// 自定义
JdtSettings custom{30, "|", "|", "*", ".", "\r", cerr};
jdt(50, custom);
```

---

### ⚠️ 异常系统 (`csexc.h`)

#### **异常类**
```cpp
class fatal_logging : public runtime_error {
public:
    fatal_logging(const string& msg);  // 日志系统致命错误
};

class jdt_range_error : public invalid_argument {
public:
    jdt_range_error(const string& msg);  // 进度条参数范围错误
};
```

#### **用途示例**
```cpp
try {
    jdt(150);  // 会抛jdt_range_error
} catch (const jdt_range_error& e) {
    logger.error("进度参数错误:", e.what());
}

try {
    logger.fatal("严重错误");
} catch (const fatal_logging& e) {
    // fatal一定会抛异常
}
```

---

## 🔧 高级用法

### 自定义配置
```cpp
// 创建自定义logger
Logging fileLogger(logfile, false, Logging::Level::DEBUG);

// 自定义进度条样式  
JdtSettings myStyle{40, ">", "<", "=", " ", "\r", cout};

// 自定义输入设置
InputSettings myInput{cout, ifstream("input.txt")};
```

### 组合使用
```cpp
// 完整的交互程序示例
logger.info("程序启动");
auto name = input<string>("姓名: ");
logger.info("用户:", name);

print("计算中...");
auto time = timer([&]{
    complex_calculation();
});

jdt(100, beautifulSettings);
print();
logger.info("计算完成，耗时:", time);
```

---

## 📁 项目结构
```
console/
├── all.h              # 总包含文件
├── std.h              # 标准库快捷包含
├── output.h           # 输出系统
├── input.h            # 输入系统
├── time.h             # 时间工具
├── random.h           # 随机工具
├── strpp.h            # 字符串处理
├── colorful.h         # 颜色常量
├── logging.h          # 日志系统
├── jdt.h              # 进度条
└── csexc.h            # 自定义异常
```

---

## ⚠️ 注意事项

1. **颜色输出**：输出到文件时请设置`colorful=false`，避免ANSI码污染
2. **Unicode字符**：`beautifulSettings`使用Unicode字符，确保终端支持
3. **异常安全**：`fatal()`会抛出异常，注意捕获处理
4. **进度条**：使用`"\r"`在同一行更新，完成后记得换行

---

## 🎯 设计哲学

**"喂饭但可调味"** - 每个功能都有合理默认值，但所有参数都可自定义。

**"太麻烦了不做"** - 专注于解决80%的常见需求，不做过度设计。

**MCGA精神** - 让C++开发更愉快，更高效，更有趣！

---

## 📄 许可证
MIT License - 详见 [LICENSE](LICENSE) 文件