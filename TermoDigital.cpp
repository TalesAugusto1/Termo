/*
DISCIPLINA: Algoritimos de programação;
PROJETINHO: LETRECO;
INTEGRANTES:
Tales Augusto Sartório Furlan 212170
Laís Chiardelli Rodrigues 212036
Gabriel Habila Pinheiro 211981
Lucas de Moraes Silveira 211668
Lucas Delfino Kozyreff 223564
Heloisa Goulart Vicencio 222312
*/

/*
Se você acertar a letra correta no lugar adequado, aparecerá a letra C.
Se acertar a letra, mas na posição errada, aparecerá a letra T.
Caso a letra não esteja na palavra do dia, aparecerá um hífen.
*/

// blibliotecas
#include <stdio.h>      //Esta biblioteca incluí as funções de ENTRADA e SAÍDA, presente em quase todos os programas em C. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/stdio.h.html
#include <stdlib.h>     //Esta biblioteca incluí várias funções e constantes básicas, tais quais RAND_MAX, *malloc e *realloc. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/stdlib.h.html
#include <string.h>     //Esta biblioteca incluí uma série de funções para manipular strings. Ver mais em: http://linguagemc.com.br/a-biblioteca-string-h/
#include <stdbool.h>    //Esta biblioteca incluí o BOOLEANO: define que 1 é TRUE e 0 é FALSE. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/stdbool.h.html
#include <time.h>       //Esta biblioteca incluí várias funções que medem o tempo. Ver mais em: https://www.ime.usp.br/~pf/algoritmos/apend/time.h.html
#include <unistd.h>		//Esta biblioteca inclui as funções sleep e getcwd neste código.
#include <locale.h>		//Esta biblioteca incluí os caracteres do idioma português.
#include <ctype.h>		//Esta biblioteca incluí a função "tolower".

// Aqui foi definido o numero maximo de palavras que podem ser usadas no código do arquivo "palavras.txt".
#define num_max_palavras 763

//lista de funções:
int   DigitarMenu();      										   //Esta função irá printar o menu e coletar a resposta do usuário, está presente na linha 42.
void  JogoEmSi();         										   //Esta função contêm o case 2 do switch, o jogo.
bool processarAcerto(const char *aResposta, const char *oAcerto);  //Esta função irá comparar a resposta coletada da lista de palavras com a tentativa de acerto do jogador, se iguais, retornará VERDADEIRO (o jogador ganhou).
void EsqueletoSwitch();   										   //Para seguir a cadeia lógica de comandos sem conflito após o término do jogo, o código foi transformado em uma função, para ser chamada novamente ao longo do programa.       

//Variáveis globais

char nome_do_jogador;	  //Variável usada para armazenar o ranking
int tentativas;

//------------main----------
int main() {
  FILE *pont_rank;						//Criando a variável do ponteiro para o arquivo.
  pont_rank = fopen("rank.txt", "a");	//Abrindo o arquivo "rank.txt".
  setlocale(LC_ALL, "Portuguese");		//Aqui foi definido o idioma do código como português.
  EsqueletoSwitch();      				//Esta função contem a estrutura do jogo conectada ao menu, seguindo este para o comando switch - 1 tutorial, 2 jogo, 3 ranking e 4 encerrar programa. 
  
}


//funções que estão dentro da main


//Esta função irá retornar o meu de opções para o jogador baseado no switch, retornando a variavel T.
int DigitarMenu(){
	int t = 0;            //Variável escolhida para contrlar o switch.
	system("cls");  //Limpa a tela dos dados anteriores.
	printf("\n\t     Jogo Termo digital!\n\n");
	printf("--------------------MENU----------------------\n\n");
	printf("--> Digite um numero para continuar\n\n");
	printf("[1] Tutorial\n");
	printf("[2] Jogar\n");
	printf("[3] Sair\n\n--> ");  //Escreve o menu.
	fflush(stdin);
	scanf("%i", &t);  //Após o usuário digitar, armazena e direciona a escolha dele dentro do menu.
	system("cls");  //Limpa o menu para aparecer as novas informações.
	return t;         //Retorna o valor da variável "t".
}

