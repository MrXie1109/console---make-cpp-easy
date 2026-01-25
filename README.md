# console.hpp - 让C++控制台编程更简单

一个模仿Python简洁API但保持C++性能的单文件头文件库。专为讨厌C++标准库繁琐语法的开发者设计，提供直观、实用的工具集。

## 🚀 特性亮点

### 1. **Python风格输出**
```cpp
print("Hello", "World", 42);               // Hello World 42
print(Color::Red, "错误信息", Color::Reset); // 彩色输出
error("错误:", "文件不存在");              // 输出到标准错误
```

### 2. **智能输入处理**
```cpp
auto name = input("请输入姓名: ");         // 读取整行
auto age = input<int>("请输入年龄: ");     // 类型安全输入
auto score = input<double>("请输入分数: ");
```

### 3. **丰富的工具集**
- **字符串处理**: `trim`, `split`, `join`, `upper/lower/title`
- **随机工具**: `randomint`, `uniform`, `choice`
- **时间工具**: `now()`, `timer()`, `sleep()`
- **进度显示**: `ProgressBar`, `jdt()`（进度条拼音彩蛋）
- **等待动画**: `wait()`三种重载方式

## 📦 安装与使用

### 单文件包含
```cpp
#include "console.hpp"
using namespace console;

int main() {
    print("欢迎使用console.hpp!");
    return 0;
}
```

### 快速开始
```cpp
#include "console.hpp"
using namespace console;

int main() {
    // 基本输出
    print("Hello", "Console", "v1.4.0");
    
    // 彩色输出
    print(Color::Green, "✓ 任务完成");
    
    // 用户输入
    auto name = input("你的名字: ");
    auto score = input<double>("考试分数: ");
    
    // 进度条
    ProgressBar bar(100);
    for(int i = 0; i <= 100; i++) {
        bar(i / 100.0);
        sleep(0.05);
    }
    
    return 0;
}
```

## 🔧 核心功能

### 输出系统
```cpp
// 基础输出
print("文本", 123, 3.14);        // 默认分隔符空格，结束符换行
error("错误信息");                // 输出到stderr

// 彩色输出
enum class Color {
    Black, Red, Green, Yellow, Blue, 
    Magenta, Cyan, White, Reset, ...
};
print(Color::Red, "警告", Color::Reset, "正常文本");

// 自定义格式
Output custom(std::cout, "\n", ", ");
custom("苹果", "香蕉", "橙子");  // 苹果, 香蕉, 橙子
```

### 输入系统
```cpp
// 读取整行
std::string line = input("提示: ");

// 类型安全读取
int num = input<int>("数字: ");
double val = input<double>("小数: ");
char ch = input<char>("字符: ");

// 注意: input<T>()使用operator>>读取单个值
//        input()使用getline读取整行
```

### 字符串工具
```cpp
// 修剪
trim("  hello  ");      // "hello"
ltrim("  left");        // "left"
rtrim("right  ");       // "right"

// 大小写
upper("hello");         // "HELLO"
lower("WORLD");         // "world"
title("hello world");   // "Hello World"

// 分割与连接
split("a,b,c", ",");    // ["a", "b", "c"]
join({"a", "b", "c"}, "-"); // "a-b-c"
partition("hello.cpp", "."); // ("hello", ".", "cpp")
```

### 随机工具
```cpp
randomint(1, 100);      // 1-100随机整数
uniform(0.0, 1.0);      // 0-1随机浮点数

std::vector<int> vec = {1, 2, 3, 4, 5};
choice(vec);            // 随机选择一个元素
```

### 时间工具
```cpp
// 计时
auto start = now();
sleep(1.5);             // 睡眠1.5秒
auto elapsed = now() - start;
print("耗时:", elapsed); // 自动选择合适单位

// 函数计时
auto time = timer([](){
    // 你的代码
});
print("函数执行时间:", time);
```

### 进度显示
```cpp
// 进度条类
ProgressBar bar(100, '|', '|', '#', ' ', '\n', 50);
for(int i = 0; i <= 100; i++) {
    bar(i / 100.0);
    sleep(0.05);
}

// 快速进度条（彩蛋函数）
for(int i = 0; i <= 100; i++) {
    jdt(i / 100.0);     // "进度条"拼音缩写
    sleep(0.05);
}
```

### 等待动画
```cpp
wait(10);               // 旋转动画10次
wait(some_condition);   // 条件控制
wait([](){ return !finished(); }); // 函数条件
```

## 📊 容器美化输出
```cpp
std::vector<int> vec = {1, 2, 3};
std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
std::set<int> s = {1, 2, 3};

print(vec);  // [1, 2, 3]
print(m);    // {a: 1, b: 2}
print(s);    // {1, 2, 3}
```

## 🎨 颜色表
| 颜色 | 前景码 | 亮色码 |
|------|--------|--------|
| 黑色 | 30 | 90 |
| 红色 | 31 | 91 |
| 绿色 | 32 | 92 |
| 黄色 | 33 | 93 |
| 蓝色 | 34 | 94 |
| 品红 | 35 | 95 |
| 青色 | 36 | 96 |
| 白色 | 37 | 97 |

## 🛠️ 设计哲学

1. **实用主义优先**: 只解决80%常见需求
2. **API简洁**: 比原生C++更简单，默认值合理
3. **零依赖**: 单文件头文件，即包含即用
4. **保持性能**: 在简洁的同时不牺牲C++性能

## 📝 版本历史

- **v1.4.0**: 添加彩色输出系统
- **v1.3.0**: 添加字符串工具和输入系统
- **v1.2.0**: 添加随机工具和时间工具
- **v1.1.0**: 添加进度条和等待动画
- **v1.0.0**: 基础输出和容器美化

## 🔗 链接

- GitHub: [https://github.com/MrXie1109/console---make-cpp-easy](https://github.com/MrXie1109/console---make-cpp-easy)
- 许可证: MIT

## 💡 提示

- 所有函数提供合理默认值，开箱即用
- 错误处理简洁，避免复杂异常
- 支持C++11及以上标准
- 使用<bits/stdc++.h>简化包含

---

**console.hpp - 为讨厌复杂语法的C++开发者而生**