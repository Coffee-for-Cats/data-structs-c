#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int num;
  struct node *next;
} Node;

typedef struct list {
  Node *first; 
} List;

void imprime_lista(Node *lista) {
  if(lista == NULL) printf("\n<A lista esta vazia>");
  else {
    Node *atual = lista;
    int pos = 0;
    while(atual) {
      printf("%d - %d \t | %p \n", pos++, atual->num, atual->next);
      atual = atual->next;
    }
  }
}

void inserir(Node **lista) {
  int index;
  do {
    printf("\nEm qual indice deseja inserir? ");
    scanf("%d", &index);
    if(index < 0) { printf("Valor invalido."); continue; };
  } while(index < 0);

  Node* new = malloc(sizeof(Node));
  printf("Digite o valor: ");
  int num;
  scanf("%d", &num);
  new->num = num;

  Node *atual = *lista;
  if(!atual || index == 0) {
    if(index != 0) printf("Indice invalido");
    else {
      // adiciona como primeiro digito
      new->next = atual;
      *lista = new;
    }
  } else {
    // "anda" até 1 antes do indice a ser adicionado
    for(int i = 1; i < index && atual; i++) {
      atual = atual->next;
    }
    if(!atual) {
      printf("Indice invalido!");
    } else {
      new->next = atual->next;
      atual->next = new;
    }
  }
}

void excluir() {
  //...
}

void insere_ordenado(Node **lista) {
  int num;
  printf("\n Digite o numero a adicionar: ");
  scanf("%d", &num);
  Node *new = malloc(sizeof(Node));
  new->num = num;
  if(!*lista) {
    printf("\nInserindo no comeco\n");
    // inserir no começo
    new->next = NULL;
    *lista = new;
  } else {
    Node *atual = *lista;
    // caminha até 1 antes do ponto onde quero adicioná-lo
    while(atual->next->num < num) atual = atual->next;
    new->next = atual->next;
    atual->next = new;
  }
}

int main() {
  Node *lista = NULL;

  int op;
  do {
    printf("LISTA ENCADEADA\n");
    imprime_lista(lista);

    printf("\nOque deseja fazer: \n 1- Inserir em posição x \n 2- Excluir em posição x\n 3- Inserir Ordenado \n 4- Sair\n");
    do {
      scanf("%d", &op);
    } while(op < 1 || op > 4);

    switch(op) {
      case 1:
        inserir(&lista);
        break;
      case 2:
        excluir(&lista);
        break;
      case 3:
        insere_ordenado(&lista);
        break;
      case 4:
        printf("Saindo...");
    }
  } while(op != 4);
}