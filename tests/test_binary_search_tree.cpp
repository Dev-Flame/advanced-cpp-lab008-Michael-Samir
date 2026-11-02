#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "project/binary_search_tree.h"

#include <stdexcept>
#include <algorithm>
#include <limits>
#include <random>
#include <vector>

TEST_CASE("BST empty-state and size checks") {
    BinarySearchTree tree;
    REQUIRE(tree.empty());
    REQUIRE(tree.size() == 0u);
    REQUIRE_THROWS_AS(tree.minimum(), std::logic_error);
    REQUIRE_THROWS_AS(tree.maximum(), std::logic_error);
    REQUIRE(tree.inorderTraversal().empty());
    REQUIRE(tree.preorderTraversal().empty());
    REQUIRE(tree.postorderTraversal().empty());
}

TEST_CASE("BST insert and search: basic values") {
    BinarySearchTree tree;
    REQUIRE(tree.insert(10));
    REQUIRE(tree.insert(5));
    REQUIRE(tree.insert(15));
    REQUIRE(tree.insert(3));
    REQUIRE(tree.insert(7));
    REQUIRE(tree.insert(12));
    REQUIRE(tree.insert(18));

    REQUIRE(tree.size() == 7u);
    REQUIRE(tree.search(10));
    REQUIRE(tree.search(3));
    REQUIRE(tree.search(18));
    REQUIRE(tree.contains(7));
    REQUIRE_FALSE(tree.search(11));
    REQUIRE_FALSE(tree.contains(99));
    REQUIRE_FALSE(tree.search(0));
}

TEST_CASE("BST insert: duplicate handling") {
    BinarySearchTree tree;
    REQUIRE(tree.insert(8));
    REQUIRE_FALSE(tree.insert(8));
    REQUIRE(tree.size() == 1u);
    REQUIRE(tree.search(8));
}

TEST_CASE("BST minimum and maximum") {
    BinarySearchTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    REQUIRE(tree.minimum() == 5);
    REQUIRE(tree.maximum() == 35);
}

TEST_CASE("BST minimum and maximum with negatives") {
    BinarySearchTree tree;
    for (int value : {-10, 0, 15, -20, 5, 12, -5}) {
        tree.insert(value);
    }

    REQUIRE(tree.minimum() == -20);
    REQUIRE(tree.maximum() == 15);
}

TEST_CASE("BST inorder, preorder, and postorder traversals") {
    BinarySearchTree tree;
    std::vector<int> values = {10, 5, 15, 3, 7, 12, 18};
    for (int value : values) {
        tree.insert(value);
    }

    REQUIRE(tree.inorderTraversal() == std::vector<int>({3, 5, 7, 10, 12, 15, 18}));
    REQUIRE(tree.preorderTraversal() == std::vector<int>({10, 5, 3, 7, 15, 12, 18}));
    REQUIRE(tree.postorderTraversal() == std::vector<int>({3, 7, 5, 12, 18, 15, 10}));
}

TEST_CASE("BST traversals on a single-node tree") {
    BinarySearchTree tree;
    tree.insert(42);

    REQUIRE(tree.inorderTraversal() == std::vector<int>({42}));
    REQUIRE(tree.preorderTraversal() == std::vector<int>({42}));
    REQUIRE(tree.postorderTraversal() == std::vector<int>({42}));
}

TEST_CASE("BST remove: leaf, internal, and missing nodes") {
    BinarySearchTree tree;
    for (int value : {10, 5, 15, 3, 7, 12, 18, 1}) {
        tree.insert(value);
    }

    REQUIRE(tree.remove(1));
    REQUIRE_FALSE(tree.search(1));
    REQUIRE(tree.remove(15));
    REQUIRE_FALSE(tree.search(15));
    REQUIRE(tree.remove(10));
    REQUIRE_FALSE(tree.search(10));
    REQUIRE_FALSE(tree.remove(99));
    REQUIRE(tree.size() == 5u);
}

TEST_CASE("BST remove: root with two children and subtree re-linking") {
    BinarySearchTree tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80, 25}) {
        tree.insert(value);
    }

    REQUIRE(tree.remove(50));
    REQUIRE_FALSE(tree.search(50));
    REQUIRE(tree.search(25));
    REQUIRE(tree.search(20));
    REQUIRE(tree.search(60));
    REQUIRE(tree.size() == 7u);
}

