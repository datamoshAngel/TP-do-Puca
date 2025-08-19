#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_RESET            "\x1b[0m"
#define ANSI_BOLD             "\x1b[1m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"

#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

void limparBuffer();
void letraMaiuscula(char *comando);
void invalido();
void centralizado(char *texto);
void quebrar(int n);
void margem(int n);
void imprimirTitulo();

int main() {
  int jogo = 1;
  while (jogo != 0) {
    char comando;
    
    system("clear");
    quebrar(4);
    imprimirTitulo();
    quebrar(1);
    centralizado("Angelo Resende da Silva              25.1.4013\n\n");
    quebrar(3);
    centralizado("O que deseja fazer?\n\n");
    centralizado(BOLD("(N)") " Novo jogo\n");
    centralizado(BOLD("(J)") " Continuar jogo atual\n");
    centralizado(BOLD("(C)") " Carregar um jogo salvo\n");
    centralizado(BOLD("(S)") " Salvar o jogo atual\n");
    centralizado(BOLD("(M)") " Mostrar Ranking\n");
    centralizado(BOLD("(A)") " Ajuda com as instruções de como jogar\n");
    centralizado(BOLD("(R)") " Sair");
    
    quebrar(9);
    printf("\t" BOLD("Comando:") " ");
    scanf(" %c", &comando);
    limparBuffer();
    letraMaiuscula(&comando);
    
    switch (comando) {
      case 'N':
        printf("Carregando novo jogo!");
        break;
      case 'J':
        printf("Continuando jogo!");
        break;
      case 'C':
        printf("Carregando jogo!");
        break;
      case 'S':
        printf("Salvando jogo!");
        break;
      case 'M':
        printf("*Abrindo Ranking*");
        break;
      case 'A':
        while (1 != 0) {
          system("clear");
          quebrar(4);
          imprimirTitulo();
          quebrar(6);
          margem(4);
          printf("2048 é um jogo de raciocínio onde o objetivo é deslizar peças numeradas em um tabuleiro e combiná-las até formar um\n"); 
          margem(4);
          printf("bloco com o número 2048.\n\n\n");
          margem(5);
          printf("- O jogador desliza as peças em um dos quatro sentidos (cima, baixo, esquerda e direita)\n\n");
          margem(5);
          printf("- A cada movimento, um novo número aparece aleatoriamente em um local vazio do tabuleiro.\n\n");
          margem(5);
          printf("- As peças deslizam o mais longe possível até colidirem.\n\n");
          margem(5);
          printf("- Duas peças iguais que se colidirem irão se fundir em uma peça com o valor total das duas peças.\n\n\n");
          margem(4);
          printf("Esse é o 2048.");
          
          quebrar(5);
          centralizado(BOLD("(R)") " Voltar ao menu");
          quebrar(7);
          
          printf("\t" BOLD("Comando:") " ");
          char comando2;
          scanf(" %c", &comando2);
          limparBuffer();
          letraMaiuscula(&comando2); 
          
          if (comando2 == 'R')
            break;
          else
            invalido();
        }
        break;
      case 'R':
        while(1 != 0) {
          system("clear");
          quebrar(4);
          imprimirTitulo();
          quebrar(10);
          centralizado("Tem certeza que deseja sair?");
          centralizado(BOLD("(S)") " Sim");
          centralizado(BOLD("(N)") " Não");
          quebrar(19); 
          printf("\t" BOLD("Comando:") " ");
          
          char confirma;
          scanf(" %c", &confirma);
          limparBuffer();
          letraMaiuscula(&confirma);
          
          if (confirma == 'S') {
            jogo = 0;
            break;
          }
          else if (confirma == 'N') {
            break;
          }
          else {
            invalido();
          }
        }
          break; 
        default:
          invalido();
          break;
    }
  }
  
  return 0;
}

// Limpa o buffer
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Converte o comando para maiúsculo, se necessário.
void letraMaiuscula(char *comando) {
  if (97 <= *comando && *comando <= 122)
    *comando -= 32;
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
    if (texto[i] == '\x1b') {
      emANSI = 1;
      continue;
    }
      
    if (emANSI) {
      if (texto[i] == 'm') {
        emANSI = 0;
      }
      continue;
    }
    
    if (texto[i] != '"' && texto[i] != '\n') {
      tamanho += 1;
    }
  }
  
  // Número de espaços a serem colocados à esquerda do texto
  n = (184 - tamanho) / 2;
  
  // Imprime o texto adicionando n espaços à esquerda
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
}
