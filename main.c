#include "abb.h"

// 1 Crie uma coleção
// 2 Insira tres elementos na coleção
// 3 Liste os elementos da Colecao
// 4 Consulte um dos elementos da coleçào
// 5 remova o segundo elemento inserido na colecao
// 6 Liste os elementos da coleçào
// 7 Esvazie a colecao
// 8 Liste os elementos da coleçào


typedef struct {
    char nome[30];
    int idade;
    float nota;
} Student;

void printaElm(void* data){
    Student* var = (Student*) data;
    printf("Nome: %s ,idade: %d ,nota: %.2f \n", var->nome, var->idade, var->nota);
}
void listarStudents(TNode *tree) {
    if (tree == NULL) {
        printf("----------Lista vazia--------\n");
    } else {
        int nelms = abbNumNos(tree);
        if (nelms > 0) {
            simetrica(tree, printaElm);
        } else {
            printf("----------Lista vazia--------\n");
        }
    }
}
// 1 quando a idade de pa for maior q pb. -1 caso contratário.
// 0 se a idade nome e nota forem iguais e -2 caso de algum tipo de erro.
int cmp(void* a, void* b) {
    Student *pa = (Student *) a;
    Student *pb = (Student*) b;
    if (pa != NULL && pb != NULL) {
        if (pa->idade > pb->idade) {
            return 1;
        }
        if (pa->idade < pb->idade) {
            return -1;
        }
        if (strcmp(pa->nome, pb->nome) == 0 && pa->nota == pb->nota && pa->idade == pb->idade) {
            return 0;
        }
    }
    return -2;
}

int main() {
    TNode *tree = NULL;

    do {
        printf("1 - Criar árvore\n");
        printf("2 - Inserir um estudante\n");
        printf("3 - Remover um estudante\n");
        printf("4 - Consultar um estudante\n");
        printf("5 - Listar os estudantes\n");
        printf("6 - Destruir a árvore\n");
        printf("7 - Esvaziar a árvore\n");
        printf("0 - Sair\n");
        printf("Deseja realizar qual operação? \n");

        int opcao;
        scanf("%d", &opcao);
        switch (opcao) {
            case 1: {
                if (tree != NULL) {
                    printf("Árvore já criada\n");
                    printf("Primeiro destrua a árvore anterior\n");
                    printf("\n");
                    break;
                }
                Student *student = (Student *) malloc(sizeof(Student));
                if (student != NULL) {
                    printf("Nome: ");
                    scanf("%s", student->nome);
                    printf("Idade: ");
                    scanf("%d", &student->idade);
                    printf("Nota: ");
                    scanf("%f", &student->nota);
                    tree = abbCreate(student);
                    if (tree != NULL) {
                        printf("Árvore criada com sucesso!\n");
                        printf("\n");
                    } else {
                        printf("Não foi possível criar a árvore. Tente novamente.\n");
                        printf("\n");
                    }
                }
                break;
            }
            case 2: {
                Student *student = (Student *) malloc(sizeof(Student));
                if (tree != NULL && student != NULL) {
                    printf("Nome: ");
                    scanf("%s", student->nome);
                    printf("Idade: ");
                    scanf("%d", &student->idade);
                    printf("Nota: ");
                    scanf("%f", &student->nota);
                    if (abbInsert(tree, student, cmp) != NULL) {
                        printf("Estudante inserido com sucesso\n");
                        printf("\n");
                    } else {
                        printf("Erro ao inserir estudante\n");
                        printf("\n");
                    }
                } else {
                    printf("Árvore não criada\n");
                    printf("\n");
                }
                break;
            }
            case 3: {
                Student *student = (Student *) malloc(sizeof(Student));
                if (tree != NULL && student != NULL) {
                    printf("Nome: ");
                    scanf("%s", student->nome);
                    printf("Idade: ");
                    scanf("%d", &student->idade);
                    printf("Nota: ");
                    scanf("%f", &student->nota);
                    void *data = NULL;
                    tree = abbRemove(tree, student, cmp, &data);  // Atualiza o ponteiro da raiz
                    if (data != NULL) {
                        printf("Estudante removido com sucesso!\n");
                        printf("\n");
                    } else {
                        printf("Estudante não encontrado\n");
                        printf("\n");
                    }
                } else {
                    printf("Árvore não criada\n");
                    printf("\n");
                }
                break;
            }
            case 4: {
                Student *student = (Student*) malloc(sizeof(Student));
                if (tree != NULL && student != NULL) {
                    printf("Nome: ");
                    scanf("%s", student->nome);
                    printf("Idade: ");
                    scanf("%d", &student->idade);
                    printf("Nota: ");
                    scanf("%f", &student->nota);

                    Student *chave = (Student*) abbQuery(tree, student, cmp);
                    if (chave != NULL) {
                        printf("Estudante encontrado!\n");
                        printf("Nome: %s, Idade: %d, Nota: %.2f\n", chave->nome, chave->idade, chave->nota);
                        printf("\n");
                    } else {
                        printf("Estudante não encontrado\n");
                        printf("\n");
                    }
                } else {
                    printf("Árvore não criada\n");
                    printf("\n");
                }
                break;
            }
            case 5: {
                if (tree != NULL) {
                    printf("Aqui estão os estudantes da Arvore:\n");
                    listarStudents(tree);
                    printf("\n");
                } else {
                    printf("Arvore não criada\n");
                    printf("\n");
                }
                break;
            }
            case 6: {
                if (tree != NULL) {
                    if (abbNumNos(tree) == 0) {
                        if (abbDestroy(&tree) == TRUE) { // Passa o endereço da árvore
                            printf("Árvore destruída\n");
                            printf("\n");
                            tree = NULL;
                        } else {
                            printf("Árvore não destruída\n");
                            printf("\n");
                        }
                    } else {
                        printf("A árvore não está vazia. Não é possível destruir.\n");
                        printf("\n");
                    }
                } else {
                    printf("Árvore não criada\n");
                    printf("\n");
                }
                break;
            }
            case 7: {
                if (tree != NULL) {
                    abbEsvazia(&tree, cmp);
                    if (tree == NULL) {
                        printf("Árvore esvaziada com sucesso\n");
                    } else {
                        printf("Erro ao esvaziar a árvore\n");
                    }
                } else {
                    printf("Árvore já está vazia\n");
                }
                printf("\n");
                break;
            }
            case 0: {
                printf("Sistema encerrado com sucesso!\n");
                return 0;
            }
            default: {
                printf("Opção inválida\n");
                printf("\n");
                break;
            }
        }
    } while (TRUE);
}