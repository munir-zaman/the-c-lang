/*
The C Programming Language
Chapter 1 : Exercise 1-23
  Write a program to remove all comments from a C program. Don't forget to handle quoted strings 
  and character constants properly. C comments don't nest.
*/

#include<stdio.h>

#define TRUE  1
#define FALSE 0

#define NOT_CMNT    0
#define LINE_CMNT   1
#define BLOCK_CMNT  2

#define CMNT_BEGIN  "/*"
#define CMNT_END    "*/"
#define CMNT        "//"
#define STR         '\"'

#define MAXLINE 256
char buffer[MAXLINE]; // global buffer for storing lines
int pos = 0; // position inside buffer array

void clear_buffer() {
  for (int i=0; i<MAXLINE; ++i) buffer[i] = 0;
}

int getline() {
  pos = 0;
  int limit = MAXLINE;
  int c, i;
  i = 0;
  while ((c = getchar()) != EOF && (c != '\n') && i<limit-1) {
    buffer[i] = c;
    ++i;
  }

  if (c == '\n') { buffer[i] = '\n'; ++i; }
  buffer[i] = '\0';
  return i;
}

char next() {
  ++pos;
  return buffer[pos];
}

char peek(int offset) {
  return buffer[pos+offset];
}

// matches at current position
int match(char *target) {
  int i = 0;
  while (target[i] != '\0') {
    if (target[i] != buffer[pos+i]) return FALSE;
    ++i;
  }
  return TRUE;
}

int strsize(char *s) {
  int i;
  for (i=0; (s[i]!='\0'); ++i);
  return i;
}

void copy(char *from, char *to) {
  for (int i = 0; ((to[i] = from[i]) != '\0'); ++i);
}

int equal(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2) return FALSE;
    s1++;
    s2++;
  }
  return (*s1 == '\0' && *s2 == '\0') ? TRUE : FALSE;
}

int main() {

  int in_comment = FALSE;
  int comment_type = NOT_CMNT;
  int in_string = FALSE;

  clear_buffer();

  while (getline()) {
    while (buffer[pos]!='\0') {
      // line comments
      if (!in_string && !in_comment && match(CMNT)) {
        //ignore current line if '//' is at the beginning of the line :D 
        if (pos == 0) break;
        in_comment = TRUE;
        comment_type = LINE_CMNT;
        
      }
      if (in_comment && !in_string && comment_type==LINE_CMNT && match("\n")) {
        in_comment = FALSE;
        comment_type = NOT_CMNT;
      }
      
      // block comments
      if (!in_string && !in_comment && match(CMNT_BEGIN)) {
        in_comment = TRUE;
        comment_type = BLOCK_CMNT;
      }
      if (in_comment && !in_string && comment_type==BLOCK_CMNT && match(CMNT_END)) {
        in_comment = FALSE;
        comment_type = NOT_CMNT;
        // move two steps forward
        next();
        next();
      }

      // handle strings
      if (!in_comment && !in_string && (match("\"") || match("\'"))) {
        in_string = !in_string; // flip current state
      }

      if (!in_string && in_comment);
      else {
        putchar(buffer[pos]);
      }
      next();
    }
  }

}
