PUBLIC UrukIntelInjectCode

EXTERN urukIntelJmpAddress:QWORD
EXTERN partialIntel:WORD
EXTERN fullIntel:WORD

.code

UrukIntelInjectCode proc
    mov     edx, [rcx]
    cmp     word ptr [partialIntel], 1
    je      TempPartial
    cmp     word ptr [fullIntel], 1
    je      TempFull
    jmp     SkipTemp

    TempPartial:
    or      edx, 0DBh   ; Set temp uruk intel bitfield
    jmp     SkipTemp

    TempFull:
    or      edx, 0FBh    ; Set temp uruk intel bitfield

    SkipTemp:
    mov     [rcx], edx
    mov     edx, [rcx+0Ah]
    and     edx, 0FFFFFFFEh
    cmp     word ptr [partialIntel], 1
    je      PermPartial
    cmp     word ptr [fullIntel], 1
    je      PermFull
    jmp     SkipPerm

    PermPartial:
    or      edx, 1      ; Set perm uruk intel bitfield
    jmp     SkipPerm

    PermFull:
    or      edx, 2       ; Set perm uruk intel bitfield

    SkipPerm:
    mov     [rcx+0Ah], edx
    mov     edx, 3
    jmp     [urukIntelJmpAddress]
UrukIntelInjectCode endp

end