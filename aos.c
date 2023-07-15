#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//function which creates the file of name fname and print its file descriptor
void create_file(char *fname, char *permission)
{
    if (open(fname,O_RDONLY)>0){
        printf("\nFile already exists.\n");
        return;
    }

    //creating the file
    // int fd = creat(fname,S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
    int x=0;
    sscanf(permission,"%o",&x);
    printf("%d",x);
    int fd = creat(fname,x);

    //error message
    if(fd<0)
    {
        printf("\nError in creating a file\n");
        return;
    }

    printf("\nFile created successfully!!!\n");
    printf("\nFile descriptor of newly created file: %d\n",fd);
    
    //closing the file
    fd = close(fd);
    if (fd<0)
    {
        printf("\nError in closing the file\n");
        return;
    }

}

//function to read n bytes from file fname
void read_file(char *fname, int seek, int n)
{
    // char buffer[n];
    //open the file
    int fd = open(fname, O_RDONLY);

    //error message
    if(fd<0)
    {
        printf("\nError in opening the file\n");
        return;
    }
    else
    {
        printf("\nFile opened successfully !!! \nFile Data :-\n");
    }

    //moving the pointer 
    lseek(fd, seek, 0);

    //read n bytes from file
    if (n == 0){ 
        // char *buff[1];
        char *buff = (char *) calloc(1, sizeof(char));
        int count;
        while((count = read(fd, buff, 1)) == 1){
            printf("%s", buff);
        }
    }
    else{
        char *buffer = (char *) calloc(n, sizeof(char));
        printf("\nData read from file:\n");
        read(fd, buffer, n);
        printf("%s", buffer);
    }

    //closing the file
    fd=close(fd);

    //error message
    if (fd<0)
    {
        printf("\nError in closing the file\n");
        return;
    }
}

void read_help(char *fname)
{
    char *buffer = (char *) calloc(1, sizeof(char));

    //open the file
    int fd = open(fname, O_RDONLY);

    //error message
    if(fd<0)
    {
        printf("\nError in opening the help\n");
        return;
    }

    int count;
    while((count = read(fd, buffer, 1)) > 0){
        printf("%s", buffer);
    }

    //closing the file
    fd=close(fd);

    //error message
    if (fd<0)
    {
        printf("\nError in closing the help\n");
        return;
    }
}

//func to write n bytes to file fname
void write_file(char *fname, int seek, char c)
{
    int fd;
    //open the files
    if (c == 'w') 
        fd = open(fname, O_WRONLY | O_CREAT,0777);
    else if (c == 't')
        fd = open(fname, O_TRUNC | O_WRONLY | O_CREAT,0777);
    else if (c == 'a')
        fd = open(fname, O_APPEND | O_WRONLY | O_CREAT,0777);

    //error message
    if(fd<0){
        printf("\nError in opening file: %s",fname);
        return;
    }
    else
        printf("\nEnter Data:- \n");

    char *buffer = (char *) calloc(1024, sizeof(char));

    lseek(fd, seek, 0);
    //reading 
    int count;
    while((count = read(0, buffer, 1024)) != 0) 
        write(fd, buffer, count);
    
    //writing the content
    printf("\nWriting Successfully !!!\n");
 
    //closing the file
    fd=close(fd);
    // fd2=close(fd2);
    //error message
    if (fd<0)
    {
        printf("\nError in closing the files\n");
        return;
    }
}

//copy n bytes from source to target file 
void copy_file(char *source, char *target, int seek, int n)
{
    //open the files
    int fd1=open(source, O_RDONLY);
    int fd2=open(target, O_TRUNC | O_WRONLY | O_CREAT,0777);

    //error message
    if(fd1<0){
        printf("\nError in opening file: %s",source);
        return;
    }
    if (fd2 < 0)
    {
        printf("\nError in opening the file: %s\n",target);
        return;
    }

    //reading and writing the content
    if(n == 0){
        lseek(fd1,seek,0);
        int count;
        char *buffer = (char *) calloc(1024, sizeof(char));
        while((count = read(fd1,buffer,1024))!=0){
            write(fd2,buffer,count);
        }
    }
    else{
        char *buffer = (char *) calloc(n, sizeof(char));
        lseek(fd1,seek,0);
        read(fd1,buffer, n);
        write(fd2,buffer, n);
    }
 
    //closing the file
    fd1=close(fd1);
    fd2=close(fd2);
    printf("\nCopied successfully...\n");

    //error message
    if (fd1<0||fd2<0)
    {
        printf("\nError in closing the files\n");
        return;
    }
    
}


//display statistical info of a file fname
void display_info(char *fname)
{
    struct stat fileStat;
    int fd = stat(fname, &fileStat);
    //error message
    if(fd<0)
    {
        printf("\nError in accessing the info regarding file\n");
        return;
    }
    printf("Statistical Information of %s\n", fname);
    printf("\nUser ID: \t\t%u\n",fileStat.st_uid);
    printf("\nFile Size: \t\t%d bytes\n", fileStat.st_size);
    printf("Number of Links: \t%d\n", fileStat.st_nlink);
    printf("File inode: \t\t%d\n", fileStat.st_ino);

    printf("File Permissions: \t");
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
}

//Main function
int main(int argc, char **argv)
{
    if(argc<2)
    {
        printf("\nError: Type help for more details.\n");
        return 0;
    }

    //readme file
    else if (strcmp(argv[1],"help")==0){
        read_help("help.md");
        return 0;
    }

    //creating a file
    else if (strcmp(argv[1],"c") == 0){
        if (argc == 3) create_file(argv[2],"0777");
        else if (argc ==  4) create_file(argv[2],argv[3]);
        else printf("Invalid arguments :Type help for more details");
    }

    //reading a file
    else if (strcmp(argv[1],"r") == 0){
        if (argc == 3) read_file(argv[2],0,0);
        else if (argc == 4) read_file(argv[2],atoi(argv[3]),0);
        else if (argc == 5) read_file(argv[2],atoi(argv[3]),atoi(argv[4]));
        else printf("Invalid arguments :Type help for more details");
    }

    //writing a file
    else if (strcmp(argv[1],"w") == 0){
        if (argc == 3) write_file(argv[2],0,'w');
        else if (argc == 4) write_file(argv[2],atoi(argv[3]),'w');
        else printf("Invalid arguments :Type help for more details");
    }

    //truncate a file
    else if (strcmp(argv[1],"wt") == 0){
        if (argc == 3) write_file(argv[2],0,'t');
        else if (argc == 4) write_file(argv[2],atoi(argv[3]),'t');
        else printf("Invalid arguments :Type help for more details");
    }

    //append a file
    else if (strcmp(argv[1],"a")==0){
        if (argc == 3) write_file(argv[2],0,'a');
        else if (argc == 4) write_file(argv[2],atoi(argv[3]),'a');        
        else printf("Invalid arguments :Type help for more details");
    }

    //copy file
    else if (strcmp(argv[1],"cp")==0){
        if (argc == 4) copy_file(argv[2],argv[3],0,0);
        else if (argc == 5) copy_file(argv[2],argv[3],atoi(argv[4]),0);
        else if (argc == 6) copy_file(argv[2],argv[3],atoi(argv[4]),atoi(argv[5]));
        else printf("Invalid arguments :Type help for more details");
    }

    //display the info of a file
    else if (strcmp(argv[1],"d") == 0){
        if (argc ==3) display_info(argv[2]);
        else printf("Invalid arguments :Type help for more details");
    }
    else{
        printf("\nINVALID : Type help for more details.");
    }
    return 0;
}
