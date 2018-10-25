#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
//pthread
void simulacao(tipo_elementoFila *fila1, tipo_elementoFila *fila2, tipo_elementoFila *fila3){
	int contador = 0;
	int contadorFila[3];
	contadorFila[0] = 0;
	contadorFila[1] = 0;
	contadorFila[3] = 0;
	for (contador = 0; contador <= 100; contador++){
		int numFila = (rand() % 3);
		contadorFila[numFila]++;
		switch (numFila){
			case 0:
				enfileirar(fila1, numFila, contadorFila[numFila]);
				break;
			case 1:
				enfileirar(fila2, numFila, contadorFila[numFila]);
				break;
			case 2:
				enfileirar(fila3, numFila, contadorFila[numFila]);
				break;
		}
	}
}
