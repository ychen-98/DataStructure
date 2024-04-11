// PA4: BST's
// Yao Chen

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

//create class for node in BST
struct Node{
    int data;
    Node* left;
    Node* right;

    explicit Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Start by sorting the input array of integers
// Middle Element as Root:
// Take the middle element of the sorted array to be the root of the BST.
// By doing so, we ensured that there are approximately equal numbers of nodes to the left and right of the root.
Node* sortedArrayToBST(const vector<int>& arr, int start, int end) {
    if (start > end) return nullptr;

    int mid = (start + end) / 2;
    Node* root = new Node(arr[mid]);

    root->left = sortedArrayToBST(arr, start, mid - 1);
    root->right = sortedArrayToBST(arr, mid + 1, end);

    return root;
}

void printTree(Node* node, const string& prefix = "", bool isLeft = true) {
    if (node != nullptr) {
        cout << prefix;
        cout << (isLeft ? "|-- " : "`-- ");
        cout << node->data << endl;

        printTree(node->left, prefix + (isLeft ? "|   " : "    "), true);
        printTree(node->right, prefix + (isLeft ? "|   " : "    "), false);
    }
}

int kthSmallestUtil(Node* root, int& k) {
    // If root is null or if k is already <= 0, we return -1 indicating error.
    if (!root || k <= 0) return -1;

    // recursively traverse the left subtree
    int left = kthSmallestUtil(root->left, k);
    if (k == 0) return left;

    // If the left subtree traversal didn't find the k-th smallest element,
    // we process the current node by decrementing k.
    // If k now becomes 0 after decrementing, the current node is the k-th smallest element.

    if (--k == 0) return root->data;

    //Right subtree traversal:
    // If neither the left subtree nor the current node is the k-th smallest element,
    // we continue the search in the right subtree
    return kthSmallestUtil(root->right, k);
}


int kthSmallest(Node* root, int k) {
    return kthSmallestUtil(root, k);
}

int main() {
    vector<int> arr = {6, 17, 20, 41, 45, 52, 57, 65, 71, 76, 79, 87, 92, 95, 99};
    sort(arr.begin(), arr.end());

    Node* root = sortedArrayToBST(arr, 0, arr.size() - 1);

    cout << "BST: " << endl;
    printTree(root);
    cout << endl;

    int k;
    cout << "Enter the value of k (between 1 and " << arr.size() << ") : ";
    cin >> k;

    int result = kthSmallest(root, k);

    if (result == -1) {
        cout << "Error: The value of k is invalid or there was an issue finding the k-th smallest element." << endl;
    } else {
        cout << k << "-th smallest element: " << result << endl;
    }
}