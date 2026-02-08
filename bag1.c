#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BACKPACK_CAP 10
#define MAX_NAME_LEN 30
#define MAX_TYPE_LEN 20

typedef struct Item {
  char name[MAX_NAME_LEN];
  char type[MAX_TYPE_LEN];
  int quant;
} Item;

bool rmItem(Item backpack[], int* size, char* itemName);
void cleanInputBuffer();
void printActionMenu(int* option, int size);
void printInsertItemMenu(Item* temp);
void printList(Item backpack[], int size);
void printRemoveItemMenu(char* itemName);
void push(Item backpack[], int* size, Item newItem);

int main() {
  // Criamos o array
  Item backpack[MAX_BACKPACK_CAP];
  int itemCount = 0;
  
  Item temp; // Usado para capturar dados do menu
  int option;
  char nameToRemove[MAX_NAME_LEN];

  do {
    printActionMenu(&option, itemCount); 
    
    switch(option) {
      case 1: 
        if (itemCount == MAX_BACKPACK_CAP) {
          printf("\nMochila lotada!\n");
          break;
        }
        
        printInsertItemMenu(&temp);
        push(backpack, &itemCount, temp);
        printf("\nItem inserido com sucesso!\n");
        break;
      case 2:
        if (itemCount == 0) {
          printf("\nMochila vazia!\n");
          break;
        }
        
        printRemoveItemMenu(nameToRemove);
        if (rmItem(backpack, &itemCount, nameToRemove)) {
          printf("\nItem removido com sucesso!\n");
          break;
        }

        printf("\nItem nao encontrado!\n");
        break;
      case 3:
        printList(backpack, itemCount);
        break;
      case 0:
        printf("\nSaindo...\n");
        break;
      default:
        if (option < 0 || option > 3) {
          printf("\nPor favor, escolha uma opcao valida!\n");
        }
    }
    if (option != 0) system("pause");

  } while (option != 0);

  return 0;
}

// Adiciona ao final do array
void push(Item backpack[], int* size, Item newItem) {
  if (*size >= MAX_BACKPACK_CAP) return;

  backpack[*size] = newItem;
  (*size)++;
}

// Remove e "puxa" os itens da frente para não deixar buracos
bool rmItem(Item backpack[], int* size, char* itemName) {
  for (int i = 0; i < *size; i++) {
    if (strcmp(backpack[i].name, itemName) == 0) {
      
      // Move todos os itens a direita uma posição para a esquerda
      for (int j = i; j < (*size) - 1; j++) {
        backpack[j] = backpack[j + 1];
      }
      
      (*size)--;
      return true;
    }
  }
  return false;
}

void printList(Item backpack[], int size) {
  printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", size, MAX_BACKPACK_CAP);
  
  if (size == 0) {
    printf("Mochila vazia.\n");
    return;
  }

  printf("----------------------------------------------------------\n");
  printf("%-29s | %-19s | %s\n", "NOME", "TIPO", "QUANTIDADE");
  printf("----------------------------------------------------------\n");
  
  for (int i = 0; i < size; i++) {
    printf("%-29s | %-19s | %d\n", backpack[i].name, backpack[i].type, backpack[i].quant);
  }
}

void printInsertItemMenu(Item* temp) {
  printf("\n--- Adicionar Novo Item ---\n");
  printf("Nome: ");
  fgets(temp->name, MAX_NAME_LEN, stdin);
  temp->name[strcspn(temp->name, "\n")] = 0;

  printf("Tipo: ");
  fgets(temp->type, MAX_TYPE_LEN, stdin);
  temp->type[strcspn(temp->type, "\n")] = 0;
  
  printf("Quantidade: ");
  scanf("%d", &temp->quant);
  cleanInputBuffer();
}

void printActionMenu(int* option, int size) {
  printf("\n==================================\n");
  printf("      MOCHILA DE SOBREVIVENCIA  \n");
  printf("==================================\n");
  printf("Capacidade: %d/%d\n\n", size, MAX_BACKPACK_CAP);
  printf("1 - Adicionar Item\n2 - Remover Item\n3 - Listar Itens\n0 - Sair\n");
  printf("Escolha uma opcao: ");
  scanf("%d", option);
  cleanInputBuffer();
}

void printRemoveItemMenu(char* itemName) {
  printf("\nNome do Item para remover: ");
  fgets(itemName, MAX_NAME_LEN, stdin);
  itemName[strcspn(itemName, "\n")] = 0;
}

void cleanInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}