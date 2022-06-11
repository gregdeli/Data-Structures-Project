#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>

typedef struct date{
    int month;
    int day;
    int year;
}date;

    typedef struct AVL_Node   //struct for the node of our avl tree
    {
    struct AVL_Node *node_left;
    struct AVL_Node *node_right;
    int height;
    char node_date[50];
    float node_key_temp;
    char *node_new_date;
    }AVL_Node;

typedef struct measurements{ //struct with floats and string only for the date
        char date[50];
        float temp, phosphate;
        float silicate,  nitrite, nitrate;
        float salinity,  oxygen;

    }measurements;


    int getheight( AVL_Node *);
    AVL_Node *rotateright(AVL_Node *);                    //We declare the functions that we we will use
     AVL_Node *rotateleft(AVL_Node *);
     AVL_Node *AVL_right_right_rotation(AVL_Node*);
     AVL_Node *AVL_left_left_rotation(AVL_Node *);
     AVL_Node *AVL_left_right_rotation(AVL_Node *);
     AVL_Node *AVL_right_left_rotation(AVL_Node *);
     int getbalance(AVL_Node *);
     void printLevelOrder(AVL_Node*);
     void printMeasurments2(measurements[]);

      void menu(struct AVL_Node *);
      int compare_datesSort(char [], char []);
      AVL_Node *creation(AVL_Node *,char[50],float);
      float maximum(AVL_Node *);
      float minimum(AVL_Node *);

    int getbalance(AVL_Node *avl_node) //function to measure balance
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
int getheight(AVL_Node *avl_node) //function to get height
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
float maximum(struct AVL_Node* avl_node)
{
    if (avl_node == NULL)
        return LONG_MIN;

    float max = avl_node->node_key_temp;

    float max_left = maximum(avl_node->node_left);

    float max_right = maximum(avl_node->node_right);

    if (max_left > max)
        max = max_left;

    if (max_right > max)
        max = max_right;
    return max;

}
float minimum(struct AVL_Node* avl_node)
{

    if (avl_node==NULL)
      return LONG_MAX;

    float max = avl_node->node_key_temp;

    float max_left = minimum(avl_node->node_left);

    float max_right = minimum(avl_node->node_right);

    if (max_left < max)
      max = max_left;

    if (max_right < max)
      max = max_right;

    return max;
}
   struct AVL_Node *AVL_search(struct AVL_Node* avl_node,float avl_key)
   {
       if((avl_node == NULL) || avl_node->node_key_temp==avl_key) //if the node is the same with the root then return the root
        return avl_node;

        if(avl_node->node_key_temp<avl_key)    //if the key of the node is smaller than the given key then you go to the right
        return AVL_search(avl_node->node_right, avl_key);

       return AVL_search(avl_node->node_left, avl_key);  //else you go to the left
   }



 struct AVL_Node *AVL_left_rotation(struct AVL_Node *avl_node)
    {
    AVL_Node *newnode;
    newnode=avl_node->node_right;

    avl_node->node_right=newnode->node_left;
                                                      //left rotation function
     newnode->node_left=avl_node;                    //   avl_node
                                                      //     /  \
                                                      //    t1   newnode                             newnode
                                                      //            /  \                left         /    \
                                                      //            t2  t3              -->      avl_node  t3
                                                      //                  \                          /  \    \
                                                      //                   t4                      t1   t2    t4
avl_node->height=getheight(avl_node);
newnode->height=getheight(newnode); //updating the heights
      return(newnode); //return new root
    }
    void delay(int number_of_seconds) //function to make a delay. Only for printf(); purposes
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


        struct AVL_Node *AVL_right_rotation(struct AVL_Node *avl_node)
   {
    struct AVL_Node *newnode;
     newnode=avl_node->node_left;                  //right rotation function
      avl_node->node_left=newnode->node_right;      //            avl_node
       newnode->node_right=avl_node;                //             /   \
                                                    //       newnode    t1                      newnode
                                                    //        /  \                  right        /  \
                                                    //       t3   t2                -->        t3   avl_node
                                                    //      /                                  /      /  \
                                                    //     t4                                 t4    t2    t1
avl_node->height=getheight(avl_node);
newnode->height=getheight(newnode); //updating the heights
    return (newnode); //return new root
   }

