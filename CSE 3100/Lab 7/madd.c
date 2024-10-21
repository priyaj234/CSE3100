#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{

    // TODO
    thread_arg_t *mat = p_arg;
    if (mat->id == 0){
        for (unsigned int i = 0; i < (mat->m->nrows)/2; i++)
            for (unsigned int j = 0; j < mat->n->ncols; j++)
                mat->t->data[i][j] = mat->m->data[i][j] + mat->n->data[i][j];
    }
    if (mat->id == 1){
        for (unsigned int i = (mat->m->nrows)/2 ; i < mat->m->nrows; i++)
            for (unsigned int j = 0; j < mat->n->ncols; j++)
                mat->t->data[i][j] = mat->m->data[i][j] + mat->n->data[i][j];
    }

    pthread_exit(NULL);
    return NULL;
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;
    pthread_t thread[NUM_THREADS];
    thread_arg_t threaddata[NUM_THREADS];
    int num;
    for(int i = 0; i < NUM_THREADS; i++){
        threaddata[i].id = i;
        threaddata[i].m = m;
        threaddata[i].n = n;
        threaddata[i].t = t;
        num = pthread_create(&thread[i], NULL, thread_main, &threaddata[i]);
        if(num){
            printf("ERROR");
            exit(-1);
        }
    }
    for(int i = 0; i < NUM_THREADS; i++){
        num = pthread_join(thread[i], NULL);
        if (num){
            printf("ERROR");
            exit(-1);
        }
    }
    return t;
}
