/*
*   SquidCore v0.1.3
*   Copyright (C) MineCommander 2020, use MIT License
*   Repo: https://github.com/MineCommanderCN/squidCore
*/
#pragma once
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
namespace squidcore {
    const int EXIT_MAIN = 65536;
    const int MAXN = 2147483647;
    struct tCmdreg {
        Fp func;
        int argcMin;
        int argcMax;
    };
    std::map<std::string, tCmdreg> cmd_register;    //first -> root command, second -> command info
    argsAry compile(std::string str) {
        str += "\n";
        argsAry tmp;
        std::string strtmp;
        int state = 0;
        for (std::string::iterator ii = str.begin(); ii != str.end(); ii++) {
            if (*ii == '\n') {
                tmp.push_back(strtmp);
                return tmp;
            }
            if (state == 0) {
                if (*ii == ' ') {

                }
                else if (*ii == '"') {
                    state = 2;
                }
                else {
                    state = 1;
                    strtmp.push_back(*ii);
                }
            }
            else if (state == 1) {
                if (*ii == ' ') {
                    tmp.push_back(strtmp);
                    strtmp.clear();
                    state = 0;
                }
                else {
                    strtmp.push_back(*ii);
                }
            }
            else if (state == 2) {
                if (*ii == '"') {
                    tmp.push_back(strtmp);
                    strtmp.clear();
                    state = 0;
                }
                else {
                    strtmp.push_back(*ii);
                }
            }
        }
        return tmp;
    }
    class cmdContainer {
    private:
        argsAry args;
    public:
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
            if (cmd_register.count(args[0]) == 1) {
                if (args.size() >= cmd_register[args[0]].argcMin && args.size() <= cmd_register[args[0]].argcMax) {
                    return cmd_register[args[0]].func(args);
                }
                else {
                    std::cout << "Incorrect arguments count: needed ("
                        << cmd_register[args[0]].argcMin << cmd_register[args[0]].argcMax
                        << ") but detected " << args.size() << std::endl;
                    return 32767;
                }
            }
            else {
                std::cout << "Unknown command '" << args[0] << "'\n";
                return 32768;
            }
        }
    };

    void regcmd(std::string cmdstr, //根命令字符串
        Fp cmdfp,           //函数指针
        int argcMin,        //需要的最少参数数量
        int argcMax) {      //需要的最大参数数量
                            //若参数数量不处于(argcMin,argcMax)中将会报错。
        tCmdreg temp{ cmdfp,argcMin,argcMax };
        cmd_register[cmdstr] = temp;
    }
}
