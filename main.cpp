#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct datos {
	char NombreEnlace[50];
	float FrecuenciaGHz; 
	float PotenciaTx; 
};

void def_enl(struct datos **info, int *total_enlaces);
void busqueda(struct datos *info, int total_enlaces);

int main() {
	struct datos *enlaces = NULL; 
	int total_enlaces = 0;
	int opcion;
	
	do {
		printf("\n--- GESTOR DE ENLACES DE TELECOMUNICACIONES ---\n");
		printf("1. Ingresar nuevos enlaces\n");
		printf("2. Busqueda por Potencia (Margen porcentual)\n");
		printf("3. Salir\n");
		printf("Ingrese una opcion: ");
		if (scanf("%d", &opcion) != 1) return 1;
		
		if (opcion == 1) {
			def_enl(&enlaces, &total_enlaces);
		} else if (opcion == 2) {
			busqueda(enlaces, total_enlaces);
		}
	} while (opcion != 3);
	
	free(enlaces); 
	return 0;
}

void def_enl(struct datos **info, int *total_enlaces) {
	int nuevos_enlaces, i;
	printf("Ingrese la cantidad de enlaces nuevos a registrar: ");
	scanf("%d", &nuevos_enlaces);
	
	*info = (struct datos *)realloc(*info, (*total_enlaces + nuevos_enlaces) * sizeof(struct datos));
	
	if (*info == NULL) {
		printf("Error: No se pudo asignar memoria.\n");
		exit(1);
	}
	
	for(i = *total_enlaces; i < (*total_enlaces + nuevos_enlaces); i++) {
		char nombre_temp[40];
		
		printf("\n--- Datos del enlace %d ---\n", i + 1);
		printf("Nombre del enlace: ");
		scanf("%s", nombre_temp);
		
		// Operación de cadenas requerida en el parcial
		strcpy((*info)[i].NombreEnlace, "NET-");
		strcat((*info)[i].NombreEnlace, nombre_temp);
		
		printf("Potencia del enlace %s (W/dBm): ", (*info)[i].NombreEnlace);
		scanf("%f", &((*info)[i].PotenciaTx));
		
		printf("Frecuencia del enlace %s (GHz): ", (*info)[i].NombreEnlace);
		scanf("%f", &((*info)[i].FrecuenciaGHz));
	}
	
	*total_enlaces += nuevos_enlaces;
}

void busqueda(struct datos *info, int total_enlaces) {
	if (total_enlaces == 0) {
		printf("No hay enlaces registrados en el sistema.\n");
		return;
	}
	
	float pot_buscada, porcentaje;
	int encontrados = 0;
	
	printf("Ingrese la potencia objetivo a buscar: ");
	scanf("%f", &pot_buscada);
	printf("Ingrese el margen de tolerancia en porcentaje (ej. 5 para 5%%): ");
	scanf("%f", &porcentaje);
	
	float margen = pot_buscada * (porcentaje / 100.0);
	float limite_inf = pot_buscada - margen;
	float limite_sup = pot_buscada + margen;
	
	printf("\n--- Resultados de la busqueda (%.2f a %.2f) ---\n", limite_inf, limite_sup);
	
	for (int i = 0; i < total_enlaces; i++) {
		if (info[i].PotenciaTx >= limite_inf && info[i].PotenciaTx <= limite_sup) {
			printf("- Enlace: %s | Freq: %.2f GHz | Potencia: %.2f\n", 
				   info[i].NombreEnlace, info[i].FrecuenciaGHz, info[i].PotenciaTx);
			encontrados++;
		}
	}
	
	if (encontrados == 0) {
		printf("Ningun enlace coincide con los criterios de busqueda.\n");
	}
}
