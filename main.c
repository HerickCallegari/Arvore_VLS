#include <stdio.h>
#include <stdlib.h>
#include "Arvore_AVL.h"
int main()
{
    pDescArvore desc = criarArvore();
    insertNoh(desc, alocaInt(0), compInt);
    insertNoh(desc, alocaInt(1), compInt);
    insertNoh(desc, alocaInt(2), compInt);
    insertNoh(desc, alocaInt(-1), compInt);
    insertNoh(desc, alocaInt(-2), compInt);
    printf("\n");
    imprimeArvore(desc, printaInt);

}
