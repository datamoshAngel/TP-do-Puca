#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void imprimirMatriz(int** matriz, int n);
void gerarBloco(int*** matriz, int n);
void espacos(int n);
void moverMatriz(int*** m, int*** mA, int n, char c);

void limparBuffer();
void letraMaiuscula(char* comando);
void invalido();
void centralizado(char *texto);
void quebrar(int n);
void margem(int n);
void imprimirTitulo();

int main() {
  int **matriz, **matrizAnterior;
  int jogo = 1;
  int n = 0;
  srand(time(NULL));
  
  do{
  
    system("clear");
    
    quebrar(4);
    imprimirTitulo();
    quebrar(10);
    
    centralizado("Escolha o modo de jogo:");
    centralizado(BOLD("(4)") " Jogo 4x4");
    centralizado(BOLD("(5)") " Jogo 5x5");
    centralizado(BOLD("(6)") " Jogo 6x6");
    
    quebrar(18);
    printf("\t" BOLD("Comando: "));
    scanf("%d", &n);
    limparBuffer();
    
    if (n < 4 || 6 < n)
      invalido();
    
  }while (n < 4 || 6 < n);
  
  // Alocar a matriz tabuleiro
  matriz = malloc(n * sizeof(int*));
  matrizAnterior = malloc(n * sizeof(int*));
  
  for (int i = 0; i < n; i++) {
    matriz[i] = malloc(n * sizeof(int));
    matrizAnterior[i] = malloc(n * sizeof(int));
  }
  
  // Zerar a matriz
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++) {
      matriz[i][j] = 0;
      matrizAnterior[i][j] = 0
    }
  
  /* ----- JOGO ----- */
  
  while (jogo == 1) {
    system("clear");
    quebrar(2);
    imprimirTitulo();
    
    quebrar(11-n);
    gerarBloco(&matriz, n);
    imprimirMatriz(matriz, n);
    quebrar(13-n);
    
    centralizado(BOLD("<W, A, S, D>") " Mover    " BOLD("<U>") " Dezfazer último movimento    " BOLD("<T> <Posição 1> <Posição 2>") " Troca a peça 1 pela peça 2    " BOLD("<V>") " Volta para o menu inicial");
    
    char comando2[3]; // 1 caractere + enter + \0 -> Garante que apenas aceite um caractere, e não uma palavra
    printf("\n\t" BOLD("Comando: "));
    fgets(comando2, 3, stdin);
    letraMaiuscula(comando2);

    if (strcmp(comando2, "W\n") == 0 || strcmp(comando2, "A\n") == 0 || strcmp(comando2, "S\n") == 0 || strcmp(comando2, "D\n") == 0) {
    
      moverMatriz(&matriz, &matrizAnterior, n, comando2[0]);
      
    } else if (strcmp(comando2, "U\n") == 0) {
      
    } else if (strcmp(comando2, "T\n") == 0) {
      
    } else if (strcmp(comando2, "V\n") == 0) {
        jogo = 0;
        system("clear");
        break;
    }
  }
  
  // Liberar memória alocada
  for (int i = 0; i < n; i++)
    free(matriz[i]);
  free(matriz);
  
  return 0;
}

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

// Adiciona n espaços
void espacos(int n) {
  for (int i = 0; i < n; i++)
    printf(" ");
}

void moverMatriz(int*** m, int*** mA, int n, char c){
  switch (c) {
    case 'W':
      
      for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
          
        
      break;
    case 'A':
      break;
    case 'S':
      break;
    case 'D':
      break;
  }
}

/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

// Limpa o buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Converte o comando para maiúsculo, se necessário.
void letraMaiuscula(char* comando) {
  for (int i = 0; i < 7; i++)
    if (97 <= (*comando) && (*comando) <= 122) // Checa se o texto está em minúsculo
      (*comando) -= 32; // Converte o texto para maiúsculo
}

// Imprime mensagem de comando inválido
void invalido() {
  printf("\tComando inválido. Pressione enter para continuar.");
  limparBuffer();
}

// Centraliza o texto no centro da tela
void centralizado(char *texto) {
  int tamanho, emANSI, n;
  
  tamanho = 0;
  emANSI = 0;
  
  // Conta o tamanho do texto entre aspas 
  for (int i = 0; texto[i] != '\0'; i++) {
  
  // Faz com que, para calcular o número de espaços, conte APENAS o texto visível
    if (texto[i] == '\x1b') { // Início de um \ de formatação
      emANSI = 1;
      continue;
    }
      
    if (emANSI) { // Significa que chegou ao final do ANSI de formatação.
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
  
  // N é o número de espaços a serem colocados à esquerda do texto
  n = (184 - tamanho) / 2;
  
  // Imprime n espaços à esquerda e depois imprime o texto
  for (int i = 0; i < n; i++){
    printf(" ");
  }
  
  printf("%s\n", texto);
}

// Quebra n linhas
void quebrar(int n) {
  for (int i = 0; i < n; i++)
    printf("\n");
}

// Adiciona '\t' n vezes
void margem(int n) {
  for (int i = 0; i < n; i++)
    printf("\t");
}

// Imprime o título do jogo
void imprimirTitulo() {
  centralizado(BG_WHITE("          ") "  " BG_WHITE("          ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("          "));
  centralizado("      " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    "));
  centralizado(BG_WHITE("          ") "  " BG_WHITE("  ") "    " BG_WHITE("    ") "  " BG_WHITE("          ") "  " BG_WHITE("          "));
  centralizado(BG_WHITE("  ") "          " BG_WHITE("  ") "    " BG_WHITE("    ") "        " BG_WHITE("    ") "  " BG_WHITE("  ") "    " BG_WHITE("    "));
  centralizado(BG_WHITE("          ") "  " BG_WHITE("          ") "        " BG_WHITE("    ") "  " BG_WHITE("          "));
} // A fonte usada chama Neo Jazz e foi feita por mim em 2023.
