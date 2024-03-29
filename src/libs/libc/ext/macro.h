#ifndef LIBS_LIBC_EXT_MACRO_H
#define LIBS_LIBC_EXT_MACRO_H

#define PACKED						__attribute__((packed))
#define NORETURN					__attribute__((noreturn))
#define USED						__attribute__((used))
#define UNUSED						__attribute__((unused))
#define UNREACHABLE					__builtin_unreachable()
#define ALIGN_DOWN(__addr, __align) ((__addr) & ~((__align) -1))
#define ALIGN_UP(__addr, __align)	(((__addr) + (__align) -1) & ~((__align) -1))
#define FALLTHROUGH					__attribute__((fallthrough));
#define KIB(x)						((uint64_t) x << 10)
#define MIB(x)						((uint64_t) x << 20)
#define GIB(x)						((uint64_t) x << 30)
#define MAX(x, y)					((x) > (y) ? (x) : (y))
#define IRQ(x)						(x + 32)

#define GET_ARG_COUNT(__args...)                                                                                       \
 __GET_ARG_COUNT(0, ##__args, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49,  \
				 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24,   \
				 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define __GET_ARG_COUNT(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_,     \
						_17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_,      \
						_32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49,  \
						_50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, \
						_69, _70, count, ...)                                                                          \
 count

/* clang-format off */
#define EMBED(NAME, FILE)	        __asm__(".global " #NAME "\n" #NAME ": .incbin \"" FILE "\"\n"); \
                                    extern uint8_t (NAME)[]

#endif /* LIBS_LIBC_EXT_MACRO_H */
