#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int id, *v, i, x, n;
    
    MPI_Datatype T_Cont;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);

    n = atoi(argv[1]);

    v = (int*) malloc(n*sizeof(int));
    MPI_Type_contiguous(n, MPI_INT, &T_Cont);
    MPI_Type_commit(&T_Cont);

    srand(time(NULL));
    if (id == 0) {
        
        for(i = 0; i < n; i++)
        {
            v[i]=rand()%1000;
            printf("%d ", v[i]);
        }
        printf("\n");
        MPI_Send(v, 1, T_Cont, 1, MPI_ANY_TAG, MPI_COMM_WORLD);

        // depois de enviar, vai esperar receber o comunicador de volta;
        MPI_Recv(v, 1, T_Cont,1, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        
        for(i = 0; i < n; i++)
        {
            printf("%d ", v[i]);
        }
        printf("\n");

    } else if (id == 1) {
        MPI_Recv(v, 1, T_Cont, 0, MPI_ANY_TAG, MPI_COMM_WORLD, NULL);
        x = rand()%10;
        printf("somando %d\n", x);
        
        for( i = 0; i < n; i++)
        {
            v[i] += x;
        }

        MPI_Send(v, 1, T_Cont, 0, MPI_ANY_TAG, MPI_COMM_WORLD);   
    }

    MPI_Type_free(&T_Cont);
    MPI_Finalize();
    free(v);
}
