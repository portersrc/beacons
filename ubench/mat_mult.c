#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>


int n; // n, as in, an n x n matrix
 

void usage_and_exit(char *program_name)
{
    printf("\nUsage: %s mem_usage_kb runtime_s\n\n", program_name);
    exit(1);
}


void mat_mult(int **m1, int **m2, int **m3)
{
    int i, j, k;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            m3[i][j] = 0;
            for(k = 0; k < n; k++){
                m3[i][j] += m1[i][k]*m2[k][j];
            }
        }
    }
}


void init_matrix(int ***m)
{
    int i;
    int j;

    *m = malloc(sizeof(int *) * n);
    for(i = 0; i < n; i++){
        (*m)[i] = malloc(sizeof(int) * n);
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            (*m)[i][j] = rand();
        }
    }
}


void alarm_handler(int sig)
{
    printf("Time expired. Exiting.\n");
    exit(1);
}


int main(int argc, char *argv[])
{
    int mem_usage_kb;
    int runtime_s;
    int num_elements_per_matrix;
    int **matrix_a;
    int **matrix_b;
    int **matrix_c;

    if(argc != 3){
        usage_and_exit(argv[0]);
    }

    srand(time(NULL));
    signal(SIGALRM, alarm_handler);

    mem_usage_kb = atoi(argv[1]);
    runtime_s   = atoi(argv[2]);
    num_elements_per_matrix = (mem_usage_kb * 1024) / (sizeof(int) * 3);
    n = (int) sqrt(num_elements_per_matrix);

    printf("Executing matrix multiply:\n");
    printf("\tnum columns/rows: %d\n", n);
    printf("\t~mem usage (KB):  %d\n", mem_usage_kb);
    printf("\truntime (s):      %d\n", runtime_s);

    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    init_matrix(&matrix_c);

    alarm(runtime_s);

    while(1){
        mat_mult(matrix_a, matrix_b, matrix_c);
        mat_mult(matrix_c, matrix_a, matrix_b);
        mat_mult(matrix_b, matrix_c, matrix_a);
    }
 
    return 0;
}
