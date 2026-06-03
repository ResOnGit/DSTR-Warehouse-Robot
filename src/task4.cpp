#include "task4.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

namespace task4_module
{
    ItemBST::ItemBST()
    {
        // Initialize the tree and get data from file
        rootByID = NULL;
        rootByName = NULL;
        readFile();
    }

    ItemBST::~ItemBST()
    {
        // Delete the trees
        deleteTree(rootByID);
        deleteTree(rootByName);
    }

    void ItemBST::deleteTree(TreeNode* root)
    {
        // Delete until reaching the end of the tree
        if (root == NULL)
            return;

        // Delete left and right root as the new subtree root
        deleteTree(root -> left);
        deleteTree(root -> right);

        // Delete the current root
        delete root;
    }

    void ItemBST::readFile()
    {
        // Create file object
        ifstream file("item.csv");
        
        // Check if file can be openned
        if (!file.is_open())
        {
            cout << "Error in opening file: item.csv" << endl;
            return;
        }

        // Loop through each line
        string line;
        getline(file, line); // skip the header
        while (getline(file, line))
        {
            // Initialize
            stringstream ss(line);
            string datum;

            // Input the value into data
            Item tmp;
            getline(ss, datum, ',');
            tmp.id = stoi(datum);
            getline(ss, datum, ',');
            tmp.name = datum;
            getline(ss, datum, ',');
            tmp.x = stoi(datum);
            getline(ss, datum, ',');
            tmp.y = stoi(datum);

            // Insert the data into the tree
            insert(tmp);
        }
    }

    void ItemBST::updateFile()
    {
        // Create file object
        ofstream file("item.csv");
        
        // Check if file can be openned
        if (!file.is_open())
        {
            cout << "Error in opening file: items.csv" << endl;
            return;
        }

        // Write the header
        file << "ItemID,ItemName,X,Y\n";

        // Write the data in pre-order traversal
        updateFilePreOrder(rootByID, file);
    }

    void ItemBST::updateFilePreOrder(TreeNode* node, ofstream& file)
    {
        // Using pre-order to have relatively the same
        // root -> left -> right
        if (node == NULL)
            return;

        // Write the current node data
        file << to_string(node -> data.id) << ","
             << node -> data.name << ","
             << to_string(node -> data.x) << ","
             << to_string(node -> data.y)
              << "\n";

        // Write the left and right subtree
        updateFilePreOrder(node -> left, file);
        updateFilePreOrder(node -> right, file);
    }

    bool ItemBST::insert(Item item)
    {
        // Create a new leaf node
        TreeNode* newNodeByID = new TreeNode;
        newNodeByID -> data = item;
        newNodeByID -> left = NULL;
        newNodeByID -> right = NULL;

        TreeNode* newNodeByName = new TreeNode;
        newNodeByName -> data = item;
        newNodeByName -> left = NULL;
        newNodeByName -> right = NULL;

        // Insert if root is empty
        if (rootByID == NULL && rootByName == NULL)
        {
            rootByID = newNodeByID;
            rootByName = newNodeByName;
            return true;
        }

        // Search the parent node
        // By ID
        TreeNode* parentByID = searchParentNode(rootByID, item, true);
        
        // Check for duplicate ID
        if (parentByID == NULL)
        {
            delete newNodeByID;
            delete newNodeByName;
            return false;
        }

        // By Name
        TreeNode* parentByName = searchParentNode(rootByName, item, false);

        // Check for duplicate Name
        if (parentByName == NULL)
        {
            delete newNodeByID;
            delete newNodeByName;
            return false;
        }

        // Insert item
        // By ID
        if (item.id < (parentByID -> data).id)
            parentByID -> left = newNodeByID;
        else
            parentByID -> right = newNodeByID;

        // By Name
        if (item.name < (parentByName -> data).name)
            parentByName -> left = newNodeByName;
        else
            parentByName -> right = newNodeByName;

        // Update size
        return true;
    }

    bool ItemBST::insertToID(Item item)
    {
        // Create a new leaf node
        TreeNode* newNodeByID = new TreeNode;
        newNodeByID -> data = item;
        newNodeByID -> left = NULL;
        newNodeByID -> right = NULL;

        // Insert if root is empty
        if (rootByID == NULL && rootByName == NULL)
        {
            rootByID = newNodeByID;
            return true;
        }

        // Search the parent node
        TreeNode* parentByID = searchParentNode(rootByID, item, true);
        
        // Check for duplicate ID
        if (parentByID == NULL)
        {
            delete newNodeByID;
            return false;
        }

        // Insert item
        if (item.id < (parentByID -> data).id)
            parentByID -> left = newNodeByID;
        else
            parentByID -> right = newNodeByID;

        return true;
    }

