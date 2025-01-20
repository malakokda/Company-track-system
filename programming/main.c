#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int employeeCount;

typedef struct
{
    int day;
    int month;
    int year;

} Date;


typedef struct
{
    char id[20];
    char full_name[150];
    float salary;
    Date date_birth;
    char address[50];
    char mobile[12];
    char email[50];
    Date enrollment_date;


} Employee;


int load(FILE *file,Employee employees[100] )
{

    char line[200];

    file= fopen("company.txt","r");
    if (file== NULL)
    {
        printf("ERROR!");
    }

    while (fgets(line, 200, file) != NULL)
    {
        char* t = strtok(line,",");
        strcpy(employees[employeeCount].id,t);

        t = strtok(NULL, ",");
        strcpy(employees[employeeCount].full_name,t);

        t = strtok(NULL, ","" ");
        employees[employeeCount].salary = atof(t);


        t = strtok(NULL, "-");
        employees[employeeCount].date_birth.day = atoi(t);
        t = strtok(NULL, "-");
        employees[employeeCount].date_birth.month = atoi(t);
        t = strtok(NULL, ",");
        employees[employeeCount].date_birth.year = atoi(t);

        t = strtok(NULL, ",");
        strcpy(employees[employeeCount].address,t);

        t = strtok(NULL, ",");
        strcpy(employees[employeeCount].mobile,t);


        t = strtok(NULL, "-");
        employees[employeeCount].enrollment_date.day = atoi(t);
        t = strtok(NULL, "-");
        employees[employeeCount].enrollment_date.month = atoi(t);
        t = strtok(NULL, ",");
        employees[employeeCount].enrollment_date.year = atoi(t);

        t = strtok(NULL, ",");
        strcpy(employees[employeeCount].email,t);
        employeeCount++;
    }

    fclose(file);
}


void FormatName(char name[])
{
    if (name[0] != '\0')
    {
        name[0] = toupper(name[0]); // Convert the first letter to uppercase
        for (int i = 1; name[i] != '\0'; ++i)
        {
            name[i] = tolower(name[i]); // Convert the rest to lowercase
        }
    }
}


int Validate_ID(char ID[], Employee employees[])
{
    int i, j;
    for (i = 0; ID[i] != '\0'; i++)
    {
        if (!(ID[i] >= '0' && ID[i] <= '9'))
        {
            return 1; // Invalid ID
        }
    }
    for ( j = 0; j < employeeCount; j++)
    {
        if(strcmp(employees[j].id, ID) == 0)
        {
            return 2;  // Duplicate ID
        }
    }

    return 0; // Valid ID
}



int Validate_mobile_number(const char mobile_number_to_check[], Employee employees[])
{
    int i = 0, j;
    if (mobile_number_to_check[i] != '0')

        return 1;

    i++;
    if (mobile_number_to_check[i] != '1')

        return 1;

    i++;

    if (!(mobile_number_to_check[i] == '0' || mobile_number_to_check[i] == '1' || mobile_number_to_check[i] == '2' || mobile_number_to_check[i] == '5'))

        return 1;

    i++;

    for (i = 3; mobile_number_to_check[i] != '\0'; i++)
    {
        if (!(mobile_number_to_check[i] >= '0' && mobile_number_to_check[i] <= '9'))

            return 1;

    }

    for (j = 0; j < employeeCount; j++)
    {
        if(strcmp(employees[j].mobile, mobile_number_to_check)==0)
        {
            return 2;
        }
    }
    return 0;

}


int Validate_Name(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            printf("Error, please enter a valid name.\n");
            return 0;
        }
    }
    return 1;
}
int Validate_Email(const char email[],Employee employees[])
{
     int i, j;
    for (i = 0; email[i] != '\0'; i++)
    {
        if (!(email[i]=='@'))
        {
            return 1; // Invalid ID
        }
    }
    for ( j = 0; j < employeeCount; j++)
    {
        if(strcmp(employees[j].email, email) == 0)
        {
            return 2;  // Duplicate
        }
    }

    return 0; // Valid
}

