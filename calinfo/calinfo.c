/** Calinfo
Function:
    1.Add
    2.Browser all
    3.Query
    4.Statistics
    5.Modify
    6.Delete
    7.Quit
**/

#ifndef CALINFO_C_
    #define CALINFO_C_
#endif // CALINFO_C_

#include "calinfo.h"

int main(void)
{
    char menu_str[MENU_ST];     //store user's imput

    table_main();               //print main menu
    printf(">> ");              //print the indicator of input

    while(s_gets(menu_str, MENU_ST)!=NULL)
    {
        menu_main(menu_str[0]);
    }
    return 1;
}


