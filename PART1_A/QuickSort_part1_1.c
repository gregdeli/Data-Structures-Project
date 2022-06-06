    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef struct date{
        int month;
        int day;
        int year;
    }date;

    typedef struct measurements{ //struct with floats and string only for the date
        char date[50];
        float temp, phosphate;
        float silicate,  nitrite, nitrate;
        float salinity,  oxygen;

    }measurements;

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
            continue;

            char *field = strtok(buff1, ",");
            while(field)
            {
                if(field_count==0)
                    strcpy(values[i].date,field);
                if(field_count==1)
                    values[i].temp=atof(field);
                if(field_count==2)
                    values[i].phosphate=atof(field);
                if(field_count==3)
                    values[i].silicate=atof(field);
                if(field_count==4)
                    values[i].nitrite=atof(field);
                if(field_count==5)
                    values[i].nitrate=atof(field);
                if(field_count==6)
                    values[i].salinity=atof(field);
                if(field_count==7)
                    values[i].oxygen=atof(field);

                field = strtok(NULL, ",");
                field_count++;
            }
            i++;
        }
        fclose(file);



clock_t start_t, end_t;


   start_t = clock();
   Quick_Sort2(values,0,1404);
   end_t = clock();





     printMeasurments2(values);


            //functions in order to print the string data struct or the float_string data struct.


           file = fopen("Output_QuickSort.csv" ,"w");
        if(file==NULL)
        {
            printf("Error");
            return 0;
        }
        //write the sorted by date data on a new file
        fprintf(file, "Date,T_degC,PO4uM,SiO3uM,NO2uM,NO3uM,Salnty,O2ml_L\n");
        for(int i=0; i<1405; i++)
        {
            fprintf(file, "%s,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", values[i].date, values[i].temp, values[i].phosphate, values[i].silicate, values[i].nitrite, values[i].nitrate, values[i].salinity, values[i].oxygen);
        }
        fclose(file);
printf("Starting of the QuickSort, start_t = %ld\n", start_t);
printf("End of the QuickSort, end_t = %ld\n", end_t);

double total_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
   printf("Time taken: %fs\n", total_t);
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
    void Quick_Sort2(measurements values[],int nleft,int nright){

float pivot=values[1404].temp;

if (nleft<nright)
    {
    float pivot1 = values[nright].temp; //We set the pivot as the last element
    int i = (nleft - 1); // We use i to point out the element that is smaller in a partition and to also indicate
                         // the right position of our pivot

    for (int j = nleft; j <= nright - 1; j++)
    {
        if (values[j].temp< pivot1)//If the element j that we are currently looking is smaller than the pivot
        {
            i++;



    measurements temp=values[i];
    values[i]=values[j]; //we swap the smaller elements to the left and the biggest to the right
    values[j]=temp;

        }
    }
    measurements temp1=values[i+1];
    values[i+1]=values[nright]; //We swap the pivot with the i+1 element because the partition of the values before the i is sorted.
    values[nright]=temp1;

    Quick_Sort2(values,nleft,i); //We now have to sort the other partitions
    Quick_Sort2(values,i+2,nright);
    }
    for(int i=0; i<1404; i++)
        {
            if(values[i].temp==values[i+1].temp){
        if(compare_datesSort(values[i].date,values[i+1].date)==1)
           {
              measurements v1=values[i];
               measurements v2=values[i+1];
               values[i]=v2;
               values[i+1]=v1;
           }
            }
        }
    }
    int compare_datesSort(char date1_s[], char date_s[])
    {
        date date1; //make 2 date structs
        date date;
        char temp_date1[20]; //cant use strtok() on the original date string because it will change it
        char temp_date[20];
        strcpy(temp_date1,date1_s);
        strcpy(temp_date,date_s);
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
        char *temp2 = strtok(temp_date, "/");
        for(int i = 0; i<3; i++)
        {
            if(i == 0)
            {
               date.month = atoi(temp2);
            }
            if(i == 1)
            {
                date.day = atoi(temp2);
            }
            if(i == 2)
            {
                date.year = atoi(temp2);
            }
            temp2 = strtok(NULL, "/");
        }
        //comparison between the two date structs first by year then by month then by day
        if (date1.year < date.year)
           return -1;

        else if (date1.year > date.year)
           return 1;

        if (date1.year == date.year)
        {
             if (date1.month<date.month)
                  return -1;
             else if (date1.month>date.month)
                  return 1;
             else if (date1.day<date.day)
                  return -1;
             else if(date1.day>date.day)
                  return 1;
             else
                  return 0;
        }
    }

void QuickSort(int array[],int nleft,int nright)
{
    if (nleft<nright)
    {
    int pivot1 = array[nright]; //We set the pivot as the last element
    int i = (nleft - 1); // We use i to point out the element that is smaller in a partition and to also indicate
                         // the right position of our pivot

    for (int j = nleft; j <= nright - 1; j++)
    {
        if (array[j] < pivot1)//If the element j that we are currently looking is smaller than the pivot
        {
            i++;

    int temp=array[i];
    array[i]=array[j]; //we swap the smaller elements to the left and the biggest to the right
    array[j]=temp;

        }
    }
    int temp1=array[i+1];
    array[i+1]=array[nright]; //We swap the pivot with the i+1 element because the partition of the array before the i is sorted.
    array[nright]=temp1;

    QuickSort(array,nleft,i); //We now have to sort the other partitions
    QuickSort(array,i+2,nright);
    }
}

/* Function to print an arrayay */