void Query(Employee employees[])
{
    //system("cls");
    char name[50];
    int i, j, count = 1, flag = 0; // Flag to track if any matches are found

    printf("Enter the single name to search (without space):");
    gets(name);

    FormatName(name);
    for (j = 0; name[j] != '\0'; j++)
    {
        if (name[j] == ' ')
            count++;

        if (!((name[j] >= 'a' && name[j] <= 'z') || (name[j] >= 'A' && name[j] <= 'Z')))
        {
            printf("Error, please enter only a single name: ");
            gets(name);
            FormatName(name);
            count = 0;
            j = -1; // Reset j to recheck the new input
        }
    }

    if (count > 1)
    {
        printf("Error, please enter only a single name: ");
        gets(name);
    }

    for (i = 0; i < employeeCount; i++)
    {
        if (strstr(employees[i].full_name, name) != NULL)
        {
            printf("ID: %s, Name: %s, Salary: %.2f, Birth Date: %d-%d-%d, Address: %s, Mobile: %s, Enrollment Date: %d-%d-%d, Email: %s\n",
                   employees[i].id, employees[i].full_name, employees[i].salary,
                   employees[i].date_birth.day, employees[i].date_birth.month, employees[i].date_birth.year,
                   employees[i].address, employees[i].mobile,
                   employees[i].enrollment_date.day, employees[i].enrollment_date.month, employees[i].enrollment_date.year,
                   employees[i].email);
            // printf("\n..........................................\n");
            printf("\t\n");
            flag = 1;
        }
    }
    if (!flag)
        printf("No matches found for the name.\n");
}



void Add(Employee employees[], const char *filename)
{
    //system("cls");
    int i, n, max_employeecount, flag = 0;
    int id_check = 0, mobile_cheak = 0,mail=0;

    FILE *file = fopen(filename, "a"); // Open the file in append mode
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }
    printf("%d\n",employeeCount);
    printf("Enter number of employees to be added: ");
    scanf("%d",&n);

    max_employeecount = n + employeeCount;

    for (i = employeeCount; i < max_employeecount; i++)
    {
        printf("Enter the ID of the employee you want to add: ");
        fflush(stdin);
        gets(employees[i].id);

        do
        {
            id_check = Validate_ID(employees[i].id, employees);
            if(id_check == 1)
            {
                printf("Error, Please ID containing only digits: ");
                gets(employees[i].id);
                id_check = Validate_ID(employees[i].id, employees);
            }
            else if(id_check == 2)
            {
                printf("%s is used.\nEnter another ID: ",employees[i].id);
                gets(employees[i].id);
                id_check = Validate_ID(employees[i].id, employees);
            }

        }
        while(id_check != 0);


        printf("Enter the full name: ");
        gets(employees[i].full_name);

        printf("Enter the Salary: ");
        scanf("%f",&employees[i].salary);

        printf("Enter the date of birth in the formate day-month-year: ");
        scanf("%d-%d-%d",&employees[i].date_birth.day,&employees[i].date_birth.month,&employees[i].date_birth.year);

        printf("Enter the address: ");
        getchar();
        gets(employees[i].address);


        printf("Enter the mobile: ");
        gets(employees[i].mobile);
        do
        {

            mobile_cheak = Validate_mobile_number(employees[i].mobile, employees);
            if(mobile_cheak == 1)
            {
                printf("Error, Please start the mobile number by 010 or 011 or 012 or 015: ");
                gets(employees[i].mobile);
                mobile_cheak = Validate_mobile_number(employees[i].mobile, employees);
            }
            else if(mobile_cheak == 2)
            {
                printf("%s is used.\nEnter another moblie number:",employees[i].mobile);
                gets(employees[i].mobile);
                mobile_cheak = Validate_mobile_number(employees[i].mobile, employees);

            }
        }
        while(mobile_cheak != 0);



        time_t t =time(NULL);
        struct tm *date = localtime(&t);
        printf("Date of enrollment is %02d-%02d-%04d,\n",date->tm_mday,(date->tm_mon)+1,(date->tm_year)+1900);
        employees[i].enrollment_date.day=date->tm_mday;
        employees[i].enrollment_date.month=(date->tm_mon)+1;
        employees[i].enrollment_date.year=(date->tm_year)+1900;


        printf("Enter the E-mail: ");
        getchar();
        gets(employees[i].email);


        do
        {mail = Validate_Email(employees[i].email, employees);
            if(mail == 1)
            {
                printf("Error, Enter another email: ");
                gets(employees[i].email);
               mail = Validate_Email(employees[i].email, employees);
            }
            else if(mail == 2)
            {
                printf("%s is used.\nEnter another ID: ",employees[i].email);
                gets(employees[i].id);
               mail = Validate_Email(employees[i].email, employees);
            }

        }
        while(mail != 0);







        employeeCount++;
        printf("\nEmployee with ID %s Added successfully.\n", employees[i].id);
    }
}


