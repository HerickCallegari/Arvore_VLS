#include <stdio.h>
#include <stdlib.h>
#include "Arvore_AVL.h"
int main()
{
    pDescArvore desc = criarArvore();
    insertNoh(desc, alocaInt(5), compInt);
    insertNoh(desc, alocaInt(4), compInt);
    insertNoh(desc, alocaInt(3), compInt);
    printf("\n");
    imprimeArvore(desc, printaInt);

}
