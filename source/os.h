/* date = April 7th 2022 11:46 am */

#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

// TODO(Cody): In the near future not relying on any 
//             c std lib would be ideal. This should be
//             pure implementations per system to maximize
//             impact. 
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

typedef u8 bool;
#define true  1
#define false 0

#define internal static
#define global   static
#define local    static

#ifdef __cplusplus
#define os_api extern "C"
#else
#define os_api extern
#endif

#define Kilobyte(x) (x * 1024ULL)
#define Megabyte(x) (Kilobyte(x) * 1024ULL)
#define Gigabyte(x) (Megabyte(x) * 1024ULL)
#define Terabyte(x) (Gigabyte(x) * 1024ULL)

#define bit_set(a,b) ((a) |= (1ULL<<(b)))
#define bit_clear(a,b) ((a) &= ~(1ULL<<(b)))
#define bit_flip(a,b) ((a) ^= (1ULL<<(b)))
#define bit_check(a,b) (!!((a) & (1ULL<<(b)))) 

#define bitmask_set(x,y) ((x) |= (y))
#define bitmask_clear(x,y) ((x) &= (~(y)))
#define bitmask_flip(x,y) ((x) ^= (y))
#define bitmask_check_all(x,y) (!(~(x) & (y)))
#define bitmask_check_any(x,y) ((x) & (y))

global u64 __get_nth_bits_from_offset(u64 number, u8 num_bits, u8 offset) {
    return (number >> offset) & ((1 << num_bits) - 1);
} 

#define unpack_bits_from_offset(num, num_bits, offset) __get_nth_bits_from_offset(num, num_bits, offset)

#endif //TYPE_DEFINITIONS_H

#ifndef OS_H
#define OS_H

typedef struct Os_Cmd     Os_Cmd;
typedef struct Os_File    Os_File;
typedef enum Os_File_Mode {
    File_Mode_Read_Only,
    File_Mode_Write_Only,
    File_Mode_Read_Write,
} Os_File_Mode;

typedef enum Os_File_Seek_Mode {
    File_Seek_Start,
    File_Seek_Current,
    File_Seek_End,
} Os_File_Seek_Mode;

typedef struct Os_Lib     Os_Lib;     // Somewhat implemented (Win32)
typedef struct Os_Proc    Os_Proc;
typedef struct Os_Thread  Os_Thread;
typedef struct Os_Socket  Os_Socket;  // Somewhat implemented (Win32)
typedef enum Os_Socket_Protocol {
    SOCKET_PROTO_TCP,
    SOCKET_PROTO_UDP
} Os_Socket_Protocol;

typedef struct Os_Window  Os_Window;  // Somewhat implemented (Win32, Linux_X11)
typedef struct Os_Window_Configuration {
    c_string title;
    u32      width;
    u32      height;
} Os_Window_Configuration;

