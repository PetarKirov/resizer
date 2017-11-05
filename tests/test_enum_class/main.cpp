#include "image/config/config.h"
#include "test_util/assert.h"

ENUM_CLASS_BEGIN(Enum1, uint32_t)
    member1,
    member2,
    member3 = 31,
    member4
ENUM_CLASS_END(Enum1)

ENUM_CLASS_BEGIN(Enum2, uint8_t)
    member1
ENUM_CLASS_END(Enum2)

int main()
{
    STATIC_ASSERT(sizeof(Enum1) == 4);
    STATIC_ASSERT((uint32_t)Enum1::member1 == 0);
    STATIC_ASSERT((uint32_t)Enum1::member2 == 1);
    STATIC_ASSERT((uint32_t)Enum1::member3 == 31);
    STATIC_ASSERT((uint32_t)Enum1::member4 == 32);

    STATIC_ASSERT(sizeof(Enum2) == 1);
    STATIC_ASSERT((uint8_t)Enum2::member1 == 0);

    ASSERT_EQ(sizeof(Enum1), 4);
    ASSERT_EQ((uint32_t)Enum1::member1, 0);
    ASSERT_EQ((uint32_t)Enum1::member2, 1);
    ASSERT_EQ((uint32_t)Enum1::member3, 31);
    ASSERT_EQ((uint32_t)Enum1::member4, 32);

    ASSERT_EQ(sizeof(Enum2), 1);
    ASSERT_EQ((uint8_t)Enum2::member1, 0);
}
