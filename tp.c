/************** TRABALHO PRÁTICO DO PUCA: JOGO "2048" **************/
/*              ANGELO RESENDE DA SILVA    25.1.4013               */

/* 
 *  Ao jogar, por favor, considere:
 *    - Usar o terminal em tela cheia no Linux Ubuntu
 *    - Usar fonte: Ubuntu Mono 14
 *  A formatação do jogo foi feita levando essas configurações
 *  em consideração
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/**************************** CONSTANTES ***************************/

// Constantes minhas
#define BLOCOVOLTAR 256
#define BLOCOTROCAR 512

// cores e formato de texto
#define ANSI_RESET            "\x1b[0m"  // desativa os efeitos anteriores
#define ANSI_BOLD             "\x1b[1m"  // coloca o texto em negrito
#define ANSI_COLOR_BLACK      "\x1b[30m"
#define ANSI_COLOR_RED        "\x1b[31m"
#define ANSI_COLOR_GREEN      "\x1b[32m"
#define ANSI_COLOR_YELLOW     "\x1b[33m"
#define ANSI_COLOR_BLUE       "\x1b[34m"
#define ANSI_COLOR_MAGENTA    "\x1b[35m"
#define ANSI_COLOR_CYAN       "\x1b[36m"
#define ANSI_COLOR_WHITE      "\x1b[37m"
#define ANSI_BG_COLOR_BLACK   "\x1b[40m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_GREEN   "\x1b[42m"
#define ANSI_BG_COLOR_YELLOW  "\x1b[43m"
#define ANSI_BG_COLOR_BLUE    "\x1b[44m"
#define ANSI_BG_COLOR_MAGENTA "\x1b[45m"
#define ANSI_BG_COLOR_CYAN    "\x1b[46m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

// macros para facilitar o uso
#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BLACK(string)      ANSI_COLOR_BLACK      string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define RED(string)        ANSI_COLOR_RED        string ANSI_RESET
#define GREEN(string)      ANSI_COLOR_GREEN      string ANSI_RESET
#define YELLOW(string)     ANSI_COLOR_YELLOW     string ANSI_RESET
#define BLUE(string)       ANSI_COLOR_BLUE       string ANSI_RESET
#define MAGENTA(string)    ANSI_COLOR_MAGENTA    string ANSI_RESET
#define CYAN(string)       ANSI_COLOR_CYAN       string ANSI_RESET
#define WHITE(string)      ANSI_COLOR_WHITE      string ANSI_RESET
#define BG_BLACK(string)   ANSI_BG_COLOR_BLACK   string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_GREEN(string)   ANSI_BG_COLOR_GREEN   string ANSI_RESET
#define BG_YELLOW(string)  ANSI_BG_COLOR_YELLOW  string ANSI_RESET
#define BG_BLUE(string)    ANSI_BG_COLOR_BLUE    string ANSI_RESET
#define BG_MAGENTA(string) ANSI_BG_COLOR_MAGENTA string ANSI_RESET
#define BG_CYAN(string)    ANSI_BG_COLOR_CYAN    string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

// caracteres uteis para tabelas
#define TAB_HOR "\u2501" // ━ (horizontal)
#define TAB_VER "\u2503" // ┃ (vertical)
#define TAB_TL  "\u250F" // ┏ (top-left)
#define TAB_ML  "\u2523" // ┣ (middle-left)
#define TAB_BL  "\u2517" // ┗ (bottom-left)
#define TAB_TJ  "\u2533" // ┳ (top-join)
#define TAB_MJ  "\u254B" // ╋ (middle-join)
#define TAB_BJ  "\u253B" // ┻ (bottom-join)
#define TAB_TR  "\u2513" // ┓ (top-right)
#define TAB_MR  "\u252B" // ┫ (middle-right)
#define TAB_BR  "\u251B" // ┛ (bottom-right)

/**************************** PROTÓTIPOS ****************************/
// Funções úteis
void limparBuffer();
void imprimirTitulo();
void espacos(int n);
void espacosPretos();
void espacosBrancos();
void quebrar(int n);
void margem(int n);
void centralizado(char *texto);
void letraMaiuscula(char* comando);
void invalido();
int algarismos(int n);

