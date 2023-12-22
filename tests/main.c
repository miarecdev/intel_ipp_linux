#include <stdio.h>
#include <ipp.h>
#include <ippsc.h>


int main()
{
    ippInit();
    const IppLibraryVersion * pVersion = ippGetLibVersion();
    printf("IPP version: %s, Build data: %s\n", pVersion->Version, pVersion->BuildDate);
    return 0;
}
