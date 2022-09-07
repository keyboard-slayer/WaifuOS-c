#ifndef LIBC_EXT_MACRO_H
#define LIBC_EXT_MACRO_H

#define PACKED						__attribute__((packed))
#define NORETURN					__attribute__((noreturn))
#define USED						__attribute__((used))
#define UNREACHABLE					__builtin_unreachable()
#define ALIGN_DOWN(__addr, __align) ((__addr) & ~((__align) -1))
#define ALIGN_UP(__addr, __align)	(((__addr) + (__align) -1) & ~((__align) -1))
#define FALLTHROUGH					__attribute__((fallthrough));
#define KIB(x)						((uint64_t) x << 10)
#define MIB(x)						((uint64_t) x << 20)
#define GIB(x)						((uint64_t) x << 30)
#define MAX(x, y)					((x) > (y) ? (x) : (y))

/* clang-format off */
#define EMBED(NAME, FILE)	        __asm__(".global " #NAME "\n" #NAME ": .incbin \"" FILE "\"\n"); \
                                    extern uint8_t (NAME)[]

#endif /* !LIBC_EXT_MACRO_H */
