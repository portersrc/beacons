#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>


int n; // n, as in, an n x n matrix
unsigned long int mat_mults_complete = 0;
unsigned long int mat_mults_complete_overflow = 0;

unsigned long int num_stores = 0;
unsigned long int num_stores_overflow = 0;
 

void usage_and_exit(char *program_name)
{
    printf("\nUsage:\n");
    printf("\t%s mem_usage_kb 0 runtime_s\n", program_name);
    printf("  or\n");
    printf("\t%s mem_usage_kb 1 num_matrix_multiply_loops\n\n", program_name);
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
                if(num_stores == ULONG_MAX){
                    num_stores_overflow++;
                }
                num_stores++;
            }
        }
    }
    if(mat_mults_complete == ULONG_MAX){
        mat_mults_complete_overflow++;
    }
    mat_mults_complete++;
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
    /*printf("mat_mults_complete %lu\n", mat_mults_complete);
    printf("mat_mults_complete_overflow %lu \n", mat_mults_complete_overflow);
    if(mat_mults_complete_overflow > 0){
        // should never happen given what we're doing.
        printf("TODO: overflow occurred, so locking must be implemented\n");
    }*/
    printf("num_stores %lu\n", num_stores);
    if(num_stores_overflow > 0){
        printf("num_stores_overflow %lu \n", num_stores_overflow);
        printf("TODO: overflow occurred, so locking must be implemented\n");
    }
    exit(1);
}


int main(int argc, char *argv[])
{
    int i;
    int mem_usage_kb;
    int is_loopcount_based;
    int num_loops;
    int runtime_s;
    int num_elements_per_matrix;
    int **matrix_a;
    int **matrix_b;
    int **matrix_c;

    if(argc != 4){
        usage_and_exit(argv[0]);
    }


    mem_usage_kb = atoi(argv[1]);
    num_elements_per_matrix = (mem_usage_kb * 1024) / (sizeof(int) * 3);
    n = (int) sqrt(num_elements_per_matrix);

    is_loopcount_based = atoi(argv[2]);
    if(is_loopcount_based){
        num_loops = atoi(argv[3]);
    }else{
        srand(time(NULL));
        signal(SIGALRM, alarm_handler);
        runtime_s = atoi(argv[3]);
    }

    /*printf("Executing matrix multiply:\n");
    printf("\tnum columns/rows: %d\n", n);
    printf("\t~mem usage (KB): %d\n", mem_usage_kb);
    if(is_loopcount_based){
        printf("\tnum matrix multiply loops: %d\n", num_loops);
    }else{
        printf("\truntime (s): %d\n", runtime_s);
    }*/

    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    init_matrix(&matrix_c);

    if(is_loopcount_based){
        for(i = 0; i < num_loops; i++){
            mat_mult(matrix_a, matrix_b, matrix_c);
            //mat_mult(matrix_c, matrix_a, matrix_b);
            //mat_mult(matrix_b, matrix_c, matrix_a);
        }
    }else{
        alarm(runtime_s);
        while(1){
            mat_mult(matrix_a, matrix_b, matrix_c);
            //mat_mult(matrix_c, matrix_a, matrix_b);
            //mat_mult(matrix_b, matrix_c, matrix_a);
        }
    }
 
    return 0;
}
