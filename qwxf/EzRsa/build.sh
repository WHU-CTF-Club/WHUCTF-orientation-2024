gcc -s rsa.c ezrsa.c -o ezrsa
gcc -DDECODE_TEST rsa.c ezrsa.c -o ezrsa_dectest