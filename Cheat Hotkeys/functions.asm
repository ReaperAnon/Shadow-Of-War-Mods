PUBLIC InfiniteHealthInjectCode

EXTERN infiniteHealthJmpAddr:QWORD

.code

InfiniteHealthInjectCode proc
    mov     rdx, [rsi+8h]
    mov     rdx, [rdx]
    test    dword ptr [rdx+90h], 100h
    je      Skip
    movups  xmm2, [rbx+428h]

    Skip:
    movups  [rbx+42Ch], xmm2
    comiss  xmm6, xmm2
    jmp     [infiniteHealthJmpAddr]
InfiniteHealthInjectCode endp

end