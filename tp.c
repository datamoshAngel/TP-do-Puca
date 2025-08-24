#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/**************************** CONSTANTES ***************************/

// Constantes minhas
#define BLOCOVOLTAR 4

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
void quebrar(int n);
void margem(int n);
void centralizado(char *texto);
void letraMaiuscula(char* comando);
void invalido();

// Funções do jogo
void imprimirMatriz(int** matriz, int n);
void gerarBloco(int*** matriz, int n);
void moverMatriz(int*** m, int n, char c);
void somarBlocos(int*** m, int n, char c, int* nVoltar);
void copiarMatriz(int*** destino, int*** origem, int n);
void voltarJogada(int*** m, int ***mA);
int algarismosMaiorNumero(int*** m, int n);

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
      int nVoltar = 0;
      int gerar = 1;
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
        quebrar(18);
        
        // Inserir comando
        printf("\t" BOLD("Comando: "));
        scanf("%d", &tamanho);

        if (tamanhoTabuleiro < 4 || 6 < tamanhoTabuleiro) { // Aceita apenas os tamanhos válidos
          limparBuffer();
          invalido();
        }
        
      } while (tamanhoTabuleiro < 4 || 6 < tamanhoTabuleiro);
      
      // Alocar a matriz tabuleiro o tabuleiro anterior
      matriz = malloc(tamanhoTabuleiro * sizeof(int*));
      matrizAnterior = malloc(tamanhoTabuleiro * sizeof(int*));
      for (int i = 0; i < tamanhoTabuleiro; i++) {
        matriz[i] = malloc(tamanhoTabuleiro * sizeof(int));
        matrizAnterior[i] = malloc(tamanhoTabuleiro * sizeof(int));
      }
      
      // Zerar as matrizes
      for (int i = 0; i < tamanhoTabuleiro; i++)
        for (int j = 0; j < tamanhoTabuleiro; j++) {
          matriz[i][j] = 0;
          matrizAnterior[i][j] = 0;
        }
      
      /* ----- JOGO ----- */
      while (jogo) {
        system("clear");
        
        // Imprimir cabeçário
        quebrar(2);
        imprimirTitulo(); 
        
        // Confirmar se deve gerar um bloco novo
        if (!gerar) {
          gerar = 1;
        } else {
          gerarBloco(&matriz, tamanhoTabuleiro);
        }
        
        // Imprimir tabuleiro
        quebrar(13-2*tamanhoTabuleiro);
        imprimirMatriz(matriz, tamanhoTabuleiro);
        quebrar(14-2*tamanhoTabuleiro);
        
        // Imprimir opções
        centralizado(BOLD("<W, A, S, D>") " Mover");
        centralizado(BOLD("<U>") " Dezfazer último movimento");
        centralizado(BOLD("<T> <Posição 1> <Posição 2>") " Troca a peça 1 pela peça 2");
        centralizado(BOLD("<V>") " Volta para o menu inicial");
        
        // Imprimir informações
        printf("Voltar: %d", nVoltar);
        quebrar(2);
        
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
          somarBlocos(&matriz, tamanhoTabuleiro, comando2[0], &nVoltar);
          moverMatriz(&matriz, tamanhoTabuleiro, comando2[0]);
          
        } else if (strcmp(comando2, "U\n") == 0) { // Retorna o tabuleiro para o movimento anterior ******************************/
          if (nVoltar > 0) {
            voltarJogada(&matriz, &matrizAnterior);
            nVoltar--;
          }
          gerar = 0; // Faz com que o tabuleiro não seja alterado
        } else if (strcmp(comando2, "T\n") == 0) { // Troca 2 peças de lugar *****************************************************/
          
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
      for (int i = 0; i < tamanhoTabuleiro; i++) {
        free(matriz[i]); free(matrizAnterior[i];
      }
      free(matriz); free(matrizAnterior);
    
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
          jogo = 0; // Encerra o jogo
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

// Imprime o tabuleiro do jogo
void imprimirMatriz(int **matriz, int n) {
  
  int larguraTab = 9*n + 2; // Largura do tabuleiro
  int k = (184 - larguraTab) / 2; // Espaços para centralizar o tabuleiro
  
  espacos(k);
  for (int i = 0; i < larguraTab; i++) // Imprime uma linha branca
    printf(BG_WHITE(" "));
  
  for (int i = 0; i < n; i++) {
    printf("\n");
    espacos(k);
    for (int j = 0; j < n; j++) // Imprime um quadrado branco, um espaçamento
      printf(BG_WHITE("  ") "       ");
    printf(BG_WHITE("  ")); // Imprime um quadrado branco pra fechar a linha
    
    printf("\n");
    espacos(k);
    for (int j = 0; j < n; j++)
      printf(BG_WHITE("  ") "   %d   ", matriz[i][j]); // Imprime um quadrado branco e um espaçamento com o número no meio
    printf(BG_WHITE("  ") "\n"); // Imprime um quadrado branco pra fechar a linha
    espacos(k);
    
    for (int j = 0; j < n; j++) // Imprime um quadrado branco, um espaçamento
      printf(BG_WHITE("  ") "       ");
    printf(BG_WHITE("  ") "\n"); // Imprime um quadrado branco pra fechar a linha
    espacos(k);
    
    for (int j = 0; j < larguraTab; j++) // Imprime uma linha branca
      printf(BG_WHITE(" "));
  }
}

/***********************************************************/

// Adiciona um bloco em uma casa vazia da matriz
void gerarBloco(int*** matriz, int n) {
  int x = rand()%n;
  int y = rand()%n;
  int r = rand()%10;

  do {
    x = rand()%n;
    y = rand()%n;
    r = rand()%10;
    
    if ((*matriz)[x][y] == 0) {
      if (r != 0) {
        (*matriz)[x][y] = 2;
        break;
      } else {
        (*matriz)[x][y] = 4;
        break;
      }
    }
  } while ((*matriz)[x][y] != 0);
}

/***********************************************************/

// Adiciona n espaços
void espacos(int n) {
  for (int i = 0; i < n; i++)
    printf(" ");
}

/***********************************************************/

// Realiza o movimento do tabuleiro
void moverMatriz(int*** m, int n, char c){
  switch (c) {
    case 'W':
      
      for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
          if ((*m)[i][j] == 0) {
            for (int k = i+1; k < n; k++) {
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
    case 'A':

      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if ((*m)[i][j] == 0) {
            for (int k = j+1; k < n; k++) {
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
    case 'S':
    
      for (int j = 0; j < n; j++) {
        for (int i = n-1; 0 <= i; i--) {
          if ((*m)[i][j] == 0) {
            for (int k = i-1; 0 <= k; k--) {
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
    case 'D':
    
      for (int i = 0; i < n; i++) {
        for (int j = n-1; 0 <= j; j--) {
          if ((*m)[i][j] == 0) {
            for (int k = j-1; 0 <= k; k--) {
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

void somarBlocos(int*** m, int n, char c, int* nVoltar) {
  switch (c) {
    case 'W':
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (i + 1 < n && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i + 1][j]) {
            (*m)[i][j] *= 2;
            (*m)[i + 1][j] = 0;
            
            if ((*m)[i][j] == BLOCOVOLTAR) {
              (*nVoltar) += 1;
            }
          }
        }
      }
      break;
    case 'A':
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          if (j + 1 < n && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i][j+1]) {
            (*m)[i][j] *= 2;
            (*m)[i][j + 1] = 0;
            
            if ((*m)[i][j] == BLOCOVOLTAR) {
              (*nVoltar) += 1;
            }
          }
        }
      }
      break;
    case 'S':
      for (int i = n-1; 0 <= i; i--) {
        for (int j = 0; j < n; j++) {
          if (i - 1 >= 0 && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i-1][j]) {
            (*m)[i][j] *= 2;
            (*m)[i - 1][j] = 0;
            
            if ((*m)[i][j] == BLOCOVOLTAR) {
              (*nVoltar) += 1;
            }
          }
        }
      }
      break;
    case 'D':
      for (int i = 0; i < n; i++) {
        for (int j = n-1; 0 <= j; j--) {
          if (j - 1 >= 0 && (*m)[i][j] != 0 && (*m)[i][j] == (*m)[i][j-1]) {
            (*m)[i][j] *= 2;
            (*m)[i][j - 1] = 0;
            
            if ((*m)[i][j] == BLOCOVOLTAR) {
              (*nVoltar) += 1;
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
  
  if (maior == 0)
    return 1; // Não é possível calcular log 0
  
  return (int)log10(maior) + 1; // equação que retorna o número de algarismos de um número
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
} // A fonte usada se chama Neo Jazz e foi feita por mim em 2023. :)

/***********************************************************/


