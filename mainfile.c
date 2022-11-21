#include<stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <strings.h>
#include <limits.h>
#include<pthread.h>

char x_[]="ls"; 

void set_flag(); 

//echo->1 pwd->2 ls->3 dateIST->4 dateUTC->5 mkdir->6 rm->7 cat->8 cd->
//4096-> pwd: too many arguments

int date_flag = 0;
int pwd_flag = 0 ; 
int rm_flag = 0 ; 

char statement[100]; 

void reset_flags(){
    date_flag = 0 ;
    pwd_flag = 0 ;
    rm_flag = 0 ;  
}

int variable= -100 ;

int choice(char x[] , int size){
    if(size ==10){
        if(x[0]=='p' && x[1]=='w' && x[2]=='d' && x[4]=='-' && x[5]=='-' && x[6]=='h' && x[7]=='e' && x[8]=='l' && x[9]=='p'){
                 pwd_flag=1 ; 
                 return 2; 
            }
    }
    if(size==3){
        if(x[0]=='p' && x[1]=='w' && x[2]=='d'){
            return 2;
        }
        
        if(x[0]=='c' && x[1]=='a' && x[2]=='t'){
        	return 8; 
        }
    }
    
    if(size==4){
        if(x[0]=='e' && x[1]=='c' && x[2]=='h' && x[3]=='o'){
            return 1;
        }
        else if(x[0]=='d' && x[1]=='a' && x[2]=='t'&&x[3]=='e'){
    		return 4; 
    	}
    }
    if(size==2){
    	if(x[0]=='l' && x[1]=='s'){
    		return 3; 
    	}
    	if(x[0]=='r' && x[1]=='m'){
    		  return 7;
            
    	}
    	if(x[0]=='c' && x[1]=='d'){
    		return 9;
    	}
    }
    else if(x[0]=='d' && x[1]=='a' && x[2]=='t'&&x[3]=='e'){
    	if(x[0]=='d' && x[1]=='a' && x[2]=='t'&&x[3]=='e' && x[4]==' ' && x[5]=='-' && x[6]=='u'){
    		return 5; 
    	}
    	else if(x[0]=='d' && x[1]=='a' && x[2]=='t'&&x[3]=='e' && x[5]=='-' && x[6]!='u'){
    		date_flag = 1; 
    		return 5; 
    	}

    }
    if(size==5){
    	if(x[0]=='m' && x[1]=='k' && x[2]=='d'&& x[3]=='i' && x[4]=='r'){
    		return 6;
    	}
    }
    if(size==6){
        if((x[0]=='p' && x[1]=='w' && x[2]=='d' && x[4]=='-' && x[5]=='-')){
            return 2; 
        }
    }
    if(x[0]=='p' && x[1]=='w' && x[2]=='d' && (x[5]!=' ' ||x[5] != 'h')){
        return 4096; 
    }   
    return 0;
}

void Callecho(char echo_cmd[100]){
    int flag = 0 ;
    // char echo_cmd[100];
    // fgets (echo_cmd, 100, stdin);
    int size =0 ;
    while(echo_cmd[size]!='\0'){
          size++;
    }
    if(echo_cmd[0]!='"'){
        for(int i = 0 ; i<size ; i++){
            if(flag ==1 && variable!=-100){
                printf("%d" , variable);
                flag = 0 ;
            }
            else if(echo_cmd[i]!='$'){
                printf("%c" , echo_cmd[i]);
            }
            else{
                flag = 1;
            }
        }
        printf("\n");
    }
    else{
        for(int i = 0 ; i<size ; i++){
            if(flag ==1 && variable!=-100){
                printf("%d" , variable);
                flag = 0 ;
            }
            else if(echo_cmd[i]!='$' && echo_cmd[i]!='"'){
                printf("%c" , echo_cmd[i]);
            }
            else{
                flag = 1;
            }
        }
        printf("\n"); 
    }
}

void execute_ls(){
    char x[4] = "./ls"; 
    system(x_);
}

int pthread_or_fork(char a, char b){
    if(b=='&'  && a=='t'){
        return 1; 
    }
    return 0; 
}


