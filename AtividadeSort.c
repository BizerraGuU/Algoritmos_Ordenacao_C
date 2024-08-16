#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>   

// Função que realiza a partição do vetor para o QuickSort
int particionaVetor(int *vet, int init, int fim){
    int piv = (vet[init] + vet[fim] + vet[(init + fim)/2]) / 3;
    /* essa primeira linha determina o pivo a partir da soma do primeiro 
    elemento do vetor e do ultimo elemento e da divisão por dois da soma 
    entre eles, e por fim divide por 3*/

    while(init < fim){
        while(init < fim && vet[init] <= piv){ init++; }  
        /* verifica se o início é menor que o fim e se o pivo é maior 
        que o valor na posição inicial do vetor, e incrementa init em caso positivo */

        while(init < fim && vet[fim] > piv){ fim--; }
        /* faz o processo inverso da anterior e decrementa fim em caso positivo */

        int auxiliar = vet[init];
        vet[init] = vet[fim];
        vet[fim] = auxiliar;
        /* realiza a troca de posição dos valores dentro do vetor */
    }

    return init; // Retorna a posição de partição para continuar o processo
}

// Função de ordenação QuickSort
void quickSort(int *vet, int init, int fim){
    if(init < fim){
        int posicao = particionaVetor(vet, init, fim); // Obtém a posição de partição
        quickSort(vet, init, posicao-1); // Ordena os números menores à esquerda
        quickSort(vet, posicao, fim); // Ordena os números maiores à direita
    }
}

// Função para trocar dois elementos de lugar
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
    if (esquerda < numero && vet[esquerda] > vet[maiorNumero]) { maiorNumero = esquerda; }

    // Se o filho direito é maior que o maior até agora
    if (direita < numero && vet[direita] > vet[maiorNumero]) { maiorNumero = direita; }

    // Se o maior não é a raiz
    if (maiorNumero != cont) {
        trocaElementos(&vet[cont], &vet[maiorNumero]);
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

// Função que mescla dois subarrays para o Merge Sort
void mergeVetores(int *vet, int esquerdaArvore, int metadeArvore, int direitaArvore){
    int tamanhoEsquerda = metadeArvore - esquerdaArvore + 1;
    int tamanhoDireita = direitaArvore - metadeArvore;

    int *arvoreTemporariaEsquerda = (int *)malloc(tamanhoEsquerda * sizeof(int));
    int *arvoreTemporariaDireita = (int *)malloc(tamanhoDireita * sizeof(int));

    int i, j, x, y, z;

    // Copia os dados para os arrays temporários
    for(x = 0; x < tamanhoEsquerda; x++){ arvoreTemporariaEsquerda[x] = vet[esquerdaArvore + x]; }
    for(i = 0; i < tamanhoDireita; i++){ arvoreTemporariaDireita[i] = vet[metadeArvore + 1 + i]; }

    j = 0;
    y = 0;
    z = esquerdaArvore;

    // Mescla os arrays temporários de volta ao array original
    while(j < tamanhoEsquerda && y < tamanhoDireita){
        if (arvoreTemporariaEsquerda[j] <= arvoreTemporariaDireita[y]){
            vet[z] = arvoreTemporariaEsquerda[j];
            j++;
        } else {
            vet[z] = arvoreTemporariaDireita[y];
            y++;
        }
        z++;
    }

    // Copia os elementos restantes de arvoreTemporariaEsquerda, se houver
    while (j < tamanhoEsquerda) {
        vet[z] = arvoreTemporariaEsquerda[j];
        j++;
        z++;
    }

    // Copia os elementos restantes de arvoreTemporariaDireita, se houver
    while (y < tamanhoDireita) {
        vet[z] = arvoreTemporariaDireita[y];
        y++;
        z++;
    }

    free(arvoreTemporariaEsquerda);  // Libera a memória alocada para o array temporário esquerdo
    free(arvoreTemporariaDireita);   // Libera a memória alocada para o array temporário direito
}

// Função recursiva do Merge Sort
void recursaomergeSort(int *vet, int esquerdaArvore, int direitaArvore){
    if (esquerdaArvore < direitaArvore){
        int metadeVetor = esquerdaArvore + (direitaArvore - esquerdaArvore) / 2;

        recursaomergeSort(vet, esquerdaArvore, metadeVetor); // Ordena a primeira metade
        recursaomergeSort(vet, metadeVetor + 1, direitaArvore); // Ordena a segunda metade

        mergeVetores(vet, esquerdaArvore, metadeVetor, direitaArvore); // Mescla as duas metades
    }
}

// Função para iniciar o Merge Sort
void mergeSort(int *vet, int tamanhoVet){ recursaomergeSort(vet, 0, tamanhoVet-1); }

// Função para imprimir o vetor
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

    int escolha;       // Variável para armazenar o tamanho do array
    int escolhaSort;   // Variável para armazenar a escolha do algoritmo de ordenação
    int i; 
    int *vet;
    int init = 0;
    clock_t inicio, fim;     // Variáveis para armazenar o tempo de início e fim da execução
    double tempo_gasto;      // Variável para armazenar o tempo gasto

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

    // Exibe um menu para o usuário escolher o algoritmo de ordenação
    printf("-----------------------------------\n");
    printf("Escolha o algoritmo de ordenacao: \n");
    printf("1 - QuickSort \n");
    printf("2 - HeapSort \n");
    printf("3 - MergeSort \n");
    printf("-----------------------------------\n");

    // Recebe a escolha do algoritmo
    printf("\nDigite o algoritmo escolhido: ");
    scanf("%d", &escolhaSort);

    // Executa o algoritmo escolhido e mede o tempo gasto
    switch(escolhaSort){
        case 1:
            printf("-----------------------------------\n");
            printf("\nVetor desordenado: ");
            imprimirVetor(vet, escolha);
            printf("-----------------------------------\n");
            
            inicio = clock(); // Marca o início da execução do QuickSort
            quickSort(vet, init, escolha-1);
            fim = clock(); // Marca o fim da execução do QuickSort
            
            printf("\nVetor ordenado: ");
            imprimirVetor(vet, escolha);
            printf("-----------------------------------\n");

            // Calcula o tempo gasto em segundos
            tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo gasto no QuickSort: %f segundos\n", tempo_gasto);
            break;
        
        case 2:
            printf("-----------------------------------\n");
            printf("\nVetor desordenado: ");
            imprimirVetor(vet, escolha);
            printf("-----------------------------------\n");

            inicio = clock(); // Marca o início da execução do HeapSort
            heapSort(vet, escolha);
            fim = clock(); // Marca o fim da execução do HeapSort
            
            printf("\nVetor ordenado: ");
            imprimirVetor(vet, escolha);
            printf("-----------------------------------\n");

            // Calcula o tempo gasto em segundos
            tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo gasto no HeapSort: %f segundos\n", tempo_gasto);
            break;

        case 3:
            printf("-----------------------------------\n");
            printf("\nVetor desordenado: ");
            imprimirVetor(vet, escolha);
            printf("-----------------------------------\n");

            inicio = clock(); // Marca o início da execução do MergeSort
            mergeSort(vet, escolha);
            fim = clock(); // Marca o fim da execução do MergeSort
            
            printf("\nVetor ordenado: ");
            imprimirVetor(vet, escolha);
            printf("-----------------------------------\n");

            // Calcula o tempo gasto em segundos
            tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
            printf("Tempo gasto no MergeSort: %f segundos\n", tempo_gasto);
            break;

        default:
            printf("\nEscolha inválida\n");
            break;
    }

    free(vet); // Libera a memória alocada para o array
    return 0;  // Encerra o programa
}
