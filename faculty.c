#include <stdio.h>
// #include "structures.c"
#include <sys/socket.h>
#include <fcntl.h>
#include<string.h>
#include <sys/stat.h>
#include<stdbool.h>
bool login_faculty(int client_socket,int id,char* password)
{
    printf("%d",id);
    printf("%s",password);
    int file=open("faculty.txt",O_RDONLY);
    struct FacultyDetail faculty;
    ssize_t read_result;
    int found=0;

    //reading file and checking if id and passwords match
    while(read(file,&faculty,sizeof(struct FacultyDetail)))
    {
        if(faculty.id==id)
        {
           if(strcmp(faculty.password,password)==0)
           {
            found=1;
            break;
           }
        }
    }
    close(file);
    return found;    
}
void add_course(int client_socket,int id)
{
    int fd=open("course.txt",O_RDWR);
    struct CourseDetail course;
    memset(&course,0,sizeof(course));
    char buff[30];
   
    struct stat file_info;
    fstat(fd, &file_info);

    if(file_info.st_size != 0){
        lseek(fd,-(sizeof(struct CourseDetail)),SEEK_END);
        struct CourseDetail stucpy;
        read(fd,&stucpy,sizeof(struct CourseDetail));
        course.id = stucpy.id + 1;
    }
    else{
       course.id= 1;
    }
    
    course.faculty_id=id;
    char text1[]="enter course name:";
    send(client_socket,text1,strlen(text1),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(course.name,buff);
    memset(&buff,0,sizeof(buff));

    char text2[]="enter department name:";
    send(client_socket,text2,strlen(text2),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(course.department,buff);
    memset(&buff,0,sizeof(buff));

    char text3[]="enter available seats:";
    send(client_socket,text3,strlen(text3),0);
    recv(client_socket,&buff,sizeof(buff),0);
    course.seat=atoi(buff);
    course.max_seats=atoi(buff);
    // strcpy(course.seat,buff);
    memset(&buff,0,sizeof(buff));

    char text4[]="enter course credit:";
    send(client_socket,text4,strlen(text4),0);
    recv(client_socket,&buff,sizeof(buff),0);
    course.credit=atoi(buff);
    // strcpy(course.credit,buff);
    memset(&buff,0,sizeof(buff));

    lseek(fd,0,SEEK_END);
    write(fd,&course,sizeof(struct CourseDetail));

    printf("Id=%d\n",course.id);
    printf("name=%s\n",course.name);
    printf("department=%s\n",course.department);
    printf("seats=%d\n",course.seat);
    printf("credit=%d\n",course.credit);
    
    close(fd);
    char sentMsg[] = "Course added successfully.\n";
    send(client_socket, sentMsg, sizeof(sentMsg), 0);

}

void view_course(int client_socket,int id)
{
    // printf("hi\n");
    int fd=open("course.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct CourseDetail course;
    int ack=1;
    // printf("after 1\n");
    while(read(fd,&course,sizeof(course)))
    {
        if(course.faculty_id==id)
        {
            send(client_socket,&ack,sizeof(ack),0);
            send(client_socket,&course,sizeof(course),0);
        }
    }
    ack=0;
    send(client_socket,&ack,sizeof(ack),0);
}

void remove_course(int client_socket,int id)
{
    int fd=open("course.txt",O_RDWR);
    struct CourseDetail rem_course;
   
    int temp_fd = open("temp.txt", O_CREAT|O_RDWR|S_IRUSR|S_IWUSR,0777);
    
    //reading file and finding id to delete
    while(read(fd,&rem_course,sizeof(rem_course)))
    {
        if(rem_course.id!=id)
        {
            write(temp_fd, &rem_course,sizeof(struct CourseDetail));
        }
    }

    close(fd);
    close(temp_fd);

    remove("course.txt");
    rename("temp.txt", "course.txt");
}

void modify_course(int client_socket)
{
    int file = open("course.txt", O_RDWR);
    if (file == -1) {
        perror("Error opening file");
    }
    struct CourseDetail detail;
    char course_buff[30];
    memset(&course_buff,0,sizeof(course_buff));
    char txt1[]="enter course id:";
    send(client_socket,txt1,strlen(txt1),0);
    recv(client_socket,&course_buff,sizeof(course_buff),0);
    int course_id=atoi(course_buff);
    printf("received id:%d\n",course_id);
    
    //set the cursor to the end of the previous record
    int offset=(course_id-1)*sizeof(struct CourseDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&detail,sizeof(struct CourseDetail));
    printf("id=%d\n",detail.id);
    printf("name=%s\n",detail.name);
    printf("department=%s\n",detail.department);
    printf("seats=%d\n",detail.seat);
    printf("credit=%d\n",detail.credit);
    printf("faculty id=%d\n",detail.faculty_id);

    char course_field[30];
    memset(&course_field,0,sizeof(course_field));
    char txt2[]="enter field:";
    send(client_socket,txt2,strlen(txt2),0);
    recv(client_socket,&course_field,sizeof(course_field),0);
    printf("received field:%s\n",course_field);
    
    char course_value[30];
    memset(&course_value,0,sizeof(course_value));
    char txt3[]="enter value:";
    send(client_socket,txt3,strlen(txt3),0);
    recv(client_socket,&course_value,sizeof(course_value),0);
    printf("received value:%s\n",course_value);
    
    //compare each value with field
    if(strcmp(course_field,"name")==0)
    {
        memset(&detail.name,0,sizeof(detail.name));
        memcpy(&detail.name,&course_value,strlen(course_value));
    }
    else if(strcmp(course_field,"seat")==0)
    {
        detail.seat=atoi(course_value);
    }
    else if(strcmp(course_field,"credit")==0)
    {
        detail.credit=atoi(course_value);
    }
    else if(strcmp(course_field,"department")==0)
    {
        memset(&detail.department,0,sizeof(detail.department));
        memcpy(&detail.department,&course_value,strlen(course_value));
    }
    printf("id=%d\n",detail.id);
    printf("name=%s\n",detail.name);
    printf("department=%s\n",detail.department);
    printf("seats=%d\n",detail.seat);
    printf("credit=%d\n",detail.credit);
    printf("faculty id=%d\n",detail.faculty_id);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&detail,sizeof(struct CourseDetail));
    
    char course_send[]="successfully.\n";
    send(client_socket,course_send,sizeof(course_send),0);
    close(file);
    
}

void change_password(int client_socket,int id,char* password)
{
    int fd=open("faculty.txt",O_RDWR);
    if(fd==-1)
    {
        perror("ERROR:");
    }
    struct FacultyDetail faculty;
    while(read(fd,&faculty,sizeof(faculty)))
    {
        if(faculty.id==id)
        {
            strcpy(faculty.password,password);
            printf("%s",faculty.password);
            lseek(fd, -sizeof(faculty), SEEK_CUR); // Move the file pointer back to the beginning of the record
            write(fd, &faculty, sizeof(faculty)); 
            char password[30]="password change successfully..";
            send(client_socket,password,sizeof(password),0);
            break; 
        }   
    }
}