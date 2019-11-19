#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>



int printfiles(char * dir, int offset){
  DIR* x = opendir(dir);
  struct dirent * file = readdir(x);
  int totalSize=0;
  int mySize = 0;
  while(file){
    struct stat filestats;
    stat(file->d_name,&filestats);
    if(file->d_type==4 && strcmp(file->d_name,".")!=0 && strcmp(file->d_name,"..")!=0){
      int i;
      for(i=0;i<offset;i++){
        printf("\t");
      }
      printf("dr %s \n",file->d_name);
      char x[strlen(dir)+strlen(file->d_name)+1];
      strcpy(x,dir);
      strcat(x,"/");
      strcat(x,file->d_name);
      //printf("%s\n",x);
      totalSize+=printfiles(x,offset+1);
      totalSize+=filestats.st_size;
      mySize+=filestats.st_size;
    }
    file = readdir(x);
  }
  x = opendir(".");
  //printf("Normal Files: \n");
  file = readdir(x);
  while(file){
    struct stat filestats;
    stat(file->d_name,&filestats);
    if(file->d_type!=4){
      int i;
      for(i=0;i<offset;i++){
        printf("\t");
      }
      printf("nf %s %ldB\n",file->d_name,filestats.st_size);
      totalSize+=filestats.st_size;
      mySize+=filestats.st_size;
    }
    file = readdir(x);
  }
  if(offset==0){
    printf("Summary Statistics \nTotal Dir Size %dB \nTotal Dir Size including subdirs %dB \n",mySize,totalSize);
  }
  return totalSize;
  //opendir returns a pointer to a directory stream (DIR *) this is a struct
  //readdir returns gives the next entry in the list

}
int main(int argc, char *argv[]){
  //argc is the number of arguments
  if(argc == 1){
    printf("Please specify a directory \n");
    char * directString;
    int limit=4096;
    fgets(directString, limit, stdin);
    printfiles(directString,0);
  }
  else{
      printfiles(argv[1],0);
  }

  return 0;
}
