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
    const std::size_t oldSize = size_;
    root_ = insertRecursive(root_, value);
    return size_ != oldSize;
}

bool BinarySearchTree::remove(int value) {
    const std::size_t oldSize = size_;
    root_ = removeRecursive(root_, value);
    return size_ != oldSize;
}

bool BinarySearchTree::search(int value) const {
    return searchRecursive(root_, value);
}

bool BinarySearchTree::contains(int value) const {
    return search(value);
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
    // An empty subtree becomes a leaf. Equal values are already present.
    if (!node) {
        TreeNode* leaf = new TreeNode(value);
        ++size_;
        return leaf;
    }
    if (value < node->value) {
        node->left = insertRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = insertRecursive(node->right, value);
    }
    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int value) {
    if (!node) {
        return nullptr;
    }
    if (value < node->value) {
        node->left = removeRecursive(node->left, value);
    } else if (value > node->value) {
        node->right = removeRecursive(node->right, value);
    } else if (!node->left || !node->right) {
        // A leaf disappears; a one-child node is replaced by its child.
        TreeNode* child = node->left ? node->left : node->right;
        delete node;
        --size_;
        return child;
    } else {
        // Use the inorder successor, then remove its original node.
        // Only that physical deletion decrements size_.
        node->value = minimumRecursive(node->right);
        node->right = removeRecursive(node->right, node->value);
    }
    return node;
}

bool BinarySearchTree::searchRecursive(const TreeNode* node, int value) const {
    if (!node) {
        return false;
    }
    if (value < node->value) {
        return searchRecursive(node->left, value);
    }
    if (value > node->value) {
        return searchRecursive(node->right, value);
    }
    return true;
}

void BinarySearchTree::inorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (!node) {
        return;
    }
    inorderRecursive(node->left, result);
    result.push_back(node->value);
    inorderRecursive(node->right, result);
}

void BinarySearchTree::preorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (!node) {
        return;
    }
    result.push_back(node->value);
    preorderRecursive(node->left, result);
    preorderRecursive(node->right, result);
}

void BinarySearchTree::postorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if (!node) {
        return;
    }
    postorderRecursive(node->left, result);
    postorderRecursive(node->right, result);
    result.push_back(node->value);
}

int BinarySearchTree::heightRecursive(const TreeNode* node) const {
    if (!node) {
        return 0;
    }
    return 1 + std::max(heightRecursive(node->left), heightRecursive(node->right));
}

int BinarySearchTree::minimumRecursive(const TreeNode* node) const {
    return node->left ? minimumRecursive(node->left) : node->value;
}

int BinarySearchTree::maximumRecursive(const TreeNode* node) const {
    return node->right ? maximumRecursive(node->right) : node->value;
}
