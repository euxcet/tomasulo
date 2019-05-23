#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <cassert>
#include <iostream>

#define REG_NUM 128

#define ADD_RS_NUM 6
#define MUL_RS_NUM 3
#define LOAD_RS_NUM 3
#define ADD_FC_NUM 3
#define MUL_FC_NUM 2
#define LOAD_FC_NUM 2

#define LOAD_LANTENCY 2
#define ADD_LANTENCY 2
#define SUB_LANTENCY 2
#define MUL_LANTENCY 10
#define DIV_LANTENCY 40
#define JUMP_LANTENCY 1

/*
#define LOAD_LANTENCY 3
#define ADD_LANTENCY 3
#define SUB_LANTENCY 3
#define MUL_LANTENCY 12
#define DIV_LANTENCY 40
#define JUMP_LANTENCY 1
*/


using namespace std;

enum INST_TYPE {
	INST_ADD, INST_MUL, INST_SUB, INST_DIV, INST_LD, INST_JUMP
};


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
};

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
		}
		return insts;
	}
};

enum RS_STATUS {
	RS_AVAILABLE, RS_BUSY_READY, RS_BUSY, RS_RESULT_READY
};

class RS {
public:
	RS_STATUS status;
	Instruction *inst;

	int vj;
	int vk;

	RS *qj;
	RS *qk;

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

enum FC_STATUS {
	FC_AVAILABLE, FC_BUSY
};

class FC {
	FC_STATUS status;
	Instruction *inst;

	int result;
};

class Tomasulo {
private:
	vector<Instruction*> insts;
	int cycles;
	int issued;
	int finished;

	vector<RS*> add_rs;
	vector<RS*> mul_rs;
	vector<RS*> load_rs;
	
	vector<RS*> all_rs;


	vector<FC*> add_fc;
	vector<FC*> mul_fc;
	vector<FC*> load_fc;

	int regs[REG_NUM];
	RS* belong[REG_NUM];


public:
	Tomasulo(vector<Instruction*> insts) : insts(insts) {
		cycles = 0;
		finished = 0;
		issued = 0;


		// init reservation stations and functional components
		for(int i = 0; i < ADD_RS_NUM; i++) {
			add_rs.push_back(new RS("add_rs" + to_string(i)));
			all_rs.push_back(add_rs[add_rs.size() - 1]);
		}
		for(int i = 0; i < MUL_RS_NUM; i++) {
			mul_rs.push_back(new RS("mul_rs" + to_string(i)));
			all_rs.push_back(mul_rs[mul_rs.size() - 1]);
		}
		for(int i = 0; i < LOAD_RS_NUM; i++) {
			load_rs.push_back(new RS("load_rs" + to_string(i)));
			all_rs.push_back(load_rs[load_rs.size() - 1]);
		}
		for(int i = 0; i < ADD_FC_NUM; i++) {
			add_fc.push_back(new FC());
		}
		for(int i = 0; i < MUL_FC_NUM; i++) {
			mul_fc.push_back(new FC());
		}
		for(int i = 0; i < LOAD_FC_NUM; i++) {
			load_fc.push_back(new FC());
		}

		for(int i = 0; i < REG_NUM; i++) {
			regs[i] = 0;
		}
	}

	~Tomasulo() {
		for(int i = 0; i < add_rs.size(); i++) {
			delete add_rs[i];
		}
		for(int i = 0; i < mul_rs.size(); i++) {
			delete mul_rs[i];
		}
		for(int i = 0; i < load_rs.size(); i++) {
			delete load_rs[i];
		}
		for(int i = 0; i < add_fc.size(); i++) {
			delete add_fc[i];
		}
		for(int i = 0; i < mul_fc.size(); i++) {
			delete mul_fc[i];
		}
		for(int i = 0; i < load_fc.size(); i++) {
			delete load_fc[i];
		}
	}

	void issue() {
		if (issued >= insts.size()) {
			return;
		}
		vector<RS*> tmp_rs;
		Instruction *inst = insts[issued];
		if (inst -> inst_type == INST_ADD || inst -> inst_type == INST_SUB) {
			tmp_rs = add_rs;
		}
		if (inst -> inst_type == INST_MUL || inst -> inst_type == INST_DIV) {
			tmp_rs = mul_rs;
		}
		if (inst -> inst_type == INST_LD) {
			tmp_rs = load_rs;
		}


		for(int i = 0; i < tmp_rs.size(); i++)
			if (tmp_rs[i] -> status == RS_AVAILABLE) {
				tmp_rs[i] -> status = RS_BUSY_READY;
				tmp_rs[i] -> inst = inst;
				if (inst -> regs.size() > 1) {
					tmp_rs[i] -> qj = belong[inst -> regs[1]];
					if (tmp_rs[i] -> qj == NULL) {
						tmp_rs[i] -> vj = regs[inst -> regs[1]];
					}
				}
				if (inst -> regs.size() > 2) {
					tmp_rs[i] -> qk = belong[inst -> regs[2]];
					if (tmp_rs[i] -> qk == NULL) {
						tmp_rs[i] -> vk = regs[inst -> regs[2]];
					}
				}


				cout << "  Issue " << tmp_rs[i] -> name << endl;
				if (tmp_rs[i] -> qj != NULL) {
					cout << tmp_rs[i] -> qj -> name << endl;
				}

				if (tmp_rs[i] -> qk != NULL) {
					cout << tmp_rs[i] -> qk -> name << endl;
				}

				inst -> issue_cycle = cycles;
				belong[inst -> regs[0]] = tmp_rs[i];
				issued += 1;
				break;
			}

	}

