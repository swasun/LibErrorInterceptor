#include <errorinterceptor/errorinterceptor.h>

#include <stdlib.h>

int main() {
    ei_init();

    ei_logger_trace("Loading library...");

    ei_logger_debug("Variable value is %d", 58);

    ei_logger_info("User %s is now connected", "username");

    ei_logger_warn("Loading time is consequently longer");

    ei_logger_error("Invalid password");

    ei_logger_fatal("Out of memory");

    ei_uninit();

    return EXIT_SUCCESS;
}
