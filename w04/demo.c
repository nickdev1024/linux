#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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

/**
 * create a alphabetical file including letter 'a' to 'z' with 3 newline characters
 *
 * @param file: char pointer to specify the file name
 *
 */
void create_file(char *file) {
  int fd;
  if ( (fd = open(file, O_CREAT | O_WRONLY, 0600)) < 0 ) {
    char *err_msg = "open file";
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    exit(EXIT_FAILURE);
  }

  char chr;
  char newline = '\n';
  int idx = 0, len = 7; // for every 7 characters, append a newline '\n'
  // abcdefg \n hijklmn \n opqrstu \n vwxyz

  for (chr = 'a'; chr <= 'z'; ++chr) {
    write(fd, &chr, sizeof chr);
    if (++idx % len == 0) {
      write(fd, &newline, sizeof newline);
    }
  }
  // don't forget to close the fd, free the resources
  close(fd);
}

/**
 * To demonstrate how to use lseek to locate any position for file reading
 *
 * @param file: char pointer to specify the file name
 *
 */
void lseek_read(char *file) {
  int fd;
  if ( (fd = open(file, O_RDONLY)) < 0 ) {
    char *err_msg = "open file";
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    exit(EXIT_FAILURE);
  }

  int cur;
  char chr;

  // 1. use lseek to check if newline exists at the end
  // SEEK_END, at the end of the file(fd)
  // 0: the difference (offset) between position located and reference point (end)
  cur = lseek(fd, 0, SEEK_END);
  printf("cur = %d\n", cur);

  cur = lseek(fd, -1, SEEK_CUR);
  int bytes_read;

  bytes_read = read(fd, &chr, sizeof chr);
  printf("bytes read is %d, chr = %d, chr = %c\n", bytes_read, chr, chr);

  // 1. use lseek to locate to 2nd character
  // SEEK_SET, at the beginning of the file(fd)
  // 1: the difference (offset) between position located and reference point (start)
  lseek(fd, 1, SEEK_SET);
  bytes_read = read(fd, &chr, sizeof chr);
  printf("bytes read is %d, chr = %d, chr = %c\n", bytes_read, chr, chr);

  // I want to read char 'i'
  // 1. I need to locate to the end of the char 'h' and before the char 'i'
  // offset is 'i' - ('b' + 1) + 1 (+1 because the existence of newline)
  char target = 'i';
  int offset = target - chr;
  lseek(fd, offset, SEEK_CUR);

  bytes_read = read(fd, &chr, sizeof chr);
  printf("bytes read is %d, chr = %d, chr = %c\n", bytes_read, chr, chr);

  // don't forget to close the fd, free the resources
  close(fd);
}
