int compInt ( void* info1, void* info2) {
     int* inteiro1 = (int*)info1;
     int* inteiro2 = (int*)info2;
    return *inteiro1 - *inteiro2;
}

void printaInt(void* info) {
    printf("%d", *(int*)info);
}

int* alocaInt(int info) {
    int* p = (int*)malloc(sizeof(int));
    *p = info;
    return p;
}
