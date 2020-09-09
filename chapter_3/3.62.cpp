//3.62

typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action) {
    long result = 0;
    switch(action) {
        case MODE_A: {
            result = *p1;
        }
        case MODE_B: {
            *p1 = *p2 + *p1;
        }
        case MODE_C: {
            *p1 = 59;
            result = *p2;
        }
        case MODE_D: {
            *p1 = *p2;
            result = 27;
        }
        case MODE_E: {
            result = 27;
        }
        default: {
            result = 12;
        }
    }
    return result;
}

__asm__(
    //p1 in %rdi, p2 in %rsi, action in %edx
    ".L8:"
        "movl $27, %eax"        //MODE_E
        "ret"
    ".L3:"
        "movq (%rsi), %rax"     //MODE_A
        "movq (%rdi), %rdx"
        "movq %rdx, (%rsi)"
        "ret"
    ".L5:"
        "movq (%rdi), %rax"     //MODE_B
        "addq (%rsi), %rax"
        "movq %rax, (%rdi)"
        "ret"
    ".L6:"
        "movq $59, (%rdi)"      //MODE_C
        "movq (%rsi), %rax"
        "ret"
    ".L7:"
        "movq (%rsi), %rax"     //MODE_B
        "movq %rax, %(rdi)"
        "movl $27, %eax"
        "ret"
    ".L9:"
        "movl $12, %eax"        //default
        "ret"
)