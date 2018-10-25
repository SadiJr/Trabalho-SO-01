#include <stdio.h>
#include <pthread.h>
#include "Fila.c"
#include <unistd.h> 
tipo_elementoFila *fila[3];
int contadorGuiche = 0;

/**
 * Thread que faz a chamada dos elementos da fila 0, aplica aging e reinfileira as outras filas
 */
void * thread_guiche(void *arg){
   int TMA = rand() % 20;
   while(fila[0] != NULL){
   		if (contadorGuiche % 3 == 0){ //aplica AGING
			if (qtdElementos(fila[1]) > 0){
				fila[0] = enfileirar(fila[0], fila[1]->prioridade, fila[1]->contador); //enfileira na fila 0 o primeiro elemento da fila 1
				fila[1] = proximo(fila[1]); 
				if (qtdElementos(fila[2]) > 0){
		   			fila[0] = enfileirar(fila[1], fila[2]->prioridade, fila[2]->contador); //enfileira na fila 1 o primeiro elemento da fila 2
		   			fila[2] = proximo(fila[2]);
				}
	 		}else{ //se não tem ninguem na fila 1
	   	 		if (qtdElementos(fila[2]) > 0){
				fila[0] = enfileirar(fila[0], fila[2]->prioridade, fila[2]->contador); //enfileira na fila 0 o primeiro elemento da fila 2
				fila[2] = proximo(fila[2]);
	    		}
	 		}
      	}
      	sleep(TMA);
      	printf("tID %li atendendo %iP%i\n\n", pthread_self(), fila[0]->prioridade+1, fila[0]->contador);
      	fila[0] = proximo(fila[0]);
      	contadorGuiche++;
      	exibir(fila[0]);
   }
   pthread_exit(NULL);
}

void * thread_organizadorFila(void *arg){
	int contador[3];
	contador[0] = 0;
	contador[1] = 0;
	contador[2] = 0;
	srand(time(NULL));
	while(1){
		int numFila = (rand() % 3);
		contador[numFila]++;
		fila[numFila] = enfileirar(fila[numFila], numFila, contador[numFila]);
		sleep(rand() % 3);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
   fila[0]=criarFila(fila[0]);
   fila[1]=criarFila(fila[1]);
   fila[2]=criarFila(fila[2]);
   
   pthread_t threadOrganizador;
   pthread_create(&threadOrganizador, NULL, thread_organizadorFila, NULL);
   int qtdGuiches = atoi(argv[1]);	
   printf("%i guiches informados\n", qtdGuiches);
   pthread_t threads[qtdGuiches];
   for (int j = 0; j < qtdGuiches; j++){
	  int rstatus;
	  rstatus = pthread_create(&(threads[j]), NULL, thread_guiche , NULL);
	  if (rstatus != 0){ printf("ERRO AO CRIAR THREAD"); }
   }

   for (int j = 0; j < qtdGuiches; j++){
	pthread_join(threads[j], NULL);
   }
   return 0;
}
