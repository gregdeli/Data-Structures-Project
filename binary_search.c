#include <stdio.h>
#include <string.h>

typedef struct measurements{
    char date[20],temp[6];

}measurements;

typedef struct date{
    int year;
    int month;
    int day;
}date;

void printMeasurments(measurements values[])
{
    for(int i=0; i<1405; i++)
    {
        printf("%s \t%s\n",values[i].date, values[i].temp);
    }
}

//if m1.date>m2.date it returns 1 if m1.date<m2.date -1 and if its equal it returns 0
int compare_dates (measurements m1, measurements m2)
{
    char date1_s[20];
    char date2_s[20];
    strcpy(date1_s, m1.date);
    strcpy(date2_s, m2.date);
    date date1;
    date date2;
    int counter = 0;
    char *temp1 = strtok(date1_s, "/");
    char *temp2 = strtok(date1_s, "/");
    for(int i = 0; i<3; i++)
    {
        if(counter == 0)
        {
            date1.day = atoi(temp1);
            date2.day = atoi(temp2);
        }
        if(counter == 1)
        {
            date1.month = atoi(temp1);
            date2.month = atoi(temp2);
        }
        if(counter == 2)
        {
            date1.year = atoi(temp1);
            date2.year = atoi(temp2);
        }
        counter++;
        temp1 = strtok(NULL, "/");
        temp2 = strtok(NULL, "/");


    }
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

/*int binarySearch(measurements arr[], int l, int r, int x) //to x einai o arithmos pou psaxnw
{
    if(l>r) {return -1;}

    int mid = (l + r) / 2;

    if(arr[mid] == x)
    {
        return mid;
    }
    else if(arr[mid] < x)
    {
        return binarySearch(arr,mid + 1, r, x);
    }
    else if(arr[mid] > x)
    {
        return binarySearch(arr, l, mid -1, x);
    }
}*/

int main()
{
    //Initialization of the file pointer
   FILE *file = fopen("ocean.csv", "r");
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
        for(field_count = 0; field_count<2; field_count++)
        {
            if(field_count==0)
                strcpy(values[i].date,field);
            if(field_count==1)
                strcpy(values[i].temp,field);

            field = strtok(NULL, ",");
        }
        i++;

    }
    fclose(file);

    //exw enan pinaka me structs pou periexoun ta dates kai temps apo to ocean.csv


    printMeasurments(values);
    return 0;
}


