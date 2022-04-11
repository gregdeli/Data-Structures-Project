#include <stdio.h>
#include <stdlib.h>

typedef struct Measurements{
    char date[50],temp[50], phosphate[50];
    char silicate[50],  nitrite[50], nitrate[50];
    char salinity[50],  oxygen[50];

}measurements;

typedef struct Measurements2{
    char date2[50];
    float temp2, phosphate2;
    float silicate2,  nitrite2, nitrate2;
    float salinity2,  oxygen2;

}measurements2;

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
    measurements2 values2[1405];
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

    for(int i=0; i<1405; i++)
    {
       strcpy(values2[i].date2,values[i].date);
       values2[i].temp2=atof(values[i].temp);
       values2[i].phosphate2=atof(values[i].phosphate);
       values2[i].silicate2=atof(values[i].silicate);
       values2[i].nitrite2=atof(values[i].nitrite);
       values2[i].nitrate2=atof(values[i].nitrate);
       values2[i].salinity2=atof(values[i].salinity);
       values2[i].oxygen2=atof(values[i].oxygen);

    }

   // printMeasurments(values);
    printMeasurments2(values2);


    return 0;
}

void printMeasurments(measurements values[])
{
    for(int i=0; i<1405; i++)
    {
        printf("%s %s %s %s ",values[i].date,values[i].temp,values[i].phosphate,values[i].silicate);
        printf("%s %s %s %s \n",values[i].nitrite,values[i].nitrate,values[i].salinity,values[i].oxygen);

    }
}

void printMeasurments2(measurements2 values2[])
{
    for(int i=0; i<1405; i++)
    {
       printf("%s %.2f %.2f %.2f ",values2[i].date2,values2[i].temp2,values2[i].phosphate2,values2[i].silicate2);
       printf("%.2f %.2f %.2f %.2f \n",values2[i].nitrite2,values2[i].nitrate2,values2[i].salinity2,values2[i].oxygen2);

    }
}

