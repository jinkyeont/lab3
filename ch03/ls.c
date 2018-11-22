/*

주어진 디렉토리 내에 존재하는 파일과 디렉토리를 나열하고, 
디렉토리의 경우 재귀적으로 방문해서 그 디렉토리 내에 존재하는 파일과 
디렉토리를 나열하는 프로그램을 작성하시오.
즉, “ls –R” 명령과 동일한 결과를 보이도록 하시오.

 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int ls(char *argv)
{
    DIR *pdir;
    struct dirent *pde;
    struct stat buf;

    int i=0;
    int count=0;
    char *dir_name[255];

    memset(dir_name, '\0', sizeof(dir_name));
    memset(&pde, '\0', sizeof(pde));
    memset(&buf, '\0', sizeof(buf));

    if((pdir = opendir(argv)) < 0)
    {
        perror("opendir");
        return 1;
    }

    chdir(argv);

    printf("\n\n");
    printf("### DIR -> %s ###\n", argv);

    while ((pde = readdir(pdir))!=NULL)
    {
        lstat(pde->d_name, &buf);

        if(S_ISDIR(buf.st_mode) == 1)
        {
            if(!strcmp(pde->d_name, ".") || !strcmp(pde->d_name, ".."))
            {
                ;
            }
            else
            {
                dir_name[count] = pde->d_name;
                count - count + 1;
            }
        }

        printf("%s\t", pde->d_name);
    }
    for(i=0; i<count; i++)
    {
        ls(dir_name[i]);
    }

    printf("\n");
    closedir(pdir);
    chdir("..");
}

int main(int argc, char *argv[]){
    if(argc < 2)
    {
        fprintf(stderr, "Usage : file_dir dirname.\n");
        return 1;
    }
    ls(argv[1]);
    return 0;
}
