#include <stdio.h>
#include <stdlib.h>

#include "demo.h"

int main(int argc, char *argv[]) {

  buffer_demo();

  char *file = "alpha";
  create_file(file);
  lseek_read(file);

  char *dest = "./dest";
  read_src_write_dest(file, dest);

  return EXIT_SUCCESS;
}
