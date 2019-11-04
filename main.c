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
struct Peca  
{  
    char 		nome[TAMMAX];  
    float 		valor; 
    int 		lugares[100];
};

struct Peca 		Pecas[3];
int totalPecas		= 3;

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

// Colors
 void SetColor(int ForgC)
 {
     WORD wColor;

      HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
      CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
                 //Mask out all but the background attribute, and add in the forgournd     color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
 }
 // Fim colors

// Funções de controle das peças

void dataBaseSavePecas(){
	FILE * filePecas = NULL;
	
	filePecas = fopen("pecas.bin", "w");
	
	if(filePecas == NULL){
        printf("Houve um problema ao criar o arquivo pecas.bin.\n");
        exit(EXIT_FAILURE);
    }
    fwrite(Pecas, sizeof(struct Peca) * totalPecas, 1, filePecas);
    fclose(filePecas);
    
}

void dataBaseGetPecas(){
	FILE* filePecas;
    if ((filePecas = fopen("pecas.bin", "rb")) == NULL){
        dataBaseSavePecas();
    }
    fread(Pecas, sizeof(struct Peca) * totalPecas, 1, filePecas);
    fclose(filePecas);
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
		
		for(int i=0;i<totalPecas;i++){
			gotoxy(23,i+20);printf("Sala %d: %s R$ %.2f",i+1, Pecas[i].nome, Pecas[i].valor);	
		}
		
		OpcaoPeca = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
		
		if(OpcaoPeca<4){
			system("cls");
			
			int indPeca = OpcaoPeca-1;
			
			gotoxy(20,2);printf(" ========== SALA %d =============\n", OpcaoPeca);
			gotoPrintMenu(20,4, " Insira os dados da peça");
			gotoPrintMenu(20,6, " Nome: ");
			cursor(1);
			fgets(Pecas[indPeca].nome, TAMMAX, stdin);
			Pecas[indPeca].nome[strlen(Pecas[indPeca].nome)-1] = '\0';
			gotoPrintMenu(20,7, " Valor: ");
			cursor(1);
			scanf("%f", &Pecas[indPeca].valor);
			
			gotoxy(21, 10);printf("SALA %d definida", OpcaoPeca);
			gotoxy(21, 11);printf("Nome: %s", Pecas[indPeca].nome);
			gotoxy(21, 12);printf("Valor: R$ %.2f \n\n\n", Pecas[indPeca].valor);
			cursor(0);
			
			OpcaoPeca = 0;
			system("pause");			
		}
	
	} while(OpcaoPeca<4);
	dataBaseSavePecas();
}

void VerPecas(){ // menu para ver as peças escolhidas
	system("cls");
	gotoxy(10, 2);
	printf(" =========== Peças em cartaz =========== \n\n");
	for(int i=0; i<totalPecas;i++){
		gotoxy(12, i+4);
		printf("%s (Sala %d) R$ %.2f \n\n", Pecas[i].nome, i+1, Pecas[i].valor);
	}
	gotoxy(12, 12);
	printf("======================================= \n\n\n\n");	
	system("pause");
}
// Fim do controle das peças

// Controle dos ingressos

void PrintLugares(int lugares[100]){

	int numeroPoltrona = 1;
	printf("\t ===================== TELA ===================== \n\n");
	int count;
	for(count = 1; count <= 10; count++){
		printf("\t");
		int fileira;
		for(fileira = 1; fileira<=10; fileira++){
			if(lugares[numeroPoltrona-1]>0){
				SetColor(7);
				printf(" OCP ");
				SetColor(0);
			} else {
				printf(" %.3d ", numeroPoltrona);
			}
			numeroPoltrona++;
		}
		printf("\n");		
	}
	printf("\n\n");
}

int escolherPeca(){
	system("cls");
	gotoPrintMenu(20,2, " =========== Escolha uma peça  ===========");
	int OptX = 33; // Coordenada X que vai começar o print
	int OptFY = 5; // Coordenada Y para a linha da primeira opção
	int OptSpc = 3; // Espaçamento entre as opções
	int OptTotal = 4; // Total de opções do menu
	int mY = OptFY;                                              
	gotoxy(OptX,mY);printf("%s", Pecas[0].nome);
	gotoxy(OptX,mY+=OptSpc);printf("%s", Pecas[1].nome);
	gotoxy(OptX,mY+=OptSpc);printf("%s", Pecas[2].nome);
	gotoPrintMenu(OptX,mY+=OptSpc, "Voltar ao menu principal");
	int peca;
	peca = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
	return peca;
}

int LugaresSala1[100];

