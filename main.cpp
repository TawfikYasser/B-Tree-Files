#include<iostream>
#include<vector>
#include <string>
#include <fstream>
using namespace std;
void createFile(string fileName, int numRecord);
int insertRecord(string fileName, int key, int address);
int deleteRecord (string fileName, int recordNo);
void displayContent(string fileName);
int searchRecord (string fileName, int recordNo);

template <class T>
class Node
{
public:
    T* key;
    Node** child;
    bool isLeaf;
    int noKey;
    Node* parent;
    bool flag = true;
    Node()
    {

    }
    Node(int order)
    {
        //create array of key
        key = new T[order + 1];
        //get array of key NULL value
        for (int i = 0; i < order + 1; i++)
            key[i] = NULL;
        // the leaf true
        isLeaf = true;
        //create array of children
        child = new Node<T> *[order + 1];
        //no key =0
        noKey = 0;
        //get array of child = NULL
        for (int i = 0; i < order + 1; i++)
        {
            child[i] = NULL;
        }
        parent = new Node<T>();
    }
    Node* insertInNode(T& item, Node* node, int order, Node* temp)
    {
        //check if node is leaf
        cout << item << "     11111111111111"<< isLeaf<<endl;
        if (isLeaf == true)
        {
            cout << "temp" << item << isLeaf << endl;
            int i = order + 1;
            //while key han value == NULL to find
            while (key[i - 1] == NULL)
            {
                i--;
            }
            //insert value in here position
            while (key[i - 1] > item && i != 0)
            {
                key[i] = key[i - 1];
                i--;
            }

            key[i] = item;

            // increament no of key in node
            noKey = noKey + 1;
        }
        //check if node isnot leaf
        else
        {
            cout << "temp" << item << "22222222"<< endl;
            int i = 0;
            // find its position
            //change i < order
            while (i < noKey && item > key[i] && i < order)
            {
                cout << "333333333333333" << i << endl;
                i++;
            }
            if (i == noKey)
            {
                flag = false;
                i--;
            }
            //this is node.childe[i]
            child[i]->parent = this;
            child[i]->insertInNode(item, this, order, temp);
        }
        //if node is full
        if (noKey == order + 1)
        {
            //if node is root
            if (this == temp)
            {
                //create node will be root
                Node<T>* newNode = new Node<T>(order);
                // the node will be not leaf becouse it has child
                newNode->isLeaf = false;
                newNode->child[0] = this;
                //split root
                newNode->split(this, order);
                return newNode;
            }
            else
            {
                //split w prf3 almo4kla llroot
                node->split(this, order);
            }

        }
        if (flag == false)
        {
            //   cout << ">>>>>>>>>>>>>>>" << item << endl << ">>>>>>>>>>>>>>>>>" << temp->noKey - 1;

        }
        flag = true;
        return temp;
    }
    void split(Node* node, int order)
    {
        //crear node will be wight of node
        Node<T>* right = new Node<T>(order);

        int minChild;
        if (order % 2 == 0)
        {
            minChild = float(order) / 2;
        }
        else
        {
            //3
            minChild = order / 2;
            minChild++;
        }
        int iR = 0;
        // 2
        int check = (order) / 2;

        int counter = node->noKey;
        T temp = node->key[check];
        T temp2 = node->key[order];
        int iC = 0;
        //
        int children = minChild;
        //n2l al key mn minkey to nokey in right
        //3
        for (int i = check + 1; i < counter; i++)
        {
            right->key[iR] = node->key[i];
            iR++;
            node->key[i] = NULL;
            node->noKey = (node->noKey) - 1;
            right->noKey = (right->noKey) + 1;
        }
        //if node not leaf
        if (node->isLeaf == false)
        {
            //n2l childred from node[min child]
            for (int i = children; i <= order; i++)
            {
                right->child[iC] = node->child[i];
                iC++;
                //to delet tkrar null
                node->child[i] = NULL;
            }
            //
            right->isLeaf = node->isLeaf;
        }
        // mmkn feha mshkla
        int k = order - 1;
        while (child[k] != node)
        {
            child[k + 1] = child[k];
            k--;
        }
        //child[order - 1] = NULL;
        child[k + 1] = right;
        //right = NULL;
        //int j = order - 1;
        int j = noKey;
        //while (key[j - 1] == NULL && j != 0)
        //{
        //  j--;
        //}
        //shift to find position of item
        while (key[j - 1] > temp && j != 0)
        {
            key[j] = key[j - 1];
            j--;
        }
        //insert the item in its position
        key[j] = temp;
        noKey = noKey + 1;

        j = noKey;
        //shift to find position of item
        while (key[j - 1] > temp2 && j != 0)
        {
            key[j] = key[j - 1];
            j--;
        }
        //insert the item in its position
        key[j] = temp2;
        noKey = noKey + 1;
        for(int i =0 ; i<noKey-1; i++)
        {
            if (key[i] == key[i + 1])
            {
                for (int j = i; j < noKey - 1; j++)
                {
                    key[j] = key[j+1];
                }
                noKey--;
            }
        }
    }
    void print(string space)
    {
        cout << space;
        for (int i = 0; i < noKey; i++)
        {
            if (i + 1 == noKey)
                cout << key[i];
            else
                cout << key[i] << ",";

        }
        cout << endl;
    }
    void printl(Node* temp, int l)
    {
        if (l > 1 && isLeaf)
        {
            return;
        }
        else if (l == 1)
        {
            for (int i = 0; i < noKey; i++)
            {
                cout << key[i] << " ";
            }
        }

        else
        {
            for (int i = 0; i <= noKey; i++)
            {
                child[i]->printl(temp, l - 1);
            }
        }

    }
    void height(Node* temp, int h, int& result)
    {
        if (isLeaf)
        {
            result = h;
            return;
        }
        child[0]->height(temp, h + 1, result);
    }
};
template <class T, int order>
class BTree
{
public:
    Node<T>* root = NULL;
    int o = order;
    void Insert(T item)
    {
        //if tree is empty
        if (root == NULL)
        {
            root = new Node<T>(o);
            root->isLeaf = true;
            root->key[0] = item;
            root->noKey = 1;
        }
        else
        {
            cout << "root" << root->isLeaf<<endl;
            root = root->insertInNode(item, root, o, root);
        }
    }

