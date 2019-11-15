#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
void printfiles(char * dir, int offset){
  DIR* x = opendir(dir);
  struct dirent * file = readdir(x);
  int totalSize=0;

  while(file){
    struct stat filestats;
    stat(file->d_name,&filestats);
    if(file->d_type==4){
      int i;
      for(i=0;i<offset;i++){
        printf(" ");
      }
      printf("dr %s \n",file->d_name);
      printfiles(file->d_name,offset+1);
      totalSize+=filestats.st_size;
    }
    file = readdir(x);
  }
  x = opendir(".");
  printf("Normal Files: \n");
  file = readdir(x);
  while(file){
    struct stat filestats;
    stat(file->d_name,&filestats);
    if(file->d_type!=4){
      printf("nf %s %ldB\n",file->d_name,filestats.st_size);
      totalSize+=filestats.st_size;
    }
    file = readdir(x);
  }
  printf("Summary Statistics \nTotal Dir Size %d \n",totalSize);
  //opendir returns a pointer to a directory stream (DIR *) this is a struct
  //readdir returns gives the next entry in the list

}
int main(){
  printfiles(".",0);
  return 0;
}
