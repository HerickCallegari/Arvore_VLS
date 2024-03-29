#include "utils.h"

#define ESPACO 5
// ############################### STRUCT ###############################
typedef struct NohArvoreAVL NohArvore;
typedef NohArvore* pNohArvore;

typedef struct DescritorArvoreAVL DescArvore;
typedef DescArvore* pDescArvore;


struct NohArvoreAVL{
    void* info;
    pNohArvore direita;
    pNohArvore esquerda;
    int FB;
};

struct DescritorArvoreAVL {
    pNohArvore raiz;
    int quantidade;
};

// ############################### Cabeçalhos ###############################

typedef int (*FuncaoComparacao) ( void*, void*);

typedef void (*FuncaoImpressao) ( void* );

pDescArvore criarArvore();

pNohArvore RightRotate(pNohArvore raiz);

pNohArvore LeftRotate(pNohArvore raiz);

int FBNoh(pNohArvore raiz);

pNohArvore Balance(pNohArvore raiz);

pNohArvore insertNohRecursivo(pNohArvore raiz, void* info, FuncaoComparacao fcp);

void insertNoh ( pDescArvore arvore, void* info, FuncaoComparacao fcp);

void imprimeArvoreRecursivo( pNohArvore raiz, FuncaoImpressao fip);

void imprimeArvore( pDescArvore arvore, FuncaoImpressao fip);

int alturaNoh ( pNohArvore raiz);

int alturaArvore ( pDescArvore arvore);

int FBNoh ( pNohArvore raiz );

pNohArvore Balance(pNohArvore raiz);

pNohArvore RightRotate(pNohArvore raiz);

pNohArvore LeftRotate(pNohArvore raiz);

pNohArvore LeftRotate(pNohArvore raiz);

pNohArvore DoubleRigthRotate(raiz);

pNohArvore DoubleLeftRotate(raiz);

void desenhaArvore(pDescArvore arvore, FuncaoImpressao fip);

void desenhaArvoreRecursivo(pNohArvore raiz, int depth, char* path,int rigth, FuncaoImpressao fip );

// ############################### implementações ###############################

// ------------------------------ free -----------------------------------------------
void freeNoh(pNohArvore raiz) {
    free(raiz->esquerda);
    free(raiz->direita);
    free(raiz->info);
    free(raiz);
}


//------------------------------- Instaciar -------------------------------------------

pDescArvore criarArvore() {
    pDescArvore desc = malloc(sizeof(DescArvore));
    desc->quantidade = 0;
    desc->raiz = NULL;
    return desc;
}

//------------------------------- Insert ---------------------------------------------

pNohArvore insertNohRecursivo(pNohArvore raiz, void* info, FuncaoComparacao fcp) {

    // Estrutura de inserção
    if (raiz == NULL) {
            //para teste
        pNohArvore noh = malloc(sizeof(NohArvore));
        noh->info = info;
        noh->FB = 0;
        noh->direita = NULL;
        noh->esquerda = NULL;
        return noh;
    }
    else if ( fcp ( info, raiz->info ) > 0) {
            //para teste
            //printf("\ndireita");
        raiz->direita = insertNohRecursivo(raiz->direita, info, fcp);
    }
    else if ( fcp ( info, raiz->info ) <= 0) {
            //para teste
            //printf("\nesquerda");
        raiz->esquerda = insertNohRecursivo(raiz->esquerda, info, fcp);
    }
    BalanceFB(raiz);
    return Balance(raiz);

}

void insertNoh ( pDescArvore arvore, void* info, FuncaoComparacao fcp) {
    arvore->raiz = insertNohRecursivo(arvore->raiz, info, fcp);
}

//------------------------------- print ---------------------------------------------

void imprimeArvoreRecursivo( pNohArvore raiz, FuncaoImpressao fip) {
    if ( raiz != NULL)
        fip(raiz->info);

    if ( raiz->direita != NULL) {
        printf(", ");

        imprimeArvoreRecursivo(raiz->direita, fip);
    }
    if ( raiz->esquerda != NULL) {
        printf(", ");
        imprimeArvoreRecursivo(raiz->esquerda, fip);
    }
}

void imprimeArvore( pDescArvore arvore, FuncaoImpressao fip) {
    printf("\nArvore: ");
    imprimeArvoreRecursivo(arvore->raiz, fip);
}

void desenhaArvoreRecursivo(pNohArvore raiz, int depth, char *path, int right, FuncaoImpressao fi) {

    if (raiz == NULL)
        return;

    depth++;

    desenhaArvoreRecursivo(raiz->direita, depth, path, 1, fi);

    path[depth-2] = 0;

    if(right)
        path[depth-2] = 1;

    if(raiz->esquerda)
        path[depth-1] = 1;

    printf("\n");
    int i;
    for(i=0; i<depth-1; i++)
    {
      if(i == depth-2)
          printf("+");
      else if(path[i])
          printf("|");
      else
          printf(" ");

      int j;
      for(j=1; j<ESPACO; j++)
      if(i < depth-2)
          printf(" ");
      else
          printf("-");
    }

    fi(raiz->info);
    printf("[%d]", raiz->FB);

    for(i=0; i<depth; i++)
    {
      if(path[i])
          printf(" ");
      else
          printf(" ");

      int j;
      for(j=1; j<ESPACO; j++)
          printf(" ");
    }

    desenhaArvoreRecursivo(raiz->esquerda, depth, path, 0, fi);
}

