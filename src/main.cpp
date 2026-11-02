#include "project/binary_search_tree.h"

#include <iostream>

int main() {
    BinarySearchTree tree;
    for (int value : {10, 5, 15, 3, 7, 12, 18}) {
        tree.insert(value);
    }
    std::cout << "Inorder:";
    for (int value : tree.inorderTraversal()) {
        std::cout << ' ' << value;
    }
    std::cout << "\nSize: " << tree.size()
              << "\nHeight: " << tree.height()
              << "\nMinimum: " << tree.minimum()
              << "\nMaximum: " << tree.maximum() << '\n';
    tree.remove(10);
    std::cout << "After removing 10, size: " << tree.size() << '\n';
}
