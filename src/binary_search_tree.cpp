#include "project/binary_search_tree.h"

#include <algorithm>
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::~BinarySearchTree() {
    deleteSubtree(root_);
}

void BinarySearchTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

bool BinarySearchTree::insert(int value) {
    (void)value;
    throw std::logic_error("Student implementation required: insert");
}

bool BinarySearchTree::remove(int value) {
    (void)value;
    throw std::logic_error("Student implementation required: remove");
}

bool BinarySearchTree::search(int value) const {
    (void)value;
    throw std::logic_error("Student implementation required: search");
}

bool BinarySearchTree::contains(int value) const {
    (void)value;
    throw std::logic_error("Student implementation required: contains");
}

bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

int BinarySearchTree::height() const {
    return heightRecursive(root_);
}

std::vector<int> BinarySearchTree::inorderTraversal() const {
    std::vector<int> result;
    inorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::preorderTraversal() const {
    std::vector<int> result;
    preorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::postorderTraversal() const {
    std::vector<int> result;
    postorderRecursive(root_, result);
    return result;
}

int BinarySearchTree::minimum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return minimumRecursive(root_);
}

int BinarySearchTree::maximum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return maximumRecursive(root_);
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value) {
    (void)node;
    (void)value;
    throw std::logic_error("Student implementation required: insertRecursive");
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int value) {
    (void)node;
    (void)value;
    throw std::logic_error("Student implementation required: removeRecursive");
}

bool BinarySearchTree::searchRecursive(const TreeNode* node, int value) const {
    (void)node;
    (void)value;
    throw std::logic_error("Student implementation required: searchRecursive");
}

void BinarySearchTree::inorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    (void)node;
    (void)result;
    throw std::logic_error("Student implementation required: inorderRecursive");
}

void BinarySearchTree::preorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    (void)node;
    (void)result;
    throw std::logic_error("Student implementation required: preorderRecursive");
}

void BinarySearchTree::postorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    (void)node;
    (void)result;
    throw std::logic_error("Student implementation required: postorderRecursive");
}

int BinarySearchTree::heightRecursive(const TreeNode* node) const {
    (void)node;
    throw std::logic_error("Student implementation required: heightRecursive");
}

int BinarySearchTree::minimumRecursive(const TreeNode* node) const {
    (void)node;
    throw std::logic_error("Student implementation required: minimumRecursive");
}

int BinarySearchTree::maximumRecursive(const TreeNode* node) const {
    (void)node;
    throw std::logic_error("Student implementation required: maximumRecursive");
}
