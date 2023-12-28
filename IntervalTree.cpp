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
 *                   Last Modified: 29-12-2023              *
 *                   Version: 1.0V                          *
 *                                                          *
 * =========================================================*
 */

#include <iostream>
#include <iomanip>

using namespace std;

class IntervalTree
{
private:
    // Node class to represent intervals in the interval tree
    class IntervalNode
    {
    public:
        int interval[2];          // Array to store the start and end points of the interval
        int maximum;              // Maximum endpoint of the interval subtree rooted at this node
        IntervalNode *leftChild;  // Pointer to the left child node
        IntervalNode *rightChild; // Pointer to the right child node

        // Constructor to initialize an IntervalNode with a given interval
        IntervalNode(int start, int end){
            interval[0] = start;
            interval[1] = end;
            maximum = end;
            leftChild = rightChild = nullptr;
        }
    };

    IntervalNode *root; // Pointer to the root of the interval tree

    // Helper function to get the maximum endpoint of a node (or -1e9 if node is null)
    int nodeMax(IntervalNode *node){
        if (node == nullptr)
            return -1e9;

        return node->maximum;
    }

    // Recursive function to insert a node into the interval tree
    IntervalNode *insert(IntervalNode *root, IntervalNode *node)
    {
        if (root == nullptr)
            return node;

        // Compare endpoint values to decide whether to insert in the left or right subtree
        if (node->interval[0] > root->interval[0] || (node->interval[0] == root->interval[0] && node->interval[1] > root->interval[1]))
            root->rightChild = insert(root->rightChild, node);
        else
            root->leftChild = insert(root->leftChild, node);

        // Update the maximum endpoint in the current node
        root->maximum = max(root->interval[1], max(nodeMax(root->leftChild), nodeMax(root->rightChild)));

        return root;
    }

    // Helper function to check if two intervals overlap
    bool doIntervalsOverlap(int start1, int end1, int start2, int end2)
    {
        return (start1 <= end2) && (end1 >= start2);
    }

    // Recursive function to check overlap between the interval tree and a given query interval

    int *SearchInterval(IntervalNode *root, int start, int end)
    {
        if (root == nullptr)
            return nullptr;

        // If there could be overlap in the left subtree, recursively SearchInterval the left subtree
        if (root->leftChild != nullptr && root->leftChild->maximum >= start)
            return SearchInterval(root->leftChild, start, end);

        // Check if the current node's interval matches the query interval
        if (doIntervalsOverlap(start, end, root->interval[0], root->interval[1]))
            return root->interval;

        // Otherwise, SearchInterval the right subtree
        return SearchInterval(root->rightChild, start, end);
    }

public:
    // Constructor to initialize an empty interval tree
    IntervalTree()
    {
        root = nullptr;
    }

    // Function to insert a new interval into the interval tree
    void insert(int start, int end)
    {
        root = insert(root, new IntervalNode(start, end));
    }

    // Function to check if there is any overlap with a given query interval
    bool doQueryOverlap(int start, int end)
    {
        return SearchInterval(root, start, end) != nullptr;
    }

    // Function to perm a query and return the overlapping interval
    int *query(int start, int end)
    {
        return SearchInterval(root, start, end);
    }

    // Function to get the root of the interval tree
    IntervalNode *getRoot()
    {
        return root;
    }
};

