#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

// TODO: temporary implementation]
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 initialize_logging(){
    // TODO: create log file
    return TRUE;
}
void shutdown_logging(){
    // TODO: cleanup logging/write queued entries
}

void log_output(log_level level, const char* message, ...){
    const char* level_strings[6] = {
        "[FATAL]: ",
        "[ERROR]: ",
        "[WARN]:  ",
        "[INFO]:  ",
        "[DEBUG]: ",
        "[TRACE]: "
    };

    b8 is_error = level < LOG_LEVEL_WARN;

    // technically imposes a 32k char limit on a single entry, but...
    // DON'T DO THAT
    // TODO: replace later
    const i32 msg_length = 32000;
    char out_message[msg_length];
    memset(out_message, 0, sizeof(out_message));

    // Format orginal message
    // NOTE: Oddly enough, MS's headers override the GCC/Clang va_list type with a "typedef char* va_list" in some cases, and as a result throws a strange error here. The workaround for now is to just use __builtin_va_list instead which is the type GCC/Clang's va_start expects.
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, sizeof(out_message), message, arg_ptr);
    va_end(arg_ptr);

    char buffer[msg_length];
    sprintf(buffer, "%s%s\n", level_strings[level], out_message);

    // platform-specific logging
    if(is_error){
        platform_console_write_error(buffer, level);
    }else{
        platform_console_write(buffer, level);
    }
}

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}