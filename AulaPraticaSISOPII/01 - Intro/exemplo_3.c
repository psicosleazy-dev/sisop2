#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *test_routine (void *arg) {
    double *value;
    int soma = 0;
    value = (double*)malloc(sizeof(double));
    *value = 0;
    for(int i=0;i<=100;i++){
	printf("\nhello : %d!", i);
        *value+=i;
    }
    return value;
}

int main( int argc, char **argv) {
    pthread_t thr;
    double *res;
    int status;

    status = pthread_create(&thr, NULL, test_routine, NULL);
    if (status != 0)
        exit(1);

    status = pthread_join (thr, (void *) &res);
    if (status != 0)
        exit(1);

    printf("\nresultado retornado: %.2f\n", *res);
    free(res);
}
