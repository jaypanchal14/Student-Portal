#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "structures.c"
#define PORT 4567
int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    //AF_NET is ipv4
    //SOCK_STREAM is for TCP
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    // Convert IP address from string to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Successfully created connection with server.\n");

    //recieving main menu prompt and writing to standard output
    char buf[200];
    int recvdata = recv(client_socket,&buf,sizeof(buf),0);
    int writedata = write(1,buf,recvdata);
    
    //taking user choice to login as
    char choiceprompt[] ="Enter your choice : ";
    writedata = write(1,choiceprompt,sizeof(choiceprompt));

    char readchoice;
    int choice = read(0,&readchoice,sizeof(readchoice));

    //sending choice to server
    int senddata = send(client_socket,&readchoice,sizeof(readchoice),0);

    if(readchoice=='1')
    {
     char server_response_admin[512];
     memset(server_response_admin,'\0',512*sizeof(char));
     //strcpy(server_response_admin,"");
     recv(client_socket, &server_response_admin, sizeof(server_response_admin), 0);
     while(1)
    {
        //admin menu
        printf("%s",server_response_admin);
        //taking choice from that admin menu
        char choice_admin;
        printf("Enter your choice admin: ");
        scanf(" %c", &choice_admin);
        send(client_socket, &choice_admin, sizeof(choice_admin), 0);
        if(choice_admin=='9') break;
        //add student
        if(choice_admin=='1')
        {
        // struct StudentDetail newStudent;
           char buffer[512],ques[30];
            memset(&ques,0,sizeof(ques));
            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            // getchar();
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            recv(client_socket,&ques,sizeof(ques),0);
            printf("%s",ques);
            memset(ques,0,sizeof(ques));
            scanf("%s",ques);
            send(client_socket,ques,sizeof(ques),0);
            memset(&ques,0,sizeof(ques));

            char rec_msg[512];
            recv(client_socket, &rec_msg, sizeof(rec_msg), 0);
            printf("%s\n", rec_msg);
     }
     if(choice_admin=='2')
     {
        char idprompt[50];
        memset(idprompt,0,sizeof(idprompt));
        recv(client_socket,idprompt,sizeof(idprompt),0);
        printf("%s",idprompt);

        //sending id
        char send_id[10];
        scanf("%s",send_id);
        send(client_socket,send_id,sizeof(send_id),0);

        //recieving the student data
        char studentData[300];

        memset(studentData,0,sizeof(studentData));
        recv(client_socket,&studentData,sizeof(studentData),0);
        printf("%s",studentData);   
     }
    if(choice_admin=='3')
    {
       // struct StudentDetail newStudent;
        char ques1[30];
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        recv(client_socket,&ques1,sizeof(ques1),0);
        printf("%s",ques1);
        memset(ques1,0,sizeof(ques1));
        scanf("%s",ques1);
        send(client_socket,ques1,sizeof(ques1),0);
        memset(&ques1,0,sizeof(ques1));

        char received_msg[512];
        recv(client_socket, &received_msg, sizeof(received_msg), 0);
        printf("%s\n", received_msg);
     }

     if(choice_admin=='4')
     {
        
        char id_prompt[50];
        memset(id_prompt,0,sizeof(id_prompt));
        recv(client_socket,id_prompt,sizeof(id_prompt),0);
        printf("%s",id_prompt);

        //sending id
        char send_id1[10];
        scanf("%s",send_id1);
        send(client_socket,send_id1,sizeof(send_id1),0);

        //recieving the student data
        char student_data[300];

        memset(student_data,0,sizeof(student_data));
        recv(client_socket,&student_data,sizeof(student_data),0);
        printf("%s",student_data);   
    }

    if(choice_admin=='5')
    {
        char get_sid[50];
        memset(get_sid,0,sizeof(get_sid));
        recv(client_socket,get_sid,sizeof(get_sid),0);
        printf("%s",get_sid);
        memset(get_sid,0,sizeof(get_sid));
        scanf("%s",get_sid);
        send(client_socket,get_sid,sizeof(get_sid),0);
        memset(get_sid,0,sizeof(get_sid));
        char s_response[400];
        memset(s_response,0,sizeof(s_response));
        recv(client_socket,s_response,sizeof(s_response),0);
        printf("%s",s_response);
    }
    if(choice_admin=='6')
    {
        char get_sid1[50];
        memset(get_sid1,0,sizeof(get_sid1));
        recv(client_socket,get_sid1,sizeof(get_sid1),0);
        printf("%s",get_sid1);
        memset(get_sid1,0,sizeof(get_sid1));
        scanf("%s",get_sid1);
        send(client_socket,get_sid1,sizeof(get_sid1),0);
        memset(get_sid1,0,sizeof(get_sid1));
        char s_response1[400];
        memset(s_response1,0,sizeof(s_response1));
        recv(client_socket,s_response1,sizeof(s_response1),0);
        printf("%s",s_response1);
    }

     if(choice_admin=='7')
     {

        char get_id[30],set_id[30];
        // int set_id;
        memset(get_id,0,sizeof(get_id));
        recv(client_socket,get_id,sizeof(get_id),0);
        printf("%s",get_id);
        scanf("%s",set_id);
        send(client_socket,set_id,sizeof(int),0);

        char get_field[30],set_field[30];
        memset(get_field,0,sizeof(get_field));
        recv(client_socket,get_field,sizeof(get_field),0);
        printf("%s",get_field);
        scanf("%s",set_field);
        send(client_socket,set_field,sizeof(set_field),0);

        char get_value[30],set_value[30];
        memset(get_value,0,sizeof(get_value));
        recv(client_socket,get_value,sizeof(get_value),0);
        printf("%s",get_value);
        scanf("%s",set_value);
        send(client_socket,set_value,sizeof(set_value),0);

        char gotit[40];
        memset(gotit,0,sizeof(gotit));
        recv(client_socket,&gotit,sizeof(gotit),0);
        printf("%s",gotit);
     }

     if(choice_admin=='8')
     {

        char get_id[30],set_id[30];
        // int set_id;
        memset(get_id,0,sizeof(get_id));
        recv(client_socket,get_id,sizeof(get_id),0);
        printf("%s",get_id);
        scanf("%s",set_id);
        send(client_socket,set_id,sizeof(int),0);

        char get_field[30],set_field[30];
        memset(get_field,0,sizeof(get_field));
        recv(client_socket,get_field,sizeof(get_field),0);
        printf("%s",get_field);
        scanf("%s",set_field);
        send(client_socket,set_field,sizeof(set_field),0);

        char get_value[30],set_value[30];
        memset(get_value,0,sizeof(get_value));
        recv(client_socket,get_value,sizeof(get_value),0);
        printf("%s",get_value);
        scanf("%s",set_value);
        send(client_socket,set_value,sizeof(set_value),0);

        char gotit[40];
        memset(gotit,0,sizeof(gotit));
        recv(client_socket,&gotit,sizeof(gotit),0);
        printf("%s",gotit);
     }

    } 
}

