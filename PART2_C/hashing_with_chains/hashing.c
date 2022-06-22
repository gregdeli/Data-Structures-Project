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
    bool is_head;
}node;

typedef struct date{
    int month;
    int day;
    int year;
}date;

void delay(int number_of_seconds) //function to make a delay
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


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

date dateString_to_dateStruct(char date1_s[])
{
    date date1; //make 2 date structs
    char temp_date1[20]; //cant use strtok() on the original date string because it will change it
    strcpy(temp_date1,date1_s);
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
    return date1;
}

//if m1.date>m2.date it returns 1 if m1.date<m2.date -1 and if its equal it returns 0
int compare_dates(char date1_s[], char date2_s[])
{
    date date1; //make 2 date structs
    date date2;
    date1 = dateString_to_dateStruct(date1_s);
    date2 = dateString_to_dateStruct(date2_s);
    //comparison between the two date structs first by year then by month then by day
    if (date1.year < date2.year)
       return -1;

    else if (date1.year > date2.year)
       return 1;

    if (date1.year == date2.year)
    {
         if (date1.month<date2.month)
              return -1;
         else if (date1.month>date2.month)
              return 1;
         else if (date1.day<date2.day)
              return -1;
         else if(date1.day>date2.day)
              return 1;
         else
              return 0;
    }
}

void clear_console()
{
    #ifdef __linux__
        system("clear");
    #endif
    #ifdef _WIN32
        system("cls");
    #endif
    #ifdef __APPLE__
        system("clear");
    #endif
}

