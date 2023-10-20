PUBLIC RarityHook

EXTERN commonIdx:DWORD
EXTERN epicIdx:DWORD
EXTERN legendaryIdx:DWORD

EXTERN epicChance:DWORD
EXTERN legendaryChance:DWORD

EXTERN rarityJmpAddr:QWORD

EXTERN GetRandomNumber:PROC

.code

RarityHook proc
    push    rax
    push    rcx
    push    r11

    push    rdx
    push    r8
    push    r9
    push    r10
    call    GetRandomNumber
    mov     r11, rax
    call    GetRandomNumber
    pop     r10
    pop     r9
    pop     r8
    pop     rdx

    mov     ecx,    [commonIdx] ; set common rarity
    cmp     r11d,   [epicChance]
    cmovbe  ecx,    [epicIdx] ; set epic rarity
    pop     r11
    cmp     eax,    [legendaryChance]
    cmovbe  ecx,    [legendaryIdx] ; set legendary rarity
    cmp     ecx,    [commonIdx]
    je      Original

    Conditions:
    cmp     dword ptr [rdx+4], 0E6FC03C6h
    je      Branch1
    cmp     dword ptr [rdx+4], 07AEAD12h
    je      Branch2

    Original:
    pop     rcx
    pop     rax
    jmp     [rarityJmpAddr]

    Branch1:
    mov     rax, [rdx+10h] ; base
    cmp     ecx, [epicIdx]
    cmove   rax, [rax+20h] ; epic rarity
    cmp     ecx, [legendaryIdx]
    cmove   rax, [rax+30h] ; legendary rarity
    pop     rcx
    add     rsp, 8 ; remove the value of rax from the stack
    ret

    Branch2:
    mov     rax, [rdx+10h] ; base
    cmp     ecx, [epicIdx]
    cmove   rax, [rax+18h] ; epic rarity
    cmp     ecx, [legendaryIdx]
    cmove   rax, [rax+28h] ; legendary rarity
    pop     rcx
    add     rsp, 8 ; remove the value of rax from the stack
    ret
RarityHook endp

end