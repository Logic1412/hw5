#include <gtest/gtest.h>

#include <ranges>
#include <chrono>
#include <algorithm>
#include <random>

extern "C"
{
#include "quicksort_c.h"

    int intcompare(const void *a, const void *b)
    {
        int aint = *((int *)a);
        int bint = *((int *)b);
        if (aint < bint)
            return -1;
        if (aint > bint)
            return 1;
        return 0;
    }
    int longcompare(const void *a, const void *b)
    {
        long long ais = *((long long *)a);
        long long bis = *((long long *)b);
        if (ais < bis)
            return -1;
        if (ais > bis)
            return 1;
        return 0;
    }
}

TEST(QuicksortCTest, TestBasic)
{
    auto rng = std::default_random_engine();
    for (auto i : std::views::iota(0, 100))
    {
        (void)i;
        std::vector<int> test;
        std::vector<long long int> test2;
        for (auto j : std::views::iota(0, 100))
        {
            test.push_back(j);
            test2.push_back(j);
        }
        std::shuffle(test.begin(), test.end(), rng);
        std::shuffle(test2.begin(), test2.end(), rng);

        quicksort_c(test.data(), test.size(), sizeof(int), intcompare);
        quicksort_c(test2.data(), test2.size(), sizeof(long long), longcompare);
        for (auto j : std::views::iota(0, 100))
        {
            ASSERT_EQ(test[j], j);
            ASSERT_EQ(test2[j], j);
        }
    }
    std::vector<int> test2;
    for (auto j : std::views::iota(0, 100000))
    {
        test2.push_back(j);
    }
    std::shuffle(test2.begin(), test2.end(), rng);
    quicksort_c(test2.data(), test2.size(), sizeof(int), intcompare);
}

TEST(QuicksortCTest, TestPathology)
{
    auto rng = std::default_random_engine();
    std::vector<int> test, test2;
    for (auto j : std::views::iota(0, 100000))
    {
        test.push_back(j);
        test2.push_back(42);
    }
    auto startpathology = std::chrono::system_clock::now();
    quicksort_c(test.data(), test.size(), sizeof(int), intcompare);
    quicksort_c(test2.data(), test2.size(), sizeof(int), intcompare);

    auto stoppathology = std::chrono::system_clock::now();
    std::shuffle(test.begin(), test.end(), rng);
    auto startnormal = std::chrono::system_clock::now();
    quicksort_c(test.data(), test.size(), sizeof(int), intcompare);

    auto stopnormal = std::chrono::system_clock::now();

    auto normaltime = std::chrono::duration_cast<std::chrono::microseconds>(stopnormal - startnormal).count();
    auto pathologicaltime = std::chrono::duration_cast<std::chrono::microseconds>(stoppathology - startpathology).count();
    EXPECT_TRUE(pathologicaltime < (normaltime * 2.2));
}
