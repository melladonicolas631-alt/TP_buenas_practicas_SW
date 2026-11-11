#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos {
	char NombreEnlace[50];
	float FrecuenciaGHz; 
	float PotenciaTx; 
};

// Declaración de funciones con punteros para modificar la memoria y el contador
void def_enl(struct datos **info, int *total_enlaces);

int main() {
	struct datos *enlaces = NULL; // Puntero nulo inicial para memoria dinámica
	int total_enlaces = 0;
	int opcion;
	
	do {
		printf("\n--- GESTOR DE ENLACES DE TELECOMUNICACIONES ---\n");
		printf("1. Ingresar nuevos enlaces\n");
		printf("2. Salir\n");
		printf("Ingrese una opcion: ");
		if (scanf("%d", &opcion) != 1) return 1;
		
		if (opcion == 1) {
			def_enl(&enlaces, &total_enlaces);
		}
	} while (opcion != 2);
	
	free(enlaces); // Buena práctica: liberar la memoria al finalizar
	return 0;
}

void def_enl(struct datos **info, int *total_enlaces) {
	int nuevos_enlaces, i;
	printf("Ingrese la cantidad de enlaces nuevos a registrar: ");
	scanf("%d", &nuevos_enlaces);
	
	// Redimensionar el bloque de memoria para acomodar los nuevos enlaces
	*info = (struct datos *)realloc(*info, (*total_enlaces + nuevos_enlaces) * sizeof(struct datos));
	
	if (*info == NULL) {
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	
	for(i = *total_enlaces; i < (*total_enlaces + nuevos_enlaces); i++) {
		printf("\n--- Datos del enlace %d ---\n", i + 1);
		printf("Nombre del enlace: ");
		scanf("%s", (*info)[i].NombreEnlace);
		
		printf("Potencia del enlace %s (W/dBm): ", (*info)[i].NombreEnlace);
		scanf("%f", &((*info)[i].PotenciaTx));
		
		printf("Frecuencia del enlace %s (GHz): ", (*info)[i].NombreEnlace);
		scanf("%f", &((*info)[i].FrecuenciaGHz));
	}
	
	*total_enlaces += nuevos_enlaces;
}
