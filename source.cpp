// CS221L Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int alphabets = 26;

class List
{
    struct Node
    {
        string data;
        Node* next;
    };
    Node* headptr;

public:
    List()
    {
        headptr = NULL;
    }

    void addNodeAtEnd(string value)
    {
        Node* temp = new Node();
        temp->data = value;
        temp->next = NULL;
        if (headptr == NULL)
        {
            headptr = temp;
            return;
        }

        Node* temp2 = headptr;
        while (temp2->next != NULL)
        {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }
    void deleteNodeAtBeginning()
    {
        Node* temp = headptr;
        headptr = temp->next;
        delete temp;
    }
    void printList()
    {
        Node* temp = headptr;
        cout << "The list of incorrect words is : ";
        while (temp != NULL)
        {
            if (temp->next == NULL)
                cout << temp->data;
            else
                cout << temp->data << ", ";

            temp = temp->next;
        }
        cout << '\n';
    }
    void deleteNodeAtEnd()
    {
        Node* temp = headptr;
        int count = 0;
        while (temp->next != NULL)
        {
            temp = temp->next;
            count++;
        }
        Node* temp2 = headptr;
        for (int i = 0; i < count - 1; i++)
        {
            temp2 = temp2->next;
        }
        temp2->next = NULL;
        delete temp;
    }
};

struct trienode
{

    trienode* children[alphabets];

    bool isendofword;
};

struct trienode* getnode(void)
{

    trienode* newnode = new trienode;
    newnode->isendofword = false;

    for (int i = 0; i < alphabets; i++)
    {
        newnode->children[i] = NULL;
    }

    return newnode;
}

void insert(trienode* root, string key)
{

    trienode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            node->children[index] = getnode();

        node = node->children[index];
    }
    node->isendofword = true;
}

bool search(trienode* root, string key)
{
    struct trienode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return false;

        node = node->children[index];
    }

    return (node->isendofword);
}

int main()
{

    struct trienode* root = getnode();
    List l1;

    { // Construct trie
        fstream reading;
        reading.open("listt.txt", ios::in);
        if (reading.is_open())
        {
            string text;
            while (getline(reading, text))
            {
                insert(root, text);
            }
            cout << "trie created \n \n"
                << endl;
        }
    }

    string key;

    // cout << "Enter a string ";
    // cin >> key;
    fstream getting;
    getting.open("input.txt", ios::in);
    if (getting.is_open())
    {

        string key;

        while (getline(getting, key, ' '))
        {
            cout << "key is " << key << endl;
            string x;
            for (int i = 0; i != key.length(); i++)
            {

                if (key[i] == '.' || key[i] == '/' || key[i] == ',' || key[i] == ':' || key[i] == ';' || key[i] == '-' || key[i] == '_' || key[i] == '!')
                {
                    // nothing happen here
                }
                else
                {
                    x += key[i];
                }
            }

            if (search(root, x))
            {

                cout << x << " :: spellings are correct and its a real word" << endl;

                // cout
                cout << "\n";
            }
            else
            {
                cout << key << " ::spelling not correct or not a real word" << endl;
                l1.addNodeAtEnd(key);
                cout << "Word added to a list of incorrect words." << endl;
                cout << endl;
            }
        }
    }
    l1.printList();
}
