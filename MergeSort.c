#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>    

// Função que realiza a mesclagem de dois subvetores de um vetor principal
void mergeVetores(int *vet, int esquerdaArvore, int metadeArvore, int direitaArvore){
    // Calcula o tamanho dos subvetores esquerdo e direito
    int tamanho_esquerda = metadeArvore - esquerdaArvore + 1;
    int tamanho_direita = direitaArvore - metadeArvore;

    // Aloca memória para os subvetores temporários
    int *arvoreTemporariaEsquerda = (int *)malloc(tamanho_esquerda * sizeof(int));
    int *arvoreTemporariaDireita = (int *)malloc(tamanho_direita * sizeof(int));

    int i, j, x, y, z;

    // Copia os elementos do subvetor esquerdo para o vetor temporário esquerdo
    for(x = 0; x < tamanho_esquerda; x++){ 
        arvoreTemporariaEsquerda[x] = vet[esquerdaArvore + x]; 
    }
    
    // Copia os elementos do subvetor direito para o vetor temporário direito
    for(i = 0; i < tamanho_direita; i++){ 
        arvoreTemporariaDireita[i] = vet[metadeArvore + 1 + i]; 
    }

    // Inicializa os índices para percorrer os subvetores
    j = 0;  // Índice do subvetor esquerdo
    y = 0;  // Índice do subvetor direito
    z = esquerdaArvore;  // Índice do vetor principal

    // Mescla os subvetores de volta no vetor principal
    while(j < tamanho_esquerda && y < tamanho_direita){
        if (arvoreTemporariaEsquerda[j] <= arvoreTemporariaDireita[y]){
            vet[z] = arvoreTemporariaEsquerda[j];
            j++;
        } else {
            vet[z] = arvoreTemporariaDireita[y];
            y++;
        }
        z++;
    }

    // Copia os elementos restantes do subvetor esquerdo, se houver
    while (j < tamanho_esquerda) {
        vet[z] = arvoreTemporariaEsquerda[j];
        j++;
        z++;
    }

    // Copia os elementos restantes do subvetor direito, se houver
    while (y < tamanho_direita) {
        vet[z] = arvoreTemporariaDireita[y];
        y++;
        z++;
    }

    // Libera a memória alocada para os subvetores temporários
    free(arvoreTemporariaEsquerda);
    free(arvoreTemporariaDireita);
}

// Função recursiva que divide o vetor e chama a função de mesclagem
void recursaomergeSort(int *vet, int esquerdaArvore, int direitaArvore){
    if (esquerdaArvore < direitaArvore){
        // Calcula o ponto médio do vetor
        int metadeVetor = esquerdaArvore + (direitaArvore - esquerdaArvore) / 2;

        // Ordena recursivamente a primeira metade
        recursaomergeSort(vet, esquerdaArvore, metadeVetor);
        // Ordena recursivamente a segunda metade
        recursaomergeSort(vet, metadeVetor + 1, direitaArvore);

        // Mescla as duas metades ordenadas
        mergeVetores(vet, esquerdaArvore, metadeVetor, direitaArvore);
    }
}

// Função que inicia o processo de ordenação usando o Merge Sort
void mergeSort(int *vet, int tamanhoVet){ 
    recursaomergeSort(vet, 0, tamanhoVet-1); 
}

// Função para imprimir o vetor na tela
void imprimirVetor(int *vet, int tamanho) {
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
    printf("-----------------------------------\n");

    // Mede o tempo de execução do Merge Sort
    inicio = clock();
    mergeSort(vet, escolha);
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
