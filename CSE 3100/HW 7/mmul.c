#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *mat = p_arg;
    if ((mat -> id) == 0){
        for (int i = 0; i < (mat->m->nrows)/2; i++){
            for (int j = 0; j < mat->n->ncols; j++){
                TElement sum = (TElement)0;
                for (int k = 0; k < mat->m->ncols; k++){
                    sum += ((mat->m->data[i][k]) * (mat->n->data[k][j]));
                }
                mat->t->data[i][j] = sum;
            }
        }
    }
    if ((mat -> id) == 1){
        for (int i = ((mat->m->nrows)/2); i < mat->m->nrows; i++){
            for (int j = 0; j < mat->n->ncols; j++){
                TElement sum = (TElement)0;
                for (int k = 0; k < mat->m->ncols; k++){
                    sum += ((mat->m->data[i][k]) * (mat->n->data[k][j]));
                }
                mat->t->data[i][j] = sum;
            }
        }
    }
    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO
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
