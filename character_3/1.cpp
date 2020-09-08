//practice 3.31
void switcher(long a, long b, long c, long *dest) {
    long val;
    switch(a) {         /* case A */
    case 5:
        c = b ^ 15;
        /* Fall through */
    case 0:             /* case B */
        val = c + 112;
        break;
    case 2:             /* case C */
    case 7:             /* case D */
        val = (b + c) << 2;
        break;
    case 4:             /* case E */
        val = a;
        break;
    default:
        val = b;
    }
    *dest = a;
}
// a in %rdi, b in %rsi, c in %rdx, dest in %rcx
/*
switcher:
    cmpq $7,%rdi
    ja .L2
    jmp *.L4(,%rdi,8)
    .section .rodata
.L7:
    xorq $15, %rsi
    movq %rsi, %rdx
.L3:
    leaq 112(%rdx), %rdi
    jmp .L6
.L5:
    leaq (%rdx,%rsi),%rdi
    salq $2, %rdi
    jmp .L6
.L2:
    movq %rsi, %rdi
.L6:
    movq %rdi, (%rcx)
    ret
*/
//首先，先看跳转表，把标号写在旁边，看比较之后大于多少，跳到哪里，那里就是default，比较的值就是标号的最大值，
//此题 标号从0～7，显然.L2是default，然后再看有case C和D 连载一起， 找跳转表 有两个.L5标号分别位2和7 所
//以caseC、D分别为2和7，再看，caseA没有jmp，对应的是.L7 所以caseB对应.L3，只剩caseE了 此时跳转表只剩.L6
//所以 caseE对应标号4，不做事情，所以是a=a 即 val=a