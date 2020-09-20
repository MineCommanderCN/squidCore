# squidCore

[CombLang](https://github.com/MineCommanderCN/combLang)使用的一款轻量的命令解析器。

## 库函数

```c++
sqc::compile(std::string str);	//将字符串转化为参数列表
sqc::regcmd(std::string cmdstr, //根命令字符串
        Fp cmdfp,           //函数指针
        int argcMin,        //需要的最少参数数量
        int argcMax);	   //需要的最大参数数量
//注册命令

sqc::atob<typeA, typeB>(typeA buf);    //使用stringstream的类型转换
sqc::str2num(std::string str);    //调用sqc::atob的std::string转double快捷方式
sqc::num2str(double buf);    //跟上面相反

sqc::io.print(std::string str);    //使用sqc::io标准输入输出类向屏幕输出字符串
//这个类还有很多其他跟统一io有关的功能（其实只有输出） 太多了懒得介绍以后再补（
        
```

## 数据类型

### 参数列表

本质上就是std::vector\<std::string\>。

```c++
std::string str;
sqc::argsAry arg;	//新建一个参数列表变量
arg = sqc::compile(str);	//通过compile()函数将字符串转化为参数列表
```

### 命令容器

命令容器用于储存命令参数列表，并通过run()函数运行其中的命令。

```c++
std::string cmd;

sqc::cmdContainer c1;	//新建一个命令容器
sqc::cmdContainer c2(cmd);	//直接通过字符串初始化命令容器
c1 = sqc::compile(cmd);	//通过compile()函数将字符串转化为参数列表，并赋值给命令容器
//若此赋值语句作为赋值表达式使用，则表达式的值类型为sqc::argsAry

c1.run();	//按照命令容器中的参数执行命令，带有int返回值
//若返回EXIT_MAIN则表示命令希望退出主程序
```

## 示例

### 编写一个命令处理函数

```c++
int funcName(const argsAry &args) {	//args是参数列表，可以当作const std::vector<std::string>使用
    sqc::io.print(args[1]);    //输出第二个参数
    return 0;    //正常退出
}
```

### 注册一个命令

```c++
sqc::regcmd("foo", funcName, 2, 2);	//表示注册一个foo命令，交由funcName(args)参数处理，参数数量为(1,1)
//根命令也记入参数列表内
```

### 从控制台输入并执行命令

```c++
while (true) {
		std::string input;
		std::cout << ">> ";
		std::getline(std::cin, input);	//从控制台读入命令
		sqc::cmdContainer cmdct(input);	//创建命令容器，储存输入的命令参数列表
		cmdct.run();	//执行命令
}
```

