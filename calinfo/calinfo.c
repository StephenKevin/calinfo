/** 学生信息统计
功能:
    1.添加一个记录
    2.浏览全部信息
    3.查询
    4.统计
    5.修改一个记录
    6.删除一个记录
    7.退出程序
**/

#ifndef CALINFO_C_
    #define CALINFO_C_
#endif // CALINFO_C_

#include "calinfo.h"

int main(void)
{
    char menu_str[MENU_ST];     //储存用户输入

    table_main();               //打印主菜单
    printf(">> ");              //输入指示符

    while(s_gets(menu_str, MENU_ST)!=NULL)
    {
        menu_main(menu_str[0]);
    }
    return 1;
}


