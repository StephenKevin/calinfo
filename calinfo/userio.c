#ifndef USERIO_C_
#define USERIO_C_
#endif // USERIO_C_

#include "calinfo.h"

/**
    @brief 打开特定文件并检查是否成功
    @param str 打开方式字符串
**/
FILE * openStuInfo(char * str)
{
    FILE * stream;
    stream = fopen("Student_Info.txt",str);
    if(stream==NULL)
    {
        system("cls");
        printf("\n 打开文件失败. 按下 enter 离开程序.");
        getchar();
        exit(EXIT_FAILURE);
    }
    return stream;
}

/**
    @brief 录入字符串
    @param str 字符数组地址 n:限制录入最大字节数
    @return NULL:录入失败 str:录入成功
**/
char* s_gets(char * str, int n)
{
    char * retc;
    int i = 0;  //必须初始化为0 否则会出问题
    retc = fgets(str, n, stdin);    //fgets函数会自定添加换行符
    if(retc)
    {
        while(str[i]!='\n' && str[i]!='\0')
            i++;
        if(str[i]=='\n')    //先遇到换行符
            str[i]='\0';
        else                //先遇到空字符 丢弃输入行
            while(getchar()!='\n')  //处理换行符
                continue;
        if(strcmp(str,"quit")==0)
                exit(EXIT_SUCCESS);
    }
    return retc;
}

/**
    @brief 录入一个8字节无符号整数ID
    @param stuid 储存数据的地址
    @return 1:成功 0:失败
**/
int get_stuid(unsigned long long * stuid )
{
    int rev=0;
    printf("\n 学号:\n\n>> ");
    while(rev = scanf("%llu",stuid ))     //在测试语句里赋值
    {
        if(*stuid<99999999999 && *stuid>10000000000)
            break;
        else
            printf("\n 输入学号不在正确范围,请重新输入.\n>> ");
        while(getchar()!='\n');
    }
    while(getchar()!='\n');
    return  rev;
}

/**
    @brief 录入姓名
    @param name 储存姓名信息的地址
**/
int get_stuname(char * name)
{
    printf("\n 姓名:\n\n>> ");
    s_gets(name,NAME_LEN); //录入姓名
    while(strcmp(name,"")==0)
    {
        printf("\n 输入名字无效,请重新输入。\n>> ");
        s_gets(name,NAME_LEN);
    }
    if(name[0]=='r' && name[1]=='e')
        return 0;
    return 1;
}

/**
    @brief 录入性别
    @param addr 储存性别字符串的地址
**/
int get_stusex(char * sex)
{
    printf("\n 性别:\n\n>> ");
    s_gets(sex,SEX_LEN);
    while(strcmp(sex,"男") && strcmp(sex,"女") && strcmp(sex,"re"))
    {
        printf(" 输入的性别不对，请重新输入。\n>> ");
        s_gets(sex,SEX_LEN);
    }
    if(sex[0]=='r' && sex[1]=='e')
        return 0;
    return 1;
}

/**
     @brief 录入班级代号
     @param classid 储存班级代号的地址
     @return 1:成功 0:失败
**/
int get_classid(unsigned * classid)
{
    int rev = 0;
    printf("\n 班别:\n\n>> ");
    while(rev = scanf("%u",classid))
    {
        if(rev==1 && *classid <= 999999)         //检查班级编号范围
            break;
        else
            printf("\n输入的班级代号不在相应范围,请重新输入.\n\n>> ");
        while(getchar()!='\n');
    }
    while(getchar()!='\n');
    return rev;
}

/**
    @brief 录入学院信息
    @param academ 储存学院信息的地址
**/
int get_academic(char * academ)
{
    printf("\n 学院:\n\n>> ");
    s_gets(academ,ACAD_LEN);
    while(strcmp(academ,"")==0)
    {
        printf("输入无效,请重新输入。\n>> ");
        s_gets(academ, ACAD_LEN);
    }
    if(academ[0]=='r' && academ[1]=='e')
        return 0;
    return 1;
}

/**
    @brief 一个普遍适用根据指示录入信息
    @param ptr:录入信息存放地址 msg:信息指示
**/
int getstug(struct stuinfo* ptr, char msg)
{
    int g;
    switch(msg)
    {
        case 'i':
            g = get_stuid(&ptr->id);break;
        case 'n':
            g = get_stuname(ptr->name);break;
        case 's':
            g = get_stusex(ptr->sex);break;
        case 'c':
            g = get_classid(&ptr->class_id);break;
        case 'a':
            g = get_academic(ptr->academic);break;
    }
    return g;
}

