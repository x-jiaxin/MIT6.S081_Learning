//
// Created by jiaxin on 2023/2/1 16:47.
//
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"
int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(1, "Usage: sleep seconds\n");
    exit(0);
  }
  sleep(atoi(argv[1]));
  exit(0);
}