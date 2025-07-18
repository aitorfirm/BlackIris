#include "Scheduler.h"
#include "../Shared/Utils.h"
#include "../Shared/Logger.h"

static SCHEDULED_TASK TaskList[MAX_TASKS];
static UINTN TaskCount = 0;

BOOLEAN SchedulerInit(void) {
    TaskCount = 0;
    LogInfo(L"[Scheduler] Iniciado correctamente\n");
    return TRUE;
}

BOOLEAN AddTask(TASK_FUNC Func, UINT64 IntervalMs) {
    if (TaskCount >= MAX_TASKS) return FALSE;

    TaskList[TaskCount].Func = Func;
    TaskList[TaskCount].IntervalMs = IntervalMs;
    TaskList[TaskCount].LastRun = GetCurrentTimeMs();

    TaskCount++;
    return TRUE;
}

VOID SchedulerTick(void) {
    UINT64 Now = GetCurrentTimeMs();

    for (UINTN i = 0; i < TaskCount; i++) {
        if ((Now - TaskList[i].LastRun) >= TaskList[i].IntervalMs) {
            TaskList[i].Func();
            TaskList[i].LastRun = Now;
        }
    }
}
