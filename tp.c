#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void limparBuffer();
void letraMaiuscula(char *comando);
void invalido();
void centralizado(char *texto);
void quebrar(int n);

int main() {
  int jogo = 1;
  while (jogo != 0) {
    char comando;
    
    system("clear");
    printf("\n\n\n");
    centralizado("2048!\n\n");
    centralizado("by Angelo Resende\n\n\n\n");
    centralizado("O que deseja fazer?\n\n\n");
    centralizado("(N) Novo jogo\n\n");
    centralizado("(J) Continuar jogo atual\n\n");
    centralizado("(C) Carregar um jogo salvo\n\n");
    centralizado("(S) Salvar o jogo atual\n\n");
    centralizado("(M) Mostrar Ranking\n\n");
    centralizado("(A) Ajuda com as instruções de como jogar\n\n");
    centralizado("(R) Sair\n\n");
    
    printf("\n\n\n\n\n\tComando: ");
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
          printf("\n\n\t\t\t\t2048 é um jogo de raciocínio onde o objetivo é deslizar peças numeradas em um tabuleiro e combiná-las até formar um\n"); 
          printf("\t\t\t\tbloco com o número 2048.\n");
          printf("\n\n\t\t\t\t\t- O jogador desliza as peças em um dos quatro sentidos (cima, baixo, esquerda e direita)\n");
          printf("\n\t\t\t\t\t- A cada movimento, um novo número aparece aleatoriamente em um local vazio do tabuleiro.\n");
          printf("\n\t\t\t\t\t- As peças deslizam o mais longe possível até colidirem.\n");
          printf("\n\t\t\t\t\t- Duas peças iguais que se colidirem irão se fundir em uma peça com o valor total das duas peças.\n");
          printf("\n\n\t\t\t\tEsse é o 2048.\n\n");
          
          centralizado("(R) Voltar ao menu\n\n\tComando: ");
          
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
          centralizado("(S) Sim");
          centralizado("(N) Nao");
          quebrar(19);
          printf("\tComando: ");
          
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
    else if (texto[i] == '´' || 
      acentos += 1;
  
  // Tamanho de espaços a serem colocados à esquerda do texto
  n = (184 - (tamTxt - quebra - acentos)) / 2;
  
  // Imprime o texto adicionando n espaços à esquerda
  printf("%*s", (int)(n + tamTxt), texto);
}

// Quebra n linhas
void quebrar(int n) {
  for (int i = 0; i < n; i++)
    printf("\n");
}
