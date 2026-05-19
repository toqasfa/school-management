#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sysfunc.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

#define MAX_STUDENTS 100
#define MAX_ATTEMPTS 3
#define PASSWORD_FILE "manager_pass.txt"

Student students[MAX_STUDENTS];
int student_count = 0;

// ========== Helper function to clear input buffer ==========
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ========== Password Functions ==========

bool login_system(void) {
    char entered_password[50];
    char saved_password[50] = {0};
    FILE* fp = fopen(PASSWORD_FILE, "r");

    // If password file doesn't exist, create with default password
    if (fp == NULL) {
        fp = fopen(PASSWORD_FILE, "w");
        if (fp != NULL) {
            fprintf(fp, "admin123");
            fclose(fp);
        }
        strcpy(saved_password, "admin123");
    } else {
        fgets(saved_password, 50, fp);
        saved_password[strcspn(saved_password, "\n")] = 0;
        fclose(fp);
    }

    int attempts = 0;

    while (attempts < MAX_ATTEMPTS) {
        printf("\n");
        printf("=========================================\n");
        printf("|       MANAGER LOGIN REQUIRED          |\n");
        printf("=========================================\n");
        printf("Enter Manager Password: ");

        scanf("%s", entered_password);
        clear_input_buffer();

        if (strcmp(entered_password, saved_password) == 0) {
            printf("\n✓ Login successful! Welcome Manager.\n");
            system(CLEAR_SCREEN);
            return true;
        }

        attempts++;
        printf("\n✗ Incorrect password! %d attempt(s) remaining.\n", MAX_ATTEMPTS - attempts);

        if (attempts >= MAX_ATTEMPTS) {
            printf("\n✗ Too many failed attempts! System locked.\n");
            return false;
        }
    }

    return false;
}

void change_password(void) {
    char current_password[50];
    char saved_password[50] = {0};
    char new_password[50];
    char confirm_password[50];

    // Read current saved password from file
    FILE* fp = fopen(PASSWORD_FILE, "r");
    if (fp == NULL) {
        printf("Error: Password file not found! Creating default password.\n");
        fp = fopen(PASSWORD_FILE, "w");
        if (fp != NULL) {
            fprintf(fp, "admin123");
            fclose(fp);
        }
        strcpy(saved_password, "admin123");
    } else {
        fgets(saved_password, 50, fp);
        saved_password[strcspn(saved_password, "\n")] = 0;
        fclose(fp);
    }

    printf("\n===== CHANGE MANAGER PASSWORD =====\n");
    printf("Enter current password: ");
    scanf("%s", current_password);
    clear_input_buffer();

    // Verify current password
    if (strcmp(current_password, saved_password) != 0) {
        printf("✗ Incorrect current password!\n");
        return;
    }

    printf("Enter new password: ");
    scanf("%s", new_password);
    clear_input_buffer();

    printf("Confirm new password: ");
    scanf("%s", confirm_password);
    clear_input_buffer();

    // Check if passwords match
    if (strcmp(new_password, confirm_password) != 0) {
        printf("✗ Passwords do not match!\n");
        return;
    }

    // Check minimum length
    if (strlen(new_password) < 4) {
        printf("✗ Password must be at least 4 characters!\n");
        return;
    }

    // Save new password to file (overwrite)
    fp = fopen(PASSWORD_FILE, "w");
    if (fp != NULL) {
        fprintf(fp, "%s", new_password);
        fclose(fp);
        printf("\n✓ Password changed successfully!\n");
        printf("  New password: %s\n", new_password);
        printf("  Please remember this password for next login.\n");
    } else {
        printf("✗ Error: Could not save new password!\n");
    }
}

// ========== Helper Functions ==========

int Get_Position_using_ID(int ID) {
    for (int i = 0; i < student_count; i++) {
        if (students[i].ID == ID)
            return i;
    }
    return -1;
}

int GetPosition() {
    int ID;
    printf("Enter Student ID: ");
    scanf("%d", &ID);
    clear_input_buffer();
    return Get_Position_using_ID(ID);
}

void PrintStudentInfo(int index) {
    printf("\n");
    printf("==========================================\n");
    printf("|       STUDENT INFORMATION              |\n");
    printf("==========================================\n");
    printf("| Name           : %-30s |\n", students[index].Name);
    printf("| ID             : %-30d |\n", students[index].ID);
    printf("| Date of Birth  : %02d/%02d/%-26d |\n",
           students[index].BirthDate.Day,
           students[index].BirthDate.Month,
           students[index].BirthDate.Year);
    printf("| Address        : %-30s |\n", students[index].Address);
    printf("| Location (City): %-30s |\n", students[index].Location);
    printf("| Phone Number   : %-30d |\n", students[index].PhoneNumber);
    printf("| Grade Year     : %-30d |\n", students[index].GradeYear);
    printf("| Scores         : English=%d, Arabic=%d, Math=%-15d |\n",
           students[index].Subjects[0],
           students[index].Subjects[1],
           students[index].Subjects[2]);
    printf("==========================================\n");
}

