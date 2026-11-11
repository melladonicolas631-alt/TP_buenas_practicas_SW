#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos{
	char NombreEnlace[50];
	int FrecuenciaGHz, PotenciaTx; 
};

//que cosas tan lindas las estructuras para las funciones :D
void def_enl(struct datos *info);
void busqueda(struct datos *info);

int main() {
	
	struct datos enlaces;
	int opcion, i;
	do {
		printf("1. Definir Enlaces\n");
		printf("2. Busqueda por Potencia\n");
		printf("3. Salir\n");
		printf("Ingrese una opcion: ");
		scanf("%d", &opcion);
		
		if (opcion == 1) {
			def_enl(&enlaces);
		}else if (opcion == 2) {
			busqueda(&enlaces);
		}
	} while (opcion != 3);
	
	return 0;
}

void def_enl(struct datos *info) {
	int i, nro_enl;
	printf("Ingrese la cdad de enlaces:\n");
	scanf("%d", &nro_enl);
	
	for(i=0;i<nro_enl;i++){
		
		printf("Nombre del enlace %d\n", i+1);
		scanf("%s", info[i].NombreEnlace);
		
		printf("Potencia del enlace %s\n", info->NombreEnlace);
		scanf("%d", &(info[i].PotenciaTx));
		
		printf("Frecuencia del enlace %s\n", info->NombreEnlace);
		scanf("%d", &(info[i].FrecuenciaGHz));
		
	}
	
}


void busqueda(struct datos *info) {
	int nro_frec, pte_busq = 5;
	printf("Ingrese la potencia que esta buscando (el porcentaje de busqueda es del 5%): \n");
	scanf("%d", &nro_frec);
	
	if(nro_frec = info->PotenciaTx){
		printf("Nombre: %s\n", info->NombreEnlace);
		printf("Frecuencia: %d\n", info->FrecuenciaGHz);
		printf("Potencia: %d\n", info->PotenciaTx);
	}
}
