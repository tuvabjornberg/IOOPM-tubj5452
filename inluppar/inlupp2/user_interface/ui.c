# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include "utils.h"
# include <string.h>
# include <ctype.h>
# include <time.h>


//FIXME: OBS! print_menu, ask_question_menu, main from db.c (lab 5), with modifications

void print_menu(void) 
{
    printf("\n[A] Add merchendise\n[L] List merchendise\n[R] Remove merchendise\n[E] Edit merchendise\n"
            "[S] Show stock\n[P] Replenish stock\n[C] Create cart\n[M] Remove cart\n[+] Add to cart\n"
            "[-] Remove item from cart\n[=] Calculate cost of all items in your cart\n[O] Checkout\n[Q] Quit\n"); 

}

char ask_question_menu(void) 
{
    print_menu(); 
    char *user_input = ask_question_string("");
    int valid_user_input = 0; 

    do 
    {
        switch (toupper(*user_input)) 
        {
            case 'A':
            case 'L': 
            case 'R': 
            case 'E': 
            case 'S': 
            case 'P': 
            case 'C': 
            case 'M': 
            case '+': //should work with toupper?
            case '-': //-||-
            case '=': //-||-
            case 'O': 
            case 'Q': 
                valid_user_input = 1; 
                break;
            default:
                user_input = ask_question_string("Try again with a valid input\n");
            } 
    }
    while(!valid_user_input); 

    return toupper(*user_input);
}


void event_loop(item_t *items, int db_size) 
{
    bool running = true; 

    do 
    {
        switch (ask_question_menu()) 
        {
            case 'A': 
            //TODO: add merchendise

            case 'L': 
            //TODO: list merchendise
                char *continue_list = ask_qustion_string("Press 'N' to return to menu");
                if (toupper(*continue_list) == 'N' ) {
                    break; 
                }
                else {
                    //TODO: continue listing
                }
                 
            case 'R':
                //TODO: read name of merch
                char *remove_confirmation = ask_qustion_string("Are you sure you want to remove %s", name_of_merch);

                if (toupper(*remove_confirmation) == 'Y')
                {
                    //TODO: Remove item
                }

                //TODO: Error handling??
                //if (db_size == 0) {
                //    printf("Add merchendise to before removing\n"); 
                //}
                //else {
                //}
                break;
            case 'E':
                //TODO: Edit merchendise
                break;
            case 'S': 
                //TODO: Show stock 
                break;
            case 'P': 
                //TODO: Replenish stock
                break;
            case 'C': 
                //TODO: Create cart
                break; 
            case 'M':
                //TODO: Remove cart
                break; 
            case '+':
                //TODO: Add item to cart
                break; 
            case '-': 
                //TODO: Remove item from cart
                break; 
            case '=': 
                //TODO: Calculate cost of all items in cart
                break; 
            case 'O': 
                //TODO: Checkout
                break; 
            case 'Q':
                char *quit_confirmation = ask_qustion_string("Press 'Y' if you really want to quit");

                if (toupper(*quit_confirmation) == 'Y')
                {
                    running = false; 
                } 
                break;
            default:
                break;
        }
        //error handling??
        //if (db_size == 16) {
        //    printf("Du har lagt till max antal varor (16 st), fortsätter du att lägga till varor skrivs det över dina tidigare varor\n"); 
        //    db_size = 0; 
        //}
    } while (running); 
}

int main() { 
    item_t db[16]; // Array med plats för 16 varor
    int db_siz = 0; // Antalet varor i arrayen just nu
    event_loop(db, db_siz); 
    return 0;
}