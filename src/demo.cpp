#include "squidCore_lib.hpp"

int printHello(const sqc::argsAry &args) {
	sqc::io.print("Hello world!");
	return 0;
}

int aplusb(const sqc::argsAry &args) {
	double a = sqc::str2num(args[1]), b = sqc::str2num(args[2]);
	sqc::io.print(sqc::num2str(a + b));
	return 0;
}


void regist_cmd(void) {
	sqc::regcmd("test", printHello, 1, 1);
	sqc::regcmd("a+b", aplusb, 3, 3);
}


int main() {
	sqc::io.coloringOnLinux(false);
	sqc::io.logWithTheTime(true);
	regist_cmd();
	while (1) {
		std::string input;
		std::cout << ">> ";
		std::getline(std::cin, input);
		sqc::cmdContainer cmdct(input);
		cmdct.run();
	}
}
