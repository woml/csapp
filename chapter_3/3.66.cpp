long NR(long n);
long NC(long n);

long sum_col(long n, long A[NR(n)][NC(n)], long j) {
    long i;
    long result = 0;
    for (i = 0; i < NR(n); i++) result += A[i][j];
    return result;
}

__asm__(
    //n in %rdi, A in %rsi, j in %rdx
    "sum_col:"
            "leaq 1(, %rdi, 4), %r8"        //4n+1->%r8
            "leaq (%rdi, %rdi, 2), %rax"    //3n->%rax
            "movq %rax, %rdi"               //n = 3n
            "testq %rax, %rax"              
            "jle .L4"                       //3n < 0 则到.L4 返回0
            "salq $3, %r8"                  //8*(4n+1)
            "leaq (%rsi, %rdx, 8), %rcx"    //&A[8j]->%rcx
            "movl $0, %eax"                 
            "movl $0, %edx"
        ".L3:"
            "addq (%rcx), %rax"             //i = 0 A[0][j]只有8j偏移量
            "addq $1, %rdx"
            "addq %r8, %rcx"
            "cmpq %rdi, %rdx"
            "jne .L3"
            "rep; ret"
        ".L4:"
            "movl $0, %eax"
            "ret"
)