#define OS_Windows
#define OS_IMPL

#include "os.h"

int main(int argc, char* argv[]) {
    
    Os_Window_Configuration config;
    config.title  = "Test Window";
    config.width  = 1280;
    config.height = 720;
    
    Os_Window window;
    if(os_window_create(&window, &config)) {
        os_window_show(&window);
        
        while(!os_window_should_close(&window)) {
            os_window_poll(&window);
        }
        
        os_window_destroy(&window);
    }
    
    return 0;
}