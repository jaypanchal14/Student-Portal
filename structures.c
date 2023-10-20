struct StudentDetail
{
	int id;
	char name[50];
	char password[50];
    int age;
    char email[50];
    char address[50];
    int active;
};

struct FacultyDetail
{
	int id;
	char name[50];
	char password[50];
    char department[50];
    char email[50];
    char address[50];
    char designation[50];
};

struct CourseDetail
{
    int id;
    int faculty_id;
    char name[50];
    char department[50];
    int seat;
    int credit;
    int max_seats;
};

struct course_enrolled
{
	int student_id;
	int course_id;
	char course_name[50];
	int faculty_id;
    int enrolled;	
};
