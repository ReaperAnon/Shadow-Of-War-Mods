PUBLIC AbilityCheckHook

EXTERN abilityCheckJmpAddress:QWORD
EXTERN isKeyHeld:BYTE
EXTERN stunBehavior:DWORD
EXTERN flurryBehavior:DWORD

.code

AbilityCheckHook proc
    pushfq
    push    rax
    push    rcx

    mov     rax, rdx                ; save the skill index
    mov     edx, [r10+rdx*4]

    mov     rcx, [r10]              ; get max index
    sub     rcx, [r10+8h]
    sar     rcx, 2

    ; should be differentiating by the actor's skill database address
    ; but can't be bothered to find the different actor objects and map them
    ; technically still works, hopefully without issue

    cmp     rcx, 2                  ; if maxIdx <= 2 skip
        jb      Skip
    cmp     rax, 2                  ; check if it's loading the flurry address | skilldb[2]
        je      Flurry

    cmp     rcx, 129                ; if maxIdx <= 129 skip
        jb      Skip
    cmp     rax, 129                ; check if it's loading the stun address | skilldb[129]
        je      Stun

    Skip:
    jmp     Exit                    ; if not equal with either, skip

    Flurry:
    cmp     dword ptr [flurryBehavior], 0 
    je      FlurryHold              ; default normal attack
    jmp     FlurryNoHold            ; default flurry attack

    FlurryHold:
    mov     al, [isKeyHeld]
    test    al, al                  ; check if modifier is held
    jnz     Exit
            and     edx, 1Fh        ; turn it off when not held
    jmp     Exit

    FlurryNoHold:
    mov     al, [isKeyHeld]
    test    al, al                  ; check if modifier is held
    jz      Exit
            and     edx, 1Fh        ; turn it off when held
    jmp     Exit

    Stun:
    cmp     dword ptr [stunBehavior], 0
    je      StunHold                ; default normal stun
    jmp     StunNoHold              ; default frost stun

    StunHold:
    mov     al, [isKeyHeld]
    test    al, al                  ; check if modifier key is held
    jnz     Exit
        and     edx, 7Fh            ; turn it off when not held
    jmp     Exit

    StunNoHold:
    mov     al, [isKeyHeld]
    test    al, al                  ; check if modifier key is held
    jz      Exit
        and     edx, 7Fh            ; turn it off when held

    Exit:
    pop     rcx
    pop     rax
    popfq
    bt      edx, r8d
    jmp [abilityCheckJmpAddress]
AbilityCheckHook endp

end