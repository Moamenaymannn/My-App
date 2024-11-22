//############ Libarary #############

#include <stdio.h>
#include <ctype.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif
#define CLEAR_SCREEN "clear"


//#############  ANSI color codes ########

#define RESET_COLOR "\033[0m"
#define RED_COLOR "\033[31m"
#define GREEN_COLOR "\033[32m"
#define YELLOW_COLOR "\033[33m"
#define BLUE_COLOR "\033[34m"

//############# movement ##################

#define MAX 5
#define MIN 0

//############## Keys #########################

#define UP 65
#define ENTER 10
#define DOWN 66
#define SIZE 5

//############ gotoxy ################

      void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);
}

//########### CleanBuffer ###############

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//########### getch ###############

int getch(void) {
    struct termios oldt, newt;
    int ch;

    // Get current terminal attributes
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    // Disable canonical mode and echoing
    newt.c_lflag &= ~(ICANON | ECHO);

    // Set the new terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();

    // Restore the old terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}



// ############Function to display the menu ###########

void DisplayMenu(int position, int row, int col) {
    printf("\033[H\033[J"); // Clear screen



     gotoxy(col / 2 - 13, 2);
    printf(" %s=========   HOME  =========%s \n" ,YELLOW_COLOR ,  RESET_COLOR);


    // "New" option
    gotoxy(col / 2 - 13, 4);
    printf("----------------------");
    gotoxy(col / 2 - 13, 5);
    if (position == 0) {
        printf(" %s-> NEW%s           ", YELLOW_COLOR, RESET_COLOR);
    } else {
        printf(" %sNEW%s              ", RESET_COLOR, RESET_COLOR);
    }
    gotoxy(col / 2 - 13, 6);
    printf("----------------------");

    // "Display" option
    gotoxy(col / 2 - 13, 7);
    printf("----------------------");
    gotoxy(col / 2 - 13, 8);
    if (position == 1) {
        printf(" %s-> DISPLAY%s        ", YELLOW_COLOR, RESET_COLOR);
    } else {
        printf(" %sDISPLAY%s           ", RESET_COLOR, RESET_COLOR);
    }
    gotoxy(col / 2 - 13, 9);
    printf("----------------------");

    // "Exit" option
    gotoxy(col / 2 - 13, 10);
    printf("----------------------");
    gotoxy(col / 2 - 13, 11);
    if (position == 2) {
        printf(" %s-> MODIFY%s          ", YELLOW_COLOR, RESET_COLOR);
    } else {
        printf(" %sMODIFY%s             ", RESET_COLOR, RESET_COLOR);
    }
    gotoxy(col / 2 - 13, 12);
    printf("----------------------");


      gotoxy(col / 2 - 13, 13);
    printf("----------------------");
    gotoxy(col / 2 - 13, 14);
    if (position == 3) {
        printf(" %s-> SEARCH%s          ", YELLOW_COLOR, RESET_COLOR);
    } else {
        printf(" %sSEARCH%s             ", RESET_COLOR, RESET_COLOR);
    }
    gotoxy(col / 2 - 13, 15);
    printf("----------------------");


      gotoxy(col / 2 - 13, 16);
    printf("----------------------");
    gotoxy(col / 2 - 13, 17);
    if (position == 4) {
        printf(" %s-> DELETE%s          ", YELLOW_COLOR, RESET_COLOR);
    } else {
        printf(" %sDELETE%s             ", RESET_COLOR, RESET_COLOR);
    }
    gotoxy(col / 2 - 13, 18);
    printf("----------------------");


        gotoxy(col / 2 - 13, 19);
    printf("----------------------");
    gotoxy(col / 2 - 13, 20);
    if (position == 5) {
        printf(" %s-> EXIT%s          ", YELLOW_COLOR, RESET_COLOR);
    } else {
        printf(" %sEXIT%s             ", RESET_COLOR, RESET_COLOR);
    }
    gotoxy(col / 2 - 13, 21);
    printf("----------------------");






}

//####### Function to validate the name (place it here) #######

int validateName(char *name) {
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') {
            return 0; // Invalid name
        }
    }
    return 1; // Valid name
}



