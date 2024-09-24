#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_string(const char *input, char *output) {
  int i, j = 0;
  for (i = 0; i < strlen(input);) {
    if (input[i] == '\xE9' && input[i + 1] == '\xA2' &&
        input[i + 2] == '\x98') {
      output[j++] = '0';
      i += 3;
    } else if (input[i] == '\xE5' && input[i + 1] == '\x91' &&
               input[i + 2] == '\xA2') {
      output[j++] = '1';
      i += 3;
    } else {
      if ((input[i] & 0xE0) == 0xC0) {
        i += 2;
      } else if ((input[i] & 0xF0) == 0xE0) {
        i += 3;
      } else if ((input[i] & 0xF8) == 0xF0) {
        i += 4;
      } else {
        i += 1;
      }
    }
  }
  output[j] = '\0';
}

void convert_binary_string_to_bytes(const char *input, unsigned char *output) {
  int index = 0;
  unsigned char byte = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    byte <<= 1;
    if (input[i] == '1') {
      byte |= 1;
    }
    index++;
    if (index == 8) {
      *output++ = byte;
      index = 0;
      byte = 0;
    }
  }
  if (index != 0) {
    byte <<= (8 - index);
    *output = byte;
  }
}

void init() {
  setbuf(stdin, 0);
  setbuf(stdout, 0);
  setbuf(stderr, 0);
}
void translate(const char *input) {
  unsigned char dest[0x100];
  char tmp[0x8000];
  convert_string(input, tmp);
  convert_binary_string_to_bytes(tmp, dest);
  printf("正在处理中，请稍候...\n");
}
void backd00r() { system("/bin/sh"); }
int main() {
  init();
  char src[0x8000];
  printf(
      "JuicyMio天天为新生赛出题冥思苦想。\nSecsome一见到他就问：\"题呢题呢题呢"
      "题呢？\"\n受不了的JuicyMio决定只要你一直像Secsome一样发问，就直接给你一"
      "个shell\n");
  printf("你可以开始发问了：");
  fgets(src, 0x8000, stdin);
  translate(src);
  return 0;
}
