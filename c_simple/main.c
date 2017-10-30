#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LEN 100

void print_help(){
    printf("Versao 0.1b\n");
    printf("Para mudar a prioridade do processo, chame o programa com os argumentos:\n");
    printf("min - prioridade minima do sistema\n");
    printf("nor - prioridade normal do sistema\n");
    printf("max - prioridade maxima do sistema\n\n");
    printf("ex: ./programa max\n");
    
}

int main(int argc, char **argv)
{
    
    if(argc > 2){
        print_help();
        return 0;
    }
    
    if(!strcmp(argv[1], "h")){
        print_help();
        return 0;
    }
    
    
    char line[LEN];
    FILE *cmd = popen("pidof docker", "r");
    
    fgets(line, LEN, cmd);
    pid_t pid = strtoul(line, NULL, 10);
    
    pclose(cmd);
    
    int priority = 0;
    
    if(!strcmp(argv[1], "max"))
        priority = -19;
    
    if(!strcmp(argv[1], "nor"))
        priority = 0;
    
    if(!strcmp(argv[1], "min"))
        priority = 20;
    
    system("renice %i -p %i", priority, pid);
    
    return 0;
}