if(readchoice=='2')
{
    //faculty module
    char login_prompt[30];
    memset(&login_prompt,0,sizeof(login_prompt));
    char send_login_id[30];
    char password_prompt[30];
    memset(&password_prompt,0,sizeof(password_prompt));
    char send_password[30];

    //recieving login prompt
    recv(client_socket,&login_prompt,sizeof(login_prompt),0);
    printf("%s",login_prompt);

    //sending login id
    scanf("%s",send_login_id);
    send(client_socket,send_login_id,sizeof(send_login_id),0);

    //recieving password prompt
    recv(client_socket,&password_prompt,sizeof(password_prompt),0);
    printf("%s",password_prompt);

    //sending password
    scanf("%s",send_password);
    send(client_socket,send_password,sizeof(send_password),0);

    //recieving valid value
    int valid;
    recv(client_socket,&valid,sizeof(valid),0);
    if(valid==1)
    {
        char result[37];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
        
        //if login is successfull recieve student menu
        char server_response_faculty[512];
        memset(server_response_faculty,0,512*sizeof(char));
        recv(client_socket, &server_response_faculty, sizeof(server_response_faculty),0);
        // printf("%s",server_response_faculty);
       while(1)
       {
        //admin menu
        printf("%s",server_response_faculty);
        //taking choice from that admin menu
        char choice_student;
        printf("Enter your choice student: ");
        scanf(" %c", &choice_student);
        send(client_socket, &choice_student, sizeof(choice_student), 0);
        if(choice_student=='6') break;

        if(choice_student=='1')
        {
            int ack;
            while(1)
            {
              recv(client_socket,&ack,sizeof(ack),0);
            //   printf("%d",ack);
              if(ack==0)break;
              struct CourseDetail course;
              recv(client_socket,&course,sizeof(course),0);
              printf("Course id=%d\n",course.id);
              printf("Course Name=%s\n",course.name);
              printf("Department offering course=%s\n",course.department);
              printf("Number of Seats=%d\n",course.seat);
              printf("course credit=%d\n",course.credit);
            }    
        }
         
        if(choice_student=='2')
        {
            //recieve choice of course
            char course_id_prompt[40];
            recv(client_socket,&course_id_prompt,sizeof(course_id_prompt),0);
            printf("%s",course_id_prompt);

            //send courseid
            int course_id;
            scanf("%d",&course_id);
            send(client_socket,&course_id,sizeof(course_id),0); 

            char receive_msg[30];
            recv(client_socket,&receive_msg,sizeof(receive_msg),0);
            printf("%s",receive_msg); 
        }
        if(choice_student=='3')
        {
            char delete[35];
            memset(&delete,0,sizeof(delete));
            recv(client_socket,&delete,sizeof(delete),0);
            printf("%s",delete);

            //send courseid
            int send_id;
            scanf("%d",&send_id);
            send(client_socket,&send_id,sizeof(send_id),0); 

            // char received_msg[10];
            // recv(client_socket,&received_msg,sizeof(received_msg),0);
            // printf("%s",received_msg); 
        }
        if(choice_student=='4')
        {
            int stu_ack;
            while(1)
            {
              recv(client_socket,&stu_ack,sizeof(stu_ack),0);
              if(stu_ack==0)break;
              struct course_enrolled stu_course;
              recv(client_socket,&stu_course,sizeof(stu_course),0);
              printf("Course id=%d\n",stu_course.course_id);
              printf("Course Name=%s\n",stu_course.course_name);
              printf("student id=%d\n",stu_course.student_id);
              printf("faculty id=%d\n",stu_course.faculty_id);
              
            }    
        }

        if(choice_student=='5')
        {
            //recieving password prompt
            char recv_pasword[30];
            memset(&recv_pasword,0,sizeof(recv_pasword));
            recv(client_socket,&recv_pasword,sizeof(recv_pasword),0);
            printf("%s",recv_pasword);

            //sending password of user
            char password[20];
            scanf("%s",password);
            send(client_socket,password,sizeof(password),0);

            char rec_result[30];
            memset(&rec_result,0,sizeof(rec_result));
            recv(client_socket,&rec_result,sizeof(rec_result),0);
            printf("%s",rec_result);
            printf("\n");
        }
   

        }

    }
    else
    {
        char result[32];
        recv(client_socket,&result,sizeof(result),0);
        printf("%s",result);
    }
}



