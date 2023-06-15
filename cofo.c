#include <stdlib.h>
#include <stdio.h>
#include "cofo.h"


gCofo *gcofCreate( int max_itens ){
    gCofo *gc;
    if ( max_itens > 0) {
        gc = (gCofo *) malloc(sizeof (gCofo ));
        if ( gc != NULL) {
            gc->item = (void **) malloc (sizeof(void *)*max_itens);
            if (gc->item != NULL){
                gc->numItens = 0;
                gc->maxItens = max_itens;
                gc-> cur = -1;
                return gc;
            }
        }
    }
    free(gc);
    return NULL;
}

int gcofInsert(gCofo *gc, void *item ){
    if ( gc != NULL ) {
        if ( gc->numItens < gc->maxItens) {
            gc->item[gc->numItens] = item;
            gc->numItens++;
            return 1;
        }
    }
    return 0;
}

void *gcofQuery (gCofo *gc, void *key, int (*cmp)(void *, void *)){
    int i=0; 
    int stat;
    if (gc!=NULL) {
        if (gc->numItens > 0 ){
            stat = cmp(gc->item[i], key);
            for(int i = 0; i < gc->numItens; i++){
                stat = cmp(gc->item[i], key);
                if(stat ==1){
                    printf("encontrou");
                    return gc->item[i];
                }
            }
        }
    }
    printf("vetor nulo");
    return NULL;
}

void* elemRemover (gCofo *col, void* chave) {
    void* data;
    if (col == NULL)
        return NULL;

    // Deve ter algo dentro da coleção pra poder tirar
    if (col->numItens <= 0) {
        return NULL;
    }

    // Procura o primeiro valor com a chave, exclui ele da coleção e retorna ele
    for (int i = 0; i < col->numItens; i++) {
        // Procura algum item dentro da coleção com essa chave
        if (col->item[i] == chave) {
            // Salva ela pra retornar depois
            data = col->item[i];
            // Pega tudo o que tem depois e reorganiza
            for (int j = i; j < col->numItens; j++) {
                col->item[j] = col->item[j+1];
            }
            // Diminui a quantidade de itens do vetor
            col->numItens--;
            return data;
        }
    }
    printf("não achou");
    return NULL;
}

int gcofDestroy (gCofo *gc){
 if ( gc != NULL ){
    if ( gc->numItens == 0 ){
        free(gc->item);
        free(gc);
        return 1;
    }
 }
 return 0;
}

void * gcofGetFirst(gCofo *gc){
    void *elm;
    if ( gc != NULL ) {
        if ( gc->numItens > 0){
            elm = gc->item[0];
            gc->cur = 0;
            return elm;
        }
    }
    return NULL;
}

void * gcofGetNext(gCofo *gc){ 
    void *elm;
    if ( gc!=NULL){
        if ( gc->numItens > 0 && gc->cur <gc->numItens-1){
            gc->cur++;
            elm = gc->item[gc->cur];
            return elm;
        }
    }
    return NULL;
}

