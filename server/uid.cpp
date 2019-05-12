#include <uid.h>

static uint32_t current_uid = 0;

uint32_t generate_uid(void) { return current_uid++; }
