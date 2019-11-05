#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define TAMMAX 255

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
    int			hora;
    int 		minuto;
};

struct Peca 		Pecas[3];
int totalPecas		= 3;

// Função menu
void menu();

// print lugares
void PrintLugares(int lugares[100], bool inv = false);

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

int newMenuYN(int x = 7){
	int OptX = 33; // Coordenada X que vai começar o print
	int OptFY = x; // Coordenada Y para a linha da primeira opção
	int OptSpc = 3; // Espaçamento entre as opções
	int OptTotal = 2; // Total de opções do menu
	int mY = OptFY;                                              
	gotoxy(OptX,mY);printf("Sim");
	gotoxy(OptX,mY+=OptSpc);printf("Não");
	
	return newMenuNav(OptFY, OptSpc, OptX, OptTotal);
}

// Fim das funções de seta dos menus

// Colors

/*
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15
*/
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
	int OpcaoPeca;
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
			
			gotoPrintMenu(20,8, " Horário: ");
			cursor(1);
			scanf("%d:%d" , &Pecas[indPeca].hora,&Pecas[indPeca].minuto);
			
			gotoxy(21, 11);printf("SALA %d definida", OpcaoPeca);
			gotoxy(21, 12);printf("Nome: %s", Pecas[indPeca].nome);
			gotoxy(21, 13);printf("Valor: R$ %.2f", Pecas[indPeca].valor);
			gotoxy(21, 14);printf("Hora: %d:%d \n\n\n\n", Pecas[indPeca].hora, Pecas[indPeca].minuto);
			cursor(0);
			
			OpcaoPeca = 0;
			system("pause");			
		}
	
	} while(OpcaoPeca<4);
	dataBaseSavePecas();
}

void VerPecas(){ // menu para ver as peças escolhidas
	system("cls");
	int l = 2;
	gotoxy(8, l);
	printf(" ====================== Peças em cartaz ====================== ");
	for(int i=0; i<totalPecas;i++){
		gotoxy(8, l+2);
		
		SetColor(1);
		printf("%s", Pecas[i].nome);
		SetColor(0);
		
		gotoxy(8, l+4);
		printf(" SALA %d às %d:%d                         %.2f", i+1, Pecas[i].hora, Pecas[i].minuto, Pecas[i].valor);
		
		gotoxy(0, l+6);
		PrintLugares(Pecas[i].lugares);
		
		l+=18;
		gotoxy(8, l+2);
		printf("=================================================");
		l+= 5;

	}

	printf("\n\n\n");
	system("pause");
}
// Fim do controle das peças

// Controle dos ingressos

