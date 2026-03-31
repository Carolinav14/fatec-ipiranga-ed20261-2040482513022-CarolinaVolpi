/******************************************************************************
/*----------------------------------------------------------------------------------*/
/*                                FATEC-Ipiranga                                    */        
/*                            ADS - Estrutura de Dados                              */
/*                             Id da Atividade: ATividade 3                         */
/*             Objetivo: Atividade 3 - Pilha                                        */
/*                                                                                  */
/*                                  Autor: Carolina Volpi                            /
/*                                                                   Data:dd/mm/2026*/
/*----------------------------------------------------------------------------------*/
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    double T=0, Z=0, Y=0, X=0; // registradores da pilha
    char line[256];

    printf("Calculadora RPN \n");
    printf("Digite a expressão \n");

    if (!fgets(line, sizeof(line), stdin)) return 0;
    line[strcspn(line, "\n")] = 0; // remove o topo

    char *token = strtok(line, " ");
    while(token != NULL) {
        char *endptr;
        double val = strtod(token, &endptr);

        if (endptr != token) {
            // é número → empilha
            T = Z;
            Z = Y;
            Y = X;
            X = val;
        } else {
            // operador
            double a = X, b = Y, r;
            char op = token[0];
            switch(op) {
                case '+': r = b + a; break;
                case '-': r = b - a; break;
                case '*': r = b * a; break;
                case '/':
                    if(a == 0){ printf("Erro: divisão por zero!\n"); r=0; }
                    else r = b / a;
                    break;
                default:
                    printf("Operador inválido: %s\n", token);
                    token = strtok(NULL, " ");
                    continue;
            }
            X = r;
            Y = Z;
            Z = T;
        }

        // exibe pilha após cada token
        printf("Pilha -> T:%.2f  Z:%.2f  Y:%.2f  X:%.2f\n", T,Z,Y,X);
        token = strtok(NULL, " ");
    }

    printf("Resultado final: %.2f\n", X);
    return 0;
}
