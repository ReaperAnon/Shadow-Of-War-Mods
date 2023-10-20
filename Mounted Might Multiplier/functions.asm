PUBLIC MountedMightCode

EXTERN mountedMightJmpAddress:QWORD
EXTERN mightGainMult:DWORD

.code

MountedMightCode proc
    movd xmm1, [mightGainMult]
    mulss xmm0, xmm1
    movaps xmm1, xmm0
    mov rcx, rbx
    jmp [mountedMightJmpAddress]
MountedMightCode endp

end