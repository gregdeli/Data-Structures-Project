#ifndef HASHING_H
#define HASHING_H

//We declare the functions that we we will use
void delay(int number_of_seconds);
void read_file(FILE *file, measurements values[]);
void print_measurments(measurements values[]);
date dateString_to_dateStruct(char date1_s[]);
int compare_dates(char date1_s[], char date2_s[]);
void clear_console();
int hash_function(node node1);
bool  is_empty(node n);
void insert(node* new_node, node hash_table[]);
float access_temp(char date[], node hash_table[]);
int edit_temp(char date[],float new_temp, node hash_table[]);
int delete_measurement(char date[], node hash_table[]);
node measurement_to_node(measurements m);
void menu_h(node hash_table[]);


#endif  HASHING_H