int escolherTipoIngresso(){
	system("cls");
	gotoPrintMenu(15,2, " =========== Escolha o tipo do seu ingresso  ===========");
	int OptX = 33; // Coordenada X que vai começar o print
	int OptFY = 5; // Coordenada Y para a linha da primeira opção
	int OptSpc = 3; // Espaçamento entre as opções
	int OptTotal = 4; // Total de opções do menu
	int mY = OptFY;                                              
	gotoxy(OptX,mY);printf("Inteira");
	gotoxy(OptX,mY+=OptSpc);printf("Meia");
	gotoxy(OptX,mY+=OptSpc);printf("Crianças Carentes");
	gotoxy(OptX,mY+=OptSpc);printf("Voltar ao menu principal");
	int tpIngresso;
	tpIngresso = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
	return tpIngresso;
}

void ComprarIngresso(int peca);
void CancelarIngresso(int peca);

void IngressoSucesso(int peca, int opt = 0){
	dataBaseSavePecas();
	system("cls");
	if(opt==0){
		gotoxy(15, 2); printf("========= Ingresso comprado com sucesso ===========");
		gotoxy(15, 4); printf("Deseja comprar outro ingresso na mesma sala?");
	} else {
		gotoxy(15, 2); printf("========= Ingresso cancelado com sucesso ===========");
		gotoxy(15, 4); printf("Deseja cancelar outro ingresso na mesma sala?");
	}

	
	int OptX = 33; // Coordenada X que vai começar o print
	int OptFY = 7; // Coordenada Y para a linha da primeira opção
	int OptSpc = 3; // Espaçamento entre as opções
	int OptTotal = 2; // Total de opções do menu
	int mY = OptFY;                                              
	gotoxy(OptX,mY);printf("Sim");
	gotoxy(OptX,mY+=OptSpc);printf("Não");

	int response;
	response = newMenuNav(OptFY, OptSpc, OptX, OptTotal);
	if(response==1){
		if(opt==0){
			ComprarIngresso(peca);
		} else {
			CancelarIngresso(peca);
		}
	}
	
}

void ComprarIngresso(int pc = 0){
	system("cls");
	
	
	int peca;
	int tpIngresso;
	int invalid = 1;

	if(pc==0){
		peca = escolherPeca();
		if(peca>totalPecas){
			return;
		}		
	} else {
		peca = pc;
	}
	
	printf("%d", peca);
	system("pause");

	tpIngresso = escolherTipoIngresso();
	if(tpIngresso==4){
		return;
	}
	
	do {

		int lugar;
		int indPeca = peca-1;
		int indLugar;
		
		system("cls");
		
		gotoPrintMenu(5,2, " =========== Escolha o numero da sua poltrona  ===========");
		
		gotoxy(0, 4);
		
		PrintLugares(Pecas[indPeca].lugares);
		gotoxy(6, 20);printf("Poltrona: ");
		cursor(1);
		scanf("%d", &lugar);
		indLugar = lugar-1;
		
		if(Pecas[indPeca].lugares[indLugar]==0 && lugar<=100){
			invalid = 0;
			Pecas[indPeca].lugares[indLugar] = tpIngresso;
		}
		
	} while(invalid == 1);
	//IngressoSucesso(peca);
	
}
void CancelarIngresso(int pc = 0){
	system("cls");
	bool invalid = true;
	int peca;
	if(pc==0){
		peca = escolherPeca();
		if(peca>totalPecas){
			return;
		}		
	} else {
		peca = pc;
	}

	do {
		
		int lugar;
		int indPeca = peca-1;
		int indLugar;
		
		system("cls");
		
		gotoPrintMenu(5,2, " ===== Escolha o numero da sua poltrona que deseja cancelar  =====");
		
		gotoxy(0, 4);
		
		PrintLugares(Pecas[indPeca].lugares);
		gotoxy(6, 20);printf("Poltrona: ");
		cursor(1);
		scanf("%d", &lugar);
		indLugar = lugar-1;
		
		if(Pecas[indPeca].lugares[indLugar]>0 && lugar<=100){
			invalid = false;
			Pecas[indPeca].lugares[indLugar] = 0;
		}
		

	} while(invalid);
	IngressoSucesso(peca, 1);
}
// Fim do controle dos ingressos

void bye(){
	system("cls");
	gotoPrintMenu(32, 10, "Até a próxima");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void menu(){//Menu inicial
	
	system("cls");
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
    	gotoPrintMenu(OptX,mY+=OptSpc, "Ver Peças");                 //
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
			case 4:
				CancelarIngresso();
			break;
			break;
			case 6:
				bye();
			break;
		}
				
	} while(Option!=6);
	
	
}//Fim do Menu Inicial
int main (int argc, char** argv)
{
	
	//system("chcp 1252");
	localeP;
    HWND wh = GetConsoleWindow();
    MoveWindow(wh, 200, 100, 900, 400, TRUE);
    
    dataBaseGetPecas();
    
	system("cls");
	menu();
	system("exit");
    return (0);
}
