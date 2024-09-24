musl-gcc -static -s rsa.c ezrsa.c -o ezrsa
musl-gcc -static -DDECODE_TEST rsa.c ezrsa.c -o ezrsa_dectest