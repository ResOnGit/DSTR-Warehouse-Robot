#ifndef TASK4_HPP
#define TASK4_HPP

#include <string>
#include <fstream>

namespace task4_module
{
    struct Item
    {
        int id;
        std::string name;
        int x;
        int y;
    };

    struct TreeNode
    {
        Item data;
        TreeNode* left;
        TreeNode* right;
    };

    class ItemBST
    {
    private:
        TreeNode* rootByID;
        TreeNode* rootByName;

        // Helper functions
        TreeNode* searchParentNode(TreeNode* root, Item item, bool byID);
        bool insert(Item item);
        bool insertToID(Item item);
        bool insertToName(Item item);
        void remove(TreeNode* parent, TreeNode* node, bool byID);
        bool removeItem(int id, TreeNode* root);
        bool removeItem(std::string name, TreeNode* root);
        void inOrderTraversalDisplay(TreeNode* root);
        
        Item* searchByID(int id, TreeNode* node);
        Item* searchByName(std::string name, TreeNode* node);

        // File management
        void readFile();
        void updateFilePreOrder(TreeNode* node, std::ofstream& file);

        void deleteTree(TreeNode* root);
        void displayBorder();

    public:
        ItemBST();
        ~ItemBST();

        void updateFile();
        
        // Search
        Item* searchByID(int id);
        Item* searchByName(std::string name);

        // Manage Data
        bool insertItem(int id, std::string name, int x, int y);

        bool updateItemNameByID(int id, std::string newName);
        bool updateItemNameByName(std::string name, std::string newName);
        bool updateItemByID(int id, int newX, int newY);
        bool updateItemByName(std::string name, int newX, int newY);

        bool removeItemByID(int id);
        bool removeItemByName(std::string name);

        // Display sorted (in order traversal)
        void displaySortedByID();
        void displaySortedByName();
    };
}

#endif