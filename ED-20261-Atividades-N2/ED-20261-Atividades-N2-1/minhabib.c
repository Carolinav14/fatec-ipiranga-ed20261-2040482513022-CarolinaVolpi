#include <stdio.h>
#include <stdlib.h>
#include "minhabib.h"

// Funções de utilidade
No* criar_no(int valor) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo) {
        novo->valor = valor;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

No* inserir(No* raiz, int valor) {
    if (raiz == NULL) return criar_no(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

No* buscar(No* raiz, int valor) {
    if (raiz == NULL || raiz->valor == valor) return raiz;
    if (valor < raiz->valor) return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}


int calcular_altura(No* no) {
    if (no == NULL) return -1;
    int h_esq = calcular_altura(no->esq);
    int h_dir = calcular_altura(no->dir);
    return (h_esq > h_dir ? h_esq : h_dir) + 1;
}

void imprimir_nos_internos(No* raiz) {
    if (raiz == NULL) return;
    if (raiz->esq != NULL || raiz->dir != NULL) {
        // É interno se não for folha. No caso da raiz, se tiver filhos é interno.
        // O PDF pede para imprimir o valor de todos os nós que possuem pelo menos um filho.
        printf("%d ", raiz->valor);
    }
    imprimir_nos_internos(raiz->esq);
    imprimir_nos_internos(raiz->dir);
}

void imprimir_folhas(No* raiz) {
    if (raiz == NULL) return;
    if (raiz->esq == NULL && raiz->dir == NULL) {
        printf("%d ", raiz->valor);
    }
    imprimir_folhas(raiz->esq);
    imprimir_folhas(raiz->dir);
}

void imprimir_nivel_especifico(No* raiz, int nivel_desejado, int nivel_atual) {
    if (raiz == NULL) return;
    if (nivel_atual == nivel_desejado) {
        printf("%d ", raiz->valor);
    } else {
        imprimir_nivel_especifico(raiz->esq, nivel_desejado, nivel_atual + 1);
        imprimir_nivel_especifico(raiz->dir, nivel_desejado, nivel_atual + 1);
    }
}

void imprimir_niveis(No* raiz, int nivel_atual) {
    int h = calcular_altura(raiz);
    for (int i = 0; i <= h; i++) {
        printf("Nivel %d: ", i);
        imprimir_nivel_especifico(raiz, i, 0);
        printf("\n");
    }
}

int calcular_profundidade(No* raiz, int valor, int profundidade_atual) {
    if (raiz == NULL) return -1;
    if (raiz->valor == valor) return profundidade_atual;
    if (valor < raiz->valor) 
        return calcular_profundidade(raiz->esq, valor, profundidade_atual + 1);
    return calcular_profundidade(raiz->dir, valor, profundidade_atual + 1);
}

void imprimir_ancestrais(No* raiz, int valor) {
    if (raiz == NULL) return;
    if (raiz->valor == valor) return;
    
    // Para BST, o caminho é único
    printf("%d ", raiz->valor);
    if (valor < raiz->valor)
        imprimir_ancestrais(raiz->esq, valor);
    else
        imprimir_ancestrais(raiz->dir, valor);
}

void imprimir_descendentes(No* no) {
    if (no == NULL) return;
    // Imprime todos na subárvore exceto o próprio nó
    if (no->esq != NULL) {
        printf("%d ", no->esq->valor);
        imprimir_descendentes(no->esq);
    }
    if (no->dir != NULL) {
        printf("%d ", no->dir->valor);
        imprimir_descendentes(no->dir);
    }
}

void exibir_visual(No* raiz, int espaco) {
    if (raiz == NULL) return;
    espaco += 5;
    exibir_visual(raiz->dir, espaco);
    printf("\n");
    for (int i = 5; i < espaco; i++) printf(" ");
    printf("%d\n", raiz->valor);
    exibir_visual(raiz->esq, espaco);
}

void analisar_arvore(No* raiz, int valorBusca) {
    if (raiz == NULL) {
        printf("Arvore vazia.\n");
        return;
    }

    
    printf("Raiz: %d\n", raiz->valor);
    
    printf("Nos Internos: ");
    imprimir_nos_internos(raiz);
    printf("\n");
    
    printf("Nos Externos (Folhas): ");
    imprimir_folhas(raiz);
    printf("\n");
    
    printf("Exibicao por Niveis:\n");
    imprimir_niveis(raiz, 0);


    No* encontrado = buscar(raiz, valorBusca);
    if (encontrado) {
        int filhos = 0;
        if (encontrado->esq) filhos++;
        if (encontrado->dir) filhos++;
        printf("Grau do No: %d\n", filhos);
        
        printf("Ancestrais: ");
        imprimir_ancestrais(raiz, valorBusca);
        printf("\n");
        
        printf("Descendentes: ");
        imprimir_descendentes(encontrado);
        printf("\n");
        
        printf("Altura: %d\n", calcular_altura(encontrado));
        printf("Profundidade: %d\n", calcular_profundidade(raiz, valorBusca, 0));
        
        printf("\n SUB-ARVORE \n");
        exibir_visual(encontrado, 0);
    } else {
        printf("Valor %d nao encontrado na arvore.\n", valorBusca);
    }
}
