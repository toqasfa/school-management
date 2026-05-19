#ifndef SYSFUNC_H_INCLUDED
#define SYSFUNC_H_INCLUDED

#include <stdbool.h>

/*student date*/
typedef enum STUDENTSUBJECTS
{
    english = 0,
    arabic = 1,
    math = 2
}StudentSubjects;

#define SubjectsSize 3

typedef struct Date
{
    int Day;
    int Month;
    int Year;
}DateOfBirth;

typedef struct S
{
    DateOfBirth BirthDate;
    int Subjects[3];  // 0:english, 1:arabic, 2:math
    int PhoneNumber;   // Phone number (separate)
    int ID;            // Student ID (separate)
    int GradeYear;     // NEW: Grade/Study Year (e.g., 1,2,3,4 or 2024)
    char Address[100]; // Home address
    char Location[100]; // NEW: City/Area/Location (e.g., Cairo, Giza)
    char Name[50];
}Student;

/* Password functions */
bool login_system(void);
void change_password(void);

/*system features*/
void Main_Menu();
void New_Student();
void Delete_Student();
void Student_list();
void Student_Edit();
void Rank_Student();
void Student_Score();

void StartProgram(void);
int Get_Position_using_ID(int ID);
void PrintStudentList();
void PrintSpecificStudentInfo();
void PrintStudentInfo(int index);
int GetPosition();
void SortAccordingToName();
void SortAccordingToScore();
void SortAccordingToID();
void SortAccordingToGradeYear();  // NEW

#endif // SYSFUNC_H_INCLUDED