void JogoEmSi(){
  
  		clock_t t0, tf;
  		double tempo_gasto;
        // Ler as palavras do arquivo palavras.txt
        t0 = clock();
        char **ListaDePalavras = (char **) calloc(num_max_palavras, sizeof(char**));  //
        int ContDePal = 0;
        char *PalComCincoLet = (char *) malloc(6 * sizeof(char));
        FILE *ArquivoDePalavras = fopen("palavras.txt", "r");						  //Esta linha irá abrir e ler o arquivo de palavras usado para definir a resposta no código.
        if(ArquivoDePalavras == NULL){												  //Caso o arquivo não exista, o programa irá retornar que não foi possível abrir o mesmo por este if.
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
  // começo do jogo.

  // escolhendo uma palavra aleatória.
  srand(time(NULL));    //Não é possível criar um número totalmente areatório, o código de aleatoriedade usa uma semente de base geral para ser gerado, aqui essa semente é transformada no horário do computador, garantindo uma maior aleatoriedade. 
  char *resposta = ListaDePalavras[rand() % ContDePal];

  // começar o loop de tentativas
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
//printf("%s ", resposta);			//Usado para o teste do código caso você não esteja conseguindo acertar a palavra.
        printf("Coloque uma palavra com 5 letras e pressione Enter: ");
        fflush(stdin);
        scanf("%54s", guess);
        
        for(int i = 0; guess[i]; i++){	//Este comando transforma todas as letras da palavra escrita pelo jogador em minusculas, de forma que fique compatível com o banco de palavras.
  		guess[i] = tolower(guess[i]);
		}
        if (strlen(guess) > 5) {
          // Se o usuário colocar mais de 5 letras a mensagem a seguir aparece:
          printf("\nLETRAS A MAIS!\n\n");
        } else if (strlen(guess) < 5) {

          // Se o usuário colocar menos 5 letras a mensagem a seguir aparece:
          printf("\nLETRAS A MENOS!\n\n");
        }
         
        else if ((adivinhou = processarAcerto(resposta, guess))) {
		
		  tf = clock();
   	  	  tempo_gasto = ( (double) (tf - t0) ) / CLOCKS_PER_SEC;
          printf("\n\nParabens! Você acertou em %i tentativas e %.2lf segundos! a palavra era %s!",num_tentativas+1, tempo_gasto, resposta);
          printf("\n\nRetornando ao menu.\n\n");
			
          int i;
           
        

          for(i=0;i < 5; i++){ // abrir um laço de repetição com for
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
           
        

          for(i=0;i < 7; i++){ // abrir um laço de repetição com for
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
  // local para indicar a posição das letras.
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
    if (dica[i] == '-') { // não encontrou.
      for (int j = 0; j < 5; j++) {
        if (oAcerto[i] == aResposta[j] && !DicasPResp[j]) {
          // Letra no lugar errado foi encontrada.
          dica[i] = 'T'; // de Têm.
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

//Para retornar ao menu após o termino de uma partida, o código principal foi transformado em uma função, a EsqueletoSwitch, que contêm todas as outras.
void EsqueletoSwitch(){
  
  while (1){            //Definiu um loop eterno de repetição.
    int t;              //Variável para controlar o switch.
    t = 0;              //Definição inicial = 0.

    t = DigitarMenu();  //Chama a função de opções do menu.
    
   do { switch (t){     //Casos do menu.
       case 1:			//Printa o tutorial.
         printf("\n\n\n===================================================== BEM VINDO! =====================================================");
        printf("\n\t\t\t\t\t\t    Este e o Termo!");
        printf("\n\n\t\t   O jogo onde você deve adivinhar uma palavra de cinco letras, com apenas cinco chances;");
        printf("\n\t\t\t\t\t          NORMAS PARA JOGAR");
        printf("\n\n\t     - Caso a palavra digitada possua letras na posição correta, um \"C\" de Correto aparecera;");
        printf(" \n\t     - Caso a palavra digitada contenha letras corretas, porem em uma posição incorreta, um \"T\" de \"Tem\" \n\t      preenchera seu espaço, desta forma se podendo alterar a posição da letra na chance seguinte;");
        printf("\n\t     - E caso não apareça nada, a letra não existe na palavra resposta.");
        printf("\n\n\t\t          Digite qualquer caractere e pressione enter para retornar ao menu.\n\n--> ");
		fflush(stdin);
		scanf("%i", &t);
        system("cls");
        break;

      case 2:			//Função do jogo.
    
          JogoEmSi();
          break;
          
      case 3:
        system("cls"); // Limpar a tela
		printf("Encerrando programa\n\n");

        int i;
           
          for(i=0;i < 3; i++){     // abrir um laço de repetição com for
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
