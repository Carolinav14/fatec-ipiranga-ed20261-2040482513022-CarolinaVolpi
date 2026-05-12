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
    n->esq = n->dir = NULL;
    return n;
}


struct No* inserir(struct No* raiz, int v) {
    if (raiz == NULL) {
        return criarNo(v);
    }
    if (v < raiz->valor) {
        raiz->esq = inserir(raiz->esq, v);
    } else if (v > raiz->valor) {
        raiz->dir = inserir(raiz->dir, v);
    }
    return raiz;
}


int calcularAltura(struct No* n) {
    if (n == NULL) return -1;

    int h_esq = calcularAltura(n->esq);
    int h_dir = calcularAltura(n->dir);

    if (h_esq > h_dir) {
        return 1 + h_esq;
    } else {
        return 1 + h_dir;
    }
}


int obterFB(struct No* n) {
    if (n == NULL) return 0;
    return calcularAltura(n->esq) - calcularAltura(n->dir);
}

int main() {
    struct No* raiz = NULL;
    int valor, i;

   
    printf("Digite os 4 valores para montar a arvore \n");

   
    for(i = 0; i < 4; i++) {
        printf("Valor %d: ", i + 1);
        scanf("%d", &valor);
        raiz = inserir(raiz, valor);
    }

    
    int h = calcularAltura(raiz);
    int fb = obterFB(raiz);

    printf("\n--- VIZUALIZAÇÃO DA ARVORE ---\n");
    printf("Raiz da Arvore: %d\n", raiz->valor);
    printf("Altura Total (H): %d\n", h);
    printf("Fator de Balanceamento (FB): %d\n", fb);

    if (fb > 1 || fb < -1) {
        printf("DESBALANCEADA \n");
    } else {
        printf("BALANCEADA\n");
    }

    return 0;
}