// ============================================
// |              Keyboard Keys               |
// ============================================
// NOTE(Cody): This currently assumes a "full" keyboard is a standard US QWERTY
// TODO(Cody): Make  this not static to support other language keyboards. 
//             This adventure can be taken at a much later date.
typedef enum Os_Keycode {
    Os_Keycode_Undefined = 0,
    
    // Alphabetical Keys
    Os_Keycode_A,
    Os_Keycode_B,
    Os_Keycode_C,
    Os_Keycode_D,
    Os_Keycode_E,
    Os_Keycode_F,
    Os_Keycode_G,
    Os_Keycode_H,
    Os_Keycode_I,
    Os_Keycode_J,
    Os_Keycode_K,
    Os_Keycode_L,
    Os_Keycode_M,
    Os_Keycode_N,
    Os_Keycode_O,
    Os_Keycode_P,
    Os_Keycode_Q,
    Os_Keycode_R,
    Os_Keycode_S,
    Os_Keycode_T,
    Os_Keycode_U,
    Os_Keycode_V,
    Os_Keycode_W,
    Os_Keycode_X,
    Os_Keycode_Y,
    Os_Keycode_Z,
    
    // Numerical Keys
    Os_Keycode_0,
    Os_Keycode_1,
    Os_Keycode_2,
    Os_Keycode_3,
    Os_Keycode_4,
    Os_Keycode_5,
    Os_Keycode_6,
    Os_Keycode_7,
    Os_Keycode_8,
    Os_Keycode_9,
    Os_Keycode_Minus,
    Os_Keycode_Equal,
    
    // Function Keys
    Os_Keycode_F1,
    Os_Keycode_F2,
    Os_Keycode_F3,
    Os_Keycode_F4,
    Os_Keycode_F5,
    Os_Keycode_F6,
    Os_Keycode_F7,
    Os_Keycode_F8,
    Os_Keycode_F9,
    Os_Keycode_F10,
    Os_Keycode_F11,
    Os_Keycode_F12,
    
    // Modifier Keys
    Os_Keycode_Alt_Left,
    Os_Keycode_Alt_Right,
    Os_Keycode_Ctrl_Left,
    Os_Keycode_Ctrl_Right,
    Os_Keycode_Shift_Left,
    Os_Keycode_Shift_Right,
    
    // Punctuation Keys
    Os_Keycode_Apostrophe,
    Os_Keycode_Comma,
    Os_Keycode_Period,
    Os_Keycode_Slash_Fwd,
    Os_Keycode_Slash_Back,
    Os_Keycode_Semi_Colon,
    Os_Keycode_Square_Left,
    Os_Keycode_Square_Right,
    Os_Keycode_Tilde,
    
    // Numpad Keys
    Os_Keycode_Num_0,
    Os_Keycode_Num_1,
    Os_Keycode_Num_2,
    Os_Keycode_Num_3,
    Os_Keycode_Num_4,
    Os_Keycode_Num_5,
    Os_Keycode_Num_6,
    Os_Keycode_Num_7,
    Os_Keycode_Num_8,
    Os_Keycode_Num_9,
    Os_Keycode_Num_Slash,
    Os_Keycode_Num_Star,
    Os_Keycode_Num_Minus,
    Os_Keycode_Num_Plus,
    Os_Keycode_Num_Enter,
    Os_Keycode_Num_Period,
    
    // Utility Keys
    Os_Keycode_Arrow_Down,
    Os_Keycode_Arrow_Left,
    Os_Keycode_Arrow_Right,
    Os_Keycode_Arrow_Up,
    Os_Keycode_Backspace,
    Os_Keycode_Caps_Lock,
    Os_Keycode_Delete,
    Os_Keycode_End,
    Os_Keycode_Enter,
    Os_Keycode_Escape,
    Os_Keycode_Home,
    Os_Keycode_Insert,
    Os_Keycode_Page_Down,
    Os_Keycode_Page_Up,
    Os_Keycode_Pause,
    Os_Keycode_Print_Screen,
    Os_Keycode_Scroll_Lock,
    Os_Keycode_Super,
    Os_Keycode_Tab,
} Os_Keycode;

typedef enum Os_Key_Action {
    Os_Keyaction_Undefined = 0,
    Os_Keyaction_Key_Down,
    Os_Keyaction_Key_Up,
} Os_Key_Action;

typedef enum Os_Key_Modifiers {
    Os_Keymods_Undefined = 0,
} Os_Key_Modifiers;

// ============================================
// |        General Purpose Utilities         |
// ============================================
os_api void* os_mem_alloc(u32 size);
os_api void  os_mem_realloc(void* ptr, u32 new_size);
os_api void  os_mem_free(void* ptr);
os_api void  os_mem_move(void* source, void* destination, u32 size);
os_api void  os_mem_copy(void* source, void* destination, u32 size);
os_api void  os_mem_zero(void* ptr, u32 size);

