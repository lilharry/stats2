#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

int sizedir(DIR* dir){
	int size = 0;
	struct dirent *data;
	struct stat *curStats;
	data = readdir(dir);
	while (data){
		if (data->d_type == DT_REG){
			stat(data->d_name,curStats);
			size += curStats->st_size;
		}
		
		if (data->d_type == DT_DIR && (data->d_name != "." || data->d_name != "..")){
			DIR* newdir = opendir(data->d_name);
			size += sizedir(newdir);
		}
		
		data = readdir(dir);
	}
	return size;
	
}

int main(){ 
  DIR *dir;
  struct dirent *data;
  dir = opendir(".");
  printf("Directory size: %d\n",sizedir(dir));
  data = readdir(dir);
  printf("Directories:\n");

  while (data){
	  if (data->d_type  == DT_DIR){
		  printf("\t%s\n",data->d_name);
	  }
	  if (data->d_type  == DT_REG){  
		  break;
	  }
	  data = readdir(dir);
  }
  
  
  printf("Files:\n");
  while (data){
	  if (data->d_type == DT_REG){  
		  printf("\t%s\n",data->d_name);
	  }
	  data = readdir(dir);
  }
  
  closedir(dir);
  
}
