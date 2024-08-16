#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void trocaElementos(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade do heap
void criaHeap(int *vet, int numero, int cont) {
    int maiorNumero = cont; // Inicializa o maior como raiz
    int esquerda = 2 * cont + 1; // filho esquerdo
    int direita = 2 * cont + 2; // filho direito

    // Se o filho esquerdo é maior que a raiz
    if (esquerda < numero && vet[esquerda] > vet[maiorNumero]) {maiorNumero = esquerda;}

    // Se o filho direito é maior que o maior até agora
    if (direita < numero && vet[direita] > vet[maiorNumero]) {maiorNumero = direita;}

    // Se o maior não é a raiz
    if (maiorNumero != cont) {
        trocaElementos(&vet[cont], &vet[maiorNumero]);

        // Recursivamente, a subárvore afetada
        criaHeap(vet, numero, maiorNumero);
    }
}

// Função para construir o heap
void constroiHeap(int *vet, int numero) {
    // Índice do último nó não-folha
    int naoFolha = (numero / 2) - 1;

    // Realiza criaHeap em todos os nós não-folha
    for (int cont = naoFolha; cont >= 0; cont--) {
        criaHeap(vet, numero, cont);
    }
}

void heapSort(int *vet, int numero) {
    // Constrói o heap (rearranja o array)
    constroiHeap(vet, numero);

    // Extrai elementos do heap um por um
    for (int cont = numero - 1; cont > 0; cont--) {
        // Move a raiz atual para o final
        trocaElementos(&vet[0], &vet[cont]);

        // Chama criaHeap na heap reduzida
        criaHeap(vet, cont, 0);
    }
}

void imprimirVetor(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (i == tamanho - 1) {
            printf("%d", vet[i]);
        } else {
            printf("%d, ", vet[i]);
        }
    }
    printf("\n");
}

int main(){

    int escolha;
    int i; 
    int *vet;

    printf("-----------------------------------\n");
    printf("Escolha o tamanho do vetor ordenar\n");
    printf("-----------------------------------\n");

    printf("\nDigite o tamanho escolhido: ");
    scanf("%d", &escolha);

    vet = (int *)malloc(escolha * sizeof(int));  // realiza a alocação de memoria

    if (vet == NULL) { printf("Erro ao alocar memória.\n"); } 
    // caso seja digitado algo fora do esperado. 
    //verifica se o vetor esta vazio ou é inexistente 

    srand(time(NULL)); //inicia o gerador de numeros

    for (i = 0; i < escolha; i++) { vet[i] = rand() % 100001; } 
    // realiza a inserção aleatoria dos numeros no vetor com base no tamanho escolhido pelo user

    printf("-----------------------------------\n");
    printf("\nVetor desordenado: ");
    imprimirVetor(vet, escolha);
    printf("-----------------------------------\n");
    heapSort(vet, escolha);
    printf("\nVetor ordenado: ");
    imprimirVetor(vet, escolha);
    printf("-----------------------------------\n");
    
    free(vet); //libera a memoria alocada no vetor
}
