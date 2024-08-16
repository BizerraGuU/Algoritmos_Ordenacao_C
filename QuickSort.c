#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    

// Função que particiona o vetor em dois subvetores com base em um pivô
int particionaVetor(int *vet, int init, int fim){

    // Calcula o valor do pivô como a média dos elementos na posição inicial, final e do meio do vetor
    int piv = (vet[init] + vet[fim] + vet[(init + fim)/2]) / 3;

    // Enquanto os índices de início e fim não se cruzarem
    while(init < fim){
        // Move o índice init para a direita enquanto os valores forem menores ou iguais ao pivô
        while(init < fim && vet[init] <= piv){ 
            init++; 
        }
        // Move o índice fim para a esquerda enquanto os valores forem maiores que o pivô
        while(init < fim && vet[fim] > piv){ 
            fim--; 
        }

        // Troca os elementos nos índices init e fim
        int auxiliar = vet[init];
        vet[init] = vet[fim];
        vet[fim] = auxiliar;
    }

    // Retorna a posição onde o vetor foi particionado
    return init;
}

// Função recursiva que implementa o algoritmo Quick Sort
void quickSort(int *vet, int init, int fim){
    if(init < fim){
        // Particiona o vetor e obtém a posição do pivô
        int posicao = particionaVetor(vet, init, fim);
        // Ordena recursivamente a parte esquerda do vetor
        quickSort(vet, init, posicao-1);
        // Ordena recursivamente a parte direita do vetor
        quickSort(vet, posicao, fim);
    }
}

// Função para imprimir o vetor na tela
void imprimirVetor(int vet[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (i == tamanho - 1) {
            printf("%d", vet[i]);  // Para o último elemento, imprime sem a vírgula
        } else {
            printf("%d, ", vet[i]);  // Imprime o elemento seguido de uma vírgula
        }
    }
    printf("\n");  // Nova linha após a impressão do vetor
}

int main(){

    int escolha;   // Tamanho do vetor
    int i; 
    int *vet;   // Ponteiro para o vetor de inteiros
    int init = 0;   // Índice inicial do vetor
    clock_t inicio, fim;   // Variáveis para medir o tempo de execução
    double tempo_gasto;    // Variável para armazenar o tempo de execução

    // Exibe um menu para o usuário escolher o tamanho do vetor
    printf("-----------------------------------\n");
    printf("Escolha o tamanho do vetor ordenar\n");
    printf("-----------------------------------\n");

    // Recebe o tamanho escolhido pelo usuário
    printf("\nDigite o tamanho escolhido: ");
    scanf("%d", &escolha);

    // Aloca memória para o vetor com o tamanho escolhido
    vet = (int *)malloc(escolha * sizeof(int));  

    // Verifica se a alocação de memória foi bem-sucedida
    if (vet == NULL) {
        printf("Erro ao alocar memória.\n"); 
        return 1; // Encerra o programa em caso de erro
    }

    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Preenche o vetor com números aleatórios
    for (i = 0; i < escolha; i++) { 
        vet[i] = rand() % 100001; 
    } 

    // Exibe o vetor desordenado
    printf("-----------------------------------\n");
    printf("\nVetor desordenado: ");
    imprimirVetor(vet, escolha);

    // Mede o tempo de execução do Quick Sort
    inicio = clock();
    quickSort(vet, init, escolha-1);
    fim = clock();

    // Calcula o tempo gasto em segundos
    tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    // Exibe o vetor ordenado
    printf("\nVetor ordenado: ");
    imprimirVetor(vet, escolha);
    printf("-----------------------------------\n");

    // Exibe o tempo gasto para ordenar o vetor
    printf("Tempo gasto para ordenar o vetor: %f segundos\n", tempo_gasto);
    printf("-----------------------------------\n");

    free(vet); // Libera a memória alocada para o vetor
}