// Funções do jogo
void imprimirMatriz(int** matriz, int n, int pontuacao, int nTrocar, int nVoltar);
int gerarBloco(int*** matriz, int n);
void moverMatriz(int*** m, int n, char c);
void somarBlocos(int*** m, int n, char c, int* pontuacao, int* nTrocar, int* nVoltar);
void copiarMatriz(int*** destino, int*** origem, int n);
void voltarJogada(int*** m, int ***mA);
int algarismosMaiorNumero(int*** m, int n);
int compararMatriz(int** m, int** mA, int n);
int movimentoAlteraTabuleiro(int** m, int n);
void trocarPecas(int*** matriz, char posicao[1000]);
int jogadaDeuTroca(int** m, int** mA, int n);
int pontuacaoAtual(int** m, int n);

// Funções de alocação
void alocarMatriz(int*** matriz, int n);
void liberarMatriz(int*** matriz, int n);
void zerarMatriz(int** matriz, int n);

/******************************* MAIN *******************************/

int main() {
  int programa = 1;
  
  /* ----- MENU ----- */
  while (programa) {
    system("clear");
    
    // Imprimir cabeçario
    quebrar(4);
    imprimirTitulo();
    quebrar(1);
    centralizado("Angelo Resende da Silva              25.1.4013\n\n");
    quebrar(4);
    
    // Imprimir opções
    centralizado("O que deseja fazer?\n\n");
    centralizado(BOLD("(N)") " Novo jogo\n");
    centralizado(BOLD("(J)") " Continuar jogo atual\n");
    centralizado(BOLD("(C)") " Carregar um jogo salvo\n");
    centralizado(BOLD("(S)") " Salvar o jogo atual\n");
    centralizado(BOLD("(M)") " Mostrar Ranking\n");
    centralizado(BOLD("(A)") " Ajuda com as instruções de como jogar\n");
    centralizado(BOLD("(R)") " Sair");
    quebrar(8);
    
    // Inserir comando
    char comando[3]; // 1 caractere + enter + \0 -> Garante que apenas aceite um caractere, e não uma palavra
    printf("\n\t" BOLD("Comando: "));
    fgets(comando, 3, stdin);
    letraMaiuscula(comando);
    
    if (strcmp(comando, "N\n") == 0) { // Novo jogo *******************************************************************************/
      
      /* ----- MODO ----- */
      int **matriz, **matrizAnterior;
      int jogo = 1;
      int tamanhoTabuleiro;
      int nVoltar = 10;
      int nTrocar = 0;
      int gerar = 1;
      int pontuacao = 0;
      int primeiraJogada = 1;
      int ganhou = 0;
      int primeiro2048 = 1;
      
      // Semente aleatória
      srand(time(NULL));
      
      do{
        system("clear");
        
        // Imprimir cabeçário
        quebrar(4);
        imprimirTitulo();
        quebrar(10);
        
        // Imprimir opções
        centralizado("Escolha o modo de jogo:");
        centralizado(BOLD("(4)") " Jogo 4x4");
        centralizado(BOLD("(5)") " Jogo 5x5");
        centralizado(BOLD("(6)") " Jogo 6x6");
        quebrar(19);
        
        // Inserir comando
        printf("\t" BOLD("Comando: "));
        scanf("%d", &tamanhoTabuleiro);

        if (tamanhoTabuleiro < 4 || 6 < tamanhoTabuleiro) { // Aceita apenas os tamanhos válidos
          limparBuffer();
          invalido();
        }
        
      } while (tamanhoTabuleiro < 4 || 6 < tamanhoTabuleiro);
      
      // Alocar a matriz tabuleiro e o tabuleiro anterior
      alocarMatriz(&matriz, tamanhoTabuleiro);
      alocarMatriz(&matrizAnterior, tamanhoTabuleiro);
      
      // Zerar as matrizes
      zerarMatriz(matriz, tamanhoTabuleiro);
      zerarMatriz(matrizAnterior, tamanhoTabuleiro);
      
      limparBuffer();
      
      /* ----- JOGO ----- */
      while (jogo) {
        system("clear");
        
        // Imprimir cabeçário
        quebrar(2);
        imprimirTitulo(); 
        
        // Gerar um bloco novo
        if (!gerar) { // Caso a geração de blocos tenha sido desativada
          gerar = 1;
        } else { // Caso não tenha sido
          if (primeiraJogada) { // Gera +1 bloco se for a primeira jogada
            gerarBloco(&matriz, tamanhoTabuleiro);
            primeiraJogada = 0;
          }
          gerarBloco(&matriz, tamanhoTabuleiro);
        }
        matriz[0][0] = 1073741824;
        // Imprimir tabuleiro
        quebrar(13-2*tamanhoTabuleiro);
        imprimirMatriz(matriz, tamanhoTabuleiro, pontuacao, nTrocar, nVoltar);
        quebrar(14-2*tamanhoTabuleiro);
        
        // Imprimir opções
        centralizado(BOLD("<W, A, S, D>") " Mover");
        centralizado(BOLD("<U>") " Dezfazer último movimento");
        centralizado(BOLD("<T> <Posição 1> <Posição 2>") " Troca a peça 1 pela peça 2");
        centralizado(BOLD("<V>") " Volta para o menu inicial");
        quebrar(3);
        
        // Confere se as condições de vitória foram atendidas        
        if (formou2048(matriz, matrizAnterior, n)) && (primeiro2048) {
          primeiro2048 = 0;
          
          printf("\nParabéns! Você venceu jogo! Deseja continuar jogando?" BOLD("\t(S)") "Sim" BOLD("\t(N)") "Não";
          
          // Inserir comando
          
        }
        
        // Conferir se é game over
        /*  Requesitos:
         *  - Qualquer movimento não altere o tabuleiro
         *  - Não pode voltar movimento
         *  - Não pode trocar duas peças
         */
        if (!movimentoAlteraTabuleiro(matriz, tamanhoTabuleiro)) {
          if (nVoltar > 0) {
            printf("\tVocê ainda pode voltar um movimento!");
          } else if (nTrocar > 0) {
            printf("\tVocê ainda pode trocar duas peças!");
          } else {
            printf("\tNão há mais movimentos possíveis. Você perdeu.\n");
            printf("\tAperte enter para continuar. ");
            limparBuffer();
            jogo = 0;
            break;
          }
        }
        
        // Inserir comando
        char comando2[3];
        printf("\n\t" BOLD("Comando: "));
        fgets(comando2, 3, stdin);
        letraMaiuscula(comando2);


        if (strcmp(comando2, "W\n") == 0 || strcmp(comando2, "A\n") == 0 || strcmp(comando2, "S\n") == 0 || strcmp(comando2, "D\n") == 0) { // Move o tabuleiro 
          
          // Salva o estado do tabuleiro anterior
          copiarMatriz(&matrizAnterior, &matriz, tamanhoTabuleiro);
          
          // Move os blocos sem fazer "peças gulosas"
          moverMatriz(&matriz, tamanhoTabuleiro, comando2[0]);
          somarBlocos(&matriz, tamanhoTabuleiro, comando2[0], &pontuacao, &nTrocar, &nVoltar);
          moverMatriz(&matriz, tamanhoTabuleiro, comando2[0]);
          
          if (compararMatriz(matriz, matrizAnterior, tamanhoTabuleiro)) { // Impede que movimentos nos quais peças não foram movidas gerem novos blocos
            gerar = 0;
          }
          
        } else if (strcmp(comando2, "U\n") == 0) { // Retorna o tabuleiro para o movimento anterior ******************************/
          if (nVoltar > 0) {
            if (jogadaDeuTroca(matriz, matrizAnterior, tamanhoTabuleiro)) { // Confere se o movimento desfeito concedeu +1 "Trocar"
              nTrocar--;
            }
            
            // Fazer função
            voltarJogada(&matriz, &matrizAnterior);
            nVoltar--;
            
            pontuacao = pontuacaoAtual(matriz, tamanhoTabuleiro);
            
          } else {
            printf("\tVocê ainda não pode desfazer sua jogada! Forme um %d primeiro! Aperte enter para continuar...", BLOCOVOLTAR);
            limparBuffer();
          }
          gerar = 0; // Faz com que o tabuleiro não seja alterado
        } else if (comando2[0] == 'T' && comando2[1] == '\n') { // Troca 2 peças de lugar *****************************************************/
          if (nTrocar > 0) {
            // Digitar comandos
            char posicao[1000];
            fgets(posicao, 1000, stdin);
            
            // Fazer função
            //trocarPecas(&matriz, posicao);
            nTrocar--;
          } else {
            printf("\tVocê ainda não pode trocar duas peças! Forme um %d primeiro! Aperte enter para continuar...", BLOCOTROCAR);
            limparBuffer();
          }
          gerar = 0; // Faz com que o tabuleiro não seja alterado
        } else if (strcmp(comando2, "V\n") == 0) { // Voltar para o menu *********************************************************/
            system("clear");
            jogo = 0;
        } else { // Comando inválido *********************************************************************************************/
          limparBuffer();
          invalido();
          gerar = 0; // Impede que comandos errados gerem novos blocos
        }
      }
      
      // Liberar memória alocada
      liberarMatriz(&matriz, tamanhoTabuleiro);
      liberarMatriz(&matrizAnterior, tamanhoTabuleiro);
    
    } else if (strcmp(comando, "J\n") == 0) { // Continuar jogo atual ********************************************************************/
    
      printf("Continuando jogo!");
    
    } else if (strcmp(comando, "C\n") == 0) { // Carregar um jogo salvo ******************************************************************/

      printf("Carregando jogo!");
    
    } else if (strcmp(comando, "S\n") == 0) { // Salvar jogo atual ***********************************************************************/

      printf("Salvando jogo!");
    
    } else if (strcmp(comando, "M\n") == 0) { // Mostrar ranking *************************************************************************/

      printf("*Abrindo Ranking*");
    
    } else if (strcmp(comando, "A\n") == 0) { // AJuda com as instruções do jogo *********************************************************/
      int ajuda = 1;
      
      /* ----- AJUDA ----- */
      while (ajuda) {
        
        system("clear");
        
        // Imprime o cabeçário
        quebrar(4);
        imprimirTitulo();
        quebrar(6);
        
        // Imprime as explicações
        margem(4); printf("2048 é um jogo de raciocínio onde o objetivo é deslizar peças numeradas em um tabuleiro e combiná-las até formar um bloco\n"); 
        margem(4); printf("com o número 2048.\n\n\n");
        margem(5); printf("- O jogador desliza as peças em um dos quatro sentidos (cima, baixo, esquerda e direita)\n\n");
        margem(5); printf("- A cada movimento, um novo número aparece aleatoriamente em um local vazio do tabuleiro.\n\n");
        margem(5); printf("- As peças deslizam o mais longe possível até colidirem.\n\n");
        margem(5); printf("- Duas peças iguais que se colidirem irão se fundir em uma peça com o valor total das duas peças.\n\n\n");
        margem(4); printf("Esse é o 2048.");
        quebrar(5);
        centralizado(BOLD("(R)") " Voltar ao menu");
        quebrar(7);
        
        // Inserir comando
        char comando2[3];
        printf("\n\t" BOLD("Comando: "));
        fgets(comando2, 3, stdin);
        letraMaiuscula(comando2);
        
        if (strcmp(comando2, "R\n") == 0) {
          ajuda = 0;
        } else {        
          limparBuffer();
          invalido();
        }
      }
    } else if (strcmp(comando, "R\n") == 0) { // Sair do jogo ****************************************************************************/
      int sair = 1;
      
      /* ----- SAIR ----- */
      while(sair) {
        system("clear");
        
        // Imprime o cabeçário
        quebrar(4);
        imprimirTitulo();
        quebrar(10);
        
        // Imprime as opções
        centralizado("Tem certeza que deseja sair?");
        centralizado(BOLD("(S)") " Sim");
        centralizado(BOLD("(N)") " Não");
        quebrar(19); 
        
        // Inserir comando
        char comando2[3];
        printf("\n\t" BOLD("Comando: "));
        fgets(comando2, 3, stdin);
        letraMaiuscula(comando2);
        
        if (strcmp(comando2, "S\n") == 0) {
          system("clear");
          programa = 0; // Encerra o jogo
          sair = 0;
        }
        else if (strcmp(comando2, "N\n") == 0) {
          sair = 0; // Finaliza o while e retorna para o menu
        } else {
          limparBuffer();
          invalido();
        }
      }
    } else { // Comando inválido *********************************************************************************************************/
      limparBuffer();
      invalido();
    } 
  }
  return 0;
}

/************************* FUNÇÕES *************************/

// Retorna a pontuação do estado do tabuleiro recebido
int pontuacaoAtual(int **m, int n){
  int pontos = 0;
  
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      for (int k = 4; k <= m[i][j]; k *= 2)
        pontos += k; // Soma todas as potências de 2 até chegar no bloco atual, que é m[i][j]
        
  return pontos;
}

/***********************************************************/

// Confere se a jogada deu +1 "Trocar"
int jogadaDeuTroca(int** m, int** mA, int n) {
  int tem = 0, tinha = 0;
  
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      if (m[i][j] == BLOCOTROCAR)
        tem += 1; // O tabuleiro tem uma peça que dá +1 Trocar
      if (mA[i][j] == BLOCOTROCAR)
        tinha += 1; // O tabuleiro tinha uma peça que dá +1 Trocar
    }

  if (tem == tinha)
    return 0; // Não foi formado um bloco que dá +1 Trocar
  return 1; // Foi formado
}