void* echo_p(){
    printf("%s\n" , statement);
    return NULL ; 
}

char xx[50]; 

void set_flags(int ptr , char command[]){
    for(int i = 2 ; xx[i]!='\0' ; i++){
        command[ptr++] = xx[i];  
    }
}


void* pwd_p(){
    char x[50] = "./pwd";
    char command[50]; strcpy(xx , x); set_flags(0 , command); 
    system(command); 
    return NULL ; 
}

void* pwdhelp_p(){
    FILE *fp;
    char c;
    fp = fopen("/Users/utkarsh/Desktop/TER/pwd --help.text", "r"); 
    while((c = fgetc(fp)) != EOF){
    printf("%c", c);
    }
    fclose(fp);
    printf("\n"); 
    return NULL ; 
}

void* ls_p(){
    char x[50] = "./ls";
    char command[50]; strcpy(xx , x); set_flags(0 , command); 
    system(command); 
    return NULL ; 
}

void* ls_a_p(){
    system("./ls");
    return NULL ; 
}

void* date_p(){
    system("./dateIST");
    return NULL ; 
}


void* dateu_p(){
    system("./dateUTC");
    return NULL ; 
}


char rm_p_file_name[50]; 
void* rm_p(){
    char rm_cmd[100] = ""; 
    strcat(rm_cmd , rm_p_file_name);
    int size = 0 ; 
    while(rm_cmd[size] != '&'){
        size++ ; 
    }
    rm_cmd[size] = '\0'; 
    rm_cmd[size+1]= '\0'; 
    system(rm_cmd);
    for(int i = 0 ; i<50 ; i++){rm_p_file_name[i]='\0';}
    return NULL ; 
}

char mkdir_p_file_name[50]; 
void* mkdir_p(){
    char mkdir_cmd[100] = ""; 
    strcat(mkdir_cmd , mkdir_p_file_name);
    int size = 0 ; 
    while(mkdir_cmd[size] != '&'){
        size++ ; 
    }
    mkdir_cmd[size] = '\0'; 
    mkdir_cmd[size+1]= '\0'; 
    system(mkdir_cmd);
    for(int i = 0 ; i<50 ; i++){mkdir_p_file_name[i]='\0';}
    return NULL ; 
}

char cat_p_file_name[50]; 
void* cat_p(){
    char cat_cmd[100] = ""; 
    strcat(cat_cmd , cat_p_file_name);
    int size = 0 ; 
    while(cat_cmd[size] != '&'){
        size++ ; 
    }
    cat_cmd[size] = '\0'; 
    cat_cmd[size+1]= '\0'; 
    system(cat_cmd);
    printf("\n"); 
    for(int i = 0 ; i<50 ; i++){cat_p_file_name[i]='\0';}
    return NULL ; 
}


char cld[50]; 
void* cd_p(){
    pid_t pid = fork(); 
     if(pid==0){
     char *args[] = {cld , NULL , NULL , NULL}; 
     system("./cd");
     }
     else if(pid >0){
     wait(NULL); 
     }
    return NULL ; 
}

void* nothing_p(){
    return NULL;
}



