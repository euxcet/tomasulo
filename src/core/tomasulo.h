#ifndef TOMASULO_H
#define TOMASULO_H

#include "rs.h"
#include "defs.h"
#include "utils.h"

class Tomasulo {
private:
	vector<Instruction*> insts;
	vector<Instruction*> run_insts;
	int cycles;
	int pc;
	bool pause;

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

	Tomasulo(vector<Instruction*> insts);
	~Tomasulo();

	FC* get_idle_fc(vector<FC*> fc);
	bool is_finished();
	void print_regs();

	void create_fc(vector<FC*> &fc, int num);
	void create_rs(vector<RS*> &rs, int num, string name);

	void issue();
	void active(RS* rs, int res);
	int process(RS *rs);
	void execute(vector<RS*> rs, vector<FC*> fc);
	void execute();
	void writeback(vector<RS*> rs, vector<FC*> fc);
	void writeback();
	void run();

};

#endif // TOMASULO_H
