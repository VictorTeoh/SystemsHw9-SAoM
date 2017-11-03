#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//to nicify the bytes
char *prettyBytes( long unsigned buff, int B, char *retStr){
  if (buff / 1024 >= 1){
    prettyBytes( buff / 1024, ++B, retStr);
  }
  else{
    sprintf( retStr, "%lu", buff);
    if (B == 0){
      strcat( retStr, "B");
    }
    else if (B == 1){
      strcat( retStr, "KB");
    }
    else if (B == 2){
      strcat( retStr, "MB");
    }
    else if (B == 3){
      strcat( retStr, "GB");
    }
    else if (B == 4){
      strcat( retStr, "TB");
    }
  }
  return retStr;
}

int main(){
  DIR * d;
  d = opendir( ".");
  struct dirent  *entry;
  int i = 0;

  //summing the 
  struct stat sb;
  printf("Total Directory Size: ");
  while(entry = readdir(d)){
    if(entry->d_type == DT_REG){
      stat(entry->d_name, &sb);
      i += sb.st_size;
    }
  }
  //reusing prettyBytes
  char retStr[256];
  printf("%s\n", prettyBytes(i, 0, retStr));

  //bring back to the top of the directory
  closedir(d);
  d = opendir( ".");

  //only print out directorites within this directory
  printf("Directories:\n");
  while(entry = readdir(d)){
    if(entry->d_type == DT_DIR){
      printf("%s\n", entry->d_name);
    }
  }

  closedir(d);
  d = opendir( ".");

  printf("Regular files:\n");
  while(entry = readdir(d)){
    if(entry->d_type == DT_REG){
      printf("%s\n", entry->d_name);
    }
  }

  closedir(d);
}
