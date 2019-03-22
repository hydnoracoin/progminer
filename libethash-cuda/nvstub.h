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

#pragma once

#if defined(__linux__) || defined(_WIN32)
#include <nvrtc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern nvrtcResult (*CompileProgram)(nvrtcProgram prog, int numOptions, const char** options);
extern nvrtcResult (*GetProgramLogSize)(nvrtcProgram prog, size_t* logSizeRet);
extern nvrtcResult (*AddNameExpression)(nvrtcProgram prog, const char* name_expression);
extern nvrtcResult (*GetPTX)(nvrtcProgram prog, char* ptx);
extern nvrtcResult (*GetPTXSize)(nvrtcProgram prog, size_t* ptxSizeRet);
extern nvrtcResult (*Version)(int* major, int* minor);
extern nvrtcResult (*CreateProgram)(nvrtcProgram* prog, const char* src, const char* name,
    int numHeaders, const char** headers, const char** includeNames);
extern nvrtcResult (*GetProgramLog)(nvrtcProgram prog, char* log);
extern nvrtcResult (*GetLoweredName)(
    nvrtcProgram prog, const char* name_expression, const char** lowered_name);
extern nvrtcResult (*DestroyProgram)(nvrtcProgram* prog);

extern void InitNVStub();

#ifdef __cplusplus
}
#endif
