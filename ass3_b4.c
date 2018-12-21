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


// from: https://www.geeksforgeeks.org/doubly-linked-list/
// begin
// A linked list node
struct _Node_
{
  char color_;
  int value_;
  char text_;
  struct _Node_* next_;
  struct _Node_* previous_;
};

/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct _Node_** head_ref, char new_color, int new_value, char new_text)
{
  /* 1. allocate node */
  struct _Node_* new_node = (struct _Node_*)malloc(sizeof(struct _Node_));
  /* 2. put in the text_  */
  new_node->color_ = new_color;
  new_node->value_ = new_value;
  new_node->text_ = new_text;
  /* 3. Make next_ of new node as head and previous as NULL */
  new_node->next_ = (*head_ref);
  new_node->previous_ = NULL;
  /* 4. change previous_ of head node to new node */
  if ((*head_ref) != NULL)
  {
    (*head_ref)->previous_ = new_node;
  }
  /* 5. move the head to point to the new node */
  (*head_ref) = new_node;
}

// This function prints contents of linked list starting from the given node 
void printList(struct _Node_* node)
{
  struct _Node_* last;
  printf("\nTraversal in forward direction \n");
  while (node != NULL)
  {
    printf("%c", node->color_);
    printf("%d", node->value_);
    printf("%c\n", node->text_);
    last = node;
    node = node->next_;
  }

  printf("\nTraversal in reverse direction \n");
  while (last != NULL)
  {
    printf("%c", last->color_);
    printf("%d", last->value_);
    printf("%c\n", last->text_);
    last = last->previous_;
  }
}
// end

bool nodeExists(struct _Node_* node, char new_color, int new_value)
{
  while (node != NULL)
  {
    if(node->color_ == new_color && node->value_ == new_value)
    {
      return true;
    }
    node = node->next_;
  }
  return false;
}

void freeList(struct _Node_** head)
{
  struct _Node_* next_node = *head;
  while(next_node != NULL)
  {
    next_node = (*head)->next_;
    //printf("[DEBUG] data_: %d, free(%p)\n", (*head)->value_, (*head));
    free(*head);
    *head = next_node;
  }
}

//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
void readConfig(char *config_file, struct _Node_** head)
{
  FILE *config;
  char buffer[512];
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
      buffer[length] = current_char;
      buffer[length+1] = '\0';
      current_char = (char)fgetc(config);
      length++;
    }
    fclose(config);

    char* delimiters = " \n";
    char* token = strtok(buffer, delimiters);
    int count = 0;
    char color = ' ';
    int value = 0;
    char* value_char;
    for(count = 0; token != NULL; count++)
    {
      //value = 0;
      //value_char = NULL;
      if(count % 2 == 0)
      {
        if(strncmp(token, "BLACK", strlen(token)) == 0)
        {
          color = 'B';
        }
        else if(strncmp(token, "RED", strlen(token)) == 0)
        {
          color = 'R';
        }
        else
        {
          printf("Input invalid");
        }
      }
      else
      {
        value = (int)strtol(token, &value_char, 10);

        switch(*value_char)
        {
          case 'A': value = 1; break;
          case 'J': value = 11; break;
          case 'Q': value = 12; break;
          case 'K': value = 13; break;
          default: *value_char = ' '; break;
        }

        if(value < 1 || value > 13)
        {
          printf("Input invalid");
        }

        if(!(nodeExists(*head, color, value)))
        {
          push(head, color, value, *value_char);
        }
        else
        {
          printf("Input invalid");
        }

      }
      //printf("%s\n", token);

      token = strtok(NULL, delimiters);
    }
  }
}

void move(struct _Node_** from_head, struct _Node_** to_head)
{
  /* 3. Make next_ of new node as head and previous as NULL */
  //new_node->next_ = (*head_ref);
  //new_node->previous_ = NULL;
  /* 4. change previous_ of head node to new node */
  //if ((*head_ref) != NULL)
  //{
  //  (*head_ref)->previous_ = new_node;
  //}
  /* 5. move the head to point to the new node */
  //(*head_ref) = new_node;
}

void distributeCards()
{

}

void printBoard()
{

}

void test(struct _Node_** head)
{
  push(head, 'Z', 1, 'B');push(head, 'Z', 1, 'A');
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
  struct _Node_* stack[7];
  stack[0] = NULL;
  stack[1] = NULL;
  stack[2] = NULL;
  stack[3] = NULL;
  stack[4] = NULL;
  stack[5] = NULL;
  stack[6] = NULL;
  //struct _Node_* head = NULL;

  readConfig("config.txt", &stack[0]);

  //push(&head, 'R', 1, "RA");push(&head, 'B', 1, "BA");
  //test(&head);
  //push(&head, 'B', 4);
  //push(&head, 'R', 3);
  //push(&head, 'B', 1);
  //printf("Created DLL is: ");

  printList(stack[0]);


  //printf("esp> ");
  //readConfig(argv[1]);
  freeList(&stack[0]);
  return 0;
}