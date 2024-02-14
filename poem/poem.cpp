#include <dlfcn.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;


int main() {

        int n = 0;
        char* s = NULL;
        char* cstr = NULL;
        char* vstr;
        s = (char*) malloc(1 * sizeof(char));
        if(s == NULL) {cout << "Memory Allocation Failed"; free(s); return 0;}
        s[0] = '\0';
        while(true) {

                void* handle = dlopen("./libshared.so", RTLD_LAZY);
                char* (*cosine)(int);
                if (!handle) {
                        fputs (dlerror(), stderr);
                        break;
                }
                cosine = (char* (*)(int))dlsym(handle, "asd");

                cstr = (cosine)(strlen(s));
                if(cstr == NULL) {break;}
                vstr = (char*) realloc(s, (strlen(s) + strlen(cstr) + 1) * sizeof(char));
                if(vstr == NULL) { cout << "Memory Re-allocation Failed\n"; break;}
                strcat(vstr, cstr);
                s = vstr;
                free(cstr);
                cstr = NULL;
		vstr = NULL;
                cout << n << ": " << s << endl;
                ++n;

                dlclose(handle);

        }

        cout << "finish\n";
        free(s);
        s = NULL;
	cout << "s == NULL\n";
        free(cstr);
        cstr = NULL;
	cout << "cstr == NULL\n";
	free(vstr);
	vstr = NULL;
	cout << "vstr == NULL\n";
        return 0;
}
