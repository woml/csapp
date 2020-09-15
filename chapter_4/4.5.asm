; 4.5
;long sum(long *start, long count)
;satrt in %rdi, count in %rsi
sum:
    irmovq $8, %r8
    irmovq $1, %r9
    xor %rax, %rax
    andq %rsi, %rsi
    jmp test
loop:
    mrmovq (%rdi), %r10
    xor %r11, %r11
    sub %r10, %r11      ;get -x & update 条件码
    jl  pos             ;x > 0时 0-x<0 不用取绝对值 跳过下一条指令
    rrmovq %r11, %r10   ;将-x移动到%r10中
pos:
    addq %r10, %rax
    addq %r8, %rdi
    subq %r9, %rsi
test:
    jne loop
    ret