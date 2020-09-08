//3.59

/*typedef __int128 int128_t;

void store_prod(int128_t * dest, int64_t x, int64_t y) {
    *dest = x * (int128_t) y;
}
*/

; x = x_h * 2^64 + x_l    y = y_h * 2^64 + y_l
; x * y = (x_h * 2^64 + x_l) * (y_h * 2^64 + y_l) = x_h * y_h * 2^128 + (x_l * y_h + x_h * y_l) * 2^64 + x_l * y_l
; x_h * y_h * 2^128 双寄存器存不下，截断后全为零。所以只有后面有效
store_prod:
    movq %rdx, %rax     ;存到%rax，%rax -> y_l,%rdx -> y_h
    cqto                ;扩展到%rdx
    movq %rsi, %rcx     ;存到%rcx
    sarq $63, %rcx      ;将%rcx变成高位, %rcx -> x_h
    imulq %rax, %rcx    ;%rcx = y_l * x_h
    imulq %rsi, %rdx    ;%rdx = x_l * y_h
    addq %rdx, %rcx     ;%rcx = y_l * x_h + x_l * y_h
    mulq %rsi           ;%rsi = y_l * x_l  并且将得到的结果的高64位放入%rdx，低64位放入%rax中，所以此时的%rdx呗更新了，为低64位的进位
    addq %rcx, %rdx     ;将%rcx和来自低位的进位相加放入%rdx中
    movq %rax, (%rdi)   ;将低64位放入 *dest
    movq %rdx, 8(%rdi)  ;将高64位放入 *dest+8
    ret
