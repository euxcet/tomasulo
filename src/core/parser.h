#ifndef PARSER_H
#define PARSER_H

class NELParser {

public:
	NELParser() { }

	~NELParser() { }

	void ignore(char *buffer, int &offset) {
		while (offset < strlen(buffer) && (buffer[offset] == ',' || buffer[offset] == ' ')) {
			offset ++;
		}
	}

	string getstring(char *buffer, int offset, int count) {
		return ((string)buffer).substr(offset, count);
	}

	pair<INST_TYPE, int> parseInst(char *buffer, int &offset) {
		ignore(buffer, offset);
		if (getstring(buffer, offset, 2) == "LD") {
			offset += 2;
			return make_pair(INST_LD, LOAD_LANTENCY);
		}
		else if (getstring(buffer, offset, 3) == "ADD") {
			offset += 3;
			return make_pair(INST_ADD, ADD_LANTENCY);
		}
		else if (getstring(buffer, offset, 3) == "SUB") {
			offset += 3;
			return make_pair(INST_SUB, SUB_LANTENCY);
		}
		else if (getstring(buffer, offset, 3) == "MUL") {
			offset += 3;
			return make_pair(INST_MUL, MUL_LANTENCY);
		}
		else if (getstring(buffer, offset, 3) == "DIV") {
			offset += 3;
			return make_pair(INST_DIV, DIV_LANTENCY);
		}
		else if (getstring(buffer, offset, 4) == "JUMP") {
			offset += 4;
			return make_pair(INST_JUMP, JUMP_LANTENCY);
		}
		return make_pair(INST_ADD, 3);
	}

	int tohex(char c) {
		if (c >= '0' && c <= '9') {
			return c - '0';
		}
		if (c >= 'a' && c <= 'f') {
			return c - 'a' + 10;
		}
		if (c >= 'A' && c <= 'F') {
			return c - 'A' + 10;
		}
		return -1;
	}

	int parseReg(char *buffer, int &offset) {
		ignore(buffer, offset);
		assert(buffer[offset] == 'F');
		int reg = 0;
		for (offset += 1; offset < strlen(buffer) && buffer[offset] >= '0' && buffer[offset] <= '9'; offset ++) {
			reg = reg * 10 + (buffer[offset] - '0');
		}
		return reg;
	}

	int parseImm(char *buffer, int &offset) {
		ignore(buffer, offset);
		assert(offset + 1 < strlen(buffer));
		assert(buffer[offset] == '0' && buffer[offset + 1] == 'x');
		int imm = 0;
		for (offset += 2; offset < strlen(buffer) && tohex(buffer[offset]) != -1; offset ++) {
			imm = imm * 16 + tohex(buffer[offset]);
		}
		return imm;
	}


	vector<Instruction*> parse(const char *path) {
		vector<Instruction*> insts;
		ifstream in(path);
		char buffer[256];
		while (!in.eof()) {
			in.getline(buffer, 100);
			if (strlen(buffer) < 3) continue;
			int offset = 0;
			pair<INST_TYPE, int> inst_info = parseInst(buffer, offset);
			INST_TYPE inst_type = inst_info.first;
			int lantency = inst_info.second;
			vector<int> imms;
			vector<int> regs;
			if (inst_type == INST_LD) {
				regs.push_back(parseReg(buffer, offset));
				imms.push_back(parseImm(buffer, offset));
			}
			else if (inst_type == INST_ADD || inst_type == INST_SUB ||
					 inst_type == INST_MUL || inst_type == INST_DIV) {
				regs.push_back(parseReg(buffer, offset));
				regs.push_back(parseReg(buffer, offset));
				regs.push_back(parseReg(buffer, offset));
			}
			else if (inst_type == INST_JUMP) {
				imms.push_back(parseImm(buffer, offset));
				regs.push_back(parseReg(buffer, offset));
				imms.push_back(parseImm(buffer, offset));
			}
			insts.push_back(new Instruction(inst_type, lantency, regs, imms));
			for(int i =0 ;i < imms.size(); i++) {
				printf("%d ",imms[i]);
			}
			puts("");
		}
		return insts;
	}
};

#endif // PARSER_H
