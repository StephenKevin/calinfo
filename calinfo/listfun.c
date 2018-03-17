#ifndef LISTFUN_C_
    #define LISTFUN_C_
#endif // LISTFUN_C_

#include "calinfo.h"

/**
    @brief  将文件里的数据全部读入链表
    @param  stream:已经打开的要读取的文件的指针
            mencnt:地址,用于储存成功分配内存的数量
    @return 链表头
    @note 本模块会打开文件，读取完毕关闭文件
**/
struct stuinfop* read_stuall(int *memcnt)
{
    FILE * stream;
    struct stuinfop * ptr_head = NULL;       //链表头
    struct stuinfop * ptr_cur = NULL;        //用于构建链表
    struct stuinfop * ptr_prev = NULL;       //用于构建链表
    int mcnt;
    char stc='\0';

    *memcnt = 0;

    stream = openStuInfo("r");          //打开文件读模式
    rewind(stream);                     //使文件位置指示器回到开始

    ptr_head = (struct stuifonp *)malloc(sizeof(struct stuinfop));    //分配内存
    malloccheck(ptr_head);              //检查内存分配
    mcnt++;                             //内存计数加1
    if(fscanf_stu(stream,&ptr_head->stu) == EOF)//从文件读入一个记录
    {
        free(ptr_head);
        printf("\n 文件是空的,没有数据.\n\n按下enter键返回主菜单\n\n>> ");
        getchar();
        return NULL;
    }
    ptr_prev = ptr_head;                //先建立链表头

    while(1)    //循环读取文件
    {
        ptr_cur = (struct stuifonp *)malloc(sizeof(struct stuinfop)); //分配内存
        malloccheck(ptr_cur);                //检查内存分配是否成功
        mcnt++;

        ptr_prev->pts = ptr_cur;     //将当前结构地址送给上一个结构的指针成员
        ptr_cur->pts = NULL;         //为链表尾做准备

        if(fscanf_stu(stream,&ptr_cur->stu) == EOF) //读取文件一行数据  并检查是否读到文件尾
        {   //如果检查到文件尾的话
            free(ptr_cur);               //释放最后分配的一块内存
            if(ptr_prev)        //先检查ptr_prev是否空指针 因为分配第一块内存时ptr_prev指针未被赋予一个有效值
                ptr_prev->pts = NULL;    //使其脱离链表
            mcnt--;                 //分配内存块计数减一
            break;                       //跳出循环
        }
        //实际上在读取过程就可以顺便检索 但暂时不采用这种方法
        ptr_prev = ptr_cur;
    }

    if(fclose(stream)!=0)        //关闭文件
        exit(EXIT_FAILURE);   //关闭文件失败退出
    *memcnt = mcnt;
    return ptr_head;
}

/**
    @brief 将链表里的数据全部写入文件(如果需要的话) 释放链表内存 关闭文件
    @param ptr_head:要打印的链表的头
            writex: 大于0截断文件，写入新的数据数据，否则不写入数据
    @return 成功写入的结构体数目
    @note
**/
int write_stuall(struct stuinfop * ptr_head, int writex )
{
    FILE * stream = NULL;
    struct stuinfop * ptr_cur = NULL;        //读取读取链表
    int memcnt = 0;

    if(writex > 0)
        stream = openStuInfo("w");

    if(ptr_head != NULL)
        ptr_cur = ptr_head;
    else
    {
        if(stream) fclose(stream);
        return -1;
    }
    while(1)
    {
        if(writex>0)  //检查是否需要写文件
        {
            fprintf_stu(stream, &ptr_cur->stu);    //将链表里的内容打印到文件里
            memcnt++;
        }
        free(ptr_cur);   //先释放这一块内存

        if(ptr_cur->pts)     //检查是否非空指针
            ptr_cur = ptr_cur->pts;   //使其指向下一块内存
        else
            break;              //链表数据输出结束 内存释放完成
    }
    if(stream) fclose(stream);
    return memcnt;
}

/**
    @brief 检索链表里与待比较对象相同的内容(包括整数字符串等) 以及后续的操作
    @param ptr_h:指向链表头的二级指针
           mo:指定链表的要比较的内容 'i'比较ID，'n'比较姓名,'s'比较性别，'c'比较班级，'a'比较学院
           data:要比较的内容的地址
           oper:函数指针，检索到相同内容要链表做的操作
           msg:储存oper操作的其他信息的地址 不同情境意义不同
    @return  返回相同内容个数
    @note 文件必须已经打开并且本函数不会关闭文件
**/
int listucomp(struct stuinfop** ptr_h, char mo, struct stuinfo* data, ListOperation_t oper,int* msg)
{
    struct stuinfop * ptr_cur = NULL;       //读取读取链表
    struct stuinfop * ptr_prev = NULL;      //用于读取链表
    int memcnt = 0;
    int eql =1;                             //用于储存比较函数返回的值

    if(*ptr_h != NULL)                      //先检查链表头指针是否NULL
        ptr_cur = *ptr_h;                   //再将指向链表头的指针赋值给
    else return -1;

    while(1)
    {
        eql = compstu(&ptr_cur->stu, data, mo);
        if(eql == 0)
        {
            memcnt++;               //检索到相同项计数
            if(oper)                //先检查函数指针是否有效
                *msg += oper(ptr_h, ptr_cur, ptr_prev); //检查到相同内容要做的操作
        }
        ptr_prev = ptr_cur;             //将当前结构体的指针成员赋给上结构指针
        if(ptr_cur->pts)                //检查指针是否NULL
            ptr_cur = ptr_cur->pts;     //使其指向下一块内存
        else
            break;                  //链表数据输出结束 内存释放完成
    }
    return memcnt;
}


/**
    @brief 对储存在链表里的学生根据信息内容排序
    @param hp:待排序的链表头 msg:排序内容指示
    @return 返回排序之后的新链表头
**/
struct stuinfop * listusort(struct stuinfop* hp, char msg)
{
    struct stuinfop* ptr_cur = NULL;        //用于访问排序前的链表
    struct stuinfop* ptr_pre = NULL;

    struct stuinfop* ptr_label = NULL;        //用于标记最小/大的节点
    struct stuinfop* ptr_lablepre = NULL;   //用于标记ptr_label所标记的前一个节点

    struct stuinfop* hpnew = NULL;                 //排序后的新链表头
    struct stuinfop* pnew = NULL;                  //访问新链表的指针

    int cmpresult;

    while(hp)           //先检查是否空指针
    {
        ptr_cur = hp;
        ptr_label = hp;
        ptr_lablepre = NULL;

        while(1)
        {
            cmpresult = compstu(&ptr_cur->stu, &ptr_label->stu, msg);
            if(cmpresult < 0)
            {
                ptr_label = ptr_cur;        //将标记移动到当前
                ptr_lablepre = ptr_pre;
            }

            ptr_pre = ptr_cur;
            if(ptr_cur->pts)
                ptr_cur = ptr_cur->pts;
            else break;
        }
        if(ptr_label == hp)
            hp = ptr_label->pts;
        else
            ptr_lablepre->pts = ptr_label->pts; //使最小的脱离原链表

        ptr_label->pts = NULL;              //使挑选出来的节点不再指向其他节点

        //构建新的链表
        if(hpnew == NULL)
            hpnew = ptr_label;
        else
            pnew->pts = ptr_label;
        pnew = ptr_label;
    }

    return hpnew;
}


