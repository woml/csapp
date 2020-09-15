;4.6
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
    sub %r10, %r11      ;get -x & update 条件码，此时 x in %r10 -x in %r11
    cmovg %r11, %r10    ;若x < 0 则上一项会得到正值，所以要用cmovg 当上一项>0时，将-x->%r10
    addq %r10, %rax
    addq %r8, %rdi
    subq %r9, %rsi
test:
    jne loop
    ret