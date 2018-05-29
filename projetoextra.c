#include <stdio.h>

int quebraN()
{
	unsigned long long int n, vet, x, i=0;

	printf("Digite um 'N':\n");
	scanf("%llu", &n);
	printf("Esse eh o 'N':%llu\n", n);

	for (i = 2; i < n; ++i)
	{
		if(n % i == 0)
		{
			vet = i;
			break;
		}
	}

	x= n/vet;

	printf("\nO produto dos fatores primos que resultam em n: %llu * %llu!\n", vet, x);

	return 0;
}

int mutiplicar()
{
    unsigned long long int x , y, z;

    printf("Digite dois primos:\n");
    scanf("%llu %llu", &x, &y);
    printf("%llu %llu\n", x, y);

    z= x*y;
    printf("\nO produto dos numeros %llu e %llu eh: %llu\n", x, y, z);
    
    return 0;
}

int main()
{
	int escolha;
	printf("1- Multiplicar Primos\n2- Quebrar 'N'\nDigite uma opcao:\n");
	scanf("%d", &escolha);
	switch(escolha)
	{
		case 1:
			printf("\nMultiplicar Primos\n");
			mutiplicar();
			break;
		case 2:
			printf("\nQuebrar 'N'\n");
			quebraN();
			break;
		default:
			printf("Opcao invalida!\n");

	}
	return 0;
}