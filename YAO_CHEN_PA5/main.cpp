// Searching a key on a B-tree in C++

#include <iostream>
#include <random>
#include <vector>
#include <iomanip>


using namespace std;

// TreeNode represents a node in the B-tree
class TreeNode {
    int *keys;
    int t;
    TreeNode **C;
    int n;
    bool leaf;

public:
    int getKeyAt(int index) const {
        if (index >= 0 && index < n) {
            return keys[index];
        }
        return -1; // Some sentinel value. Handle this case appropriately.
    }

    TreeNode *getChildAt(int index) const {
        if (index >= 0 && index < 2 * t) {
            return C[index];
        }
        return nullptr;
    }

    int getNumKeys() const {
        return n;
    }

    bool isLeafNode() const {
        return leaf;
    }

    TreeNode(int temp, bool bool_leaf);

    void insertNonFull(int k);

    void splitChild(int i, TreeNode *y);

    void traverse();

    TreeNode *search(int k);

    friend class BTree;
};

// BTree class represents the B-tree structure and provides
// functionalities like insertion and search
class BTree {
    TreeNode *root;
    int t;

public:
    BTree(int temp) {
        root = NULL;
        t = temp;
    }

    TreeNode *getRoot() const {
        return root;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }

    TreeNode *search(int k) {
        return (root == NULL) ? NULL : root->search(k);
    }

    void insert(int k);
};

TreeNode::TreeNode(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys = new int[2 * t - 1];
    C = new TreeNode *[2 * t];

    n = 0;
}

void TreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }

    if (leaf == false)
        C[i]->traverse();
}

TreeNode *TreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return C[i]->search(k);
}

void BTree::insert(int k) {
    if (root == NULL) {
        root = new TreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            TreeNode *s = new TreeNode(t, false);

            s->C[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);

            root = s;
        } else
            root->insertNonFull(k);
    }
}

void TreeNode::insertNonFull(int k) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (C[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, C[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        C[i + 1]->insertNonFull(k);
    }
}

void TreeNode::splitChild(int i, TreeNode *y) {
    TreeNode *z = new TreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j + t];
    }

    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        C[j + 1] = C[j];

    C[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];
    n = n + 1;
}

// rangeSearch is a function that returns all keys in the B-tree
// that fall within the specified range [low, high]
vector<int> rangeSearch(TreeNode *node, int low, int high) {
    vector<int> keysInRange;

    if (!node) {
        return keysInRange;
    }

    int i = 0;
    while (i < node->getNumKeys() && node->getKeyAt(i) < low) {
        i++;
    }

    // Check the keys in this node
    while (i < node->getNumKeys() && node->getKeyAt(i) <= high) {
        keysInRange.push_back(node->getKeyAt(i));
        i++;
    }

    // If this node is not a leaf, continue the search in child nodes
    if (!node->isLeafNode()) {
        for (int j = 0; j <= node->getNumKeys(); j++) {
            if (j == i || (j < i && node->getKeyAt(j) >= low)) {
                vector<int> childKeys = rangeSearch(node->getChildAt(j), low, high);
                keysInRange.insert(keysInRange.end(), childKeys.begin(), childKeys.end());
            }
        }
    }

    return keysInRange;
}

int main() {
    // Prompt the user to enter value of N
    int N;
    cout << "Generate a sequence of N random integers (keys), in the range [0,...,3*N]" << endl;
    cout << "Enter the value of N (N >= 400): ";
    cin >> N;

    // Generate N random integers between 0 and 3*N
    vector<int> randomIntegers;
    default_random_engine generator(static_cast<long unsigned int>(time(0)));
    uniform_int_distribution<int> distribution(0, 3 * N);

    for (int i = 0; i < N; ++i) {
        randomIntegers.push_back(distribution(generator));
    }

    // Initialize a 5-way B-tree
    BTree tree(5);

    // Insert the generated random integers into the B-tree
    for (int k: randomIntegers) {
        tree.insert(k);
    }

    // Display the keys of the B-tree in the order they are stored
    cout << "The B-tree is: ";
    tree.traverse();

    cout << endl;

    // List the keys in the range [N, 2*N]
    vector<int> foundKeys = rangeSearch(tree.getRoot(), N, 2 * N);

    if (!foundKeys.empty()) {
        cout << "Keys in the range [" << N << ", " << 2 * N << "]:" << endl;
        for (int key: foundKeys) {
            cout << key << " ";
        }
        cout << endl;
    } else {
        cout << "No keys found in the range [" << N << ", " << 2 * N << "]." << endl;
    }

    return 0;
}