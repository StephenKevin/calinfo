#ifndef MENU_C_
    #define MENU_C_
#endif // MENU_C_

#include <stdlib.h>
#include <stdio.h>
#include "calinfo.h"

/**
    @brief 主菜单选项表
**/
void table_main(void)
{
    system("cls");      //清屏

    printf("\n\t\t\t    学 生 信 息 管 理 系 统\n");
    printf("\t\t\t\t\t\t\t\t   version:%.2f\n",CALINFO_VERSION);
    printf("______________________________________________________________________________\n\n");
    printf(" 请输入菜单编号 (输入 quit 退出程序):\t\t\t\n");
    printf("\n\t      (1) 添加学生信息             (2) 修改学生信息\n\n");
    printf("\n\t      (3) 删除部分信息             (4) 浏览全部信息\n\n");
    printf("\n\t      (5) 高级查询工具             (6) 分类统计工具\n");
    printf("______________________________________________________________________________\n\n");
}
/**
    @brief 主菜单
**/
void menu_main(char choice)
{
    switch(choice)
    {
        case '1':
            menu_add();break;
        case '2':
            menu_modify();break;
        case '3':
            menu_delete();break;
        case '4':
            menu_brows();break;
        case '5':
            menu_query();break;
        case '6':
            menu_statistic();break;
        case '\0':
            table_main();
            printf(">> ");
            break;
        default:
            table_main();
            printf("输入错误，请重新输入:\n>> ");
            break;
    }
}

/**
    @brief 子菜单 添加信息记录
**/
void menu_add(void)
{
    struct stuinfo stup;            //录入学生信息临时储存
    struct stuinfo stut;            //文件读取临时储存
    FILE * fpt;                     //文件指针
    int stu_cnt = 0;                //新录入学生计数
    bool stu_repeat = false;        //学号重复标记

    fpt = openStuInfo("a+");        //追加读写模式文件不存在就创建一个
    system("cls");                  //清屏
    printf("\n 请根据提示输入相关信息.");

    while(1)
    {
        stup.id = 0;                        //先将stup.id清零
        stu_repeat=false;
        printf(" 输入 re 返回主菜单.\n\n");
        if(get_stuid(&stup.id)==0) break;   //录入学号 录入失败就跳出外层循环
        rewind(fpt);                        //使其位置指示器定位到起始
        while(fscanf_stu(fpt,&stut)!=EOF)   ////读取文件数据一行
        {
            if(stut.id == stup.id)          //读取到相同的ID
            {
                system("cls");
                printf("\n 您输入的学号 %lld 已经存在，无法添加.\n\n 请输入下一个学生的信息.",stut.id);
                stu_repeat = true;   //要跳出循环再跳过后面一堆语句，用goto语言可能更好
                break;
            }
        }
        if(stu_repeat == false)
        {
            getstur(&stup);             //将学生其余信息录入
            fseek(fpt, 0L, SEEK_CUR);   //文件位置指示器定位到末尾
            if(fprintf_stu(fpt, &stup))
                stu_cnt++;/**保存信息到文件**/
            system("cls");
            printf("\n 成功录入一条信息，累计录入了%d条信息。\n",stu_cnt);
            printf("\n 请输入下一个学生的信息. ");
        }
    }
    fclose(fpt);    //关闭文件
    table_main();        //返回之前要先刷新终端
    printf("\n>> ");
}
/**
    @brief 修改学生信息
**/
void menu_modify(void)
{
    struct stuinfo stup;                //录入学生信息临时储存
    struct stuinfop * stuhead = NULL;   //链表头
    FILE * fpt;                         //文件指针
    int stufound = 0;                   //找到对应项数量
    int msg = 0;
    int mcnt = 0;                       //分配内存计数

    system("cls");                      //清屏
    printf("\n 请输入你要修改的学生学号 (re返回主菜单).\n");
    while(1)
    {
        stuhead = NULL;                     //先将指针头写0
        stufound = 0;
        mcnt = 0;

        if(get_stuid(&stup.id)==0) break;   //录入学号 录入失败就跳出外层循环

        stuhead = read_stuall(&mcnt);       //将文件内的数据全部读入链表
        if(stuhead == NULL) break;

        stufound = listucomp(&stuhead,'i',&stup,replacestu,&msg);//检索链表里的id并进行替换操作

        system("cls");
        //释放内存 更新文件数据(如果需要的话)
        if( write_stuall(stuhead, stufound) > 0)
        {
            printf("\n 本项修改成功了!\n\n");
            printf(" 请输入下一个要修改信息的学号 (re返回主菜单)。\n\n");
        }
        else
            printf("\n 未能找到学生%llu。请输入新的学号. (re返回主菜单)\n",stup.id);
    }
    table_main();        //返回之前要先刷新终端
    printf(">> ");
}

