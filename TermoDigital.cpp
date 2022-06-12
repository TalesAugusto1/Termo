/*
DISCIPLINA: Algoritimos de programa��o;
PROJETINHO: LETRECO;
INTEGRANTES:
Tales Augusto Sart�rio Furlan 212170
La�s Chiardelli Rodrigues 212036
Gabriel Habila Pinheiro 211981
Lucas de Moraes Silveira 211668
Lucas Delfino Kozyreff 223564
Heloisa Goulart Vicencio 222312
*/

/*
Se voc� acertar a letra correta no lugar adequado, aparecer� a letra C.
Se acertar a letra, mas na posi��o errada, aparecer� a letra T.
Caso a letra n�o esteja na palavra do dia, aparecer� um h�fen.
*/

// blibliotecas
#include <stdio.h>      //Esta biblioteca inclu� as fun��es de ENTRADA e SA�DA, presente em quase todos os programas em C. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/stdio.h.html
#include <stdlib.h>     //Esta biblioteca inclu� v�rias fun��es e constantes b�sicas, tais quais RAND_MAX, *malloc e *realloc. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/stdlib.h.html
#include <string.h>     //Esta biblioteca inclu� uma s�rie de fun��es para manipular strings. Ver mais em: http://linguagemc.com.br/a-biblioteca-string-h/
#include <stdbool.h>    //Esta biblioteca inclu� o BOOLEANO: define que 1 � TRUE e 0 � FALSE. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/stdbool.h.html
#include <time.h>       //Esta biblioteca inclu� v�rias fun��es que medem o tempo. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/time.h.html
#include <unistd.h>		//Esta biblioteca inclui as fun��es sleep e getcwd neste c�digo.
#include <locale.h>		//Esta biblioteca inclu� os caracteres do idioma portugu�s.
#include <ctype.h>		//Esta biblioteca inclu� a fun��o "tolower".

// Aqui foi definido o numero maximo de palavras que podem ser usadas no c�digo do arquivo "palavras.txt".
#define num_max_palavras 763

//lista de fun��es:
int   DigitarMenu();      										   //Esta fun��o ir� printar o menu e coletar a resposta do usu�rio, est� presente na linha 42.
void  JogoEmSi();         										   //Esta fun��o cont�m o case 2 do switch, o jogo.
bool processarAcerto(const char *aResposta, const char *oAcerto);  //Esta fun��o ir� comparar a resposta coletada da lista de palavras com a tentativa de acerto do jogador, se iguais, retornar� VERDADEIRO (o jogador ganhou).
void EsqueletoSwitch();   										   //Para seguir a cadeia l�gica de comandos sem conflito ap�s o t�rmino do jogo, o c�digo foi transformado em uma fun��o, para ser chamada novamente ao longo do programa.       

//Vari�veis globais

char nome_do_jogador;	  //Vari�vel usada para armazenar o ranking
int tentativas;

//------------main----------
int main() {
  FILE *pont_rank;						//Criando a vari�vel do ponteiro para o arquivo.
  pont_rank = fopen("rank.txt", "a");	//Abrindo o arquivo "rank.txt".
  setlocale(LC_ALL, "Portuguese");		//Aqui foi definido o idioma do c�digo como portugu�s.
  EsqueletoSwitch();      				//Esta fun��o contem a estrutura do jogo conectada ao menu, seguindo este para o comando switch - 1 tutorial, 2 jogo, 3 ranking e 4 encerrar programa. 
  
}


//fun��es que est�o dentro da main


//Esta fun��o ir� retornar o meu de op��es para o jogador baseado no switch, retornando a variavel T.
int DigitarMenu(){
	int t = 0;            //Vari�vel escolhida para contrlar o switch.
	system("cls");  //Limpa a tela dos dados anteriores.
	printf("\n\t     Jogo Termo digital!\n\n");
	printf("--------------------MENU----------------------\n\n");
	printf("--> Digite um numero para continuar\n\n");
	printf("[1] Tutorial\n");
	printf("[2] Jogar\n");
	printf("[3] Sair\n\n--> ");  //Escreve o menu.
	fflush(stdin);
	scanf("%i", &t);  //Ap�s o usu�rio digitar, armazena e direciona a escolha dele dentro do menu.
	system("cls");  //Limpa o menu para aparecer as novas informa��es.
	return t;         //Retorna o valor da vari�vel "t".
}

