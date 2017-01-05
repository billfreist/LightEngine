/// CommonAllocator

#pragma once

namespace lite {

class CommonAllocator {
public:
    static void * Alloc (size_t bytes);
    static void Free (void * ptr);
};

} // common

