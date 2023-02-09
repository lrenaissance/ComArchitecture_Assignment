/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Homework #01
 *
 *        Version:  1.0
 *        Created:  2022-07-23
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

#include <stdio.h>
#include<stdlib.h>

//CA: DO NOT CHANGE
const int MAX = 100;
const char* outputFileName = "hw01_output.txt";

//CA: DO NOT CHANGE
int matrixOutput[MAX][MAX] = { 0 };

//CA: DO NOT CHANGE
void print_output_to_file(FILE* fp, int ROW, int COL) {
	for (int y = 0; y < ROW; y++) {
		for (int x = 0; x < COL; x++) {
			fprintf(fp, "%d ", matrixOutput[y][x]);
		}
		fprintf(fp, "\n");
	}
}

//CA: Please write your code
int main() {
	//CA: YOUR NAME with Student ID
	FILE* ifp, * ofp;
	int num, n, k, m, i, j, l = 0;


	ifp = fopen("input.txt", "r");
	printf("Kim, Yeoeun (2130008)\n");
	ofp = fopen(outputFileName, "w");
	fscanf(ifp, "%d\n", &num);
	for (; num>0; num--) {
		fscanf(ifp, "%d %d %d\n", &n, &k, &m);

		int** mA = (int**)malloc(sizeof(int*) * n);
		int** mB = (int**)malloc(sizeof(int*) * k);
		for (i = 0; i < n; i++) {
			mA[i] = (int*)malloc(sizeof(int) * n);
			*(mA + i) = (int*)malloc(sizeof(int) * k);
		}
		for (i = 0; i < k; i++) {
			mB[i] = (int*)malloc(sizeof(int) * k);
			*(mB + i) = (int*)malloc(sizeof(int) * m);
		}
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < k; j++)
			{
				fscanf(ifp, "%d ", *(mA + i) + j);
				
			}
			
		}
		for (i = 0; i < k; i++)
		{
			for (j = 0; j < m; j++)
			{
				fscanf(ifp, "%d ", *(mB + i) + j);
			}
		}
		for (i=0; i < n; i++) {
			for (l=0; l < m; l++) {
				for (j=0; j < k; j++) {
					matrixOutput[i][l] += (*(*(mA + i) + j)) * (*(*(mB + j) + l));
				}
				
			}
			
		}
		print_output_to_file(ofp, n, m);
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				matrixOutput[i][j] = { 0 };
			}
		}
	}
	fclose(ifp);
	fclose(ofp);


	return 0;
}