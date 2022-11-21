#include <stdio.h>
#include <sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<strings.h>
#include<limits.h>
#include<time.h>

int main(int argc , char* argv[]){
    char destination[100]; 
    int ptr = 0 ; 
    for(int i = 3 ; (argv[0])[i]!='\0' ; i++){
        destination[ptr++] = (argv[0])[i];
    }
    char command[100] = "cp mainfile cat cd mkdir dateIST dateUTC ls 'ls -a' rm Makefile "; 
    strcat(command , destination); 
    system(command); 
    char cd_command[150] = "cd "; 
    strcat(cd_command , destination);
    char remaining[]=  " && ./mainfile"; 
    strcat(cd_command , remaining);
    system(cd_command);  
    return 0;
}