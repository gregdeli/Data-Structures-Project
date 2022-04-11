#include <stdio.h>
#include <stdlib.h>

typedef struct String_Measurements{ //struct with array of strings
    char date[50],temp[50], phosphate[50];
    char silicate[50],  nitrite[50], nitrate[50];
    char salinity[50],  oxygen[50];

}string_measurements;

typedef struct Float_Measurements{ //struct with floats and string only for the date
    char date2[50];
    float temp2, phosphate2;
    float silicate2,  nitrite2, nitrate2;
    float salinity2,  oxygen2;

}float_measurements;

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

    string_measurements string_values[1405];
    float_measurements float_values[1405];
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
                    strcpy(string_values[i].date,field);
                if(field_count==1)
                    strcpy(string_values[i].temp,field);      //while for copying from csv to struct
                if(field_count==2)
                    strcpy(string_values[i].phosphate,field);
                if(field_count==3)
                    strcpy(string_values[i].silicate,field);
                if(field_count==4)
                    strcpy(string_values[i].nitrite,field);
                if(field_count==5)
                    strcpy(string_values[i].nitrate,field);
                if(field_count==6)
                    strcpy(string_values[i].salinity,field);
                if(field_count==7)
                    strcpy(string_values[i].oxygen,field);

                field = strtok(NULL, ",");
                field_count++;
            }
            i++;

    }
    fclose(file);

    for(int i=0; i<1405; i++)
    {
       strcpy(float_values[i].date2,string_values[i].date);
       float_values[i].temp2=atof(string_values[i].temp);
       float_values[i].phosphate2=atof(string_values[i].phosphate);
       float_values[i].silicate2=atof(string_values[i].silicate);       //for loop for converting the strings to floats in order to compare them
       float_values[i].nitrite2=atof(string_values[i].nitrite);
       float_values[i].nitrate2=atof(string_values[i].nitrate);
       float_values[i].salinity2=atof(string_values[i].salinity);
       float_values[i].oxygen2=atof(string_values[i].oxygen);

    }

   // printMeasurments(string_values);
  //printMeasurments2(float_values);       //functions in order to print the string data struct or the float_string data struct.
















    return 0;
}

void printMeasurments(string_measurements string_values[])
{
    for(int i=0; i<1405; i++)
    {
        printf("%s %s %s %s ",string_values[i].date,string_values[i].temp,string_values[i].phosphate,string_values[i].silicate);
        printf("%s %s %s %s \n",string_values[i].nitrite,string_values[i].nitrate,string_values[i].salinity,string_values[i].oxygen);

    }
}

void printMeasurments2(float_measurements float_values[])
{
    for(int i=0; i<1405; i++)
    {
       printf("%s %.2f %.2f %.2f ",float_values[i].date2,float_values[i].temp2,float_values[i].phosphate2,float_values[i].silicate2);
       printf("%.2f %.2f %.2f %.2f \n",float_values[i].nitrite2,float_values[i].nitrate2,float_values[i].salinity2,float_values[i].oxygen2);

    }
}

