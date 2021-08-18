#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
