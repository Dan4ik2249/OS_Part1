#include "poem.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <cstring>
using namespace std;

#ifndef __SHARED_CPP__
#define __SHARED_CPP__

extern "C" char* asd(int a) {
    int count = 1;
    int c = a;
    char *cstr = NULL;
    if(poem[c] == '\0' || c == strlen(poem)) return cstr;
    while(poem[c] != '\n'){
        ++c;
        ++count;
    }
    cout << endl;
    cstr = (char*) malloc((count + 1) * sizeof(char));
    if(cstr==NULL) {
        cout << "Memory Allocation Failed\n";
        return cstr;
    }
    strncpy(cstr, &poem[a], count);
    cstr[count] = '\0';
    return cstr;
}
#endif
