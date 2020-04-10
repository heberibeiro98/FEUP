#include <stdio.h>

#define DEBUG 0

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    long *cnt;	/* pointer to shared counter */
    int n;		/* no of times to increment */
    int id;		/* application-specific thread-id */
} targ_t;

void *sfun(void *arg) {

    targ_t *targ = (targ_t *) arg;
    int i;

    printf("Thread %d starting\n", targ->id);

    printf ("&cnt = %p \n", targ->cnt);

    for(i = 0; i < targ->n ; i++) {
		if( DEBUG )
		    printf("b4:  %ld ", *(targ->cnt));
	  pthread_mutex_lock(&mutex);
		(*(targ->cnt))++;
		/* If cnt is always N*MAX_ITER
		   Then comment the previous line and
		   uncomment the following 3 lines
		   aux = *(targ->cnt);
		   aux++;
		   *(targ->cnt) = aux;
		   */
       pthread_mutex_unlock(&mutex);
		if (DEBUG )
		    printf("\t %ld \n", *(targ->cnt));
    }
    printf("Thread %d done\n", targ->id);
    return NULL;
}
