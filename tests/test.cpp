// Copyright 2020 elizavetamaikova
#include "CacheExploration.hpp"
#include <gtest/gtest.h>

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
    CacheExploration qwe(64, 8192);
    std::cout << qwe;
}