if(readchoice=='3')
{

     //faculty module
    char login_prompt[30];
    memset(&login_prompt,0,sizeof(login_prompt));
    char send_login_id[30];
    char password_prompt[30];
    char send_password[30];

    //recieving login prompt
    recv(client_socket,&login_prompt,sizeof(login_prompt),0);
    printf("%s",login_prompt);

    //sending login id
    scanf("%s",send_login_id);
    send(client_socket,send_login_id,sizeof(send_login_id),0);

    //recieving password prompt
    recv(client_socket,&password_prompt,sizeof(password_prompt),0);
    printf("%s",password_prompt);

    //sending password
    scanf("%s",send_password);
    send(client_socket,send_password,sizeof(send_password),0);

    //recieving valid value
    int valid;
    recv(client_socket,&valid,sizeof(valid),0);
    if(valid==1)
    {
    char result[37];
    recv(client_socket,&result,sizeof(result),0);
    printf("%s",result);
        
    //if login is successfull recieve faculty menu
    char server_response_faculty[512];
    memset(server_response_faculty,'\0',512*sizeof(char));
    //strcpy(server_response_admin,"");
    recv(client_socket, &server_response_faculty, sizeof(server_response_faculty), 0);
    while(1)
    {
        //admin menu
        printf("%s",server_response_faculty);
        //taking choice from that admin menu
        char choice_faculty;
        printf("Enter your choice faculty: ");
        scanf(" %c", &choice_faculty);
        send(client_socket, &choice_faculty, sizeof(choice_faculty), 0);
        if(choice_faculty=='6') break;

        if(choice_faculty=='1')
        {
            int ack;
            while(1)
            {
              recv(client_socket,&ack,sizeof(ack),0);
            //   printf("%d",ack);
              if(ack==0)break;
              struct CourseDetail course;
              recv(client_socket,&course,sizeof(course),0);
              printf("Course id=%d\n",course.id);
              printf("Course Name=%s\n",course.name);
              printf("Department offering course=%s\n",course.department);
              printf("Number of Seats=%d\n",course.seat);
              printf("course credit=%d\n",course.credit);
            }    
        }
        //add course
        if(choice_faculty=='2')
        {
        
           char buffer[512],fac_ques[30];
            memset(&fac_ques,0,sizeof(fac_ques));
            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            // getchar();
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            recv(client_socket,&fac_ques,sizeof(fac_ques),0);
            printf("%s",fac_ques);
            memset(fac_ques,0,sizeof(fac_ques));
            scanf("%s",fac_ques);
            send(client_socket,fac_ques,sizeof(fac_ques),0);
            memset(&fac_ques,0,sizeof(fac_ques));

            char fac_rec_msg[512];
            recv(client_socket, &fac_rec_msg, sizeof(fac_rec_msg), 0);
            printf("%s\n", fac_rec_msg);
        }
        
        if(choice_faculty=='3')
        {
            char delete_propmt[40];
            memset(&delete_propmt,0,sizeof(delete_propmt));
            recv(client_socket,&delete_propmt,sizeof(delete_propmt),0);
            printf("%s",delete_propmt);

            //sending id to delete
            int sendId;
            scanf("%d",&sendId);
            send(client_socket,&sendId,sizeof(sendId),0);
        }
         if(choice_faculty=='4')
        {

            char get_id[30],set_id[30];
            memset(get_id,0,sizeof(get_id));
            recv(client_socket,get_id,sizeof(get_id),0);
            printf("%s",get_id);
            scanf("%s",set_id);
            send(client_socket,set_id,sizeof(sizeof(set_id)),0);

            char get_field[30],set_field[30];
            memset(get_field,0,sizeof(get_field));
            recv(client_socket,get_field,sizeof(get_field),0);
            printf("%s",get_field);
            scanf("%s",set_field);
            send(client_socket,set_field,sizeof(set_field),0);

            char get_value[30],set_value[30];
            memset(get_value,0,sizeof(get_value));
            recv(client_socket,get_value,sizeof(get_value),0);
            printf("%s",get_value);
            scanf("%s",set_value);
            send(client_socket,set_value,sizeof(set_value),0);

            char gotit[40];
            memset(gotit,0,sizeof(gotit));
            recv(client_socket,&gotit,sizeof(gotit),0);
            printf("%s",gotit);
        }
        if(choice_faculty=='5')
        {
            //recieving password prompt
            char recv_pasword[30];
            memset(&recv_pasword,0,sizeof(recv_pasword));
            recv(client_socket,&recv_pasword,sizeof(recv_pasword),0);
            printf("%s",recv_pasword);

            //sending password of user
            char password[20];
            scanf("%s",password);
            send(client_socket,password,sizeof(password),0);

            char receiving_result[30];
            memset(&receiving_result,0,sizeof(receiving_result));
            recv(client_socket,&receiving_result,sizeof(receiving_result),0);
            printf("%s",receiving_result);
            printf("\n");
        }
    }
 }
else
{
char result[32];
recv(client_socket,&result,sizeof(result),0);
printf("%s",result);
}  
}    
    close(client_socket);
    return 0;
}