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
// Latest Changes: 23.12.2018 (by Stefan Martin Wietreich)
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
//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
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

//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
void append(struct _Node_** head_ref, char new_color, int new_value, char new_text)
{
  /* 1. allocate node */
  struct _Node_* new_node = (struct _Node_*)malloc(sizeof(struct _Node_));
  struct _Node_* last = *head_ref; /* used in step 5*/
  /* 2. put in the data  */
  new_node->color_ = new_color;
  new_node->value_ = new_value;
  new_node->text_ = new_text;
  /* 3. This new node is going to be the last node, so
        make next of it as NULL*/
  new_node->next_ = NULL;
  /* 4. If the Linked List is empty, then make the new
        node as head */
  if (*head_ref == NULL)
  {
    new_node->previous_ = NULL;
    *head_ref = new_node;
    return;
  }
  /* 5. Else traverse till the last node */
  while (last->next_ != NULL)
  {
    last = last->next_;
  }
  /* 6. Change the next of last node */
  last->next_ = new_node;
  /* 7. Make last node as previous of new node */
  new_node->previous_ = last;
}

// This function prints contents of linked list starting from the given node
//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
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

//-----------------------------------------------------------------------------
///
/// Deletes a given node from the list
///
/// @param struct _Node_** head_ref Head of the list
/// @param struct _Node_* del Node to delete
//
void deleteNode(struct _Node_** head_ref, struct _Node_* del)
{
  /* base case */
  if (*head_ref == NULL || del == NULL)
    return;

  /* If node to be deleted is head node */
  if (*head_ref == del)
    *head_ref = del->next_;

  /* Change next only if node to be deleted is NOT the last node */
  if (del->next_ != NULL)
    del->next_->previous_ = del->previous_;

  /* Change prev only if node to be deleted is NOT the first node */
  if (del->previous_ != NULL)
    del->previous_->next_ = del->next_;

  /* Finally, free the memory occupied by del*/
  free(del);
}
// end

//-----------------------------------------------------------------------------
///
/// Checks if a node with the given values exists
///
/// @param struct _Node_* node head of the list
/// @param char new_color Color of the new card
/// @param int new_value Value of the new card
/// @return true if the node exists, false if not
//
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
/// @param char *config_file Name of the config file
/// @param struct _Node_** head Head of the list to insert data
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
          append(head, color, value, *value_char);
        }
        else
        {
          printf("Input invalid");
        }

      }
      token = strtok(NULL, delimiters);
    }
  }
}

//-----------------------------------------------------------------------------
///
/// moves nodes
///
/// @param struct _Node_** from node to move
/// @param struct _Node_** to destination list
//
void move(struct _Node_** from, struct _Node_** to)
{
  struct _Node_* last =  *from;
  while(last->next_ != NULL)
  {
    last = last->next_;
  }
  //append(to, (*from)->color_, (*from)->value_, (*from)->text_);
  //deleteNode(from, *from);

  append(to, last->color_, last->value_, last->text_);
  deleteNode(from, last);
}

//-----------------------------------------------------------------------------
///
/// Starts the game
///
/// @param struct _Node_* stack[] array of the card stacks
//
void distributeCards(struct _Node_* stack[])
{
  move(&stack[0], &stack[1]);
  move(&stack[0], &stack[2]);
  move(&stack[0], &stack[3]);
  move(&stack[0], &stack[4]);
  move(&stack[0], &stack[2]);
  move(&stack[0], &stack[3]);
  move(&stack[0], &stack[4]);
  move(&stack[0], &stack[3]);
  move(&stack[0], &stack[4]);
  move(&stack[0], &stack[4]);

  move(&stack[4], &stack[6]);
}

//-----------------------------------------------------------------------------
///
/// Prints spaces to the console
///
/// @param amount Number of spaces to print
//
void printSpace(int amount)
{
  int count = 0;
  for(count = 0; count < amount; count++)
  {
    printf(" ");
  }
}

void printNode(struct _Node_* node)
{
  if(node == NULL)
  {
    printSpace(4);
  }
  else
  {
    if(node->text_ == ' ')
    {
      printf("%c%d", node->color_, node->value_);
      if(node->value_ == 10)
      {
        printSpace(1);
      }
      else
      {
        printSpace(2);
      }
    }
    else
    {
      printf("%c%c", node->color_, node->text_);
      printSpace(2);
    }
  }


}

//-----------------------------------------------------------------------------
///
/// Prints the game board
///
/// @param struct _Node_* node[] array of linked list nodes
//
void printBoard(struct _Node_* node[])
{
  int column = 0;
  int row = 0;
  printf("0   | 1   | 2   | 3   | 4   | DEP | DEP\n"
         "---------------------------------------\n");

  for(row = 0; row < 16; row++)
  {
    for(column = 0; column < 7; column++)
    {
      if(column > 0)
      {
        printSpace(1);
      }
      printNode(node[column]);
      if(node[column] != NULL)
      {
        node[column] = node[column]->next_;
      }

      if(column < 6)
      {
        printf("|");
      }
    }
    printf("\n");
  }
}

//-----------------------------------------------------------------------------
///
/// scans user commands
///
/// @param struct _Node_* node[] array of linked list nodes
//
void userInput(struct _Node_* stack[])
{
  printf("esp> ");

}

//-----------------------------------------------------------------------------
///
/// Calls functions and initializes lists
///
/// @return always 0
//
int main(int argc, char *argv[])
{
  int count = 0;
  if(argc != 2)
  {
    printf("enter config file\n");
    //exit(1);
  }
  struct _Node_* stack[7];
  for(count = 0; count < 7; count++)
  {
    stack[count] = NULL;
  }
  //readConfig(argv[1]);
  readConfig("config.txt", &stack[0]);
  distributeCards(stack);

  //printList(stack[0]);
  //printList(stack[1]);

  printBoard(stack);
  userInput(stack);

  //printf("esp> ");
  for(count = 0; count < 7; count++)
  {
    freeList(&stack[count]);
  }

  return 0;
}