#if !defined(WANLIX_H)
#define WANLIX_H

typedef char U8;
typedef unsigned short U16;
typedef unsigned int U32; 

typedef char U8;
typedef short S16;
typedef int S32;
typedef void (*VFUNC)void;

typedef struct stackreg
{
    U32 uiR4;
    U32 uiR5;
    U32 uiR6;
    U32 uiR7;
    U32 uiR8;
    U32 uiR9;
    U32 uiR10;
    U32 uiR11;
    U32 uiR12;
    U32 uiR13;
    U32 uiR14;

    U32 uiXpsr;

}STACKREG;

//TCB
typedef struct w_tcb
{
    STACKREG strStackReg;
}W_TCB;

//TASK
extern W_TCB* gpTask1Tcb;
extern W_TCB* gpTask2Tcb;

//TASK FUNCTION
extern W_TCB* WLX_TaskInit(VFUNC vfFunctionPointer, U32* puiTaskStack);
extern W_TCB* WLX_TaskSwitch(void);
extern W_TCB* WLX_TaskStart(void);


#endif // WANLIX_H