struct AVL_Node *AVL_left_left_rotation(struct AVL_Node *avl_node)
{
avl_node=AVL_right_rotation(avl_node);  //if we have a left left case we need to rotate right
return(avl_node);
}

struct AVL_Node *AVL_right_right_rotation(struct AVL_Node *avl_node)
{
avl_node=AVL_left_rotation(avl_node); //if we have a right right case we need to rotate left
return(avl_node);
}

struct AVL_Node *AVL_left_right_rotation(struct AVL_Node *avl_node)
{
avl_node->node_left=AVL_left_rotation(avl_node->node_left); //if we have a left right case we need to rotate left the left child and then right rotate
avl_node=AVL_right_rotation(avl_node);
return(avl_node);
}

struct AVL_Node *AVL_right_left_rotation(struct AVL_Node *avl_node)
{
avl_node->node_right=AVL_right_rotation(avl_node->node_right); //if we have a right left case we need to rotate right the right child and then left
avl_node=AVL_left_rotation(avl_node);
return(avl_node);
}

struct AVL_Node * AVL_creation(struct AVL_Node* avl_node,char avl_date[50],float avl_key) //Function that returns the structs root pointer so we can create
{                                                                      //the avl tree through binary insertion and rebalancing when needed.
    if(avl_node==NULL) //We crate the Node and set its left and right
    {                 // child nodes to null.
      avl_node = (struct AVL_Node*)malloc(sizeof(struct AVL_Node));//WE HAVE TO ALLOCATE MEMORY DYNAMICALLY INTO THE HEAP!!!

   avl_node->node_key_temp=avl_key; //new node has to have null children and its key and temp values
    avl_node->node_right = NULL;
    avl_node->node_left = NULL;                    //    node_key_temp
    strcpy(avl_node->node_date,avl_date);                 //    /  \
                                                    //    NULL   NULL

    avl_node->node_new_date= (char *)malloc(sizeof(char*)*11);
    //avl_node->node_new_date= realloc(avl_node->node_new_date,sizeof(char*)*15);
    }

            else if(avl_key<avl_node->node_key_temp) //if the key we want to insert is smaller than the root then it goes to the left
        {
            avl_node->node_left = AVL_creation(avl_node->node_left,avl_date,avl_key);
            if(getbalance(avl_node)==-2) //if the insertion creates any imbalance we have to rebalance our avl tree! if it is -2 then it leans to the left
            if(avl_key<avl_node->node_left->node_key_temp) // if the key we want to add is smaller than the left child it means it will go to the left
            avl_node=AVL_left_left_rotation(avl_node);                              //so we just have to do a left left rotation
            else
             avl_node=AVL_left_right_rotation(avl_node); // if the key we want to add is greater than the left child it means it will go to the right and it will ruin our tree
            }                                            //so we just have to do a left right rotation


        else if(avl_key>avl_node->node_key_temp)
        {
            avl_node->node_right = AVL_creation(avl_node->node_right,avl_date,avl_key);
            if(getbalance(avl_node)==2) //if the insertion creates any imbalance we have to rebalance our avl tree! if it is 2 then it leans to the right
            if(avl_key> avl_node->node_right->node_key_temp)// if the key we want to add is greater than the right child it means it will go to the right
            avl_node=AVL_right_right_rotation(avl_node); //so we just have to do a right right rotation
            else
             avl_node=AVL_right_left_rotation(avl_node); // if the key we want to add is smaller than the right child it means it will go to the left and it will ruin our tree
                                                         //so we just have to do a right left rotation

        }
        else if(avl_key==avl_node->node_key_temp)
        {


          strcat(avl_node->node_new_date,avl_date);
          strcat(avl_node->node_new_date,", ");



        }

                avl_node->height=getheight(avl_node); //we update heights
            return(avl_node);



}


