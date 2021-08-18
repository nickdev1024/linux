#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "data.h"

/**
 * To demonstrate how to read from source file and then write to the destination file
 *
 * @param src  : the char pointer to the source file
 * @param dest : the char pointer to the destination file
 *
 */
void read_src_write_dest(char *src, char *dest) {
  int src_fd, dest_fd;

  if ( (src_fd = open(src, O_RDONLY)) < 0 ) {
    char *err_msg = "open src file\n";
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    exit(EXIT_FAILURE);
  }

  if ( (dest_fd = open(dest, O_CREAT | O_WRONLY, 0600)) < 0 ) {
    // remember to close the src file
    close(src_fd);

    char *err_msg = "open dest file\n";
    write(STDERR_FILENO, err_msg, strlen(err_msg));
    exit(EXIT_FAILURE);
  }

  // prepare a buffer for file reading and writing
  char buf[BUF_SIZE];
  int bytes_read;

  // question: do I need to initialize the buf with null characters
  // No, for file reading, the read index starts from the very beginning of the file
  // read system call then read up to the (buf size) characters then put all characters into the buf,
  // which overwrites any weird characters in the buf, bytes_read keeps track of the number characters
  // read from each system call (read), and then for file writing, only the number bytes_read characters
  // will be written into the destination file, any characters after that will be disregarded

  while ( (bytes_read = read(src_fd, buf, sizeof buf)) ) {
    write(dest_fd, buf, bytes_read);
  }

  char *success_msg = "copy successfully!\n";
  write(STDOUT_FILENO, success_msg, strlen(success_msg));

  close(src_fd);
  close(dest_fd);
}
