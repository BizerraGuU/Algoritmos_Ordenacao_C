#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int particionaVetor(int *vet, int init, int fim){

    int piv = (vet[init] + vet[fim] + vet[(init + fim)/2]) / 3;

    /* essa primeira linha determina o pivo a partir da soma do primeiro 
    elemento do vetor e do ultimo elemento e da divisão por dois da soma 
    entre eles, e por fim divide por 3*/

    while(init < fim){
        while(init < fim && vet[init] <= piv){ init++; } 
        /*verifica se o inicio é menor que o final e se pivo é maior do 
        que o valor na posição inicial do vetor e incrementa mais um caso a condição seja verdadeira*/  
        while(init < fim && vet[fim] > piv){ fim--; }
        /*faz o processo inverso da anterior e decrementa um em caso da condição ser atendida*/

        int auxiliar = vet[init];
        vet[init] = vet[fim];
        vet[fim] = auxiliar;

        /*realiza a troca de posição dos valores dentro do vetor*/
    }

    /*retorna o inicio para cotinuar realizando o processo de verificação*/

    return init;
}

void quickSort(int *vet, int init, int fim){
    if(init < fim){
        int posicao = particionaVetor(vet, init, fim); // pega o valor da posicao
        quickSort(vet, init, posicao-1); // faz a ordenação dos numeros menores à esquerda
        quickSort(vet, posicao, fim); // faz a ordenacao dos numeros maiores à direita
    }
}

void imprimirVetor(int vet[], int tamanho) {
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
    int init = 0;

    printf("-----------------------------------\n");
    printf("Escolha o tamanho do vetor ordenar\n");
    printf("-----------------------------------\n");

    printf("\nDigite o tamanho escolhido: ");
    scanf("%d", &escolha);

    vet = (int *)malloc(escolha * sizeof(int));  // realiza a alocação de memoria

    if (vet == NULL) {
        //verifica se o vetor esta vazio ou é inexistente
        printf("Erro ao alocar memória.\n"); // caso seja digitado algo fora do esperado
    }

    srand(time(NULL)); //inicia o gerador de numeros

    for (i = 0; i < escolha; i++) { vet[i] = rand() % 100001; } 
    // realiza a inserção aleatoria dos numeros no vetor com base no tamanho escolhido pelo user

    printf("-----------------------------------\n");
    printf("\nVetor desordenado: ");
    imprimirVetor(vet, escolha);

    quickSort(vet, init, escolha-1);

    printf("\nVetor ordenado: ");
    imprimirVetor(vet, escolha);
    printf("-----------------------------------\n");
    
    free(vet); //libera a memoria alocada no vetor
}