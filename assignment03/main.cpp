 /*
 * Input instructions
 * add, sub, addi, sw, lw
 */

#include <stdio.h>
#include <stdlib.h>

 //CA: DO NOT CHANGE
const char* inputInstFile = "input_inst.txt";
const char* inputRegFile = "input_reg.txt";
const char* inputMemFile = "input_mem.txt";
const char* outputFileName = "hw03_output.txt";

const unsigned MAX_REG_SIZE = 32;
const unsigned MAX_MEM_SIZE = 1024;

unsigned Register[MAX_REG_SIZE] = { 0 };
unsigned Memory[MAX_MEM_SIZE] = { 0 };

void print_output_to_file(FILE* fp) {
	for (unsigned i = 0; i < MAX_REG_SIZE; i++) {
		fprintf(fp, "%08x\n", Register[i]);
	}
	for (unsigned i = 0; i < MAX_MEM_SIZE; i++) {
		fprintf(fp, "%08x\n", Memory[i]);
	}
}

int* to_binary(unsigned int inst) {
	int i = 30;
	int* binary = (int*)malloc(sizeof(int) * 32);
	unsigned int quotient = inst / 2;
	binary[31] = inst % 2;
	while (quotient != 0 && quotient != 1) {
		binary[i] = quotient % 2;
		quotient = quotient / 2;
		i--;
	}
	binary[i] = quotient;
	i--;
	for (; i >= 0; i--) {
		binary[i] = 0;
	}
	return binary;
}

void add(FILE* ifp_reg, int bi[32]) {
	int rd, rs1, rs2;
	rd = bi[20] * 16 + bi[21] * 8 + bi[22] * 4 + bi[23] * 2 + bi[24];
	rs1 = bi[12] * 16 + bi[13] * 8 + bi[14] * 4 + bi[15] * 2 + bi[16];
	rs2 = bi[7] * 16 + bi[8] * 8 + bi[9] * 4 + bi[10] * 2 + bi[11];
	if (rd == 0) {
		return;
	}
	else {
		Register[rd] = Register[rs1] + Register[rs2];
	}
}

void sub(FILE* ifp_reg, int bi[32]) {
	int rd, rs1, rs2;
	rd = bi[20] * 16 + bi[21] * 8 + bi[22] * 4 + bi[23] * 2 + bi[24];
	rs1 = bi[12] * 16 + bi[13] * 8 + bi[14] * 4 + bi[15] * 2 + bi[16];
	rs2 = bi[7] * 16 + bi[8] * 8 + bi[9] * 4 + bi[10] * 2 + bi[11];
	if (rd == 0) {
		return;
	}
	else {
		Register[rd] = Register[rs1] - Register[rs2];
	}
}

void addi(FILE* ifp_reg, int bi[32]) {
	int rd, rs1;
	int imm;
	if (bi[0] == 1) {
		imm = -4096 + bi[11] + bi[10] * 2 + bi[9] * 4 + bi[8] * 8 + bi[7] * 16 + bi[6] * 32 + bi[5] * 64 + bi[4] * 128 + bi[3] * 256 + bi[2] * 512 + bi[1] * 1024 + bi[0] * 2048;
	}
	else {
		imm = bi[11] + bi[10] * 2 + bi[9] * 4 + bi[8] * 8 + bi[7] * 16 + bi[6] * 32 + bi[5] * 64 + bi[4] * 128 + bi[3] * 256 + bi[2] * 512 + bi[1] * 1024 + bi[0] * 2048;
	}
	rd = bi[20] * 16 + bi[21] * 8 + bi[22] * 4 + bi[23] * 2 + bi[24];
	rs1 = bi[12] * 16 + bi[13] * 8 + bi[14] * 4 + bi[15] * 2 + bi[16];
	if (rd == 0) {
		return;
	}
	else {
		Register[rd] = Register[rs1] + imm;
	}
}