/***********************************************************/
/*
// Troca duas peças de posição
void trocarPecas(int*** matriz, int n, char posicao[1000]){
  
} */

/***********************************************************/

// Simula movimentos nas três direções e checa se isso altera o tabuleiro
int movimentoAlteraTabuleiro(int** m, int n) {
  int **mAux, lixo;
  
  alocarMatriz(&mAux, n);
  
  for (int i = 0; i < 4; i++) {
    copiarMatriz(&mAux, &m, n);

    switch (i) {
      case 0: moverMatriz(&mAux, n, 'W'); somarBlocos(&mAux, n, 'W', &lixo, &lixo, &lixo); break;
      case 1: moverMatriz(&mAux, n, 'A'); somarBlocos(&mAux, n, 'A', &lixo, &lixo, &lixo); break;
      case 2: moverMatriz(&mAux, n, 'S'); somarBlocos(&mAux, n, 'S', &lixo, &lixo, &lixo); break;
      case 3: moverMatriz(&mAux, n, 'D'); somarBlocos(&mAux, n, 'D', &lixo, &lixo, &lixo); break;
    }
    
    if (!compararMatriz(mAux, m, n)) {
      liberarMatriz(&mAux, n);
      return 1; // Movimento altera o tabuleiro
    }
  }
  
  liberarMatriz(&mAux, n);
  return 0; // Movimentos não alteram o tabuleiro
}

