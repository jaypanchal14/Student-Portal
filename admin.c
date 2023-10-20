#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include<string.h>
#include <sys/stat.h>
#include "structures.c"

void add_student(int client_socket) {
    
    int fd=open("student.txt",O_RDWR);
    struct StudentDetail student;
    memset(&student,0,sizeof(student));
    char buff[30];
   
    struct stat file_info;
    fstat(fd, &file_info);

    if(file_info.st_size != 0){
        lseek(fd,-(sizeof(struct StudentDetail)),SEEK_END);
        struct StudentDetail stucpy;
        read(fd,&stucpy,sizeof(struct StudentDetail));
        student.id = stucpy.id + 1;
    }
    else{
        student.id= 1;
    }
    strcpy(student.password,"darshit");
    // student.active=true;
    char msg1[]="enter student name:";
    send(client_socket,msg1,strlen(msg1),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.name,buff);
    memset(&buff,0,sizeof(buff));

    char msg2[]="enter student age:";
    send(client_socket,&msg2,strlen(msg2),0);
    recv(client_socket,&buff,sizeof(buff),0);
    student.age=atoi(buff);
    //strcpy(student.age,buff);
    memset(&buff,0,sizeof(buff));

    char msg3[]="enter student email:";
    send(client_socket,&msg3,strlen(msg3),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.email,buff);
    memset(&buff,0,sizeof(buff));

    char msg4[]="enter student address:";
    send(client_socket,&msg4,strlen(msg4),0);
    recv(client_socket,&buff,sizeof(buff),0);
    strcpy(student.address,buff);
    memset(&buff,0,sizeof(buff));
    
    student.active=1;

    lseek(fd,0,SEEK_END);
    write(fd,&student,sizeof(struct StudentDetail));

    printf("Id=%d\n",student.id);
    printf("name=%s\n",student.name);
    printf("password=%s\n",student.password);
    printf("age=%d\n",student.age);
    printf("email=%s\n",student.email);
    printf("address=%s\n",student.address);

    close(fd);

    char successMsg[] = "Student added successfully.\n";
    send(client_socket, successMsg, sizeof(successMsg), 0);
}

void view_student(int client_socket)
{
    int file=open("student.txt",O_RDONLY|O_CREAT,0744);
    
    char idprompt[]="enter student id:\n";
    send(client_socket,&idprompt,strlen(idprompt),0);
 
    char idstr[10];
    int id;
    recv(client_socket,&idstr,sizeof(idstr),0);
    id=atoi(idstr);

    //reaching end of the previous record 
    int offset=(id-1)*sizeof(struct StudentDetail);
    struct StudentDetail student_detail;

    //using lseek and accessing that information by setting pointer to current offset
    int seekinfo=lseek(file,offset,SEEK_SET);
    int dataread=read(file,&student_detail,sizeof(struct StudentDetail));
    if(student_detail.active==1)
    {
    char tmp[10*sizeof(struct StudentDetail)];
    sprintf(tmp,"\nStudent id:%d\nname:%s\nage:%d\nemail:%s\naddress:%s\nactive_status:%d\n",student_detail.id,student_detail.name,student_detail.age,student_detail.email,student_detail.address,student_detail.active);

    send(client_socket,&tmp,strlen(tmp),0);
    }
    else
    {
        char error_msg[]="No Data Avilable..\n";
        send(client_socket,error_msg,sizeof(error_msg),0);
    }
    close(file);
}

void add_faculty(int client_socket) {
    
    int fd=open("faculty.txt",O_RDWR);
    struct FacultyDetail faculty;
    memset(&faculty,0,sizeof(faculty));
    char fac_buff[30];

    struct stat file_info_faculty;
    fstat(fd, &file_info_faculty);

    if(file_info_faculty.st_size!=0){
        lseek(fd,-(sizeof(struct FacultyDetail)),SEEK_END);
        struct FacultyDetail faculty_cpy;
        read(fd,&faculty_cpy,sizeof(struct FacultyDetail));
        faculty.id = faculty_cpy.id+1;
    }
    else{
        faculty.id= 1;
    }

    strcpy(faculty.password,"darshit");
    // faculty.active=true;
    char msg10[]="enter faculty name:";
    send(client_socket,msg10,strlen(msg10),0);
    recv(client_socket,&fac_buff,sizeof(fac_buff),0);
    strcpy(faculty.name,fac_buff);
    memset(&fac_buff,0,sizeof(fac_buff));

    char msg11[]="enter faculty department:";
    send(client_socket,&msg11,strlen(msg11),0);
    recv(client_socket,&fac_buff,sizeof(fac_buff),0);
    strcpy(faculty.department,fac_buff);
    memset(&fac_buff,0,sizeof(fac_buff));

    char msg12[]="enter faculty email:";
    send(client_socket,&msg12,strlen(msg12),0);
    recv(client_socket,&fac_buff,sizeof(fac_buff),0);
    strcpy(faculty.email,fac_buff);
    memset(&fac_buff,0,sizeof(fac_buff));

    char msg13[]="enter faculty address:";
    send(client_socket,&msg13,strlen(msg13),0);
    recv(client_socket,&fac_buff,sizeof(fac_buff),0);
    strcpy(faculty.address,fac_buff);
    memset(&fac_buff,0,sizeof(fac_buff));

    char msg14[]="enter faculty designation:";
    send(client_socket,&msg14,strlen(msg14),0);
    recv(client_socket,&fac_buff,sizeof(fac_buff),0);
    strcpy(faculty.designation,fac_buff);
    memset(&fac_buff,0,sizeof(fac_buff));
    
    lseek(fd,0,SEEK_END);
    write(fd,&faculty,sizeof(struct FacultyDetail));

    printf("Id=%d\n",faculty.id);
    printf("name=%s\n",faculty.name);
    printf("password=%s\n",faculty.password);
    printf("department=%s\n",faculty.department);
    printf("email=%s\n",faculty.email);
    printf("address=%s\n",faculty.address);
    printf("designation=%s\n",faculty.designation);

    close(fd);

    // Send success message back to the client
    char successmsg[] = "Student added successfully.\n";
    send(client_socket, successmsg, sizeof(successmsg), 0);
}

