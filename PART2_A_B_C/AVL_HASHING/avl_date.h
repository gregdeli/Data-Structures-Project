#ifndef AVL_DATE_H
#define AVL_DATE_H
#include "common.h"

typedef struct AVL_Node_a   //struct for the node of our avl tree
{
    struct AVL_Node_a *node_left;
    struct AVL_Node_a *node_right;
    int height;
    char node_key_date[50];
    float node_temp;
}AVL_Node_a;

//We declare the functions that we we will use
void delay(int number_of_seconds);
void printInorder(AVL_Node_a *);
int getheight_a( AVL_Node_a *);
AVL_Node_a *rotateright_a(AVL_Node_a *);
AVL_Node_a *rotateleft_a(AVL_Node_a *);
AVL_Node_a *AVL_right_right_rotation_a(AVL_Node_a*);
AVL_Node_a *AVL_left_left_rotation_a(AVL_Node_a *);
AVL_Node_a *AVL_left_right_rotation_a(AVL_Node_a *);
AVL_Node_a *AVL_right_left_rotation_a(AVL_Node_a *);
int getbalance_a(AVL_Node_a *);
void printInorder(AVL_Node_a *avl_node);
void printLevelOrder(AVL_Node_a*);
void printMeasurments(measurements[]);
int menu_a(struct AVL_Node_a *);
int compare_datesSort(char [], char []);
AVL_Node_a *AVL_creation_a(AVL_Node_a *,char[50],float);
AVL_Node_a *AVL_delete(AVL_Node_a *,char[50]);
AVL_Node_a* load_avl_a(measurements values[], AVL_Node_a *avl);



#endif  AVL_DATE_H
