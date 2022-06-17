#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "avl_date.h"
#include "common.h"



void printInorder(AVL_Node_a *avl_node)
{
    if(avl_node!=NULL)
    {
        printInorder(avl_node->node_left);
        printf("%s\n",avl_node->node_key_date); //function to print the Inorder Traversal of the tree
        printInorder(avl_node->node_right);      // (Left, Root , Right)
    }
}
int getbalance_a(AVL_Node_a *avl_node) //function to measure balance
{
    int right_height,left_height;

    if(avl_node==NULL)
    return(0);                    //we measure the left and right height of each node

    if(avl_node->node_left==NULL)
    left_height=0;                    //if the node hasn't a left child then the left height is zero
    else
    left_height=1+avl_node->node_left->height;

    //if the node has a left child then the left height 1+ the child's height
    if(avl_node->node_right==NULL)
    right_height=0; //if the node hasn't a right child then the left height is zero
    else
    right_height=1+avl_node->node_right->height;
    //if the node has a right child then the right height 1+ the child's height

    return(right_height-left_height); //balance = hr-hl
}
int getheight_a(AVL_Node_a *avl_node) //function to get height
{
    int right_height,left_height;

    if(avl_node==NULL)
    return(0);

    if(avl_node->node_left==NULL)
    left_height=0;
    else
    left_height=1+avl_node->node_left->height;

    if(avl_node->node_right==NULL)
    right_height=0;
    else
    right_height=1+avl_node->node_right->height;

    if(left_height>right_height) //we take the level of the child with the biggest height
    return(left_height);

    return(right_height);
}

struct AVL_Node_a *AVL_search_a(struct AVL_Node_a* avl_node,char avl_key[50])
{
    if((avl_node == NULL) || compare_datesSort(avl_node->node_key_date,avl_key)==0) //if the node is the same with the root then return the root
    return avl_node;

    if(compare_datesSort(avl_node->node_key_date,avl_key)==-1)    //if the key of the node is smaller than the given key then you go to the right
    return AVL_search_a(avl_node->node_right, avl_key);

    return AVL_search_a(avl_node->node_left, avl_key);  //else you go to the left
}



struct AVL_Node_a *AVL_left_rotation_a(struct AVL_Node_a *avl_node)
{
    AVL_Node_a *newnode;
    newnode=avl_node->node_right;

    avl_node->node_right=newnode->node_left;
                                  //left rotation function
    newnode->node_left=avl_node;  //   avl_node
                                  //     /  \
                                  //    t1   newnode                             newnode
                                  //            /  \                left         /    \
                                  //            t2  t3              -->      avl_node  t3
                                  //                  \                          /  \    \
                                  //                   t4                      t1   t2    t4
    avl_node->height=getheight_a(avl_node);
    newnode->height=getheight_a(newnode); //updating the heights
    return(newnode); //return new root
}

void delay(int number_of_seconds) //function to make a delay. Only for printf(); purposes
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}


struct AVL_Node_a *AVL_right_rotation_a(struct AVL_Node_a *avl_node)
{
    struct AVL_Node_a *newnode;
    newnode=avl_node->node_left;                  //right rotation function
    avl_node->node_left=newnode->node_right;      //            avl_node
    newnode->node_right=avl_node;                //             /   \
                                                //       newnode    t1                      newnode
                                                //        /  \                  right        /  \
                                                //       t3   t2                -->        t3   avl_node
                                                //      /                                  /      /  \
                                                //     t4                                 t4    t2    t1
    avl_node->height=getheight_a(avl_node);
    newnode->height=getheight_a(newnode); //updating the heights
    return (newnode); //return new root
}

struct AVL_Node_a *AVL_left_left_rotation_a(struct AVL_Node_a *avl_node)
{
    avl_node=AVL_right_rotation_a(avl_node);  //if we have a left left case we need to rotate right
    return(avl_node);
}

struct AVL_Node_a *AVL_right_right_rotation_a(struct AVL_Node_a *avl_node)
{
    avl_node=AVL_left_rotation_a(avl_node); //if we have a right right case we need to rotate left
    return(avl_node);
}

struct AVL_Node_a *AVL_left_right_rotation_a(struct AVL_Node_a *avl_node)
{
    avl_node->node_left=AVL_left_rotation_a(avl_node->node_left); //if we have a left right case we need to rotate left the left child and then right rotate
    avl_node=AVL_right_rotation_a(avl_node);
    return(avl_node);
}

struct AVL_Node_a *AVL_right_left_rotation_a(struct AVL_Node_a *avl_node)
{
    avl_node->node_right=AVL_right_rotation_a(avl_node->node_right); //if we have a right left case we need to rotate right the right child and then left
    avl_node=AVL_left_rotation_a(avl_node);
    return(avl_node);
}

