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

int subtract_dates(char date1_s[], char date2_s[])
{
    date date1; //make 2 date structs
    date date2;
    date1 = dateString_to_dateStruct(date1_s);
    date2 = dateString_to_dateStruct(date2_s);
    //to subtract dates for interpolation first check the years if they are different subtract them and take the absolute value and multiply by 1000 then do the same for the months and mul by 100 and then the same for the days and mul by 10. Lastly add every result and you get an indication of the distance between the dates
    int result1 = 0;
    if(date1.year!=date2.year)
    {
        result1 = abs(date1.year - date2.year) * 1000;
    }
    int result2 = 0;
    if(date1.month!=date2.month)
    {
        result2 = abs(date1.month - date2.month) * 100;
    }
    int result3 = 0;
    if(date1.day!=date2.day)
    {
        result3 = abs(date1.day - date2.day) * 100;
    }

    int result = result1 + result2 + result3;
    return result;
}

int interpolationSearch(measurements arr[], int lo, int hi, char x[])
{
    int pos;
    // Since array is sorted, an element present
    // in array must be in range defined by corner
    bool x_grtr_eq_to_arrlo = false; //date x is grater than or equal to arr[lo].date
    bool x_smlr_eq_to_arrhi = false; //date x is smaller than or equal to arr[hi].date
    int y = compare_dates(x, arr[lo].date);
    int y1 = compare_dates(x, arr[hi].date);
    if(y==1 || y==0) x_grtr_eq_to_arrlo = true;
    if(y1==-1 || y1==0) x_smlr_eq_to_arrhi = true;
    if (lo <= hi && x_grtr_eq_to_arrlo && x_smlr_eq_to_arrhi) {
        // Probing the position with keeping
        // uniform distribution in mind.
        int sub1 = subtract_dates(x ,arr[lo].date);
        int sub2 = subtract_dates(arr[hi].date ,arr[lo].date);
        pos = lo + (((double)(hi - lo) / (sub2) * (sub1)));

        // Condition of target found
        if (compare_dates(arr[pos].date, x) == 0) //arr[pos].date == x
            return pos;

        // If x is larger, x is in right sub array
        if (compare_dates(arr[pos].date, x) == -1)  //arr[pos].date < x
            return interpolationSearch(arr, pos + 1, hi, x);

        // If x is smaller, x is in left sub array
        if (compare_dates(arr[pos].date, x) == 1)  //arr[pos].date > x
            return interpolationSearch(arr, lo, pos - 1, x);
    }
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
    bool invalid_date;
    do
    {
        invalid_date = false;
        printf("Enter a date(mm/dd/yy): ");
        scanf("%s", date);
        int size = sizeof(values)/sizeof(measurements);
        clock_t start = clock();
        index = interpolationSearch(values, 0, size-1, date);
        clock_t end = clock();
        double time = (double) (end-start) / CLOCKS_PER_SEC;
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
