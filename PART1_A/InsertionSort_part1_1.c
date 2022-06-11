#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
#include <time.h>
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
void swap(measurements values[],int x,int y)
{
    measurements temp;

    temp=values[x];
    values[x]=values[y];
    values[y]=temp;
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



   Insertion_Sort2(values);
   end_t = clock();

        //printMeasurments(string_values);


      printMeasurments2(values);
      //Output_File(values,"Output_Insertion_Sort.csv");

            //functions in order to print the string data struct or the float_string data struct.


            file = fopen("Output_InsertionSort.csv" ,"w");
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
        printf("Starting the Insertion_Sort at, start_t = %ld\n", start_t);
        printf("End of the big loop, end_t = %ld\n", end_t);

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
    void Insertion_Sort2(measurements values[]){
    for(int i=0; i<1405; i++)
        {

           if(values[i+1].temp<values[i].temp) //if the next element is smaller than the previous go inside the if
           {

               for(int y=0; y<i+1; y++)       //now we need to see where we need to put the i+1 element
               {

                   if(values[i+1].temp<values[y].temp) //if the i+1 element is smaller than y element then we have to insert it to y location
                   {                                                 //we start for y=0 cause we want to start from the element 0 and find --
                                                                     //-- the first element that is bigger than the i+1 in order to insert it there.
                       measurements g1=values[i+1];
                       float g=values[i+1].temp;               //we set  the whole i+1 struct as a temp struct called g1
                                                                      //we also set the i+1 temperature as a temp value called g

                       for(int z=i; z>=0; z--)
                        {
                            if(values[z].temp<=g)                //we use a break in order to stop moving our elements 1 location further ---
                                break;                                 //---- We need to stop cause we want to move 1 location further only the part of the array ---
                                                                       //--- is bigger than the i+1 element


                        values[z+1]=values[z];               //we need to move the bigger elements 1 location further


                        }
                       values[y]=g1;                               //we insert our i+1 element to the y location

                   }

               }

           }

        }

        int max_position=0;

    int max_date_position=0;

    char max_date[50];

    float number=values[0].phosphate;

    int j=0;
       for(int i=1; i<1405+1; i++)
    {
        if(number!=values[i].temp || i==1405)
        {
            number=values[i].temp;

            max_position=i;

            for(int temp_max_position=max_position-1; temp_max_position>j; temp_max_position--)
            {
                strcpy(max_date,values[temp_max_position].date);

                max_date_position=temp_max_position;

                for(int g=j; g<temp_max_position; g++)
                {
                    if(compare_datesSort(max_date,values[g].date)==-1)
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
