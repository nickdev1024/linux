#include <stdio.h>

#include "data.h"

/**
 * print the content of the buffer either in char format or in decimal format
 *
 * @param buf         : the pointer to the beginning of the buffer - memory address
 * @param len         : the size of the buffer - total number of spots
 * @param char_format : boolean value, true to print in character format, false in decimal format
 *
 */
void print_buf(char *buf, int len, bool char_format) {
  int i;
  printf(">> buffer size = %d\n", len);
  if (char_format) {
    for (i = 0; i < len; ++i) {
      printf("%c", *(buf + i));
    }
  } else {
    for (i = 0; i < len; ++i) {
      printf("%d", *(buf + i));
    }
  }
  printf("\ni = %d\n", i);
}

/**
 * To demonstrate the root cause why some students encounter weird characters when using char buffer[]
 *
 * 1. declare a buf with certain size but without initialisation;
 * 2. declare a buf with certain size, only initialise 1st character;
 * 2. declare a buf with certain size, only initialise 1st and 2nd character;
 */
void buffer_demo() {

  // declare a buf with size of 1024 bytes without initialisation
  char weird_buf[BUF_SIZE];

  // use sizeof operator to calculate the total size of the buf
  int len = sizeof weird_buf / sizeof (char);

  // print the content of the buf character by character
  print_buf(weird_buf, len, true);

  // declare a buf with size of 1024 bytes with initialisation
  // 1. index 0 (1st char) will be set to '!', 33 (decimal) => '!' (char)
  // 2. the rest of the characters will be automatically set to null character (hidden)
  char clean_buf[BUF_SIZE] = { 33 };

  // use sizeof operator to calculate the total size of the buf
  len = sizeof clean_buf / sizeof (char);

  // print the content of the buf character by character
  print_buf(clean_buf, len, true);

  printf("\n");

  // print the content of the buf character by character in decimal format
  print_buf(clean_buf, len, false);

  // declare a buf with size of 1024 bytes with initialisation
  // 1. index 0 (1st char) will be set to !, 34 (decimal) => '"' (char)
  // 1. index 1 (2nd char) will be set to !, 36 (decimal) => '$' (char)
  // 2. the rest of the characters will be automatically set to null character (hidden)
  char clean_buf1[BUF_SIZE] = { 34, 36 };

  // use sizeof operator to calculate the total size of the buf
  len = sizeof clean_buf1 / sizeof (char);

  // print the content of the buf character by character
  print_buf(clean_buf1, len, true);

  printf("\n");

  // print the content of the buf character by character in decimal format
  print_buf(clean_buf1, len, false);
}
