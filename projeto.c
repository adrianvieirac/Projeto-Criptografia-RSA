#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long int ULLI;

ULLI mdcDeEuclides(ULLI a, ULLI b)
{
    ULLI resto;
    resto = a%b;
    while(resto!=0)
    {
        a = b;
        b = resto;
        resto = a%b;         
    }

    return b;
}

ULLI acharE(ULLI tn)
{
    ULLI e;
    e= 2;
    while(mdcDeEuclides(tn, e) != 1)
    {
        e++;
    }
    return e;
}


ULLI exponenciacaoModular(ULLI a, ULLI e, ULLI m)
{
    if(e==0)
    {
      return 1;
    }
    else if(e%2==0)
    {
    long int x = exponenciacaoModular(a,e/2,m);
    return (x*x)%m; 
    }
    else
    {
     return (a%m*exponenciacaoModular((a%m)*(a%m),(e-1)/2,m))%m;
    }
}

ULLI verificarPrimo(ULLI p)
{
    ULLI i;

    for(i = 2; i < p; i++)
    {
        if(p%i == 0)
        {
          return 0;
        }
    }
        return 1;
}

ULLI inversoMutiplicativo(ULLI e, ULLI tn)
{
    printf("\nTestando inversos...\n");
    ULLI d;
    for(d=1;d<=tn;d++)
    {
        //comparando se e*d mod tn == 1
        if((e*d)%tn==1)
        {
            printf("Inverso 'd':%llu\n", d);
            return d;
        }
    }
}

ULLI gerarChave(void)
{
    ULLI p, q, n, tn, e;

    //recebendo P e Q
    DENOVO: printf("Digite P e Q:\n");
    scanf("%llu %llu", &p, &q);

    //verificando se sao primos

    if(verificarPrimo(p) == 0 && verificarPrimo(q) == 0 )
    {
        printf("Ocorreu um erro! Por gentileza, digite 'P' e 'Q' novamente.\n");
        goto DENOVO;
    }

    if(verificarPrimo(p) == 0)
    {
        printf("Ocorreu um erro! Por gentileza, digite 'P' novamente.\n");
        goto DENOVO;
    }

    if(verificarPrimo(q) == 0)
    {
        printf("Ocorreu um erro! Por gentileza, digite 'Q' novamente.\n");
        goto DENOVO;
    }

    // calculando n e tn
    n= p*q;
    tn= (p-1)*(q-1);

    //mostrando um valor para E
    CACATUA: printf("\nUm valor possível para 'E': %llu\nDigite esse valor, ou outro 'E' de sua escolha:\n", acharE(tn));
    scanf("%llu", &e);
    if (mdcDeEuclides(e, tn) != 1)
    {
    	printf("\nOcorreu um erro! Por gentileza, digite 'E' novamente.\n");
    	goto CACATUA;
    }

    printf("Essas sao as chaves publicas:\n%llu %llu\n", n, e);

    //salvando em arquivo txt
    FILE *chaves;
    chaves = fopen("chavesPublicas.txt", "w");
    fprintf(chaves,"%llu %llu", n, e);
    fclose(chaves);
    printf("\nChaves salvas em ChavesPublicas.txt\n");
    return 0;
}

ULLI criptografar(void) 
{
    ULLI i;
    
    //receber frase
    char frase[100];
    printf("Digite a frase\n");
    setbuf(stdin, NULL);
    fgets(frase, 100, stdin);
    
    //passar para ascii
    ULLI fraseAscii[100];
    for (i = 0; i < strlen(frase) - 1; i++) 
    {
        fraseAscii[i] = frase[i];
    }

    //ler chaves
    ULLI chave1, chave2;
    printf("\nDigite as chaves publicas\n");
    scanf("%llu %llu", &chave1, &chave2);

    //fazendo a exponenciação modular
    for (i = 0; i < strlen(frase) - 1; i++) 
    {
        fraseAscii[i] = exponenciacaoModular(fraseAscii[i], chave2, chave1);
    }

    //mostrando na tela
    printf("\nFrase criptografada\n");
    for (i = 0; i < strlen(frase) -1; ++i)
    {
        printf("%llu ", fraseAscii[i]);
    }
    printf("\n");

    //guardando em um arquivo txt
    printf("\nFrase Salva em fraseCriptografada.txt\n");
    FILE *fraseCriptografada;
    fraseCriptografada = fopen("fraseCriptografada.txt", "w");
    for (i = 0; i < strlen(frase)-1; ++i)
    {
        fprintf(fraseCriptografada, "%llu ", fraseAscii[i]);
    }
    fclose(fraseCriptografada);
    return 0;
}

ULLI descriptografar(void) 
{
    int i;
    ULLI fraseCripto[100]= {0};
    ULLI p, q, e, tn, chave1, chave2;

    //recebendo P, Q e E
    printf("Digite P, Q e E:\n");
    scanf("%llu %llu %llu", &p, &q, &e);

    chave1 = p*q;
    tn = (p-1)*(q-1);

    //calculando D
    chave2 = inversoMutiplicativo(e, tn);

    //receber frase criptografada
    char textAux[100];
    printf("\nDigite Tamanho da frase:\n");
    int tam;
    scanf("%d", &tam);
    
    printf("\nDigite a frase criptografada:\n");
    for (i = 0; i < tam; ++i)
    {
        scanf("%llu", &fraseCripto[i]);
    }

    //fazendo a exponenciação modular
    for (i = 0; i < tam; i++) 
    {
        fraseCripto[i] = exponenciacaoModular(fraseCripto[i], chave2, chave1);
    }

    //tranformando em caractere
    for (i = 0; i < tam; ++i)
    {
        textAux[i] = fraseCripto[i];
    }

    //mostra frase descrip em ascii
    printf("\nFrase descriptografada em ASCII:\n");
    for (i = 0; i < tam; ++i)
    {
        printf("%llu ", fraseCripto[i]);
    }printf("\n\n");

        //frase descriptografada
        printf("\nFrase descriptografada:\n");
    for(i = 0; i < tam; ++i)
    {
        printf("%c", textAux[i]);
    }printf("\n");

    //savar frase em um arquivo txt
    printf("\nFrase salva em fraseDesencriptada.txt\n");
    FILE *fraseDes;
    fraseDes = fopen("fraseDesencriptada.txt", "w");
    for(i = 0; i < tam; ++i)
    {
        fprintf(fraseDes,"%c", textAux[i]);
    }printf("\n");
    fclose(fraseDes);

    return 0;
}

int main(void)
{
    int escolha;
    do
    {
        printf("Por favor escolha uma das opcoes:\n1 - Gerar chave publica, 2 - Criptografar, 3 - Descriptografar.\nDigite uma Opcao:\n");
        scanf("%d", &escolha);
                printf("\nOpcao escolida:\n");
        switch (escolha)
        {
           case 1:
             printf("Gerar chave publica.\n\n");
             gerarChave();
           break;

           case 2:
             printf("Criptografar.\n\n");
             criptografar();
           break;

           case 3:
             printf("Descriptografar.\n\n");
             descriptografar();
           break;

           default:
             printf("Opcao invalida!\n\n");
        }
    }
    while(escolha!= 3);

    return 0;
}
