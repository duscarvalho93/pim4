#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> 
#define TAMMAX 100

// Propriedades do teatro
char 			TeatroNome[] = "Municipal";
float			TeatroValor = 10.00;

// Variaveis de opções
int				OpcaoPrincipal = 0;


// Controle das peças
char 			PecaUmNome[TAMMAX] = "Nao definida";
float			PecaUmValor;
char 			PecaDoisNome[TAMMAX] = "Nao definida";
float			PecaDoisValor;
char 			PecaTresNome[TAMMAX] = "Nao definida";
float			PecaTresValor;
int				OpcaoPeca = 0;
void DefinirPecas(){
	do {
		system("cls");
    	printf(" =========== Em qual sala deseja definir uma peca? =========== \n\n");
    	printf("\t 1 - Sala 1\n");
		printf("\t 2 - Sala 2\n");
		printf("\t 3 - Sala 3\n");
		printf("\t 4 - Voltar ao menu principal\n");
		printf(" ============================================== \n\n");
		scanf("%d", &OpcaoPeca);
		setbuf(stdin, NULL);
		
		if(OpcaoPeca==1){
			printf("\nDigite o nome da peca: ");
			fgets(PecaUmNome, TAMMAX, stdin);
			printf("\nDigite o valor da peca: ");
			scanf("%f", &PecaUmValor);
			OpcaoPeca = 0;		
		} else if(OpcaoPeca==2){
			printf("\nDigite o nome da peca: ");
			fgets(PecaDoisNome, TAMMAX, stdin);
			printf("\nDigite o valor da peca: ");
			scanf("%f", &PecaDoisValor);
			OpcaoPeca = 0;		
		} else if(OpcaoPeca==3){
			printf("\nDigite o nome da peca: ");
			fgets(PecaDoisNome, TAMMAX, stdin);
			printf("\nDigite o valor da peca: ");
			scanf("%f", &PecaTresValor);
			OpcaoPeca = 0;			
		}
		

	} while(OpcaoPeca<4 || OpcaoPeca>4);		
}
void VerPecas(){
	system("cls");
	printf(" =========== Pecas em cartaz =========== \n\n");
	printf("%s (Sala 1) R$ %.2f \n\n", PecaUmNome, PecaUmValor);
	printf("%s (Sala 2) R$ %.2f \n\n", PecaDoisNome, PecaDoisValor);
	printf("%s (Sala 3) R$ %.2f \n\n", PecaTresNome, PecaTresValor);
	system("pause");
	printf(" ============================================== \n\n");	
}
// Fim do controle das peças

// Controle dos ingressos
void PrintLugares(){

	int numeroPoltrona = 1;
	printf("\t ===================== TELA ===================== \n\n");
	for(int count = 1; count <= 10; count++){
		printf("\t");
		for(int fileira = 1; fileira<=10; fileira++){
			printf(" %.3d ", numeroPoltrona);
			numeroPoltrona++;
		}
		printf("\n");		
	}
	printf("\n\n");
	system("pause");
}

int main (int argc, char** argv)
{    
    do {
    	
    	system("cls");
    	
    	printf(" =========== Bem-vindo ao teatro %s =========== \n\n", TeatroNome);
    	printf("\t 1 - Definir Pecas\n");
    	printf("\t 2 - Ver Pecas\n");
		printf("\t 3 - Comprar Ingresso\n");
		printf("\t 4 - Cancelar Ingresso\n");
		printf("\t 5 - Faturar\n");
		printf("\t 6 - Encerrar o Sistema\n");
		printf("\n ============================================== \n\n");
		
		scanf("%d", &OpcaoPrincipal);
		switch(OpcaoPrincipal){
			case 1:
				DefinirPecas();
				break;
			case 2:
				VerPecas();
				break;
		}
    	
	} while(OpcaoPrincipal!=6);
	
	system("exit");
    return (0);
}