// ============================================
// |         File API Functions               |
// ============================================
os_api bool  os_file_create(c_string file_location, bool overwrite_existing);
os_api bool  os_file_open(c_string file_location, Os_File_Mode mode, Os_File* output);
os_api void  os_file_close(Os_File* file);
os_api void  os_file_delete(c_string file_location);
os_api void  os_file_read_size(Os_File* file, u32 size, u8* output);
os_api void  os_file_write_size(Os_File* file, u32 size, u8* input);
os_api void  os_file_seek(Os_File* file, u32 position, Os_File_Seek_Mode mode);
os_api void* os_file_get_sys_handle(Os_File* file);

// ============================================
// |         Library API Functions            |
// ============================================
os_api bool   os_lib_load(Os_Lib* lib, c_string library_name);
os_api void   os_lib_unload(Os_Lib* lib);
os_api void*  os_lib_find(Os_Lib* lib, c_string name);
os_api void*  os_lib_get_sys_handle(Os_Lib* lib);

// ============================================
// |         Socket API Functions             |
// ============================================
os_api bool  os_socket_create(Os_Socket* sock, Os_Socket_Protocol protocol);
os_api void  os_socket_close(Os_Socket* sock);
os_api i32   os_socket_send(Os_Socket* sock, void* data, u32 data_length);
os_api i32   os_socket_receive(Os_Socket* sock, void* destination, u32 count);
os_api bool  os_socket_connect(Os_Socket* sock, c_string ip, u32 port);
os_api void  os_socket_listen(Os_Socket* sock);
os_api bool  os_socket_bind(Os_Socket* sock, u32 port);
os_api bool  os_socket_accept(Os_Socket* sock, Os_Socket* destination);
os_api void* os_socket_get_sys_handle(Os_Socket* sock); 

// ============================================
// |         Window API Functions             |
// ============================================
typedef void (*Os_Window_Key_Callback)(Os_Keycode, Os_Key_Action, Os_Key_Modifiers);
os_api bool     os_window_create(Os_Window* destination, Os_Window_Configuration* config);
os_api void     os_window_destroy(Os_Window* window);
os_api void     os_window_show(Os_Window* window);
os_api void     os_window_hide(Os_Window* window);
os_api void     os_window_poll(Os_Window* window);
os_api bool     os_window_should_close(Os_Window* window);
os_api u32      os_window_get_width(Os_Window* window);
os_api u32      os_window_get_height(Os_Window* window);
os_api void     os_window_resize(Os_Window* window, u32 width, u32 height);
os_api void     os_window_set_position(Os_Window* window, u32 x, u32 y);
os_api c_string os_window_get_title(Os_Window* window);
os_api void     os_window_set_title(Os_Window* window, c_string title);
os_api void     os_window_set_key_callback(Os_Window* window, Os_Window_Key_Callback callback);
os_api void*    os_window_get_sys_handle(Os_Window* window);

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

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>

#elif defined(OS_Android)

#elif defined(OS_Ios)

#endif // End Platform Specific Includes

// ============================================
// |     Platform Agnostic Implementations    |
// ============================================
typedef struct Os_File_Data {
    c_string     file_location;
    u32          size;
    Os_File_Mode mode;
    bool         open;
} Os_File_Data;

typedef struct Os_Window_Data {
    c_string title;
    u32      width;
    u32      height;
    bool     should_close;
} Os_Window_Data;

// ============================================
// |     Platform Specific Implementations    |
// ============================================
#if defined(OS_Windows)
// ============================================
// |     Windows Specific Implementations     |
// ============================================

os_api void* os_mem_alloc(u32 size) {
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

os_api void os_mem_realloc(void* ptr, u32 new_size) {
    HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, new_size);
}

os_api void os_mem_free(void* ptr) {
    HeapFree(GetProcessHeap(), 0, ptr);
}

os_api void os_mem_move(void* source, void* destination, u32 size) {
    MoveMemory(destination, source, size);
}

os_api void os_mem_copy(void* source, void* destination, u32 size) {
    CopyMemory(destination, source, size);
}

os_api void os_mem_zero(void* ptr, u32 size) {
    ZeroMemory(ptr, size);
}

