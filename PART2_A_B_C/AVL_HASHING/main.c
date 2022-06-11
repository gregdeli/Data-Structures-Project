#include <stdio.h>
#include <stdlib.h>
#include "avl_date.h"
#include "avl_temp.h"
#include "common.h"


int main()
{
    measurements values[1405];
    AVL_Node_a *avl_1=NULL;
    AVL_Node_b *avl_2=NULL;
    avl_1 = load_avl_a(values, avl_1); //load values on an avl tree based on the dates
    //menu_a(avl_1); //Function to create the menu
    avl_2 = load_avl_b(values, avl_2); //load values on an avl tree based on the temps
    menu_b(avl_2);
    return 0;
}
