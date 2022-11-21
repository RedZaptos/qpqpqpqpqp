#include <stdio.h>
#include <sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<strings.h>
#include<limits.h>
#include<time.h>

int main(int argc , char* argv[]){
    struct tm *local;
    time_t t  = time(NULL);
    printf("UTC %s", asctime(gmtime(&t)));
    return 0;
  }
