#ifndef HASHING_H
#define HASHING_H
#include <stdbool.h>
#include "common.h"

typedef struct measurements_hashing
{
    char date[20];
    float temp;
}measurements_hashing;

typedef struct node
{
    char date[20];
    float temp;
    struct node* next; //pointer to next node
    struct node* tail; //pointer to last node
    bool is_head;
}node;


//We declare the functions that we we will use
void delay(int number_of_seconds);
void read_file(FILE *file, measurements_hashing values[]);
void print_measurments(measurements_hashing values[]);
date dateString_to_dateStruct(char date1_s[]);
int compare_dates(char date1_s[], char date2_s[]);
void clear_console();
int hash_function(node node1);
bool  is_empty(node n);
void insert(node* new_node, node hash_table[]);
float access_temp(char date[], node hash_table[]);
int edit_temp(char date[],float new_temp, node hash_table[]);
int delete_measurement(char date[], node hash_table[]);
node measurement_to_node(measurements_hashing m);
void menu_h();


#endif  HASHING_H


