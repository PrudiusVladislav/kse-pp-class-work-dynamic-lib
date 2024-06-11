#include "string-utils-library.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>

extern "C" {
    __declspec(dllexport) char *trim(const char *str) {
        while (isspace((unsigned char)*str)) {
            str++;
        }

        char *end = strdup(str);
        if (*end == 0) {
            return end;
        }

        char *back = end + strlen(end);
        while (isspace((unsigned char)*(--back)));
        *(back+1) = '\0';

        return end;
    }

    __declspec(dllexport) char *toLower(const char *str) {
        char *result = strdup(str);
        for (char *p = result; *p; ++p) {
            *p = tolower((unsigned char)*p);
        }

        return result;
    }

    __declspec(dllexport) char *toUpper(const char *str) {
        char *result = strdup(str);
        for (char *p = result; *p; ++p) {
            *p = toupper((unsigned char)*p);
        }

        return result;
    }

    __declspec(dllexport) char *reverse(const char *str) {
        char *result = strdup(str);
        char *start = result;
        char *end = start + strlen(start) - 1;

        while (end > start) {
            char temp = *start;
            *start = *end;
            *end = temp;

            ++start;
            --end;
        }

        return result;
    }
}