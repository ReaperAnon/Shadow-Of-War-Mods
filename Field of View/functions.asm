PUBLIC FOVCode

EXTERN fovJmpAddr:QWORD
EXTERN minFOV:DWORD
EXTERN maxFOV:DWORD
EXTERN oldFOV:DWORD

.code

FOVCode proc
    ; original code
    movaps  xmm3, xmm0
    mov     ecx, [rax]

    movups  xmm0, [rax+4h]  ; actual FOV value
    movss   xmm2, [minFOV]  ; minimum FOV value
    movss   xmm1, [maxFOV]  ; maximum FOV value

    ucomiss xmm0, xmm1
    ja      Return          ; don't set FOV if new value would be above max
    ucomiss xmm2, xmm0
    ja      Return          ; don't set FOV if new value would be below min

    movss   xmm1, [oldFOV]
    ucomiss xmm0, xmm1
    ja      SetMax          ; if FOV is higher than the old max but lower than new, set it to new max

    subss   xmm0, xmm2
    subss   xmm1, xmm2

    divss   xmm0, xmm1

    movss   xmm1, [maxFOV]
    subss   xmm1, xmm2

    mulss   xmm0, xmm1
    addss   xmm0, xmm2
    jmp     Return

    SetMax:
    movss   xmm1, [maxFOV]
    movups  [rax+4h], xmm1

    Return:
    jmp     [fovJmpAddr]
FOVCode endp

end