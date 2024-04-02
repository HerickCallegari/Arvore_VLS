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

pNohArvore BalanceRecursivo(pNohArvore raiz);

pNohArvore RightRotate(pNohArvore raiz);

pNohArvore LeftRotate(pNohArvore raiz);

pNohArvore DoubleRigthRotate(pNohArvore raiz);

pNohArvore DoubleLeftRotate(pNohArvore raiz);

void desenhaArvore(pDescArvore arvore, FuncaoImpressao fip);

void desenhaArvoreRecursivo(pNohArvore raiz, int depth, char* path,int rigth, FuncaoImpressao fip );

pNohArvore preMaxNoh(pNohArvore raiz);

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
        raiz->direita = insertNohRecursivo(raiz->direita, info, fcp);
    }
    else if ( fcp ( info, raiz->info ) <= 0) {
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

pNohArvore BalanceRecursivo(pNohArvore raiz) {
    raiz->FB = FBNoh(raiz);
    if ( raiz->direita != NULL)
        raiz->direita = BalanceRecursivo(raiz->direita);

    if ( raiz->esquerda != NULL)
        raiz->esquerda = BalanceRecursivo(raiz->esquerda);

    return Balance(raiz);
}

pNohArvore Balance(pNohArvore raiz) {

    if ( raiz->FB > 1 && raiz->direita->FB == -1) { // Rotacao dupla Esquerda
        return DoubleLeftRotate(raiz);
    } else if(raiz->FB < -1 && raiz->esquerda->FB == 1) { // Rotacao dupla Direita
        return DoubleRigthRotate(raiz);
    } else if ( raiz->FB > 1 ) { // Rotacao direita
        return LeftRotate (raiz);
    } else if ( raiz->FB < -1 ){ // Rotacao esquerda
       return RightRotate(raiz);
    } else { // esta balanceado
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
    //procura o Noh que se quer remover
    if ( fcp(info, raiz->info) > 0)
        raiz->direita = removeInfoRecursivo(raiz->direita, info, fcp);
    else if ( fcp(info, raiz->info) < 0)
        raiz->esquerda = removeInfoRecursivo(raiz->esquerda, info, fcp);
    else {
            //encontrou o noh
        printaInt(raiz->info);
        if ( isLeaf(raiz) == 1) { //caso nao tenha filhos
            freeNoh(raiz);
            return NULL;
        }
        else if ( raiz->direita != NULL && raiz->esquerda != NULL ) { //caso tenha 2 filhos
                // Funcao para encontrar o noh mais proximo da raiz desejada
            pNohArvore preNewRoot = preMaxNoh(raiz);
            pNohArvore newRoot = preNewRoot->direita;

                //caso o nó mais proximo da raiz nao seja uma folha
            if ( newRoot != NULL)
                preNewRoot->direita = newRoot->esquerda;
            else
                preNewRoot->direita = NULL;

                //faco que meu newNoh aponte para os mesmos Nohs da raiz
            newRoot->direita = raiz->direita;
            newRoot->esquerda = raiz->esquerda;

                //tiro as ligacoes da raiz com o resto da arvore para limpar adequadamente
            raiz->direita = NULL;
            raiz->esquerda = NULL;
            freeNoh(raiz);

                //Balanceia os Nohs afedatos e garante a integridade da arvore
            BalanceFB(preNewRoot);
            BalanceFB(newRoot);

            return newRoot;


        }
        else if ( raiz->direita != NULL ) {

                //Faz com que o codigo retorne a parna direita da raiz e garanta que a raiz seja adequadamente liberada
            pNohArvore aux = raiz->direita;
            raiz->direita = NULL;
            raiz->esquerda = NULL;
            freeNoh(raiz);

            return aux;
        }
        else if ( raiz->esquerda != NULL ) {
            printf("\nfilho a esquerda");

              //Faz com que o codigo retorne a parna esquerda da raiz e garanta que a raiz seja adequadamente liberada
            pNohArvore aux = raiz->esquerda;
            raiz->direita = NULL;
            raiz->esquerda = NULL;
            freeNoh(raiz);

            return aux;
        }
    }

  return raiz;
}


int removeInfo(pDescArvore arvore, void* info, FuncaoComparacao fcp) {
    if ( findBy(arvore, info, fcp) == NULL) {
            printf("nao achou");
        return 0;
    } else {
        arvore->raiz = removeInfoRecursivo(arvore->raiz, info, fcp);
        arvore->quantidade--;
        arvore->raiz = BalanceRecursivo(arvore->raiz);
        BalanceFB(arvore->raiz);
        return 1;
    }
}

pNohArvore preMaxNoh(pNohArvore raiz) {
    pNohArvore aux = raiz->esquerda;
    while ( aux->direita->direita != NULL) {
        aux = aux->direita;
    }
    return aux;
}
