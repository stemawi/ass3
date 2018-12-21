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
struct Node
{
  char color_;
  int value_;
  char* text_;
  struct Node* next_;
  struct Node* previous_;
};

/* Given a reference (pointer to pointer) to the head of a list
   and an int, inserts a new node on the front of the list. */
void push(struct Node** head_ref, char new_color, int new_value, char* new_text)
{
  /* 1. allocate node */
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
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
void printList(struct Node* node)
{
  struct Node* last;
  printf("\nTraversal in forward direction \n");
  while (node != NULL)
  {
    printf("%c", node->color_);
    printf("%d", node->value_);
    printf("%s\n", node->text_);
    last = node;
    node = node->next_;
  }

  printf("\nTraversal in reverse direction \n");
  while (last != NULL)
  {
    printf("%c", last->color_);
    printf("%d", last->value_);
    printf("%s\n", last->text_);
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
void readConfig(char *config_file, struct Node** head)
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
      //printf("%c",current_char);
      //if(current_char == ' ' || (current_char == '\n' && buffer[length-1] ==
      //'\n'))
      //{
        //current_char = (char)fgetc(config);
        //continue;
      //}
      buffer[length] = current_char;
      buffer[length+1] = '\0';
      current_char = (char)fgetc(config);
      length++;
    }
    //printf("%s\n\n", buffer);

    fclose(config);

    char* delimiters = " \n";
    char* token = strtok(buffer, delimiters);
    int count = 0;
    char color = ' ';
    int value = 0;
    char* value_str;
    char* text;
    for(count = 0; token != NULL; count++)
    {
      value = 0;
      value_str = NULL;
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
        //printf("%s\n",token);
        text = token;
        value = (int)strtol(token, &value_str, 10);
        printf("v_str: %s\n",value_str);

        switch(*value_str)
        {
          case 'A': value = 1; break;
          case 'J': value = 11; break;
          case 'Q': value = 12; break;
          case 'K': value = 13; break;
          default: break;
        }

        push(head, color, value, " ");
      }
      //printf("%s\n", token);

      token = strtok(NULL, delimiters);
    }
  }

}

void test(struct Node** head)
{
  push(head, 'Z', 1, "BA");push(head, 'Z', 1, "BA");
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

  struct Node* head = NULL;

  readConfig("config.txt", &head);

  //push(&head, 'R', 1, "RA");push(&head, 'B', 1, "BA");
  //test(&head);
  //push(&head, 'B', 4);
  //push(&head, 'R', 3);
  //push(&head, 'B', 1);
  //printf("Created DLL is: ");

  printList(head);


  //printf("esp> ");
  //readConfig(argv[1]);

  return 0;
}