#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_RESET            "\x1b[0m"
#define ANSI_BOLD             "\x1b[1m"
#define ANSI_BG_COLOR_RED     "\x1b[41m"

#define BOLD(string)       ANSI_BOLD             string ANSI_RESET
#define BG_RED(string)     ANSI_BG_COLOR_RED     string ANSI_RESET

void limparBuffer();
void letraMaiuscula(char *comando);
void invalido();
void centralizado(char *texto);
void quebrar(int n);
void margem(int n);

int main() {
  int jogo = 1;
  while (jogo != 0) {
    char comando;
    
    system("clear");
    quebrar(4);
    centralizado(BG_RED(BOLD("2048!")) "\n\n\n");
    centralizado("by Angelo Resende\n\n");
    quebrar(3);
    centralizado("O que deseja fazer?\n\n");
    centralizado(BOLD("(N)") " Novo jogo\n");
    centralizado(BOLD("(J)") " Continuar jogo atual\n");
    centralizado(BOLD("(C)") " Carregar um jogo salvo\n");
    centralizado(BOLD("(S)") " Salvar o jogo atual\n");
    centralizado(BOLD("(M)") " Mostrar Ranking\n");
    centralizado(BOLD("(A)") " Ajuda com as instruções de como jogar\n");
    centralizado(BOLD("(R)") " Sair");
    
    quebrar(11);
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
          quebrar(2);
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
          quebrar(20);
          
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
          quebrar(19);
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
  int tamTxt, quebra, n, acentos;
  
  tamTxt = strlen(texto);
  quebra = 0;
  acentos = 0;
  
  // Calcular quebras e acentos
  for (int i = 0; i < tamTxt; i++)
    if (texto[i] == '\n')
      quebra += 1;
    else if (texto[i] == '´' || texto[i] == '`' || texto[i] == '~' || texto[i] == '^')
      acentos += 1;
  
  // Tamanho de espaços a serem colocados à esquerda do texto
  n = (184 - (tamTxt - quebra - acentos)) / 2;
  
  // Imprime o texto adicionando n espaços à esquerda
  printf("%*s\n", (int)(n + tamTxt), texto);
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
