
#include<sys/wait.h>
#include<stdlib.h>
#include<signal.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#include<sys/types.h>


#define MAX_TOKEN_SIZE 64
#define MAX_NUM_TOKENS 64
#define MAX_INPUT_SIZE 1024


bool bgexist=false;
bool fgexist=false;
int foregroundpid;
void exit_handler() {
  if(fgexist==true) {
    // printf("killing fg process: %d\n", foregroundpid);
    kill(foregroundpid, SIGINT);
    fgexist=false;
  }
}

char **tokenize(char *line)
{
  char **tokens = (char **)malloc(MAX_NUM_TOKENS * sizeof(char *));
  char *token = (char *)malloc(MAX_TOKEN_SIZE * sizeof(char));
  int i, tokenIndex = 0, tokenNo = 0;

  for(i =0; i < strlen(line); i++){

    char readChar = line[i];

    if (readChar == ' ' || readChar == '\n' || readChar == '\t'){
      token[tokenIndex] = '\0';
      if (tokenIndex != 0){
  tokens[tokenNo] = (char*)malloc(MAX_TOKEN_SIZE*sizeof(char));
  strcpy(tokens[tokenNo++], token);
  tokenIndex = 0;
      }
    } else {
      token[tokenIndex++] = readChar;
    }
  }

  free(token);
  tokens[tokenNo] = NULL ;
  return tokens;
}

int main(int argc, char * argv[]) {

  // create a process-ids list here max size is 64
  int bgpids[64];
  for(int i=0;i<64;i++) {
    bgpids[i]=-1;
  }
  char line[MAX_INPUT_SIZE];
  signal(SIGINT,exit_handler);
  char ** tokens;
  int i,status;

  while (1){

    // loop over all the children list to see which ones have exited and reap them
    for(int i=0;i<64;i++) {
      if(bgpids[i]!=-1) {
      int waitpidreturn=waitpid(bgpids[i],&status,WNOHANG);
      if(waitpidreturn>0) { // learn about these two (79 & 80)// checks child process without suspending the caller process
        // child definately dead and we are now reaping it
        waitpid(bgpids[i],&status,0);
        bgpids[i]=-1;
        printf("Shell: Background process finished \n");
      }
      }
    }

    /* BEGIN: TAKING INPUT */
    bzero(line, sizeof(line));
    printf("$");
    scanf("%[^\n]", line);
    getchar();

    line[strlen(line)]='\n'; //terminate with new line
    tokens=tokenize(line);

       //do whatever you want with the commands, here we just print them


    // #################################################
//Mycode starts from here
    if(tokens[0]==NULL)
    {
      continue;
    }

    i=0;
    bool flag=false;
    while(tokens[i]!=NULL)
    {
      if(tokens[i][0]!='\0'&&tokens[i][0]=='&'&&tokens[i][1]=='\0')
      {
      tokens[i]=NULL;
        flag=true;
        break;
      }
      i++;
    }



    if(strcmp(tokens[0],"cd")==0)
    {
      int chdirreturn;
      if(tokens[1]==NULL || tokens[2]!=NULL)
      {
      printf("Shell: Incorrect command \n");
      }
      else
        {
          chdirreturn=chdir(tokens[1]);
        }
      if(chdirreturn==-1)
      {
      printf("Shell: The directory entered is not a valid one \n");
      }
    }
    else if(strcmp(tokens[0],"exit")==0)
    {
      for(int i=0;i<64;i++)
      {
        if(bgpids[i]!=-1)
        {
        int killreturn = kill(bgpids[i],SIGKILL);
        }
      }
      break;
    }
    else
    {

      // background process
      if(flag)
      {
        int processid=fork();
        if(processid==0)
        {
          // this is child
          setpgid(processid,processid);
          int ret=execvp(tokens[0],tokens);
          if(ret==-1){
            printf("Shell: command not found: %s\n",tokens[0]);
          }
          break;
        }
        else
        {
          for(int i=0;i<64;i++)
          {
            if(bgpids[i]==-1)
            {
              bgpids[i]=processid;
              break;
            }
          }
        }
      }


      //foreground process
      else
      {

      int processid=fork();
        if(processid==0)
        {
        int ret=execvp(tokens[0],tokens);
        if(ret==-1){
          printf("Shell: command not found: %s\n",tokens[0]);
        }
        break;
        }
        else
        {
          foregroundpid=processid;
          fgexist=true;
          waitpid(processid,&status,0);
          fgexist=false;
        }
      }



    }


    // #################################################

    // Freeing the allocated memory
    for (i = 0; tokens[i] != NULL; i++) {
      free(tokens[i]);
    }
    free(tokens);
  }
  return 0;
}
