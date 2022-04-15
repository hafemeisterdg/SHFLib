/* date = April 7th 2022 11:46 am */

#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include <stdbool.h>
#include <stdint.h>

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t  i8;

typedef double f64;
typedef float  f32;

typedef char* c_string;

#define internal static
#define global   static
#define local    static

#define Kilobyte(x) (x * 1024ULL)
#define Megabyte(x) (Kilobyte(x) * 1024ULL)
#define Gigabyte(x) (Megabyte(x) * 1024ULL)
#define Terabyte(x) (Gigabyte(x) * 1024ULL)

#endif //TYPE_DEFINITIONS_H

#ifndef OS_H
#define OS_H

typedef struct Os_Cmd    Os_Cmd;
typedef struct Os_File   Os_File;
typedef struct Os_Lib    Os_Lib;     // Mostly implemented
typedef struct Os_Proc   Os_Proc;
typedef struct Os_Socket Os_Socket;  // Mostly implemented
typedef struct Os_Thread Os_Thread;
typedef struct Os_Window Os_Window;  // Mostly implemented

typedef enum Os_Socket_Protocol {
    SOCKET_PROTO_TCP,
    SOCKET_PROTO_UDP
} Os_Socket_Protocol;

typedef struct Os_Window_Configuration {
    c_string title;
    u32      width;
    u32      height;
} Os_Window_Configuration;

internal bool   os_lib_load(Os_Lib* lib, c_string library_name);
internal void   os_lib_unload(Os_Lib* lib);
internal void*  os_lib_find(Os_Lib* lib, c_string name);
internal void*  os_lib_get_sys_handle(Os_Lib* lib);

internal bool  os_socket_create(Os_Socket* sock, Os_Socket_Protocol protocol);
internal void  os_socket_close(Os_Socket* sock);
internal i32   os_socket_send(Os_Socket* sock, void* data, u32 data_length);
internal i32   os_socket_receive(Os_Socket* sock, void* destination, u32 count);
internal bool  os_socket_connect(Os_Socket* sock, c_string ip, u32 port);
internal void  os_socket_listen(Os_Socket* sock);
internal bool  os_socket_bind(Os_Socket* sock, u32 port);
internal bool  os_socket_accept(Os_Socket* sock, Os_Socket* destination);
internal void* os_socket_get_sys_handle(Os_Socket* sock); 

internal bool  os_window_create(Os_Window* destination, Os_Window_Configuration* config);
internal void  os_window_destroy(Os_Window* window);
internal void  os_window_show(Os_Window* window);
internal void  os_window_hide(Os_Window* window);
internal void  os_window_poll(Os_Window* window);
internal bool  os_window_should_close(Os_Window* window);
internal u32   os_window_get_width(Os_Window* window);
internal u32   os_window_get_height(Os_Window* window);
internal void  os_window_resize(Os_Window* window, u32 width, u32 height);
internal void  os_window_set_title(Os_Window* window, c_string title);
internal void* os_window_get_sys_handle(Os_Window* window);

#endif //OS_H

#ifdef OS_IMPL
// ============================================
// |        Platform Specific Includes        |
// ============================================
#if defined(OS_Windows)

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#elif defined(OS_Osx)

#elif defined(OS_Linux)

#elif defined(OS_Android)

#elif defined(OS_Ios)

#endif // End Platform Specific Includes

// ============================================
// |     Platform Specific Implementations    |
// ============================================
#if defined(OS_Windows)
// ============================================
// |     Windows Specific Implementations     |
// ============================================

#include <stdio.h>
#include <stdlib.h>

// ***************************
// *         Cmd Line        *
// ***************************
typedef struct Os_Cmd {
    
} Os_Cmd;

// ***************************
// *          Files          *
// ***************************
typedef struct Os_File {
    
} Os_File;

// ***************************
// *         Libraries       *
// ***************************
typedef struct Os_Lib {
    HMODULE win32_lib;
} Os_Lib;

internal bool os_lib_load(Os_Lib* lib, c_string library_name) {
    lib->win32_lib = NULL;
    lib->win32_lib = LoadLibraryA(library_name);
    if(lib->win32_lib == NULL) {
        printf("Os: [Error] - Failed to load library '%s' \n", library_name);
        
        return false;
    }
    
    return true;
}

internal void os_lib_unload(Os_Lib* lib) {
    if(lib->win32_lib != NULL) FreeLibrary(lib->win32_lib);
}

internal void* os_lib_find(Os_Lib* lib, c_string name) {
    return (void*) GetProcAddress(lib->win32_lib, name);
}

