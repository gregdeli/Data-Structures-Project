#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


typedef struct measurements{
    char date[20],temp[6], phosphate[6];

}measurements;

typedef struct date{
    int month;
    int day;
    int year;
}date;

void print_measurments(measurements values[])
{
    for(int i=0; i<1405; i++)
    {
        printf("%s \t%s\t%s\n",values[i].date, values[i].temp, values[i].phosphate);
    }
}

//if m1.date>m2.date it returns 1 if m1.date<m2.date -1 and if its equal it returns 0
int compare_dates(char date1_s[], char date2_s[])
{
    date date1; //make 2 date structs
    date date2;
    char temp_date1[20]; //cant use strtok() on the original date string because it will change it
    char temp_date2[20];
    strcpy(temp_date1,date1_s);
    strcpy(temp_date2,date2_s);
    char *temp1 = strtok(temp_date1, "/"); //seperate month/day/year with strtok()
    for(int i = 0; i<3; i++)
    {
        if(i == 0)
        {
            date1.month = atoi(temp1);
        }
        if(i == 1)
        {
            date1.day = atoi(temp1);
        }
        if(i == 2)
        {
            date1.year = atoi(temp1);
        }
        temp1 = strtok(NULL, "/");
    }
    //I need 2 different loops for each date because strtok() doesnt work with two strings at the same time
    char *temp2 = strtok(temp_date2, "/");
    for(int i = 0; i<3; i++)
    {
        if(i == 0)
        {
           date2.month = atoi(temp2);
        }
        if(i == 1)
        {
            date2.day = atoi(temp2);
        }
        if(i == 2)
        {
            date2.year = atoi(temp2);
        }
        temp2 = strtok(NULL, "/");
    }
    //comparison between the two date structs first by year then by month then by day
    if (date1.year < date2.year)
       return -1;

    else if (date1.year > date2.year)
       return 1;

    if (date1.year == date2.year)
    {
         if (date1.month<date2.month)
              return -1;
         else if (date1.month>date2.month)
              return 1;
         else if (date1.day<date2.day)
              return -1;
         else if(date1.day>date2.day)
              return 1;
         else
              return 0;
    }
}

int binary_search(measurements arr[], int l, int r, char x[])//x is the date I am looking for
{
    if(l>r) {return -1;}

    int mid = (l + r) / 2;
    int result = compare_dates(arr[mid].date, x);

    if(result == 0) //if the dates are equal
    {
        return mid;
    }
    else if(result == -1)
    {
        return binary_search(arr,mid + 1, r, x);
    }
    else if(result == 1)
    {
        return binary_search(arr, l, mid -1, x);
    }
}

int main()
{
    //Initialization of the file pointer
   FILE *file = fopen("ocean_sorted_dates.csv", "r");
    if(!file)
    {
      printf("Error");
      return 0;
    }

    char buff1[1024]; //se auton ton pinaka apothikeuetai i kathe grammi k
    int row_count = 0;
    int field_count =0;

    measurements values[1405]; //autos o pinakas periexei structs me ta dates kai temps apo olo to arxeio csv

    int i=0;
    while(fgets(buff1,sizeof(buff1),file))
    {

        row_count++;
        if(row_count == 1)
            continue;

        char *field = strtok(buff1, ",");
        for(field_count = 0; field_count<3; field_count++)
        {
            if(field_count==0)
                strcpy(values[i].date,field);
            if(field_count==1)
                strcpy(values[i].temp,field);
            if(field_count==2)
            strcpy(values[i].phosphate,field);

            field = strtok(NULL, ",");
        }
        i++;

    }
    fclose(file);
    //now I have an array of structs that contain the dates and temps from to ocean.csv
    char date[20];
    int index;
    bool invalid_date;
    do
    {
        invalid_date = false;
        printf("Enter a date(mm/dd/yy): ");
        scanf("%s", date);
        int size = sizeof(values)/sizeof(measurements);
        clock_t start, end;
        start = clock();
        index = binary_search(values, 0, size-1, date);
        end = clock();
        double time = (double)(end - start)/CLOCKS_PER_SEC;
        printf("It took %f secs to run the algorithm\n", time);
        if(index==-1)
        {
            invalid_date = true;
            int choice = 0;
            printf("Invalid date!\n\n");
            printf("Continue: 1\n");
            printf("Exit: 2\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);
            while ((getchar()) != '\n'); //reads input buffer until the end and discards them including newline
            if((choice != 1)&(choice != 2))
            {
                system("cls");
                continue;
            }
            switch(choice)
            {
                case 1:
                    system("cls"); //works only on windows
                    break;
                case 2:
                    return 0;

            }
        }
    }
    while(invalid_date);
    bool loop = true;
    do
    {
        int choice = 0;
        printf("Do you want to access the temperature or phosphate reading?\n");
        printf("Temperature: 1\n");
        printf("Phosphate: 2\n");
        printf("Both: 3\n");
        printf("Exit: 4\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);
        while ((getchar()) != '\n');
        if((choice != 1) & (choice != 2) & (choice != 3) & (choice != 4))
        {
            system("cls");
            continue;
        }
        switch(choice)
        {
            case 1:
                printf("The temperature on %s was %s\n", date, values[index].temp);
                break;
            case 2:
                printf("The phosphate reading on %s was %s\n", date, values[index].phosphate);
                break;
            case 3:
                printf("The temperature on %s was %s C and the phosphate reading was %s\n", date, values[index].temp, values[index].phosphate);
                break;
            case 4:
                printf("Exiting...");
                loop = false;
        }
        if(loop)
        {
            printf("Press any key to continue ");
            getch();
            system("cls"); //works only on windows
        }
    }
    while(loop);

    return 0;
}

