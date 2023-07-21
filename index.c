#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int ano, mes, dia;
}Data;

typedef struct {
    Data nascimento;
    char nome [30];
}Dados;

void saida (Dados* perfis, int cont);
unsigned long int calcularDiferenca (Dados pessoa1, Dados pessoa2);
int diasDoMes (Data pessoa);

int main () {
    Dados *perfis;
    int usuarios;
    puts ("Insira a quantidade de usuarios: ");
    scanf ("%d", &usuarios);
    getchar ();
    perfis = (Dados*) malloc (usuarios * sizeof (Dados));

    for (int i = 0; i < usuarios; i++) {
        printf ("Insira o nome da pessoa %d\n", i + 1);
        fgets (perfis[i].nome, 30, stdin);
        printf ("Insira o dia/mes/ano de nascimento de %s", perfis[i].nome);
        scanf ("%d %d %d", &perfis[i].nascimento.dia, &perfis[i].nascimento.mes, &perfis[i].nascimento.ano);
        getchar ();
    }
    saida (perfis, usuarios);
    return 0;
}

void saida (Dados* perfis, int cont) {
    unsigned long int diferenca;
    for (int i = 0; i < cont; i++)
        for (int j = i + 1; j < cont; j++) {
            diferenca = calcularDiferenca (perfis [i], perfis [j]);
            printf ("A diferenca de idade em dias entre %s e %s e igual a %lu\n", perfis[i].nome, perfis[j].nome, diferenca);
            putchar ('\n');
        }
}

unsigned long int calcularDiferenca (Dados pessoa1, Dados pessoa2) {
    unsigned long int diasP1 = 0, diasP2 = 0;
    int aux;

    for (int ano = 0; ano < pessoa1.nascimento.ano; ano++) {
        if (ano % 4 == 0) {
            diasP1 += 366;
            continue;
        }
        diasP1 += 365;
    }

    for (int ano = 0; ano < pessoa2.nascimento.ano; ano++) {
        if (ano % 4 == 0) {
            diasP2 += 366;
            continue;
        }
        diasP2 += 365;
    }

    diasP1 += diasDoMes (pessoa1.nascimento) + pessoa1.nascimento.dia;
    diasP2 += diasDoMes (pessoa2.nascimento) + pessoa2.nascimento.dia;

    if (diasP2 > diasP1) {
        aux = diasP1;
        diasP1 = diasP2;
        diasP2 = aux;
    }

    return diasP1 - diasP2;
}

int diasDoMes (Data pessoa) {
    int dias = 0;
    switch (pessoa.mes) {
        case 12: dias+=30;
        case 11: dias+=31;
        case 10: dias+=30;
        case 9: dias+=31;
        case 8: dias+=31;
        case 7: dias+=30;
        case 6: dias+=31;
        case 5: dias+=30;
        case 4: dias+=31;
        case 3: dias+=28;
        case 2: dias+=31;
    }

    if (pessoa.mes > 2 && pessoa.ano % 4 == 0) {
        dias ++;
        return dias;
    }

    return dias;
}
