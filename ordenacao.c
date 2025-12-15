#include <stdio.h>
#include <stdlib.h> // Para as funções rand(), srand()
#include <time.h> // Para a função time(), usada para semear o gerador de numeros aleatorios

// Define o tamanho das lisas que serão ordenadas.
// Facilita a alteração para testes com mas ou menos elementos.
#define TAMANHO 10


// --- DECLARAÇÃO DAS FUNÇÕES (PROTÓTIPOS) ---
// Informa ao compilador sobre a existência e a "assinatura" das funções
// que serão implementadas mais abaixo.

// Funções para gerar os diferentes tipos de listas
void gerarListaOrdenada(int lista[], int n);
void gerarListaInversa(int lista[], int n);
void gerarListaAleatoria(int lista[], int n);

// Funções de ordenação
void bubbleSort(int lista[], int n);
void insertionSort(int lista[], int n);
void selectionSort(int lista[], int n);

// Funções auxiliares
void imprimirLista(const char* titulo, const int lista[], int n);
void copiarLista(int destino[], const int origem[], int n);



// =========== FUNÇÃO PRINCIPAL (MAIN) ===========
// O programa inicia sua execução aqui
int main() {
    // Semeia o gerador de números aleatorios com a hora atual
    // Isso garante que a lista aleatoria seja diferente a cada execução do programa
    // Deve ser chamado apenas UMA VEZ.
    srand(time(NULL));

    //Declara os três tipos de listas que servirão como nossos casos de teste.
    int listaOrdenada[TAMANHO];
    int listaInversa[TAMANHO];
    int listaAleatoria[TAMANHO];

    // Preenche as listas com os padroes desejados
    printf("\n--- GERANDO LISTAS DE ENTRADA ---\n");
    gerarListaOrdenada(listaOrdenada, TAMANHO);
    gerarListaInversa(listaInversa, TAMANHO);
    gerarListaAleatoria(listaAleatoria, TAMANHO);
    printf("---------------------------------\n\n");


    // Declara uma lista temporaria que será usada para receber uma cópia
    // dos dados antes de cada ordenação. Isso é CRUCIAL para garantir que 
    // cada algoritmo receba a mesma lista de entrada original.
    int listaTemp[TAMANHO];



    // =================================================
    // 1. TESTANDO O BUBBLE SORT
    // =================================================
    printf("=================== 1. BUBBLE SORT ===================");

    // a) Melhor caso: Lista ja ordenada
    copiarLista(listaTemp, listaOrdenada, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Melhor Caso (já ordenada)", listaTemp, TAMANHO);

    // b) Pior Caso: Lista em ordem inversa
    copiarLista(listaTemp, listaInversa, TAMANHO);
    bubbleSort(listaTemp, TAMANHO);
    imprimirLista("Bubble Sort | Pior Caso (ordem inversa)", listaTemp, TAMANHO);

    // c) Caso Medio : Lista aleatoria
    copiarLista(listaTemp, listaAleatoria, TAMANHO);
    selectionSort(listaTemp, TAMANHO);
    imprimirLista("Selection Sort | Caso Medio (aleatorio)", listaTemp, TAMANHO);
    printf("\n");

    return 0; // Fim do programa
}

// ---- IMPLEMENTAÇÃO DAS FUNÇÕES DE ORDENAÇÃO ----

/**
 * @brief Ordena uma lista usando o algoritmo Bubble sort,
 * @details Lógica: Compara pare de eleentos adjacentes e os troca se estiverem
 * na ordem errada. Repete esse processo até que a lista esteja ordenada.
 * Eleentos maiores "borbulham" para o final da lista.
 * - Melhor Caos: Com a otimização, faz apenas uma passagem;
 * - Pior caso: lista em ordem inversa
 */
void bubbleSort(int lista[], int n) {
    int i, j, temp;
    int trocou; // Flag de otimização

    // Laço externo controla o numero de passagem pela lista
    // Após cada passagem 'i', o i esimo valor elemento estara no lugar certo
    for (i = 0; i < n; i++) {
        trocou = 0; // No inicio de cada passagem, assumimos que nao havera trocas

        // Laço interno percorre a lista, comparando elementos adjacentes.
        // O imite é 'n - i - 1' porque oselementos no final ja estao ordenados.
        for (j = 0; j < n - 1; j++) {
            // Se o elemento atual for maior que o proximo...
            if (lista[j] > lista[j + 1]) {
                // .. Troc eles de lugar.
                temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = 1; // Maraca que uam troca ocorreu
            }
        }

        // OTIMIZAÇÃO: Se após uma passagem complea nenhuma troca foi feita,
        // a lista já está ordenada e pdemos parar o algoritmo.
        if (trocou == 0) {
            break;
        }
    }
}

/**
 * @brief Ordena uma lista usando o algoritmo Insertion Sort.
 * @details Lógica: Percorre a lista, construindo uma sub-lista ordenada a esquerda
 * A cada passo, pega o proximo elemento e o insere na posicao correta.
 * dentro da sub-lista ja ordenada, "empurrando" os maiores para a direita.
 * - Melhor Caso: Lista ja ordenada, só percorre.
 * - Pior Caso: Lista em ordem inversa.
 */
void insertionSort(int lista[], int n) {
    int i, chave, j;

    // Começa do segundo elemento (indice 1), pois o primeiro ja e uma sub-lista ordenada
    for (i = 1;i < n; i++) {
        //'chave' é o elemento que queremos inserir na parte ordenada.
        chave = lista[i];
        // 'j' aponta para o ultimo elemento da parte ordenada.
        j = i - 1;

        // Move os elementos da parte ordenada que sao maiores que a 'chave'
        // uma posição para a direita, para abrir espaço para a inserção.
        while (j >= 0 && lista[j] > chave) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }
        
        // Insere a 'chave' na posicao correta (o "buraco" aberto).
        lista[j + 1] = chave;
    }
}


