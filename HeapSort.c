#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>   

// Função para trocar dois elementos de lugar
void trocaElementos(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para manter a propriedade do heap
void criaHeap(int *vet, int numero, int cont) {
    int maiorNumero = cont;         // Inicializa o maior como raiz
    int esquerda = 2 * cont + 1;    // Índice do filho esquerdo
    int direita = 2 * cont + 2;     // Índice do filho direito

    // Se o filho esquerdo é maior que a raiz
    if (esquerda < numero && vet[esquerda] > vet[maiorNumero]) {
        maiorNumero = esquerda;
    }

    // Se o filho direito é maior que o maior até agora
    if (direita < numero && vet[direita] > vet[maiorNumero]) {
        maiorNumero = direita;
    }

    // Se o maior não é a raiz
    if (maiorNumero != cont) {
        trocaElementos(&vet[cont], &vet[maiorNumero]);  // Troca a raiz com o maior filho

        // Recursivamente, aplica criaHeap na subárvore afetada
        criaHeap(vet, numero, maiorNumero);
    }
}

// Função para construir o heap a partir de um array desordenado
void constroiHeap(int *vet, int numero) {
    // Índice do último nó não-folha no array
    int naoFolha = (numero / 2) - 1;

    // Realiza criaHeap em todos os nós não-folha para construir o heap
    for (int cont = naoFolha; cont >= 0; cont--) {
        criaHeap(vet, numero, cont);
    }
}

// Função para ordenar o array usando o algoritmo Heap Sort
void heapSort(int *vet, int numero) {
    // Constrói o heap a partir do array
    constroiHeap(vet, numero);

    // Extrai os elementos do heap um por um, do maior para o menor
    for (int cont = numero - 1; cont > 0; cont--) {
        // Move a raiz (o maior elemento) para o final do array
        trocaElementos(&vet[0], &vet[cont]);

        // Chama criaHeap na heap reduzida para restaurar a propriedade do heap
        criaHeap(vet, cont, 0);
    }
}

// Função para imprimir o array
void imprimirVetor(int *vet, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (i == tamanho - 1) {
            printf("%d", vet[i]);  // Imprime o último elemento sem a vírgula
        } else {
            printf("%d, ", vet[i]);  // Imprime o elemento seguido de uma vírgula
        }
    }
    printf("\n");  // Nova linha após a impressão do vetor
}

int main(){

    int escolha;  // Variável para armazenar o tamanho do array
    int i; 
    int *vet;     // Ponteiro para o array de inteiros
    clock_t inicio, fim;   // Variáveis para armazenar o tempo de início e fim da execução
    double tempo_gasto;    // Variável para armazenar o tempo gasto

    // Exibe um menu para o usuário escolher o tamanho do array
    printf("-----------------------------------\n");
    printf("Escolha o tamanho do vetor ordenar\n");
    printf("-----------------------------------\n");

    // Recebe o tamanho escolhido pelo usuário
    printf("\nDigite o tamanho escolhido: ");
    scanf("%d", &escolha);

    // Aloca memória para o array com o tamanho escolhido
    vet = (int *)malloc(escolha * sizeof(int));  

    // Verifica se a alocação de memória foi bem-sucedida
    if (vet == NULL) { 
        printf("Erro ao alocar memória.\n"); 
        return 1;  // Encerra o programa em caso de erro
    } 

    srand(time(NULL));  // Inicializa o gerador de números aleatórios

    // Preenche o array com números aleatórios
    for (i = 0; i < escolha; i++) { 
        vet[i] = rand() % 100001; 
    } 

    // Exibe o array desordenado
    printf("-----------------------------------\n");
    printf("\nVetor desordenado: ");
    imprimirVetor(vet, escolha);
    printf("-----------------------------------\n");

    // Marca o início da execução do Heap Sort
    inicio = clock();

    // Ordena o array usando Heap Sort
    heapSort(vet, escolha);

    // Marca o fim da execução do Heap Sort
    fim = clock();

    // Calcula o tempo gasto em segundos
    tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;

    // Exibe o array ordenado
    printf("\nVetor ordenado: ");
    imprimirVetor(vet, escolha);
    printf("-----------------------------------\n");

    // Exibe o tempo gasto na ordenação
    printf("Tempo gasto no Heap Sort: %f segundos\n", tempo_gasto);
    
    free(vet);  // Libera a memória alocada para o array
}
