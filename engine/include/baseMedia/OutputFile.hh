#ifndef _OUTPUT_FILE_HH
#define _OUTPUT_FILE_HH

#include <BaseEnv.hh>
#include <stdio.h>

FILE* OpenOutputFile(BaseEnv& env, char const* fileName);

void CloseOutputFile(FILE* fid);

#endif
