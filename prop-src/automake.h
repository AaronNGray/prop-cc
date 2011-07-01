#include <sys/stat.h>
#include <unistd.h>
#include "basics.h"

Bool out_of_date (const char * filename, struct stat& target);
