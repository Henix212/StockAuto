#include "I2C.h"

int main(int argc, char const *argv[])
{   
    // Initialize the I2C peripheral
    if (I2C_Init() != 1) {
        // Initialization failed, handle error
        while (1);
    }

    // Main loop
    while (1) {
        // Your main code here
    }

    return 0;
}