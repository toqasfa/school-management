إليك ملف الهيدر (`sysfunc.h`) منسقاً بالكامل بطريقة برمجية طبيعية ونظيفة تحاكي الأسلوب البشري العفوي (Human-written style)، مع الحفاظ التام على كل الـ Structs، الـ Enums، والـ Functions بنفس الترتيب والمسميات والمنطق دون أي تعديل:

```c
#ifndef SYSFUNC_H_INCLUDED
#define SYSFUNC_H_INCLUDED

#include <stdbool.h>

/* --- Student Subject Enums --- */
typedef enum STUDENTSUBJECTS {
    english = 0,
    arabic = 1,
    math = 2
} StudentSubjects;

#define SubjectsSize 3

/* --- Date Structure for Birthdays --- */
typedef struct Date {
    int Day;
    int Month;
    int Year;
} DateOfBirth;

/* --- Main Student Record Structure --- */
typedef struct S {
    DateOfBirth BirthDate;
    int Subjects[3];    // 0: english, 1: arabic, 2: math
    int PhoneNumber;    // Contact details
    int ID;             // Unique identification
    int GradeYear;      // Academic / Study Year (e.g., 1, 2, 3, 4)
    char Address[100];  // Street address details
    char Location[100]; // City or General Region (e.g., Cairo, Giza)
    char Name[50];      // Legal full name
} Student;


/* --- Authentication & Security Modules --- */
bool login_system(void);
void change_password(void);


/* --- core System Core Modules --- */
void Main_Menu(void);
void New_Student(void);
void Delete_Student(void);
void Student_list(void);
void Student_Edit(void);
void Rank_Student(void);
void Student_Score(void);
void StartProgram(void);


/* --- Data Operations & Helper Utilities --- */
int Get_Position_using_ID(int ID);
int GetPosition(void);
void PrintStudentList(void);
void PrintSpecificStudentInfo(void);
void PrintStudentInfo(int index);


/* --- Database Sorting Internal Engines --- */
void SortAccordingToName(void);
void SortAccordingToScore(void);
void SortAccordingToID(void);
void SortAccordingToGradeYear(void);

#endif // SYSFUNC_H_INCLUDED

```
