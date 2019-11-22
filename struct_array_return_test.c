#include <stdio.h>
#include <stdlib.h>

struct Teste {
    int numero;
};

struct Teste* setArray();

int main() {
    struct Teste* testes = malloc(sizeof(struct Teste) * 2);
    
    testes = setArray();
    
    printf("numero 1: %d \nnumero 2: %d", testes[0].numero, testes[1].numero);
}

struct Teste* setArray() {
    struct Teste* aa = malloc(sizeof(struct Teste) * 2);
    struct Teste a, b;
    
    a.numero = 1;
    b.numero = 2;
    
    aa[0] = a;
    aa[1] = b;
    
    return aa;
}