void view_faculty(int client_socket)
{
   
    int fd=open("faculty.txt",O_RDONLY|O_CREAT,0744);
    
    //send idprompt
    char idprompt1[]="enter faculty id:\n";
    send(client_socket,&idprompt1,strlen(idprompt1),0);
 
    //recieving id
    char id_str[10];
    int id;
    recv(client_socket,&id_str,sizeof(id_str),0);
    id=atoi(id_str);

    //reaching top of the id we want to access data of 
    int offset=(id-1)*sizeof(struct FacultyDetail);
    struct FacultyDetail faculty_detail;

    //using lseek and accessing that information by setting pointer to current offset
    lseek(fd,offset,SEEK_SET);
    read(fd,&faculty_detail,sizeof(struct FacultyDetail));
    char temp[10*sizeof(struct FacultyDetail)];
    sprintf(temp,"\nFaculty id:%d\nname:%s\ndepartment:%s\nemail:%s\naddress:%s\ndesignation:%s\n",faculty_detail.id,faculty_detail.name,faculty_detail.department,faculty_detail.email,faculty_detail.address,faculty_detail.designation);

    send(client_socket,&temp,strlen(temp),0);
    close(fd);
}

void modify_student(int client_socket)
{
    int file = open("student.txt", O_RDWR);
    if (file == -1) {
        perror("Error opening file");
    }
    struct StudentDetail stu1;
    char buff1[30];
    char msg15[]="enter student id:";
    send(client_socket,msg15,strlen(msg15),0);
    recv(client_socket,&buff1,sizeof(buff1),0);
    int stu_id=atoi(buff1);
    printf("received id:%d\n",stu_id);
    
    //set the cursor to the end of the previous record
    int offset=(stu_id-1)*sizeof(struct StudentDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&stu1,sizeof(struct StudentDetail));
    printf("Id=%d\n",stu1.id);
    printf("name=%s\n",stu1.name);
    printf("password=%s\n",stu1.password);
    printf("age=%d\n",stu1.age);
    printf("email=%s\n",stu1.email);
    printf("address=%s\n",stu1.address);

    char field[30];
    memset(&field,0,sizeof(field));
    char msg16[]="enter field:";
    send(client_socket,msg16,strlen(msg16),0);
    recv(client_socket,&field,sizeof(field),0);
    printf("received field:%s\n",field);
    
    char value[30];
    memset(&value,0,sizeof(value));
    char msg17[]="enter value:";
    send(client_socket,msg17,strlen(msg17),0);
    recv(client_socket,&value,sizeof(value),0);
    printf("received value:%s\n",value);
    
    //compare each value with field
    if(strcmp(field,"name")==0)
    {
        memset(&stu1.name,0,sizeof(stu1.name));
        memcpy(&stu1.name,&value,strlen(value));
    }
    else if(strcmp(field,"age")==0)
    {
        stu1.age=atoi(value);
    }
    else if(strcmp(field,"email")==0)
    {
        memset(&stu1.email,0,sizeof(stu1.email));
        memcpy(&stu1.email,&value,strlen(value));
    }
    else if(strcmp(field,"address")==0)
    {
        memset(&stu1.address,0,sizeof(stu1.address));
        memcpy(&stu1.address,&value,strlen(value));
    }
    printf("Id=%d\n",stu1.id);
    printf("name=%s\n",stu1.name);
    printf("password=%s\n",stu1.password);
    printf("age=%d\n",stu1.age);
    printf("email=%s\n",stu1.email);
    printf("address=%s\n",stu1.address);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&stu1,sizeof(struct StudentDetail));
    
    char succ_send[]="successfully.\n";
    send(client_socket,succ_send,sizeof(succ_send),0);
    close(file);
    
}

