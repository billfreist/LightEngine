///
/// LICENSE
///

#pragma once

LITE_NAMESPACE_BEGIN(lite)

class MiniZCompressor {
public:

    enum CompressionLevel {
        COMPRESSION_LEVEL_NONE       = 0,
        COMPRESSION_LEVEL_SUPER_FAST = 1,
        COMPRESSION_LEVEL_VERY_FAST  = 2,
        COMPRESSION_LEVEL_FASTER     = 3,
        COMPRESSION_LEVEL_FAST       = 4,
        COMPRESSION_LEVEL_NORMAL     = 5,
        COMPRESSION_LEVEL_SLOW       = 6,
        COMPRESSION_LEVEL_SLOWER     = 7,
        COMPRESSION_LEVEL_VERY_SLOW  = 8,
        COMPRESSION_LEVEL_BEST       = 9,
        COMPRESSION_LEVEL_UBER       = 10,
    };

    MiniZCompressor () = default;
    MiniZCompressor (CompressionLevel level);
    ~MiniZCompressor ();

    // Naive implementation - for one-off use cases.
    bool Compress (size_t rawDataBytes, const uint8_t * rawData, size_t * cmpDataBytes, uint8_t * cmpData);
    bool Decompress (size_t cmpDataBytes, const uint8_t * cmpData, size_t * rawDataBytes, uint8_t * rawData);

    // Cached implementation - for repetitive use (prevents unnecessary heap allocations).
    bool CompressWithContext (size_t rawDataBytes, const uint8_t * rawData, size_t * cmpDataBytes, uint8_t * cmpData);
    bool DecompressWithContext (size_t cmpDataBytes, const uint8_t * cmpData, size_t * rawDataBytes, uint8_t * rawData);

private:

    void InitCompressContext ();
    void InitDecompressContext ();

    void *           m_compressContext   = nullptr;
    void *           m_decompressContext = nullptr;
    CompressionLevel m_compressionLevel  = COMPRESSION_LEVEL_NORMAL;

};

LITE_NAMESPACE_END(lite)
