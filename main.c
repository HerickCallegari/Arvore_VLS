#include <stdio.h>
#include <stdlib.h>
#include "Arvore_AVL.h"
int main()
{
    pDescArvore desc = criarArvore();
    insertNoh(desc, alocaInt(150), compInt);
    insertNoh(desc, alocaInt(125), compInt);
    insertNoh(desc, alocaInt(200), compInt);
    insertNoh(desc, alocaInt(121), compInt);
    insertNoh(desc, alocaInt(126), compInt);
    insertNoh(desc, alocaInt(190), compInt);
    insertNoh(desc, alocaInt(201), compInt);
    insertNoh(desc, alocaInt(120), compInt);
    insertNoh(desc, alocaInt(122), compInt);
    insertNoh(desc, alocaInt(123), compInt);
    printf("\n");
    printf("\n");
    imprimeArvore(desc, printaInt);
    printf("\n");    printf("\n");
    desenhaArvore(desc, printaInt);


}