void PrintLugares(int lugares[100], bool inv){

	int numeroPoltrona = 1;
	printf("\t ===================== TELA ===================== \n\n");
	int count;
	for(count = 1; count <= 10; count++){
		printf("\t");
		int fileira;
		for(fileira = 1; fileira<=10; fileira++){
			if(inv){
				if(lugares[numeroPoltrona-1]==0){
					SetColor(1);
					printf(" LVR ");
					SetColor(0);
				} else {
					printf(" %.3d ", numeroPoltrona);
				}
			} else {
				if(lugares[numeroPoltrona-1]>0){
					SetColor(7);
					printf(" OCP ");
					SetColor(0);
				} else {
					printf(" %.3d ", numeroPoltrona);
				}
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
void ComprarIngressoTicket(int peca, int lugar, int tpIng);

void IngressoSucesso(int peca, int opt = 0, int lugar = 0, int tpIng = 0){
	dataBaseSavePecas();
	system("cls");
	int lYN = 7;
	if(opt==0){
		gotoxy(18, 2); printf("========= Ingresso comprado com sucesso ===========");
		ComprarIngressoTicket(peca, lugar, tpIng);
		lYN = 22;
		gotoxy(18, 20); printf("Deseja comprar outro ingresso na mesma sala?");
	} else {
		gotoxy(15, 2); printf("========= Ingresso cancelado com sucesso ===========");
		gotoxy(15, 4); printf("Deseja cancelar outro ingresso na mesma sala?");
	}

	int response;
	response = newMenuYN(lYN);

	if(response==1){
		if(opt==0){
			ComprarIngresso(peca);
		} else {
			CancelarIngresso(peca);
		}
	}
	
}

void ComprarIngressoTicket(int peca, int lugar, int tpIng){
	
	srand(time(NULL));
	time_t t = time(NULL);
  	struct tm tm = *localtime(&t);
  	
	int id = rand();
	float valor = 0;
	if(tpIng==1){
		valor = Pecas[peca-1].valor;
	} else if(tpIng==2){
		valor = Pecas[peca-1].valor/2;
	} else {
		valor = 0;
	}
	gotoxy(20, 4);printf("==============  Ticket %d  =============", id);
	
	gotoxy(21,  8);printf("Sala ___________________________ %d", peca);
	gotoxy(21, 10);printf("Peça ___________________________ %s", Pecas[peca-1].nome);
	gotoxy(21, 12);printf("Poltrona _______________________ %d", lugar);
	gotoxy(21, 14);printf("Valor __________________________ %.2f", valor);
	gotoxy(21, 16);printf("Data ___________________________ %d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
	gotoxy(21, 18);printf("Horário_________________________ %d:%d", Pecas[peca-1].hora, Pecas[peca-1].minuto);
}

void ComprarIngresso(int pc = 0){

	system("cls");
	
	int peca;
	int tpIngresso;
	bool invalid = true;

	if(pc==0){
		peca = escolherPeca();
		if(peca>totalPecas){
			return;
		}		
	} else {
		peca = pc;
	}

	tpIngresso = escolherTipoIngresso();
	
	if(tpIngresso==4){
		return;
	}
	
	int lugar;
	
	do {

		lugar = 0;
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
			invalid = false;
			Pecas[indPeca].lugares[indLugar] = tpIngresso;
		}
		
	} while(invalid);
	IngressoSucesso(peca, 0, lugar, tpIngresso);
	
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
		
		gotoPrintMenu(5,2, " ===== Escolha o numero da poltrona que deseja cancelar  =====");
		
		gotoxy(0, 4);
		
		PrintLugares(Pecas[indPeca].lugares, true);
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

// Faturamento

void faturamento(){
	system("cls");
	gotoPrintMenu(25,2, " ===== FATURAMENTO  =====");
	gotoPrintMenu(15,4, " Essa opção irá calcular o valor obtivo no dia ");
	gotoPrintMenu(15,5, "   e irá definir todos os lugares como livre. ");
	gotoxy(15, 6);printf("===============================================");
	gotoPrintMenu(15,7, " Tem certeza que deseja continuar? ");
	
	int response;
	response = newMenuYN(10);
	
	if(response==1){
		int totalInteira = 0, totalMeia = 0, totalFree = 0;
		float total;
		for(int i=0; i<totalPecas; i++){
			
			float valor = Pecas[i].valor;
			
			for(int j = 0; j<100; j++){
				switch(Pecas[i].lugares[j]){
					case 1:
						total += valor;
						totalInteira++;
					break;
					case 2:
						total += valor/2;
						totalMeia++;
					break;
					case 3:
						totalFree++;
					break;
				}
				Pecas[i].lugares[j] = 0;
			}
		}
		
		dataBaseSavePecas();
		system("cls");
		
		time_t t = time(NULL);
  		struct tm tm = *localtime(&t);
		
		
		gotoxy(10, 2);printf("Faturamento do dia %d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
		gotoxy(10, 4);printf("Total de entradas inteiras:");gotoxy(40, 4);printf("%d", totalInteira);
		gotoxy(10, 5);printf("Total de meia entradas:");gotoxy(40, 5);printf("%d", totalMeia);
		gotoxy(10, 6);printf("Total de entradas cedidas:");gotoxy(40, 6);printf("%d", totalFree);
		
		gotoxy(10, 8);printf("Valor total arrecadado:");gotoxy(40, 8);printf("%.2f", total);
		
		gotoxy(10, 10);printf("Todas as poltronas foram liberadas!");

		gotoxy(0, 28);
		system("pause");
	}
	

}

// Fim do faturamento

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
			break;
			case 4:
				CancelarIngresso();
			break;
			case 5:
				faturamento();
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
