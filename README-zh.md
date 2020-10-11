# squidCore

[CombLang](https://github.com/MineCommanderCN/combLang)使用的一款轻量的命令解析器。

## 库函数

```c++
sqc::argsAry sqc::compile(std::string str);	//将字符串转化为参数列表
void sqc::regcmd(std::string cmdstr, //根命令字符串
        Fp cmdfp,           //函数指针
        int argcMin,        //需要的最少参数数量
        int argcMax);	   //需要的最大参数数量
//注册命令

template<class typeA, class typeB>
typeB sqc::atob(typeA buf);    //使用stringstream和模板的类型转换
double sqc::str2num(std::string str);    //调用sqc::atob的std::string转double快捷方式，避免一长串的转换函数
std::string sqc::num2str(double buf);    //跟上面相反
        
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
c1 = sqc::compile(cmd);	//通过compile()函数将字符串转化为参数列表，并直接赋值给命令容器
//若此赋值语句作为赋值表达式使用，则表达式的值类型为sqc::argsAry

c1.run();	//按照命令容器中的参数执行命令，带有int返回值
//若返回EXIT_MAIN则表示命令希望退出主程序
```

## 命令语法

squidCore只能解析不带换行符的命令。

默认情况下，字符串中两段空格隔出的区域将会被视为一个参数。（开头和结尾不计空格）

e.g. `foo abc 100`

-> `foo | abc | 100`

用双引号扩起且两端为空格的部分会被视为一个参数整体。（开头和结尾不计空格）

e.g. `foo "abc 100"`

-> `foo | abc 100`

双引号两端若缺失空格将会按照空格分隔处理，且记入引号。

e.g. `foo"abc" 100`

-> `foo"abc" | 100`

`foo "abc "100`

-> `foo | "abc | "100`

## 示例

### 编写一个命令处理函数

```c++
int funcName(const argsAry &args) {	//args是参数列表，可以当作const std::vector<std::string>使用
    std::cout << args[1];    //输出第二个参数
    return 0;    //正常退出
}
```

### 注册一个命令

```c++
sqc::regcmd("foo", funcName, 2, 2);	//表示注册一个foo命令，交由funcName(args)参数处理，参数数量为(2,2)
//根命令也记入参数列表内
```

### 从控制台输入并执行命令

```c++
while (true) {
		std::string input;
		std::cout << ">> ";
		std::cin.flush();	//清空命令内部可能使用过的输入缓冲区
		std::getline(std::cin, input);	//从控制台读入命令
		sqc::cmdContainer cmdct(input);	//创建命令容器，储存输入的命令参数列表
		int result = cmdct.run();	//执行命令并捕获返回值
    
		switch(result) {	//返回现象处理
		case sqc::EXIT_MAIN:
			return 0;	//退出主程序
			break;
		case sqc::ARGUMENT_ERROR:	//参数数量错误
			std::cout << "Argument Error!" << std::endl;	//输出信息
			break;
		case sqc::UNKNOWN_COMMAND:	//未知命令
			std::cout << "Unknown Command!" << std::endl;	//输出信息
			break;
		case 0:	//正常退出
			std::cout << "Command Exits Normally." << std::endl;	//输出信息
			break;
		default:	//其他返回值（未定义的错误）
			std::cout << "Unexpect Error!" << std::endl;
		}
		//是是是，我知道这样手动处理很麻烦，新功能下次就加
}
```