// Compara os elementos de uma matriz com os de outra
int compararMatriz(int** m, int** mA, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (m[i][j] != mA[i][j])
        return 0; // Não são iguais

  return 1; // São iguais
}

/***********************************************************/

// Aloca memória para uma matriz
void alocarMatriz(int*** matriz, int n) {
  (*matriz) = malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++)
    (*matriz)[i] = malloc(n * sizeof(int)); 
}

/***********************************************************/

// Libera a memória alocada
void liberarMatriz(int*** matriz, int n) {
  for (int i = 0; i < n; i++)
    free((*matriz)[i]);
  free((*matriz));
}

/***********************************************************/

// Tranforma todos os elementos da matriz em zero
void zerarMatriz(int** matriz, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      matriz[i][j] = 0;
}

/***********************************************************/

// Adiciona n espaços pretos
void espacosPretos(int n) {
  for (int i = 0; i < n; i++)
    printf(BG_BLACK(" "));
}

/***********************************************************/

// Adiciona n espaços brancos
void espacosBrancos(int n) {
  for (int i = 0; i < n; i++)
    printf(BG_WHITE(" "));
}

/***********************************************************/

// Retorna o número de algarismos de n
int algarismos(int n) {
  if (n == 0){
    return 1; // Não é possível calcular o log de 0
  }
  return (int)log10(n) + 1; // Fórmula que dá o número de algarismos de n
}

