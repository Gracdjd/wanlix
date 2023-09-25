    INCLUDE wanlix_core_a

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