int main()
{
    // Create an instance of the IntervalTree
    IntervalTree intervalTree;

    // Insert intervals into the interval tree
    intervalTree.insert(1, 5);
    intervalTree.insert(10, 15);
    intervalTree.insert(20, 25);
    intervalTree.insert(19, 30);
    intervalTree.insert(2, 13);
    intervalTree.insert(4, 19);
    intervalTree.insert(3, 12);
    intervalTree.insert(2, 14);
    intervalTree.insert(2, 12);

    // Define a query interval
    int queryStart = 12;
    int queryEnd = 22;

    // Check if there is any overlap with the query interval
    bool overlap = intervalTree.doQueryOverlap(queryStart, queryEnd);

    // Output the result of the overlap check
    if (overlap)
    {
        cout << "Overlap exists." << endl;
    }
    else
    {
        cout << "No overlap." << endl;
    }

    // Perm a query and get the overlapping interval
    int *result = intervalTree.query(queryStart, queryEnd);

    // Output the result of the query
    if (result != nullptr)
    {
        cout << "Overlap exists. Interval: [" << result[0] << ", " << result[1] << "]" << endl;
    }
    else
    {
        cout << "No overlap." << endl;
    }

    cout << endl;
    cout << "Test Cases:" << endl;

    //     // Return True or False for each query if it is exists or not.
    // cout << "   Overlap Checks:" << endl;
    // cout << std::boolalpha << "       [2, 8]: " << intervalTree.doQueryOverlap(2, 8) << endl;
    // cout << std::boolalpha << "       [45, 50]: " << intervalTree.doQueryOverlap(45, 50) << endl;
    // cout << std::boolalpha << "       [-20, -15]: " << intervalTree.doQueryOverlap(-20, -15) << endl;
    // cout << std::boolalpha << "       [70, 90]: " << intervalTree.doQueryOverlap(70, 90) << endl;
    // cout << std::boolalpha << "       [12, 18]: " << intervalTree.doQueryOverlap(12, 18) << endl;
    // cout << endl;


    cout << "   Query:" << endl;

        // Return the node we Searching for
    result = intervalTree.query(10, 20);
    cout << "       Searching For: [10, 20] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(5, 15);
    cout << "       Searching For: [5, 15] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(7, 17);
    cout << "       Searching For: [7, 17] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(21, 25);
    cout << "       Searching For: [21, 25] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(10, 23);
    cout << "       Searching For: [10, 23] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-34, -20);
    cout << "       Searching For: [-34, -20] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(5, 10);
    cout << "       Searching For: [5, 10] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(6, 26);
    cout << "       Searching For: [6, 26] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(1, 24);
    cout << "       Searching For: [1, 24] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(1, 2);
    cout << "       Searching For: [1, 2] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(4, 13);
    cout << "       Searching For: [4, 13] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(3, 56);
    cout << "       Searching For: [3, 56] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-110, -100);
    cout << "       Searching For: [-110, -100] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(11, 21);
    cout << "       Searching For: [11, 21] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(13, 23);
    cout << "       Searching For: [13, 23] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(1, 19);
    cout << "       Searching For: [1, 19] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-5, -3);
    cout << "       Searching For: [-5, -3] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-2, -1);
    cout << "       Searching For: [-2, -1] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-6, 4);
    cout << "       Searching For: [-6, 4] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(9, 18);
    cout << "       Searching For: [9, 18] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(8, 18);
    cout << "       Searching For: [8, 18] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(3, 18);
    cout << "       Searching For: [3, 18] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-2, 20);
    cout << "       Searching For: [-2, 20] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-1, 1);
    cout << "       Searching For: [-1, 1) -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(2, 4);
    cout << "       Searching For: [2, 4] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(4, 30);
    cout << "       Searching For: [4, 30] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-4, 30);
    cout << "       Searching For: [-4, 30] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-10, -20);
    cout << "       Searching For: [-10, -20] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(11, 13);
    cout << "       Searching For: [11, 13] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(9, 13);
    cout << "       Searching For: [9, 13] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(-4, -2);
    cout << "       Searching For: [-4, -2] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(0, 1);
    cout << "       Searching For: [0,   1] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(40, 50);
    cout << "       Searching For: [40, 50] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;
    result = intervalTree.query(25, 200);
    cout << "       Searching For: [25, 200] -> " << (result ? "it exists at: [" + to_string(result[0]) + ", " + to_string(result[1]) + "]" : "Does Not Exist") << endl;

    return 0;
}
