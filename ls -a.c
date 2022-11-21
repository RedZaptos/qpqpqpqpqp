#include <stdio.h>
#include <sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<strings.h>
#include<limits.h>
#include<time.h>
#include<dirent.h>
//
//This code has been referenced from GitHub open source
//code after understanding its working completely

int main(int argc , char* argv[]){
	DIR *directory;
    struct dirent *file;
    char path[PATH_MAX];
    directory = opendir(getcwd(path, PATH_MAX));
    while(file = readdir(directory)){
        printf("%s", file->d_name);
        printf("\n");
    }
    printf("\n");
    return 0;
}


