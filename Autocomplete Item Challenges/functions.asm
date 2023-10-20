PUBLIC ItemChallengeInjectCode

EXTERN itemChallengeJmpAddr:QWORD

.code

ItemChallengeInjectCode proc
    mov [rdx+30h], ecx
    cmp ecx, [rdx+30h]
    jmp [itemChallengeJmpAddr]
ItemChallengeInjectCode endp

end