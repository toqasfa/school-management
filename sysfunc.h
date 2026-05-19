#ifndef SYSFUNC_H_INCLUDED
#define SYSFUNC_H_INCLUDED

/*student date*/
typedef enum STUDENTSUBJECTS
{
    english = 0,
    arabic = 0,
    math = 0
}StudentSubjects;

#define SubjectsSize sizeof(StudentSubjects)

typedef struct Date
{
    int Day;
    int Month;
    int Year;
}DateOfBirth;

 typedef struct S
 {
     DateOfBirth BirthDate;
     int Subjects[SubjectsSize];
     int PhoneNumber;
     int ID;
     char Address[100];
     char Name[50];
 }Student;

 /*system features*/
 void Main_Menu();  //this function displays the welcome screen and targeted activates.
 void New_Student();  // this function creates a new student account. it asks about details of the student such as name, date of birth, ID, address and phone number.
 void Delete_Student();  //This function is for deleting a student account
 void Student_list();   //This function, you can view the Students information such as name, date of birth, ID, Address and phone number in table from (alphabetically ascending).
 void Student_Edit();  //This function has been used for updating a particular student account.
 void Rank_Student();    //This function can sort all students according to english score.
 void Student_Score();   //this function has been used for updating score of all students.

 void StartProgram(void);
 int Get_Position_using_ID();
 void PrintStudentList();  //This Function Print the whole student list
 void PrintSpecificStudentInfo();  //Print only 1 student info
 void PrintStudentInfo();
 int GetPosition();
 void SortAccordingToName();
 void SortAccordingToScore();
 void SortAccordingToID();

#endif // SYSFUNC_H_INCLUDED
