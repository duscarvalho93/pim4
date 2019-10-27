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
char 			PecaUmNome[TAMMAX] = "Peça não definida";
float			PecaUmValor;
char 			PecaDoisNome[TAMMAX] = "Peça não definida";
float			PecaDoisValor;
char 			PecaTresNome[TAMMAX] = "Peça não definida";
float			PecaTresValor;
int				OpcaoPeca = 0;

// Função menu
void menu();


// Funções para setas nos menus

#define tclENTER  13
#define tclUP     72
#define tclDOWN   80
#define SETA	  62

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
				if(Y>LastLine){ //se passar da ultima do menu volta pro topo
					Y=OptFY;
					Option=1;
				}
				gotoxy(OptX-4,Y); printf("%c", SETA);
				break;
		}
		
	} while (decimalChar != tclENTER);
	return(Option);
}

// Fim das funções de seta dos menus

// Funções de controle das peças
void DefinirSalaIn(char NomeSala[TAMMAX]){
	gotoxy(20,2);printf(" ========== %s =============\n", NomeSala);
	gotoPrintMenu(20,4, " Insira os dados da peça");
	gotoPrintMenu(20,6, " Nome: ");
	gotoPrintMenu(20,7, " Valor: ");
	cursor(1);
	gotoxy(27, 6);
}
void DefinirSalaOut(char NomeSala[TAMMAX], char NomePeca[TAMMAX], float ValorPeca){
	gotoxy(21, 10);printf("%s definida", NomeSala);
	gotoxy(21, 11);printf("Nome: %s", NomePeca);
	gotoxy(21, 12);printf("Valor: R$ %.2f \n\n\n", ValorPeca);
	cursor(0);
}
void DefinirPecas(){
	do {
		
		system("cls");
		setbuf(stdin, NULL);
		
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
		
		gotoxy(27,20);printf("Sala 1: %s R$ %.2f",PecaUmNome,PecaUmValor);
		gotoxy(27,21);printf("Sala 2: %s R$%.2f",PecaDoisNome,PecaDoisValor);
		gotoxy(27,22);printf("Sala 3: %s R$%.2f",PecaTresNome,PecaTresValor);
		
		OpcaoPeca = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
		
		system("cls");
			
		switch(OpcaoPeca){
			case 1:
				DefinirSalaIn("SALA 1");
				fgets(PecaUmNome, TAMMAX, stdin);
				PecaUmNome[strlen(PecaUmNome)-1] = '\0';
				cursor(1);
				gotoxy(28,7);
				scanf("%f", &PecaUmValor);
				DefinirSalaOut("SALA 1", PecaUmNome, PecaUmValor);
				OpcaoPeca = 0;
				system("pause");
			break;
			case 2:
				DefinirSalaIn("SALA 2");
				fgets(PecaDoisNome, TAMMAX, stdin);
				PecaDoisNome[strlen(PecaDoisNome)-1] = '\0';
				cursor(1);
				gotoxy(28,7);
				scanf("%f", &PecaDoisValor);
				DefinirSalaOut("SALA 2", PecaDoisNome, PecaDoisValor);
				OpcaoPeca = 0;
				system("pause");
			break;		
			case 3:
				DefinirSalaIn("SALA 3");
				fgets(PecaTresNome, TAMMAX, stdin);
				PecaTresNome[strlen(PecaTresNome)-1] = '\0';
				cursor(1);
				gotoxy(28,7);
				scanf("%f", &PecaTresValor);
				DefinirSalaOut("SALA 3", PecaTresNome, PecaTresValor);
				OpcaoPeca = 0;
				system("pause");
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

int escolherPeca(){
	gotoPrintMenu(20,2, " =========== Escolha uma peça  ===========");
	int OptX = 33; // Coordenada X que vai começar o print
	int OptFY = 5; // Coordenada Y para a linha da primeira opção
	int OptSpc = 3; // Espaçamento entre as opções
	int OptTotal = 4; // Total de opções do menu
	int mY = OptFY;                                              
	gotoxy(OptX,mY);printf("%s", PecaUmNome);
	gotoxy(OptX,mY+=OptSpc);printf("%s", PecaDoisNome);
	gotoxy(OptX,mY+=OptSpc);printf("%s", PecaTresNome);
	gotoPrintMenu(OptX,mY+=OptSpc, "Voltar ao menu principal");
	int peca;
	peca = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
	return peca;
}

void ComprarIngresso(){
	system("cls");
	
	int peca;
	
	peca = escolherPeca();
}

// Fim do controle dos ingressos

void bye(){
	system("cls");
	gotoPrintMenu(32, 10, "Até a próxima");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void menu(){//Menu inicial
	
	system("cls");
	localeP;
	system("color F0");
	
	int Option;
    
	do {
		
		system("cls");
		
		gotoPrintMenu(20,2, " =========== Bem-vindo ao teatro  ===========");
		
		int OptX = 33; // Coordenada X que vai começar o print
		int OptFY = 5; // Coordenada Y para a linha da primeira opção
		int OptSpc = 3; // Espaçamento entre as opções
		int OptTotal = 6; // Total de opções do menu
		    	
    	int mY = OptFY;                                              
		gotoPrintMenu(OptX,mY, "Definir Peças");             //
    	gotoPrintMenu(OptX,mY+=OptSpc, "Ver Pecas");                 //
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
			case 3:
				ComprarIngresso();
			break;
			case 6:
				bye();
				Option = 7;
			break;
		}
				
	} while(Option<=6);
	
	
}//Fim do Menu Inicial
int main (int argc, char** argv)
{
    HWND wh = GetConsoleWindow();
    MoveWindow(wh, 200, 100, 900, 400, TRUE);
    
	system("cls");
	menu();
	system("exit");
    return (0);
}
