#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>

int cmp_init(const void *a, const void *b){
    return *(int*)a - *(int*)b;
}

int main(){
    int id, size, x, *v, i;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    srand(time(NULL));

    x = rand()%100;

    v=(int *) malloc(sizeof(int)*size);

    MPI_Gather(&x, 1, MPI_INT, v, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if(id==0)
        qsort(v, size, sizeof(int), cmp_init);
    MPI_Bcast(v, size, MPI_INT, 0, MPI_COMM_WORLD);

    printf("id:%d -> ", id);

    for(i=0; i<size;i++)
        printf("%d ", v[i]);

    printf("\n");
    MPI_Finalize();
}