#include <stdio.h>
#include <sys/stat.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<strings.h>
#include<limits.h>
#include<time.h>

int main(int argc , char* argv[]){


   
   FILE *fp;
   char c;
   fp = fopen(argv[0], "r");
   if(fp==NULL){
         printf("cat: %s: No such file exists" , argv[0]);
      } 
	int ctr = 0 ; 
   while(!feof(fp)){
                char c = fgetc(fp);
                if(c != '\n' && c!= EOF){
                    printf("%c", c);
                }
                else if(c == '\n'){
                    printf("$\n");
                }
            }
            printf("\n");

   fclose(fp);
	if(ctr == 0){
      printf("cat: %s: is a directory" , argv[0]);
   }
   printf("\n"); 

  
   return 0;
}