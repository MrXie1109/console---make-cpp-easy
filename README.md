# console.hpp

让C++写起来像Python一样爽的单头文件库。

## 为什么？
因为C++标准库太TM难用了。

## 怎么用？
```cpp
#include "console.hpp"
using namespace console;

int main() {
    // Python风格的print
    print("Hello", "World", 42, 3.14);
    
    // 容器漂亮输出
    std::vector<int> v = {1, 2, 3};
    print(v);  // 输出: [1, 2, 3]
    
    std::map<std::string, int> m = {{"a", 1}, {"b", 2}};
    print(m);  // 输出: {a: 1, b: 2}
    
    // 计时
    auto t = timer([]{
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    });
    print("耗时:", t);  // 自动选单位
    
    // 随机
    print("随机数:", randomint(1, 100));
    
    return 0;
}

```

有什么？
print(...) - Python风格输出

容器输出：vector, map, set, array, pair

时间工具：timer(), sleep(), now()

随机工具：randomint(), uniform(), choice()

字符串工具：trim(), split(), join(), partition()

文件工具：save(), load() (仅POD类型)