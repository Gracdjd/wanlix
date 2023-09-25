#if !defined(WANLIX_CORE_C_H)
#define WANLIX_CORE_C_H

#define MODE_USR 0x01000000


extern U32 guiCurTask;


extern void WLX_ContextSwitch(STACKREG* pstrCurTaskStackRegAddr,
                              STACKREG* pstrNextTaskStackRegAddr);
extern void WLX_SwitchToTask(STACKREG* pstrNextTaskStackRegAddr);
#endif // WANLIX_CORE_C_H
