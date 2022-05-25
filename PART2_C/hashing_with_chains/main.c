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

void build_hash_table(measurements values[])
{

}
bool  is_empty(node n)
{
    if(n.temp == 200) return true;
    else return false;
}

void insert(node new_node, node hash_table[])
{
    new_node.p = NULL;
    int index = hash_function(new_node);
    if(!is_empty(hash_table[index]))
    {
        node* node_pointer = hash_table[index].p;
        if(node_pointer==NULL)
            hash_table[index].p = &new_node;
        else
        {
            while(node_pointer != NULL)
            {
                if((*node_pointer).p==NULL)
                {
                    (*node_pointer).p = &new_node;
                    node_pointer = NULL;
                }
                else
                    node_pointer = (*node_pointer).p;
            }

        }

    }
    else hash_table[index] = new_node;

}


int main()
{
    FILE *file = fopen("ocean.csv", "r");
    measurements values[1405];
    read_file(file, values);
    print_measurments(values);
    node initial_node;
    initial_node.temp = 200;
    node hash_table[11]; //because h(node) = ... mod11
    //initialize hash table with node that have an impossible temp value so that we can check later if hash_table[i] "is empty"
    for(int i=0; i<11; i++)
        hash_table[i] = initial_node;
    node node1;
    node node2;
    node node3;
    node node4;
    strcpy(node1.date, "1/1/2012");
    strcpy(node2.date, "1/1/2012");
    strcpy(node3.date, "1/1/2012");
    strcpy(node4.date, "1/1/2012");
    node1.temp = 16.5;
    node2.temp = 16.6;
    node2.temp = 16.7;
    node2.temp = 16.8;
    insert(node1, hash_table);
    insert(node2, hash_table);
    insert(node3, hash_table);
    insert(node4, hash_table);
    return 0;
}
