#include<stdio.h>
#include<stdlib.h>

char *commandlist[6]={"pwd","whoami","ls","uname","showKey","openthedoor"};
void handle_input(char *input)
{
  char *result; // rax
  result = strchr(input, '\n');
  if ( result )
    *result = 0;
  return result;
}

void vuln(char *input,char *buf)
{ 
  handle_input(input);
  char s[256];
  if ( !strcmp(input, "help") )
  {
    strcpy(buf, "Supported commands:  pwd, whoami,ls,uname, showKey, openthedoor \n");
    return ;
  }
  if ( !strcmp(input, "showKey"))
  {
    unsigned int v1=0;
    v1 = time(0LL);
    srand(v1);
    unsigned int v2=0;
    v2 = rand();
    sprintf(s, "%s %d %s", "Key: ", v2, "\n");
    strcpy(buf, s);
  }
  else if ( strchr(input, '&') || strchr(input,"||") || strchr(input, ';') )
  {
    strcpy(buf, "Not Support 1. \n");
  }
  else if ( strchr(input, '>') || strchr(input, '<') || strchr(input, '|') )
  {
    strcpy(buf, "Not Support 2. \n");
  }
  else if ( strchr(input, '$') || strchr(input, '`') )
  {
    strcpy(buf, "Not Support 3. \n");
  }
  else
  {
    char s1[256];
    memset(s1, 0, sizeof(s1));
    char * a1= strchr(input, ' ');
    if ( a1 )
    {
      strncpy(s1,input, a1 - input);
    }
    else
    {
      int n=strlen(input);
      strncpy(s1, input, n);
    }
    int n1 = strlen(s1);
    if ( n1 ){
      int cnt = 0;
      char * tmp = commandlist[0];
      while ( strncmp(s1, tmp, n1) ){
        if ( !commandlist[++cnt] ){
          strcpy(buf, "Not Support 4. \n");
          return ;
        }
        tmp = commandlist[cnt];
      }
      if ( !strncmp("openthedoor", s1, n1) ){
          char *s2= strstr(input, "-k");
          if ( s2 ){
            if ( strlen(s2) > 2 ){
              int v3 = time(0LL);
              srand(v3);
              int v4 = rand();
              char s3[32];
              sprintf(s3, "%d", v4);
              memset(s, 0, 256);
              v4 = strlen(input);
              strncpy(s, input + 15, v4 - 15);
              s[strlen(input) - 15] = 0;
              if ( !strcmp(s3, s) ){
                memset(input, 0, 8uLL);
                snprintf(input, 8uLL, "cat /flag\n");
              }
              else{
                strcpy(buf, "Fail to get shell!\n");
              }
            }
            else{
              strcpy(buf, "please use openthedoor -k <key>.\n");
            }
          }
          else{
            strcpy(buf, "please use openthedoor -k <key>. \n");
          }
        }
        else{
            FILE * stream;
            stream = popen(input, "re");
            if ( !stream ){
              perror("popen failed");
              exit(1);
            }
            while ( fgets(s, 256, stream) )
              strcat(buf, s);
            pclose(stream);
        }
    }
    else{
      strcpy(buf, "Please enter command. \n");
    }
   
  }
}

int main()
{
    char input[256];
    char buf[1024];
    printf("%s", "Welcome to the debug console! Use \"help\" to see supported commands. \n");
    printf("Welcome to my ezshell.You can get flag easily\n");
    while(1){
       memset(input,0,sizeof(input));
       printf("$");
       if(fgets(input,256,stdin)){
        memset(buf,0,sizeof(buf));
        vuln(input,buf);
        printf("%s",buf);
        }
        else{
            printf("error");
        }
    }
   
}