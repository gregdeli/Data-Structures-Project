#include <stdio.h>
#include <stdlib.h>
#include "avl_date.h"
#include "avl_temp.h"
#include "common.h"


int main()
{
    measurements values[1405];
    AVL_Node_a *avl=NULL;
    avl = load_avl_a(values, avl);
    menu_a(avl); //Function to create the menu

    return 0;
}