void PrintSpecificStudentInfo() {
    int pos = GetPosition();
    if (pos != -1)
        PrintStudentInfo(pos);
    else
        printf("Student with ID not found!\n");
}

void PrintStudentList() {
    if (student_count == 0) {
        printf("\nNo students in the system.\n");
        return;
    }

    printf("\n");
    printf("+------------------+------------+----------+--------------------------+------------------+------------+------------+\n");
    printf("| %-16s | %-10s | %-8s | %-24s | %-16s | %-10s | %-10s |\n",
           "Name", "Birth Date", "ID", "Address", "Location", "Phone", "Grade Year");
    printf("+------------------+------------+----------+--------------------------+------------------+------------+------------+\n");

    for (int i = 0; i < student_count; i++) {
        printf("| %-16s | %02d/%02d/%-4d | %-8d | %-24s | %-16s | %-10d | %-10d |\n",
               students[i].Name,
               students[i].BirthDate.Day,
               students[i].BirthDate.Month,
               students[i].BirthDate.Year,
               students[i].ID,
               students[i].Address,
               students[i].Location,
               students[i].PhoneNumber,
               students[i].GradeYear);
    }
    printf("+------------------+------------+----------+--------------------------+------------------+------------+------------+\n");
}

void SortAccordingToName() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (strcmp(students[i].Name, students[j].Name) > 0) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void SortAccordingToScore() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].Subjects[0] < students[j].Subjects[0]) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void SortAccordingToID() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].ID > students[j].ID) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void SortAccordingToGradeYear() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].GradeYear > students[j].GradeYear) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

// ========== Core Functions ==========

void New_Student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    Student new_student;

    printf("\n===== ADD NEW STUDENT =====\n\n");

    printf("Enter Name: ");
    fgets(new_student.Name, sizeof(new_student.Name), stdin);
    new_student.Name[strcspn(new_student.Name, "\n")] = 0;

    printf("Enter Day of Birth: ");
    scanf("%d", &new_student.BirthDate.Day);
    clear_input_buffer();

    printf("Enter Month of Birth: ");
    scanf("%d", &new_student.BirthDate.Month);
    clear_input_buffer();

    printf("Enter Year of Birth: ");
    scanf("%d", &new_student.BirthDate.Year);
    clear_input_buffer();

    printf("Enter Student ID: ");
    scanf("%d", &new_student.ID);
    clear_input_buffer();

    if (Get_Position_using_ID(new_student.ID) != -1) {
        printf("Student with this ID already exists!\n");
        return;
    }

    printf("Enter Address (Street/House number): ");
    fgets(new_student.Address, sizeof(new_student.Address), stdin);
    new_student.Address[strcspn(new_student.Address, "\n")] = 0;

    printf("Enter Location (City/Area): ");
    fgets(new_student.Location, sizeof(new_student.Location), stdin);
    new_student.Location[strcspn(new_student.Location, "\n")] = 0;

    printf("Enter Phone Number: ");
    scanf("%d", &new_student.PhoneNumber);
    clear_input_buffer();

    printf("Enter Grade Year (e.g., 1,2,3,4 or graduation year): ");
    scanf("%d", &new_student.GradeYear);
    clear_input_buffer();

    new_student.Subjects[0] = 0;
    new_student.Subjects[1] = 0;
    new_student.Subjects[2] = 0;

    students[student_count] = new_student;
    student_count++;

    printf("\n✓ Student added successfully!\n");
}

void Delete_Student() {
    int pos = GetPosition();
    if (pos == -1) {
        printf("Student not found!\n");
        return;
    }

    printf("Are you sure you want to delete %s? (y/n): ", students[pos].Name);
    char confirm;
    scanf(" %c", &confirm);
    clear_input_buffer();

    if (confirm != 'y' && confirm != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }

    for (int i = pos; i < student_count - 1; i++) {
        students[i] = students[i + 1];
    }
    student_count--;
    printf("✓ Student deleted successfully!\n");
}

void Student_list() {
    int sort_choice;
    printf("\nSort by:\n");
    printf("1. Name (Alphabetical)\n");
    printf("2. ID\n");
    printf("3. Grade Year\n");
    printf("Enter choice: ");
    scanf("%d", &sort_choice);
    clear_input_buffer();

    switch(sort_choice) {
        case 1:
            SortAccordingToName();
            break;
        case 2:
            SortAccordingToID();
            break;
        case 3:
            SortAccordingToGradeYear();
            break;
        default:
            SortAccordingToName();
    }

    PrintStudentList();
}

