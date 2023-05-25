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
	FILE* ifp, * ofp;
	int num, n, k, m, i, j, l = 0;


	ifp = fopen("input.txt", "r");
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