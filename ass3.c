//-----------------------------------------------------------------------------
// ass3.c
//
// Solitaire
//
// Group: 20772 study assistant Florian Hager
//
// Authors: Stefan Martin Wietreich 11811040
//                 Alexandra Nadler 11807596
//
// Latest Changes: 19.12.2018 (by Stefan Martin Wietreich)
//-----------------------------------------------------------------------------
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// structure of a Node
typedef struct _Node_
{
  char color_;
  int value_;
  struct _Node_ *next_;
  struct _Node_ *previous_;
} Node;

// from: https://www.geeksforgeeks.org/doubly-linked-list/
// begin
/* Given a reference (pointer to pointer) to the head of a list 
   and an int, inserts a new node on the front of the list. */
void push(Node** head_ref, char new_color, int new_value)
{
  /* 1. allocate node */
  Node* new_node = (Node*)malloc(sizeof(Node));
  /* 2. put in the data  */
  new_node->color_ = new_color;
  new_node->value_ = new_value;
  /* 3. Make next of new node as head and previous as NULL */
  new_node->next_ = (*head_ref);
  new_node->previous_ = NULL;
  /* 4. change prev of head node to new node */
  if ((*head_ref) != NULL)
    (*head_ref)->previous_ = new_node;
  /* 5. move the head to point to the new node */
  (*head_ref) = new_node;
}

// This function prints contents of linked list starting from the given node
void printList(Node* node)
{
  Node* last;
  printf("\nTraversal in forward direction \n");
  while (node != NULL)
  {
    printf(" %c", node->color_);
    printf(" %d\n", node->value_);
    last = node;
    node = node->next_;
  }

  printf("\nTraversal in reverse direction \n");
  while (last != NULL) {
    printf(" %d ", node->color_);
    printf(" %d ", node->value_);
    last = last->previous_;
  }
}
// end

//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
void readConfig(char *config_file)
{
  FILE *config;
  char buffer[555];
  char current_char;
  int length = 0;
  config = fopen(config_file, "r");
  if(config == NULL)
  {
    printf("file not found");
  }
  else
  {
    printf("file found\n");

    current_char = (char)fgetc(config);
    while(current_char != EOF)
    {
      //printf("%c",current_char);
      if(current_char == ' ' || (current_char == '\n' && buffer[length-1] ==
      '\n'))
      {
        current_char = (char)fgetc(config);
        continue;
      }
      buffer[length] = current_char;
      buffer[length+1] = '\0';
      current_char = (char)fgetc(config);
      length++;
    }
    printf("%s", buffer);
  }
  fclose(config);
}

//-----------------------------------------------------------------------------
///
/// Call functions and initialize list
///
/// @return always 0
//
int main(int argc, char *argv[])
{
  if(argc != 2)
  {
    printf("enter config file");
    //exit(1);
  }

  Node *head[7];
  int count;
  for(count = 0; count < 7; count++)
  {
    head[count] = malloc(sizeof(Node));
    if(head[count] == NULL)
    {
      printf("[ERR] Out of memory.\\n");
    }
    head[count]->next_ = NULL;
    head[count]->previous_ = NULL;
  }

  //printf("esp> ");
  //readConfig(argv[1]);

  push(&head[0], 'R', 2);
  push(&head[0], 'B', 5);

  printList(head[0]);

  for(count = 0; count < 7; count++)
  {
    free(head[count]);
  }
  return 0;
}