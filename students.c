#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STUDENTS 1 // represent the MAX number of students
#define MAX_WORD_LENGTH 31 // represent the MAX number a word length

//--------------------Structure declaration---------------------
typedef struct student student;
typedef struct Course Course;

struct student {
  int ID;
  char name[MAX_WORD_LENGTH];
  float score;
  char grade;
  char academic_advisor_name[MAX_WORD_LENGTH];
};

struct Course {
  int total;
  student std[MAX_STUDENTS];
};

//----------------  PROTOTYPE ---------------------------------

void initializer(Course *gc);

int findStudent(student s[], int id, int *index);

char calculat_grade(float s);

int find_Empty_index(student s[]);

int addStudent(Course *gc);

void Add_Student_Score(Course *gc, int id);

int Remove_student(Course *gc);

void Print_Student_Info(Course *gc, int id); // search by ID un etudiant et print ses info

void Print_All(Course *gc); // tout

void Print_All_Grade(Course *gc, char g); 

int Number_Of_Students_Advisor(Course *gc, char *name);

//------------------- MAIN FUCNTION ----------------------------

int main(int argc, char *argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (strcmp(argv[i], "non") == 0) {
      exit(-1);
    }
    int choice;
    int unused __attribute__((unused));
    Course *gc = malloc(sizeof(*gc));
    if (gc == NULL) {
      fprintf(stderr, "*** Error: Not enough memory.\n");
      return EXIT_FAILURE;
    }
    initializer(gc);
restart:
    puts("---------------------------------------------------	");
    puts("------------------- menu --------------------------");
    puts("1  .	Add a student");
    puts("2  .	Remove a student");
    puts("3  .	Find and print the information of a student");
    puts("4  .	Add student score");
    puts("5  .	List all students");
    puts("6  .	List students for a given grade");
    puts("7  .	Total number of students for a given academic advisor");
    puts("8  .	Total number of students");
    puts("-1 .	To STOP ");
    puts("----------------------------------------------------	");
    printf("What would you like to do: ");
    unused = scanf("%d", &choice);
    if (choice == 1) {
      if (addStudent(gc) == false) {
        printf("An errror was accord ! \n");
        puts("----------------------------------------------------	");
        goto restart;
      }
      printf("student added successfully \n");
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == 2) {
      if (Remove_student(gc) == 0) {
        printf("the student is not registerd in this course \n");
        puts("----------------------------------------------------	");
        goto restart;
      }
      printf("student removed successfully \n");
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == 3) {
      int ID;
      printf("enter id number : ");
      unused = scanf("%d", &ID);
      Print_Student_Info(gc, ID);
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == 4) {
      int ID;
      printf("enter id number : ");
      unused = scanf("%d", &ID);
      Add_Student_Score(gc, ID);
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == 5) {
      Print_All(gc);
      goto restart;
    } else if (choice == 6) {
      char lett;
      printf("enter the grade : ");
      unused = scanf(" %c", &lett);
      Print_All_Grade(gc, lett);
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == 7) {
      printf("enter academic advisor name :");
      char nm[MAX_WORD_LENGTH];
      unused = scanf("%s", nm);
      printf("the advisor have %d student\n",
          Number_Of_Students_Advisor(gc, nm));
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == 8) {
      printf("Total number of students : %d\n", gc->total);
      puts("----------------------------------------------------	");
      goto restart;
    } else if (choice == -1) {
      printf("\n\n\t\tHave a great day !! \n");
      puts("----------------------------------------------------	");
      free(gc);
      exit(EXIT_SUCCESS);
    } else {
      puts("Wrong choise");
      puts("----------------------------------------------------	");
      goto restart;
    }
  }
  return EXIT_SUCCESS;
} //end main

//-----------------function definitions ------------------------

void initializer(Course *gc) {
  gc->total = 0;
  gc->std->ID = 0;
  gc->std->name[0] = '\0';
  gc->std->score = 0.0;
  gc->std->grade = ' ';
  gc->std->academic_advisor_name[0] = '\0';
  puts("---------------------------------------------------	");
  puts("------------------initializer done-----------------");
}

//--------------------------------------

int findStudent(student s[], int id, int *index) {
  for (int i = 0; i < MAX_STUDENTS; ++i) {
    if (s[i].ID == id) {
      *index = i;
      return 1;
    }
  }
  return 0;
}

//--------------------------------------

char calculat_grade(float s) {
  if (s >= 90 && s <= 100) {
    return 'A';
  } else if (s >= 80 && s <= 89) {
    return 'B';
  } else if (s >= 70 && s <= 79) {
    return 'C';
  } else if (s >= 60 && s <= 69) {
    return 'D';
  } else {
    return 'F';
  }
}

