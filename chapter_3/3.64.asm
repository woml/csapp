long A[R][S][T];

long store_ele(long i, long j, long k, long *dest) {
    *dest = A[i][j][k];
    return sizeof(A);
}

;long store_ele(long i, long j, long k, long *dest) 
;i in %rdi, j in %rsi, k in %rdx, dest in %rcx
store_ele:
    leaq (%rsi, %rsi, 2), %rax
    leaq (%rsi, %rax, 4), %rax
    movq %rdi, %rsi         ;和下两行一起生成65i
    salq $6, %rsi           
    addq %rsi, %rdi
    addq %rax, %rdi         ;%rdi = 65i + 13j
    addq %rdi, %rdx         ;%rdx = 65i + 13j + k
    movq A(, %rdx, 8), %rax ;算出偏移地址，因为是long 8位 所以乘8
    movq %rax, (%rcx)       
    movl $3640, %eax        ;= L*R*S*T
    ret

;A[i][j][k]的位置公式 A + L*(i*S*T + j*T + k)
;此题L = 8，T = 13， S = 65/13 = 5,， R通过sizeof(A)得出 R = 3640/(8*5*13) = 7