    void pre(Node<T>* node, string space)
    {
        if (node == NULL)
            return;
        else
        {
            node->print(space);
            space += "  ";
            for (int i = 0; i < order; i++)
            {
                if (node->child[i] != NULL)
                    pre(node->child[i], space);
            }
        }
    }
    void Print()
    {
        pre(root, "");
        cout << endl;
    }

    void printlevel()
    {
        int h = height();
        for (int i = 1; i <= h; i++)
        {
            root->printl(root, i);
            cout << endl;
        }
    }

    int height()
    {
        int result;
        root->height(root, 1, result);
        return result;
    }
    void clear()
    {
        root = NULL;
    }
};
int main()
{

    string fileName;
    int numRecord;

    cout << "Enter file name: ";
    cin >> fileName;

    cout << "Enter number of records: ";
    cin >> numRecord;

    createFile(fileName, numRecord);

    int choice;

    cout << "***********Welcome in multilevel indexing***********\n";
    cout << "1) Insert record\n";
    cout << "2) Delete record\n";
    cout << "3) Display content\n";
    cout << "4) Search record\n";

    cin >> choice;

    switch(choice)
    {

    case 1:
        int key, address;

        cout << "Enter key and address respectively: ";
        cin >> key >> address;
        insertRecord(fileName, key, address);
        break;
    case 2:
        int recordNo;

        cout << "Enter record number: ";
        cin >> recordNo;

        deleteRecord(fileName, recordNo);
        break;
    case 3:
        displayContent(fileName);
        break;
    case 4:
        int recordID;

        cout << "Enter record number: ";
        cin >> recordID;

        searchRecord(fileName, recordNo);
        break;

    }

    // Construct a BTree of order 3, which stores int data
    BTree<int,5> t1;
    t1.Insert(3);
    t1.Insert(7);
    t1.Insert(10);
    t1.Insert(24);
    t1.Insert(14);
    t1.Insert(19);
    t1.Insert(30);
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(15);
    t1.Insert(2);

    t1.Print(); // Should output the following on the screen:
    /*
    1,4
      0
      2,3
      5
    */

    return 0;
}

void createFile(string fileName, int numRecord)
{

}

int insertRecord(string fileName, int key, int address)
{

}

int deleteRecord (string fileName, int recordNo)
{

}

void displayContent(string fileName)
{

}

int searchRecord (string fileName, int recordNo)
{

}

