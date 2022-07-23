#include "general.h"
#ifdef _WIN32
#include <io.h>
/* Values for the second argument to access.
   These may be OR'd together.  */
#define R_OK 4 /* Test for read permission.  */
#define W_OK 2 /* Test for write permission.  */
//#define   X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK 0 /* Test for existence.  */
#define access _access
#else
#include <unistd.h>
#endif

bool is_writeable(char *dir)
{
    if (access(dir, W_OK) == 0) {
        return true;
    }
    return false;
}