void addEmploy();
void searchEmploy();
void displayEmploy();
void deleteEmploy();


struct Employ{
  int ID;
  int SALARY;
  char NAME [50];
  int roll_no;
  };


int main()
{
   int ch ;
   int col = 80;
   int position = 0;
   int row =24;

   while(1){
   DisplayMenu(position, row, col);

    ch = getch();
   if( ch == 27  ){
   ch = getch();
   if(ch == 91){
    ch = getch();
    if(ch == UP && position != MIN){
       position--;
    } else if ( ch == DOWN && position != MAX   ){
        position++ ;
    }
   }
   } else if( ch == ENTER && position == 0 ){
     system("clear");
      addEmploy();
  }else if( ch == ENTER && position == 1 ){
     system("clear");
      displayEmploy();
      printf("\t\t\t press any key to Exit\n");
      getch();
  }else if( ch == ENTER && position == 2 ){
     system("clear");
      modifyEmploy();
      printf("\t\t\t press any key to Exit\n");
      getch();
  }else if( ch == ENTER && position == 3 ){
     system("clear");
       searchEmploy();
      printf("\t\t\t press any key to Exit\n");
      getch();
  }else if( ch == ENTER && position == 4 ){
     system("clear");
       deleteEmploy();
      printf("\t\t\t press any key to Exit\n");
      getch();
  }

   else if(ch == ENTER && position == 5 ){
      system("clear");
      printf("Exiting..... GodBye \n ");
      break;
   }

};

return 0;
}

//=============== ADD Employ ======================

void addEmploy() {
    char another;
    FILE *fp;
    struct Employ info, tempInfo;
    int valid, found;

    do {
        system("clear");

        printf("\t\t %s========= ADD Employ HERE ========%s\n\n\n", YELLOW_COLOR, RESET_COLOR);

         printf("\t\t %s WARNING  Employ Roll will ignore any Character !! %s\n\n\n", RED_COLOR, RESET_COLOR);
        fp = fopen("Employ_info.txt", "a+"); // Open file for both reading and appending

        if (fp == NULL) {
            fprintf(stderr, "  Can't open file\n");
            return;
        }

        // Validate unique Employ ID
        do {
            valid = 1; // Assume valid until proven otherwise
            found = 0;
            printf("\n\t\t\t Enter Employ ID: ");
            scanf("%d", &info.ID);
            clearBuffer(); // Clear buffer to avoid leftover newline characters

            rewind(fp); // Start from the beginning of the file
            while (fread(&tempInfo, sizeof(struct Employ), 1, fp)) {
                if (tempInfo.ID == info.ID) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("\t\t\t%s Error: Employ ID must be unique. Try again.%s\n", RED_COLOR, RESET_COLOR);
                valid = 0;
            }
        } while (!valid);

        // Validate unique Roll No
        do {
            valid = 1; // Assume valid until proven otherwise
            found = 0;
            printf("\n\t\t\t Enter Employ Roll No: ");
            scanf("%d", &info.roll_no);
            clearBuffer(); // Clear buffer to avoid leftover newline characters

            rewind(fp); // Start from the beginning of the file
            while (fread(&tempInfo, sizeof(struct Employ), 1, fp)) {
                if (tempInfo.roll_no == info.roll_no) {
                    found = 1;
                    break;
                }
            }

            if (found) {
                printf("\t\t\t%s Error: Employ Roll No must be unique. Try again.%s\n", RED_COLOR, RESET_COLOR);
                valid = 0;
            }
        } while (!valid);

        // Validate Employ Name
        do {
            valid = 1; // Assume valid until proven otherwise
            printf("\n\t\t\t Enter Employ Name: ");
            fgets(info.NAME, sizeof(info.NAME), stdin);
            info.NAME[strcspn(info.NAME, "\n")] = '\0'; // Remove trailing newline

            for (int i = 0; info.NAME[i] != '\0'; i++) {
                if (!isalpha(info.NAME[i]) && info.NAME[i] != ' ') { // Allow alphabets and spaces
                    valid = 0;
                    break;
                }
            }

            if (!valid) {
                printf("\t\t\t%s Error: Name must contain only letters. Try again.%s\n", RED_COLOR, RESET_COLOR);
            }
        } while (!valid);

        // Validate Salary
        do {
            valid = 1; // Assume valid until proven otherwise
            printf("\n\t\t\t Enter Employ Salary: ");
            if (scanf("%d", &info.SALARY) != 1) {
                valid = 0;
                clearBuffer(); // Clear invalid input
            } else {
                clearBuffer(); // Clear leftover newline character
            }

            if (!valid) {
                printf("\t\t\t%s Error: Salary must be a valid number. Try again.%s\n", RED_COLOR, RESET_COLOR);
            }
        } while (!valid);

        // Write the record to the file
        fwrite(&info, sizeof(struct Employ), 1, fp);
        fclose(fp);

        printf("\t\t\t%s Employ added successfully!%s\n", GREEN_COLOR, RESET_COLOR);

        // Ask if the user wants to add another Employ
        printf("\t\t\t Do you want to add another Employ? (y/n): ");
        scanf(" %c", &another);
        clearBuffer(); // Clear buffer for next input
    } while (another == 'y' || another == 'Y');

    printf("\n\t\t Returning to the main menu. Press any key to continue...");
    getch();
}



