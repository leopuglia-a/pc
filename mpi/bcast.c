#include <stdio.h>
#include <mpi.h>
#include <time.h>
#include <stdlib.h>

int main(){
	int id, size, x, val,min,max,i;
	
    MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
    srand(time(NULL)+id);
	x = rand()%10;
	if (id == 0){
		min = max = x;
		for(i = 1; i < size; i++){
			
            MPI_Recv(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, NULL);
            if(val > max){
				max = val;
			}else if(val < min){
				min = val;
			}
		}
	}else {
		MPI_Send(&x, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	
    MPI_Bcast(&max,1,MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&min,1,MPI_INT, 0, MPI_COMM_WORLD);

	printf("processo id:%d gerou: %d min:%d max%d\n", id, x, min, max);
	
    MPI_Finalize();
}