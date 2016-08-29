#include <stdlib.h>
#include <math.h>
#include "src/SOIL.h"

int main()
{
    int width, height;
    unsigned char* image = SOIL_load_image("container.jpg", &width, &height, 0, SOIL_LOAD_RGB);
    return 0;
}
