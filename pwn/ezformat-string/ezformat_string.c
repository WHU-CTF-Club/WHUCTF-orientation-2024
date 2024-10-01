#include<stdio.h>
#include<unistd.h>
long long int magic=0;

int main()
{
    char buf[0x200];
    printf("Do you konw format-string?\n");
    printf("Just try to getshell\n");
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