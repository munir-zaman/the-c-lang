/*
The C Programming Language
Chapter 1 : Exercise 1-24
    Write a program to check a C program for rudimentary syntax errors like
    unmatched parentheses, brackets and braces. Don't forget about quotes, both
single and double, escape sequences, and comments. (This program is hard if you
do it in full generality.)
*/

// one char is enough
// stack based?!
#include <stdio.h>
#include <stdlib.h>

// indices for accessing stack
enum Punctuation {
  PARNES,
  BRACKETS,
  BRACES,
  SINGLE_QUOTE,
  DOUBLE_QUOTE,
  COMMENT
};

char *punct_names[] = {
  "parenthesis",
  "brackets",
  "braces",
  "single quote",
  "double quote",
  "comment"
};

#define PUNCTS 6

#define TRUE 1
#define FALSE 0

#define MAXLINE 256
char buffer[MAXLINE]; // global buffer for storing lines
int pos = 0;          // position inside buffer array

void clear_buffer() {
  for (int i = 0; i < MAXLINE; ++i)
    buffer[i] = 0;
}

int getline() {
  pos = 0;
  int limit = MAXLINE;
  int c, i;
  i = 0;
  while ((c = getchar()) != EOF && (c != '\n') && i < limit - 1) {
    buffer[i] = c;
    ++i;
  }

  if (c == '\n') {
    buffer[i] = '\n';
    ++i;
  }
  buffer[i] = '\0';
  return i;
}

char next() {
  ++pos;
  return buffer[pos];
}

char peek(int offset) { return buffer[pos + offset]; }

// matches at current position
int match(char *target) {
  int i = 0;
  while (target[i] != '\0') {
    if (target[i] != buffer[pos + i])
      return FALSE;
    ++i;
  }
  return TRUE;
}

int strsize(char *s) {
  int i;
  for (i = 0; (s[i] != '\0'); ++i)
    ;
  return i;
}

void copy(char *from, char *to) {
  for (int i = 0; ((to[i] = from[i]) != '\0'); ++i)
    ;
}

int equal(const char *s1, const char *s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2)
      return FALSE;
    s1++;
    s2++;
  }
  return (*s1 == '\0' && *s2 == '\0') ? TRUE : FALSE;
}

int check_stack(int stack[], int index) {
  // check if stack value is negative
  if (stack[index] < 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

void report_syntax_error(char *msg, int line, int pos) {
  printf("Syntax Error (%d,%d): %s\n", line, pos, msg);
}

int main(int argc, char *argv[]) {

  // stack
  int stack[] = {0, 0, 0, 0, 0, 0};

  // state variable
  int in_comment = 0;
  int in_string = 0;

  int line = 0;

  while (getline()) {
    line++;
    // read line by line
    while (buffer[pos] != '\0') {
      // loop till end of buffer/line

      // double quote strings
      // not in comment and not a escape sequence and c == '\"'
      if (!in_comment && buffer[pos - 1] != '\\' && buffer[pos] == '\"') {
        printf("STRING \n");
        if (in_string) {
          // end of string
          stack[DOUBLE_QUOTE]--;
          if (check_stack(stack, DOUBLE_QUOTE))
            report_syntax_error("Unmatched double quote", line, pos);
        } else {
          // start of string
          stack[DOUBLE_QUOTE]++;
        }
        in_string = !in_string;
      }

      // single quote strings
      // not in comment and not a escape sequence and c == '\''
      if (!in_comment && buffer[pos - 1] != '\\' && buffer[pos] == '\'') {
        if (in_string) {
          // end of string
          stack[SINGLE_QUOTE]--;
          if (check_stack(stack, SINGLE_QUOTE))
            report_syntax_error("Unmatched single quote", line, pos);
        } else {
          // start of string
          stack[SINGLE_QUOTE]++;
        }
        in_string = !in_string;
      }

      if (!in_string && match("//")) {
        // ignore line comments
        line++;
        break;
      }

      if (!in_string && match("/*")) {
        in_comment = TRUE;
        stack[COMMENT]++;
      }

      if (!in_string && match("*/")) {
        in_comment = FALSE;
        stack[COMMENT]--;
        if (check_stack(stack, COMMENT))
          report_syntax_error("Unmatched comment (*/)", line, pos);
      }

      // handle brackets
      if (!in_string && !in_comment && match("(")) {
        stack[PARNES]++;
      }
      if (!in_string && !in_comment && match(")")) {
        stack[PARNES]--;
        if (check_stack(stack, PARNES))
          report_syntax_error("Unmatched parenthesis", line, pos);
      }

      if (!in_string && !in_comment && match("{")) {
        stack[BRACES]++;
      }
      if (!in_string && !in_comment && match("}")) {
        stack[BRACES]--;
        if (check_stack(stack, BRACES))
          report_syntax_error("Unmatched braces", line, pos);
      }

      if (!in_string && !in_comment && match("[")) {
        stack[BRACKETS]++;
      }
      if (!in_string && !in_comment && match("]")) {
        stack[BRACKETS]--;
        if (check_stack(stack, BRACKETS))
          report_syntax_error("Unmatched brackets", line, pos);
      }

      next();
    }

    if (stack[DOUBLE_QUOTE]!=0) {
      printf("Syntax Error (%d, ): Unmatched %s\n", line, punct_names[DOUBLE_QUOTE]);
    }

    if (stack[SINGLE_QUOTE]!=0) {
      printf("Syntax Error (%d, ): Unmatched %s\n", line, punct_names[SINGLE_QUOTE]);
    }
  }

  for (int i=0; i<PUNCTS; i++) {
    if (stack[i]!=0) {
      printf("Syntax Error : Unmatched %s\n", punct_names[i]);
    }
  }

  return 0;
}
