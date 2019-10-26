#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#define TAMMAX 100

#define localeC setlocale(LC_ALL,"C");
#define localeP setlocale(LC_ALL,"Portuguese");

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

// Função menu
void menu();


// Funções para setas nos menus

#define tclENTER  13
#define tclUP     72
#define tclDOWN   80
#define SETA	  26

void gotoxy(int x,int y){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y}); // x=j (sao colunas) e y=i (sao as linhas)
}

void gotoPrintMenu(int x, int y, char txt[]){
	gotoxy(x,y);printf(txt);
}

void cursor (int x) { // mostra ou não o cursor do prompt
	switch (x) {
		case 0: { //ocultar cursor
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: { //apresentar cursor
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

int newMenuNav(int OptFY, int OptSpc, int OptX, int OpcTotal){
	char decimalChar;
	int LastLine = (OptFY+(OptSpc*(OpcTotal-1)));
	int Y = OptFY;
	int Option = 1;
	
	cursor(0);
	
	do {
		gotoxy(OptX-4,Y);printf("%c", SETA); //primeira seta (26 é o caractere '->')
		decimalChar=getch();
		gotoxy(OptX-4,Y); printf(" "); //limpa a seta quando muda de linha
			
		switch(decimalChar){
			case tclUP :
				Y -= OptSpc;
				Option--;
				if(Y<OptFY)  { //se passar da primeira opcao do menu volta pro inicio
					Y = LastLine;
					Option = 1;	
				}
				gotoxy(OptX-4,Y); printf("%c", SETA);
				break;
			case tclDOWN : // seta para baixo
				Y += OptSpc;//soma valor nas cordenadas para mudar linha
				Option++;
				if(Y>LastLine){ //se passar da primeira ultima do menu volta pro topo
					Y=OptFY;
					Option=OpcTotal;
				}
				gotoxy(OptX-4,Y); printf("%c", SETA);
				break;
		}
		
	} while (decimalChar != tclENTER);
	return(Option);
}

// Fim das funções de seta dos menus

// Funções de controle das peças
void DefinirPecas(){
	do {
		
		system("cls");
		
		gotoPrintMenu(10,2, " =========== Escolha as salas e suas respectivas peças ===========");
		
		int OptX = 33; // Coordenada X que vai começar o print
		int OptFY = 5; // Coordenada Y para a linha da primeira opção
		int OptSpc = 3; // Espaçamento entre as opções
		int OptTotal = 4; // Total de opções do menu
		    	
    	int mY = OptFY;
		gotoPrintMenu(OptX,mY, "Sala 1");
    	gotoPrintMenu(OptX,mY+=OptSpc, "Sala 2");
		gotoPrintMenu(OptX,mY+=OptSpc, "Sala 3");
		gotoPrintMenu(OptX,mY+=OptSpc, "Voltar ao menu principal");
		gotoPrintMenu(10,17, " ========== Nome das peças escolhidas e suas salas =============\n");
		printf("\nSala 1: %s R$%.2f",PecaUmNome,PecaUmValor);
		printf("\nSala 2: %s R$%.2f",PecaDoisNome,PecaDoisValor);
		printf("\nSala 3: %s R$%.2f",PecaTresNome,PecaTresValor);
		
		OpcaoPeca = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
		
		system("cls");
			
		switch(OpcaoPeca){
			case 1:
				printf("\t *Peça 1: Escolha a peça e seu valor*\n");
				printf("\nDigite o nome da peca: ");
				fgets(PecaUmNome, TAMMAX, stdin);
				printf("\n--Peça escolhida: %s",PecaUmNome);
				printf("\nDigite o valor da peca: ");
				scanf("%f", &PecaUmValor);
				printf("\n--Valor que será cobrado: R$%.2f",PecaUmValor);
				printf("\nPressione enter para continuar");
				OpcaoPeca = 0;
				getch();
//				DefinirPecas();
			break;
			case 2:
				printf("\t *Peça 2: Escolha a peça e seu valor*\n");
				printf("\nDigite o nome da peca: ");
				fgets(PecaDoisNome, TAMMAX, stdin);
				printf("\n--Peça escolhida: %s",PecaDoisNome);
				printf("\nDigite o valor da peca: ");
				scanf("%f", &PecaDoisValor);
				printf("\n--Valor que será cobrado: R$%.2f",PecaDoisValor);
				printf("\nPressione enter para continuar");
				OpcaoPeca = 0;
				getch();
//				DefinirPecas();
				break;		
			case 3:
				printf("\t *Peça 3: Escolha a peça e seu valor*\n");
				printf("\nDigite o nome da peca: ");
				fgets(PecaTresNome, TAMMAX, stdin);
				printf("\n--Peça escolhida: %s",PecaTresNome);
				printf("\nDigite o valor da peca: ");
				scanf("%f", &PecaTresValor);
      			printf("\n--Valor que será cobrado: R$%.2f",PecaTresValor);
      			printf("\nPressione enter para contuinuar");
				OpcaoPeca = 0;
				getch();
//				DefinirPecas();	
			break;		
		}
	} while(OpcaoPeca<4);
	menu();	
}
void VerPecas(){ // menu para ver as peças escolhidas
	system("cls");
	printf(" =========== Pecas em cartaz =========== \n\n");
	printf("%s (Sala 1) R$ %.2f \n\n", PecaUmNome, PecaUmValor);
	printf("%s (Sala 2) R$ %.2f \n\n", PecaDoisNome, PecaDoisValor);
	printf("%s (Sala 3) R$ %.2f \n\n", PecaTresNome, PecaTresValor);
	system("pause");
	printf(" ============================================== \n\n");	
	menu();
}
// Fim do controle das peças

// Controle dos ingressos
void PrintLugares(){

	int numeroPoltrona = 1;
	printf("\t ===================== TELA ===================== \n\n");
	int count;
	for(count = 1; count <= 10; count++){
		printf("\t");
		int fileira;
		for(fileira = 1; fileira<=10; fileira++){
			printf(" %.3d ", numeroPoltrona);
			numeroPoltrona++;
		}
		printf("\n");		
	}
	printf("\n\n");
	system("pause");
}

void menu(){//Menu inicial
	
	system("cls");
	localeP;
	system("color F0");
	
	int Option;
    
	do {
		
		gotoPrintMenu(20,2, " =========== Bem-vindo ao teatro  ===========");
		
		int OptX = 33; // Coordenada X que vai começar o print
		int OptFY = 5; // Coordenada Y para a linha da primeira opção
		int OptSpc = 3; // Espaçamento entre as opções
		int OptTotal = 6; // Total de opções do menu
		    	
    	int mY = OptFY;                                      //
		gotoPrintMenu(OptX,mY, "Definir Peças");             //
    	gotoPrintMenu(OptX,mY+=OptSpc, "Ver Pecas");         //
		gotoPrintMenu(OptX,mY+=OptSpc, "Comprar Ingresso");  // Opções do menu inicial
		gotoPrintMenu(OptX,mY+=OptSpc, "Cancelar Ingresso"); //
		gotoPrintMenu(OptX,mY+=OptSpc, "Faturar");           //
		gotoPrintMenu(OptX,mY+=OptSpc, "Encerrar o Sistema");//
		
		Option = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
	//Opções disponiveis até o momento	
		switch(Option){
			case 1:
				DefinirPecas();
				break;
			case 2:
				VerPecas();
				break;
		}
				
	} while(Option!=6);
	
	
}//Fim do Menu Inicial
int main (int argc, char** argv)
{
	system("cls");
	menu();
	system("exit");
    return (0);
}
