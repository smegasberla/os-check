#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "os_check.h"

int main(void)
{
    int count = is_windows() + is_linux() + is_macos() + is_ios() +
                is_android() + is_freebsd() + is_openbsd() + is_netbsd();

    assert(count == 1);
    assert(is_unix() == !is_windows());
    assert(is_bsd() == (is_freebsd() || is_openbsd() || is_netbsd()));
    assert(is_linux_kernel() == (is_linux() || is_android()));
    assert(is_posix() == is_unix());
    assert(is_nt() == is_windows());
    assert(is_posix() != is_nt());
    assert(os_name() != NULL && strlen(os_name()) > 2);

#if OS_CHECK_KNOWN
    assert(strcmp(os_name(), "unknown") != 0);
#else
    assert(strcmp(os_name(), "unknown") == 0);
#endif

    /* the macro and the function must always agree */
    assert(is_linux() == OS_CHECK_LINUX);
    assert(is_windows() == OS_CHECK_WINDOWS);
    assert(is_macos() == OS_CHECK_MACOS);
    assert(is_posix() == OS_CHECK_POSIX);
    assert(is_nt() == OS_CHECK_NT);

    printf("os-check: ok (%s)\n", os_name());
    return 0;
}
