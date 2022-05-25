#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



typedef struct measurements
{
    char date[20];
    float temp;
}measurements;

typedef struct node
{
    char date[20];
    float temp;
    struct node* p; //pointer to node
}node;



void read_file(FILE *file, measurements values[])
{
    if(!file)
      printf("Error");

    char buff1[1024]; //se auton ton pinaka apothikeuetai i kathe grammi k
    int row_count = 0;
    int field_count =0;


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
                values[i].temp = atof(field);

            field = strtok(NULL, ",");
        }
        i++;

    }
    fclose(file);
    //now I have an array of structs that contain the dates and temps from to ocean.csv
    return values;
}

void print_measurments(measurements values[])
{
    for(int i=0; i<1405; i++)
    {
        printf("%s \t%.2f\n",values[i].date, values[i].temp);
    }
}

int hash_function(node node1)
{
    char num = 'a';
    int sum = 0;
    int i=0;
    while(num != '\0')
    {
        num = node1.date[i];
        if(num=='/')
        {
            i++;
            continue;
        }
        sum += num;
        i++;
    }
    return sum % 11;
}



int main()
{
    FILE *file = fopen("ocean.csv", "r");
    measurements values[1405];
    read_file(file, values);
    print_measurments(values);
    node hash_table[11]; //because h(node) = ... mod11
    node node1;
    strcpy(node1.date, "1/1/2012");
    node1.temp = 16.5;
    int i = hash_function(node1);
    return 0;
}
