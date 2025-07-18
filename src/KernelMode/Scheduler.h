#ifndef SYRIAL_BOT_SCHEDULER_H
#define SYRIAL_BOT_SCHEDULER_H

#include <Uefi.h>

typedef VOID (*TASK_FUNC)(VOID);

typedef struct {
    TASK_FUNC Func;
    UINT64 IntervalMs;
    UINT64 LastRun;
} SCHEDULED_TASK;

#define MAX_TASKS 16

BOOLEAN SchedulerInit(void);
VOID SchedulerTick(void);
BOOLEAN AddTask(TASK_FUNC Func, UINT64 IntervalMs);

#endif 
