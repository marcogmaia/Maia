#include <python3.7m/Python.h>

void threadPythonTest(int argc, char const *argv[]) {
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if(program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program); /* optional but recommended */
    Py_Initialize();
    PyRun_SimpleString("from time import time,ctime\n"
                       "print('Today is', ctime(time()))\n"
                       "for i in range(10):\n"
                       "    print(i**i)");
    if(Py_FinalizeEx() < 0) {
        exit(120);
    }
    PyMem_RawFree(program);
}