TEST_CASE("BST height and edge cases") {
    BinarySearchTree emptyTree;
    REQUIRE(emptyTree.height() == 0);

    BinarySearchTree singleTree;
    singleTree.insert(42);
    REQUIRE(singleTree.height() == 1);

    BinarySearchTree tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        tree.insert(value);
    }
    REQUIRE(tree.height() == 3);

    BinarySearchTree skewed;
    for (int value : {1, 2, 3, 4, 5, 6, 7}) {
        skewed.insert(value);
    }
    REQUIRE(skewed.height() == 7);
}

TEST_CASE("BST handles negative and repeated values") {
    BinarySearchTree tree;
    tree.insert(-5);
    tree.insert(0);
    tree.insert(-10);
    tree.insert(10);

    REQUIRE(tree.search(-5));
    REQUIRE(tree.search(0));
    REQUIRE(tree.search(10));
    REQUIRE_FALSE(tree.search(2));
    REQUIRE_FALSE(tree.insert(-5));
    REQUIRE(tree.size() == 4u);
}

TEST_CASE("BST contains is consistent with search") {
    BinarySearchTree tree;
    for (int value : {8, 3, 10, 1, 6, 14, 4, 7}) {
        tree.insert(value);
    }

    for (int value : {1, 3, 4, 6, 7, 8, 10, 14}) {
        REQUIRE(tree.contains(value));
        REQUIRE(tree.search(value));
    }

    for (int value : {-1, 2, 5, 9, 12, 15}) {
        REQUIRE_FALSE(tree.contains(value));
        REQUIRE_FALSE(tree.search(value));
    }
}

TEST_CASE("BST empty removal, one-child roots, and reuse") {
    BinarySearchTree tree;
    REQUIRE_FALSE(tree.remove(1));
    REQUIRE_FALSE(tree.search(1));
    for (int child : {5, 15}) {
        REQUIRE(tree.insert(10));
        REQUIRE(tree.insert(child));
        REQUIRE(tree.remove(10));
        REQUIRE(tree.size() == 1);
        REQUIRE(tree.height() == 1);
        REQUIRE(tree.minimum() == child);
        REQUIRE(tree.maximum() == child);
        REQUIRE(tree.remove(child));
        REQUIRE(tree.empty());
        REQUIRE(tree.height() == 0);
        REQUIRE_THROWS_AS(tree.minimum(), std::logic_error);
        REQUIRE_THROWS_AS(tree.maximum(), std::logic_error);
    }
}

TEST_CASE("BST deletion keeps the successor's right child") {
    BinarySearchTree tree;
    for (int value : {50, 30, 80, 60, 90, 65}) {
        tree.insert(value);
    }
    REQUIRE(tree.remove(50));
    REQUIRE(tree.size() == 5);
    REQUIRE(tree.inorderTraversal() == std::vector<int>{30, 60, 65, 80, 90});
    REQUIRE(tree.preorderTraversal() == std::vector<int>{60, 30, 80, 65, 90});
    REQUIRE(tree.postorderTraversal() == std::vector<int>{30, 65, 90, 80, 60});
}

TEST_CASE("BST supports the full integer range") {
    BinarySearchTree tree;
    const int low = std::numeric_limits<int>::min();
    const int high = std::numeric_limits<int>::max();
    for (int value : {0, low, high}) {
        REQUIRE(tree.insert(value));
        REQUIRE_FALSE(tree.insert(value));
        REQUIRE(tree.contains(value));
    }
    REQUIRE(tree.minimum() == low);
    REQUIRE(tree.maximum() == high);
    REQUIRE(tree.remove(0));
    REQUIRE(tree.inorderTraversal() == std::vector<int>{low, high});
}

TEST_CASE("BST shuffled insertion and removal preserve ordering and size") {
    BinarySearchTree tree;
    std::vector<int> keys;
    for (int value = -128; value < 128; ++value) {
        keys.push_back(value);
    }
    auto remaining = keys;
    std::mt19937 random(42);
    std::shuffle(keys.begin(), keys.end(), random);
    for (int value : keys) {
        REQUIRE(tree.insert(value));
    }
    std::shuffle(keys.begin(), keys.end(), random);
    for (int value : keys) {
        REQUIRE(tree.remove(value));
        remaining.erase(std::lower_bound(remaining.begin(), remaining.end(), value));
        REQUIRE(tree.size() == remaining.size());
        REQUIRE(tree.inorderTraversal() == remaining);
        REQUIRE_FALSE(tree.contains(value));
        REQUIRE_FALSE(tree.remove(value));
        if (!remaining.empty()) {
            REQUIRE(tree.minimum() == remaining.front());
            REQUIRE(tree.maximum() == remaining.back());
        }
    }
    REQUIRE(tree.empty());
}
