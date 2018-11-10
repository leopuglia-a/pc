#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main() {
	int idw, idpi, sizew, sizepi, color;
	char frase[10];

	MPI_Init(NULL, NULL);
	MPI_Comm PAR_IMPAR;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &idw);
	
	color = idw % 2;

	MPI_Comm_split(MPI_COMM_WORLD, color, idw, &PAR_IMPAR);

	// para obter o rank de cada um comunicador
	MPI_Comm_rank(PAR_IMPAR, &idpi);

    if (idpi == 0) {
        if (color == 0) {
            strcpy(frase, "par");
        } else if (color == 1) {
            strcpy(frase, "impar");
        }
    }
    // para só os pares fazerem o broadcast, apenas fazer:
    // if(color == 0)
    MPI_Bcast(frase,10,MPI_CHAR,0,PAR_IMPAR);
    printf("idw:%d, idpi:%d, frase: %s \n", idw, idpi, frase);

    MPI_Comm_free(&PAR_IMPAR);
    MPI_Finalize();

}