    bool ItemBST::insertToName(Item item)
    {
        // Create a new leaf node
        TreeNode* newNodeByName = new TreeNode;
        newNodeByName -> data = item;
        newNodeByName -> left = NULL;
        newNodeByName -> right = NULL;

        // Insert if root is empty
        if (rootByName == NULL)
        {
            rootByName = newNodeByName;
            return true;
        }

        // Search the parent node
        TreeNode* parentByName = searchParentNode(rootByName, item, false);

        // Check for duplicate Name
        if (parentByName == NULL)
        {
            delete newNodeByName;
            return false;
        }

        // Insert item
        if (item.name < (parentByName -> data).name)
            parentByName -> left = newNodeByName;
        else
            parentByName -> right = newNodeByName;

        return true;
    }

    TreeNode* ItemBST::searchParentNode(TreeNode* root, Item item, bool byID)
    {
        // Initialize
        TreeNode* parent = NULL;
        TreeNode* node = root;

        // Traverse to the intended leaf node as parent
        while (node != NULL)
        {
            parent = node;

            if (byID)
            {
                // Check for duplicate ID
                if (item.id == (node -> data).id)
                    return NULL;

                // Traverse left or right based on current ID
                if (item.id < (node -> data).id)
                    node = node -> left;
                else
                    node = node -> right;
            }
            else
            {
                // Check for duplicate Name
                if (item.name == (node -> data).name)
                    return NULL;

                // Traverse left or right based on current Name
                if (item.name < (node -> data).name)
                    node = node -> left;
                else
                    node = node -> right;
            }
        }

        // Found the parent node
        return parent;
    }

    void ItemBST::inOrderTraversalDisplay(TreeNode* root)
    {
        // Using in-order traversal to display the data in sorted order
        // left -> root -> right
        if (root == NULL)
            return;

        inOrderTraversalDisplay(root -> left);

        // Display the data
        cout << " | " << setw(7) << (root -> data).id 
             << " | " << setw(30) << (root -> data).name 
             << " | " << setw(5) << (root -> data).x
             << " | " << setw(5) << (root -> data).y
             << " |" << endl;
        
        inOrderTraversalDisplay(root -> right);
    }

    void ItemBST::remove(TreeNode* parent, TreeNode* node, bool byID)
    {
        // Case 1: Node is a leaf
        if (node -> left == NULL && node -> right == NULL)
        {
            // Node is the root
            if (parent == NULL)
            {
                if (byID)
                    rootByID = NULL;
                else
                    rootByName = NULL;
            }

            // Remove reference to the node from parent
            else if (parent -> left == node)
                parent -> left = NULL;
            else
                parent -> right = NULL;

            // Delete the node
            delete node;
            return;
        }

        // Case 2: Node has no left subtree
        if (node -> left == NULL)
        {
            // Node is the root
            if (parent == NULL)
            {
                if (byID)
                    rootByID = node -> right;
                else
                    rootByName = node -> right;
            }

            // Change the reference from the node to the right child
            else if (parent -> left == node)
                parent -> left = node -> right;
            else
                parent -> right = node -> right;

            // Delete the node
            delete node;
            return;
        }

        // Case 3: Node has no right subtree
        if (node -> right == NULL)
        {
            // Node is the root
            if (parent == NULL)
            {
                if (byID)
                    rootByID = node -> left;
                else
                    rootByName = node -> left;
            }

            // Change the reference from the node to the left child
            else if (parent -> left == node)
                parent -> left = node -> left;
            else
                parent -> right = node -> left;

            // Delete the node
            delete node;
            return;
        }

        // Case 4: Node has left and right subtree
        // Find the successor node
        TreeNode* successorParent = node;
        TreeNode* successor = node -> right;
        // Traverse to the leftmost node in the right subtree
        while (successor -> left != NULL)
        {
            successorParent = successor;
            successor = successor -> left;
        }

        // Change the data of the node to successor's data
        node -> data = successor -> data;

        // Change the reference from the successor's parent to successor's right child
        if (successorParent -> left == successor)
            successorParent -> left = successor -> right;
        else
            successorParent -> right = successor -> right;

        // Delete the original data of the node and the successor node
        delete successor;
    }

    Item* ItemBST::searchByID(int id)
    {
        return searchByID(id, rootByID);
    }

    Item* ItemBST::searchByName(string name)
    {
        return searchByName(name, rootByName);
    }

    Item* ItemBST::searchByID(int id, TreeNode* node)
    {
        if (node == NULL)
            return NULL;

        if (id == (node -> data).id)
            return &(node -> data);

        if (id < (node -> data).id)
            return searchByID(id, node -> left);
        else
            return searchByID(id, node -> right);
    }