internal void* os_lib_get_sys_handle(Os_Lib* lib) {
    return (void*) lib->win32_lib;
}


// ***************************
// *        Processes        *
// ***************************
typedef struct Os_Proc {
    
} Os_Proc;

// ***************************
// *         Sockets         *
// ***************************
typedef struct Os_Socket {
    SOCKET win32_socket;
    u8     protocol;
} Os_Socket;

global bool _win32_winsock_initialized = false;
bool _win32_winsock_init() {
    WSADATA wsa_data;
    i32 result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    
    if(result != 0) {
        printf("Winsock initialization failed. \n");
        
        return false;
    }
    
    return true;
}

internal bool os_socket_create(Os_Socket* sock, Os_Socket_Protocol protocol) {
    if(!_win32_winsock_initialized) {
        if(!_win32_winsock_init()) {
            printf("Winsock init failed \n");
        } else {
            _win32_winsock_initialized = true;
        }
    }
    
    sock->protocol = protocol;
    switch(sock->protocol) {
        case SOCKET_PROTO_TCP: {
            sock->win32_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        } break;
        
        case SOCKET_PROTO_UDP: {
            
        } break;
    }
    
    if(sock->win32_socket == INVALID_SOCKET) {
        printf("Socket creation failed. /n");
        
        return false;
    }
    
    return true;
}

internal void os_socket_close(Os_Socket* sock) {
    closesocket(sock->win32_socket);
}

internal i32 os_socket_send(Os_Socket* sock, void* data, u32 data_length) {
    return send(sock->win32_socket, (const char*) data, data_length, 0);
}

internal i32 os_socket_receive(Os_Socket* sock, void* destination, u32 count) {
    i32 received = recv(sock->win32_socket, (char*) destination, count, 0);
    
    if(received == SOCKET_ERROR) return 0;
    
    return received;
    
}

internal bool os_socket_connect(Os_Socket* sock, c_string ip, u32 port) {
    struct sockaddr_in connection_address;
    switch(sock->protocol) {
        case SOCKET_PROTO_TCP: {
            connection_address.sin_family      = AF_INET;
            connection_address.sin_addr.s_addr = inet_addr(ip);
            connection_address.sin_port        = htons(port);
        } break;
        
        case SOCKET_PROTO_UDP: {
            
        } break;
    }
    
    i32 connection_result = connect(sock->win32_socket, (SOCKADDR*) &connection_address, sizeof(connection_address));
    if(connection_result == SOCKET_ERROR) {
        printf("Failed to connect sock \n");
        
        return false;
    }
    
    return true;
}

internal void os_socket_listen(Os_Socket* sock) {
    i32 listen_result = listen(sock->win32_socket, SOMAXCONN);
    if(listen_result == SOCKET_ERROR) {
        printf("Socket failed to listen! \n");
    } else {
        printf("TCP Socket now listening... \n");
    }
}

internal bool os_socket_bind(Os_Socket* sock, u32 port) {
    struct sockaddr_in bind_address;
    switch(sock->protocol) {
        case SOCKET_PROTO_TCP: {
            bind_address.sin_family      = AF_INET;
            bind_address.sin_addr.s_addr = inet_addr("127.0.0.1");
            bind_address.sin_port        = htons(port);
            
            i32 bind_result = bind(sock->win32_socket, (SOCKADDR*) &bind_address, sizeof(bind_address));
            if(bind_result == SOCKET_ERROR) {
                printf("Failed to bind sock \n");
                
                return false;
            }
        } break;
        
        case SOCKET_PROTO_UDP: {
            
        } break;
    }
    
    return true;
}

internal bool os_socket_accept(Os_Socket* sock, Os_Socket* destination) {
    SOCKET win32_connected_socket = accept(sock->win32_socket, 0, 0);
    
    if(win32_connected_socket == INVALID_SOCKET) return false;
    
    destination->win32_socket = win32_connected_socket;
    destination->protocol     = sock->protocol;
    
    return true;
}

internal void* os_socket_get_sys_handle(Os_Socket* sock) {
    return (void*) sock->win32_socket;
}
// ***************************
// *         Threads         *
// ***************************
typedef struct Os_Thread {
    
} Os_Thread;

// ***************************
// *         Windows         *
// ***************************
typedef struct Os_Window {
    HWND win32_window_handle;
    
    u32  width;
    u32  height;
    bool should_close;
} Os_Window;