//===========  DISPLAY Employ ===============
void displayEmploy(){
 FILE *fp;
 struct Employ info;
 printf("\t\t %s=========     Records Employ  ========%s\n\n\n     " , YELLOW_COLOR ,  RESET_COLOR);
 fp=fopen("Employ_info.txt","a+");
 if( fp == NULL){
    fprintf( stderr   ,"  can't open File \n"  );
    return;
  }

  while(fread(&info,sizeof(struct Employ),1,fp)){
   printf("\n\t\t\t\t Employ Name : %s",info.NAME);
   printf("\n\t\t\t\t Employ ROLL : %d",info.roll_no);
   printf("\n\t\t\t\t Employ ID : %d",info.ID);
   printf("\n\t\t\t\t Employ SALARY : %d",info.SALARY);
   printf("\n\t\t\t%s___________________________%s \n", YELLOW_COLOR   , RESET_COLOR  );

  }
fclose(fp);

printf("\n\t\t Returning to the main menu. Press any key to continue...");
clearBuffer();
getch();
system("clear");

}

//============= searchEmploy =================

void searchEmploy(){
 FILE *fp;
 struct Employ info;
 int roll_no,found=0;
 system("clear");
  printf("\t\t %s=========     Search Employ    ========%s\n\n\n     " , YELLOW_COLOR ,  RESET_COLOR);
  fp=fopen("Employ_info.txt","a+");
  if( fp == NULL){
    fprintf( stderr   ,"  can't open File \n"  );
    return;
  }
  printf("\t\t\t ENTER roll no :");
  scanf("%d",&roll_no);
  clearBuffer();


  while(fread(&info,sizeof(struct Employ),1,fp)){

  if(info.roll_no == roll_no){
   found=1;
   printf("\n\t\t\t\t Employ Name : %s",info.NAME);
   printf("\n\t\t\t\t Employ ROLL : %d",info.roll_no);
   printf("\n\t\t\t\t Employ ID : %d",info.ID);
   printf("\n\t\t\t\t Employ SALARY : %d",info.SALARY);
   printf("\n\t\t\t%s___________________________%s \n", YELLOW_COLOR   , RESET_COLOR  );

  }
  }
  fclose(fp);
  if(!found){
    printf("\n\t\t\tRecord Not Found\n");
  }

printf("\n\t\t Returning to the main menu. Press any key to continue...");
clearBuffer();
getch();

}

