#include <vector>
#include "strformat.h"

String vformat(const char *fmt, ...)
{
    // Allocate a buffer on the stack that's big enough for us almost
    size_t size = 1024;
    char stackbuf[1024];
    std::vector<char> dynamicbuf;
    char *buf = &stackbuf[0];
    va_list ap;
    va_list ap_copy;
    va_start(ap, fmt);
    va_copy(ap_copy, ap);

    int needed = vsnprintf(buf, size, fmt, ap);
    va_end(ap_copy);
    return String(buf);
}