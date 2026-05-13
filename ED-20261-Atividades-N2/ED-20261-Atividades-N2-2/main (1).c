#include <stdio.h>
#include <stdlib.h>

struct No {
    int valor;
    struct No *esq;
    struct No *dir;
};

struct No* criarNo(int v) {

    struct No* n = (struct No*)malloc(sizeof(struct No));

    n->valor = v;
    n->esq = NULL;
    n->dir = NULL;

    return n;
}


void mostrarArvore(struct No* raiz, int nivel) {

    if (raiz == NULL)
        return;

    mostrarArvore(raiz->dir, nivel + 1);

    for(int i = 0; i < nivel; i++) {
        printf("     ");
    }

    printf("%d\n", raiz->valor);

    mostrarArvore(raiz->esq, nivel + 1);
}

 struct No* inserir(struct No* raiz, int v) {

    if (raiz == NULL) {

        printf("\nInserindo %d na arvore\n", v);

        return criarNo(v);
    }

    if (v < raiz->valor) {

        printf("%d < %d -> ESQUERDA\n",
               v, raiz->valor);

        raiz->esq = inserir(raiz->esq, v);
    }

    else if (v > raiz->valor) {

        printf("%d > %d -> DIREITA\n",
               v, raiz->valor);

        raiz->dir = inserir(raiz->dir, v);
    }

    return raiz;
}

int calcularAltura(struct No* n) {

    if (n == NULL)
        return -1;

    int h_esq = calcularAltura(n->esq);

    int h_dir = calcularAltura(n->dir);

    int altura;

    if (h_esq > h_dir) {
        altura = 1 + h_esq;
    }
    else {
        altura = 1 + h_dir;
    }

    printf("NO %d | Esq = %d | Dir = %d | Altura = %d\n",
           n->valor,
           h_esq,
           h_dir,
           altura);

    return altura;
}

 
int obterFB(struct No* n) {

    if (n == NULL)
        return 0;

    return calcularAltura(n->esq)
         - calcularAltura(n->dir);
}

int main() {

    struct No* raiz = NULL;

    int valor;

    printf("Digite os valores:\n");

    for(int i = 0; i < 4; i++) {

        printf("\nValor %d: ", i + 1);
        scanf("%d", &valor);

        raiz = inserir(raiz, valor);

        printf("\nARVORE :\n\n");

        mostrarArvore(raiz, 0);

    
    }

    

    int altura = calcularAltura(raiz);

    int fb = obterFB(raiz);

    

    printf("Raiz: %d\n", raiz->valor);

    printf("Altura Total: %d\n", altura);

    printf("Fator de Balanceamento: %d\n", fb);

    if (fb > 1 || fb < -1) {
        printf("ARVORE DESBALANCEADA\n");
    }
    else {
        printf("ARVORE BALANCEADA\n");
    }

    return 0;
}