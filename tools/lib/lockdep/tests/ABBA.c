#include <liblockdep/mutex.h>
#include "common.h"

void main(void)
{
    pthread_mutex_t a, b;

    pthread_mutex_init(&a, NULL);
    pthread_mutex_init(&b, NULL);

    LOCK_UNLOCK_2(a, b);
    LOCK_UNLOCK_2(b, a);
}