/**
 * @brief Ordena uma lista usando o algoritmo Selection Sort
 * @details Lógica: Divide a lista em duas partes: orednada (a esquerda) e
 *  não ordenada (a direita). A cada passo, encontra o menor elemento
 * na parte não ordenada e o troca com o primeiro elemento da parte não ordenada.
 * 
 * O número de comparações é o mesmo independentemente da ordem inicial.
 */
void selectionSort( int lista[], int n) {
    int i, j, indice_min, temp;

    // Laço externo percorre a lista para definir a fronteira entre
    // a parte ordenda e a não ordenada
    for (i = 0; i < n - 1; i++) {
        // Assume que o primeiro elemento da parte nao ordenada é o menor
        indice_min = i;

        // Laço interno percorre a parte não ordenada para encontrar o menor elemento
        for (j = i + 1; j < n; j++) {
        // Se encontrar um elemento menor que o minimo atual...
        if (lista[j] < lista[indice_min]) {
            //.... Atualiza o indice do minimo.
            indice_min = j;
        }
    }

    // Se o menor elemento não for o priemiro da parte nao ordenada
    // Troca os de lugar.
    if (indice_min != i) {
        temp = lista[i];
        lista[i] = lista[indice_min];
        lista[indice_min] = temp;
    }
  }
}

// --- IMPLEMENTAÇÃO DA FUNÇÕES AUXILIARES ---

/**
 * @brief Gera uma lista de 'n' elementos em ordem crescente.
 */
void gerarListaOrdenada(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = i + 1;
    }
    imprimirLista("Original - Ordenada", lista, n);
}

/**
 * @brief Gera uma lista de 'n' elemento em ordem decrescente.
 */
void gerarListaInversa(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = n - i;
    }
    imprimirLista("Original - Inversa", lista, n);
}

/**
 * @brief Gera uma lista de 'n' elementos com valores aleatórios entre 1 e 100.
 */
void gerarListaAleatoria(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        lista[i] = rand() % 100 + 1;  // Gera número entre 1 e 100
    }
    imprimirLista("Original - Aleatoria", lista, n);
}

/**
 * @brief Copia os elementos de uma lista origem para uma lista destino.
 */
void copiarLista(int destino[], const int origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

/**
 * @brief Imprime uma lista de inteiros no formato legível.
 * @param titulo Descrição da lista a ser impressa
 * @param lista Array de inteiros
 * @param n Tamanho da lista
 */
void imprimirLista(const char* titulo, const int lista[], int n) {
    printf("%s: [", titulo);
    for (int i = 0; i < n; i++) {
        printf("%d", lista[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}