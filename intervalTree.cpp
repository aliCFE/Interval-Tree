/*
 *==========================================================*
 *                                                          *
 *          Advanced Data Structures - Assignment-2         *
 *                      Interval Tree                       *
 *                                                          *
 * ----------------------------------------------------------
 *                                                          *
 *          Author1.Name() = Ali Mohammed Abduljabbar;      *
 *                  Author1.ID() = 20210876;                *
 *          Author2.Name() = Youssef Emad Eldin Ali;        *
 *                  Author2.ID() = 20210479;                *
 *          Author3.Name() = Mohamed Ashraf Fahim;          *
 *                  Author3.ID() = 20210329;                *
 *          Author4.Name() = AbdelRahman Ezzat;             *
 *                  Author4.ID() = 20210208                 *
 *          Author5.Name() = Momen Mostafa Mabrook;         *
 *                  Author5.ID() = 20210416                 *
 *                                                          *
 * ---------------------------------------------------------*
 *                                                          *
 *                   Start Date: 21-12-2023                 *
 *                   Last Modified: 24-12-2023              *
 *                   Version: 1.0V                          *
 *                                                          *
 * =========================================================*
 */

#include <iostream>
#include <iomanip>

using namespace std;

class IntervalTree{
private:
    // Node class to represent intervals in the interval tree
    class IntervalNode{
    public:
        int interval[2];       // Array to store the start and end points of the interval
        int maximum;            // Maximum endpoint of the interval subtree rooted at this node
        IntervalNode *leftChild;    // Pointer to the left child node
        IntervalNode *rightChild;   // Pointer to the right child node

        // Constructor to initialize an IntervalNode with a given interval
        IntervalNode(int start, int end)
        {
            interval[0] = start;
            interval[1] = end;
            maximum = end;
            leftChild = rightChild = nullptr;
        }
    };

    IntervalNode *root;  // Pointer to the root of the interval tree

    // Helper function to get the maximum endpoint of a node (or -1e9 if node is null)
    int nodeMax(IntervalNode *node){
        if (node == nullptr)
            return -1e9;

        return node->maximum;
    }

    // Recursive function to insert a node into the interval tree
    IntervalNode *insert(IntervalNode *root, IntervalNode *node){
        if (root == nullptr)
            return node;

        // Compare endpoint values to decide whether to insert in the left or right subtree
        if (node->interval[1] > root->interval[1])
            root->rightChild = insert(root->rightChild, node);
        else
            root->leftChild = insert(root->leftChild, node);

        // Update the maximum endpoint in the current node
        root->maximum = max(root->interval[1], max(nodeMax(root->leftChild), nodeMax(root->rightChild)));

        return root;
    }

    // Helper function to check if two intervals overlap
    bool doIntervalsOverlap(int start1, int end1, int start2, int end2){
        return (start1 <= end2) && (end1 >= start2);
    }

    // Recursive function to check overlap between the interval tree and a given query interval
    bool doIntervalTreeAndQueryOverlap(IntervalNode *node, int start, int end){
        if (node == nullptr)
            return false;

        // Check if the current node's interval overlaps with the query interval
        if (doIntervalsOverlap(node->interval[0], node->interval[1], start, end))
            return true;

        // If there could be overlap in the left subtree, recursively check the left subtree
        if (node->leftChild != nullptr && node->leftChild->maximum >= start)
            return doIntervalTreeAndQueryOverlap(node->leftChild, start, end);

        // Otherwise, check the right subtree
        return doIntervalTreeAndQueryOverlap(node->rightChild, start, end);
    }

    // Recursive function to search for an interval in the interval tree
    int *search(IntervalNode *root, int start, int end);

public:
    // Constructor to initialize an empty interval tree
    IntervalTree(){
        root = nullptr;
    }

    // Function to insert a new interval into the interval tree
    void insert(int start, int end){
        root = insert(root, new IntervalNode(start, end));
    }

    // Function to check if there is any overlap with a given query interval
    bool doQueryOverlap(int start, int end){
        return doIntervalTreeAndQueryOverlap(root, start, end);
    }

    // Function to perform a query and return the overlapping interval
    int *query(int start, int end){
        return search(root, start, end);
    }

    // Function to get the root of the interval tree
    IntervalNode *getRoot(){
        return root;
    }
};

// Definition of the search function outside the private section of the class
int *IntervalTree::search(IntervalNode *root, int start, int end){
    if (root == nullptr)
        return nullptr;

    // Check if the current node's interval matches the query interval
    if (doIntervalsOverlap(start, end, root->interval[0], root->interval[1]))
        return root->interval;

    // If there could be overlap in the left subtree, recursively search the left subtree
    if (root->leftChild != nullptr && root->leftChild->maximum >= start)
        return search(root->leftChild, start, end);

    // Otherwise, search the right subtree
    return search(root->rightChild, start, end);
}

int main(){
    // Create an instance of the IntervalTree
    IntervalTree intervalTree;

    // Insert intervals into the interval tree
    intervalTree.insert(1, 5);
    intervalTree.insert(10, 15);
    intervalTree.insert(20, 25);

    // Define a query interval
    int queryStart = 12;
    int queryEnd = 22;

    // Check if there is any overlap with the query interval
    bool overlap = intervalTree.doQueryOverlap(queryStart, queryEnd);

    // Output the result of the overlap check
    if (overlap)
        cout << "Overlap exists." << endl;
    else
        cout << "No overlap." << endl;

    // Perform a query and get the overlapping interval
    int *result = intervalTree.query(queryStart, queryEnd);

    // Output the result of the query
    if (result != nullptr){
        cout << "Overlap exists. Interval: [" << result[0] << ", " << result[1] << "]" << endl;
    }
    else{
        cout << "No overlap." << endl;
    }

    return 0;
}
