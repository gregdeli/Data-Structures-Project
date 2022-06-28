#ifndef AVL_TEMP_H
#define AVL_TEMP_H
#include "common.h"

typedef struct AVL_Node_b   //struct for the node of our avl tree
{
    struct AVL_Node_b *node_left;
    struct AVL_Node_b *node_right;
    int height;
    char node_date[50];
    float node_key_temp;
    char *node_new_date;

}AVL_Node_b;

//We declare the functions that we we will use
int getheight_b( AVL_Node_b *);
AVL_Node_b *rotateright(AVL_Node_b *);
AVL_Node_b *rotateleft(AVL_Node_b *);
AVL_Node_b *AVL_right_right_rotation(AVL_Node_b*);
AVL_Node_b *AVL_left_left_rotation(AVL_Node_b *);
AVL_Node_b *AVL_left_right_rotation(AVL_Node_b *);
AVL_Node_b *AVL_right_left_rotation(AVL_Node_b *);
int getbalance_b(AVL_Node_b *);
int menu_b(struct AVL_Node_b *);
int compare_datesSort(char [], char []);
AVL_Node_b *creation(AVL_Node_b *,char[50],float);
float maximum(AVL_Node_b *);
float minimum(AVL_Node_b *);
AVL_Node_b* load_avl_b(measurements values[]);



#endif  AVL_TEMP_H