void Delete(Employee employees[], const char *filename)
{
    char idToDelete[20];
    int flag = 0, i, nop,j;
    FILE *fileptr1;


    printf("%d\n",employeeCount);
    printf("Enter number of employees to delete: ");
    scanf("%d",&nop);
    while (nop>employeeCount)
    {
        printf("The entered value is larger than the existed employees\nEnter another number:");
        scanf("%d",&nop);
    }
    for(j=0; j<nop; j++)
    {
        do
        {
            // Get employee ID to delete
            printf("\nEnter the ID for the employee you want to delete: ");
            fflush(stdin);
            gets(idToDelete);
            for(i=0; idToDelete[i]!='\0'; i++)
            {
                if(!(idToDelete[i]>='0'&&idToDelete[i]<='9'))
                {
                    printf("Error, Please Enter Id again: ");
                    gets(idToDelete);
                    flag=1;
                    break;
                }
            }
            // Search for the employee with the given ID
            for (int i = 0; i < employeeCount; i++)
            {
                if (strstr(employees[i].id, idToDelete) )
                {
                    printf("employees[%d].id=%s , idToDelete=%s",i,employees[i].id,idToDelete);
                    // Shift elements to fill the gap
                    for (int j = i; j < (employeeCount - 1); j++)
                    {
                        employees[j] = employees[j + 1];
                    }

                    employeeCount--;
                    flag = 1;
                    break;
                }
            }

            // If the employee was found, update the file
            if (flag==1)
            {
                FILE *fileptr1;
                fileptr1 = fopen(filename, "w");  // Open the file in write mode

                /*// Write the modified data back to the file
                for (int i = 0; i < employeeCount ; i++)
                {
                    fprintf(fileptr1, "%s, %s, %.2f, %d-%d-%d, %s, %s, %d-%d-%d, %s\n",
                            employees[i].id,
                            employees[i].full_name,
                            employees[i].salary,
                            employees[i].date_birth.day,
                            employees[i].date_birth.month,
                            employees[i].date_birth.year,
                            employees[i].address,
                            employees[i].mobile,
                            employees[i].enrollment_date.day,
                            employees[i].enrollment_date.month,
                            employees[i].enrollment_date.year,
                            employees[i].email);
                }*/

                fclose(fileptr1);

                printf("\nEmployee with ID %s deleted successfully.\n", idToDelete);
                break;
            }
            else
            {
                printf("Employee with ID %s not found.\n", idToDelete);
            }
        }
        while (flag ==1);
    }
}


