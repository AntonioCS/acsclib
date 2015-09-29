/* 
 * File:   minunit.h
 * http://www.jera.com/techinfo/jtns/jtn002.html
 *
 */

#ifndef MINUNIT_H
#define	MINUNIT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define mu_assert(message, test) do { \
                                    asserts_run++; \
                                    if (!(test)) {\
                                        return message; \
                                    } \
                                 } while (0)
    
#define mu_run_test(test) do { \
                            char *message = test(); \
                            tests_run++; \
                            if (message) { \
                                printf("Failed at test number: %d\n", tests_run -1);\
                                return message; \
                            } \
                          } while (0)
    extern int tests_run;
    extern int asserts_run;

#define mu_main(void) int main(int argc, char** argv) { \
    char *result = all_tests(); \
    \
    if (result != 0) { \
        printf("Test error msg: %s\n", result); \
    } else { \
        printf("ALL TESTS PASSED\n"); \
    } \
    printf("Tests run: %d\nAsserts executed: %d\n", tests_run, asserts_run); \
 \
    return result != 0; \
} \

#define mu_all_tests(...) static char *all_tests() {\
\
    testFuncPtr funcs[] = {\
        __VA_ARGS__\
    };\
\
    for (int funcsPosition = 0, max = (sizeof(funcs) / sizeof(funcs[0])); funcsPosition < max; funcsPosition++) {\
        mu_run_test(funcs[funcsPosition]);\
    }\
    \
    return 0;\
}\


    typedef char *(*testFuncPtr)(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MINUNIT_H */

