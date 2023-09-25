    INCLUDE wanlix_core_a

WLX_ContextSwitch

    ;保存当前任务的栈信息
    STMIA R0!, {R4 - R14} ;保存R4-R14
    MRS R2, XPSR    ;获取XPSR
    STMIA R0, {R2}          ;保存到寄存器组中的XPSR

    LDMIA R1! {R4 - R13};
    ADD R1, #4
    LDMIA R1, {R0}
    MSR XPSR, R0
    SUB R1, #4
    LDMIA R1, {PC}  ;切换任务


    
WLX_SwitchToTask

    ;恢复将要运行的栈任务并运行新任务
    ;R0保存的是TCB中的stack
    LDMIA R0!, {R4 - R12}   ;恢复r4 - 12
    LDMIA R0， {R3}         ;sp
    ADD R0, #8              ;R0指向寄存器组中的XPSR
    LDMIA R0, {R1}          ;获取寄存器组中XPSR

    MSR XPSR, R1
    SUB R0, #4              ;指向LR

    LDMIA R0, {PC}          ;运行首个任务