//We also added the LevelOrder Traversal which prints the avl based on the nodes in each level
void printLevelOrder(struct AVL_Node_a* root)
{
    int h = getheight_a(root)+1;
    int i;
    for (i = 1; i <= h; i++)
    printCurrentLevel(root, i);
}

int compare_datesSort(char date1_s[], char date2_s[]) //function to compare 2 dates. if date1>date2 = 1 , if date1<date2 = -1, if date1==date2 = 0
{
    date date1; //make 2 date structs
    date date2;
    char temp_date1[20]; //cant use strtok() on the original date string because it will change it
    char temp_date2[20];
    strcpy(temp_date1,date1_s);
    strcpy(temp_date2,date2_s);
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
    char *temp2 = strtok(temp_date2, "/");
    for(int i = 0; i<3; i++)
    {
        if(i == 0)
        {
            date2.month = atoi(temp2);
        }
        if(i == 1)
        {
            date2.day = atoi(temp2);
        }
        if(i == 2)
        {
            date2.year = atoi(temp2);
        }
        temp2 = strtok(NULL, "/");
    }

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

void printCurrentLevel(struct AVL_Node_a *root, int level) // function to help as to  print the Level Order representation of the tree
{
    if(level==0)
    printf("\n");
    if (root == NULL)
    return;

    if (level == 1)
    {
        printf("\n");
        printf("%s", root->node_key_date);
    }
    else if (level > 1)
    {
        printCurrentLevel(root->node_left, level - 1);
        printCurrentLevel(root->node_right, level - 1);
    }
}

struct AVL_Node_a * AVL_creation_a(struct AVL_Node_a* avl_node,char avl_key[50],float avl_temp) //Function that returns the structs root pointer so we can create
{                                                                                        //the avl tree through binary insertion and rebalancing when needed.
    if(avl_node==NULL) //We crate the Node and set its left and right
    {                 // child nodes to null.
        avl_node = (struct AVL_Node_a*)malloc(sizeof(struct AVL_Node_a));//WE HAVE TO ALLOCATE MEMORY DYNAMICALLY INTO THE HEAP!!!

        strcpy(avl_node->node_key_date,avl_key); //new node has to have null children and its key and temp values
        avl_node->node_right = NULL;
        avl_node->node_left = NULL;                    //    node_key_date
        avl_node->node_temp=avl_temp;                 //        /  \
                                                     //    NULL   NULL
    }

    else if(compare_datesSort(avl_key , avl_node->node_key_date)==-1) //if the key we want to insert is smaller than the root then it goes to the left
    {
        avl_node->node_left = AVL_creation_a(avl_node->node_left,avl_key,avl_temp);
        if(getbalance_a(avl_node)==-2) //if the insertion creates any imbalance we have to rebalance our avl tree! if it is -2 then it leans to the left
        if(compare_datesSort(avl_key , avl_node->node_left->node_key_date)==-1) // if the key we want to add is smaller than the left child it means it will go to the left
        avl_node=AVL_left_left_rotation_a(avl_node);                              //so we just have to do a left left rotation
        else
        avl_node=AVL_left_right_rotation_a(avl_node); // if the key we want to add is greater than the left child it means it will go to the right and it will ruin our tree
                                                   //so we just have to do a left right rotation
    }


    else if(compare_datesSort(avl_key , avl_node->node_key_date)==1)
    {
        avl_node->node_right = AVL_creation_a(avl_node->node_right,avl_key,avl_temp);
        if(getbalance_a(avl_node)==2) //if the insertion creates any imbalance we have to rebalance our avl tree! if it is 2 then it leans to the right
        if(compare_datesSort(avl_key , avl_node->node_right->node_key_date)==1)// if the key we want to add is greater than the right child it means it will go to the right
        avl_node=AVL_right_right_rotation_a(avl_node); //so we just have to do a right right rotation
        else
        avl_node=AVL_right_left_rotation_a(avl_node); // if the key we want to add is smaller than the right child it means it will go to the left and it will ruin our tree
                                                    //so we just have to do a right left rotation
    }

    avl_node->height=getheight_a(avl_node); //we update heights
    return(avl_node);
}


struct AVL_Node_a * AVL_delete(struct AVL_Node_a* avl_node,char avl_key[50])
{
    //there are some cases we need to take into mind

    struct AVL_Node_a *newnode;

    if(avl_node==NULL)
    {
        return NULL; //if the node doesn't exist
    }

    else if(compare_datesSort(avl_node->node_key_date,avl_key)==-1) // if the key is greater than the node
    {

        avl_node->node_right=AVL_delete(avl_node->node_right,avl_key);  // we know that we have to search the right part

        if(getbalance_a(avl_node)==-2) //if the deletion creates any imbalance we have to rebalance our avl tree! if it is -2 then it leans to the left
        if(getbalance_a(avl_node->node_left)<=0) //if the balance of the left child is smaller than zero it means it leans to the left
        avl_node=AVL_left_left_rotation_a(avl_node); //so we just have to do a left left rotation
        else
        avl_node=AVL_left_right_rotation_a(avl_node);// if the left child leans to the right it means  it will ruin our tree
                                                   //so we just have to do a left right rotation

    }

    else if(compare_datesSort(avl_node->node_key_date,avl_key)==1)// if the key is smaller than the node
    {
        avl_node->node_left=AVL_delete(avl_node->node_left,avl_key);  // we know  that we have to search the left part


        if(getbalance_a(avl_node)==2) //if the deletion creates any imbalance we have to rebalance our avl tree! if it is 2 then it leans to the right
        {

            if(getbalance_a(avl_node->node_right)>=0) //if the balance of the right child is greater than zero it means it leans to the right
            avl_node=AVL_right_right_rotation_a(avl_node); //so we just have to do a right right rotation
            else
            avl_node=AVL_right_left_rotation_a(avl_node);// if the right child leans to the left it means it will ruin our tree
                                             //so we just have to do a right left rotation

        }
    }

    else
    {

        if(avl_node->node_right!=NULL)
        {
            newnode=avl_node->node_right;  // if we have 2 children we replace the father with the smallest node on the right subtree

            while(newnode->node_left!=NULL)
            newnode=newnode->node_left;

            strcpy(avl_node->node_key_date,newnode->node_key_date);
            avl_node->node_right=AVL_delete(avl_node->node_right,newnode->node_key_date);

            if(getbalance_a(avl_node)==-2)           //we check for imbalance
            {
                if(getbalance_a(avl_node->node_left)<=0)
                avl_node=AVL_left_left_rotation_a(avl_node);
                else
                avl_node=AVL_left_right_rotation_a(avl_node);
            }
        }

        else return(avl_node->node_left);
    }

    avl_node->height=getheight_a(avl_node);
    return(avl_node);
}

AVL_Node_a* load_avl_a(measurements values[], AVL_Node_a *avl)
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


    for(int i=0; i<1405; i++)
    {
        avl=AVL_creation_a(avl,values[i].date,values[i].temp);
    }
    return avl;

}

