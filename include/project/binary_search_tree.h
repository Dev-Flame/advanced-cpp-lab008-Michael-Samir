#pragma once

#include <cstddef>
#include <stdexcept>
#include <vector>

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(int v, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : value(v), left(l), right(r) {}
};

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();

    bool insert(int value);
    bool remove(int value);
    bool search(int value) const;
    bool contains(int value) const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    int height() const;

    std::vector<int> inorderTraversal() const;
    std::vector<int> preorderTraversal() const;
    std::vector<int> postorderTraversal() const;

    int minimum() const;
    int maximum() const;

private:
    TreeNode* root_;
    std::size_t size_;

    void deleteSubtree(TreeNode* node);
    TreeNode* insertRecursive(TreeNode* node, int value);
    TreeNode* removeRecursive(TreeNode* node, int value);
    bool searchRecursive(const TreeNode* node, int value) const;
    void inorderRecursive(const TreeNode* node, std::vector<int>& result) const;
    void preorderRecursive(const TreeNode* node, std::vector<int>& result) const;
    void postorderRecursive(const TreeNode* node, std::vector<int>& result) const;
    int heightRecursive(const TreeNode* node) const;
    int minimumRecursive(const TreeNode* node) const;
    int maximumRecursive(const TreeNode* node) const;
};
