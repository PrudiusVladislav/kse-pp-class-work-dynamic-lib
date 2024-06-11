#include <iostream>
#include <windows.h>
#include <tchar.h>

typedef char*(*function_ptr)(char*);

void testStrUtil(HINSTANCE handle, const char *functionName, const char *input)
{
    auto function = (function_ptr)GetProcAddress(handle, TEXT(functionName));
    if (function == nullptr)
    {
        std::cout << "Function '" << functionName << "' not found" << std::endl;
        FreeLibrary(handle);
        return;
    }

    char *result = function(const_cast<char*>(input));
    std::cout << "Function '" << functionName << "' called with input '" << input << "'" << std::endl;
    std::cout << "Result: " << result << std::endl;
}

char* getDllPath(const char *dllName)
{
    std::string path = R"(C:\C\kse-pp-class-work-dynamic-lib\)";
    path += dllName;
    char *result = new char[path.length() + 1];
    strcpy(result, path.c_str());
    return result;
}

int main()
{
    const char *dllName = "string_utils.dll";
    char *dllPath = getDllPath(dllName);
    std::cout << "Loading lib '" << dllName << "' from '" << dllPath << "'" << std::endl;

    HINSTANCE handle = LoadLibrary(TEXT(dllPath));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
    {
        std::cout << "Lib '" << dllName << "' not found" << std::endl;
        return -1;
    }

    std::cout << "Lib '" << dllName << "' loaded" << std::endl;

    testStrUtil(handle, "trim", "  Hello, World!  ");
    testStrUtil(handle, "toLower", "Hello, World!");
    testStrUtil(handle, "toUpper", "Hello, World!");
    testStrUtil(handle, "reverse", "Hello, World!");

    FreeLibrary(handle);

    return 0;
}