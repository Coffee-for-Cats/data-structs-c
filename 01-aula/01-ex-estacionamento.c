//Exercício . Considere que um estacionamento da Rua Direita, em Porto alegre, que é composto por uma única alameda que vários carros. Existe apenas uma entrada/saída no estacionamento, e esta extremidade da alameda dá acesso justamente à Rua Direita. Se chegar um cliente para retirar um carro que não seja o mais próximo da saída, todos os carros bloqueando seu caminho sairão do estacionamento. O carro do cliente será manobrado para fora do estacionamento, e os outros carros voltarão a ocupar a mesma sequência inicial. Escreva um programa que processe um grupo de linhas de entrada. Cada linha de entrada contém um 'E' ou 1, de entrada, ou um 'S' ou 2 de saída, e o número da placa do carro.  Presume-se que os carros cheguem e partam na mesma ordem que entraram no estacionamento. O programa deve imprimir uma mensagem sempre que um carro  chegar ou sair. Quando um carro chegar, a mensagem deve especificar se existe ou não vaga para o carro no estacionamento. Se não houver vaga, o carro partirá sem entrar no estacionamento. Quando um carro sair do estacionamento, a mensagem deverá incluir o número de vezes em que o carro foi manobrado para fora do estacionamento para permitir que os outros carros saíssem

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define total_vagas 4

typedef struct node {
  char sign[8];
  struct node* next;
} Node;

typedef struct park {
  int max;
  int free;
  Node* first;
} Park;

void print_rec(Node* atual) {
  printf("\n- %s", atual->sign);
  if(atual->next) print_rec(atual->next);
}

Node* look_for(Node* atual, char* sign) {
  if(atual == NULL) return NULL;
  if(strcmp(atual->sign, sign) == 0) return atual;
  else return look_for(atual->next, sign);
}

void try_enter(Park* Parking, char* sign) {
  if(Parking->free < 1) {
    printf("\nCarro %s passou reto pois o estacionamento estava cheio.", sign);
    return;
  }

  // pilha ( >->)
  Node* new_car = malloc(sizeof(Node));
  strcpy(new_car->sign, sign);
  new_car->next = Parking->first;
  Parking->first = new_car;
  Parking->free--;
  printf("\nCarro de placa %s entrou.", sign);
}

void get_out(Park* Parking, char* sign) {
  Node* is_there = look_for(Parking->first, sign);
  if(!is_there) {
    printf("\nO carro %s nao esta no estacionamento!", sign);
    return;
  }
  Node* temp[total_vagas]; int i = 0;
  Node* atual = Parking->first;
  for(; strcmp(atual->sign, sign) != 0; atual = atual->next) {
    printf("\nO carro %s saiu", atual->sign);
    temp[i++] = atual;
    Parking->first = atual;
  }
  i--;
  // remove o item da lista e da free()
  temp[i]->next = atual->next;
  printf("\nO carro %s conseguiu sair do estacionamento.", atual->sign);
  free(atual);

  printf("\nOs carros que tinham saido vao voltar ao estacionamento.");
  for(atual = temp[i]; i > 0; atual = temp[i--]) {
    printf("\nO carro %s entrou novamente", atual->sign);
    Parking->first = atual;
  }
  Parking->free++;
}

int main() {
  int vagas_disp = total_vagas;

  Park Parking = {max: 4, free: 4, first: NULL};

  printf("\nDigite o nome do arquivo: ");
  char file_name[40];
  gets(file_name);
  FILE* input = fopen(file_name, "r");
  if(!input) {
    printf("\nArquivo nao encontrado!");
    return 1;
  }
  
  char line[20];
  while(fgets(line, 20, input)) {
    // primeiro char da linha, é sempre E de entrada ou S de saída.
    char op = line[0];
    // suporto comentários!
    if(op == '#') continue;

    // depois, temos um espaço e 7 dígitos da placa do carro
    char sign[20];
    strcpy(sign, &line[2]); // pega um \n a mais no final
    sign[7] = '\0';         // limpa esse \n
    
    strupr(sign);

    switch(op) {
      case 'E': {
        printf("\nCarro de placa %s tenta entrar.", sign);
        try_enter(&Parking, sign);
        break;
      }
      case 'S': {
        printf("\nCarro de placa %s quer sair.", sign);
        get_out(&Parking, sign);
        break;
      }
      default: {
        printf("\nErro de formatacao de arquivo!");
      }
    }
  }
  printf("\nEstacionamento final: ");
  print_rec(Parking.first);
}