LRESULT CALLBACK _win32_platform_window_callback(HWND hwnd, u32 msg, WPARAM wparam, LPARAM lparam) {
    switch(msg) {
        case WM_CLOSE: {
            Os_Window* window    = (Os_Window*) GetPropA(hwnd, "Os_Window");
            window->should_close = true;
        } break;
    }
    
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

global bool _win32_is_window_class_registered = false;
bool _win32_register_window_class() {
    WNDCLASSEXA window_class = {};
    window_class.cbSize        = sizeof(window_class);
    window_class.cbClsExtra    = 0;
    window_class.cbWndExtra    = 0;
	window_class.style         = CS_OWNDC | CS_VREDRAW | CS_HREDRAW | CS_GLOBALCLASS;
	window_class.lpfnWndProc   = _win32_platform_window_callback;
	window_class.hInstance     = GetModuleHandle(0);
    window_class.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    window_class.hCursor       = LoadCursor(NULL, IDC_ARROW);
	window_class.lpszClassName = "win32_window_class";
    
    _win32_is_window_class_registered = true;
	if(RegisterClassExA(&window_class) == 0) _win32_is_window_class_registered = false;
    
    return _win32_is_window_class_registered;
}

internal bool os_window_create(Os_Window* destination, Os_Window_Configuration* config) {
    if(!_win32_is_window_class_registered && !_win32_register_window_class()) {
        printf("Win32 window class registration failed \n");
        
        return false;
    }
    
    destination->win32_window_handle = CreateWindowA("win32_window_class", config->title, WS_OVERLAPPEDWINDOW,
                                                     CW_USEDEFAULT, CW_USEDEFAULT, config->width, config->height,
                                                     NULL, NULL, GetModuleHandle(0), NULL);
    if(destination->win32_window_handle == 0) {
        printf("Win32 window creation failed. \n");
        
        return false;
    }
    
    destination->width  = config->width;
    destination->height = config->height;
    destination->should_close = false;
    SetPropA(destination->win32_window_handle, "Os_Window", destination);
    
    return true;
}

internal void os_window_destroy(Os_Window* window) {
    DestroyWindow(window->win32_window_handle);
}

internal void os_window_show(Os_Window* window) {
    ShowWindow(window->win32_window_handle, SW_SHOW);
}

internal void os_window_hide(Os_Window* window) {
    ShowWindow(window->win32_window_handle, SW_HIDE);
}

internal void os_window_poll(Os_Window* window) {
    MSG e;
    while(PeekMessageA(&e, window->win32_window_handle, 0, 0, PM_REMOVE)) {
        TranslateMessage(&e);
        DispatchMessage(&e);
    }
}

internal bool os_window_should_close(Os_Window* window) {
    return window->should_close;
}

internal u32 os_window_get_width(Os_Window* window) {
    return window->width;
}

internal u32 os_window_get_height(Os_Window* window) {
    return window->height;
}

internal void os_window_resize(Os_Window* window, u32 width, u32 height) {
    
}

internal void os_window_set_title(Os_Window* window, c_string title) {
    SetWindowTextA(window->win32_window_handle, title);
}

internal void* os_window_get_sys_handle(Os_Window* window) {
    return (void*) window->win32_window_handle;
}

#elif defined(OS_Osx)
// ============================================
// |       Osx Specific Implementations     |
// ============================================

#elif defined(OS_Linux)
// ============================================
// |       Linux Specific Implementations     |
// ============================================

// ***************************
// *         Cmd Line        *
// ***************************

// ***************************
// *          Files          *
// ***************************

// ***************************
// *         Libraries       *
// ***************************

// ***************************
// *        Processes        *
// ***************************

// ***************************
// *         Sockets         *
// ***************************

// ***************************
// *         Windows         *
// ***************************

#elif defined(OS_Android)
// ============================================
// |     Android Specific Implementations     |
// ============================================

// ***************************
// *         Cmd Line        *
// ***************************

// ***************************
// *          Files          *
// ***************************

// ***************************
// *         Libraries       *
// ***************************

// ***************************
// *        Processes        *
// ***************************

// ***************************
// *         Sockets         *
// ***************************

// ***************************
// *         Windows         *
// ***************************

#elif defined(OS_Ios)
// ***************************
// *         Cmd Line        *
// ***************************

// ***************************
// *          Files          *
// ***************************

// ***************************
// *         Libraries       *
// ***************************

// ***************************
// *        Processes        *
// ***************************

// ***************************
// *         Sockets         *
// ***************************

// ***************************
// *         Windows         *
// ***************************

#endif // End Platform Specific Implementations

#endif
