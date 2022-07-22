#include "general.h"
#include <unistd.h>


bool is_writeable(char* dir)
{
    if (access(dir, W_OK) == 0)
    {
        return true;
    }
    return false;
}
