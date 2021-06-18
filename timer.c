#include <time.h>

struct tm* gettime() {
    time_t t = time(NULL); //1623522751   
    return gmtime(&t);
}
