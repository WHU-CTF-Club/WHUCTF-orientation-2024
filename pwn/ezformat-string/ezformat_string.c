#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<unistd.h>
long long int magic=0;
void init()
{
    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 2, 0LL);
    setvbuf(stderr, 0LL, 2, 0LL);
}

int main(int argc, char** argv)
{   
    char buf[0x200];
    init();
    printf("Do you konw format-string?\n");
    printf("Just try to getshell\n");
    memset(buf,0,0x200);
    read(0,buf,0x200);
    printf(buf);
    if(magic==0x32107654ba98fedc){
        system("/bin/sh\x00");
    }
    else{
        printf("You don't understand format-string\n");
    }
    
    return 0;
}