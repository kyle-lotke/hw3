// CS104 Heap test suite

#include "heap.h"  // Include your heap implementation

#include <gtest/gtest.h>
#include <queue>
#include <algorithm>
#include <vector>
#include <random>

// Type alias for easier heap type definition
typedef int IntType;

#define RANDOM_SEED 57821
const int DEFAULT_HEAP_ARY = 2;
const int MAX_HEAP_ARY = 26;

// **HeapTest Class for Google Test Framework**
class HeapTest : public testing::Test {
protected:
    HeapTest() {
        D_ARY = DEFAULT_HEAP_ARY;  // Default to binary heap
    }

    ~HeapTest() override = default;
    void SetUp() override {}  // Optional setup before each test
    void TearDown() override {}  // Optional cleanup after each test

    int D_ARY;  // Stores the value of d-ary heap
};

// **Helper Function to Verify Heap Contents**
testing::AssertionResult checkHeapContents(Heap<int>& heap, std::vector<int> contents) {
    std::sort(contents.begin(), contents.end());  // Sort for correct heap ordering

    for (size_t i = 0; i < contents.size(); ++i) {
        if (heap.empty()) {
            return testing::AssertionFailure() << "Heap is missing " << (contents.size() - i) << " elements!";
        }

        if (heap.top() != contents[i]) {
            return testing::AssertionFailure() << "Incorrect element at index " << i << "! Expected " << contents[i] << ", got " << heap.top();
        }

        heap.pop();
    }

    if (!heap.empty()) {
        return testing::AssertionFailure() << "Heap has extra elements!";
    }

    return testing::AssertionSuccess();
}

// **Basic Construction & Empty Heap Tests**
TEST_F(HeapTest, ConstructionDestruction) {
    Heap<IntType> heap(D_ARY);
}

TEST_F(HeapTest, InitiallyEmpty) {
    Heap<IntType> heap(D_ARY);
    EXPECT_TRUE(heap.empty());
}

TEST_F(HeapTest, EmptyTopException) {
    Heap<IntType> heap(D_ARY);
    EXPECT_ANY_THROW(heap.top());
}

TEST_F(HeapTest, EmptyPopException) {
    Heap<IntType> heap(D_ARY);
    EXPECT_ANY_THROW(heap.pop());
}

// **Single Element Tests**
TEST_F(HeapTest, SingleItemNonempty) {
    Heap<IntType> heap(D_ARY);
    heap.push(1);
    EXPECT_FALSE(heap.empty());
}

TEST_F(HeapTest, SingleItemPush) {
    Heap<IntType> heap(D_ARY);
    heap.push(1);
    EXPECT_EQ(1, heap.top());
}

TEST_F(HeapTest, SingleItemPushPop) {
    Heap<IntType> heap(D_ARY);
    heap.push(1);
    heap.pop();
    EXPECT_TRUE(heap.empty());
}

// **Basic Multi-Element Tests**
TEST_F(HeapTest, TwoElementPush_LowPriFirst) {
    Heap<IntType> heap(D_ARY);
    heap.push(3);
    heap.push(10);
    EXPECT_EQ(3, heap.top());
    heap.pop();
    EXPECT_EQ(10, heap.top());
}

TEST_F(HeapTest, TwoElementPush_HighPriFirst) {
    Heap<IntType> heap(D_ARY);
    heap.push(50);
    heap.push(49);
    EXPECT_EQ(49, heap.top());
    heap.pop();
    EXPECT_EQ(50, heap.top());
}

TEST_F(HeapTest, Duplicates) {
    Heap<IntType> heap(D_ARY);
    heap.push(9);
    heap.push(9);
    heap.push(20);
    EXPECT_EQ(9, heap.top());
    heap.pop();
    heap.pop();
    EXPECT_EQ(20, heap.top());
}

TEST_F(HeapTest, NegativeElements) {
    Heap<IntType> heap(D_ARY);
    heap.push(9999);
    heap.push(-9999);
    EXPECT_EQ(-9999, heap.top());
}

// **Heap Behavior with Different Orderings**
TEST_F(HeapTest, ThreeElementPush_0_5_10) {
    Heap<IntType> heap(D_ARY);
    heap.push(0);
    heap.push(5);
    heap.push(10);
    EXPECT_EQ(0, heap.top());
    heap.pop();
    EXPECT_EQ(5, heap.top());
    heap.pop();
    EXPECT_EQ(10, heap.top());
}

TEST_F(HeapTest, ThreeElementPush_5_0_10) {
    Heap<IntType> heap(D_ARY);
    heap.push(5);
    heap.push(0);
    heap.push(10);
    EXPECT_EQ(0, heap.top());
    heap.pop();
    EXPECT_EQ(5, heap.top());
    heap.pop();
    EXPECT_EQ(10, heap.top());
}

// **Max-Heap (Greater Comparator)**
TEST_F(HeapTest, GreaterComparator) {
    Heap<IntType, std::greater<IntType>> heap(D_ARY);
    heap.push(10);
    heap.push(1000);
    heap.push(100);
    EXPECT_EQ(1000, heap.top());
    heap.pop();
    EXPECT_EQ(100, heap.top());
    heap.pop();
    EXPECT_EQ(10, heap.top());
}

// **String Heap**
TEST_F(HeapTest, StringStorage) {
    Heap<std::string> stringHeap(D_ARY);
    stringHeap.push("blah");
    stringHeap.push("bluh");
    stringHeap.push("bloh");
    EXPECT_EQ("blah", stringHeap.top());
    stringHeap.pop();
    EXPECT_EQ("bloh", stringHeap.top());
    stringHeap.pop();
    EXPECT_EQ("bluh", stringHeap.top());
}

// **Multi-ary Heap Tests**
TEST_F(HeapTest, FiveElementPush_TrinaryHeap) {
    Heap<IntType> heap(3);
    heap.push(0);
    heap.push(5);
    heap.push(10);
    heap.push(15);
    heap.push(20);
    EXPECT_TRUE(checkHeapContents(heap, {0, 5, 10, 15, 20}));
}

TEST_F(HeapTest, SixElementPush_QuaternaryHeap) {
    Heap<IntType> heap(4);
    heap.push(0);
    heap.push(5);
    heap.push(10);
    heap.push(15);
    heap.push(20);
    heap.push(25);
    EXPECT_TRUE(checkHeapContents(heap, {0, 5, 10, 15, 20, 25}));
}

// **Stress Tests**
TEST(HeapStress, LargeBinaryHeap) {
    std::vector<int> data(1000);
    std::generate(data.begin(), data.end(), []() { return rand() % 10000; });

    Heap<int> heap(2);
    for (int value : data) {
        heap.push(value);
    }
    EXPECT_TRUE(checkHeapContents(heap, data));
}

TEST(HeapStress, LargeTernaryHeap) {
    std::vector<int> data(1000);
    std::generate(data.begin(), data.end(), []() { return rand() % 10000; });

    Heap<int> heap(3);
    for (int value : data) {
        heap.push(value);
    }
    EXPECT_TRUE(checkHeapContents(heap, data));
}

TEST(HeapStress, LargeTwelveAryHeap) {
    std::vector<int> data(1000);
    std::generate(data.begin(), data.end(), []() { return rand() % 10000; });

    Heap<int> heap(12);
    for (int value : data) {
        heap.push(value);
    }
    EXPECT_TRUE(checkHeapContents(heap, data));
}

// **Main Function for Running Tests**
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
