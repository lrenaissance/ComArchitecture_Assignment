/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #02
 *
 *        Version:  1.0
 *        Created:  2022-09-15
 *       Revision:  none
 *       Compiler:  g++
 *
 * 	 Student Name: Yeoeun Kim
 * 	 Student ID: 2130008
 *   Organization:  Ewha Womans University
 *
 * =====================================================================================
 */

 /*
 * ********** Please read the instructions below carefully ********** 
 * Your name and student ID must be printed when this project is executed
 * Do not print anything other than your name and student ID (Delete printf functions used for debugging when submitting this homework)
 * - If not, there will be 20% penalty
 * Run make clean command before submitting your homework
 * Change this project folder name to studentID_yourname (EX: 1234567_myungkukyoon)
 * You must compress this project folder (not the files in this folder)
 * - If not, there will be 20% penalty
 * - Use ZIP compression utility (DO NOT USE TAR COMMAND)
 * The name of ZIP file must be studentID_yourname.zip (EX: 1234567_myungkukyoon.zip)
 * All the tests must be done in 5 seconds
 * - If not, you will get 0%
 */

 /*
 * Input instructions
 * add, sub, addi, sw, lw, beg
 */

#include <stdio.h>
#include <stdlib.h>

//CA: DO NOT CHANGE
const char *outputFileName="hw02_output.txt";

int char_to_int(char n) {
	int num;
	if (n >= 'a' && n <= 'f') {
		num = n - 87;
	}
	else
		num = n - '0';
	return num;
}

int* hex_to_bi(int n) {
	int quo = n / 2;
	int i = 1;
	int* rbi = (int*)malloc(sizeof(int) * 4);
	int* bi = (int*)malloc(sizeof(int) * 4);;
	rbi[0] = n % 2;

	for (; i < 3; i++) {
		rbi[i] = quo % 2;
		quo = quo / 2;
	}
	rbi[3] = quo;
	for (i = 0; i <= 3; i++) {
		bi[i] = rbi[3 - i];
	}
	return bi;
}

void add(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7) {
	int rd, rs1, rs2;
	rd = b6[0] * 16 + b6[1] * 8 + b6[2] * 4 + b6[3] * 2 + b7[0];
	rs1 = b4[0] * 16 + b4[1] * 8 + b4[2] * 4 + b4[3] * 2 + b5[0];
	rs2 = b2[3] * 16 + b3[0] * 8 + b3[1] * 4 + b3[2] * 2 + b3[3];
	fprintf(ofp, "add x%d,x%d,x%d\n", rd, rs1, rs2);
}

void sub(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7) {
	int rd, rs1, rs2;
	rd = b6[0] * 16 + b6[1] * 8 + b6[2] * 4 + b6[3] * 2 + b7[0];
	rs1 = b4[0] * 16 + b4[1] * 8 + b4[2] * 4 + b4[3] * 2 + b5[0];
	rs2 = b2[3] * 16 + b3[0] * 8 + b3[1] * 4 + b3[2] * 2 + b3[3];
	fprintf(ofp, "sub x%d,x%d,%d\n", rd, rs1, rs2);
}

void sw(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7) {
	int rs1, rs2;
	int imm;
	if (b1[0] == 1) {
		imm = -4096 + b7[0] + b6[3] * 2 + b6[2] * 4 + b6[1] * 8 + b6[0] * 16 + b2[2] * 32 + b2[1] * 64 + b2[0] * 128 + b1[3] * 256 + b1[2] * 512 + b1[1] * 1024 + b1[0] * 2048;
	}
	else {
		imm = b7[0] + b6[3] * 2 + b6[2] * 4 + b6[1] * 8 + b6[0] * 16 + b2[2] * 32 + b2[1] * 64 + b2[0] * 128 + b1[3] * 256 + b1[2] * 512 + b1[1] * 1024 + b1[0] * 2048;
	}
	rs1 = b4[0] * 16 + b4[1] * 8 + b4[2] * 4 + b4[3] * 2 + b5[0];
	rs2 = b2[3] * 16 + b3[0] * 8 + b3[1] * 4 + b3[2] * 2 + b3[3];
	fprintf(ofp, "sw x%d,%d(x%d)\n", rs2, imm, rs1);
}

void addi(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7) {
	int rd, rs1;
	int imm;
	if (b1[0] == 1) {
		imm = -4096 + b3[3] + b3[2] * 2 + b3[1] * 4 + b3[0] * 8 + b2[3] * 16 + b2[2] * 32 + b2[1] * 64 + b2[0] * 128 + b1[3] * 256 + b1[2] * 512 + b1[1] * 1024 + b1[0] * 2048;
	}
	else {
		imm = b3[3] + b3[2] * 2 + b3[1] * 4 + b3[0] * 8 + b2[3] * 16 + b2[2] * 32 + b2[1] * 64 + b2[0] * 128 + b1[3] * 256 + b1[2] * 512 + b1[1] * 1024 + b1[0] * 2048;
	}
	rd = b6[0] * 16 + b6[1] * 8 + b6[2] * 4 + b6[3] * 2 + b7[0];
	rs1 = b4[0] * 16 + b4[1] * 8 + b4[2] * 4 + b4[3] * 2 + b5[0];
	fprintf(ofp, "addi x%d,x%d,%d\n", rd, rs1, imm);
}