int main(int argc , char* argv[]){
    while(1){
        char echo_cmd[100]; 
        char current_directory[300];
        printf("| ");
        char cmd[100];
        for(int i = 0 ; i<100 ; i++){cmd[i]='\0';}
        gets(cmd); 


        int size_of_cmd = 0;
        for(int i = 0 ; cmd[i]!='\0' ; i++){size_of_cmd++;}
        int check = pthread_or_fork(cmd[size_of_cmd-1] , cmd[size_of_cmd-2]); 

        if(cmd[0]=='c' && cmd[1]=='l' && cmd[2]=='e' && cmd[3]=='a' && cmd[4]=='r'){
            system("clear");
            char *args[] = {NULL , NULL , NULL , NULL}; 
            execv("./mainfile"  , args); 
        }

        if(cmd[0]=='r' && cmd[1]=='m' && cmd[3]=='-' && cmd[4]=='-' && cmd[5]=='v' && cmd[6]=='e' && cmd[7]=='r' &&  cmd[8]=='s' &&  cmd[9]=='i' &&  cmd[10]=='o' &&  cmd[11]=='n'){
                FILE *fp;
                   char c;
                   fp = fopen("rmhelp.text", "r");
                
                    int ctr = 0 ; 
                   while((c = fgetc(fp)) != EOF){
                      printf("%c", c);
                       ctr ++; 
                   }

                   fclose(fp);
                   printf("\n"); 
                   check = 2 ; 
            }
            if(cmd[0]=='c' && cmd[1]=='d' && cmd[3]=='-' && cmd[4]=='-' && cmd[5]=='v' && cmd[6]=='e' && cmd[7]=='r' &&  cmd[8]=='s' &&  cmd[9]=='i' &&  cmd[10]=='o' &&  cmd[11]=='n'){
                FILE *fp;
                   char c;
                   fp = fopen("cdversion.text", "r");
                
                    int ctr = 0 ; 
                   while((c = fgetc(fp)) != EOF){
                      printf("%c", c);
                       ctr ++; 
                   }

                   fclose(fp);
                   printf("\n"); 
                   check = 2 ; 
            }
            if(cmd[0]=='d' && cmd[1]=='a' && cmd[2]=='t' && cmd[3]=='e' && cmd[5]=='-' && cmd[6]=='-' && cmd[7]=='v' && cmd[8]=='e' && cmd[9]=='r' && cmd[10]=='s' && cmd[11]=='i' && cmd[12]=='o' && cmd[13]=='n'){
                printf("date: version 13.4.0 Copyright © 2020 Free Software Foundation, Inc.  License GPLv3+: \nGNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\nThis is free software: you are free to change and redistribute\nit.  There is NO WARRANTY, to the extent permitted by law."); 
            }

            if(cmd[0]=='l' && cmd[1]=='s' && cmd[3]=='-' && cmd[4]=='-' && cmd[5]=='v' && cmd[6]=='e' && cmd[7]=='r'){
                FILE *fp;
                   char c;
                   fp = fopen("lshelp.text", "r");
                
                    int ctr = 0 ; 
                   while((c = fgetc(fp)) != EOF){
                      printf("%c", c);
                       ctr ++; 
                   }

                   fclose(fp);
                   printf("\n"); 
                   check = 2 ; 
            } 
            if(cmd[0]=='m' && cmd[1]=='k' && cmd[2]=='d' && cmd[3]=='i' && cmd[4]=='r' && cmd[8]=='v' && cmd[9]=='e' && cmd[10]=='r' && cmd[11]=='s'){
                FILE *fp;
                   char c;
                   fp = fopen("mkdirversion.text", "r");
                
                    int ctr = 0 ; 
                   while((c = fgetc(fp)) != EOF){
                      printf("%c", c);
                       ctr ++; 
                   }

                   fclose(fp);
                   printf("\n"); 
                   check = 2 ; 
            } 

            if(cmd[0]=='c' && cmd[1]=='a' && cmd[2]=='t' && cmd[4]=='-' && cmd[6]=='v' && cmd[7]=='e' && cmd[8]=='r'){
                FILE *fp;
                   char c;
                   fp = fopen("catversion.text", "r");
                
                    int ctr = 0 ; 
                   while((c = fgetc(fp)) != EOF){
                      printf("%c", c);
                       ctr ++; 
                   }

                   fclose(fp);
                   printf("\n"); 
                   check = 2 ; 
            }
            if(cmd[0]=='p' && cmd[1]=='w' && cmd[2]=='d' && cmd[4]=='-' && cmd[6]=='v' && cmd[7]=='e' && cmd[8]=='r' && cmd[9]=='s' && cmd[10]=='i' && cmd[11]=='o' && cmd[12]=='n'){
                FILE *fp;
                   char c;
                   fp = fopen("cmdversion.text", "r");
                
                    int ctr = 0 ; 
                   while((c = fgetc(fp)) != EOF){
                      printf("%c", c);
                       ctr ++; 
                   }

                   fclose(fp);
                   printf("\n"); 
                   check = 2 ; 
            }
            if(cmd[0]=='d' & cmd[1]=='a' && cmd[2]=='t' && cmd[3]=='e' && cmd[4]==' ' && cmd[5]=='-' && cmd[6]=='d' && cmd[7]==' ' && cmd[8]=='t' && cmd[9]=='o' && cmd[10]=='d' && cmd[11]=='a' && cmd[12]=='y'){
                pid_t pid = fork(); 
                if(pid==0){
                    char *args[] = {NULL , NULL , NULL , NULL}; 
                    execv("./datetoday" , args);
                }
                else if(pid >0){
                    wait(NULL); 
                }
                check = 2; 
            }
            if(cmd[0]=='l' && cmd[1]=='s' && cmd[2]==' ' && cmd[3]=='-' && cmd[4]=='r'){
                pid_t pid = fork(); 
                    if(pid==0){
                        char *args[] = {NULL , NULL , NULL , NULL}; 
                        execv("./ls_r" , args);
                    }
                    else if(pid >0){
                        wait(NULL); 
                    }
            }
            if(cmd[0]=='m' && cmd[1]=='k' && cmd[2]=='d' && cmd[3]=='i' && cmd[4]=='r' && cmd[5]==' ' && cmd[6]=='-' && cmd[7]=='v'){
                char directory_name[100]; 
                int ptr = 0 ; 
                for(int i = 9 ; cmd[i]!='\0' ; i++){
                    directory_name[ptr++] = cmd[i]; 
                }
                pid_t pid = fork(); 
                if(pid==0){
                    // printf("%s\n",directory_name );
                    char *args[] = {directory_name , NULL , NULL , NULL}; 
                    printf("successfully created %s\n", directory_name);
                    execv("./mkdir" , args);

                }
                else if(pid >0){
                    wait(NULL); 
                }
                check=2; 
            }
            if(cmd[0]=='r' && cmd[1]=='m' && cmd[2]==' ' && cmd[3]=='-' && cmd[4]=='v'){
                char directory_name[100]; 
                int ptr = 0 ; 
                for(int i = 6 ; cmd[i]!='\0' ; i++){
                    directory_name[ptr++] = cmd[i]; 
                }
                pid_t pid = fork(); 
                if(pid==0){
                    // printf("%s\n",directory_name );
                    char *args[] = {directory_name , NULL , NULL , NULL}; 
                    printf("successfully deleted %s\n", directory_name);
                    execv("./rm" , args);

                }
                else if(pid >0){
                    wait(NULL); 
                }
                check=2; 
            }
            if(cmd[0]=='c' && cmd[1]=='a' & cmd[2]=='t' && cmd[3]==' ' && cmd[4]=='-' && cmd[5]=='n'){
                char directory_name[100]; 
                int ptr = 0 ; 
                for(int i = 7 ; cmd[i]!='\0' ; i++){
                    directory_name[ptr++] = cmd[i]; 
                }
                pid_t pid = fork(); 
                if(pid==0){
                    char *args[] = {directory_name , NULL , NULL , NULL}; 
                    execv("./cat2" , args);

                }
                else if(pid >0){
                    wait(NULL); 
                }
                check=2; 
            }
        


 

        if(cmd[0]=='c' && cmd[1]=='d' && check==1){
            int size = 0 ; 
            for(int i = 0  ; cmd[i]!='&' ; i++){
                size++; 
            }
            for(int i = size ; cmd[i]!='\0' ; i++){
                cmd[i]='\0';
            }
            check=0;
        }





        //                              PTHREAD 






        if(check ==1){
            pthread_t thread1; 
            //-------
            if(cmd[0]=='l' && cmd[1]=='s' && cmd[3]=='-' && cmd[4]=='a'){
                pthread_create(&thread1 , NULL , ls_p , NULL); 
            } 
            if(cmd[0]=='e' && cmd[1]=='c' && cmd[2]=='h' && cmd[3] == 'o'){
                int ptr = 0 ; 
                for(int i = 5 ; cmd[i]!='&' ; i++){
                    if(cmd[i]!='"' && cmd[i] != '$'){
                        statement[ptr++] = cmd[i]; 
                    }
                    if(cmd[i]=='$'){
                        statement[ptr++]= cmd[i+1]; 
                        i++ ; 
                    }
                }
                pthread_create(&thread1 , NULL , echo_p , NULL); 
            }
            else if(cmd[0]=='p' && cmd[1]=='w' && cmd[2]=='d'){
                if(cmd[0]=='p' && cmd[1]=='w' && cmd[2]=='d' && cmd[4]=='-' && cmd[5]=='-' && cmd[6]=='h' && cmd[7]=='e' && cmd[8]=='l' && cmd[9]=='p'){
                    pthread_create(&thread1 , NULL , pwdhelp_p , NULL); 
                }
                else if(cmd[0]=='p' && cmd[1]=='w' && cmd[2]=='d' && cmd[4]=='-' && cmd[5]=='-'){
                    pthread_create(&thread1 , NULL , pwd_p , NULL); 
                }
                
                else if(cmd[0]=='p' && cmd[1]=='w' && cmd[2]=='d' && cmd[4]=='&' && cmd[5]=='t'){
                    pthread_create(&thread1 , NULL , pwd_p , NULL); 
                }
                else{
                    printf("pwd: too many arguments\n"); 
                }
            }
            else if(cmd[0]=='l' && cmd[1]=='s'){
                if(cmd[0]=='l' && cmd[1]=='s' && cmd[3]=='-' && cmd[4]=='a' && cmd[6]=='&' && cmd[7]=='t'){
                    pthread_create(&thread1 , NULL , ls_a_p , NULL); 
                }
                else if(cmd[0]=='l' && cmd[1]=='s' && cmd[2]==' '  && cmd[3]=='&' && cmd[4]=='t'){
                    pthread_create(&thread1 , NULL , ls_p , NULL); 
                }
                else if(cmd[0]=='l' && cmd[1]=='s' && cmd[2]==' '  && cmd[3]=='-' && cmd[4]=='-'){
                    pthread_create(&thread1 , NULL , ls_p , NULL); 
                }
                else{
                    char msg[100] = ""; 
                    int ptr = 0 ; 
                    for(int i = 3 ; cmd[i]!='&' ; i++){
                        msg[ptr++] = cmd[i]; 
                    }
                    printf("ls: %s: No such file or directory exists\n" , msg); 
                }
            }
            else if(cmd[0]=='d' && cmd[1]=='a' && cmd[2]=='t' && cmd[3]=='e'){
                if(cmd[4]==' ' && cmd[5]=='&' && cmd[6]=='t'){
                    pthread_create(&thread1 , NULL , date_p , NULL); 
                }
                else if(cmd[5]=='-' && cmd[6]=='u'){
                    pthread_create(&thread1 , NULL , dateu_p , NULL);
                }
                else if(cmd[5]=='-' && cmd[6]!='u'){
                    printf("date: illegal option\nusage: date [-jnRu] [-d dst] [-r seconds] [-t west] [-v[+|-]val[ymwdHMS]] ... \n\t[-f fmt date | [[[mm]dd]HH]MM[[cc]yy][.ss]] [+format]\n"); 
                }
            }
            else if(cmd[0]=='r' && cmd[1]=='m'){
                strcpy(rm_p_file_name , cmd); 
                pthread_create(&thread1 , NULL , rm_p , NULL);
            }
            else if(cmd[0]=='m' && cmd[1]=='k' && cmd[2]=='d' && cmd[3]=='i' && cmd[4]=='r'){
                if(cmd[6]=='-' && cmd[7]=='-' && cmd[8]=='h' && cmd[9]=='e' && cmd[10]=='l' && cmd[11]=='p'){
                    FILE *fp;char c;fp = fopen("mkdirhelpfile.txt", "r"); while((c = fgetc(fp)) != EOF){printf("%c", c);}fclose(fp);printf("\n"); }
                else{
                    strcpy(mkdir_p_file_name , cmd); 
                    pthread_create(&thread1 , NULL , mkdir_p , NULL);
                }
            }
            else if(cmd[0]=='c' && cmd[1]=='a' && cmd[2]=='t'){
                strcpy(cat_p_file_name , cmd); 
                pthread_create(&thread1 , NULL , cat_p , NULL);
            }
            else if(cmd[0]=='c' && cmd[1]=='d'){
                pthread_create(&thread1 , NULL , cd_p , NULL);
            }

            else{
                pthread_create(&thread1 , NULL , nothing_p , NULL);
                printf("%s: invalid pthread command\n" , cmd);
            }
            
          
            pthread_join(thread1 , NULL);



            for(int i = 0 ; i<100 ;i++){statement[i]='\0'; }
            variable = -100 ;
        }









        //                      FORK() and EXEC()










        else if(check == 0){
             
       
            if(cmd[0]=='c' && cmd[1]=='d'){
                if(cmd[0]=='c' && cmd[1]=='d' && cmd[2]==' ' && cmd[3]=='/'){
                    system("cd /Users/utkarsh/Desktop/TER && ./mainfile"); 
                    exit(0);
                }
                else{
                    pid_t pid = fork(); 
                    if(pid==0){
                        char destination[100];                    
                        for(int i = 0 ; i<100 ; i++){destination[i]='\0';}
                        int ptr = 0 ; 
                        for(int i = 3 ; cmd[i]!='\0' ; i++){
                            destination[ptr++] = cmd[i];
                        }
                        char command[100] = "cp mainfile cat cd mkdir dateIST dateUTC ls 'ls -a' rm Makefile "; 
                        strcat(command , destination); 
                        system(command); 
                        char cd_command[150] = "cd "; 
                        strcat(cd_command , destination);
                        char remaining[]=  " && ./mainfile"; 
                        strcat(cd_command , remaining);
                        if(system(cd_command)==1){} 
                        else{
                            printf("cd: no such file or directory\n");
                        }
                        exit(0);  
                        }
                        else if(pid >0){
                            wait(NULL); 
                        }


                    
                }
            }

            if(cmd[0]=='l' && cmd[1]=='s' && cmd[3]=='-' && cmd[4]=='a'){
                pid_t pid = fork(); 
                    if(pid==0){
                        char *args[] = {NULL , NULL , NULL , NULL}; 
                        execv("./ls -a" , args);
                    }
                    else if(pid >0){
                        wait(NULL); 
                    }
            }

            if(cmd[0]=='l' && cmd[1]=='s' && cmd[3]=='-' && cmd[4]=='-'){
                pid_t pid = fork(); 
                    if(pid==0){
                        char *args[] = {NULL , NULL , NULL , NULL}; 
                        execute_ls(); 
                    }
                    else if(pid >0){
                        wait(NULL); 
                    }
            }



            if(cmd[0]=='m' && cmd[1]=='k' && cmd[2]=='d' && cmd[3]=='i' && cmd[4]=='r' && cmd[6]=='-' && cmd[7]=='-' && cmd[8]=='h' && cmd[9]=='e'  && cmd[10]=='l'  && cmd[11]=='p'){
                FILE *fp;char c;
                fp = fopen("mkdirhelpfile.txt", "r"); 
                while((c = fgetc(fp)) != EOF){
                    printf("%c", c);
                }
                fclose(fp);
                printf("\n"); 
            }
            else{
            if(cmd[0]=='e' && cmd[1]=='c' && cmd[2]=='h' && cmd[3]=='o'){
            	int temp_len = sizeof(cmd)/sizeof(cmd[0]); 
            	int k = 0 ; 
            	for(int i = 5 ; i<temp_len ; i++){
            		echo_cmd[k]=cmd[i]; 
            		k++;
            	}
            	strcpy(cmd , "echo"); 
            }
            //------------------------
            char remaining_string_ofcommand_copy[50]; 
            for(int i = 0 ; i<50 ; i++){remaining_string_ofcommand_copy[i]='\0';}

            if(cmd[0]=='m' && cmd[1]=='k' && cmd[2]=='d'&& cmd[3]=='i' && cmd[4]=='r'){
            	int i_i = 6 ; 
            	int ptr_ptr = 0 ;
            	while(cmd[i_i] !='\0'){
            		remaining_string_ofcommand_copy[ptr_ptr++]=cmd[i_i];
            		i_i++;
            	}
            	strcpy(cmd , "mkdir"); 
            	cmd[5]='\0'; 
            }


            if(cmd[0]=='r' && cmd[1]=='m'){
                if(cmd[3]=='-'&& cmd[4]=='i'){
                    rm_flag = 1; 
                }
            	int i_i=3; 
            	int ptr_ptr = 0; 
            	while(cmd[i_i] !='\0'){
            		remaining_string_ofcommand_copy[ptr_ptr++]=cmd[i_i];
            		i_i++;
            	}
            	strcpy(cmd , "rm"); 
            	cmd[2]= '\0'; 
            }
            if(cmd[0]=='c' && cmd[1]=='a' && cmd[2]=='t'){
            	int i_i=4; 
            	int ptr_ptr = 0; 
            	int temp_len = sizeof(cmd)/sizeof(cmd[0]); 
            	while(i_i < temp_len){
            		remaining_string_ofcommand_copy[ptr_ptr++]=cmd[i_i];
            		i_i++;
            	}
            	strcpy(cmd , "cat"); 
            	cmd[3]='\0'; 
            }
            if(cmd[0]=='c' && cmd[1]=='d'){
            	int i_i=3; 
            	int ptr_ptr = 0; 
            	int temp_len = sizeof(cmd)/sizeof(cmd[0]); 
            	while(i_i < temp_len){
            		remaining_string_ofcommand_copy[ptr_ptr++]=cmd[i_i];
            		i_i++;
            	}
            	strcpy(cmd , "cd"); 
            	cmd[3]='\0'; 
            }
         

            int size=0;
          	while(cmd[size]!='\0'){
               size++ ; 
            }
            int c = choice(cmd , size);


         
            if(c==1){
                Callecho(echo_cmd);
            }

            else if(c==2){
                if(pwd_flag==0){
                    char buffer[500];
                    FILE *output;
                    char *pwd = fgets(buffer, sizeof(buffer), popen("/bin/pwd", "r"));
                    pwd = strtok(pwd, "\n");
                    printf("%s\n", pwd);
                }
                else if(pwd_flag ==1){
                    FILE *fp;
                    char c;
                    fp = fopen("/Users/utkarsh/Desktop/TER/pwd --help.text", "r"); 
                    while((c = fgetc(fp)) != EOF){
                        printf("%c", c);
                    }
                    fclose(fp);
                    printf("\n"); 
                    pwd_flag = 0;
                }
            }

            else if((cmd[0]-'0')==('x'-'0')){
            	char dummy; 
            	scanf("%s \n" , &dummy); 
            
                scanf("%d \n" , &variable);

            }
            else if((cmd[0]-'0')==('y'-'0')){
            	char dummy; 
            	scanf("%s \n" , &dummy); 
    
                scanf("%d \n" , &variable);
            }
            else if(c==3){
            	pid_t pid = fork(); 
            	if(pid==0){
    	        	char *args[] = {NULL , NULL , NULL , NULL}; 
                    execute_ls(); 
    	        }
    	        else if(pid >0){
    	        	wait(NULL); 
    	        }
            }
            else if(c==4){
            	pid_t pid = fork(); 
            	if(pid==0){
    	        	char *args[] = {NULL , NULL , NULL , NULL}; 
    	        	execv("./dateIST" , args);
    	        }
    	        else if(pid >0){
    	        	wait(NULL); 
    	        }
            }
            else if(c==5){
            	if(date_flag == 1){
            		printf("date: illegal option\nusage: date [-jnRu] [-d dst] [-r seconds] [-t west] [-v[+|-]val[ymwdHMS]] ... \n\t[-f fmt date | [[[mm]dd]HH]MM[[cc]yy][.ss]] [+format]\n");
            	}
            	else{
    	        	pid_t pid = fork(); 
    	        	if(pid==0){
    		        	char *args[] = {NULL , NULL , NULL , NULL}; 
    		        	execv("./dateUTC" , args);
    		        }
    		        else if(pid >0){
    		        	wait(NULL); 
    		        }
    		    }
            }

            else if(c==6){
            	pid_t pid = fork(); 
            	if(pid==0){
    	        	char *args[] = {remaining_string_ofcommand_copy , NULL , NULL , NULL}; 
    	        	execv("./mkdir" , args);
    	        }
    	        else if(pid >0){
    	        	wait(NULL); 
    	        }
            }

            else if(c==7){
                
                if(rm_flag ==0){
                    pid_t pid = fork(); 
                	if(pid==0){
        	        	// char *args[] = {remaining_string_ofcommand_copy , NULL , NULL , NULL}; 
                        int size= 0 ; 
                         char *args[] = {remaining_string_ofcommand_copy , NULL , NULL , NULL};
               
                        for(int i = 0 ; remaining_string_ofcommand_copy[i]!='\0' ; i++){
                            size++ ; 
                        }
              
                        // if(remaining_string_ofcommand_copy[size-2]=='-' && remaining_string_ofcommand_copy[size-1]=='v'){
                        //     remaining_string_ofcommand_copy[size-2]='\0'; 
                        //     remaining_string_ofcommand_copy[size-1]='\0'; 
                        //     for(int i = size-1 ; remaining_string_ofcommand_copy[i]!='\0' ; i++){
                        //         remaining_string_ofcommand_copy[i]='\0';
                        //     }
                        //     printf("Successfully deleted %s\n", remaining_string_ofcommand_copy);
                            
                        //     char *args[] = {remaining_string_ofcommand_copy , NULL , NULL , NULL}; 
                        // }
        	        	execv("./rm" , args);
        	        }
        	        else if(pid >0){
        	        	wait(NULL); 
        	        }
                }
                else if(rm_flag==1){
                    int i1 = 0 , i2=i1+3;
                    while(remaining_string_ofcommand_copy[i2]!='\0'){
                        remaining_string_ofcommand_copy[i1]=remaining_string_ofcommand_copy[i2];
                        i2++ ; 
                        i1++;
                    }
                    remaining_string_ofcommand_copy[i1]='\0'; 
                    printf("remove %s? " , remaining_string_ofcommand_copy); 
                    char y_n; 
                    scanf("%c", &y_n);
                    if(y_n=='y'){
                        pid_t pid = fork(); 
                        if(pid==0){
                        char *args[] = {remaining_string_ofcommand_copy , NULL , NULL , NULL}; 
                        execv("./rm" , args);

                        }
                        else if(pid >0){
                            wait(NULL); 
                        }
                    }
                    else{
                        continue; 
                    }
                }
            }
            
            else if(c==8){
            	pid_t pid = fork(); 
            	if(pid==0){
                    int size = 0 ; 
                       for(int i = 0 ; remaining_string_ofcommand_copy[i] != '\0' ; i++){
                          size++ ; 
                       }
                       int space_size = 0 ; 
                       for(int i = 0 ; remaining_string_ofcommand_copy[i] != ' ' ; i++){
                          space_size++ ; 
                       }
                       char link1[200]=""; 
                       char link2[200]="";
                       
                       if(space_size < size){

                          int ptr1=0; 
                          for(int i = 0 ; i<space_size ; i++){
                             link1[ptr1++]=remaining_string_ofcommand_copy[i];
                          }
                          int ptr2=0; 
                          for (int i = space_size+1;  i<size ; i++){
                             link2[ptr2++]=remaining_string_ofcommand_copy[i];
                          }
 
           
                          char *args[] = {link1 , link2 , NULL , NULL}; 
                          execv("./cat" , args);
                       }
                       else{                
                        int ptr1=0; 
                          for(int i = 0 ; i<space_size ; i++){
                             link1[ptr1++]=remaining_string_ofcommand_copy[i];
                          }
                          printf("%s\n",link1 );
                          char *args[] = {link1 , NULL , NULL , NULL}; 
                          execv("./cat" , args);

                       }

                       
    	        	
    	        	
    	        }
    	        else if(pid >0){
    	        	wait(NULL); 
    	        }
            }
            else if(c==4096){
                printf("pwd: too many arguments\n");
            }
    		else{
                if(cmd[0]=='c' && cmd[1]=='d'){

                }
                else{
    		      printf("%s\n",cmd);
              }
    		 }

            reset_flags(); 
    	}
    }
}
    
    


    for(int i = 0 ; xx[i]!='\0' ;i++){
        xx[i] = '\0';
    }


	 return 0;
    
}



 