//############# deleteEmploy  ################

void deleteEmploy(){

 FILE *fp,*fp1;
 struct Employ info;
 int roll_no,found=0;
 system("clear");
  printf("\t\t %s=========     Delete Employ Record   ========%s\n\n\n     " , YELLOW_COLOR ,  RESET_COLOR);
 fp=fopen("Employ_info.txt","a+");
 fp1=fopen("temp.txt","w");


 if( fp == NULL || fp1 == NULL){
    fprintf( stderr   ,"  can't open File \n"  );
    return;
  }

  printf("\n\t\t\t\t Enter Employ ROLL to delete: ");
    scanf("%d", &roll_no);
    clearBuffer();

  while(fread(&info,sizeof(struct Employ),1,fp)){

  if(info.roll_no == roll_no){
   found=1;
   }else{
     fwrite(&info,sizeof(struct Employ),1,fp1);
   }
}
fclose(fp);
fclose(fp1);
if(found){
 remove("Employ_info.txt");
 rename("temp.txt","Employ_info.txt");
 printf("\n\t\t\t  Record Delete Successfuly \n");
} else {
        remove("temp.txt");
        printf("\n\t\t\t  Record Not Found.\n");
    }

 printf("\n\t\t Press any key to return to the main menu...");

 clearBuffer();
getch();
}


//############# modifyEmploy  ################

void modifyEmploy() {
    FILE *fp, *fp1;
    struct Employ info;
    int found , valid, id;

    printf("\t\t %s=========     Modify Employee Record    ========%s\n\n\n", YELLOW_COLOR, RESET_COLOR);

    fp = fopen("Employ_info.txt", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL || fp1 == NULL) {
        fprintf(stderr, "Cannot open file.\n");
        return;
    }

    printf("\n\t\t\tEnter Employee ID to Modify: ");
    scanf("%d", &id);
     clearBuffer();

    while (fread(&info, sizeof(struct Employ), 1, fp)) {
        if (info.ID == id) {
            found = 1;
            printf("\n\t\t\tCurrent Details:");
            printf("\n\t\t\tName: %s", info.NAME);
            printf("\n\t\t\tRoll No: %d", info.roll_no);
            printf("\n\t\t\tSalary: %d", info.SALARY);

            printf("\n\n\t\t\tEnter New Details:\n");

            // Get updated name
            do {

                printf("\n\t\t\tNew Name (no special characters or numbers): ");
                scanf("%s", info.NAME);
                clearBuffer();
                if (!validateName(info.NAME)) {
                    printf("\n\t\t\t%sInvalid name! Please try again.%s", RED_COLOR, RESET_COLOR);
                }
            } while (!validateName(info.NAME));

            // Get updated roll number
            printf("\n\t\t\tNew Roll No: ");
            scanf("%d", &info.roll_no);
            clearBuffer();

            // Get updated salary
            do {
                printf("\n\t\t\tNew Salary (numbers only): ");
                scanf("%d", &info.SALARY);
                 clearBuffer();
                if (info.SALARY <= 0) {
                    printf("\n\t\t\t%sInvalid salary! Must be greater than 0.%s", RED_COLOR, RESET_COLOR);
                }
            } while (info.SALARY <= 0);

            printf("\n\t\t\t%sRecord updated successfully!%s\n", GREEN_COLOR, RESET_COLOR);
        }

        fwrite(&info, sizeof(struct Employ), 1, fp1);
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("Employ_info.txt");
        rename("temp.txt", "Employ_info.txt");
    } else {
        printf("\n\t\t\t%sRecord with ID %d not found.%s\n", RED_COLOR, id, RESET_COLOR);
        remove("temp.txt"); // Clean up temp file
    }

    printf("\n\t\t Returning to the main menu. Press any key to continue...");
     clearBuffer();
    getch();
}











