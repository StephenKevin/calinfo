#ifndef LISTFUN_H_INCLUDED
#define LISTFUN_H_INCLUDED

#ifndef LISTFUN_C_
    #define LISTFUN_EXTERN extern
#else
    #define LISTFUN_EXTERN
#endif // LISTFUN_C_

typedef int(*ListOperation_t)(struct stuinfop** ph, struct stuinfop* pc,struct stuinfop* pr);

LISTFUN_EXTERN int listucomp(struct stuinfop** ptr_h, char mo,struct stuinfo* data, ListOperation_t oper,int* msg);

LISTFUN_EXTERN struct stuinfop* read_stuall(int *memcnt);

LISTFUN_EXTERN int write_stuall(struct stuinfop * ptr_head, int writex );

LISTFUN_EXTERN struct stuinfop * listusort(struct stuinfop* hp, char msg);


#endif // LISTFUN_H_INCLUDED