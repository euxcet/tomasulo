#ifndef DEFS_H
#define DEFS_H

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

/*
#define LOAD_LANTENCY 2
#define ADD_LANTENCY 2
#define SUB_LANTENCY 2
#define MUL_LANTENCY 10
#define DIV_LANTENCY 40
#define JUMP_LANTENCY 1
*/

#define LOAD_LANTENCY 3
#define ADD_LANTENCY 3
#define SUB_LANTENCY 3
#define MUL_LANTENCY 12
#define DIV_LANTENCY 40
#define JUMP_LANTENCY 1

using namespace std;

enum INST_TYPE {
	INST_ADD, INST_MUL, INST_SUB, INST_DIV, INST_LD, INST_JUMP
};

enum RS_STATUS {
	RS_AVAILABLE, RS_BUSY_READY, RS_BUSY, RS_RESULT_READY
};

enum FC_STATUS {
	FC_AVAILABLE, FC_BUSY
};

#endif // DEFS_H
