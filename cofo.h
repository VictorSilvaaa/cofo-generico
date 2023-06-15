#ifndef _COFO_H
#define _COFO_H

typedef struct _gcofo_{
    int numItens;
    int maxItens;
    int cur;
    void **item;
}gCofo;

gCofo *gcofCreate( int max_itens );
int gcofInsert(gCofo *c, void *item );
void *gcofRemove(gCofo *c, void *key );
void *gcofQuery (gCofo *gc, void *key, int (*cmp)(void *, void *));
void *gcofGetFirst(gCofo *c);
void *gcofGetNext (gCofo *c);
int colDestroy (gCofo *);
void* elemRemover (gCofo *col, void* chave);

#else
extern gCofo *gcofCreate( int max_itens );
extern int gcofInsert(gCofo *c, void *item );
extern void * gcofRemove(gCofo *c, void *key );
extern void * gcofQuery (gCofo *c, void *key );
extern void *gcofGetFirst(gCofo *c);
extern void *gcofGetNext (gCofo *c);
extern int colDestroy (gCofo *);

#endif // __COFO_H