void sw(FILE* ifp_reg, FILE* ifp_mem, int bi[32]) {//register->mem
	int rs1, rs2;
	int imm, address;
	if (bi[0] == 1) {
		imm = -4096 + bi[24] + bi[23] * 2 + bi[22] * 4 + bi[21] * 8 + bi[20] * 16 + bi[6] * 32 + bi[5] * 64 + bi[4] * 128 + bi[3] * 256 + bi[2] * 512 + bi[1] * 1024 + bi[0] * 2048;
	}
	else {
		imm = bi[24] + bi[23] * 2 + bi[22] * 4 + bi[21] * 8 + bi[20] * 16 + bi[6] * 32 + bi[5] * 64 + bi[4] * 128 + bi[3] * 256 + bi[2] * 512 + bi[1] * 1024 + bi[0] * 2048;
	}
	rs1 = bi[12] * 16 + bi[13] * 8 + bi[14] * 4 + bi[15] * 2 + bi[16];
	rs2 = bi[7] * 16 + bi[8] * 8 + bi[9] * 4 + bi[10] * 2 + bi[11];

	address = (Register[rs1] + imm) / 4;
	Memory[address] = Register[rs2];
}

void lw(FILE* ifp_reg, FILE* ifp_mem, int bi[32]) { //mem->register
	int rd, rs1;
	int imm;
	int address;
	if (bi[0] == 1) {
		imm = -4096 + bi[11] + bi[10] * 2 + bi[9] * 4 + bi[8] * 8 + bi[7] * 16 + bi[6] * 32 + bi[5] * 64 + bi[4] * 128 + bi[3] * 256 + bi[2] * 512 + bi[1] * 1024 + bi[0] * 2048;
	}
	else {
		imm = bi[11] + bi[10] * 2 + bi[9] * 4 + bi[8] * 8 + bi[7] * 16 + bi[6] * 32 + bi[5] * 64 + bi[4] * 128 + bi[3] * 256 + bi[2] * 512 + bi[1] * 1024 + bi[0] * 2048;
	}
	rd = bi[20] * 16 + bi[21] * 8 + bi[22] * 4 + bi[23] * 2 + bi[24];
	rs1 = bi[12] * 16 + bi[13] * 8 + bi[14] * 4 + bi[15] * 2 + bi[16];
	if (rd == 0) {
		return;
	}
	else {
		address = (Register[rs1] + imm) / 4;
		Register[rd] = Memory[address];
	}
}

void decode(FILE* ifp_reg, FILE* ifp_mem, int* bi, unsigned Register[MAX_REG_SIZE], unsigned MEMORY[MAX_MEM_SIZE]) {
	if (bi[26] == 1) {
		if (bi[27] == 1) {
			if (bi[1] == 0) {
				add(ifp_reg, bi);
			}
			else {
				sub(ifp_reg, bi);
			}
		}
		else if (bi[27] == 0) {
			sw(ifp_reg, ifp_mem, bi);
		}
	}
	else {
		if (bi[27] == 1) {
			addi(ifp_reg, bi);
		}
		else {
			lw(ifp_reg, ifp_mem, bi);
			//lw
		}
	}
}

//CA: Please write your code
int main() {
	int num, i;
	int* bi = (int*)malloc(sizeof(int) * 32);

	FILE* ifp_inst = fopen(inputInstFile, "r");
	FILE* ifp_reg = fopen(inputRegFile, "r");
	FILE* ifp_mem = fopen(inputMemFile, "r");
	FILE* ofp = fopen(outputFileName, "w");


	fscanf(ifp_inst, "%d", &num);//inst size
	unsigned int* inst = (unsigned int*)malloc(sizeof(unsigned int) * num);//allocating inst
	for (i = 0; i < MAX_REG_SIZE; i++) {
		fscanf(ifp_reg, "%x\n", &Register[i]);
	}
	for (i = 0; i < MAX_MEM_SIZE; i++) {
		fscanf(ifp_mem, "%x\n", &Memory[i]);
	}
	for (i = 0; i < num; i++) {//reading inst from the file
		fscanf(ifp_inst, "%x\n", &inst[i]);
		bi = to_binary(inst[i]);
		decode(ifp_reg, ifp_mem, bi, Register, Memory); //decoding inst
	}


	print_output_to_file(ofp);
	fclose(ifp_inst);
	fclose(ifp_reg);
	fclose(ifp_mem);
	fclose(ofp);
	return true;
}