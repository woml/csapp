//3.61
#include <cstdio>
/*long cread(long *xp) {
    return (xp ? *xp : 0);
}
*/
int main(void) {
    return 0;
}
long cread_alt(long *xp) {
    return (!xp ? 0 : *xp);
}
//若是return(xp ? *xp : 0)，汇编则会先产生一个中间变量temp，先将temp = *xp
//然后才会检查xp 若xp为空则temp=0，不为空不变，所以会发生错误，当指针为空时，会访问*xp
//换个思路，上述会先将temp初值为*xp，即三目运算符的第二条，那我初值为0，即可以避免当指针为空时的访问
//即return(!xp ? 0 : *xp)，这样产生的汇编代码为
// cread_alt: (xp in %rdi)
// movl $0, %eax            ;ax为返回值，先将ax初始化为0，即三目运算符的第二项
// testq %rdi, %rdi         ;检测%rdi是否为零，即是否为空指针
// cmovne (%rdi), %rax      ;若%rdi为0，不执行此条，若%rdi不为0，则将
