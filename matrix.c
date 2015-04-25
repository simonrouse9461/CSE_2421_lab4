/*
 * NAME:  Chuhan Feng
 * DATE:  Feb 22, 2015
 * CLASS: CSE 2421, T/TH 8:00AM
 * ID:    0x05194445
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "matrix.h"
#include "testmode.h"
#define true 1
#define false 0

void initialize_func_list(function_pointer** func_list) {
	*func_list = calloc(MAX_NUM_FUNC, sizeof(function_pointer));
	(*func_list)[add] = &func_add;
	(*func_list)[multiply] = &func_multiply;
	(*func_list)[square_root] = &func_square_root;
	(*func_list)[square] = &func_square;
}

int func_add(data* datum, double arg1, double arg2) {
	datum->temperature += arg1;
	datum->density += arg2;
	return 0;
}

int func_multiply(data* datum, double arg1, double arg2) {
	datum->temperature *= arg1;
	datum->density *= arg2;
	return 0;
}

int func_square_root(data* datum, double arg1, double arg2) {
	if (fabs(arg1) > EPSILON && datum->temperature < 0.0) return 1;
	if (fabs(arg2) > EPSILON && datum->density < 0.0) return 2;
	if (fabs(arg1) > EPSILON) {
		datum->temperature = sqrt(datum->temperature);
	}
	if (fabs(arg2) > EPSILON) {
		datum->density = sqrt(datum->density);
	}
	return 0;
}

int func_square(data* datum, double arg1, double arg2) {
	if (fabs(arg1) > EPSILON) {
		datum->temperature = pow(datum->temperature, 2.0);
	}
	if (fabs(arg2) > EPSILON) {
		datum->density = pow(datum->density, 2.0);
	}
	return 0;
}

void construct_matrix(int dimension[3], data**** matrix, FILE* fin) {
	int i, j, k;
	*matrix = calloc(dimension[0], sizeof(data**));
	for (i = 0; i < dimension[0]; i++) {
		(*matrix)[i] = calloc(dimension[1], sizeof(data*));
	}
	for (i = 0; i < dimension[0]; i++) {
		for (j = 0; j < dimension[1]; j++) {
		(*matrix)[i][j] = calloc(dimension[2], sizeof(data));
		}
	}
	TEST printf("%s: [original data]\n", __FILE__);
	for (i = 0; i < dimension[0]; i++) {
		for (j = 0; j < dimension[1]; j++) {
			for (k = 0; k < dimension[2]; k++) {
				fscanf(fin, "%lf %lf\n",
					&(*matrix)[i][j][k].temperature,
					&(*matrix)[i][j][k].density);
				TEST printf("%.8f %.9f\n",
					(*matrix)[i][j][k].temperature,
					(*matrix)[i][j][k].density);
			}
		}
	}
	REPORT("\n");
	return;
}

int execute(int dimension[3], data*** matrix, instruction transform) {
	function_pointer *func_list = NULL;
	initialize_func_list(&func_list);
	int stat;
	int fail_count = 0;
	int i, j, k;
	
	TEST assert(func_list[add] == &func_add);
	TEST assert(func_list[multiply] == &func_multiply);
	TEST assert(func_list[square_root] == &func_square_root);
	TEST assert(func_list[square] == &func_square);

	for (i = 0; i < dimension[0]; i++) {
		for (j = 0; j < dimension[1]; j++) {
			for (k = 0; k < dimension[2]; k++) {
				stat = (*func_list[transform.func_code])(
					&matrix[i][j][k],
					transform.arg1, transform.arg2);
				if (stat) fail_count++;
				TEST printf("%s", !stat ? "SUCC" : "FAIL");
				TEST printf("[%d][%d][%d] %.8f %.9f\t",
					i, j, k,
					matrix[i][j][k].temperature,
					matrix[i][j][k].density);
			}
			REPORT("\n");
		}
		if (i < dimension[0] - 1) {
			REPORT("\n");
		}
	}
	TEST printf("%d fail case(s)\n\n", fail_count);

	free(func_list);
	return fail_count;
}

void output_matrix(int dimension[3], data*** matrix, FILE* fout) {
	int i, j, k;
	TEST printf("%s: [output data]\n", __FILE__);
	for (i = 0; i < dimension[0]; i++) {
		for (j = 0; j < dimension[1]; j++) {
			for (k = 0; k < dimension[2]; k++) {
				fprintf(fout, "%lf %lf\n",
					matrix[i][j][k].temperature,
					matrix[i][j][k].density);
				TEST printf("%lf %lf\n",
					matrix[i][j][k].temperature,
					matrix[i][j][k].density);
			}
		}
	}
	return;
}

void free_matrix(int dimension[3], data**** matrix) {
	int i, j;
	for (i = 0; i < dimension[0]; i++) {
		for (j = 0; j < dimension[1]; j++) {
		free((*matrix)[i][j]);
		}
	}
	for (i = 0; i < dimension[0]; i++) {
		free((*matrix)[i]);
	}
	free(*matrix);
	return;
}
