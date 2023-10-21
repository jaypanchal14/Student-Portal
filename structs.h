#include<stdbool.h>

struct Admin{
        char username[50];
        char password[50];
};

struct Course{
        int code;
        int faculty_id;
        char name[256];
        char branch[10];
        bool isActive;
        int intake;
        int current;
};

struct Student{
        char name[256];
        int rollno;
        int courses[6];
        char branch[10];
        char degree[10];
        char username[50];
        char password[50];
        bool isActivated;
        bool isBlocked;
};

struct Faculty{
        int faculty_id;
        char name[256];
        char branch[10];
        int courses[10];
        char username[50];
        char password[50];
};

struct Count{
        int students;
        int faculties;
        int courses;
};