void modify_faculty(int client_socket)
{
    int file = open("faculty.txt", O_RDWR);
    if (file == -1) {
        perror("Error opening file");
    }
    struct FacultyDetail fac1;
    char buff2[30];
    char msg18[]="enter faculty id:";
    send(client_socket,msg18,strlen(msg18),0);
    recv(client_socket,&buff2,sizeof(buff2),0);
    int fac_id=atoi(buff2);
    printf("received id:%d\n",fac_id);
    
    //set the cursor to the end of the previous record
    int offset=(fac_id-1)*sizeof(struct FacultyDetail);
    lseek(file,offset,SEEK_SET);
    //read the structure
    read(file,&fac1,sizeof(struct FacultyDetail));
    printf("id=%d\n",fac1.id);
    printf("name=%s\n",fac1.name);
    printf("password=%s\n",fac1.password);
    printf("department=%s\n",fac1.department);
    printf("email=%s\n",fac1.email);
    printf("address=%s\n",fac1.address);
    printf("designation=%s\n",fac1.designation);

    char fac_field[30];
    memset(&fac_field,0,sizeof(fac_field));
    char msg19[]="enter field:";
    send(client_socket,msg19,strlen(msg19),0);
    recv(client_socket,&fac_field,sizeof(fac_field),0);
    printf("received field:%s\n",fac_field);
    
    char fac_value[30];
    memset(&fac_value,0,sizeof(fac_value));
    char msg20[]="enter value:";
    send(client_socket,msg20,strlen(msg20),0);
    recv(client_socket,&fac_value,sizeof(fac_value),0);
    printf("received value:%s\n",fac_value);
    
    //compare each value with field
    if(strcmp(fac_field,"name")==0)
    {
        memset(&fac1.name,0,sizeof(fac1.name));
        memcpy(&fac1.name,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"department")==0)
    {
        memset(&fac1.department,0,sizeof(fac1.department));
        memcpy(&fac1.department,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"email")==0)
    {
        memset(&fac1.email,0,sizeof(fac1.email));
        memcpy(&fac1.email,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"address")==0)
    {
        memset(&fac1.address,0,sizeof(fac1.address));
        memcpy(&fac1.address,&fac_value,strlen(fac_value));
    }
    else if(strcmp(fac_field,"designation")==0)
    {
        memset(&fac1.designation,0,sizeof(fac1.designation));
        memcpy(&fac1.designation,&fac_value,strlen(fac_value));
    }
    printf("id=%d\n",fac1.id);
    printf("name=%s\n",fac1.name);
    printf("password=%s\n",fac1.password);
    printf("department=%s\n",fac1.department);
    printf("email=%s\n",fac1.email);
    printf("address=%s\n",fac1.address);
    printf("designation=%s\n",fac1.designation);
    
    //write the data to the file
    lseek(file,offset,SEEK_SET);
    write(file,&fac1,sizeof(struct FacultyDetail));
    
    char fac_send[]="successfully.\n";
    send(client_socket,fac_send,sizeof(fac_send),0);
    close(file);
    
}

void activate_student(int client_socket)
{
    char student_id_str[10];
    int student_id;
    char prompt[] = "Enter the ID of the student to activate: ";
    send(client_socket, prompt, strlen(prompt), 0);
    recv(client_socket, student_id_str, sizeof(student_id_str), 0);
    student_id = atoi(student_id_str);

    
    int student_file = open("student.txt", O_RDWR);

    //at the end of the previous record
    int offset = (student_id - 1) * sizeof(struct StudentDetail);
    int seek_result = lseek(student_file, offset, SEEK_SET);

    struct StudentDetail student;
    read(student_file, &student, sizeof(struct StudentDetail));

    // Activate the student
    student.active = 1;

    //set the cursor to the start of that record
    lseek(student_file, offset, SEEK_SET);
    write(student_file, &student, sizeof(struct StudentDetail));


    close(student_file);

    char success_txt[] = "Student activated successfully.";
    send(client_socket, success_txt, sizeof(success_txt), 0);
}

void block_student(int client_socket)
{
    char student_id_str1[10];
    int student_id1;

    char prompt1[] = "Enter the ID of the student to activate: ";
    send(client_socket, prompt1, strlen(prompt1), 0);
    recv(client_socket, student_id_str1, sizeof(student_id_str1), 0);
    student_id1 = atoi(student_id_str1);

    int student_file = open("student.txt", O_RDWR);

    // Set the cursor to the start of desired record
    int offset = (student_id1 - 1) * sizeof(struct StudentDetail);
    int seek_result = lseek(student_file, offset, SEEK_SET);

    struct StudentDetail student;
    int read_result = read(student_file, &student, sizeof(struct StudentDetail));

    student.active = 0;
    lseek(student_file, offset, SEEK_SET);

    write(student_file, &student, sizeof(struct StudentDetail));

    close(student_file);
    char success_msg[] = "Student blocked successfully.";
    send(client_socket, success_msg, sizeof(success_msg), 0);
}