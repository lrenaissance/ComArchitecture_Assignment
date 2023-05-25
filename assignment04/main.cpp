#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

 //CA: DO NOT CHANGE
const char* outputFileName = "hw04_output.txt";

unsigned long long cacheHit;
unsigned long long cacheMiss;

int log2(int x) {
	return log(x) / log(2);
}

void init() {
	cacheHit = 0;
	cacheMiss = 0;
}

void check(int* cache, int blocks, int blocksize, int add) {
	int address = add / blocksize;
	int index = address % blocks;
	int tag = address >> log2(blocks);

	if (cache[index] != -1) {//not empty
		if (cache[index] == tag) {
			cacheHit++;
		}
		else {
			cache[index] = tag;
			cacheMiss++;
		}
	}
	else {//empty
		cache[index] = tag;
		cacheMiss++;
	}
}

void ratio(FILE* fp) {
	unsigned long long total = cacheHit + cacheMiss;
	fprintf(fp, "Hit: %3.2f\n", (float)cacheHit / total * 100);
	fprintf(fp, "Miss: %3.2f\n", (float)cacheMiss / total * 100);
}

//CA: Please write your code
int main() {
	init();
	FILE* ifp = fopen("input.txt", "r");
	FILE* ofp = fopen(outputFileName, "w");

	int testcase, blocks, blocksize,numadd;

	fscanf(ifp, "%d\n", &testcase);
	for (; testcase > 0; testcase--) {
		init();
		fscanf(ifp, "%d\n", &blocks);
		fscanf(ifp, "%d\n", &blocksize);
		fscanf(ifp, "%d\n", &numadd);
		int* address = (int*)malloc(sizeof(int) * numadd);
		int* cache = (int*)malloc(sizeof(int) * blocks);
		memset(cache, -1, sizeof(int) * blocks);

		for (int i = 0; i < numadd; i++) {
			fscanf(ifp, "%x\n", &address[i]);
			check(cache, blocks, blocksize, address[i]);
		}
		ratio(ofp);
	}
	fclose(ifp);
	fclose(ofp);
	return 1;
}