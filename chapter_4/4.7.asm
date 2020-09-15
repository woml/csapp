;4.7
;my machine test push %rsp
    .text
.global pushtest
pushtest:
    movq %rsp, %rax
    pushq %rsp
    popq %rdx
    sub %rdx, %rax
    ret