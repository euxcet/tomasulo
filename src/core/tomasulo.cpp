#include "tomasulo.h"

bool Tomasulo::is_finished() {
	for(int i = 0; i < all_rs.size(); i++) {
		if (all_rs[i] -> status != RS_AVAILABLE)
			return false;
	}
	if (pc < insts.size()) {
		return false;
	}
	return true;
}

FC* Tomasulo::get_idle_fc(vector<FC*> fc) {
	for(int i = 0; i < fc.size(); i++)
		if (fc[i] -> status == FC_AVAILABLE) {
			return fc[i];
		}
	return NULL;
}

void Tomasulo::print_regs() {
	for(int i = 0; i < run_insts.size(); i++) {
		printf("%d %d %d\n", run_insts[i] -> issue_cycle, run_insts[i] -> exec_cycle, run_insts[i] -> wb_cycle);
	}
	for(int i = 0; i < 8; i++) {
		printf("F%d = %d\n", i, regs[i]);
	}
	puts("");
}

// issue stage
void Tomasulo::issue() {
	if (pc >= insts.size() || pause) {
		return;
	}
	run_insts.push_back(new Instruction(insts[pc]));
	vector<RS*> tmp_rs;
	Instruction *inst = run_insts[run_insts.size() - 1];
	if (inst -> inst_type == INST_ADD || inst -> inst_type == INST_SUB || inst -> inst_type == INST_JUMP) {
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

			if (inst -> inst_type == INST_JUMP) {
				pause = true;
				tmp_rs[i] -> qj = belong[inst -> regs[0]];
				if (tmp_rs[i] -> qj == NULL) {
					tmp_rs[i] -> vj = regs[inst -> regs[0]];
				}
				tmp_rs[i] -> qk = NULL;
				tmp_rs[i] -> vk = 0;
			}
			else {
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
				belong[inst -> regs[0]] = tmp_rs[i];
			}
			inst -> issue_cycle = cycles;
			pc ++;

			cout << "  Issue " << tmp_rs[i] -> name << endl;
			if (tmp_rs[i] -> qj != NULL) {
				cout << tmp_rs[i] -> qj -> name << endl;
			}

			if (tmp_rs[i] -> qk != NULL) {
				cout << tmp_rs[i] -> qk -> name << endl;
			}
			return;
		}
	delete run_insts[run_insts.size() - 1];
	run_insts.pop_back();
}

void Tomasulo::execute(vector<RS*> rs, vector<FC*> fc) {
	for(int i = 0; i < rs.size(); i++)
		if (rs[i] -> status == RS_BUSY && rs[i] -> qj == NULL && rs[i] -> qk == NULL) {
			if (rs[i] -> timer == -1) {
				FC* fc_ava;
				if ((fc_ava = get_idle_fc(fc)) != NULL) {
					rs[i] -> fc = fc_ava;
					fc_ava -> status = FC_BUSY;
					rs[i] -> timer = rs[i] -> inst -> lantency - 1;
					rs[i] -> inst -> exec_cycle = cycles;
				}
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

void Tomasulo::active(RS* rs, int res) {
	for(int j = 0; j < all_rs.size(); j++) {
		if (all_rs[j] -> qj == rs) {
			all_rs[j] -> qj = NULL;
			all_rs[j] -> vj = res;
		}
		if (all_rs[j] -> qk == rs) {
			all_rs[j] -> qk = NULL;
			all_rs[j] -> vk = res;
		}
	}
}

int Tomasulo::process(RS *rs) {
	Instruction *inst = rs -> inst;
	int vj = rs -> vj;
	int vk = rs -> vk;
	if (inst -> inst_type == INST_ADD) {
		return vj + vk;
	}
	else if (inst -> inst_type == INST_SUB) {
		return vj - vk;
	}
	else if (inst -> inst_type == INST_MUL) {
		return vj * vk;
	}
	else if (inst -> inst_type == INST_DIV) {
		return vj / vk;
	}
	else if (inst -> inst_type == INST_LD) {
		return inst -> imms[0];
	}
	if (inst -> inst_type == INST_JUMP) {
		printf(" regs[%d] = %d  limit = %d  delta = %d\n", inst -> regs[0], regs[inst -> regs[0]], inst -> imms[0], inst -> imms[1]);
		if (regs[inst -> regs[0]] != inst -> imms[0]) {
			pc += inst -> imms[1] - 1;
			pause = false;
		}
		return 0;
	}
	return -1;
}

void Tomasulo::writeback(vector<RS*> rs, vector<FC*> fc) {
	for(int i = 0; i < rs.size(); i++)
		if (rs[i] -> status == RS_BUSY && rs[i] -> qj == NULL && rs[i] -> qk == NULL && rs[i] -> timer == 0) {
			if (rs[i] -> fc != NULL) {
				rs[i] -> fc -> status = FC_AVAILABLE;
				rs[i] -> fc = NULL;
			}
			rs[i] -> status = RS_RESULT_READY;
		}
		else if (rs[i] -> status == RS_RESULT_READY) {
			rs[i] -> inst -> wb_cycle = cycles;

			int res = process(rs[i]);

			if (belong[rs[i] -> inst -> regs[0]] == rs[i]) {
				belong[rs[i] -> inst -> regs[0]] = NULL;
				regs[rs[i] -> inst -> regs[0]] = res;
			}

			active(rs[i], res);


			rs[i] -> status = RS_AVAILABLE;
			rs[i] -> inst = NULL;
			rs[i] -> qj = rs[i] -> qk = NULL;
			rs[i] -> timer = 0;

		}
}

void Tomasulo::execute() {
	execute(add_rs, add_fc);
	execute(mul_rs, mul_fc);
	execute(load_rs, load_fc);
}

void Tomasulo::writeback() {
	writeback(add_rs, add_fc);
	writeback(mul_rs, mul_fc);
	writeback(load_rs, load_fc);
}

// main loop
void Tomasulo::run() {
	while (!is_finished()) {
		cycles ++;
		issue();
		execute();
		writeback();
	}
}


void Tomasulo::create_rs(vector<RS*> &rs, int num, string name) {
    for(int i = 0; i < num; i++) {
        RS *tmp_rs = new RS(name + to_string(i));
        rs.push_back(tmp_rs);
        all_rs.push_back(tmp_rs);
    }
}

void Tomasulo::create_fc(vector<FC*> &fc, int num) {
    for(int i = 0; i < num; i++) {
        fc.push_back(new FC());
    }
}

Tomasulo::Tomasulo(vector<Instruction*> insts) : insts(insts) {
    cycles = 0;
    pc = 0;
    pause = false;

    memset(regs, 0, sizeof(regs));

    // initialize reservation stations and functional components
    create_rs(add_rs, ADD_RS_NUM, "add_rs");
    create_rs(mul_rs, MUL_RS_NUM, "mul_rs");
    create_rs(load_rs, LOAD_RS_NUM, "load_rs");
    create_fc(add_fc, ADD_FC_NUM);
    create_fc(mul_fc, MUL_FC_NUM);
    create_fc(load_fc, LOAD_FC_NUM);
}

Tomasulo::~Tomasulo() {
    clear_vector(add_rs);
    clear_vector(mul_rs);
    clear_vector(load_rs);
    clear_vector(add_fc);
    clear_vector(mul_fc);
    clear_vector(load_fc);
    clear_vector(run_insts);
}
