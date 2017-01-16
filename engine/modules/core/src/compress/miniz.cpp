///
/// LICENSE
///

#include "core_pch.h"
#define MINIZ_HEADER_FILE_ONLY
#include <compress/miniz.h>
#include "miniz/miniz.c"

LITE_NAMESPACE_BEGIN(lite)

const int MEM_LEVEL   = 9;
const int WINDOW_BITS = MZ_DEFAULT_WINDOW_BITS;


inline static void * MiniZAlloc (void * /*opaque*/, size_t items, size_t size) {
    return LITE_ALLOC(items * size);
}

inline static void MiniZFree (void * /*opaque*/, void * address) {
    LITE_FREE(address);
}


MiniZCompressor::MiniZCompressor (ECompressionLevel level)
    : m_compressionLevel(level)
{

}

MiniZCompressor::~MiniZCompressor () {
}

bool MiniZCompressor::Compress (
    size_t          rawDataBytes,
    const uint8_t * rawData,
    size_t *        cmpDataBytes,
    uint8_t *       cmpData
) {
    mz_ulong cmpBytes = mz_ulong(*cmpDataBytes);
    const auto result = mz_compress2(
        cmpData,
        &cmpBytes,
        rawData,
        mz_ulong(rawDataBytes),
        int(m_compressionLevel)
    );
    if (result != MZ_OK)
        return false;

    *cmpDataBytes = cmpBytes;
    return true;
}

bool MiniZCompressor::Decompress (
    size_t          cmpDataBytes,
    const uint8_t * cmpData,
    size_t *        rawDataBytes,
    uint8_t *       rawData
) {
    mz_ulong rawBytes = mz_ulong(*rawDataBytes);
    const auto result = mz_uncompress(
        rawData,
        &rawBytes,
        cmpData,
        mz_ulong(cmpDataBytes)
    );
    if (result != MZ_OK)
        return false;

    *rawDataBytes = rawBytes;
    return true;
}

bool MiniZCompressor::CompressWithContext (
    size_t          rawDataBytes,
    const uint8_t * rawData,
    size_t *        cmpDataBytes,
    uint8_t *       cmpData
) {
    InitCompressContext();

    mz_streamp context = static_cast<mz_streamp>(m_compressContext);
    context->next_in   = rawData;
    context->avail_in  = mz_uint32(rawDataBytes);
    context->next_out  = cmpData;
    context->avail_out = mz_uint32(*cmpDataBytes);

    int result = mz_deflate(context, MZ_FINISH);
    if (result != MZ_STREAM_END) {
        mz_deflateEnd(context);
        return false;
    }

    *cmpDataBytes = context->total_out;
    result = mz_deflateEnd(context);
    return result == MZ_OK;
}

bool MiniZCompressor::DecompressWithContext (
    size_t          cmpDataBytes,
    const uint8_t * cmpData,
    size_t *        rawDataBytes,
    uint8_t *       rawData
) {
    InitDecompressContext();

    mz_streamp context = static_cast<mz_streamp>(m_decompressContext);
    context->next_in   = cmpData;
    context->avail_in  = mz_uint32(cmpDataBytes);
    context->next_out  = rawData;
    context->avail_out = mz_uint32(*rawDataBytes);

    int result = mz_inflate(context, MZ_FINISH);
    if (result != MZ_STREAM_END) {
        mz_inflateEnd(context);
        return false;
    }

    *rawDataBytes = context->total_out;
    result = mz_inflateEnd(context);
    return result == MZ_OK;
}

void MiniZCompressor::InitCompressContext () {
    if (m_compressContext)
       mz_deflateReset(static_cast<mz_streamp>(m_compressContext));
    else {
        mz_stream * context = LITE_NEW(mz_stream);
        MemZero(context, sizeof(mz_stream));
        context->zalloc = &MiniZAlloc;
        context->zfree  = &MiniZFree;
        mz_deflateInit2(
            context,
            int(m_compressionLevel),
            MZ_DEFLATED,
            WINDOW_BITS,
            MEM_LEVEL,
            MZ_FILTERED
        );
        m_compressContext = context;
    }
}

void MiniZCompressor::InitDecompressContext () {
    if (!m_decompressContext) {
        mz_stream * context = LITE_NEW(mz_stream);
        MemZero(context, sizeof(mz_stream));
        context->zalloc = &MiniZAlloc;
        context->zfree  = &MiniZFree;
        m_decompressContext = context;
    }
    mz_inflateInit2(static_cast<mz_streamp>(m_decompressContext), WINDOW_BITS);
}

LITE_NAMESPACE_END(lite)
