//3.60
;long loop(long x, int n)
;x in %rdi, n in %esi

loop:
    movl %esi, %ecx     ;cx = n
    movl $1, %edx       ;mask = %rdx
    movl $0, %eax       ;result = %rax, 因为立即数只能是int 32位，即使是long赋给初值也得是movl，（本人猜测是这个机制）-> movl会把高位也清空，所以result = 0
    jmp .L2             
.L3:
    movq %rdi, %r8      ;备份x到%r8
    andq %rdx, %r8      ;%r8 &= mask
    orq %r8, %rax       ;result |= %r8
    salq %cl, %rdx      ;mask <<= %cl
.L2:
    testq %rdx, %rdx    ;cmp的另一种表示，但是cmp会改变值，testq不会
    jne .L3             ; != 0 ->.L3
    rep ret

long loop(long x, int n) {
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n % 256) {
        result |= (x & mask);
    }
    return result;
}
; 这个c代码是获得n及n的倍数位掩码的程序。例如x = 0~0_1111_1111_1111_1111, n = 3
;先是最低位与mask与，result（0）| 1 -> result(1) 然后mask <<= 3; mask = 1000 先和x与取出倒数第四位，
;再和result或，把第四位放进去等等。 所以若n = 3 就是与1000100010001～10001与
;所以可能n很小，汇编之后，cl不会超过256，这也是肯定的，因为long是64位，n最大64，否则再往上没有意义
;ps 网上很多答案直接 mask = mask << n， 本人增加了n对256的取余，虽说不是必要，但是还是加上了，因为cl是8位，2^8=256 仅此

