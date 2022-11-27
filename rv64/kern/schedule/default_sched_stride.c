#include <defs.h>
#include <list.h>
#include <proc.h>
#include <assert.h>
#include <default_sched.h>

#define USE_SKEW_HEAP 1



#define BIG_STRIDE (1 << 30)


static int
proc_stride_comp_f(void *a, void *b)
{
     struct proc_struct *p = le2proc(a, lab6_run_pool);
     struct proc_struct *q = le2proc(b, lab6_run_pool);
     int32_t c = p->lab6_stride - q->lab6_stride;
     if (c > 0) return 1;
     else if (c == 0) return 0;
     else return -1;
}


static void
stride_init(struct run_queue *rq) {

    list_init(&(rq->run_list));
    rq->lab6_run_pool = NULL;
    rq->proc_num = 0;
}


static void
stride_enqueue(struct run_queue *rq, struct proc_struct *proc) {

    rq->lab6_run_pool = skew_heap_insert(rq->lab6_run_pool, &(proc->lab6_run_pool), proc_stride_comp_f);

    if (proc->time_slice == 0 || proc->time_slice > rq->max_time_slice) {
        proc->time_slice = rq->max_time_slice;
    }

    proc->rq = rq;
    rq->proc_num++;
}


static void
stride_dequeue(struct run_queue *rq, struct proc_struct *proc) {

    assert(proc->rq == rq && rq->proc_num > 0);
    rq->lab6_run_pool = skew_heap_remove(rq->lab6_run_pool, &(proc->lab6_run_pool), proc_stride_comp_f);
    rq->proc_num--;
}

static struct proc_struct *
stride_pick_next(struct run_queue *rq) {

    if (rq->lab6_run_pool == NULL) {
      return NULL;
    }
    struct proc_struct* proc = le2proc(rq->lab6_run_pool, lab6_run_pool);
    proc->lab6_stride += proc->lab6_priority ? BIG_STRIDE / proc->lab6_priority : BIG_STRIDE;
    return proc;
}


static void
stride_proc_tick(struct run_queue *rq, struct proc_struct *proc) {

    if (proc->time_slice > 0) {
        proc->time_slice--;
    }
    if (proc->time_slice == 0) {
        proc->need_resched = 1;
    }
}

struct sched_class default_sched_class = {
     .name = "stride_scheduler",
     .init = stride_init,
     .enqueue = stride_enqueue,
     .dequeue = stride_dequeue,
     .pick_next = stride_pick_next,
     .proc_tick = stride_proc_tick,
};
