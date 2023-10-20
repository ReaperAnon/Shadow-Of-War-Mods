PUBLIC SkillReqInjectCode

EXTERN skillReqJmpAddr:QWORD

.code

SkillReqInjectCode proc
    mov ebp, 100
    mov rdi, rdx
    jmp [skillReqJmpAddr]
SkillReqInjectCode endp

end