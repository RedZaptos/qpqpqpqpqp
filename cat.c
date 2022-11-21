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
   while((c = fgetc(fp)) != EOF){
      printf("%c", c);
	   ctr ++; 
   }

   fclose(fp);
	if(ctr == 0){
      printf("cat: %s: is a directory" , argv[0]);
   }
   printf("\n"); 

   if(argv[1] != NULL){
      FILE *fp;
      char c;
      fp = fopen(argv[1], "r"); 
      if(fp==NULL){
         printf("cat: %s: No such file exists" , argv[1]);
      }
      int ctr = 0 ; 
      while((c = fgetc(fp)) != EOF){
         printf("%c", c);
         ctr ++; 
      }

      fclose(fp);
      if(ctr == 0){
         printf("cat: %s: is a directory" , argv[1]);
      }
      printf("\n"); 
   }
  
   return 0;
}