//-------------------------------------------------------------------------------------
/**
    @brief 子菜单 删除条目
**/
void menu_delete(void)
{
    struct stuinfo stup;            //录入学生信息临时储存
    struct stuinfop * stuhead=NULL; //链表头
    FILE * fpt;                     //文件指针
    int stufound = 0;               //是否找到对应项计数
    int studelete = 0;              //确认删除计数
    int mcnt=0;                     //分配内存计数

    system("cls");                      //清屏
    printf("\n 请输入你要修改的学生学号 (re返回主菜单).\n");
    while(1)
    {
        //变量赋值
        stup.id = 0;
        stuhead = NULL;                 //先将指针写0
        studelete = 0;
        stufound = 0;
        mcnt = 0;

        if(get_stuid(&stup.id)==0) break;  //录入学号,录入失败就跳出外层循环

        stuhead = read_stuall(&mcnt);       //将文件内的数据全部读入链表
        if(stuhead == NULL) break;

        stufound = listucomp(&stuhead,'i',&stup, deletestu, &studelete); //检索链表里的信息并进行删除

        write_stuall(stuhead, studelete);  //释放内存 写入文件(如果需要的话)

        system("cls");
        if(stufound)
        {
            if(studelete)
            {
                printf("\n 本次删除成功了!\n");
                if(stuhead == NULL)
                {
                    printf("\n 数据文件里没有任何数据了.\n");
                    printf("\n 按下 erter键 返回主菜单.\n\n>> ");
                    getchar();break;
                }
            }
            else printf("\n 取消删除成功.\n");
            printf("\n 请输入下一个要删除信息的学号 (re返回主菜单).\n");
        }
        else printf("\n 未能找到学生 %llu ,请输入新的学号 (re 返回主菜单).\n",stup.id);
    }
    table_main();        //返回之前要先刷新终端
    printf(">> ");
}
//-------------------------------------------------------------------------------------
/**
    @brief 子菜单 浏览全部信息
**/
void menu_brows(void)
{
    struct stuinfop* headp = NULL;
    struct stuinfo stut;     //文件读取临时储存
    FILE * fpt = NULL;               //文件指针
    int pcnt = 0;                   //打印信息条数
    int mcnt = 0;
    char cmd[3]={'\0','\0','\0'};

    while(1)
    {
        pcnt = 0;
        system("cls");                  //清屏
        printf("\n     学号\t 姓名\t 性别\t 专业代号\t 学院\n");
        printf("_______________________________________________________________\n\n");

        fpt = openStuInfo("r");         //读模式
        rewind(fpt);
        while(fscanf_stu(fpt, &stut)!=EOF)
        {
            printf_stu(&stut);
            pcnt++;
        }
        fclose(fpt);                    //关闭文件

        printf("\n 全部信息显示完毕.");
        printf(" 一共有学生 %d 人.\n",pcnt);

        printf("\n 输入 si、sc、ss、sa 可以分别按学号、班别、性别、学院进行排序.\n");
        printf("\n 按下 enter键 返回主菜单. \n\n>> ");
        s_gets(cmd, 10);
        if(cmd[0]=='s' && (cmd[1]=='i'||cmd[1]=='c'||cmd[1]=='s'||cmd[1]=='a'))
        {
            headp = read_stuall(&mcnt);
            headp = listusort(headp, cmd[1]);   //按学号排序
            write_stuall(headp, 1);             //向文件写入数据
        }
        else break;
    }
    table_main();        //返回之前要先刷新终端
    printf(">> ");
}