// ***************************
// *         Cmd Line        *
// ***************************
typedef struct Os_Cmd {
    
} Os_Cmd;

// ***************************
// *          Files          *
// ***************************

typedef struct Os_File {
    HFILE win32_file_handle;
    
    Os_File_Data data;
} Os_File;

os_api bool os_file_create(c_string file_location, bool overwrite_existing) {
    i32 file_flags;
    
    if(overwrite_existing) file_flags = CREATE_ALWAYS;
    else                   file_flags = CREATE_NEW;
    
    HANDLE file = CreateFileA(file_location, GENERIC_READ | GENERIC_WRITE, 0, NULL, file_flags, FILE_ATTRIBUTE_NORMAL, NULL);
    if(file == INVALID_HANDLE_VALUE) return false;
    
    CloseHandle(file);
    
    return true;
}

os_api bool os_file_open(c_string file_location, Os_File_Mode mode, Os_File* output) {
    OFSTRUCT win32_open_file_data;
    HFILE    win32_file_handle;
    
    switch(mode) {
        case File_Mode_Read_Only: {
            win32_file_handle = OpenFile(file_location, &win32_open_file_data, OF_READ);
        } break;
        
        case File_Mode_Write_Only: {
            win32_file_handle = OpenFile(file_location, &win32_open_file_data, OF_WRITE);
        } break;
        
        case File_Mode_Read_Write: {
            win32_file_handle = OpenFile(file_location, &win32_open_file_data, OF_READWRITE);
        } break;
    }
    
    if(win32_file_handle == HFILE_ERROR) return false;
    
    output->win32_file_handle  = win32_file_handle;
    output->data.file_location = file_location;
    output->data.size          = GetFileSize(output->win32_file_handle, NULL);
    output->data.open          = true;
    
    return true;
}

os_api void os_file_close(Os_File* file) {
    if(file->data.open) CloseHandle(file->win32_file_handle);
    file->data.open = false;
}

os_api void os_file_delete(c_string file_location) {
    DeleteFile(file_location);
}

os_api void os_file_read_size(Os_File* file, u32 size, u8* output) {
    if(!file->win32_file_handle || !file->data.open) return;
    
    ReadFile(file->win32_file_handle, (LPVOID) output, size, NULL, NULL);
}

os_api void os_file_write_size(Os_File* file, u32 size, u8* input) {
    if(!file->win32_file_handle || !file->data.open) return;
    
    WriteFile(file->win32_file_handle, input, size, NULL, NULL);
}

os_api void os_file_seek(Os_File* file, u32 position, Os_File_Seek_Mode mode) {
    if(!file->win32_file_handle || !file->data.open) return;
    
    LARGE_INTEGER windows_mega_memes;
    windows_mega_memes.u.LowPart  = position & 0xFFFFFFFF;
    windows_mega_memes.u.HighPart = position >> 32;
    
    switch(mode) {
        case File_Seek_Start: {
            SetFilePointerEx(file->win32_file_handle, windows_mega_memes, NULL, FILE_BEGIN);
        } break;
        
        case File_Seek_Current: {
            SetFilePointerEx(file->win32_file_handle, windows_mega_memes, NULL, FILE_CURRENT);
        } break;
        
        case File_Seek_End: {
            SetFilePointerEx(file->win32_file_handle, windows_mega_memes, NULL, FILE_END);
        } break;
    }
}

os_api void* os_file_get_sys_handle(Os_File* file) {
    return (void*) file->win32_file_handle;
}

// ***************************
// *         Libraries       *
// ***************************
typedef struct Os_Lib {
    HMODULE win32_lib;
} Os_Lib;

os_api bool os_lib_load(Os_Lib* lib, c_string library_name) {
    lib->win32_lib = NULL;
    lib->win32_lib = LoadLibraryA(library_name);
    if(lib->win32_lib == NULL) return false;
    
    return true;
}

os_api void os_lib_unload(Os_Lib* lib) {
    if(lib->win32_lib != NULL) FreeLibrary(lib->win32_lib);
}

