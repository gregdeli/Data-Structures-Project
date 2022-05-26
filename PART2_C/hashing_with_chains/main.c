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
    struct node* next; //pointer to next node
    struct node* tail; //pointer to last node
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

bool  is_empty(node n)
{
    if(n.temp == 200) return true;
    else return false;
}

void insert(node new_node, node hash_table[])
{
    int index = hash_function(new_node);

    if(!is_empty(hash_table[index]))
    {
        //node* node_pointer = hash_table[index].p;
        //if the pointer of the node in position (index) of the hash table is null then make iy point to the new node
        if(hash_table[index].next==NULL)
        {
            hash_table[index].next = &new_node;
            hash_table[index].tail = &new_node;
        }

        else
        {
            (*hash_table[index].tail).next = &new_node;
            hash_table[index].tail = &new_node;
            /*while(node_pointer != NULL)
            {
                //if the pointer of the node that is being pointed by the node_pointer is null the make it point to the new node
                if((*node_pointer).p==NULL)
                {
                    (*node_pointer).p = &new_node;
                    node_pointer = NULL;
                }
                else
                    node_pointer = (*node_pointer).p;
            }*/

        }

    }
    //if hash table at position (index) is empty insert the new node
    else hash_table[index] = new_node;

}

node measurement_to_node(measurements m)
{
    node n;
    strcpy(n.date, m.date);
    n.temp = m.temp;
    n.next = NULL;
    n.tail = NULL;
    return n;
}

/*void build_hash_table(measurements values[], int size_of_values, node hash_table[])
{
    for(int i=0; i<size_of_values; i++)
    {
        node new_node = measurement_to_node(values[i]);
        insert(&new_node, hash_table);
    }
}*/


int main()
{
    FILE *file = fopen("ocean.csv", "r");
    measurements values[1405];
    read_file(file, values);
    int size = sizeof(values)/sizeof(values[0]);
    print_measurments(values);
    node hash_table[11]; //because h(node) = ... mod11
    //initialize hash table with node that have an impossible temp value so that we can check later if hash_table[i] "is empty"
    node initial_node;
    initial_node.temp = 200;
    for(int i=0; i<11; i++)
        hash_table[i] = initial_node;
    //build node array an array with all the measurments in node form
    node node_array[size];
    for(int i=0; i<size; i++)
    {
        node_array[i] = measurement_to_node(values[i]);
    }
    //build_hash_table
    for(int i=0; i<size; i++)
    {
        insert(node_array[i], hash_table);
    }

    /*node node1;
    node node2;
    node node3;
    node node4;
    strcpy(node1.date, "1/1/2012");
    strcpy(node2.date, "1/1/2012");
    strcpy(node3.date, "1/1/2014");
    strcpy(node4.date, "1/1/2014");
    node1.temp = 16.5;
    node2.temp = 16.6;
    node3.temp = 16.7;
    node4.temp = 16.8;
    //na to kanw na pairnei pointer se node
    insert(&node1, hash_table);
    insert(&node2, hash_table);
    insert(&node3, hash_table);
    insert(&node4, hash_table);*/
    return 0;
}