void menu(struct AVL_Node *avl){
int input,input1,input5,input6,input8,input9,input10;
        float input2,input3;
        char input7[50];
        float input4;
        bool loop=false;
        bool loop1=false;
        bool loop2=false;
        bool loop3=false;
        bool loop4=false;
        bool loop5=false;

        printf("Hello, welcome.\n");
        printf("1.Minimum or Maximum temperature.\n");
        printf("2.Search.\n");
        printf("3.Exit.\n");
        do
               {
        printf("What action would you like to choose?: ");
        scanf("%d",&input);
        while((getchar()) != '\n');
        printf("\n");


        switch (input)
        {
           case 1:
        loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
               printf("1.Minimum temperature.");
               printf("\n2.Maximum temperature.");
               printf("\n3.Back");
               printf("\n4.Exit");


               do
               {
               printf("\nWhat acrtion would you like to see?: ");
               scanf("%d",&input1);
               while((getchar()) != '\n');
            printf("\n");

               switch (input1)
               {
                  case 1:
             loop=false;

        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                      printf("Reading ocean.csv...");
                     for (int i = 0; i < 3; i++)
                     delay(1);
                 printf("\nWhen the ocean had the MINIMUM temperature of %.2f it was %s, %s",minimum(avl),AVL_search(avl,minimum(avl))->node_date,AVL_search(avl,minimum(avl))->node_new_date);


                 printf("\n1.Back");
             printf("\n2.Exit");
             do{
             printf("\nWhat actions would you like to choose?: ");
             scanf("%d",&input9);
             while((getchar()) != '\n');
             printf("\n");
             switch(input9)
             {
             case 1:
                 loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                menu(avl);
                break;
             case 2:
                 loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                printf("Exiting...");
                     for (int i = 0; i < 3; i++)
                     delay(1);
                     exit(0);
                     break;
                     default:
                    printf("Wrong Input!\n");
                   loop2=true;
             }
             }while(loop2);
                break;
                case 2:
                    loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                    printf("Reading ocean.csv...");
                     for (int i = 0; i < 3; i++)
                     delay(1);
                printf("\nWhen the ocean had the MAXIMUM temperature of %.2f it was %s, %s",maximum(avl),AVL_search(avl,maximum(avl))->node_date,AVL_search(avl,maximum(avl))->node_new_date);
                 printf("\n\n1.Back");
             printf("\n2.Exit");
             do{
             printf("\nWhat action would you like to choose?: ");
             scanf("%d",&input10);
             while((getchar()) != '\n');
             printf("\n");
             switch(input10)
             {
             case 1:
                 loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                menu(avl);
                break;
             case 2:
                 loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                printf("Exiting...");
                     for (int i = 0; i < 3; i++)
                     delay(1);
                     exit(0);
                     break;
                     default:
                    printf("Wrong Input!\n");
                    loop3=true;
             }
             }while(loop3);
                break;
                case 3:
                    loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                menu(avl);
                break;
                case 4:
                    loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                    printf("Exiting...");
                     for (int i = 0; i < 3; i++)
                     delay(1);
                     exit(0);
                     break;
                default:
     printf("Wrong Input!\n");
                    loop1=true;
               }
               }while(loop1);


            break;

           case 2:

        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
          loop=false;
            printf("What temp would you like to search? : ");
            scanf("%f",&input2);
            while((getchar()) != '\n');
            printf("\n");
            if(AVL_search(avl,input2)==NULL)
                printf("The temp %.2f does not exist!!\n",input2);
            else printf("\nWhen the ocean had %.2f temperature it was %s, %s",input2,AVL_search(avl,input2)->node_date,AVL_search(avl,input2)->node_new_date);



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
                 loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                menu(avl);
                break;
             case 2:
                 loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
                printf("Exiting...");
                     for (int i = 0; i < 3; i++)
                     delay(1);
                     exit(0);
                     break;
                     default:
                    printf("Wrong Input!\n");
                    loop4=true;
             }
             }while(loop4);

            break;

           case 3:
               loop=false;
        loop1=false;
        loop2=false;
        loop3=false;
        loop4=false;
        loop5=false;
               printf("Exiting...");
               for (int i = 0; i < 3; i++)
               delay(1);
               exit(0);
            break;

            default:
                    printf("Wrong Input!\n");
                        loop=true;

               }
        }while(loop);
}

int main()
{
    char array[50];
    float n=0;
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


    AVL_Node *avl=NULL;

    for(int i=0; i<1405; i++)
    {
      avl=AVL_creation(avl,values[i].date,values[i].temp); //printf("%.2f\n",values[i].temp2);
    }

    menu(avl); //Function to create the menu

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
