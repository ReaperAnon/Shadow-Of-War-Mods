PUBLIC MyrianChangeCode

EXTERN myrianJmpAddress:QWORD
EXTERN myrianLossMult:DWORD
EXTERN myrianGainMult:DWORD

.code

MyrianChangeCode proc
    push    r9
    mov     r9, [r9]
    cmp     dword ptr [r9+4h], 23B603FBh
    pop     r9
    jne     Skip
        push        rcx              ; r10d is new value
        mov         ecx, r10d        ; [r9+20h] is old value
        sub         ecx, [r9+20h]    ; ecx = new - old
        pxor        xmm0, xmm0
        cvtsi2ss    xmm0, ecx
        cmp         ecx, 0h
        jg          Positive         ; signed jump

        Negative:
        mulss       xmm0, [myrianLossMult]
        jmp         Assign

        Positive:
        ;mulss       xmm0, [myrianGainMult]

        Assign:
        cvttss2si   ecx, xmm0
        add         ecx, [r9+20h]
        mov         r10d, ecx
        pop         rcx

    Skip:
    jmp     [myrianJmpAddress]
MyrianChangeCode endp

end