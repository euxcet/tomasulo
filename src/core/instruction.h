#ifndef INSTRUCTION_H
#define INSTRUCTION_H

class Instruction {
public:
	INST_TYPE inst_type;

	vector<int> regs;
	vector<int> imms;

	int lantency;

	int issue_cycle;
	int exec_cycle;
	int wb_cycle;

	Instruction(INST_TYPE inst_type, int lantency, vector<int> regs, vector<int> imms)
		: inst_type(inst_type), regs(regs), imms(imms), lantency(lantency) {
		issue_cycle = 0;
		exec_cycle = 0;
		wb_cycle = 0;
	}

	Instruction(Instruction *inst) {
		inst_type = inst -> inst_type;
		regs = inst -> regs;
		imms = inst -> imms;
		lantency = inst -> lantency;
		issue_cycle = 0;
		exec_cycle = 0;
		wb_cycle = 0;
	}
};

#endif // INSTRUCTION_h