int hash_function(node node1)
{
    char num = 'a'; //initializing num
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

void insert(node* new_node, node hash_table[])
{
    int index = hash_function(*new_node);

    if(!is_empty(hash_table[index]))
    {
        if(hash_table[index].next==NULL)
        {
            hash_table[index].next = new_node;
            hash_table[index].tail = new_node;
        }

        else
        {
            (*hash_table[index].tail).next = new_node;
            hash_table[index].tail = new_node;
        }

    }
    //if hash table at position (index) is empty insert the new node
    else
    {
        (*new_node).is_head = true;
        hash_table[index] = (*new_node);
    }
}

float access_temp(char date[], node hash_table[]) //returns temp
{
    node n;
    strcpy(n.date, date);
    int index = hash_function(n);
    node* p_to_node; //pointer to node
    p_to_node = &hash_table[index];
    if((*p_to_node).temp==200) return 200; //if temp=200 then there is not a valid node in hash_table[index]
    while((*p_to_node).next!=NULL)
    {
        if(compare_dates((*p_to_node).date, date)==0)
                return (*p_to_node).temp;
        else
            p_to_node = (*p_to_node).next;
        //if the last node on the chain doesn't contain the date you are looking for then it doesn't exist on the hash_table
        if((*p_to_node).next == NULL)
            return 200;
    }
}
//if date is not found return -1 else change the temp of the given date and return 1
int edit_temp(char date[],float new_temp, node hash_table[])
{
    node n;
    strcpy(n.date, date);
    int index = hash_function(n);
    node* p_to_node; //pointer to node
    p_to_node = &hash_table[index];
    if((*p_to_node).temp==200) return -1; //if temp=200 then there is not a valid node in hash_table[index]
    while((*p_to_node).next!=NULL)
    {
        if(compare_dates((*p_to_node).date, date)==0)
        {
            (*p_to_node).temp = new_temp;
            return 1;
        }
        else
            p_to_node = (*p_to_node).next;
        //if the last node on the chain doesn't contain the date you are looking for then it doesn't exist on the hash_table
        if((*p_to_node).next == NULL)
            return -1;
    }
}

int delete_measurement(char date[], node hash_table[])
{
    node n;
    strcpy(n.date, date);
    int index = hash_function(n);
    node* p_to_node; //pointer to node
    node* previous_node = NULL; //pointer to the previous node;
    p_to_node = &hash_table[index];
    if((*p_to_node).temp==200) return -1; //if temp=200 then there is not a valid node in hash_table[index]
    while((*p_to_node).next!=NULL)
    {
        if(compare_dates((*p_to_node).date, date)==0)
        {
            if((*p_to_node).is_head == true)
            {
                strcpy(hash_table[index].date, (*hash_table[index].next).date);
                hash_table[index].temp = (*hash_table[index].next).temp;
                hash_table[index].next = (*hash_table[index].next).next;
                return 1;
            }
            else
            {
                (*previous_node).next = (*p_to_node).next;
                return 1;
            }
        }
        else
        {
            previous_node = p_to_node;
            p_to_node = (*p_to_node).next;
        }
        //if the last node on the chain doesn't contain the date you are looking for then it doesn't exist on the hash_table
        if((*p_to_node).next == NULL)
            return -1;
    }
}

node measurement_to_node(measurements m)
{
    node n;
    strcpy(n.date, m.date);
    n.temp = m.temp;
    n.next = NULL;
    n.tail = NULL;
    n.is_head = false;
    return n;
}

void menu(node hash_table[])
{
    //menu
    int choice = 0;
    bool loop;
    do
    {
        loop = false;
        printf("Search Temperature: 1\n");
        printf("Edit Temperature: 2\n");
        printf("Delete Measurement: 3\n");
        printf("Exit: 4\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);
        while ((getchar()) != '\n');
        if((choice != 1) & (choice != 2) & (choice != 3) & (choice != 4))
        {
            loop = true;
            clear_console();
            continue;
        }
        char date[15];
        if(choice!=4)
        {
            printf("Enter a date(mm/dd/yy): ");
            scanf("%s", date);
        }
        switch(choice)
        {
            case 1:
                {
                    float temp = access_temp(date, hash_table);
                    if(temp==200)
                    {
                        //printf("error\n");
                        loop = true;
                        clear_console();
                        continue;
                    }
                    else
                    {
                        printf("The temperature on %s was %.2fC\n",date, temp);
                        printf("Continue: 1\n");
                        printf("Exit: 2\n");
                        char ch;
                        int choice1 = 0;
                        printf("Enter your choice: ");
                        scanf(" %d", &choice1);
                        while ((getchar()) != '\n');
                        if((choice1 != 1) & (choice1 != 2))
                        {
                            loop = true;
                            clear_console();
                            continue;
                        }
                        switch(choice1)
                        {
                            case 1:
                                loop = true;
                                printf("Press Enter to continue...");
                                scanf("%c", &ch);
                                clear_console();
                                continue;
                            case 2:
                                printf("Exiting...\n");
                                loop = false;
                                continue;
                        }

                    }
                }
            case 2:
                {
                    float old_temp = access_temp(date, hash_table);
                    float new_temp;
                    printf("Enter a new temperature: ");
                    if(scanf("%f", &new_temp)!=1)
                    while ((getchar()) != '\n');
                    {
                        printf("\n");
                        loop = true;
                        clear_console();
                        continue;
                    }
                    while ((getchar()) != '\n');
                    if(new_temp>=100)
                    {
                        loop = true;
                        printf("The temperature of the water can't be over 100C\n");
                        printf("Press Enter to continue...");
                        char ch = 'a';
                        scanf("%c", &ch);
                        clear_console();
                        continue;
                    }
                    int res = edit_temp(date, new_temp, hash_table);
                    if(res==-1)
                    {
                        loop = true;
                        clear_console();
                        continue;
                    }
                    else
                    {
                        printf("The temperature on %s was changed from %.2fC to %.2fC\n", date, old_temp, access_temp(date, hash_table));
                        printf("Continue: 1\n");
                        printf("Exit: 2\n");
                        char ch;
                        int choice1 = 0;
                        printf("Enter your choice: ");
                        scanf(" %d", &choice1);
                        while ((getchar()) != '\n');
                        if((choice1 != 1) & (choice1 != 2))
                        {
                            loop = true;
                            clear_console();
                            continue;
                        }
                        switch(choice1)
                        {
                            case 1:
                                loop = true;
                                printf("Press Enter to continue...");
                                scanf("%c", &ch);
                                clear_console();
                                continue;
                            case 2:
                                printf("Exiting...\n");
                                loop = false;
                                continue;
                        }
                    }
                }

            case 3:
                {
                    float temp = access_temp(date, hash_table);
                    if(temp==200)
                    {
                        printf("error\n");
                        loop = true;
                        clear_console();
                        continue;
                    }
                    int res = delete_measurement(date, hash_table);
                    if(res==-1)
                    {
                        loop = true;
                        clear_console();
                        continue;
                    }
                    else
                    {
                        printf("The measurement on %s when the temperature was %.2f was deleted\n", date, temp);
                        printf("Continue: 1\n");
                        printf("Exit: 2\n");
                        char ch;
                        int choice1 = 0;
                        printf("Enter your choice: ");
                        scanf(" %d", &choice1);
                        while ((getchar()) != '\n');
                        if((choice1 != 1) & (choice1 != 2))
                        {
                            loop = true;
                            clear_console();
                            continue;
                        }
                        switch(choice1)
                        {
                            case 1:
                                loop = true;
                                printf("Press Enter to continue...");
                                scanf("%c", &ch);
                                clear_console();
                                continue;
                            case 2:
                                printf("Exiting...\n");
                                loop = false;
                                continue;
                        }
                    }
                }
            case 4:
                printf("Exiting...\n");
                loop = false;
                break;

        }
    }
    while(loop);
}

main()
{
    FILE *file = fopen("ocean.csv", "r");
    measurements values[1405];
    read_file(file, values);
    int size = sizeof(values)/sizeof(values[0]);
    node hash_table[11]; //because h(node) = ... mod11
    //initialize hash table with node that have an impossible temp value so that we can check later if hash_table[i] "is empty"
    node initial_node;
    initial_node.temp = 200;
    for(int i=0; i<11; i++)
        {hash_table[i] = initial_node;}
    //build node array an array with all the measurments in node form so that each node is in a different place in memory
    node node_array[size];
    for(int i=0; i<size; i++)
        node_array[i] = measurement_to_node(values[i]);
    //build hash table
    for(int i=0; i<size; i++)
        insert(&node_array[i] ,hash_table);

    //menu
    menu(hash_table);

    return 0;
}
