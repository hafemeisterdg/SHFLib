#define OS_Windows
#define OS_IMPL

#include "os.h"

#include <stdio.h>

void window_callback(Os_Keycode keycode, Os_Key_Action action, Os_Key_Modifiers mods) {
    printf("Keycode: %hu     Action: %hhu \n", keycode, action);
}

int main(int argc, char* argv[]) {
    Os_Window_Configuration config;
    config.title  = "Test Window";
    config.width  = 1280;
    config.height = 720;
    
    Os_Window window;
    if(os_window_create(&window, &config)) {
        os_window_set_key_callback(&window, window_callback);
        os_window_show(&window);
        
        while(!os_window_should_close(&window)) {
            os_window_poll(&window);
        }
        
        os_window_destroy(&window);
    }
    
    return 0;
}