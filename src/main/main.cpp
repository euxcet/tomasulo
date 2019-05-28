#include "tomasulo.h"
#include "parser.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("usage: ./main NEL_FILE\n");
		return 0;
	}
	NELParser parser;
	vector<Instruction*> insts = parser.parse(argv[1]);
	Tomasulo tomasulo(insts);
	tomasulo.run();
	tomasulo.print_regs();
	for(int i = 0; i < insts.size(); i++) {
		delete insts[i];
	}
}
