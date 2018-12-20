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


// structure of a card
typedef struct _Card_
{
  char color_;
  int value_;
  struct _Card_ *next_;
  struct _Card_ *previous_;
} Card;

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
    exit(1);
  }

  Card *head = malloc(sizeof(Card));
  head->next_ = NULL;
  head->previous_ = NULL;

  printf("esp> ");
  readConfig(argv[1]);

  free(head);
  head = NULL;
  return 0;
}