void desenhaArvore(pDescArvore arvore, FuncaoImpressao fi) {
    char path[255] = {};

    desenhaArvoreRecursivo(arvore->raiz, 0, path, 0, fi);
    printf("\n");
}


//--------------------------- heigth --------------------------------
int alturaNoh ( pNohArvore raiz) {
    if ( raiz == NULL) {
        return 0;
    }

    int hDir = 1 + alturaNoh(raiz->direita);
    int hEsq = 1 + alturaNoh(raiz->esquerda);

    return hDir >= hEsq ? hDir: hEsq;
}

int alturaArvore ( pDescArvore arvore) {
    return alturaNoh (arvore->raiz);
}

//-------------------------- FB -------------------------------------

int FBNoh ( pNohArvore raiz ) {
    if ( raiz->direita != NULL && raiz->esquerda != NULL) {
        return alturaNoh(raiz->direita) - alturaNoh(raiz->esquerda);
    }
    else if ( raiz->direita != NULL ) {
        return alturaNoh(raiz->direita);
    }
    else if ( raiz->esquerda != NULL ) {
        return -alturaNoh(raiz->esquerda);
    }
    else
        return 0;
}

void BalanceFB( pNohArvore raiz) {
    if ( raiz != NULL)
        raiz->FB = FBNoh(raiz);

    if ( raiz->direita != NULL) {
        BalanceFB(raiz->direita);
    }
    if ( raiz->esquerda != NULL) {
        BalanceFB(raiz->esquerda);
    }
}


//-------------------------- Balance ---------------------------------

pNohArvore Balance(pNohArvore raiz) {
    BalanceFB(raiz);
    if ( raiz->FB > 1 && raiz->direita->FB == -1) { // Rotacao dupla Esquerda
        return DoubleLeftRotate(raiz);
    } else if(raiz->FB < -1 && raiz->esquerda->FB == 1) { // Rotacao dupla Direita
        return DoubleRigthRotate(raiz);
    } else if ( raiz->FB > 1 ) { // Rotacao direita
        return LeftRotate (raiz);
    } else if ( raiz->FB < -1 ){ // Rotacao esquerda
       return RightRotate(raiz);
    } else { // esta balanceado
            BalanceFB(raiz);
        return raiz;
    }
}

pNohArvore RightRotate(pNohArvore raiz) {
    pNohArvore u = raiz->esquerda;

    if ( u->direita != NULL) {
        raiz->esquerda = u->direita;
    } else {
        raiz->esquerda = NULL;
    }

    u->direita = raiz;

    BalanceFB(raiz);
    return u;
}

pNohArvore LeftRotate(pNohArvore raiz) {
    pNohArvore u = raiz->direita;

    if ( u->esquerda != NULL ) {
    raiz->direita = u->esquerda;
    } else {
    raiz->direita = NULL;
    }

    u->esquerda = raiz;

    BalanceFB(raiz);
    return u;
}

pNohArvore DoubleRigthRotate(pNohArvore p) {
    pNohArvore u =  p->esquerda;
    pNohArvore v = u->direita;

    if ( v->esquerda != NULL)
        u->direita = v->esquerda;
    else
        u->direita = NULL;

    v->esquerda = u;
    p->esquerda = v;

    if ( v->direita != NULL)
        p->esquerda = v->direita;
    else
        p->esquerda = NULL;

    v->direita = p;

    BalanceFB(v);
    return v;
}

pNohArvore DoubleLeftRotate(pNohArvore p) {
    pNohArvore z = p->direita;
    pNohArvore y = z->esquerda;

    //Primeira operacao
    if (y->direita != NULL)
        z->esquerda = y->direita;
    else
        z->esquerda = NULL;

    y->direita = z;
    p->direita = y;

    //Segunda operacao
    if ( y->esquerda != NULL)
        p->direita = y->esquerda;
    else
        p->direita = NULL;

    y->direita = p;

    BalanceFB(y);
    return y;
}

//-------------------------- FindBy ---------------------------------
pNohArvore proxLeaf(pNohArvore raiz, void* info, FuncaoComparacao fcp) {
    if (raiz == NULL) {
            printf("raiz é nula");
        return NULL;
    }

    if ( raiz->direita != NULL && fcp(raiz->info, info) < 0) {
            return raiz->direita;
    }

    if ( raiz->esquerda != NULL && fcp( raiz->info, info ) > 0) {
            return raiz->esquerda;

    }

    return NULL;
}


