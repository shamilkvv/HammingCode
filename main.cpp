#include <gtest/gtest.h>
#include "coder.cpp" 

TEST(HammingCodeTest, EncodeDecodeA) {
    char input = 'a';
    int encoded = Encode1(input);
    int decoded = decode1(encoded);
    EXPECT_EQ(decoded, input);
}

TEST(HammingCodeTest, EncodeDecodeB) {
    char input = 'b';
    int encoded = Encode1(input);
    int decoded = decode1(encoded);
    EXPECT_EQ(decoded, input);
}

TEST(HammingCodeTest, EncodeDecodeC) {
    char input = 'c';
    int encoded = Encode1(input);
    int decoded = decode1(encoded);
    EXPECT_EQ(decoded, input);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
