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

date dateString_to_dateStruct(char date1_s[])
{
    date date1; //make 2 date structs
    char temp_date1[20]; //cant use strtok() on the original date string because it will change it
    strcpy(temp_date1,date1_s);
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
    return date1;
}

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
    date1 = dateString_to_dateStruct(date1_s);
    date2 = dateString_to_dateStruct(date2_s);
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

// To store number of days in
// all months from January to Dec.
const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };

// This function counts number of
// leap years before the given date
int countLeapYears(date d)
{
    int years = d.year;

    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (d.month <= 2)
        years--;

    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
     // multiple of 100.
    return years / 4
           - years / 100
           + years / 400;
}

// This function returns number of
// days between two given dates
int subtract_dates(char date1_s[], char date2_s[])
{
    date dt1;
    date dt2;
    dt1 = dateString_to_dateStruct(date1_s);
    dt2 = dateString_to_dateStruct(date2_s);

    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'

    // initialize count using years and day
    long int n1 = dt1.year * 365 + dt1.day;

    // Add days for months in given date
    for (int i = 0; i < dt1.month - 1; i++)
        n1 += monthDays[i];

    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);

    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'

    long int n2 = dt2.year * 365 + dt2.day;
    for (int i = 0; i < dt2.month- 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);

    // return difference between two counts
    if(compare_dates(date1_s, date2_s)==1)
    {
        return (n1-n2);
    }
    else if(compare_dates(date1_s, date2_s)==-1)
    {
        return (n2-n1);
    }
    else return 0;
}

int binary_interpolation_search(measurements arr[], int left, int right, char x[])
{
    if(compare_dates(x, arr[left].date)==-1 || compare_dates(x, arr[right].date)==1) // if(x<arr[left].date) or if(x>arr[right].date)
        return -1;
    int result = -2;
    int size = right-left+1;
    int sub1 = subtract_dates(x ,arr[left].date);
    int sub2 = subtract_dates(arr[right].date ,arr[left].date);
    int next =((size) * sub1 / sub2);
    result = compare_dates(x, arr[next].date);
    while(result==1 || result==-1)
    {
        int i = 0;
        size = right - left + 1;
        if(result == 1 || result == 0) //if x >= arr[next].date
        {
            int pos = next+i*sqrt(size);
            int res = compare_dates(x, arr[pos].date);
            while(res == 1) //while x>arr[pos].date
            {
                i++;
                pos = next+i*sqrt(size);
                res = compare_dates(x, arr[pos].date);
            }
            right = next + i*sqrt(size);
            left = next + (i-1)*sqrt(size);
        }
        if(result == -1) //if x < arr[next].date
        {
            int pos = next-i*sqrt(size);
            int res = compare_dates(x, arr[pos].date);
            while(res == -1)
            {
                i++;
                pos = next-i*sqrt(size);
                res = compare_dates(x, arr[pos].date);
            }
            right = next - (i-1)*sqrt(size);
            left = next - i*sqrt(size);
        }
        if(compare_dates(x, arr[right].date)==0)
            return right;
        if(compare_dates(x, arr[left].date)==0)
            return left;
        sub1 = subtract_dates(x ,arr[left].date);
        sub2 = subtract_dates(arr[right].date ,arr[left].date);
        next = left + ((right-left+1) * sub1 / sub2);
        result = compare_dates(x, arr[next].date);
    }
    result = compare_dates(x, arr[next].date);
    if(result == 0)
        return next;
    else
        return -1;

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
    bool loop;
    do
    {
        loop = false;
        printf("Enter a date(mm/dd/yy): ");
        scanf("%s", date);
        int temp = atoi(date);
        int size = sizeof(values)/sizeof(measurements);
        clock_t start = clock();
        index = binary_interpolation_search(values, 0, size-1, date);
        clock_t end = clock();
        double time = (double) (end-start) / CLOCKS_PER_SEC;
        if(index==-1)
        {
            loop = true;
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
                    continue;
                case 2:
                    return 0;

            }
        }
        printf("It took %f secs to run the algorithm\n", time);
        int choice = 0;
        printf("Do you want to access the temperature or phosphate reading?\n");
        printf("Temperature: 1\n");
        printf("Phosphate: 2\n");
        printf("Both: 3\n");
        printf("New date: 4\n");
        printf("Exit: 5\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);
        while ((getchar()) != '\n');
        if((choice != 1) & (choice != 2) & (choice != 3) & (choice != 4) & (choice != 5))
        {
            system("cls");
            continue;
        }
        switch(choice)
        {
            case 1:
                printf("The temperature on %s was %s\n", date, values[index].temp);

            case 2:
                printf("The phosphate reading on %s was %s\n", date, values[index].phosphate);

            case 3:
                printf("The temperature on %s was %s C and the phosphate reading was %s\n", date, values[index].temp, values[index].phosphate);

            case 4:
                loop = true;
                system("cls"); //works only on windows
                continue;
            case 5:
                printf("Exiting...\n");
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
