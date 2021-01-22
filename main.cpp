#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
void createFile(string fileName, int numRecord);
int deleteRecord(string fileName, int recordNo);
void displayContent(string fileName, int numRecord);

void defaultArray(int** arr, int numRecord);
void printArr(int** arr, int numRecord);

class Node
{
public:
    int* key;
    int* address;
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
        key = new int[order + 1];
        //get array of key NULL value
        for (int i = 0; i < order + 1; i++)
            key[i] = NULL;
        //create array of address
        address = new int[order + 1];
        //get array of address NULL value
        for (int i = 0; i < order + 1; i++)
            address[i] = NULL;
        // the leaf true
        isLeaf = true;
        //create array of children
        child = new Node* [order + 1];
        //no key =0
        noKey = 0;
        //get array of child = NULL
        for (int i = 0; i < order + 1; i++)
        {
            child[i] = NULL;
        }
        parent = new Node();
    }
    Node* insertInNode(int& item, int add, Node* node, int order, Node* temp)
    {
        //check if node is leaf
        //cout << item << "     11111111111111"<< isLeaf<<endl;
        if (isLeaf == true)
        {
            //cout << "temp" << item << isLeaf << endl;
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
                address[i] = address[i - 1];
                i--;
            }

            key[i] = item;
            address[i] = add;
            // increament no of key in node
            noKey = noKey + 1;
        }
        //check if node isnot leaf
        else
        {
            //cout << "temp" << item << "22222222"<< endl;
            int i = 0;
            // find its position
            //change i < order
            while (i < noKey && item > key[i] && i < order)
            {
                //cout << "333333333333333" << i << endl;
                i++;
            }
            if (i == noKey)
            {
                flag = false;
                i--;
            }
            //this is node.childe[i]
            //child[i]->parent = this;
            child[i]->insertInNode(item, add, this, order, temp);
        }
        //if node is full
        if (noKey == order + 1)
        {
            //if node is root
            if (this == temp)
            {
                //create node will be root
                Node* newNode = new Node(order);
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
        Node* right = new Node(order);

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
        int temp = node->key[check];
        int tempadd = node->address[check];
        int temp2 = node->key[order];
        int temp2add = node->address[order];
        int iC = 0;
        //
        int children = minChild;
        //n2l al key mn minkey to nokey in right
        //3
        for (int i = check + 1; i < counter; i++)
        {
            right->key[iR] = node->key[i];
            right->address[iR] = node->address[i];
            iR++;
            node->key[i] = NULL;
            node->address[i] = NULL;
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
            address[j] = address[j - 1];
            j--;
        }
        //insert the item in its position
        key[j] = temp;
        address[j] = tempadd;
        noKey = noKey + 1;

        j = noKey;
        //shift to find position of item
        while (key[j - 1] > temp2 && j != 0)
        {
            key[j] = key[j - 1];
            address[j] = address[j - 1];
            j--;
        }
        //insert the item in its position
        key[j] = temp2;
        address[j] = temp2add;
        noKey = noKey + 1;
        for (int i = 0; i < noKey - 1; i++)
        {
            if (key[i] == key[i + 1])
            {
                for (int j = i; j < noKey - 1; j++)
                {
                    key[j] = key[j + 1];
                    address[j] = address[j + 1];
                }
                noKey--;
            }
        }
        key[noKey] = NULL;
        address[noKey] = NULL;
    }
    void print(string space, int** arr, int index)
    {
        if(isLeaf){
           arr[index][0] = 0;
        }else{
           arr[index][0] = 1;
        }
        int j = 0;
        int i = 1;
        for (; j < noKey; j++,i++)
        {
            arr[index][i] = key[j];
            arr[index][++i] = address[j];
        }
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

class BTree
{
public:
    Node* root = NULL;
    int o;
    BTree(int order)
    {
        o = order;
    }

    void Insert(int item, int add)
    {
        //if tree is empty
        if (root == NULL)
        {
            root = new Node(o);
            root->isLeaf = true;
            root->key[0] = item;
            root->address[0] = add;
            root->noKey = 1;
        }
        else
        {
            //cout << "root" << root->isLeaf<<endl;
            root = root->insertInNode(item, add, root, o, root);
        }
    }

    void pre(Node* node, string space, int** arr)
    {
        static int c = 1;
        if (node == NULL)
        {
            return;
        }
        else
        {
            node->print(space, arr, c);
            arr[0][1] = c + 1;
            for (int i = 0; i < o; i++)
            {
                if (node->child[i] != NULL)
                {
                    c++;
                    pre(node->child[i], space, arr);
                }

            }
        }
    }
    void Print(int** arr)
    {
        pre(root, "", arr);
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
void insertRecord(string fileName, int key, int address, int num, BTree* btree)
{
    btree->Insert(key,address);
    int** arr = new int* [num];
    for (int i = 0; i < num; i++)
    {
        arr[i] = new int[11];
    }
    defaultArray(arr,num);
    btree->Print(arr);
    fstream indexFile;
    indexFile.open(fileName+".txt", ios::out|ios::trunc);
    indexFile.unsetf(ios::skipws);
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            indexFile.write((char*)&(arr[i][j]), sizeof(arr[i][j]));
        }
    }
    indexFile.close();
}
int searchRecord(string fileName, int key,int num, BTree* btree)
{
    int** arr = new int* [num];
    for (int i = 0; i < num; i++)
    {
        arr[i] = new int[11];
    }
    defaultArray(arr,num);
    btree->Print(arr);
    int reNum = -1;
    for(int i = 1 ; i<num; i++)
    {
        for(int j = 1 ; j< 11 ; j+=2)
        {
            cout<<arr[i][j]<<endl;
            if(arr[i][j] == key)
            {
                cout<<arr[i][j]<<endl;
                reNum = arr[i][j+1];
                return reNum;
            }
        }
    }
    return reNum;
}
int main()
{
    BTree* btree = new BTree(5);
    string fileName;
    int numRecord;

    cout << "Enter file name: ";
    cin >> fileName;

    cout << "Enter number of records: ";
    cin >> numRecord;

    createFile(fileName, numRecord);

    int choice;
    do
    {
        cout << "***********Welcome in multilevel indexing***********\n";
        cout << "1) Insert record\n";
        cout << "2) Delete record\n";
        cout << "3) Display content\n";
        cout << "4) Search record\n";
        cout << "5) Exit\n";

        cin >> choice;

        switch (choice)
        {

        case 1:
            int key, address;
            cout << "Enter key and address respectively: ";
            cin >> key >> address;
            insertRecord(fileName, key, address,numRecord, btree);
            break;
        case 2:
            int recordNo;
            cout << "Enter record number: ";
            cin >> recordNo;
            deleteRecord(fileName, recordNo);
            break;
        case 3:
            displayContent(fileName, numRecord);
            break;
        case 4:
            int keySearch;
            cout << "Enter record number: ";
            cin >> keySearch;
            int result = searchRecord(fileName, keySearch,numRecord,btree);
            if(result == -1){
                cout<<"Key "<<keySearch<<" not found ->"<<result<<endl;
            }else{
                cout<<"Key "<<keySearch<<" found at Address "<<result<<endl;
            }
            break;

        }
    }
    while (choice != 5);
    return 0;
}

void createFile(string fileName, int numRecord)
{
    int** arr = new int* [numRecord];
    for (int i = 0; i < numRecord; i++)
    {
        arr[i] = new int[11];
    }
    defaultArray(arr, numRecord);
    fstream indexFile;
    indexFile.open(fileName+".txt", ios::out);
    indexFile.unsetf(ios::skipws);
    for (int i = 0; i < numRecord; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            indexFile.write((char*)&(arr[i][j]), sizeof(arr[i][j]));
        }
    }
    indexFile.close();
}

int deleteRecord(string fileName, int recordNo)
{
    return -1;
}

void displayContent(string fileName, int numRecord)
{
    fstream indexFile1;
    int** arr2 = new int*[numRecord];
    for (int i = 0; i < numRecord; i++)
    {
        arr2[i] = new int[11];
    }
    indexFile1.open(fileName+".txt", ios::in);
    string line;
    for (int i = 0; i < numRecord; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            indexFile1.read((char*)&arr2[i][j], sizeof(arr2[i][j]));
        }
    }
    printArr(arr2, numRecord);
    indexFile1.close();
}

int searchRecord(string fileName, int recordNo)
{

    return -1;
}

void defaultArray(int** arr, int numRecord)
{
    for (int i = 0; i < numRecord; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (j == 1 && i != numRecord - 1)
            {
                arr[i][j] = (i + 1);
            }
            else
            {
                arr[i][j] = -1;
            }
        }
    }
}

void printArr(int** arr, int numRecord)
{
    for (int i = 0; i < numRecord; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}