void JogoEmSi(){
  
  		clock_t t0, tf;
  		double tempo_gasto;
        // Ler as palavras do arquivo palavras.txt
        t0 = clock();
        char **ListaDePalavras = (char **) calloc(num_max_palavras, sizeof(char**));  //
        int ContDePal = 0;
        char *PalComCincoLet = (char *) malloc(6 * sizeof(char));
        FILE *ArquivoDePalavras = fopen("palavras.txt", "r");						  //Esta linha ir� abrir e ler o arquivo de palavras usado para definir a resposta no c�digo.
        if(ArquivoDePalavras == NULL){												  //Caso o arquivo n�o exista, o programa ir� retornar que n�o foi poss�vel abrir o mesmo por este if.
        	char diretorio[30];
			getcwd(diretorio, 30);
        	printf("Nao conseguiu abrir o arquivo palavras.txt no diretorio %s\n", diretorio);
        	sleep(3);
        	exit(1);
		}
        while (fscanf(ArquivoDePalavras, "%s", PalComCincoLet) != EOF && ContDePal < num_max_palavras) {
          ListaDePalavras[ContDePal] = PalComCincoLet;
          ContDePal++;
          PalComCincoLet = (char *)malloc(6 * sizeof(char));
          }
        fclose(ArquivoDePalavras);
  // come�o do jogo.

  // escolhendo uma palavra aleat�ria.
  srand(time(NULL));    //N�o � poss�vel criar um n�mero totalmente areat�rio, o c�digo de aleatoriedade usa uma semente de base geral para ser gerado, aqui essa semente � transformada no hor�rio do computador, garantindo uma maior aleatoriedade. 
  char *resposta = ListaDePalavras[rand() % ContDePal];

  // come�ar o loop de tentativas
  int num_tentativas = 0;
  bool adivinhou = false;
//Livia modificou 114 
  

  
  while (num_tentativas <= 6 || !adivinhou) {
    // pegar a tentativa do jogador e verificar o numero de letras

    char guess[55];
    

      



    
    while (num_tentativas < 6 ||
           adivinhou != processarAcerto(resposta, guess)) {
      int x, y, i;
      x = 1;
      while ((x == 1)) {
//printf("%s ", resposta);			//Usado para o teste do c�digo caso voc� n�o esteja conseguindo acertar a palavra.
        printf("Coloque uma palavra com 5 letras e pressione Enter: ");
        fflush(stdin);
        scanf("%54s", guess);
        
        for(int i = 0; guess[i]; i++){	//Este comando transforma todas as letras da palavra escrita pelo jogador em minusculas, de forma que fique compat�vel com o banco de palavras.
  		guess[i] = tolower(guess[i]);
		}
        if (strlen(guess) > 5) {
          // Se o usu�rio colocar mais de 5 letras a mensagem a seguir aparece:
          printf("\nLETRAS A MAIS!\n\n");
        } else if (strlen(guess) < 5) {

          // Se o usu�rio colocar menos 5 letras a mensagem a seguir aparece:
          printf("\nLETRAS A MENOS!\n\n");
        }
         
        else if ((adivinhou = processarAcerto(resposta, guess))) {
		
		  tf = clock();
   	  	  tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
          printf("\n\nParabens! Voc� acertou em %i tentativas e %.2lf segundos! a palavra era %s!",num_tentativas+1, tempo_gasto, resposta);
          printf("\n\nRetornando ao menu.\n\n");
			
          int i;
           
        

          for(i=0;i < 5; i++){ // abrir um la�o de repeti��o com for
          sleep(1); // pausa de 1 segundo
          printf("."); // escrever 1 "." na tela
          fflush(stdout); // atualizar a tela
          
          }
        EsqueletoSwitch();

        }

        else {
          x = 0;
        }
      }

      y = (5 - num_tentativas);
      //  Game over
      if (y == 0) {
      	system("cls");
        printf("\n\nGAME OVER!\nA palavra era %s.", resposta);
        tf = clock();
   		tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
  		printf("\n\nForam usados %.2lf segundos em sua partida\n", tempo_gasto);
        printf("\n\nRetornando ao menu.\n\n");

        int i;
           
        

          for(i=0;i < 7; i++){ // abrir um la�o de repeti��o com for
          sleep(1); // pausa de 1 segundo
          printf("."); // escrever 1 "." na tela
          fflush(stdout); // atualizar a tela
          
          }
        EsqueletoSwitch();
      }
      printf("%s\n", guess);
      printf("\nAinda faltam %i tentativas \n\n", y);

      num_tentativas += 1;

      // faltaT

      // testar resposta
    }

    for (int i = 0; i < ContDePal; i++) {
      free(ListaDePalavras[i]);
    }
    free(ListaDePalavras);
    free(PalComCincoLet);

   
  }



  
}



