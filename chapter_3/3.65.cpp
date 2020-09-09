#define M 15

void transpose(long A[M][M]) {
    long i, j;
    for (i = 0; i < M; i++) {
        for (j = 0; j < M; j++) {
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
    }
}

__asm__(
    ".L6:"
        "movq (%rdx), %rcx"
        "movq (%rax), %rsi"
        "movq %rsi, (%rdx)"
        "movq %rcx, (%rax)"
        "addq $8, %rdx"
        "addq $120, %rax"
        "cmpq %rdi, %rax"
        "jne .L6"
)
//此题c代码的意义是，数组沿对角线对称的一对数交换值
//突破口->因为最内层是j循环，所以当j+1时，A[i][j] + sizeof(A[0][0])即加一个数组元素大小长度
//此题为long，所以+8，而A[j][i]则加M*L = 120 -> M = 120/8 = 15
//dx+8,所以dx存A[i][j],cx+120,所以cx存A[j][i]
