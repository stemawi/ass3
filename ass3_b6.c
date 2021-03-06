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
// end

//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
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
    int write_count = 0;
    int stack = 0;
    bool card_exists = false;
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

        switch(write_count+1)
        {
          case 1: stack = 1; break;
          case 2: stack = 2; break;
          case 3: stack = 3; break;
          case 4: stack = 4; break;
          case 5: stack = 2; break;
          case 6: stack = 3; break;
          case 7: stack = 4; break;
          case 8: stack = 3; break;
          case 9: stack = 4; break;
          case 10: stack = 4; break;
          default: stack = 0; break;
        }

        int exists_count = 0;
        for(exists_count = 0; exists_count < 7; exists_count++)
        {
          if(nodeExists(*(head+exists_count), color, value))
          {
            card_exists = true;
          }
        }

        if(!(card_exists))
        {
          push(head+stack, color, value, *value_char);
          write_count++;
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

//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
void move(struct _Node_** from, struct _Node_** to)
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

//-----------------------------------------------------------------------------
///
/// Reads the config file
///
/// @return always 0
//
void distributeCards()
{

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



  //printNode(node);
  //printf("|");
  //printSpace(1);
  //printNode(node->next_->next_->next_);
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
    printf("enter config file");
    //exit(1);
  }
  struct _Node_* stack[7];
  for(count = 0; count < 7; count++)
  {
    stack[count] = NULL;
  }

  //struct _Node_* head = NULL;

  readConfig("config.txt", &stack[0]);
  //push(&stack[1], 'Z', 1, 'A');
  move(&stack[0], &stack[1]);

  //push(&head, 'R', 1, "RA");push(&head, 'B', 1, "BA");
  //test(&head);
  //push(&head, 'B', 4);
  //push(&head, 'R', 3);
  //push(&head, 'B', 1);
  //printf("Created DLL is: ");

  printList(stack[0]);
  printList(stack[1]);

  printBoard(stack);

  printf("esp> ");
  //readConfig(argv[1]);
  for(count = 0; count < 7; count++)
  {
    freeList(&stack[count]);
  }

  return 0;
}