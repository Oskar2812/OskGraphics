#include <inttypes.h>

typedef struct OskWindow OskWindow;

OskWindow* OpenWindow(uint32_t width, uint32_t height, const char* title);

void DestroyOskWindow(OskWindow* window);

int PollEvents();