pNohArvore findByRecursivo(pNohArvore raiz, void* info, FuncaoComparacao fcp) {
    if (raiz == NULL) {
        return NULL; // Se raiz for nulo, não há mais nó para procurar
    }

    // Verifica se a raiz atual corresponde ao valor buscado
    if (fcp(raiz->info, info) == 0) {
        return raiz;
    }

    pNohArvore prox = proxLeaf(raiz, info, fcp);

    return findByRecursivo(prox, info, fcp);

}



pNohArvore findBy(pDescArvore arvore, void* info, FuncaoComparacao fcp) {
    return findByRecursivo(arvore->raiz, info, fcp);;
}



//---------------------- isLeaf ---------------------------------------

int isLeaf(pNohArvore raiz) {
    if ( raiz->direita == NULL && raiz->esquerda == NULL ) {
    return 1;
    }else {
    return 0;
    }
}

//--------------------- Remove ---------------------------------------

pNohArvore removeInfoRecursivo(pNohArvore raiz, void* info, FuncaoComparacao fcp){
    BalanceFB(raiz);
    //caso a raiz seja nula
    if (raiz == NULL) {
            printf("\nNulo\n");
        return NULL;
    }

    if ( raiz->esquerda != NULL && fcp(info, raiz->info) < 0 ) {
        raiz->esquerda = removeInfoRecursivo(raiz->esquerda, info, fcp);
    }
    else if ( raiz->direita != NULL && fcp(info, raiz->info ) > 0 ) {
        raiz->direita = removeInfoRecursivo(raiz->direita, info, fcp);
    }
    // Primeiro caso: se o nó encontrado é uma folha

    if (fcp(raiz->info, info) == 0 && isLeaf(raiz) == 1 ) {
            printaInt(raiz->info);
                    /*
                    desc
                     |
                      0
                    /   \
                  -5     1
                  / \     \
                -6  -3     3
                    / \   /
                  -4  -1 2
                       /
                      -2 <- esse por exemplo

                    */
        freeNoh(raiz);
        return NULL;
    }

    // se o nó nao é folha
    if ( fcp(raiz->info, info) == 0 && isLeaf(raiz) == 0) {
            // caso 3: é uma raiz com 2 filhos
        if ( raiz->direita != NULL && raiz->esquerda != NULL) {
                /*
                    desc
                      |
                      0 <- esse por exemplo
                    /   \
                  -5     1
                  / \     \
                -6  -3<PNR 2
                    / \     \
                  -4  -1<NR  3
                       /
                      -2
                Neste caso o ideal é procurar o nó mais proximo desta raiz com 2 filhos
                que por padrao deifinimos que sera o à esquerda e mais a direita
                possivel neste caso o -1
                    */
                        //PNR
            pNohArvore preNewRoot = raiz->esquerda;
            pNohArvore newRoot = preNewRoot;

            while (newRoot->direita != NULL) {
                preNewRoot = newRoot;
                newRoot = newRoot->direita;
            }

            if ( newRoot != preNewRoot && newRoot->esquerda != NULL ) {
                preNewRoot->direita = newRoot->esquerda;
                newRoot->direita = raiz->direita;
                newRoot->esquerda = raiz->esquerda;
            }

            if( newRoot == preNewRoot) {
                newRoot->direita = raiz->direita;
            }


            //para teste
            printf("\npreNewRoot: ");
            printaInt(preNewRoot->info);
            printf("\nNewRoot: ");
            printaInt(newRoot->info);
            printf("\nraiz: ");
            printaInt(raiz->info);
            printf("\n");

            raiz->direita = NULL;
            raiz->esquerda = NULL;
            free(raiz);

            return newRoot;

        }

        // caso 2: é uma raiz com 1 filho
        else if (raiz->direita != NULL && raiz->esquerda == NULL) {
                    /*
                    desc
                     |
                      0
                    /   \
                  -5     1
                  / \     \
                -6  -3     2 <- esse por exemplo
                    / \     \
                  -4  -1     3
                       /
                      -2

                    */
            pNohArvore aux = raiz->direita;
            raiz->direita = NULL;
            freeNoh(raiz);
            return aux;

        }

        // caso 2: é uma raiz com 1 filho
        else if (raiz->direita == NULL && raiz->esquerda != NULL) {
                     /*
                    desc
                     |
                      0
                    /   \
                  -5     1
                  / \     \
                -6  -3     2 - 3
                    / \
                  -4  -1 <- esse por exemplo
                       /
                      -2

                    */
            pNohArvore aux = raiz->esquerda;
            raiz->esquerda = NULL;
            freeNoh(raiz);
            return aux;
        }

        else { printf("ERRO GRAVE!!!!");}
    }

    BalanceFB(raiz);
    return raiz;
}

int removeInfo(pDescArvore arvore, void* info, FuncaoComparacao fcp) {
    if ( findBy(arvore, info, fcp) == NULL) {
            printf("oi");
        return 0;
    } else {
        arvore->raiz = removeInfoRecursivo(arvore->raiz, info, fcp);
        arvore->quantidade--;
        BalanceFB(arvore->raiz);
        return 1;
    }
}
