# squidCore

[CombLang](https://github.com/MineCommanderCN/combLang)使用的一款轻量的命令解析器。

## 库函数

```c++
squidcore::compile(std::string str);	//将字符串转化为参数列表
squidcore::regcmd(std::string cmdstr, //根命令字符串
        Fp cmdfp,           //函数指针
        int argcMin,        //需要的最少参数数量
        int argcMax);	   //需要的最大参数数量
//注册命令
        
```

## 数据类型

### 参数列表

本质上就是std::vector\<std::string\>。

```c++
std::string str;
squidcore::argsAry arg;	//新建一个参数列表变量
arg = squidcore::compile(str);	//通过compile()函数将字符串转化为参数列表
```

### 命令容器

命令容器用于储存命令参数列表，并通过run()函数运行其中的命令。

```c++
std::string cmd;

squidcore::cmdContainer c1;	//新建一个命令容器
squidcore::cmdContainer c2(cmd);	//直接通过字符串初始化命令容器
c1 = squidcore::compile(cmd);	//通过compile()函数将字符串转化为参数列表，并赋值给命令容器
//若此赋值语句作为赋值表达式使用，则表达式的值类型为squidcore::argsAry

c1.run();	//按照命令容器中的参数执行命令，带有int返回值
//若返回EXIT_MAIN则表示命令希望退出主程序
```

## 示例

### 编写一个命令处理函数

```c++
int funcName(const argsAry &args) {	//args是参数列表，可以当作const std::vector<std::string>使用
    code();
    ...
    return 0;	//正常返回
    return EXIT_MAIN;	//向命令解释器提出退出主程序请求
}
```

### 注册一个命令

```c++
squidcore::regcmd("foo", funcName, 1, 1);	//表示注册一个foo命令，交由funcName(args)参数处理，参数数量为(1,1)
//根命令也记入参数列表内
```

### 从控制台输入并执行命令

```c++
while (true) {
		std::string input;
		std::cout << ">> ";
		std::getline(std::cin, input);	//从控制台读入命令
		squidcore::cmdContainer cmdct(input);	//创建命令容器，储存输入的命令参数列表
		cmdct.run();	//执行命令
}
```

