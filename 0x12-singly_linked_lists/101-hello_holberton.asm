section .data
    msg db "Hello, Holberton", 0
section .text
    global main
    extern printf
main:
    push rbp
    mov rbp, rsp
    mov edi, msg
    xor eax, eax
    call printf
    xor eax, eax
    pop rbp
    ret
