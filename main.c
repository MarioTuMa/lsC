#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
int main(){
  DIR* x = opendir(".");
  struct dirent * file = readdir(x);
  int haveFinishedDirs = 0;
  int totalSize=0;
  printf("Dirs: \n");
  while(file){
    struct stat filestats;
    stat(file->d_name,&filestats);
    if(0==haveFinishedDirs && filestats.st_size!=4096){
      printf("Normal Files: \n");
      haveFinishedDirs=1;
    }
    printf("%s %ldB\n",file->d_name,filestats.st_size);
    totalSize+=filestats.st_size;
    file = readdir(x);
  }
  //opendir returns a pointer to a directory stream (DIR *) this is a struct
  //readdir returns gives the next entry in the list

  return 0;
}
