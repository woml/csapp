//3.58
// x in %rdi, y in %rsi, z in %rdx

/*decode2:
    subq %rdx, %rsi
    imulq %rsi, %rdi
    movq %rsi, %rax
    salq $63, %rax
    sarq $63, %rax
    xorq %rdi, %rax
    ret
*/

long decode2(long x, long y, long z) {
    x *= (y - z);
    y <<= 63;
    y >>= 63;
    return y ^ x;
}
