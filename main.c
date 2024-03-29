#include <stdio.h>
#include <stdlib.h>
#include "Arvore_AVL.h"
int main()
{
    pDescArvore desc = criarArvore();
    insertNoh(desc, alocaInt(150), compInt);
    insertNoh(desc, alocaInt(100), compInt);
    insertNoh(desc, alocaInt(200), compInt);
    insertNoh(desc, alocaInt(99), compInt);
    insertNoh(desc, alocaInt(110), compInt);
    insertNoh(desc, alocaInt(109), compInt);
    insertNoh(desc, alocaInt(98), compInt);

    printf("\n");
    printf("\n");
    //printf("Removeu: %d", removeInfo(desc, alocaInt(110), compInt));
    printf("\n");
    printf("\n");
    imprimeArvore(desc, printaInt);
    printf("\n");    printf("\n");
    desenhaArvore(desc, printaInt);
}
