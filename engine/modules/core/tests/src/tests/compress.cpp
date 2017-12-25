///
/// LICENSE
///

#include "pch.h"

#include <core/memory.h>
#include <sys/stat.h>
#include <compress/MiniZ.h>

namespace lite {

constexpr uint32_t kRawBytes = 1024 * 50;

TEST(Compress, MiniZWithCtx) {
    uint8_t * rawData = (uint8_t *)LITE_ALLOC(kRawBytes);
    uint8_t * cmpData = (uint8_t *)LITE_ALLOC(kRawBytes);
    uint8_t * decData = (uint8_t *)LITE_ALLOC(kRawBytes);

    MemZero(rawData, kRawBytes);
    MemSet(rawData, kRawBytes / 3, 1);
    MemSet(rawData + (kRawBytes / 3), kRawBytes / 3, 2);
    MemSet((rawData + kRawBytes / 3) + (kRawBytes / 3), kRawBytes / 3, 3);

    MiniZCompressor cmp;
    size_t cmpBytes = kRawBytes;
    const bool cresult = cmp.CompressWithContext(kRawBytes, rawData, &cmpBytes, cmpData);
    size_t decBytes = kRawBytes;
    const bool dresult = cmp.DecompressWithContext(cmpBytes, cmpData, &decBytes, decData);
    const bool binarySame = !MemCmp(rawData, decData, kRawBytes);
    EXPECT_TRUE(cresult);
    EXPECT_TRUE(dresult);
    EXPECT_TRUE(binarySame);
    MemZero(decData, kRawBytes);
    const bool dresult2 = cmp.DecompressWithContext(cmpBytes, cmpData, &decBytes, decData);
    EXPECT_TRUE(dresult2);
    EXPECT_EQ(0, MemCmp(rawData, decData, kRawBytes));
}

} // namespace lite
