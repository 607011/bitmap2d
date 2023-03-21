#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <utility>

#include <gtest/gtest.h>

#include "bitmap2d.hpp"

TEST(SizeTest, Tiny)
{
    bitmap2d<1, 1, uint32_t> test;
    ASSERT_EQ(test.rows(), 1);
    ASSERT_EQ(test.cols(), 1);
    ASSERT_EQ(test.size(), 1);
}

TEST(SizeTest, Small)
{
    typedef uint32_t size_type;
    bitmap2d<4, 4, size_type> test;
    ASSERT_EQ(test.rows(), 4);
    ASSERT_EQ(test.cols(), 4);
    ASSERT_EQ(test.size(), std::max(1UL, 4 * 4 / (sizeof(size_type) * CHAR_BIT)));
}

TEST(SizeTest, Medium)
{
    typedef uint32_t size_type;
    bitmap2d<16, 16, size_type> test;
    ASSERT_EQ(test.rows(), 16);
    ASSERT_EQ(test.cols(), 16);
    ASSERT_EQ(test.size(), std::max(1UL, 16 * 16 / (sizeof(size_type) * CHAR_BIT)));
}

TEST(SizeTest, Large)
{
    typedef uint32_t size_type;
    bitmap2d<1024, 768, size_type> test;
    ASSERT_EQ(test.rows(), 1024);
    ASSERT_EQ(test.cols(), 768);
    ASSERT_EQ(test.size(), std::max(1UL, 1024 * 768 / (sizeof(size_type) * CHAR_BIT)));
}

TEST(SizeTest, Large1)
{
    typedef uint64_t size_type;
    bitmap2d<768, 1024, size_type> test;
    ASSERT_EQ(test.rows(), 768);
    ASSERT_EQ(test.cols(), 1024);
    ASSERT_EQ(test.size(), std::max(1UL, 768 * 1024 / (sizeof(size_type) * CHAR_BIT)));
}

TEST(SizeTest, Large2)
{
    typedef uint8_t size_type;
    bitmap2d<1000, 1000, size_type> test;
    ASSERT_EQ(test.rows(), 1000);
    ASSERT_EQ(test.cols(), 1000);
    ASSERT_EQ(test.size(), std::max(1UL, 1000 * 1000 / (sizeof(size_type) * CHAR_BIT)));
}

TEST(SizeTest, Huge)
{
    typedef uint16_t size_type;
    auto *test = new bitmap2d<12'345, 6'789, size_type>();
    ASSERT_EQ(test->rows(), 12345);
    ASSERT_EQ(test->cols(), 6789);
    ASSERT_EQ(test->size(), std::max(1UL, 12'345 * 6'789 / (sizeof(size_type) * CHAR_BIT)));
    delete test;
}

// TEST(SizeTest, VeryHuge)
// {
//     auto *test = new bitmap2d<123'456, 456'789>();
//     ASSERT_EQ(test->size(), 881'145'981);
//     delete test;
// }

TEST(PatternTest, Empty)
{
    bitmap2d<64, 64> a;
    for (size_t i = 0; i < a.rows(); ++i)
    {
        for (size_t j = 0; j < a.cols(); ++j)
        {
            ASSERT_FALSE(a.get(i, j)) << "i=" << i << ", j=" << j;
        }
    }
}

TEST(PatternTest, Full)
{
    bitmap2d<64, 64> a;
    for (size_t i = 0; i < a.rows(); ++i)
    {
        for (size_t j = 0; j < a.cols(); ++j)
        {
            a.set(i, j);
        }
    }
    for (size_t i = 0; i < a.rows(); ++i)
    {
        for (size_t j = 0; j < a.cols(); ++j)
        {
            ASSERT_TRUE(a.get(i, j)) << "i=" << i << ", j=" << j;
        }
    }
}

TEST(PatternTest, OneZero)
{
    bitmap2d<64, 64> a;
    for (size_t i = 0; i < a.rows(); i += 2)
    {
        for (size_t j = 0; j < a.cols(); j += 2)
        {
            a.set(i, j);
        }
    }
    for (size_t i = 1; i < a.rows(); i += 2)
    {
        for (size_t j = 1; j < a.cols(); j += 2)
        {
            ASSERT_FALSE(a.get(i, j)) << "i=" << i << ", j=" << j;
        }
    }
    for (size_t i = 0; i < a.rows(); i += 2)
    {
        for (size_t j = 0; j < a.cols(); j += 2)
        {
            ASSERT_TRUE(a.get(i, j)) << "i=" << i << ", j=" << j;
        }
    }
}

TEST(PatternTest, ZeroOne)
{
    bitmap2d<64, 64> a;
    for (size_t i = 1; i < a.rows(); i += 2)
    {
        for (size_t j = 1; j < a.cols(); j += 2)
        {
            a.set(i, j);
        }
    }
    for (size_t i = 1; i < a.rows(); i += 2)
    {
        for (size_t j = 1; j < a.cols(); j += 2)
        {
            ASSERT_TRUE(a.get(i, j)) << "i=" << i << ", j=" << j;
        }
    }
    for (size_t i = 0; i < a.rows(); i += 2)
    {
        for (size_t j = 0; j < a.cols(); j += 2)
        {
            ASSERT_FALSE(a.get(i, j)) << "i=" << i << ", j=" << j;
        }
    }
}

TEST(PatternTest, Diagonal)
{
    bitmap2d<64, 64> a;
    for (size_t i = 0; i < a.cols(); ++i)
    {
        a.set(i, i);
    }
    for (size_t i = 0; i < a.rows(); ++i)
    {
        for (size_t j = 0; j < a.cols(); ++j)
        {
            if (i != j)
            {
                ASSERT_FALSE(a.get(i, j)) << "i=" << i << ", j=" << j;
            }
            else
            {
                ASSERT_TRUE(a.get(i, i)) << "i=" << i << ", j=" << j;
            }
        }
    }
    for (size_t i = 0; i < a.cols(); ++i)
    {
        a.set(i, i, false);
    }
    for (size_t i = 0; i < a.cols(); ++i)
    {
        ASSERT_FALSE(a(i, i));
    }
}