bool processarAcerto(const char *aResposta, const char *oAcerto) {
  // dica.
  char dica[6] = {'-', '-', '-', '-', '-', '\0'};
  // local para indicar a posi��o das letras.
  bool DicasPResp[5] = {false, false, false, false, false};

  // passa uma vez, procura letras no lugar certo.
  for (int i = 0; i < 5; i++) {
    if (oAcerto[i] == aResposta[i]) {
      dica[i] = 'C'; // de Correto
      DicasPResp[i] = true;
    }
  }

  // segunda vez que "passa", buscando as letras no lugar errado
  for (int i = 0; i < 5; i++) {
    if (dica[i] == '-') { // n�o encontrou.
      for (int j = 0; j < 5; j++) {
        if (oAcerto[i] == aResposta[j] && !DicasPResp[j]) {
          // Letra no lugar errado foi encontrada.
          dica[i] = 'T'; // de T�m.
          DicasPResp[j] = true;
          // break; //finalizar esse comando quando acabar a palavra.
        }
      }
    }
  }

  printf("%s\n", dica);
  return strcmp(dica, "CCCCC") == 0; // strcmp = resposta totalmente correta, se
                                     // acontecer o jogador ganhou, retornar 0.
}

//Para retornar ao menu ap�s o termino de uma partida, o c�digo principal foi transformado em uma fun��o, a EsqueletoSwitch, que cont�m todas as outras.
void EsqueletoSwitch(){
  
  while (1){            //Definiu um loop eterno de repeti��o.
    int t;              //Vari�vel para controlar o switch.
    t = 0;              //Defini��o inicial = 0.

    t = DigitarMenu();  //Chama a fun��o de op��es do menu.
    
   do { switch (t){     //Casos do menu.
       case 1:			//Printa o tutorial.
         printf("\n\n\n===================================================== BEM VINDO! =====================================================");
        printf("\n\t\t\t\t\t\t    Este e o Termo!");
        printf("\n\n\t\t   O jogo onde voc� deve adivinhar uma palavra de cinco letras, com apenas cinco chances;");
        printf("\n\t\t\t\t\t          NORMAS PARA JOGAR");
        printf("\n\n\t     - Caso a palavra digitada possua letras na posi��o correta, um \"C\" de Correto aparecera;");
        printf(" \n\t     - Caso a palavra digitada contenha letras corretas, porem em uma posi��o incorreta, um \"T\" de \"Tem\" \n\t      preenchera seu espa�o, desta forma se podendo alterar a posi��o da letra na chance seguinte;");
        printf("\n\t     - E caso n�o apare�a nada, a letra n�o existe na palavra resposta.");
        printf("\n\n\t\t          Digite qualquer caractere e pressione enter para retornar ao menu.\n\n--> ");
		fflush(stdin);
		scanf("%i", &t);
        system("cls");
        break;

      case 2:			//Fun��o do jogo.
    
          JogoEmSi();
          break;
          
      case 3:
        system("cls"); // Limpar a tela
		printf("Encerrando programa\n\n");

        int i;
           
          for(i=0;i < 3; i++){     // abrir um la�o de repeti��o com for
          sleep(1);                // pausa de 1 segundo
          printf(".");             // escrever 1 "." na tela
          fflush(stdout);          // atualizar a tela
          
          }
        
        exit(0);
      
      default:
	    break;
      
     }
    t = 0;
}while(t!=0);

    
  }

  
}
