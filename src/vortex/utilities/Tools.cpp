#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vortex/utilities/Tools.h"

namespace vortex {
    bool Tools::isNull(void *obj) {
        return obj == NULL || obj == nullptr;
    }

    char* Tools::concatString(const char *s1, const char *s2) {
        char *result = (char*)malloc(strlen(s1) + strlen(s2) + 1);
        strcpy(result, s1);
        strcat(result, s2);
        return result;
    }
}