void lw(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7) {
	int rd, rs1;
	int imm;
	if (b1[0] == 1) {
		imm = -4096 + b3[3] + b3[2] * 2 + b3[1] * 4 + b3[0] * 8 + b2[3] * 16 + b2[2] * 32 + b2[1] * 64 + b2[0] * 128 + b1[3] * 256 + b1[2] * 512 + b1[1] * 1024 + b1[0] * 2048;
	}
	else {
		imm = b3[3] + b3[2] * 2 + b3[1] * 4 + b3[0] * 8 + b2[3] * 16 + b2[2] * 32 + b2[1] * 64 + b2[0] * 128 + b1[3] * 256 + b1[2] * 512 + b1[1] * 1024 + b1[0] * 2048;
	}
	rd = b6[0] * 16 + b6[1] * 8 + b6[2] * 4 + b6[3] * 2 + b7[0];
	rs1 = b4[0] * 16 + b4[1] * 8 + b4[2] * 4 + b4[3] * 2 + b5[0];
	fprintf(ofp, "lw x%d,%d(x%d)\n", rd, imm, rs1);
}

void beq(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7) {
	int rs1, rs2;
	int imm;
	if (b1[0] == 1) {
		imm = -4096 + b6[3] + b6[2] * 2 + b6[1] * 4 + b6[0] * 8 + b2[2] * 16 + b2[1] * 32 + b2[0] * 64 + b1[3] * 128 + b1[2] * 256 + b1[1] * 512 + b7[0] * 1024 + b1[0] * 2048;
	}
	else {
		imm = b6[3] + b6[2] * 2 + b6[1] * 4 + b6[0] * 8 + b2[2] * 16 + b2[1] * 32 + b2[0] * 64 + b1[3] * 128 + b1[2] * 256 + b1[1] * 512 + b7[0] * 1024 + b1[0] * 2048;
	}
	rs1 = b4[0] * 16 + b4[1] * 8 + b4[2] * 4 + b4[3] * 2 + b5[0];
	rs2 = b2[3] * 16 + b3[0] * 8 + b3[1] * 4 + b3[2] * 2 + b3[3];
	fprintf(ofp, "beq x%d,x%d,%d\n", rs1, rs2, 2*imm);
}

void check_type(FILE* ofp, int* b1, int* b2, int* b3, int* b4, int* b5, int* b6, int* b7, int* b8) {
	if (b7[1] == 1) {
		beq(ofp, b1, b2, b3, b4, b5, b6, b7);
	}
	else if (b7[2] == 1) {
		if (b7[3] == 1) {
			if (b1[1] == 0) {
				add(ofp, b1, b2, b3, b4, b5, b6, b7);
			}
			else {
				sub(ofp, b1, b2, b3, b4, b5, b6, b7);
			}
		}
		else if (b7[3] == 0) {
			sw(ofp, b1, b2, b3, b4, b5, b6, b7);
		}
	}
	else {
		if (b7[3] == 1) {
			addi(ofp, b1, b2, b3, b4, b5, b6, b7);
			//addi
		}
		else {
			lw(ofp, b1, b2, b3, b4, b5, b6, b7);
			//lw
		}
	}
}

//CA: Please write your code
int main(){
	int num;
	char c1, c2, c3, c4, c5, c6, c7, c8;
	int n1, n2, n3, n4, n5, n6, n7, n8;
	int* b1, * b2, * b3, * b4, * b5, * b6, * b7, * b8;

	//CA: YOUR NAME with Student ID
	printf("Kim, Yeoeun (2130008)\n"); 
	FILE* ifp, * ofp;
	ifp= fopen("input.txt", "r");
	ofp = fopen(outputFileName, "w");

	fscanf(ifp, "%d\n", &num);

	for (; num > 0; num--) {
		fscanf(ifp, "0x%c%c%c%c%c%c%c%c\n", &c1, &c2, &c3, &c4, &c5, &c6, &c7, &c8);
		n1 = char_to_int(c1);
		n2 = char_to_int(c2);
		n3 = char_to_int(c3);
		n4 = char_to_int(c4);
		n5 = char_to_int(c5);
		n6 = char_to_int(c6);
		n7 = char_to_int(c7);
		n8 = char_to_int(c8);
		b1 = hex_to_bi(n1);
		b2 = hex_to_bi(n2);
		b3 = hex_to_bi(n3);
		b4 = hex_to_bi(n4);
		b5 = hex_to_bi(n5);
		b6 = hex_to_bi(n6);
		b7 = hex_to_bi(n7);
		b8 = hex_to_bi(n8);
		check_type(ofp, b1, b2, b3, b4, b5, b6, b7, b8);
	}

	fclose(ifp);
	fclose(ofp);

	return 0;
}
