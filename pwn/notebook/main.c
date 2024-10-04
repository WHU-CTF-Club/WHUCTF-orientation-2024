#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

char *notes[0x10];
size_t len[0x10];

void init() {
  setbuf(stdin, 0);
  setbuf(stdout, 0);
  setbuf(stderr, 0);
}

int add_note(int idx) {

  unsigned long long addr;
  printf("note addr: ");
  scanf("%llu", &addr);
  size_t length;
  printf("note length: ");
  scanf("%lu", &length);
  unsigned int prot;
  printf("note protect mode: ");
  scanf("%u", &prot);
  if (prot > 7) {
    printf("prot error!\n");
    return 0;
  }
  notes[idx] = mmap((void *)addr, length, prot, MAP_SHARED | MAP_ANON, -1, 0);
  len[idx] = length;
  if (!notes[idx]) {
    puts("mmap error!");
    return 1;
  }
  printf("note added successfully\n");
  printf("input the note: ");
  read(0, notes[idx], len[idx]);
  return 0;
}

int delete_note(int idx) {
  if (notes[idx] != NULL) {
    munmap(notes[idx], len[idx]);
    notes[idx] = 0;
    len[idx] = 0;
  } else {
    printf("note don't exist\n");
    return 1;
  }
  return 0;
}

int edit_note(int idx) {
  if (notes[idx] != NULL) {
    read(0, notes[idx], len[idx]);
  } else {
    printf("note don't exist\n");
    return 1;
  }
  return 0;
}

int view_note(int idx) {
  if (notes[idx] != NULL) {
    write(1, notes[idx], len[idx]);
  } else {
    printf("note don't exist\n");
    return 1;
  }
  return 0;
}

int read_num() {
  char s[8];
  gets(s);
  return atoi(s);
}
void print_menu() {
  puts("1.add note");
  puts("2.delete note");
  puts("3.view note");
  puts("4.edit note");
  puts("5.exit");
}
int main() {
  init();
  while (1) {
    print_menu();
    int option = read_num();
    int idx;
    if (option == 1) {
      printf("input note id: ");
      scanf("%d", &idx);
      int idx = read_num();
      if (idx < 0 || idx >= 0x10) {
        puts("id out of bound");
        continue;
      }
      add_note(idx);
    } else if (option == 2) {
      printf("input note id: ");
      scanf("%d", &idx);
      int idx = read_num();
      if (idx < 0 || idx >= 0x10) {
        puts("id out of bound");
        continue;
      }
      delete_note(idx);
    } else if (option == 3) {
      printf("input note id: ");
      scanf("%d", &idx);
      int idx = read_num();
      if (idx < 0 || idx >= 0x10) {
        puts("id out of bound");
        continue;
      }
      view_note(idx);
    } else if (option == 4) {
      printf("input note id: ");
      scanf("%d", &idx);
      int idx = read_num();
      if (idx < 0 || idx >= 0x10) {
        puts("id out of bound");
        continue;
      }
      edit_note(idx);
    } else if (option == 5) {
      exit(0);
    } else
      puts("invalid option");
  }
}