int menu_a(AVL_Node_a *avl)
{
    int input,input1,input5,input6,input8,input9,input10;
    char input2[50];
    char input3[50];
    char input7[50];
    float input4;
    bool loop=false;
    bool loop1=false;
    bool loop2=false;
    bool loop3=false;
    bool loop4=false;
    bool loop5=false;
    bool loop6=false;
    bool loop7=false;

    printf("Hello, welcome.\n");
    printf("1.Represenation of the avl tree.\n");
    printf("2.Search.\n");
    printf("3.Modify.\n");
    printf("4.Delete.\n");
    printf("5.Exit.\n");
    do
    {
        printf("What action would you like to choose?: ");
        scanf("%d",&input);
        while((getchar()) != '\n');
        printf("\n");

        switch (input)
        {
            case 1:
            printf("1.Inorder Traversal.");
            printf("\n2.Level Order Traversal.");
            printf("\n3.Back");
            printf("\n4.Exit");
            do{
                printf("\nWhat traversal would you like to see?: ");
                scanf("%d",&input1);
                while((getchar()) != '\n');
                printf("\n");
                switch (input1)
                {
                    case 1:
                    printf("Reading ocean.csv...");
                    for (int i = 0; i < 3; i++)
                    delay(1);
                    printf("\n\nInorder traversal of the constructed AVL tree is :\n");
                    printInorder(avl);

                    printf("\n1.Back");
                    printf("\n2.Exit");
                    do{
                        printf("\nWhat action would you like to choose?: ");
                        scanf("%d",&input9);
                        while((getchar()) != '\n');
                        printf("\n");
                        switch(input9)
                        {
                            case 1:
                            menu_a(avl);
                            break;

                            case 2:
                            printf("Exiting...");
                            for (int i = 0; i < 3; i++)
                            delay(1);
                            return 0;
                            break;

                            default:
                            printf("Wrong Input!\n");
                            loop2=true;
                        }
                    }while(loop2);
                    break;

                    case 2:
                    printf("Reading ocean.csv...");
                    for (int i = 0; i < 3; i++)
                    delay(1);
                    printf("\n\nLevel Order traversal of the constructed AVL tree is :\n");
                    printLevelOrder(avl);
                    printf("\n\n1.Back");
                    printf("\n2.Exit");
                    do
                    {
                        printf("\nWhat action would you like to choose?: ");
                        scanf("%d",&input10);
                        while((getchar()) != '\n');
                        printf("\n");
                        switch(input10)
                        {
                            case 1:
                            menu_a(avl);
                            break;

                            case 2:
                            printf("Exiting...");
                            for (int i = 0; i < 3; i++)
                            delay(1);
                            return 0;
                            break;

                            default:
                            printf("Wrong Input!\n");
                            loop3=true;
                        }
                    }while(loop3);
                    break;

                    case 3:
                    menu_a(avl);
                    break;

                    case 4:
                    printf("Exiting...");
                    for (int i = 0; i < 3; i++)
                    delay(1);
                    return 0;
                    break;

                    default:
                    printf("Wrong Input!\n");
                    loop1=true;
                }
            }while(loop1);

            break;

            case 2:
            printf("What date would you like to search? : ");
            scanf("%s",input2);

            printf("\n");
            if(AVL_search_a(avl,input2)==NULL)
            printf("The date %s does not exist!!\n",input2);
            else printf("\nIn %s the temperature of the ocean was  %.2f \n",input2,AVL_search_a(avl,input2)->node_temp);
            printf("\n1.Back");
            printf("\n2.Exit");
            do{
                printf("\nWhat action would you like to choose?: ");
                scanf("%d",&input6);
                while((getchar()) != '\n');
                printf("\n");
                switch(input6)
                {
                    case 1:
                    menu_a(avl);
                    break;

                    case 2:
                    printf("Exiting...");
                    for (int i = 0; i < 3; i++)
                    delay(1);
                    return 0;
                    break;

                    default:
                    printf("Wrong Input!\n");
                    loop4=true;
                }
            }while(loop4);

            break;


            case 3:
            printf("\nWhat date would you like to search? : ");
            scanf("%s",input3);
            printf("\n");
            if(AVL_search_a(avl,input3)==NULL)
            printf("The date %s does not exist!!\n",input3);
            else{
                printf("\nIn %s the temperature of the ocean was  %.2f \n",input3,AVL_search_a(avl,input3)->node_temp);
                do{
                    loop5=false;
                    printf("\nWhat would you like to be your new temperature? : ");
                    if(scanf("%f",&input4)!=1)
                    {
                        while((getchar()) != '\n');
                        loop5=true;
                        printf("\nWrong Input -- Only floats please!\n");
                    }
                }while(loop5);

                printf("\n");
                AVL_search_a(avl,input3)->node_temp=input4;
                printf("\nIn %s the temperature of the ocean was  %.2f \n",input3,AVL_search_a(avl,input3)->node_temp);
            }
            printf("\n1.Back");
            printf("\n2.Exit");
            do{

                printf("\nWhat action would you like to choose?: ");
                scanf("%d",&input5);
                while((getchar()) != '\n');
                printf("\n");
                switch(input5)
                {
                    case 1:
                    menu_a(avl);
                    break;

                    case 2:
                    printf("Exiting...");
                    for (int i = 0; i < 3; i++)
                    delay(1);
                    return 0;
                    break;

                    default:
                    printf("Wrong Input!\n");
                    loop6=true;
                }
            }while(loop6);
            break;

            case 4:
            printf("What date would you like to delete? : ");
            scanf("%s",input7);
            printf("\n");
            if(AVL_search_a(avl,input7)==NULL)
            printf("The date %s does not exist!!\n",input7);
            else{
                avl=AVL_delete(avl,input7);
                printf("\nThe date has been deleted succesfully!\n");
            }
            printf("\n1.Back");
            printf("\n2.Exit");
            do{
                printf("\nWhat action would you like to choose?: ");
                scanf("%d",&input8);
                while((getchar()) != '\n');
                printf("\n");
                switch(input8)
                {
                    case 1:
                    menu_a(avl);
                    break;

                    case 2:
                    printf("Exiting...");
                    for (int i = 0; i < 3; i++)
                    delay(1);
                    return 0;
                    break;

                    default:
                    printf("Wrong Input!\n");
                    loop7=true;
                }
            }while(loop7);
            break;

            case 5:
            printf("Exiting...");
            for (int i = 0; i < 3; i++)
            delay(1);
            return 0;
            break;

            default:
            printf("Wrong Input!\n");
            loop=true;
        }
    }while(loop);
}

void printMeasurments(measurements values[])
{
for(int i=0; i<1405; i++)
{

printf("%s %.2f %.2f %.2f ",values[i].date,values[i].temp,values[i].phosphate,values[i].silicate);
printf("%.2f %.2f %.2f %.2f\n",values[i].nitrite,values[i].nitrate,values[i].salinity,values[i].oxygen);
}
}
