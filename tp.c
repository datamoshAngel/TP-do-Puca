#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void letraMaiuscula(char *comando);

int main(){
  int jogo = 1;
  while (jogo != 0){
    char *comando;
    
    system("clear");
    printf("\n2048!\n\nby Angelo Resende\n\n\n\n\nO que deseja fazer?\n\n\n");
    printf("(N) Novo jogo\n\n");
    printf("(J) Continuar jogo atual\n\n");
    printf("(C) Carregar um jogo salvo\n\n");
    printf("(S) Salvar o jogo atual\n\n");
    printf("(M) Mostrar Ranking\n\n");
    printf("(A) Ajuda com as instruções de como jogar\n\n");
    printf("(R) Sair\n\n");
    
    printf("\tComando: "); scanf("%c", comando);
    letraMaiuscula(comando);
    
    switch (*comando){
      case 'N':
        printf("Carregando novo jogo!"); break;
      case 'J':
        printf("Continuando jogo!"); break;
      case 'C':printf("\n\n(R) Voltar ao menu\n\n\tComando: ");
        printf("Carregando jogo!"); break;
      case 'S':
        printf("Salvando jogo!"); break;
      case 'M':
        printf("*Abrindo Ranking*"); break;
      case 'A':
        while (1 != 0){
          system("clear");
          printf("\t2048 é um jogo de raciocínio onde o objetivo é deslizar peças numeradas em um tabuleiro e combiná-las até formar um bloco com o número 2048.");
          printf("\n\n\t- O jogador desliza as peças em um dos quatro sentidos (cima, baixo, esquerda e direita)\n");
          printf("\n\t- A cada movimento, um novo número aparece aleatoriamente em um local vazio do tabuleiro.\n");
          printf("\n\t- As peças deslizam o mais longe possível até colidirem.\n");
          printf("\n\t- Duas peças iguais que se colidirem irão se fundir em uma peça com o valor total das duas peças.\n");
          printf("\n\nEsse é o 2048.");
          printf("\n\n(R) Voltar ao menu\n\n\tComando: ");
          scanf("%c", comando); letraMaiuscula(comando); 
          if (*comando == 'R')
            break;
          else
            printf("Comando inválido.");
        }
        
      case 'R':
        printf("\nTem certeza que deseja sair?\n(S) Sim\n(N) Não");
        printf("\n\n\tComando: ");
        scanf("%c", comando); letraMaiuscula(comando);
        if (*comando == 'S')
          jogo = 0;
        else if (*comando != 'N')
          printf("Comando inválido.");
        break;
      case '\n':
        system("clear");
      default:
        system("clear");
        printf("Comando inválido\n");
        break;
    }
  }
  
  return 0;
}

void letraMaiuscula(char *comando){
  if (97 <= *comando && *comando <= 122)
    *comando -= 32;
}
