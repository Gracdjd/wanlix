#include "wanlix.h"
#include "wanlix_core_c.h"
U32 guiCurTask; //当前运行的任务

W_TCB* gpstrTask1Tcb;// 任务1
W_TCB* gpstrTask2TCB; //任务2

/// @brief 初始化任务运行前的环境
/// @param vfFunctionPointer 任务运行时的函数指针
/// @param puiTaskStack 任务使用的栈指针
/// @return 函数的TCB
W_TCB* WLX_TaskInit(VFUNC vfFunctionPointer, U32* puiTaskStack)
{
    W_TCB* ptcbTcb;
    STACKREG* pstrStackReg;

    //tcb放在栈顶
    ptcbTcb = (W_TCB*) ((U32)puiTaskStack - sizeof(W_TCB));

    pstrStackReg = &(ptcbTcb->strStackReg);

    pstrStackReg->uiR4 = 0;
    pstrStackReg->uiR5 = 0;
    pstrStackReg->uiR6 = 0;
    pstrStackReg->uiR7 = 0;
    pstrStackReg->uiR8 = 0;
    pstrStackReg->uiR9 = 0;
    pstrStackReg->uiR10 = 0;
    pstrStackReg->uiR11 = 0;
    pstrStackReg->uiR12 = 0;
    pstrStackReg->uiR13 = (U32)ptcbTcb;
    pstrStackReg->uiR14 = (U32)vfFunctionPointer; //lr保存着函数返回后需要调用的地址，init函数返回func
    pstrStackReg->uiXpsr = MODE_USR;

    return ptcbTcb;
}

W_TCB *WLX_TaskSwitch(void)
{
    STACKREG* pstrCurTaskStackRegAddr;
    STACKREG* pstrNextTaskStackRegAddr;

    if(1 == guiCurTask)
    {
        //当前任务的寄存器地址
        pstrCurTaskStackRegAddr = &gpstrTask1Tcb->strStackReg;

        //即将运行任务的寄存器组的地址
        pstrNextTaskStackRegAddr = &gpstrTask2TCB->strStackReg;

        //更新下次运行的任务
        guiCurTask = 2;
    }
    else
    {
        pstrCurTaskStackRegAddr = &gpstrTask1Tcb->strStackReg;
        pstrNextTaskStackRegAddr = &gpstrTask2TCB->strStackReg;
        guiCurTask = 1;
    }

    WLX_ContextSwitch(pstrCurTaskStackRegAddr, pstrNextTaskStackRegAddr);
}

/// @brief 将初始化的寄存器组进行恢复
/// @param  
void WLX_TaskStart(void)
{
    STACKREG* pstrNextTaskStackRegAddr;
    
    //即将运行任务寄存器组的地址
    pstrNextTaskStackRegAddr = &gpstrTask1Tcb->strStackReg;
    //更新下次调度的任务
    guiCurTask = 1;

    //切换到任务状态
    WLX_SwitchToTask(pstrNextTaskStackRegAddr);

}
