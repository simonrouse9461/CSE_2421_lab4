/*
 * NAME:  Chuhan Feng
 * DATE:  Feb 22, 2015
 * CLASS: CSE 2421, T/TH 8:00AM
 * ID:    0x05194445
 */
 
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "testmode.h"
#define true 1
#define false 0

int main(void)
{
	int magnitude[3];
	data ***matrix = NULL;
	instruction transform;
	int status;
	int i, j, k;
	
	FILE *fin = fopen("input", "r");
	if (fin == NULL) {
		perror("Error while opening the input file.\n");
		exit(EXIT_FAILURE);
	}
	FILE *fout = fopen("output", "w");
	if (fout == NULL) {
		perror("Error while opening the output file.\n");
		exit(EXIT_FAILURE);
	}

	REPORT("Reading...\n");
	fscanf(fin, "%d %d %d\n", &magnitude[0], &magnitude[1],
		&magnitude[2]);
	construct_matrix(magnitude, &matrix, fin);

	TEST printf("%s: [data in matrix]\n", __FILE__);
	for (i = 0; i < magnitude[0]; i++) {
		for (j = 0; j < magnitude[1]; j++) {
			for (k = 0; k < magnitude[2]; k++) {
				REPORT("[%d][%d][%d] %.8f %.9f\t", i, j, k,
					matrix[i][j][k].temperature,
					matrix[i][j][k].density);
			}
			REPORT("\n");
		}
		REPORT("\n");
	}
	REPORT("Calculating...\n");
	for (i = 1; !feof(fin); i++) {
		fscanf(fin, "%d %lf %lf\n", (int*)&transform.func_code,
			&transform.arg1, &transform.arg2);
		TEST printf("Instruction #%d: %d %.8f %.9f\n", i,
			(int)transform.func_code,
			transform.arg1, transform.arg2);
		status = execute(magnitude, matrix, transform);
		SUPPRESS printf("Instruction #%d %s!\n", i,
			status ? "FAILED" : "SUCCEEDED");
	}

	REPORT("Writing...\n");
	output_matrix(magnitude, matrix, fout);

	free_matrix(magnitude, &matrix);
	fclose(fin);
	return 0;
}
