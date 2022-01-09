#include <mcp/syscalls.h>
#include <stdlib.h>
#include <string.h>

#define	FA_READ				0x01
#define	FA_WRITE			0x02
#define	FA_OPEN_EXISTING	0x00
#define	FA_CREATE_NEW		0x04
#define	FA_CREATE_ALWAYS	0x08
#define	FA_OPEN_ALWAYS		0x10
#define	FA_OPEN_APPEND		0x30

#define STDIN_FILENO        0
#define STDOUT_FILENO       1 
#define STDERR_FILENO       2

typedef struct {
    char posix[3];
    int fsys;
} mode_map_t;

// Mapping copied from http://elm-chan.org/fsw/ff/doc/open.html
static mode_map_t mapping[] = {
    {"r",   FA_READ},
    {"r+",  FA_READ | FA_WRITE},
    {"w",   FA_CREATE_ALWAYS | FA_WRITE},
    {"w+",  FA_CREATE_ALWAYS | FA_WRITE | FA_READ},
    {"a",   FA_OPEN_APPEND | FA_WRITE},
    {"a+",  FA_OPEN_APPEND | FA_WRITE | FA_READ},
    {"wx",  FA_CREATE_NEW | FA_WRITE},
    {"w+x", FA_CREATE_NEW | FA_WRITE | FA_READ}
};


int __open(const char *name,const char *mode) {
    int result = -1;
    int m = -1;

    for (int i=0; i<8; i++) {
        char *map = mapping[i].posix;
        if (strcmp(mode, map) == 0) {
            m = mapping[i].fsys;
            break;
        }
    }

    if (m >= 0) {
        result = sys_fsys_open(name, m);
    }

    return (result >= 0) ? result + 3 : result;
}

void __close(int h) {
    if (h > STDERR_FILENO) {
        sys_fsys_close(h - 3);
    }
}

size_t __read(int h,char *p,size_t l) {
    if (h == STDIN_FILENO) {
        return sys_chan_read(0, p, l);
    } else if (h > STDERR_FILENO) {
        return sys_chan_read(h - 3, p, l);
    } else {
        return -1;
    }
}

size_t __write(int h, char *p, size_t l) {
    if (h == STDOUT_FILENO || h == STDERR_FILENO) {
        return sys_chan_write(0, p, l);
    } else if (h == STDIN_FILENO) {
        return -1;
    } else {
        return sys_chan_write(h - 3, p, l);
    }
}

long __seek(int h, long offset, int origin) {
	if (h > STDERR_FILENO) {
		return sys_chan_seek(h - 3, offset, origin - 1);
	} else {
		return -1;
	}
}
