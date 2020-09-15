#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<fstream>
#include<string>
#include<sstream>

typedef std::vector<std::string> argsAry;
typedef int(*Fp)(const argsAry &args);
namespace sll {
    const int EXIT_MAIN = 65536;
    const int MAXN = 2147483647;
    struct tCmdreg {
        Fp func;
        int argcMin;
        int argcMax;
    };
    std::map<std::string, tCmdreg> cmd_register;    //first -> root command, second -> command info
    std::string getSysTimeData(void) {
        time_t t = time(0);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y%m%d-%H%M%S", localtime(&t));
        return tmp;
    }
    std::string getSysTime(void) {
        time_t t = time(0);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%H:%M:%S", localtime(&t));
        return tmp;
    }
    template <class Ta, class Tb>
    Tb atob(const Ta& t) {
        std::stringstream temp;
        temp << t;
        Tb i;
        temp >> i;
        return i;
    }
    argsAry compile(std::string str) {
        str += "\n";
        argsAry tmp;
        tmp.push_back("");/*
        int state = 0;
        for (std::string::iterator ii = str.begin(); ii != str.end(); ii++) {   //WIP

        }*/
        return tmp;
    }
    class cmdContainer {
        public:
            argsAry args;
            cmdContainer operator=(const std::string& str) {
                this->args = compile(str);
                return this->args;
            }
            cmdContainer() {

            }
            cmdContainer(std::string str) {
                args = compile(str);
            }
            cmdContainer(argsAry argy) {
                args = argy;
            }
            int run() {
                if (cmd_register.count(args[0]) == 1) return cmd_register[args[0]].func(args);
                else std::cout << "Unknown command '" << args[0] << "'\n";
            }
    };
    
    void regcmd(std::string cmdstr, //根命令字符串
                Fp cmdfp,           //函数指针
                int argcMin,        //需要的最少参数数量
                int argcMax) {      //需要的最大参数数量
                                    //若参数数量不处于[argcMin,argcMax]中将会报错。
        tCmdreg temp{ cmdfp,argcMin,argcMax };
        cmd_register[cmdstr] = temp;
    }
}