void Modify(Employee employees[], const char *filename)
{
    char idToModify[20];
    int i, x, check_id;

    printf("\nEnter the ID for the employee you want to modify: ");
    getchar();
    gets(idToModify);
    fflush(stdin);

    check_id = Validate_ID(idToModify, employees);
    if(check_id == 1)
    {
        printf("Invalid ID.\n");
    }
    else if(check_id == 2)
    {
        printf("\nEmployee found. Choose Which data you Want to Edit:\n");
        printf("1. Full name\n");
        printf("2. Salary\n");
        printf("3. Mobile number\n");
        printf("4. Address\n");
        printf("5. E-mail Address\n");

        printf("Your choose is: ");
        scanf("%d",&x);
        do
        {
            switch (x)
            {
            case 1:
                do
                {
                    printf("Enter the new full name: ");
                    getchar();
                    gets(employees[i].full_name);
                }
                while (!Validate_Name(employees[i].full_name));
                break;

            case 2:
                printf("Enter the new Salary: ");
                scanf("%f", &employees[i].salary);
                break;

            case 3:
                printf("Enter the new mobile: ");
                getchar();
                gets(employees[i].mobile);
                do
                {
                    printf("Error, enter the new mobile: ");
                    getchar();
                    gets(employees[i].mobile);
                }
                while(!Validate_mobile_number(employees[i].mobile, employees));
                break;

            case 4:
                printf("Enter the new address: ");
                getchar();
                gets(employees[i].address);
                break;

            case 5:
                printf("Enter the new E-mail: ");
                getchar();
                gets(employees[i].email);
                  do
                {
                    printf("Error, enter the new email: ");
                    getchar();
                    gets(employees[i].email);
                }
                while(!Validate_Email(employees[i].email, employees));
                break;

            default:
                printf("Error, Choose from 1-5.");

            }
        }
        while(!(x>=1 || x<=5));



        // Update the modified employee in the file
        FILE *fileptr = fopen(filename, "w");
        if (fileptr == NULL)
        {
            printf("Error opening the file for writing.\n");
            return;
        }

        for (int j = 0; j < employeeCount; j++)
        {
            fprintf(fileptr, "%s, %s, %.2f, %d-%d-%d, %s, %s, %d-%d-%d, %s",
                    employees[j].id,
                    employees[j].full_name,
                    employees[j].salary,
                    employees[j].date_birth.day,
                    employees[j].date_birth.month,
                    employees[j].date_birth.year,
                    employees[j].address,
                    employees[j].mobile,
                    employees[j].enrollment_date.day,
                    employees[j].enrollment_date.month,
                    employees[j].enrollment_date.year,
                    employees[j].email);
        }

        fclose(fileptr);

        if(x>=1 || x<=5)
            printf("\nEmployee with ID %s modified successfully.\n", idToModify);


        else
            printf("Employee with ID %s not found.\n", idToModify);
    }
}

