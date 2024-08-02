#include "abb.h"

TNode* abbCreate(void* data){
    TNode* tree = (TNode*) malloc(sizeof(TNode));
    if(tree != NULL){
        tree->data = data;
        tree->l = NULL;
        tree->r = NULL;
        return tree;
    }
    return NULL;
}

TNode *abbInsert(TNode *t, void *data, int (*cmp)(void *, void *)) {
    if (t == NULL) {
        TNode *newnode = (TNode *) malloc(sizeof(TNode));
        if (newnode != NULL) {
            newnode->l = newnode->r = NULL;
            newnode->data = data;
            return newnode;
        }
        return NULL;
    } else {
        int stat = cmp(data, t->data);
        if (stat > 0) {
            t->r = abbInsert(t->r, data, cmp);
        } else if (stat < 0) {
            t->l = abbInsert(t->l, data, cmp);
        }
        return t;
    }
}

TNode* abbRemove (TNode *t, void *key, int (*cmp)(void *, void *), void **data) {
    if (t == NULL) {
        return NULL;
    }

    int cmpResult = cmp(key, t->data);
    if (cmpResult < 0) {
        t->l = abbRemove(t->l, key, cmp, data);
    } else if (cmpResult > 0) {
        t->r = abbRemove(t->r, key, cmp, data);
    } else {
        // Encontrou o nó a ser removido
        if (data) {
            *data = t->data; // Salva o dado removido, se fornecido
        }

        // Nó com apenas um filho ou nenhum filho
        if (t->l == NULL) {
            TNode *temp = t->r;
            free(t);
            return temp;
        } else if (t->r == NULL) {
            TNode *temp = t->l;
            free(t);
            return temp;
        }

        // Nó com dois filhos: encontrar o sucessor em ordem (menor valor na subárvore direita)
        TNode *temp = t->r;
        while (temp->l != NULL) {
            temp = temp->l;
        }

        // Copiar o conteúdo do sucessor para este nó
        t->data = temp->data;

        // Remover o sucessor
        t->r = abbRemove(t->r, temp->data, cmp, NULL);
    }

    return t;
}

void* abbQuery(TNode* t, void* key, int(*cmp)(void*, void*)){
    void* data;
    if(t != NULL){
        int stat = cmp(key, t->data);
        if(stat == 0){
            data = t->data;
            return data;
        }else if(stat == 1){
            data = abbQuery(t->r, key, cmp);
            return data;
        }else if(stat == -1){
            data = abbQuery(t->l, key, cmp);
            return data;
        }
    }
    return NULL;
}
void* abbMenorData(TNode* tree){
    if(tree != NULL){
        if(tree->l != NULL){
            return abbMenorData(tree->l);
        }else{
            return tree->data;
        }
    }else{
        return NULL;
    }
}
void* abbMaiorData(TNode* t){
    if(t != NULL){
        if(t->r != NULL){
            return abbMaiorData(t->r);
        }else{
            return t->data;
        }
    }else{
        return NULL;
    }
}
TNode *abbRemoveMaior(TNode *t, int (*cmp)(void *, void *), void **data){
    if (t != NULL){
        void *data2;
        TNode *aux;
        if (t->r != NULL){
            t->r = abbRemoveMaior(t->r, cmp, &data2);
            return t;
        } else {
            if (t->l != NULL){
                aux = t->l;
                *data = t->data;
                free(t);
                return aux;
            } else {
                *data = t->data;
                free(t);
                return NULL;
            }
        }
    }
    *data = NULL;
    return NULL;
}

TNode *abbRemoveMenor(TNode *t, int (*cmp)(void *, void *), void **data){
    if (t != NULL){
        void *data2;
        TNode* aux;
        if (t->l != NULL){
            t->l = abbRemoveMenor(t->l, cmp, &data2);  // Corrigido aqui
            return t;
        } else {
            if (t->r != NULL){
                aux = t->r;
                *data = t->data;
                free(t);
                return aux;
            } else {
                *data = t->data;
                free(t);
                return NULL;
            }
        }
    }
    *data = NULL;
    return NULL;
}



void preOrdem(TNode* t, void(*visit)(void*)){
    if(t != NULL){
        visit(t->data);
        preOrdem(t->l, visit);
        preOrdem(t->r, visit);
    }
}

void simetrica(TNode* t, void(*visit)(void*)){
    if(t != NULL){
        simetrica(t->l, visit);
        visit(t->data);
        simetrica(t->r, visit);
    }
}

void posOrdem(TNode* t, void(*visit)(void*)){
    if(t != NULL){
        posOrdem(t->l, visit);
        posOrdem(t->r, visit);
        visit(t->data);
    }
}
int abbNumNos(TNode* t){
    int nl, n, nr;
    if(t != NULL){
        nl = abbNumNos(t->l);
        n = 1;
        nr = abbNumNos(t->r);
        return nl + n + nr;
    }
    return 0;
}


/**
 * abbDestroy(TNode **tree):
 * Destroi a árvore binária de busca (ABB).
 *
 * Esta função libera toda a memória alocada para a árvore binária de busca,
 * esvaziando-a completamente e garantindo que o ponteiro da árvore seja definido como NULL.
 *
 * O paramatro tree é um Ponteiro duplo para a raiz da árvore. O uso de um ponteiro duplo permite
 *              que a função modifique o ponteiro original, garantindo que ele seja
 *              definido como NULL após a destruição da árvore.
 *
 * Retorna TRUE se a árvore foi destruída com sucesso, caso contrário, retorna FALSE.
 */
int abbDestroy(TNode **t) { // Recebe um ponteiro para ponteiro para a raiz da árvore
    if (*t != NULL) { // Verifica se a árvore não está vazia
        abbEsvazia(t, NULL);  // Usa a função abbEsvazia para limpar a árvore
        return TRUE;
    }
    return FALSE;
}
void abbEsvazia(TNode** t, int(*cmp)(void*, void*)) { // Recebe um ponteiro para ponteiro para a raiz da árvore
    if (*t != NULL) { // Verifica se a árvore não está vazia
        abbEsvazia(&(*t)->l, cmp);// Esvazia a subárvore esquerda
        abbEsvazia(&(*t)->r, cmp);// Esvazia a subárvore direita
        free((*t)->data);// Libera a memória alocada para o dado
        free(*t);// Libera a memória alocada para o nó
        *t = NULL;  // Garante que o ponteiro da árvore seja NULL após esvaziar
    }
}