void Student_Edit() {
    int pos = GetPosition();
    if (pos == -1) {
        printf("Student not found!\n");
        return;
    }

    char temp[100];
    int temp_int;

    printf("\n===== EDIT STUDENT (Press Enter to keep current value) =====\n\n");

    printf("Current Name: %s\n", students[pos].Name);
    printf("New Name (press Enter to skip): ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strcpy(students[pos].Name, temp);
    }

    printf("Current Date of Birth: %d/%d/%d\n",
           students[pos].BirthDate.Day,
           students[pos].BirthDate.Month,
           students[pos].BirthDate.Year);

    printf("New Day (0 to skip): ");
    scanf("%d", &temp_int);
    clear_input_buffer();
    if (temp_int > 0) students[pos].BirthDate.Day = temp_int;

    printf("New Month (0 to skip): ");
    scanf("%d", &temp_int);
    clear_input_buffer();
    if (temp_int > 0) students[pos].BirthDate.Month = temp_int;

    printf("New Year (0 to skip): ");
    scanf("%d", &temp_int);
    clear_input_buffer();
    if (temp_int > 0) students[pos].BirthDate.Year = temp_int;

    printf("Current Address: %s\n", students[pos].Address);
    printf("New Address (press Enter to skip): ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strcpy(students[pos].Address, temp);
    }

    printf("Current Location: %s\n", students[pos].Location);
    printf("New Location (press Enter to skip): ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = 0;
    if (strlen(temp) > 0) {
        strcpy(students[pos].Location, temp);
    }

    printf("Current Phone: %d\n", students[pos].PhoneNumber);
    printf("New Phone (0 to skip): ");
    scanf("%d", &temp_int);
    clear_input_buffer();
    if (temp_int > 0) students[pos].PhoneNumber = temp_int;

    printf("Current Grade Year: %d\n", students[pos].GradeYear);
    printf("New Grade Year (0 to skip): ");
    scanf("%d", &temp_int);
    clear_input_buffer();
    if (temp_int > 0) students[pos].GradeYear = temp_int;

    printf("✓ Student information updated successfully!\n");
}

void Rank_Student() {
    if (student_count == 0) {
        printf("\nNo students to rank.\n");
        return;
    }

    SortAccordingToScore();

    printf("\n========== STUDENT RANKING (by English Score) ==========\n");
    printf("Rank | %-20s | %-15s | %-10s\n", "Name", "English Score", "Grade Year");
    printf("-----+----------------------+-----------------+------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%-4d | %-20s | %-15d | %-10d\n",
               i + 1,
               students[i].Name,
               students[i].Subjects[0],
               students[i].GradeYear);
    }
}

void Student_Score() {
    printf("\n===== UPDATE ALL STUDENT SCORES =====\n");
    for (int i = 0; i < student_count; i++) {
        printf("\nUpdating scores for: %s (ID: %d)\n",
               students[i].Name, students[i].ID);

        printf("  English Score (0-100): ");
        scanf("%d", &students[i].Subjects[0]);
        clear_input_buffer();

        printf("  Arabic Score (0-100): ");
        scanf("%d", &students[i].Subjects[1]);
        clear_input_buffer();

        printf("  Math Score (0-100): ");
        scanf("%d", &students[i].Subjects[2]);
        clear_input_buffer();
    }
    printf("\n✓ All scores updated successfully!\n");
}

void Main_Menu() {
    printf("\n");
    printf("========================================================\n");
    printf("|              STUDENT MANAGEMENT SYSTEM               |\n");
    printf("========================================================\n");
    printf("| 1. Add New Student                                   |\n");
    printf("| 2. Delete Student                                    |\n");
    printf("| 3. Show Student List (with sorting options)          |\n");
    printf("| 4. Edit Student Information                          |\n");
    printf("| 5. Rank Students (by English Score)                  |\n");
    printf("| 6. Update All Students' Scores                       |\n");
    printf("| 7. Search Student by ID                              |\n");
    printf("| 8. Show All Students (as is)                         |\n");
    printf("| 9. Change Manager Password                           |\n");
    printf("| 0. Exit                                              |\n");
    printf("========================================================\n");
    printf("Enter your choice: ");
}

void StartProgram(void) {
    if (!login_system()) {
        printf("\nAccess Denied. Exiting program.\n");
        return;
    }

    int choice;

    do {
        Main_Menu();
        scanf("%d", &choice);
        clear_input_buffer();

        switch(choice) {
            case 1:
                New_Student();
                break;
            case 2:
                Delete_Student();
                break;
            case 3:
                Student_list();
                break;
            case 4:
                Student_Edit();
                break;
            case 5:
                Rank_Student();
                break;
            case 6:
                Student_Score();
                break;
            case 7:
                PrintSpecificStudentInfo();
                break;
            case 8:
                PrintStudentList();
                break;
            case 9:
                change_password();
                break;
            case 0:
                printf("\nExiting program. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while(choice != 0);
}

int main() {
    StartProgram();
    return 0;
}
