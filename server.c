#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "admin.c"
#include "faculty.c"
#include "student.c"

void handle_client(int client_socket) {

    char string[20];
    char buff[] = "----------Welcome to Academia ----------\n"
    "Choose login type \n"
    "1. Admin\t 2. Student\t 3. Faculty\n";

    //sending menu to client
    int bytesSend = send(client_socket,&buff,sizeof(buff),0);

    //recieving choice from client
    int recvBytes = recv(client_socket,&string,sizeof(string),0);
    string[recvBytes] = '\0';  //append the null at the end
    int choice = atoi(string);

    if(choice==1)
    {
        char menu_student[] = "Choose from the following options\n" 
                                "1) Add Student \n"
                                "2) View Student Details \n"
                                "3) Add Faculty \n"
                                "4) View Faculty Details \n"
                                "5) Activate Student \n"
                                "6) Block Student \n"
                                "7) Modify Student Details \n"
                                "8) Modify Faculty Details \n"
                                "9) Logout and Exit \n";
        send(client_socket,menu_student,strlen(menu_student), 0);
        while(1)
        {
            //if choice is 1 send admin menu
            char student_choice;
            recv(client_socket, &student_choice,sizeof(student_choice), 0);
            //call to respective c functions
            if(student_choice=='9') break;
            if(student_choice=='1')
            {
                add_student(client_socket);
            }
            if(student_choice=='2')
            {
                view_student(client_socket);
            }
            if(student_choice=='3')
            {
                add_faculty(client_socket);
            }
            if(student_choice=='4')
            {
                view_faculty(client_socket);
            }
            if(student_choice=='5')
            {
                activate_student(client_socket);
            }
            if(student_choice=='6')
            {
                block_student(client_socket);
            }
            if(student_choice=='7')
            {
                modify_student(client_socket);
            }
            if(student_choice=='8')
            {
                modify_faculty(client_socket);
            }
        }
     
    } 
    // printf("\n");
    if(choice==2)
    {

      char login_prompt[]="enter login id:";
      char password_prompt[]="enter password:";
      char recv_login_id[30];
      char recv_password[30];
      //sending login prompt
      send(client_socket,login_prompt,strlen(login_prompt),0);

      //recieving login id
      recv(client_socket,&recv_login_id,sizeof(recv_login_id),0);
      int stu_id=atoi(recv_login_id);
      printf("%d\n",stu_id);

      //sending password prompt
      send(client_socket,password_prompt,strlen(password_prompt),0);

      //recieving password
      recv(client_socket,&recv_password,sizeof(recv_password),0);
      printf("%s\n",recv_password);
      
      //sending valid value to check if user is found or not
      int valid_stu = login_student(client_socket,stu_id,recv_password);
      send(client_socket,&valid_stu,sizeof(valid_stu),0);

      if(valid_stu==1)
      {
        char result[]="login successfull....welcome Student\n";
        send(client_socket,result,strlen(result),0);

        //if login is successfull send faculty menu
        char menu_student[] = "Choose from the following options\n" 
                                "1) View all Courses \n"
                                "2) Enroll new Course \n"
                                "3) Drop Course \n"
                                "4) View Enrolled Course Detail \n"
                                "5) Change Password \n"
                                "6) Logout and exit \n";
        send(client_socket,menu_student,strlen(menu_student), 0);
        while(1)
        {
            //if choice is 1 send admin menu
            char student_choice;
            recv(client_socket, &student_choice,sizeof(student_choice), 0);
            //call to respective c functions
            if(student_choice=='6') break;
            if(student_choice=='1')
            {
                view_all_course(client_socket);
            }
            if(student_choice=='2')
            {
                send(client_socket,"Enter course id,want to register:",sizeof("Enter course id,want to register?"),0);

                //recieve courseid
                int course_id;
                recv(client_socket,&course_id,sizeof(course_id),0);

                enroll_course(client_socket,stu_id,course_id);
            }
            if(student_choice=='3')
            {
                 //asking the user which course they want to denroll
                send(client_socket,"Enter the course id you want to denroll for: ",sizeof("Enter the course id you want to denroll for: "),0);

                //recieving course id
                int course_id;
                recv(client_socket,&course_id,sizeof(course_id),0);

                //calling de-enroll function
                drop_course(client_socket,stu_id,course_id);
                // remove_course(client_socket);
            }
            if(student_choice=='4')
            {
                view_enrolled_course(client_socket,stu_id);
            }
            if(student_choice=='5')
            {
                char old_password[]="enter password:";
                send(client_socket,old_password,strlen(old_password),0);
            
                //recieving password of user
                char password[20];
                recv(client_socket,&password,sizeof(password),0);
                change_password_student(client_socket,stu_id,password);
            }
    
        }
      }
      else
      {
        char sent_result[]="invalid credentials...try again\n";
        send(client_socket,sent_result,strlen(sent_result),0);
      }
      
    } 

    if(choice==3)
    {
      char login_prompt[]="enter login id:";
      char password_prompt[]="enter password:";
      char recv_login_id[30];
      char recv_password[30];
      //sending login prompt
      send(client_socket,login_prompt,strlen(login_prompt),0);

      //recieving login id
      recv(client_socket,&recv_login_id,sizeof(recv_login_id),0);
      int id=atoi(recv_login_id);
      printf("%d\n",id);

      //sending password prompt
      send(client_socket,password_prompt,strlen(password_prompt),0);

      //recieving password
      recv(client_socket,&recv_password,sizeof(recv_password),0);
      printf("%s\n",recv_password);
      
      //sending valid value to check if user is found or not
      int valid = login_faculty(client_socket,id,recv_password);
      send(client_socket,&valid,sizeof(valid),0);

      if(valid==1)
      {
        char result[]="login successfull....welcome faculty\n";
        send(client_socket,result,strlen(result),0);

        //if login is successfull send faculty menu
        char menu_faculty[] = "Choose from the following options\n" 
                                "1) View offering Course \n"
                                "2) Add course \n"
                                "3) Remove Course from catalog \n"
                                "4) Upadte Course \n"
                                "5) Change Password \n"
                                "6) Logout and exit \n";
        send(client_socket,menu_faculty,strlen(menu_faculty), 0);
        while(1)
        {
            //if choice is 1 send admin menu
            char faculty_choice;
            recv(client_socket, &faculty_choice,sizeof(faculty_choice), 0);
            //call to respective c functions
            if(faculty_choice=='6') break;
            if(faculty_choice=='1')
            {
                view_course(client_socket,id);
            }
            if(faculty_choice=='2')
            {
                add_course(client_socket,id);
            }
            if(faculty_choice=='3')
            {
            
                char delete_prompt[]="select course id you want to delete:";
                send(client_socket,delete_prompt,strlen(delete_prompt),0);

                //recieving course id to delete
                int c_id=0;
                recv(client_socket,&c_id,sizeof(c_id),0);
                remove_course(client_socket,c_id);
            }
            if(faculty_choice=='4')
            {
                modify_course(client_socket);
            }
            if(faculty_choice=='5')
            {
                char old_password[]="enter password:";
                send(client_socket,old_password,strlen(old_password),0);
                
                //recieving password of user
                char password[20];
                recv(client_socket,&password,sizeof(password),0);
                
                change_password(client_socket,id,password);
            }
    
        }
      }
      else
      {
        char fac_result[]="invalid credentials...try again\n";
        send(client_socket,fac_result,strlen(fac_result),0);
      }
         
    } 
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(4567);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    if (listen(server_socket, 5) == 0) {
        printf("Server listening on port %d...\n", ntohs(server_addr.sin_port));
    } else {
        perror("Error listening");
        exit(1);
    }

    while (1) {
        //connect with the client and store the client information in client_addr
        addr_size = sizeof(client_addr);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);

        if (client_socket < 0) {
            perror("Error accepting client");
            exit(1);
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Error forking");
            exit(1);
        } else if (pid == 0) {
            // Child process
            close(server_socket);
            handle_client(client_socket);
            exit(0);
        } else {
            // Parent process
            close(client_socket);
        }
    }
    return 0;
}