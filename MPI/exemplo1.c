#include <stdio.h>
#include <mpi.h>

int main(int argc, char const *argv[])
{
    int id, size, i;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("\n");
    
    
    for(i = 0; i < argc-1; i++)
    {
        printf("%s", argv[i]);
    }
    
    printf("%s\"",argv[i]);
    printf(" do processo %d num total de %d processos\n",id,size);
    MPI_Finalize();

}
