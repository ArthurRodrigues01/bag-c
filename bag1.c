#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BACKPACK_CAP 10
#define MAX_NAME_LEN 30
#define MAX_TYPE_LEN 20

typedef struct Item {
  char* name;
  char* type;
  int quant;
  struct Item* next;
} Item;

Item* getLast(Item* head);
Item* getPrevious(Item* head, Item* item);
bool push(Item** head, Item* item);
bool rmItem(Item** head, char* itemName);
int getSize(Item* head);
void cleanInputBuffer();
void freeMemory(Item* head);
void printActionMenu(int* option, int size);
void printInsertItemMenu(Item* temp);
void printList(Item* head);
void printRemoveItemMenu(char* itemName);

int main() {
  Item* head = (Item*) calloc(1, sizeof(Item));
  Item* temp = (Item*) calloc(1, sizeof(Item)); 
  temp->name = (char*) malloc((MAX_NAME_LEN + 1) * sizeof(char));
  temp->type = (char*) malloc((MAX_TYPE_LEN + 1) * sizeof(char));
  int option, size;
  char name[MAX_NAME_LEN];

  if (head == NULL || temp == NULL) {
    printf("Falha na alocacao de memoria!\n");
    return 1;
  }

  do {
    size = getSize(head);
    printActionMenu(&option, size);

    switch(option) {
      case 1: // adicionar item
        if (size == MAX_BACKPACK_CAP) {
          printf("\nMochila lotada!\n");
          printf("E necessario remover alguma coisa, para adicionar outro item.\n");
          break;
        }

        printInsertItemMenu(temp);
        if (push(&head, temp)) { // inseriu com sucesso
          printf("\nItem inserido com sucesso!\n");
          printList(head);
          break;
        } 
        printf("\nFalha na insercao do item!\n");

        break;
      case 2: // remover item
        printRemoveItemMenu(name);
        if (rmItem(&head, name)) {
          printf("\nItem removido com sucesso!\n");
          printList(head);
          break;
        }
        printf("\n Falha na remocao do item!\n");
        
        break;
      case 3: // listar itens
        printList(head);
        break;
      case 0: // sair
        printf("\nSaindo do programa...\n");
        break;
      default:
        if (option < 0 || option > 3) {
          printf("\nPor favor digite uma opcao valida!\n");
        }
    }

    system("pause");
  } while (option != 0);
  
  free(temp->name);
  free(temp->type);
  free(temp);
  freeMemory(head);
  printf("\nMemoria liberada.");
  return 0;
}

Item* getLast(Item* head) {
  Item* curr = head;

  while (curr->next != NULL) {
    curr = curr->next;
  }

  return curr;
}
Item* getPrevious(Item* head, Item* item) {
  Item* curr = head;

  while (curr != NULL) {
    if (curr->next == item) return curr;

    curr = curr->next;
  }

  return NULL;
}
bool push(Item** head, Item* item) {
  if ((*head)->name == NULL) {
    (*head)->name = strdup(item->name);
    (*head)->type = strdup(item->type);
    (*head)->quant = item->quant;

    return true;
  }
  Item* new = (Item*) malloc(sizeof(Item));

  if (new == NULL) return false; // falhou na alocacao de memoria

  Item* last = getLast(*head);

  new->name = strdup(item->name);
  new->type = strdup(item->type);
  new->quant = item->quant;
  new->next = NULL;
  
  last->next = new;
  last = new;

  return true;
}
bool rmItem(Item** head, char* itemName) {
  Item* curr = *head;
  
  while (curr != NULL && curr->name != NULL) {
    if (strcmp(curr->name, itemName) == 0) {
      if (curr == *head) { // é o primeiro item
        if (curr->next == NULL) { // só tem um item na lista
          curr->name = NULL;
          curr->type = NULL;
          curr->quant = -1;
          
          return true;
        } else {
          *head = curr->next;
        }
      } else { // não é o primeiro item
        Item* prev = getPrevious(*head, curr);
        
        prev->next = curr->next;
      }
      
      free(curr->name);
      free(curr->type);
      free(curr);
      return true; // removeu alguma coisa
    }
    
    curr = curr->next;
  }
  
  return false; // não removeu nada
}
int getSize(Item* head) {
  Item* curr = head;
  int size = 0;

  while (curr != NULL && curr->name != NULL) {
    curr = curr->next;
    size++;
  }
  
  return size;
}
void cleanInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c !=  EOF);
}
void printActionMenu(int* option, int size) {
  printf("\n==================================\n");
  printf("     MOCHILA DE SOBREVIVENCIA     \n");
  printf("==================================\n");
  printf("Itens na mochila: %d/%d\n\n", size, MAX_BACKPACK_CAP);
  printf("1 - Adicionar Item\n");
  printf("2 - Remover Item\n");
  printf("3 - Listar Itens na Mochila\n");
  printf("0 - Sair\n");
  printf("----------------------------------\n");
  printf("Escolha uma opcao: ");
  scanf("%d", option);
  cleanInputBuffer();
}
void printList(Item* head) {
  Item* curr = head;
  printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", getSize(head), MAX_BACKPACK_CAP);
  printf("----------------------------------------------------------\n");
  printf("NOME  | TIPO  | QUANTIDADE  \n");
  printf("----------------------------------------------------------\n");
  while (curr != NULL) {
    printf("%s", curr->name);
    printf(" | ");
    printf("%s", curr->type);
    printf(" | ");
    printf("%d\n", curr->quant);
    
    curr = curr->next;
  }
  printf("----------------------------------------------------------\n");
}
void printInsertItemMenu(Item* temp) {
  printf("\n--- Adicionar Novo Item ---\n");
  printf("Nome do item: ");
  fgets(temp->name, MAX_NAME_LEN, stdin);
  temp->name[strcspn(temp->name, "\n")] = 0;

  printf("Tipo do item: ");
  fgets(temp->type, MAX_TYPE_LEN, stdin);
  temp->type[strcspn(temp->type, "\n")] = 0;
  
  printf("Quantidade: ");
  scanf("%d", &temp->quant);
  cleanInputBuffer();
}
void printRemoveItemMenu(char* itemName) {
  printf("\n--- Remover Item ---\n");
  printf("Nome do Item: ");
  fgets(itemName, MAX_NAME_LEN, stdin);
  itemName[strcspn(itemName, "\n")] = 0;
} 
void freeMemory(Item* head) {
  Item* curr = head;

  while (curr != NULL) {
    Item* temp = curr;

    free(curr->name);
    free(curr->type);
    curr = temp->next;
    free(temp);
  }
}