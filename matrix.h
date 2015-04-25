/*
 * NAME:  Chuhan Feng
 * DATE:  Feb 22, 2015
 * CLASS: CSE 2421, T/TH 8:00AM
 * ID:    0x05194445
 */

#define MAX_NUM_FUNC 10
#define EPSILON 0.0001

typedef struct data {
	double temperature;
	double density;
} data;

typedef enum operation {
	add = 0,
	multiply = 1,
	square_root = 2,
	square = 3,
} operation;

typedef struct instruction {
	operation func_code;
	double arg1;
	double arg2;
} instruction;

typedef int (*function_pointer)(data*, double arg1, double arg2);

void initialize_func_list(function_pointer**);

int func_add(data*, double, double);

int func_multiply(data*, double, double);

int func_square_root(data*, double, double);

int func_square(data*, double, double);

void construct_matrix(int[3], data****, FILE*);

int execute(int[3], data***, instruction);

void output_matrix(int[3], data***, FILE*);

void free_matrix(int[3], data****);
