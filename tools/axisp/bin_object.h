// Binary Imgae Object File Reader
//
// [2014-??-??]
//
//

#ifndef __BIN_OBJECT_INC__
#define __BIN_OBJECT_INC__

#include <sys/types.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef MAX_PATH
#define MAX_PATH 256
#endif

class bin_object
{
public:
    char        _file_path[MAX_PATH];
    int         _h_file;

    bool        _out;

    uint32_t    _size;

    void        *_map_base;
    void        *_map_end;
    void        *_map_iter;

public:
    bin_object();
    ~bin_object();

    int  open(const char *file_path, bool out = false);
    void close();

    uint32_t size()  { return _size; }

    int read(void *buff, uint32_t size);
    int write(const void *buff, uint32_t size);

    int seek(uint32_t offset);

    int read_line(void *buff, uint32_t size);

    void *offset(uint32_t size, bool from_begining = true);
};

#endif  // __BIN_OBJECT_INC__

