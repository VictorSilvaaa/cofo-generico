#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cofo.h"

typedef struct _pessoa_{
    char nome[30];
    int idade;
    float altura;
}Pessoa;

// funções de comparação
int cmpString(void* item, void* chave) {
    Pessoa* item_temp = (Pessoa*)item;
    // strcmp retorna 0 caso as strings sejam iguais
    if (strcmp(item_temp->nome, (char*)chave) == 0) {  
        return 1;
    }
    return 0;
}

int cmpInt(void* item, void* chave) {
    Pessoa* item_temp = (Pessoa*)item;
    if (item_temp->idade == *(int*)chave) {
        return  1;
    }
    return 0;
}

int cmpFloat(void* item, void* chave) {
    Pessoa* item_temp = (Pessoa*)item;
    if (item_temp->altura == *(float*)chave) {
        return 1;
    }
    return 0;
}


void imprimeelemento(Pessoa* pessoa){
    printf("\nnome: %s", pessoa->nome);
    printf("\nIdade: %d", pessoa->idade);
    printf("\nAltura: %f", pessoa->altura);
}

int main(){
    int flag = 1, resp =0, maxItems, tipoBusca =0, idade, altura;
    char nome[30];
    Pessoa* pessoa;
    gCofo *gc;
    Pessoa* pessoaResult;
    Pessoa* pessoaParaRemover;
    while(flag ==1){
        printf("\n1- Criar um cofo \n2- inserir um elemento no cofo \n3 - consulte algum elemento do cofo \n4- remover um elemento do cofo\n");
        scanf("%d", &resp);

        switch (resp){
            case 1:
                printf("\nDigite maxItens: ");
                scanf("%d", &maxItems);
                gc = gcofCreate(maxItems);
                break;

            case 2:
                pessoa = (Pessoa*) malloc(sizeof(Pessoa));
                printf("\nDigite nome da pessoa: ");
                scanf(" %s", pessoa->nome);
                printf("\nDigite a idade da pessoa: ");
                scanf("%d",&pessoa->idade);
                printf("\nDigite altura: ");
                scanf("%f",&pessoa->altura);
                if(gcofInsert(gc, (void*)pessoa)==1){
                    printf("\nAdicionado com sucesso");
                }else{
                    printf("\nNão adicionado ao cofo");
                };
                break;

            case 3:
                printf("\n1- Buscar elemento pelo nome \n2- Buscar elemento pela idade \n3- Buscar elemento pela altura\n\n");
                scanf("%d", &tipoBusca);
                switch (tipoBusca){
                    case 1:
                        printf("\nDigite nome para busca: ");
                        scanf("%s", nome);
                        pessoaResult = (Pessoa*) gcofQuery(gc, (void*)&nome, cmpString);
                        if (pessoaResult!=NULL){
                            imprimeelemento(pessoaResult);
                        }else{
                            printf("Elemento não encontrado");
                        }
                        break;
                    case 2:
                        printf("\nDigite idade para busca: ");
                        scanf("%d", &idade);
                        if (gcofQuery(gc, &idade, cmpInt)!=NULL){
                            pessoaResult = (Pessoa*) gcofQuery(gc, (void*)&idade, cmpInt);
                            imprimeelemento(pessoaResult);
                        }else{
                            printf("Elemento não encontrado");
                        }
                        break;
                    default:
                        printf("\nDigite altura para busca: ");
                        scanf("%f", &altura);
                        pessoaResult = (Pessoa*) gcofQuery(gc,(void*)&altura, cmpFloat);
                        if (pessoaResult!=NULL){
                            imprimeelemento(pessoaResult);
                        }else{
                            printf("Elemento não encontrado");
                        }
                        break;
                    }
                break;

            case 4:
                pessoaParaRemover = (Pessoa*) malloc(sizeof(Pessoa));
                printf("\nDigite idade do elemento para remover: ");
                scanf("%d", &idade);
                printf("\nDigite nome do elemento para remover: ");
                scanf(" %s", pessoaParaRemover->nome);
                printf("\nDigite altura do elemento para remover: ");
                scanf("%f", &pessoaParaRemover->altura);
                pessoaResult = (Pessoa*) gcofQuery(gc, (void*)&idade, cmpInt);
                if(elemRemover(gc, (void*)&pessoaResult)!= NULL){
                    printf("Removido com sucesso");
                }else{
                    printf("nao removido com sucesso");
                };
        default:
            break;
        }

    }
    return 0;
}