os_api void* os_lib_find(Os_Lib* lib, c_string name) {
    return (void*) GetProcAddress(lib->win32_lib, name);
}

os_api void* os_lib_get_sys_handle(Os_Lib* lib) {
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

internal bool _win32_winsock_initialized = false;
internal bool _win32_winsock_init() {
    WSADATA wsa_data;
    i32 result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    
    if(result != 0) return false;
    
    return true;
}

os_api bool os_socket_create(Os_Socket* sock, Os_Socket_Protocol protocol) {
    if(!_win32_winsock_initialized) {
        if(!_win32_winsock_init()) {
            return false;
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
    
    if(sock->win32_socket == INVALID_SOCKET) return false;
    
    return true;
}

os_api void os_socket_close(Os_Socket* sock) {
    closesocket(sock->win32_socket);
}

os_api i32 os_socket_send(Os_Socket* sock, void* data, u32 data_length) {
    return send(sock->win32_socket, (const char*) data, data_length, 0);
}

os_api i32 os_socket_receive(Os_Socket* sock, void* destination, u32 count) {
    i32 received = recv(sock->win32_socket, (char*) destination, count, 0);
    
    if(received == SOCKET_ERROR) return 0;
    
    return received;
    
}

os_api bool os_socket_connect(Os_Socket* sock, c_string ip, u32 port) {
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
    if(connection_result == SOCKET_ERROR) return false;
    
    return true;
}

os_api void os_socket_listen(Os_Socket* sock) {
    i32 listen_result = listen(sock->win32_socket, SOMAXCONN);
}

os_api bool os_socket_bind(Os_Socket* sock, u32 port) {
    struct sockaddr_in bind_address;
    switch(sock->protocol) {
        case SOCKET_PROTO_TCP: {
            bind_address.sin_family      = AF_INET;
            bind_address.sin_addr.s_addr = inet_addr("127.0.0.1");
            bind_address.sin_port        = htons(port);
            
            i32 bind_result = bind(sock->win32_socket, (SOCKADDR*) &bind_address, sizeof(bind_address));
            
            if(bind_result == SOCKET_ERROR) return false;
        } break;
        
        case SOCKET_PROTO_UDP: {
            
        } break;
    }
    
    return true;
}

os_api bool os_socket_accept(Os_Socket* sock, Os_Socket* destination) {
    SOCKET win32_connected_socket = accept(sock->win32_socket, 0, 0);
    
    if(win32_connected_socket == INVALID_SOCKET) return false;
    
    destination->win32_socket = win32_connected_socket;
    destination->protocol     = sock->protocol;
    
    return true;
}

os_api void* os_socket_get_sys_handle(Os_Socket* sock) {
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
    
    Os_Window_Data data;
    Os_Window_Key_Callback key_callback;
} Os_Window;

typedef struct _Win32_Keypress_Lparam_Data {
    u16 repeat_count;
    u8  scan_code;
    u8  extended_key;
    u8  context_code;
    u8  previous_state;
    u8  transition_state;
} _Win32_Keypress_Lparam_Data;

internal _Win32_Keypress_Lparam_Data _win32_breakdown_keypress_lparam(LPARAM lparam) {
    _Win32_Keypress_Lparam_Data data;
    
    data.repeat_count     = unpack_bits_from_offset(lparam, 16, 0);
    data.scan_code        = unpack_bits_from_offset(lparam, 8, 16);
    data.extended_key     = unpack_bits_from_offset(lparam, 1, 24);
    data.context_code     = unpack_bits_from_offset(lparam, 1, 29);
    data.previous_state   = unpack_bits_from_offset(lparam, 1, 30);
    data.transition_state = unpack_bits_from_offset(lparam, 1, 31);
    
    return data;
}

internal Os_Keycode _win32_convert_keycode(WPARAM wparam) {
    switch(wparam) {
        
        // Alphabetical Keys
        case 0x41: return Os_Keycode_A;
        case 0x42: return Os_Keycode_B;
        case 0x43: return Os_Keycode_C;
        case 0x44: return Os_Keycode_D;
        case 0x45: return Os_Keycode_E;
        case 0x46: return Os_Keycode_F;
        case 0x47: return Os_Keycode_G;
        case 0x48: return Os_Keycode_H;
        case 0x49: return Os_Keycode_I;
        case 0x4A: return Os_Keycode_J;
        case 0x4B: return Os_Keycode_K;
        case 0x4C: return Os_Keycode_L;
        case 0x4D: return Os_Keycode_M;
        case 0x4E: return Os_Keycode_N;
        case 0x4F: return Os_Keycode_O;
        case 0x50: return Os_Keycode_P;
        case 0x51: return Os_Keycode_Q;
        case 0x52: return Os_Keycode_R;
        case 0x53: return Os_Keycode_S;
        case 0x54: return Os_Keycode_T;
        case 0x55: return Os_Keycode_U;
        case 0x56: return Os_Keycode_V;
        case 0x57: return Os_Keycode_W;
        case 0x58: return Os_Keycode_X;
        case 0x59: return Os_Keycode_Y;
        case 0x5A: return Os_Keycode_Z;
        
        // Numerical Keys
        case 0x30: return Os_Keycode_0;
        case 0x31: return Os_Keycode_1;
        case 0x32: return Os_Keycode_2;
        case 0x33: return Os_Keycode_3;
        case 0x34: return Os_Keycode_4;
        case 0x35: return Os_Keycode_5;
        case 0x36: return Os_Keycode_6;
        case 0x37: return Os_Keycode_7;
        case 0x38: return Os_Keycode_8;
        case 0x39: return Os_Keycode_9;
        case 0xBD: return Os_Keycode_Minus;
        case 0xBB: return Os_Keycode_Equal;
        
        // Function Keys
        case 0x70: return Os_Keycode_F1;
        case 0x71: return Os_Keycode_F2;
        case 0x72: return Os_Keycode_F3;
        case 0x73: return Os_Keycode_F4;
        case 0x74: return Os_Keycode_F5;
        case 0x75: return Os_Keycode_F6;
        case 0x76: return Os_Keycode_F7;
        case 0x77: return Os_Keycode_F8;
        case 0x78: return Os_Keycode_F9;
        case 0x79: return Os_Keycode_F10;
        case 0x7A: return Os_Keycode_F11;
        case 0x7B: return Os_Keycode_F12;
        
        // Modifier Keys
        
        // Punctuation Keys
        
        // Numpad Keys
        case 0x60: return Os_Keycode_Num_0;
        case 0x61: return Os_Keycode_Num_1;
        case 0x62: return Os_Keycode_Num_2;
        case 0x63: return Os_Keycode_Num_3;
        case 0x64: return Os_Keycode_Num_4;
        case 0x65: return Os_Keycode_Num_5;
        case 0x66: return Os_Keycode_Num_6;
        case 0x67: return Os_Keycode_Num_7;
        case 0x68: return Os_Keycode_Num_8;
        case 0x69: return Os_Keycode_Num_9;
        case 0x6F: return Os_Keycode_Num_Slash;
        case 0x6A: return Os_Keycode_Num_Star;
        case 0x6D: return Os_Keycode_Num_Minus;
        case 0x6B: return Os_Keycode_Num_Plus;
        // TODO(Cody): What the hell is Num enter on stupid windows?
        case 0x6E: return Os_Keycode_Num_Period;
        
        // Utility Keys
    }
}

internal void _win32_default_window_key_callback(Os_Keycode keycode, Os_Key_Action action, Os_Key_Modifiers mods) {
    
}

// TODO(Cody): Lots to implement here still, but this is a working start.
LRESULT CALLBACK _win32_platform_window_callback(HWND hwnd, u32 msg, WPARAM wparam, LPARAM lparam) {
    Os_Window* window    = (Os_Window*) GetPropA(hwnd, "Os_Window");
    
    switch(msg) {
        case WM_CLOSE: {
            window->data.should_close = true;
        } break;
        
        case WM_KEYDOWN: {
            _Win32_Keypress_Lparam_Data lparam_data = _win32_breakdown_keypress_lparam(lparam);
            Os_Keycode os_keycode  = _win32_convert_keycode(wparam);
            
            // TODO(Cody): Implement modifiers
            window->key_callback(os_keycode, Os_Keyaction_Key_Down, Os_Keymods_Undefined);
        } break;
        
        case WM_KEYUP: {
            Os_Keycode os_keycode  = _win32_convert_keycode(wparam);
            
            // TODO(Cody): Implement modifiers
            window->key_callback(os_keycode, Os_Keyaction_Key_Up, Os_Keymods_Undefined);
        } break;
        
        case WM_SYSKEYDOWN: {
            
        } break;
        
        case WM_SYSKEYUP: {
            
        } break;
    }
    
    return DefWindowProc(hwnd, msg, wparam, lparam);
}

internal bool _win32_is_window_class_registered = false;
internal bool _win32_register_window_class() {
    WNDCLASSEXA window_class = {};
    window_class.cbSize        = sizeof(window_class);
    window_class.cbClsExtra    = 0;
    window_class.cbWndExtra    = 0;
    // TODO(Cody):              At some point we should probably setup an abstracted flag set
    //                          that can translate into these for user control
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

os_api bool os_window_create(Os_Window* destination, Os_Window_Configuration* config) {
    if(!_win32_is_window_class_registered && !_win32_register_window_class()) return false;
    
    destination->win32_window_handle = CreateWindowA("win32_window_class", config->title, WS_OVERLAPPEDWINDOW,
                                                     CW_USEDEFAULT, CW_USEDEFAULT, config->width, config->height,
                                                     NULL, NULL, GetModuleHandle(0), NULL);
    
    if(destination->win32_window_handle == 0) return false;
    
    destination->data.title  = config->title;
    destination->data.width  = config->width;
    destination->data.height = config->height;
    destination->data.should_close = false;
    destination->key_callback = _win32_default_window_key_callback;
    SetPropA(destination->win32_window_handle, "Os_Window", destination);
    
    return true;
}

os_api void os_window_destroy(Os_Window* window) {
    DestroyWindow(window->win32_window_handle);
}

os_api void os_window_show(Os_Window* window) {
    ShowWindow(window->win32_window_handle, SW_SHOW);
}

os_api void os_window_hide(Os_Window* window) {
    ShowWindow(window->win32_window_handle, SW_HIDE);
}

os_api void os_window_poll(Os_Window* window) {
    MSG e;
    while(PeekMessageA(&e, window->win32_window_handle, 0, 0, PM_REMOVE)) {
        TranslateMessage(&e);
        DispatchMessage(&e);
    }
}

os_api bool os_window_should_close(Os_Window* window) {
    return window->data.should_close;
}

os_api u32 os_window_get_width(Os_Window* window) {
    return window->data.width;
}

os_api u32 os_window_get_height(Os_Window* window) {
    return window->data.height;
}

os_api void os_window_resize(Os_Window* window, u32 width, u32 height) {
    RECT window_rect;
    SetWindowPos(window->win32_window_handle, HWND_TOP, 0, 0, width, height, SWP_NOMOVE);
    
    window->data.width  = width;
    window->data.height = height;
}

os_api void os_window_set_position(Os_Window* window, u32 x, u32 y) {
    SetWindowPos(window->win32_window_handle, HWND_TOP, x, y, x + window->data.width, y + window->data.height, 0);
}

os_api c_string os_window_get_title(Os_Window* window) {
    return window->data.title;
}

os_api void os_window_set_title(Os_Window* window, c_string title) {
    SetWindowTextA(window->win32_window_handle, title);
    window->data.title = title;
}

os_api void os_window_set_key_callback(Os_Window* window, Os_Window_Key_Callback callback) {
    window->key_callback = callback;
}

os_api void* os_window_get_sys_handle(Os_Window* window) {
    return (void*) window->win32_window_handle;
}

#elif defined(OS_Osx)
// ============================================
// |       OSX Specific Implementations     |
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
// *         Threads       *
// ***************************

// ***************************
// *         Windows         *
// ***************************

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
// *         Threads       *
// ***************************

// ***************************
// *         Windows         *
// ***************************
typedef struct Os_Window {
    Display* x11_display;
    Window   x11_window;
    i32      x11_screen_id;
    
    Os_Window_Data data;
    
    Atom x11_delete_message;
} Os_Window;

os_api bool os_window_create(Os_Window* destination, Os_Window_Configuration* config) {
    destination->x11_display = XOpenDisplay(NULL);
    
    if(destination->x11_display == NULL) return false;
    
    destination->x11_screen_id = DefaultScreen(destination->x11_display);
    destination->x11_window    = XCreateSimpleWindow(destination->x11_display,
                                                     RootWindow(destination->x11_display, destination->x11_screen_id),
                                                     10, 10, 320, 200, 1,
                                                     BlackPixel(destination->x11_display, destination->x11_screen_id),
                                                     WhitePixel(destination->x11_display, destination->x11_screen_id));
    XSelectInput(destination->x11_display, destination->x11_window, ExposureMask | KeyPressMask);
    destination->x11_delete_message = XInternAtom(destination->x11_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(destination->x11_display, destination->x11_window, &destination->x11_delete_message, 1);
    
    destination->data.title  = config->title;
    destination->data.width  = config->width;
    destination->data.height = config->height;
    destination->data.should_close = false;
    
    os_window_set_title(destination, config->title);
    os_window_resize(destination, config->width, config->height);
}

os_api void os_window_destroy(Os_Window* window) {
    XDestroyWindow(window->x11_display, window->x11_window);
    XCloseDisplay(window->x11_display);
}

os_api void os_window_show(Os_Window* window) {
    XClearWindow(window->x11_display, window->x11_window);
    XMapWindow(window->x11_display, window->x11_window);
}

os_api void os_window_hide(Os_Window* window) {
    
}

os_api void os_window_poll(Os_Window* window) {
    XEvent e;
    
    while(XPending(window->x11_display) > 0) {
        XNextEvent(window->x11_display, &e);
        
        switch(e.type) {
            case ClientMessage: {
                if(e.xclient.data.l[0] == window->x11_delete_message) {
                    window->data.should_close = true;
                }
            } break;
        }
    }
}

os_api bool os_window_should_close(Os_Window* window) {
    return window->data.should_close;
}

os_api u32 os_window_get_width(Os_Window* window) {
    return window->data.width;
}

os_api u32 os_window_get_height(Os_Window* window) {
    return window->data.height;
}

os_api void os_window_resize(Os_Window* window, u32 width, u32 height) {
    u32 resize_mask = CWWidth | CWHeight;
    XWindowChanges resize_values;
    resize_values.width  = width;
    resize_values.height = height;
    XConfigureWindow(window->x11_display, window->x11_window, resize_mask, &resize_values);
    
    window->data.width  = width;
    window->data.height = height;
}

os_api void os_window_set_position(Os_Window* window, u32 x, u32 y) {
    
}

os_api c_string os_window_get_title(Os_Window* window) {
    return window->data.title;
}

os_api void os_window_set_title(Os_Window* window, c_string title) {
    XStoreName(window->x11_display, window->x11_window, title);
    
    window->data.title = title;
}

os_api void* os_window_get_sys_handle(Os_Window* window) {
    return (void*) window->x11_window;
}



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
// *         Threads       *
// ***************************

// ***************************
// *         Windows         *
// ***************************


#elif defined(OS_Ios)
// ============================================
// |     IOS Specific Implementations         |
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
// *         Threads       *
// ***************************

// ***************************
// *         Windows         *
// ***************************

#endif // End Platform Specific Implementations

#endif
