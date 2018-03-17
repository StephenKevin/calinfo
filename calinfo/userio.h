#ifndef USERIO_H_INCLUDED
#define USERIO_H_INCLUDED

#ifndef USERIO_C_
    #define USERIO_EXTERN extern
#else
    #define USERIO_EXTERN
#endif

USERIO_EXTERN FILE * openStuInfo(char * str);
USERIO_EXTERN char* s_gets(char * str, int n);

USERIO_EXTERN int get_stuid(unsigned long long * stuid );
USERIO_EXTERN int get_stuname(char * name);
USERIO_EXTERN int get_stusex(char * sex);
USERIO_EXTERN int get_classid(unsigned int * classid);
USERIO_EXTERN int get_academic(char * academ);

USERIO_EXTERN int getstug(struct stuinfo* ptr, char msg);
USERIO_EXTERN int compstu(struct stuinfo* tar, struct stuinfo* src, char msg);

USERIO_EXTERN void getstur(struct stuinfo * stu);

USERIO_EXTERN int replacestu(struct stuinfop** ph, struct stuinfop* ptrc, struct stuinfop* ptrp);
USERIO_EXTERN int deletestu(struct stuinfop** ph, struct stuinfop* ptrc, struct stuinfop* ptrp);

USERIO_EXTERN char getsure(void);

USERIO_EXTERN int fscanf_stu(FILE * stream, struct stuinfo * stu);
USERIO_EXTERN int fprintf_stu(FILE * stream, struct stuinfo * stu);

USERIO_EXTERN int printf_stu(struct stuinfo * stu);
USERIO_EXTERN int printf_stutable(struct stuinfo * stu);

USERIO_EXTERN char getsure(void);

USERIO_EXTERN int malloccheck(void * p);

#endif // USERIO_H_INCLUDED