//--------------------------------------

int find_Empty_index(student s[]) {
  for (int i = 0; i < MAX_STUDENTS; ++i) {
    if (s[i].ID == 0) {
      return i;
    }
  }
  return 26;
}

//--------------------------------------

int addStudent(Course *gc) {
  FILE *src = fopen("/home/administrateur/Desktop/one.txt", "a");
  if (src == NULL) {
    printf("Error\n");
  }
  int unused __attribute__((unused));
  int ID;
  int num;
  int var;
  num = find_Empty_index(gc->std);
  if (num == 26) {
    printf("Warrning : no more room for a new student ! \n");
    return false;
  }
  printf("enter student ID : ");
  unused = scanf("%d", &ID);
  var = findStudent(gc->std, ID, &num);
  if (var == 0) {
    gc->std[num].ID = ID;
    fprintf(src, "Student's ID : %d\n", ID);
    printf("enter student name : ");
    unused = scanf("%s", gc->std[num].name);
    fprintf(src, "Student's name : %s\n", gc->std[num].name);
    printf("enter student academic advisor name : ");
    unused = scanf("%s", gc->std[num].academic_advisor_name);
    fprintf(src, "Student's academic advisor name :: %s\n",
        gc->std[num].academic_advisor_name);
    gc->total += 1;
    return true;
  }
  return false;
}

//--------------------------------------

void Add_Student_Score(Course *gc, int id) {
  int unused __attribute__((unused));
  int i;
  int fnd = findStudent(gc->std, id, &i);
  if (fnd == 1) {
    printf("enter score : ");
    float sco;
    unused = scanf("%f", &sco);
    gc->std[i].score = sco;
    gc->std[i].grade = calculat_grade(sco);
    printf("score added successfully \n");
  } else {
    printf("ID %d is not exist !\n", id);
  }
}

//--------------------------------------

int Remove_student(Course *gc) {
  printf("enter student ID : ");
  int d;
  int ind;
  int unused __attribute__((unused));
  unused = scanf("%d", &d);
  printf("\n");
  if (findStudent(gc->std, d, &ind) == 0) {
    return false;
  }
  gc->total -= 1;
  gc->std[ind].ID = 0;
  gc->std[ind].name[0] = '\0';
  gc->std[ind].score = 0.0;
  gc->std[ind].grade = ' ';
  gc->std[ind].academic_advisor_name[0] = '\0';
  return true;
}

//--------------------------------------

void Print_Student_Info(Course *gc, int id) {
  int ind;
  if (findStudent(gc->std, id, &ind) == 0) {
    return;
  }
  printf("\n");
  printf("student ID : %d\n", gc->std[ind].ID);
  printf("student name : %s\n", gc->std[ind].name);
  printf("student score : %0.1f\n", gc->std[ind].score);
  printf("student Grade : %c\n", gc->std[ind].grade);
  printf("academic advisor name : %s\n", gc->std[ind].academic_advisor_name);
  printf("----------------------------------------------------	\n");
}

//--------------------------------------

void Print_All(Course *gc) {
  if (gc->total == 0) {
    return;
  } else {
    for (int i = 0; i < gc->total; ++i) {
      printf("\n");
      printf("student ID : %d\n", gc->std[i].ID);
      printf("student name : %s\n", gc->std[i].name);
      printf("student score : %0.1f\n", gc->std[i].score);
      printf("student Grade : %c\n", gc->std[i].grade);
      printf("academic advisor name : %s\n", gc->std[i].academic_advisor_name);
      printf("----------------------------------------------------	\n");
    }
  }
}

//--------------------------------------

void Print_All_Grade(Course *gc, char g) {
  if (gc->total == 0) {
    printf("Sorry no student is registerd yet ! \n");
    return;
  } else {
    int counter = 1;
    for (int i = 0; i < gc->total; ++i) {
      if (gc->std[i].grade == g) {
        printf("%d - %d\n", counter, gc->std[i].ID);
        ++counter;
      }
    }
  }
  printf("----------------------------------------------------	\n");
}

//--------------------------------------

int Number_Of_Students_Advisor(Course *gc, char *name) {
  if (gc->total == 0) {
    return 0;
  } else {
    int cn = 0;
    for (int i = 0; i < gc->total; ++i) {
      if (strcmp(name, gc->std[i].academic_advisor_name) == 0) {
        ++cn;
      }
    }
    return cn;
  }
}
