#include "squidCore_lib.hpp"

int printHello(const lcmd& args) {
	std::cout << "Hello world!" << std::endl;
	return 0;
}



void regist_cmd(void) {
	sll::regcmd("test",printHello,1,1);
}


int main() {
	regist_cmd();
	while (1) {
		std::string input;
		std::cout << ">> ";
		std::getline(std::cin, input);
		sll::command.run(input);
	}
}