void SortByName(Employee employees[], const char *filename)
{
    FILE *fileptr = fopen(filename, "w");

    Employee temp;
    if (fileptr == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

   // Write the sorted array to the file
    for (int i = 0; i < employeeCount - 1; i++)
    {
        for (int j = i + 1; j < employeeCount; j++)
        {
            if (strcmp(employees[j].full_name, employees[i].full_name) < 0)
            {
                strcpy(temp.id, employees[i].id);
                strcpy(temp.full_name, employees[i].full_name);
                temp.salary = employees[i].salary;
                temp.date_birth.day = employees[i].date_birth.day;
                temp.date_birth.month = employees[i].date_birth.month;
                temp.date_birth.year = employees[i].date_birth.year;
                strcpy(temp.address, employees[i].address);
                strcpy(temp.mobile, employees[i].mobile);
                temp.enrollment_date.day = employees[i].enrollment_date.day;
                temp.enrollment_date.month = employees[i].enrollment_date.month;
                temp.enrollment_date.year = employees[i].enrollment_date.year;
                strcpy(temp.email, employees[i].email);

                strcpy(employees[i].id, employees[j].id);
                strcpy(employees[i].full_name, employees[j].full_name);
                employees[i].salary = employees[j].salary;
                employees[i].date_birth.day = employees[j].date_birth.day;
                employees[i].date_birth.month = employees[j].date_birth.month;
                employees[i].date_birth.year = employees[j].date_birth.year;
                strcpy(employees[i].address, employees[j].address);
                strcpy(employees[i].mobile, employees[j].mobile);
                employees[i].enrollment_date.day = employees[j].enrollment_date.day;
                employees[i].enrollment_date.month = employees[j].enrollment_date.month;
                employees[i].enrollment_date.year = employees[j].enrollment_date.year;
                strcpy(employees[i].email, employees[j].email);

                strcpy(employees[j].id, temp.id);
                strcpy(employees[j].full_name, temp.full_name);
                employees[j].salary = temp.salary;
                employees[j].date_birth.day = temp.date_birth.day;
                employees[j].date_birth.month = temp.date_birth.month;
                employees[j].date_birth.year = temp.date_birth.year;
                strcpy(employees[j].address, temp.address);
                strcpy(employees[j].mobile, temp.mobile);
                employees[j].enrollment_date.day = temp.enrollment_date.day;
                employees[j].enrollment_date.month = temp.enrollment_date.month;
                employees[j].enrollment_date.year = temp.enrollment_date.year;
                strcpy(employees[j].email, temp.email);
            }
        }
    }
    for (int i = 0; i < employeeCount; i++)
    {
        fprintf(fileptr, "%s,%s,%f,%d-%d-%d,%s,%s,%d-%d-%d,%s\n",
                employees[i].id, employees[i].full_name, employees[i].salary, employees[i].date_birth.day,
                employees[i].date_birth.month, employees[i].date_birth.year, employees[i].address, employees[i].mobile,
                employees[i].enrollment_date.day, employees[i].enrollment_date.month, employees[i].enrollment_date.year,
                employees[i].email);
    }


}
 void SortByDOB(Employee employees, const char *filename)
 {
     FILE *fileptr = fopen(filename, "w");

    if (fileptr == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

      for (int i = 0; i < employeeCount - 1; i++)
    {  Employee temp[i];
        for (int j = i + 1; j < employeeCount; j++)
        {
            if (employees[j].date_birth.year>employees[i].date_birth.year)
            {

               strcpy(temp,employees[i]);
               strcpy(employees[i],employees[j]);
               strcpy(employees[j],temp);

            }
            else if(employees[j].date_birth.year==employees[i].date_birth.year)
            {
                if (employees[j].date_birth.month>employees[i].date_birth.month)
                {

               strcpy(temp,employees[i]);
               strcpy(employees[i],employees[j]);
               strcpy(employees[j],temp);
                }
            }
            else if (employees[j].date_birth.month==employees[i].date_birth.month)
            {
                if(employees[j].date_birth.day>employees[i].date_birth.day)
                {
                      strcpy(temp,employees[i]);
               strcpy(employees[i],employees[j]);
               strcpy(employees[j],temp);
                }

            }
        }
    }
     for (int k = 0; k < employeeCount; k++)
    {
        fprintf(fileptr, "%s,%s,%f,%d-%d-%d,%s,%s,%d-%d-%d,%s\n",
                employees[k].id, employees[k].full_name, employees[k].salary, employees[k].date_birth.day,
                employees[k].date_birth.month, employees[k].date_birth.year, employees[k].address, employees[k].mobile,
                employees[k].enrollment_date.day, employees[k].enrollment_date.month, employees[k].enrollment_date.year,
                employees[k].email);
    }

 }


void SortBySalary(Employee employees[],  const char *filename)
{
    FILE *fileptr = fopen(filename, "w");

    if (fileptr == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    for (int i = 0; i < employeeCount - 1; i++)
    {
        for (int j = i + 1; j < employeeCount; j++)
        {
            if (employees[j].salary>employees[i].salary)
            {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }

    for (int i = 0; i < employeeCount; i++)
    {
        fprintf(fileptr, "%s,%s,%f,%d-%d-%d,%s,%s,%d-%d-%d,%s\n",
                employees[i].id, employees[i].full_name, employees[i].salary, employees[i].date_birth.day,
                employees[i].date_birth.month, employees[i].date_birth.year, employees[i].address, employees[i].mobile,
                employees[i].enrollment_date.day, employees[i].enrollment_date.month, employees[i].enrollment_date.year,
                employees[i].email);
    }

}


void print_sort(Employee employees[],  const char *filename)
{
    int x;
    printf("Enter which type you want to sort by:\n");
    printf("1. Name\n");
    printf("2. Date of Birth\n");
    printf("3. Salary\n");
    printf("Your choice is: ");
    fflush(stdin);
    scanf("%d", &x);

    do
    {
        switch (x)
        {
        case 1:
            printf("Sorting by Name...\n");
            SortByName(employees, filename);
            break;

        case 2:
            printf("Sorting by Date of Birth...\n");
            SortByDOB(employees, filename);
            break;

        case 3:
            printf("Sorting by Salary...\n");
            SortBySalary(employees, filename);

            break;

        default:
            printf("Error, enter number from 1-3:\n");
            scanf("%d", &x);
            break;
        }
    }
    while (!(x == 1 || x == 2 || x == 3));
}



void Save(Employee employees[], const char *filename)
{
    int p;
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Error opening the file for saving.\n");
        return;
    }

    /*for (int i = 0; i < employeeCount; i++)
    {
        fprintf(file, "\n%s, %s, %.2f, %d-%d-%d, %s, %s, %d-%d-%d, %s",
                employees[i].id,
                employees[i].full_name,
                employees[i].salary,
                employees[i].date_birth.day,
                employees[i].date_birth.month,
                employees[i].date_birth.year,
                employees[i].address,
                employees[i].mobile,
                employees[i].enrollment_date.day,
                employees[i].enrollment_date.month,
                employees[i].enrollment_date.year,
                employees[i].email);
    }*/
    printf("\nData saved successfully.\n");
    printf("Do you want to exit?\n1)yes , 2)No \n enter the numebr of your choice: ");
    scanf("%d",&p);
    if(p==1)
    {
        exit(0);
    }

}


void quit()
{
    int choice;
    printf("Are you sure you want to quit without saving? (1 - Yes, 0 - No)\n");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        printf("Warning: All of your changes will be discarded.\n");
        exit(0);
    }
}


// Function to display the menu
void DisplayMenu( Employee employees [])
{
    int choice;
    do
    {

        printf("\nMENU:\n");
        printf("1. ADD\n");
        printf("2. DELETE\n");
        printf("3. MODIFY\n");
        printf("4. SEARCH\n");
        printf("5. PRINT\n");
        printf("6. SAVE\n");
        printf("7. QUIT\n");


        // DisplayMenu(employees,&employeeCount);
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            //system("cls");
            Add(employees, "company.txt");
            break;
        case 2:
            //system("cls");
            Delete(employees, "company.txt");
            break;
        case 3:
            //system("cls");

            Modify( employees, "company.txt");
            break;
        case 4:
            system("cls");
            Query(employees);
            break;
        case 5:
            //system("cls");
            print_sort(employees, "company.txt");
            break;
        case 6:
            //system("cls");
            Save(employees,  "company.txt");
            break;
        case 7:
            //system("cls");
            quit();
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }


    }
    while (choice != 0);

}




int main()
{
    FILE *file;
    Employee employees[100];


    file = fopen("company.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }
    load(file,employees );
    DisplayMenu(employees);

    /*for (int i =0 ; i < employeeCount; i++)
    {
        printf("ID: %s, Name: %s, Salary: %.2f, Birth Date: %d-%d-%d, Address: %s, Mobile: %s, Enrollment Date: %d-%d-%d, Email: %s",
               employees[i].id, employees[i].full_name, employees[i].salary,
               employees[i].date_birth.day, employees[i].date_birth.month, employees[i].date_birth.year,
               employees[i].address, employees[i].mobile,
               employees[i].enrollment_date.day, employees[i].enrollment_date.month, employees[i].enrollment_date.year,
               employees[i].email);
        printf("\n\n");
    }*/

    fclose(file);

    return 0;

}