/**
    @brief 查询菜单列表
**/
void table_query(void)
{
    printf("\n 请选择查找方式.\n");
    printf("______________________________________________________________________________\n\n");
    printf("\t\t(1) 按学号查找\t\t(2) 按姓名查找\n\n");
    printf("\t\t(3) 按性别查找\t\t(4) 按班别查找\n\n");
    printf("\t\t(5) 按学院查找\n\n");
    printf("______________________________________________________________________________\n\n");
}

/**
    @brief 子菜单 高级查询工具
**/
void menu_query(void)
{
    char slc[3];                    //记录用户选择
    FILE * fpt;                     //文件指针

    fpt = openStuInfo("r");
    while(1)
    {
        system("cls");                      //清屏
        table_query();
        printf(" 输入 re 返回上一级.\n>> ");
        if(s_gets(slc,3)!=NULL)
        {
            rewind(fpt);
            if(slc[0]=='1')
                querystu(fpt, 'i');
            else if(slc[0]=='2')
                querystu(fpt, 'n');
            else if(slc[0]=='3')
                querystu(fpt, 's');
            else if(slc[0]=='4')
                querystu(fpt, 'c');
            else if(slc[0]=='5')
                querystu(fpt, 'a');
            else if(slc[0]=='r' && slc[1]=='e')
                break;
        }
    }
    fclose(fpt);        //关闭文件
    table_main();        //返回之前要先刷新终端
    printf(">> ");
}

void querystu(FILE* fpt, char msg)
{
    struct stuinfo stut;            //文件读取临时储存
    struct stuinfo stup;            //数据录入临时储存
    int pcnt = 0;
    system("cls");
    printf("\n 输入 re 返回上一级.\n\n");
    while(getstug(&stup, msg))
    {
        pcnt = 0;
        system("cls");
        printf("\n 学号\t\t姓名\t 性别   班级代号    学院\n\n");
        rewind(fpt);
        while(fscanf_stu(fpt, &stut) != EOF)
        {
            if(compstu(&stup, &stut, msg)==0)
            {
                printf_stu(&stut);
                pcnt++;
            }
        }
        printf("\n 搜索完毕,一共找到 %d 个.\n", pcnt);
        printf("\n 请输入下一个(输入re返回上一级):\n ");
    }
}

/**
    @brief 统计菜单列表
**/
void table_statistic(void)
{
    printf("\n 请选择统计方式.\n");
    printf("______________________________________________________________________________\n\n");
    printf("\t\t(1) 统计性别\t\t(2) 统计年龄\n\n");
    printf("\t\t(3) 统计学分\t\t(4) 统计绩点\n\n");
    printf("\t\t(5) 统计身高\t\t(6) 统计就业\n\n");
    printf("______________________________________________________________________________\n");
}

/**
    @brief 子菜单 分类统计工具
**/
void menu_statistic(void)
{
    char cho[5];
    struct stuinfo stut;            //文件读取临时储存
    FILE * fpt;                     //文件指针
    int sex_mcnt = 0;
    int sex_wcnt = 0;

    fpt = openStuInfo("r");         //读模式
    system("cls");                  //清屏
    table_statistic();
    printf("\n 输入re上回上一级.\n\n>> ");
    while(s_gets(cho,3))
    {
        if(cho[0]=='r' && cho[1]=='e')
            break;
        sex_mcnt = 0.0;
        sex_wcnt = 0.0;
        system("cls");                  //清屏
        rewind(fpt);
        if(cho[0] == '1')
        {
            while(fscanf_stu(fpt, &stut)!=EOF)
            {
                if(strcmp(stut.sex,"男") == 0)
                    sex_mcnt++;
                else sex_wcnt++;
            }
            table_statistic();
            printf("\n 统计结果:\n");
            printf("\n 男生 %d 人",sex_mcnt);
            printf("\n 女生 %d 人",sex_wcnt);
            printf("\n 男女比例是 %.3f / 100 . \n",100.0f*sex_mcnt/sex_wcnt);
        }
        else
        {
            table_statistic();
            printf("\n 除了性别外，其余信息尚未包括，无法统计. 这些功能待日后添加.\n");
        }
        printf("\n 输入re上回上一级.\n\n>> ");
    }
    fclose(fpt);        //关闭文件
    table_main();        //返回之前要先刷新终端
    printf(">> ");
}