/**
    @brief 指示比较学生信息
    @param tar:要比较的信息地址1 src:要比较的信息地址2 msg:提示比较信息
    @return 0:无差别 其他:有差别
**/
int compstu(struct stuinfo* tar, struct stuinfo* src, char msg)
{
    switch(msg)
    {
        case 'i':
            return(tar->id - src->id);
        case 'n':
            return(strcmp(tar->name, src->name));
        case 's':
            return(strcmp(tar->sex, src->sex));
        case 'c':
            return(tar->class_id - src->class_id);
        case 'a':
            return(strcmp(tar->academic, src->academic));
    }
    return -1;
}

/**
    @brief 录入剩余学生除学号外的其余信息
**/
void getstur(struct stuinfo * stu)
{
    get_stuname(stu->name);
    get_stusex(stu->sex);
    get_classid(&stu->class_id);
    get_academic(stu->academic);
}

/**
    @brief 用输入内容替换链表里的某个结构体里的学生数据
**/
int replacestu(struct stuinfop** ph, struct stuinfop* ptrc, struct stuinfop* ptrp)
{
    printf_stutable(&ptrc->stu);      //先打印学生的信息
    printf("请输入学生新的信息\n");   //下面替换链表里的对应数据
    getstur(&ptrc->stu);
    return 1;
}

/**
    @brief 将包含某学生信息的链表节点删除
    @param ph:指向链表头的二级指针 ptrc:当前检索的项的地址 ptrp:上一个项的地址
**/
int deletestu(struct stuinfop** ph, struct stuinfop* ptrc, struct stuinfop* ptrp)
{
    char cmd;
    printf_stutable(&ptrc->stu);  //显示该学生信息
    printf("\n 确认要删除这条信息? 1:是 2:否\n\n>> ");
    cmd = getsure();              //获取用户选择
    if(cmd == '1')
    {
        if(ptrp)
            ptrp->pts = ptrc->pts;     //使当前节点脱离出来 但要先检查上一个地址是不是有效的
        else
            *ph = ptrc->pts;           //链表头的话脱离方式会特殊一点

        free(ptrc);                         //释放脱离出来的内存
        return 1;
    }
    else if(cmd == '2')
        return 0;
}

/**
    @brief 读取一个学生信息结构体 并将文件指示器移动到行末
    @param stream:要读取的文件指针 stu:储存信息的地址
    @return EOF:读到文件结尾就返回EOF cnt:否则返回读取成功个数
**/
int fscanf_stu(FILE * stream, struct stuinfo * stu)
{
    char stc = '\0';
    int cnt;

    cnt = fscanf(stream,"%llu%s%s%u%s",
           &stu->id,stu->name,stu->sex,&stu->class_id,stu->academic);
    do
    {   stc=getc(stream);         //读取一行里剩余的无用字符
    }while(stc!='\n' && stc != EOF);

    if(cnt==0 && stc==EOF)
        return EOF;
    else
        return cnt;
}

/**
    @brief 写入一个学生信息结构体到一行上
**/
int fprintf_stu(FILE * stream, struct stuinfo * stu)
{
    int rev;
    rev = fprintf(stream, "%llu  %s  %s  %6u  %s\n", //后面的换行符很重要
                    stu->id, stu->name, stu->sex, stu->class_id, stu->academic);
    return rev;
}

/**
    @brief 在屏幕以一行打印学生信息
**/
int printf_stu(struct stuinfo * stu)
{
    if(printf(" %llu    %s    %s     %6u     %s\n",
               stu->id,stu->name,stu->sex,stu->class_id,stu->academic))
        return 1;
}

/**
    @brief 以列表方式打印一个学生的信息
    @param stu:学生信息结构体地址
**/
int printf_stutable(struct stuinfo * stu)
{
    printf("\n这个学生的信息是:\n\n");
    printf(" 学号: %llu\n",stu->id);
    printf(" 名字: %s\n",stu->name);
    printf(" 性别: %s\n",stu->sex);
    printf(" 班级: %u\n",stu->class_id);
    printf(" 学院: %s\n\n",stu->academic);
}

/**
    @brief 获取用户选择键码
    @return 返回键码
    @note 1:确认 2:否定
**/
char getsure(void)
{
    char cmd = '0';
    do
    {
        cmd = getchar();
        while(getchar()!='\n');     //处理多余输入
    }while(cmd!='1' && cmd!='2');
    return cmd;
}

int malloccheck(void * p)
{
    if(p == NULL)    //检查内存分配是否成功
    {
        system("cls");
        printf("\n内存分配失败\n\n 按下 enter 键退出程序");
        getchar();
        exit(EXIT_FAILURE);
    }
    return 1;
}



