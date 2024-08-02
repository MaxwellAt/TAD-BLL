#ifndef ABB_H
#define ABB_H
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnode {
    struct tnode *l;
    struct tnode *r;
    void *data;
} TNode;

TNode *abbCreate(void* data);
TNode* abbInsert(TNode* t, void* data, int(*cmp)(void*, void*));
TNode* abbRemove(TNode *t, void *key, int (*cmp)(void *, void *), void **data);
void* abbQuery(TNode* t, void* key, int(*cmp)(void*, void*));
void* abbMenorData(TNode* t);
void* abbMaiorData(TNode* t);
TNode *abbRemoveMaior(TNode *t, int (*cmp)(void *, void *), void **data);
TNode *abbRemoveMenor(TNode *t, int (*cmp)(void *, void *), void **data);
void preOrdem(TNode* t, void(*visita)(void*));
void simetrica(TNode* t, void(*visita)(void*));
void posOrdem(TNode* t, void(*visita)(void*));
int abbNumNos(TNode* t);
int abbDestroy(TNode **t);
void abbEsvazia(TNode** t, int(*cmp)(void*, void*));

#endif // ABB_H