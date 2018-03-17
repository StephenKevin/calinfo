#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#ifndef MENU_C_
    #define MENU_EXTERN extern
#else
    #define MENU_EXTERN
#endif

#define CALINFO_VERSION 0.1

#define NAME_LEN 40
#define SEX_LEN 10
#define ACAD_LEN 100

struct stuinfo
{
    unsigned long long id;
    char name[NAME_LEN];
    char sex[SEX_LEN];
    unsigned int class_id;
    char academic[ACAD_LEN];
};

struct stuinfop
{
    struct stuinfo stu;     //储存学生信息的内嵌结构体
    struct stuinfop * pts;  //指向stuifonp结构体的指针
};

MENU_EXTERN void table_main(void);
MENU_EXTERN void menu_main(char choice);
MENU_EXTERN void menu_add(void);
MENU_EXTERN void menu_modify(void);
MENU_EXTERN void menu_delete(void);
MENU_EXTERN void menu_brows(void);
MENU_EXTERN void table_query(void);
MENU_EXTERN void menu_query(void);
MENU_EXTERN void querystu(FILE* fpt, char msg);
MENU_EXTERN void table_statistic(void);
MENU_EXTERN void menu_statistic(void);


MENU_EXTERN void query_id(void);
MENU_EXTERN void query_name(void);
MENU_EXTERN void query_class(void);
MENU_EXTERN void query_academic(void);


#endif // MENU_H_INCLUDED