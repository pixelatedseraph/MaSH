#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/wait.h>
#include "../headers/loopsh.h"
#define INPUT_BUFF 1024 /* allocate 1kb for input stream */

void loop_sh(){
    printf("sam@mash ");
    fflush(stdout);
    char ibuff[INPUT_BUFF];
    if(!fgets(ibuff,sizeof(ibuff),stdin)){
        perror("Parsing String Error (PSE)\n");
        return ;
    }
    /* trim the new line  */
    ibuff[strcspn(ibuff,"\n")] = '\0';
    pid_t pid = fork();
    if(pid == 0){
        char* cmd[] = {ibuff,NULL};
        execvp(cmd[0],cmd);
        perror("Child Flop (CF)\n");
        exit(1);
    }
    else if(pid > 0){
        wait(NULL);
    }
    else {
        perror("Fork Flop (FF) \n");
    }
}