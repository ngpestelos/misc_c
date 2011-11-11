#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

int walk(const char *path);

int main(void)
{
  walk("/tmp");

  return 0;
}

/**
 * Recursively walk a directory
 */
int walk(const char *path)
{
  struct dirent *dirp;
  DIR           *dp;
  int           ret;
  
  if ((dp = opendir(path)) == NULL) {
    printf("Can't read directory %s\n", path);
    return -1;
  }
  
  printf("Walking %s\n", path);
  printf("---\n");
    
  while((dirp = readdir(dp)) != NULL) {
    if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
      continue;
  
    // Append path with / and dirname
    int len = strlen(path) + 1 + strlen(dirp->d_name);
    
    char *buf = malloc(len);
    buf[len - 1] = '\0';
    
    strncat(buf, path, strlen(path));
    strncat(buf + strlen(path), "/", 1);
    strncat(buf + strlen(path) + 1, dirp->d_name, strlen(dirp->d_name));

    // If this is a directory, walk it
    struct stat statbuf;
    lstat(buf, &statbuf);
    
    if (S_ISDIR(statbuf.st_mode)) {
      printf("%s is a directory\n", buf);
      walk(buf);
    } else if (S_ISREG(statbuf.st_mode)) {
      printf("%s is a regular file\n", buf);
    }
    
    // Skip other file types
      
    buf = '\0';
    free(buf);
  }

  return ret;
}
