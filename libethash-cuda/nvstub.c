/*
This file is part of ethminer.

ethminer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ethminer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ethminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#if defined(__linux__)
#include <dlfcn.h>
#endif
#if defined(_WIN32)
#include <stdlib.h>
#include <windows.h>
#endif

#include "nvstub.h"

nvrtcResult ppCompileProgram(nvrtcProgram prog, int numOptions, const char** options)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcCompileProgram(prog, numOptions, options);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppGetProgramLogSize(nvrtcProgram prog, size_t* logSizeRet)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcGetProgramLogSize(prog, logSizeRet);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppAddNameExpression(nvrtcProgram prog, const char* name_expression)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcAddNameExpression(prog, name_expression);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppGetPTX(nvrtcProgram prog, char* ptx)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcGetPTX(prog, ptx);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppGetPTXSize(nvrtcProgram prog, size_t* ptxSizeRet)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcGetPTXSize(prog, ptxSizeRet);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppVersion(int* major, int* minor)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcVersion(major, minor);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppCreateProgram(nvrtcProgram* prog, const char* src, const char* name, int numHeaders,
    const char** headers, const char** includeNames)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcCreateProgram(prog, src, name, numHeaders, headers, includeNames);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppGetProgramLog(nvrtcProgram prog, char* log)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcGetProgramLog(prog, log);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppGetLoweredName(
    nvrtcProgram prog, const char* name_expression, const char** lowered_name)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcGetLoweredName(prog, name_expression, lowered_name);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult ppDestroyProgram(nvrtcProgram* prog)
{
#if !defined(_WIN32) && !defined(__linux__)
    return nvrtcDestroyProgram(prog);
#else
    return NVRTC_ERROR_INTERNAL_ERROR;
#endif
}

nvrtcResult (*CompileProgram)(
    nvrtcProgram prog, int numOptions, const char** options) = ppCompileProgram;
nvrtcResult (*GetProgramLogSize)(nvrtcProgram prog, size_t* logSizeRet) = ppGetProgramLogSize;
nvrtcResult (*AddNameExpression)(
    nvrtcProgram prog, const char* name_expression) = ppAddNameExpression;
nvrtcResult (*GetPTX)(nvrtcProgram prog, char* ptx) = ppGetPTX;
nvrtcResult (*GetPTXSize)(nvrtcProgram prog, size_t* ptxSizeRet) = ppGetPTXSize;
nvrtcResult (*Version)(int* major, int* minor) = ppVersion;
nvrtcResult (*CreateProgram)(nvrtcProgram* prog, const char* src, const char* name, int numHeaders,
    const char** headers, const char** includeNames) = ppCreateProgram;
nvrtcResult (*GetProgramLog)(nvrtcProgram prog, char* log) = ppGetProgramLog;
nvrtcResult (*GetLoweredName)(
    nvrtcProgram prog, const char* name_expression, const char** lowered_name) = ppGetLoweredName;
nvrtcResult (*DestroyProgram)(nvrtcProgram* prog) = ppDestroyProgram;

#if defined(_WIN32)
static int findNvrtcDllInPath(char* searchPath, char* dllPath, int maxChars)
{
    char tempPath[_MAX_PATH];
    strcpy_s(tempPath, sizeof(tempPath), searchPath);
    if (strlen(tempPath) && (tempPath[strlen(tempPath) - 1] != '\\'))
        strcat_s(tempPath, sizeof(tempPath), "\\");
    strcat_s(tempPath, sizeof(tempPath), "nvrtc64_*.dll");
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind;
    hFind = FindFirstFile(tempPath, &FindFileData);
    if (hFind == INVALID_HANDLE_VALUE)
        return 0;
    FindClose(hFind);
    strcpy_s(dllPath, maxChars, searchPath);
    if (strlen(dllPath) && (dllPath[strlen(dllPath) - 1] != '\\'))
        strcat_s(dllPath, maxChars, "\\");
    strcat_s(dllPath, maxChars, FindFileData.cFileName);
    return 1;
}

static int findNvrtcDll(char* dllPath, int maxChars)
{
    char path[_MAX_PATH];
    char dirPath[_MAX_PATH];
    char drive[_MAX_DRIVE];

    // The directory from which the application loaded.
    int bytes = GetModuleFileName(NULL, path, sizeof(path));
    if (bytes == 0)
        return 0;
    _splitpath_s(path, drive, sizeof(drive), dirPath, sizeof(dirPath), NULL, 0, NULL, 0);
    strcpy_s(path, sizeof(path), drive);
    strcat_s(path, sizeof(path), dirPath);
    if (findNvrtcDllInPath(path, dllPath, maxChars))
        return 1;

    // The current directory.
    if (GetCurrentDirectory(MAX_PATH, path))
    {
        if (findNvrtcDllInPath(path, dllPath, maxChars))
            return 1;
    }

    // The system directory.Use the GetSystemDirectory function to get the path of this directory.
    if (GetSystemDirectory(path, _MAX_PATH))
    {
        if (findNvrtcDllInPath(path, dllPath, maxChars))
            return 1;
    }

    // The Windows directory.Use the GetWindowsDirectory function to get the path of this directory.
    if (GetWindowsDirectory(path, _MAX_PATH))
    {
        if (findNvrtcDllInPath(path, dllPath, maxChars))
            return 1;
    }

    // The directories that are listed in the PATH environment variable.
    DWORD size = GetEnvironmentVariable("PATH", NULL, 0);
    char* env = malloc(size);
    int rc = 0;
    if (env)
    {
        rc = 1;
        GetEnvironmentVariable("PATH", env, size);
        char* cp = env;
        while (*cp)
        {
            char* cp2 = strchr(cp, ';');
            if (cp2)
            {
                *cp2 = 0;
                if (findNvrtcDllInPath(cp, dllPath, maxChars))
                    break;
                cp = cp2 + 1;
            }
            else
            {
                rc = findNvrtcDllInPath(cp, dllPath, maxChars);
                break;
            }
        }
        free(env);
    }

    return rc;
}
#endif

void InitNVStub()
{
#if defined(__linux__)
    void* dl = dlopen("libnvrtc.so", RTLD_NOW);
    if (dl == (void*)0)
        return;
    CompileProgram = dlsym(dl, "nvrtcCompileProgram");
    GetProgramLogSize = dlsym(dl, "nvrtcGetProgramLogSize");
    AddNameExpression = dlsym(dl, "nvrtcAddNameExpression");
    GetPTX = dlsym(dl, "nvrtcGetPTX");
    GetPTXSize = dlsym(dl, "nvrtcGetPTXSize");
    Version = dlsym(dl, "nvrtcVersion");
    CreateProgram = dlsym(dl, "nvrtcCreateProgram");
    GetProgramLog = dlsym(dl, "nvrtcGetProgramLog");
    GetLoweredName = dlsym(dl, "nvrtcGetLoweredName");
    DestroyProgram = dlsym(dl, "nvrtcDestroyProgram");
#endif
#if defined(_WIN32)
    char dllPath[_MAX_PATH];
    if (!findNvrtcDll(dllPath, sizeof(dllPath)))
        return;
    HINSTANCE hDLL = LoadLibrary(dllPath);

    if (!hDLL)
        return;
    CompileProgram = (void*)GetProcAddress(hDLL, "nvrtcCompileProgram");
    GetProgramLogSize = (void*)GetProcAddress(hDLL, "nvrtcGetProgramLogSize");
    AddNameExpression = (void*)GetProcAddress(hDLL, "nvrtcAddNameExpression");
    GetPTX = (void*)GetProcAddress(hDLL, "nvrtcGetPTX");
    GetPTXSize = (void*)GetProcAddress(hDLL, "nvrtcGetPTXSize");
    Version = (void*)GetProcAddress(hDLL, "nvrtcVersion");
    CreateProgram = (void*)GetProcAddress(hDLL, "nvrtcCreateProgram");
    GetProgramLog = (void*)GetProcAddress(hDLL, "nvrtcGetProgramLog");
    GetLoweredName = (void*)GetProcAddress(hDLL, "nvrtcGetLoweredName");
    DestroyProgram = (void*)GetProcAddress(hDLL, "nvrtcDestroyProgram");
#endif
}
