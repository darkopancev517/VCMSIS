
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

#include "bin_object.h"

bin_object::bin_object()
{
    _file_path[0] = 0;
    _h_file = -1;
    _out = false;
    _size = 0;
    _map_base = MAP_FAILED;
    _map_end = MAP_FAILED;
    _map_iter = MAP_FAILED;
}

bin_object::~bin_object()
{
    close();
}

int bin_object::open(const char *file_path, bool out)
{
    if (_h_file >= 0)
        return -1;

    ::memset(_file_path, 0, MAX_PATH);

    if (out) {

        _h_file = ::open(file_path, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        if (_h_file < 0)
            return -1;

        _out = true;
        _size = 0;
        _map_base = MAP_FAILED;
        _map_end = MAP_FAILED;
        _map_iter = MAP_FAILED;

    } else {

        _h_file = ::open(file_path, O_RDONLY);
        if (_h_file < 0)
            return -1;

        struct stat st;
        st.st_size = 0;

        if (::stat(file_path, &st) != 0)
            return -1;

        if (st.st_size == 0)
            return -1;

        _size = (uint32_t)st.st_size;

        _map_base = (uint32_t *)::mmap(0, st.st_size, PROT_READ, MAP_SHARED, _h_file, 0);
        if (_map_base == (uint32_t *)MAP_FAILED)
            return -1;

        _map_iter = _map_base;
        _map_end = (uint8_t *)_map_base + st.st_size;

        _out = false;
    }

    ::strcpy(_file_path, file_path);

    return 0;
}

void bin_object::close()
{
    if ((_map_base != MAP_FAILED) && (_map_base != NULL))
        ::munmap(_map_base, size_t((uint8_t *)_map_end - (uint8_t *)_map_base));

    _map_base = MAP_FAILED;
    _map_end = MAP_FAILED;
    _map_iter = MAP_FAILED;

    if (_h_file >= 0) {
        ::close(_h_file);
        _h_file = -1;
    }

    _size = 0;

    ::memset(_file_path, 0, MAX_PATH);
}

int bin_object::read(void *buff, uint32_t size)
{
    if (_out)
        return -1;

    if ((_map_base == MAP_FAILED) || (_map_base == NULL))
        return -1;

    if (size == 0) {
        // reset read-iterator
        _map_iter = _map_base;
        return 0;
    }

    if (_map_iter >= _map_end)
        return -1;

    uint32_t copy_size = (uint8_t *)_map_end - (uint8_t *)_map_iter;

    if (copy_size < size) {
        ::memset((uint8_t*)buff + copy_size, 0, size - copy_size);
        size = copy_size;
    }
    copy_size = size;

    ::memcpy(buff, _map_iter, copy_size);
    _map_iter = (uint8_t *)_map_iter + copy_size;

    return copy_size;
}

int bin_object::read_line(void *buff, uint32_t size_max)
{
    if (_out)
        return -1;

    if ((_map_base == MAP_FAILED) || (_map_base == NULL))
        return -1;

    if (size_max == 0) {
        // reset read-iterator
        _map_iter = _map_base;
        return 0;
    }

    if (_map_iter >= _map_end)
        return -1;

    uint8_t *map_iter = (uint8_t *)_map_iter;
    uint8_t *buff_iter = (uint8_t *)buff;
    uint32_t size = 0;
    bool do_break = false;

    while (map_iter < (uint8_t *)_map_end) {
        if (*map_iter == 0x0d) {
            if (!do_break)
                do_break = true;
            ++map_iter;
            continue;
        } else if (*map_iter == 0x0a) {
            if (!do_break)
                do_break = true;
            ++map_iter;
            continue;
        }

        if (do_break)
            break;

        *buff_iter++ = *map_iter++;
        ++size;
        if (size >= size_max)
            break;
    }

    _map_iter = (void *)map_iter;

    if (size > 0)
        *buff_iter = 0;

    return size;
}

int bin_object::write(const void *buff, uint32_t size)
{
    if (!_out)
        return -1;

    if (_h_file < 0)
        return -1;

    if (size == 0)
        return 0;

    int r = (uint32_t)::write(_h_file, buff, size);
    if (r >= 0)
        _size += (uint32_t)r;

    return r;
}

int bin_object::seek(uint32_t offset)
{

    int r = (uint32_t)::lseek(_h_file, offset, SEEK_SET);

    if (r < 0)
        return -1;

    return r;
}

void *bin_object::offset(uint32_t size, bool from_begining)
{
    if (_out)
        return NULL;

    if ((_map_base == MAP_FAILED) || (_map_base == NULL))
        return NULL;

    uint32_t off_size;

    if (from_begining)
        off_size = (uint8_t *)_map_end - (uint8_t *)_map_base;
    else
        off_size = (uint8_t *)_map_end - (uint8_t *)_map_iter;

    if (off_size > size)
        off_size = size;

    if (from_begining)
        _map_iter = (uint8_t *)_map_base + off_size;
    else
        _map_iter = (uint8_t *)_map_iter + off_size;

    return _map_iter;
}
