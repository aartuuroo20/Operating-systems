#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	int fichero = open("mi_fichero", O_RDONLY, 0644);
	
	if(fichero == -1){
		perror("Error al abrir el archivo");
		exit(1);
	}
	
	int tamaño = lseek(fichero, 0, SEEK_END);
	char buffer[tamaño];
	
	int seek = lseek(fichero, 50, SEEK_SET);
	read(fichero, buffer, 20);
	
	printf("Los caracteres del 50 al 70 son: %s \n", buffer);
	

	close(fichero);
	return 0;
}
