PUBLIC AbilityCheckHook

EXTERN abilityCheckJmpAddress:QWORD
EXTERN isKeyHeld:BYTE
EXTERN stunBehavior:DWORD
EXTERN flurryBehavior:DWORD

.code

AbilityCheckHook proc
    pushfq
    push    rax

    mov     rax, rdx                ; save the skill index
    mov     edx, [r10+rdx*4]

    cmp     rax, 2                  ; check if it's loading the flurry address | skilldb[2]
        je      Flurry

    cmp     rax, 129                ; check if it's loading the stun address | skilldb[129]
        je      Stun

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
    pop     rax
    popfq
    bt      edx, r8d
    jmp [abilityCheckJmpAddress]
AbilityCheckHook endp

end
