#include "utils.h"
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

// ############################### implementações ###############################

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
            printf("\nincluiu");
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

    // verificação de propriedade
    raiz->FB = FBNoh(raiz);
    //BalancearArvore(raiz);
return Balance(raiz);

}

void insertNoh ( pDescArvore arvore, void* info, FuncaoComparacao fcp) {
    arvore->raiz = insertNohRecursivo(arvore->raiz, info, fcp);
}

//------------------------------- print ---------------------------------------------

void imprimeArvoreRecursivo( pNohArvore raiz, FuncaoImpressao fip) {
    if ( raiz != NULL) {
        fip(raiz->info);

        printf(" FB: %d", raiz->FB);
    }

    if ( raiz->direita != NULL) {
        printf("\nDireita: ");

        imprimeArvoreRecursivo(raiz->direita, fip);
    }
    if ( raiz->esquerda != NULL) {
        printf("\nEsquerda: ");
        imprimeArvoreRecursivo(raiz->esquerda, fip);
    }
}

void imprimeArvore( pDescArvore arvore, FuncaoImpressao fip) {
    printf("\nRaiz principal: ");
    imprimeArvoreRecursivo(arvore->raiz, fip);
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

//-------------------------- Balance ---------------------------------

pNohArvore Balance(pNohArvore raiz) {
    if ( raiz->FB > 1) {
        return LeftRotate (raiz);
    } else if ( raiz->FB < -1 ){
       return RightRotate(raiz);
    } else {
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
    raiz->FB = FBNoh(raiz);
    u->FB = FBNoh(raiz);
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
    raiz->FB = FBNoh(raiz);
    u->FB = FBNoh(raiz);
    return u;
}
