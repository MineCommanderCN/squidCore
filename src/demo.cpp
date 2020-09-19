#include "squidCore_lib.hpp"

int printHello(const squidcore::argsAry &args) {
	squidcore::io.print("Hello world!");
	return 0;
}

int aplusb(const squidcore::argsAry &args){
	float a = squidcore::str2num(args[1]), b = squidcore::str2num(args[2]);
	squidcore::io.print(squidcore::atob<float, std::string>(a+b));
	return 0;
}


void regist_cmd(void) {
	squidcore::regcmd("test",printHello,1,1);
	squidcore::regcmd("a+b",aplusb,3,3);
}


int main() {
	squidcore::io.coloringOnLinux(false);
	regist_cmd();
	while (1) {
		std::string input;
		std::cout << ">> ";
		std::getline(std::cin, input);
		squidcore::cmdContainer cmdct(input);
		cmdct.run();
	}
}
