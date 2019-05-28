#ifndef RS_H
#define RS_H

#include "defs.h"
#include "instruction.h"

class FC {
public:
	FC_STATUS status;
};

class RS {
public:
	RS_STATUS status;
	Instruction *inst;
	int vj;
	int vk;
	RS *qj;
	RS *qk;

	FC *fc;
	int timer;

	string name;

	RS(string name) : name(name) {
		status = RS_AVAILABLE;
		inst = NULL;
		vj = vk = 0;
		qj = qk = NULL;
		timer = 0;
	}
	~RS() {}
};

#endif // RS_H
