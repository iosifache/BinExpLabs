BITS 32
    push 0x0a2173
    push 0x776f6c6c
    push 0x65662073
    push 0x62614c70
    push 0x78456e69
    push 0x42202c6f
    push 0x6c6c6548
    mov edx, 27
    mov ecx, esp
    mov ebx, 1
    mov eax, 4
    int 0x80
    mov ebx, 0
    mov eax, 1
    int 0x80
    ret