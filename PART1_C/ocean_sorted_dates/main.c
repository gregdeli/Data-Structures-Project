#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct measurements{
    char date[20],temp[10], phosphate[10];
    char silicate[10],  nitrite[10], nitrate[10];
    char salinity[10],  oxygen[10];

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
        printf("%s %s %s %s ",values[i].date,values[i].temp,values[i].phosphate,values[i].silicate);
        printf("%s %s %s %s \n",values[i].nitrite,values[i].nitrate,values[i].salinity,values[i].oxygen);

    }
}

//if date1_s>date2_s it returns 1 if date1_s<date2_s -1 and if they're equal it returns 0
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

//swap function between 2 types measurements
void swap(measurements *x, measurements *y)
{
    measurements temp = *x;
    *x = *y;
    *y = temp;
}

void bubble_sort(measurements arr[], int size)
{
   int i, j;
   for (i = 0; i < size-1; i++)

       // Last i elements are already in place
       for (j = 0; j < size-i-1; j++)
           if (compare_dates(arr[j].date, arr[j+1].date)==1) //if(arr[j].date>arr[j+1].date)
              swap(&arr[j], &arr[j+1]);
}

int main()
{
    //Initialization of the file pointer
   FILE *file = fopen("ocean.csv", "r");
    if(!file)
    {
      printf("Error");
      return 0;
    }

    char buff1[1024];
    int row_count = 0;
    int field_count =0;

    measurements values[1405];
    int i=0;

    while(fgets(buff1,sizeof(buff1),file))
    {
        field_count=0;
        row_count++;
        if(row_count == 1)
            {continue;}

            char *field = strtok(buff1, ",");
            while(field)
            {
                if(field_count==0)
                    strcpy(values[i].date,field);
                if(field_count==1)
                    strcpy(values[i].temp,field);
                if(field_count==2)
                    strcpy(values[i].phosphate,field);
                if(field_count==3)
                    strcpy(values[i].silicate,field);
                if(field_count==4)
                    strcpy(values[i].nitrite,field);
                if(field_count==5)
                    strcpy(values[i].nitrate,field);
                if(field_count==6)
                    strcpy(values[i].salinity,field);
                if(field_count==7)
                    strcpy(values[i].oxygen,field);

                field = strtok(NULL, ",");
                field_count++;
            }
            i++;

    }
    fclose(file);

    int size_of_values = sizeof(values)/sizeof(measurements);
    bubble_sort(values, size_of_values);
    print_measurments(values);
    //write the sorted values by date onto a new file ocean_sorted_by_dates.csv
    return 0;
}