    Item* ItemBST::searchByName(string name, TreeNode* node)
    {
        if (node == NULL)
            return NULL;

        if (name == (node -> data).name)
            return &(node -> data);

        if (name < (node -> data).name)
            return searchByName(name, node -> left);
        else
            return searchByName(name, node -> right);
    }

    bool ItemBST::insertItem(int id, string name, int x, int y)
    {
        Item item;
        item.id = id;
        item.name = name;
        item.x = x;
        item.y = y;

        return insert(item);
    }

    bool ItemBST::updateItemNameByID(int id, string newName)
    {
        // Search for item that matches the id
        Item* itemByID = searchByID(id);
        if (itemByID == NULL)
        {
            cout << "ID is not found" << endl;
            return false;
        }

        // the name is the same as new name
        if (itemByID -> name == newName)
        {
            return true;
        }

        // try to insert new name
        Item item;
        item.id = itemByID -> id;
        item.name = newName;
        item.x = itemByID -> x;
        item.y = itemByID -> y;
        
        // Name must be unique
        if (!insertToName(item))
        {
            cout << "Name must be unique" << endl;
            return false;
        }

        // Check in case error (debugging purpose)
        if (!removeItem(itemByID -> name, rootByName))
        {
            cout << "Error: Name is not found" << endl;
            return false;
        }

        // update the name
        itemByID -> name = newName;
        return true;
    }

    bool ItemBST::updateItemNameByName(string name, string newName)
    {
        // Search for item that matches the name
        Item* itemByName = searchByName(name);
        if (itemByName == NULL)
        {
            cout << "Name is not found" << endl;
            return false;
        }

        // Search for item that matches the id
        Item* itemByID = searchByID(itemByName -> id);
        if (itemByID == NULL)
        {
            cout << "ID is not found" << endl;
            return false;
        }

        // update the name
        itemByName -> name = newName;
        itemByID -> name = newName;
        return true;
    }

    bool ItemBST::updateItemByID(int id, int newX, int newY)
    {
        Item* item = searchByID(id);
        if (item == NULL)
        {
            return false;
        }

        Item* item2 = searchByName(item -> name);

        item -> x = newX;
        item -> y = newY;
        item2 -> x = newX;
        item2 -> y = newY;
        return true;
    }

    bool ItemBST::updateItemByName(string name, int newX, int newY)
    {
        Item* item = searchByName(name);
        if (item == NULL)
        {
            return false;
        }

        Item* item2 = searchByID(item -> id);

        item -> x = newX;
        item -> y = newY;
        item2 -> x = newX;
        item2 -> y = newY;
        return true;
    }
    
    bool ItemBST::removeItemByID(int id)
    {
        Item* item = searchByID(id);

        if (item == NULL)
        {
            return false;
        }

        removeItem(item -> name, rootByName);
        removeItem(id, rootByID);
        return true;
    }

    bool ItemBST::removeItemByName(std::string name)
    {
        Item* item = searchByName(name);

        if (item == NULL)
        {
            return false;
        }

        removeItem(item -> id, rootByID);
        removeItem(name, rootByName);
        return true;
    }

    bool ItemBST::removeItem(int id, TreeNode* root)
    {
        TreeNode* parent = NULL;
        TreeNode* node = root;
        
        while (node != NULL)
        {
            if ((node -> data).id == id)
            {
                remove(parent, node, true);
                return true;
            }

            parent = node;
            if (id < (node -> data).id)
                node = node -> left;
            else
                node = node -> right;
        }

        return false;
    }

    bool ItemBST::removeItem(string name, TreeNode* root)
    {
        TreeNode* parent = NULL;
        TreeNode* node = root;
        
        while (node != NULL)
        {
            if ((node -> data).name == name)
            {
                remove(parent, node, false);
                return true;
            }

            parent = node;
            if (name < (node -> data).name)
                node = node -> left;
            else
                node = node -> right;
        }

        return false;
    }

    void ItemBST::displaySortedByID()
    {
        displayBorder();
        cout << " | " << setw(7) << "ID"
             << " | " << setw(30) << "Name"
             << " | " << setw(5) << "X"
             << " | " << setw(5) << "Y"
             << " | " << endl;
        displayBorder();
        inOrderTraversalDisplay(rootByID);
        displayBorder();
    }

    void ItemBST::displaySortedByName()
    {
        displayBorder();
        cout << " | " << setw(7) << "ID"
             << " | " << setw(30) << "Name"
             << " | " << setw(5) << "X"
             << " | " << setw(5) << "Y"
             << " | " << endl;
        displayBorder();
        inOrderTraversalDisplay(rootByName);
        displayBorder();
    }

    void ItemBST::displayBorder()
    {
        cout << "-----------------------------------------------------------------" << endl;
    }

}