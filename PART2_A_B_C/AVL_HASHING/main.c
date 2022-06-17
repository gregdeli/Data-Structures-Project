#include <stdio.h>
#include <stdlib.h>
#include "avl_date.h"
#include "avl_temp.h"
#include "common.h"
#include "hashing.h"


int main()
{
    bool loop = false;
    do
    {
        int choice = -1;
        printf("Load file ""ocean.csv"" on one of the following data structures:\n");
        printf("AVL Tree: 1\n");
        printf("Hash Table: 2\n");
        printf("Exit: 3\n");
        printf("Enter your choice: ");
        scanf(" %d", &choice);
        while ((getchar()) != '\n');
        if((choice != 1) & (choice != 2) & (choice != 3))
        {
            loop = true;
            clear_console();
            continue;
        }
        switch(choice)
        {
            case 1:
                clear_console();
                printf("Load file ""ocean.csv"" on an AVL Tree based on one of the following:\n");
                printf("Date: 1\n");
                printf("Temperature: 2\n");
                printf("Exit: 3\n");
                printf("Enter your choice: ");
                scanf(" %d", &choice);
                while ((getchar()) != '\n');
                if((choice != 1) & (choice != 2) & (choice != 3))
                {
                    loop = true;
                    clear_console();
                    continue;
                }
                switch(choice)
                {
                    case 1:
                        {
                            clear_console();
                            measurements values[1405];
                            AVL_Node_a *avl_1=NULL;
                            avl_1 = load_avl_a(values, avl_1); //load values on an avl tree based on the dates
                            menu_a(avl_1); //Function to create the menu
                            loop = true;
                            clear_console();
                        }
                        continue;
                    case 2:

                        {
                            clear_console();
                            measurements values[1405];
                            AVL_Node_b *avl_2=NULL;
                            avl_2 = load_avl_b(values); //load values on an avl tree based on the temps
                            menu_b(avl_2); //Function to create the menu
                            loop = true;
                            clear_console();
                            continue;
                        }

                    case 3:
                        loop = false;
                        continue;
                }

                case 2:
                    clear_console();
                    menu_h(); // hashing menu
                    loop = true;
                    clear_console();
                    continue;
                case 3:
                    loop = false;
                    continue;
        }

    }
    while(loop);
    return 0;
}
