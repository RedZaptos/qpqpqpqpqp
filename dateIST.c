#include <stdio.h>
#include <sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<strings.h>
#include<limits.h>
#include<time.h>

int main(int argc , char* argv[]){
    time_t t = time(NULL);
    printf("IST %s" , ctime(&t));
    return 0;
  }
