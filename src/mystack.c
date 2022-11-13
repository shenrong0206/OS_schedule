#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include "coroutine_int.h"

void my_rq_init(struct my_rq *rq)
{
    rq->in = 0;
    rq->mask = RINGBUFFER_SIZE - 1;
}

static inline unsigned int my__ringbuffer_unused(struct my_rq *rq)
{
    return rq->mask ==rq->in;
}

int my_addstack(struct my_rq *rq, struct task_struct *task)
{
    if (my__ringbuffer_unused(rq))
        return -EAGAIN;
    rq->r[rq->in] = task;
    rq->in++;
    return 0;
}

struct task_struct *my_destack(struct my_rq *rq)
{
    struct task_struct *rev;
    if (!rq->in)
        return NULL;
    rq->in--;
    rev = rq->r[rq->in];
 return rev;
}
