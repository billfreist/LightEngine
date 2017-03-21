///
/// LICENSE
///

#include "pch.h"
#include <core/identifer.h>

LITE_NAMESPACE_BEGIN(lite)

LITE_UNIQUE_IDENTIFIER(AlphaId, uint32_t);
LITE_UNIQUE_IDENTIFIER(BetaId, uint32_t);

TEST(Identifier, TypeSafety) {
    AlphaId idA(1);
    AlphaId idAA(1);
    BetaId idB(5);
    // idA = idB;
    EXPECT_EQ(idA, idAA);
    EXPECT_FALSE(idA < idAA);
    EXPECT_FALSE(idA > idAA);
}

LITE_NAMESPACE_END(lite)
