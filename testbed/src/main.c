#include <core/logger.h>
#include <core/asserts.h>

// TODO: TEST
#include <platform/platform.h>

int main() {
    KFATAL("This is a fatal message: %f", 3.14f);
    KERROR("This is an error message: %f", 3.14f);
    KWARN("This is a warning message: %f", 3.14f);
    KINFO("This is an info message: %f", 3.14f);
    KDEBUG("This is a debug message: %f", 3.14f);
    KTRACE("This is a trace message: %f", 3.14f);

    platform_state state;
    if(platform_startup(&state, "Kohi Engine Testbed", 100, 100, 1280, 720)){
        while(TRUE){
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);
    return 0;
}