/***********************************************************/

// Imprime o tabuleiro do jogo
void imprimirMatriz(int **matriz, int n, int pontuacao, int nTrocar, int nVoltar) {
  
  int x = algarismosMaiorNumero(&matriz, n); // quantidade de algarismos do maior número
  int larguraTab = 8*n + n*x + 2; // largura do tabuleiro
  int k = (184 - larguraTab) / 2; // espaços para centralizar o tabuleiro
  
  // Imprime a primeira linha
  espacos(k); // Centraliza o tabuleiro
  espacosBrancos(larguraTab);
  
  // Imprime as próximas 4 linhas n vezes
  for (int i = 0; i < n; i++) {
    
    // Imprime a linha 4i + 2
    printf("\n");
    espacos(k);
    for (int j = 0; j < n; j++) {
      printf(BG_WHITE("  "));
      espacosPretos(6 + x);
    }
    printf(BG_WHITE("  "));
    
    // Imprime a linha 4i + 3
    printf("\n");
    espacos(k);
    for (int j = 0; j < n; j++) {
      printf(BG_WHITE("  "));
      espacosPretos(3);
      
      int diferenca = x - algarismos(matriz[i][j]); // Quantos algarismos x tem a mais que devem ser compensados em espaços pretos
      int nEspacosE = (int)floor(diferenca / 2.0); // metade irá pra um lado
      int nEspacosD = (int)ceil(diferenca / 2.0); // a outra metade pro outro lado
      
      // Formatação para cada cor específica
      switch (matriz[i][j]) {
        case 0:
          espacosPretos(x); // imprimirá x vezes, que é a quantidade de algarismos do maior número da tabela
          break;
        case 2:
            espacosPretos(nEspacosE); 
            printf(BG_BLACK("\x1b[32m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 4:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[92m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 8:
            espacosPretos(nEspacosE);
            printf("\x1b[42;30m%d\x1b[0m", matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 16:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[33m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 32:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[93m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 64:
            espacosPretos(nEspacosE);
            printf("\x1b[43;30m%d\x1b[0m", matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 128:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[31m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 256:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[91m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 512:
            espacosPretos(nEspacosE);
            printf("\x1b[41;37m%d\x1b[0m", matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 1024:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[35m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 2048:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[95m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 4096:
            espacosPretos(nEspacosE);
            printf("\x1b[45;37m%d\x1b[0m", matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 8192:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[36m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 16384:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[96m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 32768:
            espacosPretos(nEspacosE);
            printf("\x1b[46;30m%d\x1b[0m", matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 65536:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[34m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        case 131072:
            espacosPretos(nEspacosE);
            printf(BG_BLACK("\x1b[94m%d\x1b[0m"), matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
        default:
            espacosPretos(nEspacosE);
            printf("\x1b[46;30m%d\x1b[0m", matriz[i][j]);
            espacosPretos(nEspacosD);
            break;
      }
      espacosPretos(3);
    }
    printf(BG_WHITE("  "));
    if (i == 0) { // Caso seja a linha 2 do tabuleiro
        printf(BOLD("    PONTUAÇÃO:") " %5d pontos", pontuacao);
    } else if (i == n - 1) { // Caso seja a linha  4n-4 do tabuleiro
        printf(BOLD("    TROCAR:") " Pode trocar duas peças %d vez", nTrocar);
        if (nTrocar != 1) {
          printf("es");
        }
    }
    printf("\n");
    
    // Imprime a linha 4i + 4
    espacos(k);
    for (int j = 0; j < n; j++) {
      printf(BG_WHITE("  "));
      espacosPretos(6 + x);
    }
    printf(BG_WHITE("  ") "\n");
    
    
    // Imprime a última linha
    espacos(k);
    espacosBrancos(larguraTab);
    if (i == n-1) {
      printf(BOLD("    DESFAZER:") " Pode desfazer o movimento %d vez", nVoltar);
      if (nVoltar != 1) {
        printf("es");
      }
    }
  }
}

/***********************************************************/

// Adiciona um bloco em uma casa vazia da matriz
int gerarBloco(int*** matriz, int n) {
  int tentativas = 0;
  int tentativasMax = n*n;

  int x; // índice aleatório da coluna
  int y; // índice aleatório da linha
  int r; // número aleatório entre 1 e 100

  do {
    x = rand()%n;
    y = rand()%n;
    r = (rand()%100) + 1;
    
    if ((*matriz)[x][y] == 0) { // Bloco está vazio
      if (r <= (5*n - 10)) { //"r" é menor que 5n-10. Efetivamente dá 10% de chance para n = 4, 15% para n = 5 e 20% para n = 6
        (*matriz)[x][y] = 4;
      } else {
        (*matriz)[x][y] = 2;
      }
      
      return 1; // Sucesso em gerar bloco
    }
    
    tentativas++;
    
  } while ((*matriz)[x][y] != 0 && tentativas < tentativasMax); // Enquanto o bloco sorteado estiver preenchido e não tiver excedido o limite de tentativas
  
  return 0; // Tentativas excederam o limite, falhou em gerar bloco.
}

/***********************************************************/

// Dá n espaços
void espacos(int n) {
  for (int i = 0; i < n; i++)
    printf(" ");
}

/***********************************************************/

// Realiza o movimento do tabuleiro
void moverMatriz(int*** m, int n, char c){
  switch (c) {
    case 'W': // Cima
      for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
        /*
         *    Começa aqui
         *    |   depois aqui
         *    v   v   ... ...
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * v [ ] [ ] [ ] [ ]
         *
         */
          if ((*m)[i][j] == 0) {
            for (int k = i+1; k < n; k++) { // Procura o próximo bloco preenchido na coluna
              if ((*m)[k][j] != 0) {
                (*m)[i][j] = (*m)[k][j];
                (*m)[k][j] = 0;
                break;
              }
            }
          }
        }
      }
      
      break;
    case 'A': // Esquerda
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        /*
         *                -------------->
         * Começa aqui -> [ ] [ ] [ ] [ ]
         * depois aqui -> [ ] [ ] [ ] [ ]
         *            ... [ ] [ ] [ ] [ ]
         *            ... [ ] [ ] [ ] [ ]
         *
         */
          if ((*m)[i][j] == 0) {
            for (int k = j+1; k < n; k++) { // Procura o próximo bloco preenchido na linha
              if ((*m)[i][k] != 0) {
                (*m)[i][j] = (*m)[i][k];
                (*m)[i][k] = 0;
                break;
              }
            }
          }
        }
      }

      break;
    case 'S': // Baixo
      for (int j = 0; j < n; j++) {
        for (int i = n-1; 0 <= i; i--) {
        /*
         * ^ [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         *    ^   ^   ... ...
         *    |   depois aqui
         *    Começa aqui
         *
         */
          if ((*m)[i][j] == 0) {
            for (int k = i-1; 0 <= k; k--) { // Procura o próximo bloco preenchido na  coluna
              if ((*m)[k][j] != 0) {
                (*m)[i][j] = (*m)[k][j];
                (*m)[k][j] = 0;
                break;
              }
            }
          }
        }
      }
    
      break;
    case 'D': // Direita
      for (int i = 0; i < n; i++) {
        for (int j = n-1; 0 <= j; j--) {
        /*
         * <--------------
         * [ ] [ ] [ ] [ ] <- Começa aqui
         * [ ] [ ] [ ] [ ] <- depois aqui
         * [ ] [ ] [ ] [ ] ...
         * [ ] [ ] [ ] [ ] ...
         *
         */
          if ((*m)[i][j] == 0) {
            for (int k = j-1; 0 <= k; k--) { // Procura o próximo bloco preenchido na linha
              if ((*m)[i][k] != 0) {
                (*m)[i][j] = (*m)[i][k];
                (*m)[i][k] = 0;
                break;
              }
            }
          }
        }
      }
    
      break;
  }
}

/***********************************************************/

void somarBlocos(int*** m, int n, char c, int* pontuacao, int* nTrocar, int* nVoltar) {
  switch (c) {
    case 'W': // Cima
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        /*
         *    Começa aqui
         *    |   depois aqui
         *    v   v   ... ...
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * v [ ] [ ] [ ] [ ]
         *
         */
        
          if (i + 1 < n && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i + 1][j]) { // Checa se o índice checado é válido e se os blocos são iguais
            (*m)[i][j] *= 2;
            (*m)[i + 1][j] = 0;
            
            (*pontuacao) += (*m)[i][j]; // Soma a pontuação
            
            if ((*m)[i][j] == BLOCOVOLTAR) { // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nVoltar) += 1;
            } else if ((*m)[i][j] == BLOCOTROCAR) {  // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nTrocar) += 1;
            }
          }
        }
      }
      break;
    case 'A': // Esquerda
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
        /*
         *                -------------->
         * Começa aqui -> [ ] [ ] [ ] [ ]
         * depois aqui -> [ ] [ ] [ ] [ ]
         *            ... [ ] [ ] [ ] [ ]
         *            ... [ ] [ ] [ ] [ ]
         *
         */
        if (j + 1 < n && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i][j+1]) { // Checa se o índice checado é válido e se os blocos são iguais
          (*m)[i][j] *= 2;
            (*m)[i][j + 1] = 0;
            
            (*pontuacao) += (*m)[i][j]; // Soma a pontuação
            
            if ((*m)[i][j] == BLOCOVOLTAR) { // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nVoltar) += 1;
            } else if ((*m)[i][j] == BLOCOTROCAR) {  // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nTrocar) += 1;
            }
          }
        }
      }
      break;
    case 'S': // Baixo
      for (int i = n-1; 0 <= i; i--) {
        for (int j = 0; j < n; j++) {
        /*
         * ^ [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         * | [ ] [ ] [ ] [ ]
         *    ^   ^   ... ...
         *    |   depois aqui
         *    Começa aqui
         *
         */
          if (i - 1 >= 0 && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i-1][j]) { // Checa se o índice checado é válido e se os blocos são iguais
            (*m)[i][j] *= 2;
            (*m)[i - 1][j] = 0;
            
            (*pontuacao) += (*m)[i][j]; // Soma a pontuação
            
            if ((*m)[i][j] == BLOCOVOLTAR) { // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nVoltar) += 1;
            } else if ((*m)[i][j] == BLOCOTROCAR) {  // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nTrocar) += 1;
            }
          }
        }
      }
      break;
    case 'D': // Direita
      for (int i = 0; i < n; i++) {
        for (int j = n-1; 0 <= j; j--) {
        /*
         * <--------------
         * [ ] [ ] [ ] [ ] <- Começa aqui
         * [ ] [ ] [ ] [ ] <- depois aqui
         * [ ] [ ] [ ] [ ] ...
         * [ ] [ ] [ ] [ ] ...
         *
         */
          if (j - 1 >= 0 && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i][j-1]) { // Checa se o índice checado é válido e se os blocos são iguais
            (*m)[i][j] *= 2;
            (*m)[i][j - 1] = 0;
            
            (*pontuacao) += (*m)[i][j]; // Soma a pontuação
            
            if ((*m)[i][j] == BLOCOVOLTAR) { // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nVoltar) += 1;
            } else if ((*m)[i][j] == BLOCOTROCAR) {  // Checa se foi formado um bloco que dá +1 "Voltar Jogada"
              (*nTrocar) += 1;
            }
          }
        }
      }
      break;
  }
}

/***********************************************************/

// Copia cada um dos elementos de uma matriz para outra
void copiarMatriz(int*** destino, int*** origem, int n) {
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      (*destino)[i][j] = (*origem)[i][j];
}

/***********************************************************/

// Transforma o tabuleiro atual no anterior e a última jogada se torna a que era a atual
void voltarJogada(int*** m, int ***mA) {
  int** aux = *m;
  *m = *mA;
  *mA = aux;
}

/***********************************************************/

// Retorna o número de algarismos do maior número da matriz
int algarismosMaiorNumero(int*** m, int n) {
  int maior = 0;
  
  // Descobre o maior valor do tabuleiro
  for (int i = 0; i < n ; i++)
    for (int j = 0; j < n ; j++)
      if ((*m)[i][j] > maior)
        maior = (*m)[i][j];
  
  return algarismos(maior);
}

/***********************************************************/

// Limpa o buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/***********************************************************/

// Converte o comando pra maiúsculo
void letraMaiuscula(char* comando) {
  if (97 <= (*comando) && (*comando) <= 122) // Checa se o texto está em minúsculo
    (*comando) -= 32; // Converte o texto para maiúsculo
}

/***********************************************************/

// Imprime mensagem de comando inválido
void invalido() {
  printf("\tComando inválido. Pressione enter para continuar.");
  limparBuffer();
}

/***********************************************************/

// Centraliza o texto no centro da tela
void centralizado(char *texto) {
  int tamanho, emANSI, n;
  
  tamanho = 0;
  emANSI = 0;
  
  // Conta o número de caracteres APENAS do texto visível
  for (int i = 0; texto[i] != '\0'; i++) {  
    if (texto[i] == '\x1b') { // início de um ANSI de formatação
      emANSI = 1;
      continue;
    }
      
    if (emANSI) { // Chegou ao final do ANSI de formatação. (\x1b...m)
      if (texto[i] == 'm') {
        emANSI = 0;
      }
      continue;
    }
    
    if (texto[i] != '"' && texto[i] != '\n') { // Ignora o restante dos caracteres não visíveis 
      if (texto[i] == '\t') {
        tamanho += 4;
      } else {
        tamanho += 1;
      }
    }
  }
  
  n = (184 - tamanho) / 2; // número de espaços a serem colocados à direita do texto
  
  espacos(n);
  printf("%s\n", texto);
}

/***********************************************************/

// Quebra n linhas
void quebrar(int n) {
  for (int i = 0; i < n; i++)
    printf("\n");
}

/***********************************************************/

// Dá TAB n vezes
void margem(int n) {
  for (int i = 0; i < n; i++)
    printf("\t");
}

/***********************************************************/

// Imprime o título do jogo
void imprimirTitulo() {
  centralizado(BG_WHITE("          ") "  " BG_WHITE("          ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("          "));
  centralizado("      " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    "));
  centralizado(BG_WHITE("          ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("          ") "  " BG_WHITE("          "));
  centralizado(BG_WHITE("  ") "          " BG_WHITE("  ") "    " BG_WHITE("    ") "        " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    "));
  centralizado(BG_WHITE("          ") "  " BG_WHITE("          ") "        " BG_WHITE("    ") "  " BG_WHITE("          "));
}

/***********************************************************/


