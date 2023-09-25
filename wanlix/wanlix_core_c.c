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