#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

int primo (int x) {
	if (x ==1 ) 
	{
		return 0;
	}

	for (int i = 0; i <= x/2; ++i)
	{
		if (x%i==0)
		{
			return 0;
		}
	}
	return 1;
}


int main() {
	int *v, id, size, *vp, x, p;

	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	v=(int*)malloc(size*sizeof(int));
	vp=(int*)malloc(size*sizeof(int));

	if (id == 0)
	{
		srand(time(NULL));
		for (int i = 0; i < size; ++i)
		{
			v[i]=rand()%1000;
		}
	}
	MPI_Scatter(v,1,MPI_INT, &x, 1, MPI_INT, 0, MPI_COMM_WORLD);
	p=primo(x);
	MPI_Gather(&p, 1, MPI_INT, vp, 1, MPI_INT, 0, MPI_COMM_WORLD);
	if (id == 0)
	{
		for (int i = 0; i < size; ++i)
		{
			printf("%d", v[i]);
			if (vp[i])
			{
				printf("é primo\n");
			} else {
				printf("não é primo\n");
			}
		}
	}

	MPI_Finalize();

}