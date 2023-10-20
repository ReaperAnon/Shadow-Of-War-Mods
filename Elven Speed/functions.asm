PUBLIC ElvenSpeedInjectCode

EXTERN elvenSpeedJmpAddr:QWORD
EXTERN elvenSpeedDrain:DWORD
EXTERN elvenSpeedRegen:DWORD

.code

ElvenSpeedInjectCode proc
    movups  xmm7, [rbx+108h]        ; xmm7 has the drain value
    pushfq
    comiss  xmm7, [elvenSpeedDrain] ; if the drain value is equal to elven speed's focus drain
    jne     Skip
    movss   xmm7, [elvenSpeedRegen] ; set the focus cost to the regular focus regen rate * our mult

    Skip:
    popfq
    jmp     [elvenSpeedJmpAddr]
ElvenSpeedInjectCode endp

end