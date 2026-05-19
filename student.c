#include <stdio.h>
#include <string.h>
#include "student.h"
//===========================================//
void add_student(Student* students, int* num_students) {
    printf("Enter student details:\n");
    printf("Name: ");
    scanf("%s", students[*num_students].name);
    printf("Date of birth (D/M/Y): ");
    scanf("%s", students[*num_students].dob);
    printf("ID: ");
    scanf("%d", &students[*num_students].id);
    printf("Address: ");
    scanf("%s", students[*num_students].address);
    printf("Phone number: ");
    scanf("%s", students[*num_students].phone);

    (*num_students)++;}
//=============================================//
void delete_student(Student* students, int* num_students) {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);
    for ( int i = 0; i < *num_students; i++) {
        if (students[i].id == id) {
            // shift all the elements after i one position to the left
            for (int j = i; j < *num_students - 1; j++) {
                students[j] = students[j+1];
            }
            (*num_students)--;
            printf("Student with ID %d deleted\n", id);
            return;
        }}
    printf("Student with ID %d not found\n", id);}

//===============================================//
void print_students(Student* students, int num_students) {
    // sort students by name
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = i+1; j < num_students; j++) {
            // compare between  names to alphabetical order
            if (strcmp(students[i].name, students[j].name) > 0) {
               Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }}}

    // print students in table format
    printf("+-----------------+-----------------+---------+------------------------------+---------------+\n");
    printf("| %-15s | %-15s | %-7s | %-28s | %-13s |\n", "Name", "Date of Birth", "ID", "Address", "Phone");
    printf("+-----------------+-----------------+---------+------------------------------+---------------+\n");

for (int i = 0; i < num_students; i++) {

         printf("+-----------------+-----------------+---------+------------------------------+---------------+\n");
         printf("| %-15s | %-15s | %-7d | %-28s | %-13s |\n", students[i].name, students[i].dob, students[i].id, students[i].address, students[i].phone);
    }
         printf("+-----------------+-----------------+---------+------------------------------+---------------+\n");}

//======================================================//
void edit_student(Student* students, int num_students) {
    int id;
    printf("Enter student ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            printf("Enter new student details:\n");
            printf("Name: ");
            scanf("%s", students[i].name);
            printf("Date of birth (DD/MM/YYYY): ");
            scanf("%s", students[i].dob);
            printf("ID: ");
            scanf("%d", &students[i].id);
            printf("Address: ");
            scanf("%s", students[i].address);
            printf("Phone number: ");
            scanf("%s", students[i].phone);
            printf("Student details updated\n");
            return;
        }
    }
    printf("Student with ID %d not found\n", id);}

//===============================================//
void rank_students(Student* students, int num_students) {
    // sort students by cs score
    for (int i = 0; i < num_students - 1; i++) {
        for (int j = i + 1; j < num_students; j++) {
        //compare between scors of stu then choose the hightest
            if (students[i].cs_score < students[j].cs_score) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
                }}}

    // print students in table format
    printf("%-20s | %-15s | %-10s | %-30s | %-15s | %-15s\n", "Name", "Date of Birth", "ID", "Address", "Phone", "CS Score");
    for (int i = 0; i < num_students; i++){
printf("%-20s | %-15s | %-10d | %-30s | %-15s | %-15d\n", students[i].name, students[i].dob, students[i].id, students[i].address, students[i].phone, students[i].cs_score);
    }
}
//====================================================//
void update_student_scores(Student* students, int num_students) {
    for (int i = 0; i < num_students; i++) {
            // just call name to edit score
        printf("Enter CS score for %s: ", students[i].name);
        scanf("%d", &students[i].cs_score);
    }
}
//===================================================//

// function to search for a student by their ID
void search_student_by_id(Student* students, int num_students) {
    int id;
    printf("Enter student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < num_students; i++) {
        if (students[i].id == id) {
            printf("Student found:\n");
            printf("Name: %s\n", students[i].name);
            printf("Date of birth: %s\n", students[i].dob);
            printf("ID: %d\n", students[i].id);
            printf("Address: %s\n", students[i].address);
            printf("Phone number: %s\n", students[i].phone);
            printf("CS score: %d\n", students[i].cs_score);
            return;
        }
    }
    printf("Student with ID %d not found\n", id);

}
