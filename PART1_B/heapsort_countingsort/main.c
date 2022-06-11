#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Measurements
{
    char date[50];
    float temp, phosphate;
    float silicate,  nitrite, nitrate;
    float salinity,  oxygen;
}measurements;

typedef struct date
{
    int month;
    int day;
    int year;
}date;

int Compare_dates(char date1_s[], char date2_s[])
{
    date date1;
    date date2;

    char temp_date1[50]; //cant use strtok() on the original date string because it will change it
    char temp_date2[50];

    strcpy(temp_date1,date1_s);
    strcpy(temp_date2,date2_s);

    char *temp1 = strtok(temp_date1, "/");

    for(int i = 0; i<3; i++)
    {
        if(i == 0)
        {
            date1.month = atoi(temp1);
        }
        else if(i == 1)
        {
            date1.day = atoi(temp1);
        }
        else if(i == 2)
        {
            date1.year = atoi(temp1);
        }
        temp1 = strtok(NULL, "/");
    }

    char *temp2 = strtok(temp_date2, "/");

    for(int i = 0; i<3; i++)
    {
        if(i == 0)
        {
           date2.month = atoi(temp2);
        }
        else if(i == 1)
        {
            date2.day = atoi(temp2);
        }
        else if(i == 2)
        {
            date2.year = atoi(temp2);
        }
        temp2 = strtok(NULL, "/");
    }

    if (date1.year < date2.year)
    {
       return -1;
    }
    else if (date1.year > date2.year)
    {
       return 1;
    }
    else if (date1.year == date2.year)
    {
        if(date1.month<date2.month)
        {
            return -1;
        }
        else if(date1.month>date2.month)
        {
            return 1;
        }
        else if(date1.day<date2.day)
        {
            return -1;
        }
        else if(date1.day>date2.day)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void swap(measurements values[],int x,int y)
{
    measurements temp;

    temp=values[x];
    values[x]=values[y];
    values[y]=temp;
}

void Heapify(measurements values[],int size,int position)
{
    int largest=position;
    int left=2*position+1;
    int right=2*position+2;

    if (left<size && values[left].phosphate>values[largest].phosphate)
    {
        largest=left;
    }
    else if(left<size && values[left].phosphate==values[largest].phosphate)
    {
        int result_dates1;

        result_dates1=Compare_dates(values[left].date,values[largest].date);

        if(result_dates1==1)
        {
            largest=left;
        }
    }

    if (right<size && values[right].phosphate>values[largest].phosphate)
    {
        largest=right;
    }
    else if(right<size && values[right].phosphate==values[largest].phosphate)
    {
        int result_dates2;

        result_dates2=Compare_dates(values[right].date,values[largest].date);

        if(result_dates2==1)
        {
            largest=right;
        }
    }

    if (largest!=position)
    {
        swap(values,position,largest);

        Heapify(values,size,largest);
    }
}

void Heap_sort(measurements values[],int size)
{
    for (int i=size/2-1; i>=0; i--)
    {
        Heapify(values, size, i);
    }

    for (int i=size-1; i>0; i--)
    {
        swap(values,0,i);

        Heapify(values, i, 0);
    }
}

void Counting_sort(measurements values[],int size)
{
    for(int i=0; i<size; i++)
    {
        values[i].phosphate=values[i].phosphate*100;
    }

   int max=0;

   max=values[0].phosphate;

   for(int i=1; i<size; i++)
   {
       if(values[i].phosphate>max)
       {
           max=values[i].phosphate;
       }
   }

   int count_size=0;

   count_size=max+1;

   int count_array[count_size];

    for(int i=0; i<count_size; i++)
    {
        count_array[i]=0;
    }

    for(int i=0; i<size; i++)
    {
        count_array[(int)values[i].phosphate]++;
    }

    for(int i=0; i<count_size-1; i++)
    {
        count_array[i+1]=count_array[i+1]+count_array[i];
    }

    measurements result_array[size];

    for(int i=size-1; i>=0; i--)
    {
        result_array[count_array[(int)values[i].phosphate]-1]=values[i];

        count_array[(int)values[i].phosphate]--;
    }

    for(int i=0; i<size; i++)
    {
        result_array[i].phosphate=result_array[i].phosphate/100;
    }

    for(int i=0; i<size; i++)
    {
        values[i]=result_array[i];
    }

    int max_position=0;

    int max_date_position=0;

    char max_date[50];

    float number=values[0].phosphate;

    int j=0;

    for(int i=1; i<size+1; i++)
    {
        if(number!=values[i].phosphate || i==size)
        {
            number=values[i].phosphate;

            max_position=i;

            for(int temp_max_position=max_position-1; temp_max_position>j; temp_max_position--)
            {
                strcpy(max_date,values[temp_max_position].date);

                max_date_position=temp_max_position;

                for(int g=j; g<temp_max_position; g++)
                {
                    if(Compare_dates(max_date,values[g].date)==-1)
                    {
                        strcpy(max_date,values[g].date);

                        max_date_position=g;
                    }
                }

                if(max_date_position!=temp_max_position)
                {
                    swap(values,max_date_position,temp_max_position);
                }
            }

            j=max_position;
        }
    }
}

int main()
{
   FILE *file=fopen("ocean.csv", "r");

   if(!file)
    {
      printf("Error");
      return 0;
    }

    char buff1[1024];
    int row_count = 0;
    int field_count =0;

    measurements values1[1405], values2[1405];

    int i=0;

    while(fgets(buff1,sizeof(buff1),file))
    {
        field_count=0;
        row_count++;
        if(row_count == 1)
            continue;

            char *field = strtok(buff1, ",");
            while(field)
            {
                if(field_count==0)
                    strcpy(values1[i].date,field);
                if(field_count==1)
                    values1[i].temp=atof(field);
                if(field_count==2)
                    values1[i].phosphate=atof(field);
                if(field_count==3)
                    values1[i].silicate=atof(field);
                if(field_count==4)
                    values1[i].nitrite=atof(field);
                if(field_count==5)
                    values1[i].nitrate=atof(field);
                if(field_count==6)
                    values1[i].salinity=atof(field);
                if(field_count==7)
                    values1[i].oxygen=atof(field);

                field = strtok(NULL, ",");
                field_count++;
            }
            i++;
    }

    fclose(file);

    for(int i=0; i<1405; i++)
    {
        values2[i]=values1[i];
    }

    int size=0;

    size=i;

    clock_t start1, end1;

    start1=clock();
    Heap_sort(values1, size);
    end1=clock();
printMeasurments2(values1);
    double time_taken1=(double)(end1-start1)/CLOCKS_PER_SEC;

    printf("Heap_sort took %f seconds to execute.\n", time_taken1);

    clock_t start2, end2;

    start2=clock();
    Counting_sort(values2,size);
    end2=clock();

    double time_taken2=(double)(end2-start2)/CLOCKS_PER_SEC;

    printf("\nCounting_sort took %f seconds to execute.\n", time_taken2);

    file=fopen("ocean_heap_sorted.csv","w");

    if(file==NULL)
    {
        printf("Error");
        return 0;
    }

    fprintf(file, "Date,T_degC,PO4uM,SiO3uM,NO2uM,NO3uM,Salnty,O2ml_L\n");

    for(int i=0; i<1405; i++)
    {
        fprintf(file,"%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",values1[i].date,values1[i].temp,values1[i].phosphate,values1[i].silicate,values1[i].nitrite,values1[i].nitrate,values1[i].salinity,values1[i].oxygen);
    }

    fclose(file);

    file=fopen("ocean_counting_sorted.csv","w");

    if(file==NULL)
    {
        printf("Error");
        return 0;
    }

    fprintf(file, "Date,T_degC,PO4uM,SiO3uM,NO2uM,NO3uM,Salnty,O2ml_L\n");

    for(int i=0; i<1405; i++)
    {
        fprintf(file,"%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",values2[i].date,values2[i].temp,values2[i].phosphate,values2[i].silicate,values2[i].nitrite,values2[i].nitrate,values2[i].salinity,values2[i].oxygen);
    }

    fclose(file);

    return 0;
}
void printMeasurments2(measurements values[])
    {
        for(int i=0; i<1405; i++)
        {

           printf("%s %.2f %.2f %.2f ",values[i].date,values[i].temp,values[i].phosphate,values[i].silicate);
           printf("%.2f %.2f %.2f %.2f\n",values[i].nitrite,values[i].nitrate,values[i].salinity,values[i].oxygen);
           //printf("%.2f\n",values[i].temp2);
        }
    }
