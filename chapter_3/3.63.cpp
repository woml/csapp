//3.63
long switch_prob(long x, long n) {
    long result = x;
    switch(n) {
        case 60:
        case 62: {
            result = 8 * x;
            break;
        }
        case 63: {
            result = x >> 3;
        }
        case 64: {
            x = (result << 4) - x;
        }
        case 65: {
            x = x * x;
        }

        default: result = x + 75;
    }
    return result;
}
// x in %rdi, n in %rsi
//关键是第五行 jmpq *0x4006f8(,%rsi,8) 通过n的变化从该地址得到不同的跳转地址，也就是跳到了不同的case




