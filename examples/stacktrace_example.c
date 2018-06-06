#include <errorinterceptor/errorinterceptor.h>

#include <stdlib.h>

bool foo(void *parameter) {
    if (!parameter) {
        ei_stacktrace_push_msg("Specified parameter is invalid");
        return false;
    }

    return true;
}

bool bar(void *parameter) {
    if (!foo(parameter)) {
        ei_stacktrace_push_msg("foo failed :(");
        return false;
    }

    return true;
}

/**
 * output:
 * bar failed ! (thread 140371337471744)
 * Caused by: Specified parameter is invalid
 *    at foo (stacktrace_example.c:7)
 *    at bar (stacktrace_example.c:16)
 *    at main (stacktrace_example.c:31)
 */
int main() {
    void *arg;

    arg = NULL;

    ei_init();

    if (!bar(arg)) {
        ei_stacktrace_push_msg("bar failed !");
    }

    ei_stacktrace_print();

    ei_uninit();

    return EXIT_SUCCESS;
}