	void execute(vector<RS*> rs, vector<FC*> fc) {
		for(int i = 0; i < rs.size(); i++)
			if (rs[i] -> status == RS_BUSY && rs[i] -> qj == NULL && rs[i] -> qk == NULL) {
				if (rs[i] -> timer == -1) {
					rs[i] -> timer = rs[i] -> inst -> lantency - 1;
					rs[i] -> inst -> exec_cycle = cycles;
				}
				else {
					rs[i] -> timer --;
				}
			}
			else if (rs[i] -> status == RS_BUSY_READY) {
				rs[i] -> status = RS_BUSY;
				rs[i] -> timer = -1;
			}
	}

	void active(RS* rs) {
		for(int j = 0; j < all_rs.size(); j++) {
			if (all_rs[j] -> qj == rs) {
				all_rs[j] -> qj = NULL;
				all_rs[j] -> vj = regs[rs -> inst -> regs[0]];
			}
			if (all_rs[j] -> qk == rs) {
				all_rs[j] -> qk = NULL;
				all_rs[j] -> vk = regs[rs -> inst -> regs[0]];
			}
		}
	}

	void process(Instruction *inst, int vj, int vk) {
		if (inst -> inst_type == INST_ADD) {
			regs[inst -> regs[0]] = vj + vk;
		}
		else if (inst -> inst_type == INST_SUB) {
			regs[inst -> regs[0]] = vj - vk;
		}
		else if (inst -> inst_type == INST_MUL) {
			regs[inst -> regs[0]] = vj * vk;
		}
		else if (inst -> inst_type == INST_DIV) {
			printf("%d %d\n", vj, vk);
			regs[inst -> regs[0]] = vj / vk;
		}
		else if (inst -> inst_type == INST_LD) {
			regs[inst -> regs[0]] = inst -> imms[0];
		}
		else if (inst -> inst_type == INST_JUMP) {
		}
	}

	void writeback(vector<RS*> rs, vector<FC*> fc) {
		for(int i = 0; i < rs.size(); i++)
			if (rs[i] -> status == RS_BUSY && rs[i] -> qj == NULL && rs[i] -> qk == NULL) {
				if (rs[i] -> timer == 0) {
					rs[i] -> status = RS_RESULT_READY;
				}
			}
			else if (rs[i] -> status == RS_RESULT_READY) {
				rs[i] -> inst -> wb_cycle = cycles;

				finished ++;

				cout << "  Writeback " << rs[i] -> name << endl;

				process(rs[i] -> inst, rs[i] -> vj, rs[i] -> vk);


				active(rs[i]);

				belong[rs[i] -> inst -> regs[0]] = NULL;
				rs[i] -> status = RS_AVAILABLE;
				rs[i] -> inst = NULL;
				rs[i] -> qj = rs[i] -> qk = NULL;
				rs[i] -> timer = 0;

			}
	}

	void execute() {
		execute(add_rs, add_fc);
		execute(mul_rs, mul_fc);
		execute(load_rs, load_fc);
	}

	void writeback() {
		writeback(add_rs, add_fc);
		writeback(mul_rs, mul_fc);
		writeback(load_rs, load_fc);
	}

	void run() {
		while (finished < insts.size()) {
			cycles ++;
			//printf("cycle %d\n", cycles);
			issue();
			execute();
			writeback();
		}
		puts("\n");
		for(int i = 0; i < all_rs.size(); i++) {
			cout << all_rs[i] -> name << "   " << all_rs[i] << endl;
			if (all_rs[i] -> qj != NULL) {
				cout << "   " << all_rs[i] -> qj -> name << "  " << all_rs[i] -> qj << endl;
			}
			if (all_rs[i] -> qk != NULL) {
				cout << "   " << all_rs[i] -> qk -> name << "  " << all_rs[i] -> qk << endl;
			}
		}
	}

	void print_regs() {
		for(int i = 0; i < 16; i++) {
			printf("F%d = %d\n", i, regs[i]);
		}
		puts("");
	}
};


int main() {
	NELParser parser;
	vector<Instruction*> insts = parser.parse("../data/test4.nel");
	Tomasulo tomasulo(insts);
	tomasulo.run();
	for(int i = 0; i < insts.size(); i++) {
		printf("%d %d %d\n", insts[i] -> issue_cycle, insts[i] -> exec_cycle, insts[i] -> wb_cycle);
	}
	tomasulo.print_regs();
	for(int i = 0; i < insts.size(); i++) {
		delete insts[i];
	}
}
