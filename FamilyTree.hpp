#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace family
{
class Node
{

private:
    string m_name;
    Node *m_father;
    Node *m_mother;
    int m_level;
    string m_relation;

public:
    Node(string name) : m_name(name), m_father(NULL), m_mother(NULL), m_level(0), m_relation("me"){};
    void setFather(Node *father);
    void setMother(Node *mother);
    void setLevel(int level);
    void setRe(string gender);
    string getRe();
    string getName();
    Node *getFather();
    Node *getMother();
    int getLevel();
};

class Tree
{
private:
    Node *root;

public:
    Tree(string name);
    Node *findChild(Node *root, string child);
    Node *findRelation(Node *root, string relation);
    Tree &addFather(string child, string father);
    Tree &addMother(string child, string mother);
    string relation(string name);
    string find(string relation);
    Node *findByParent(Node *root, string child, int &gender);
    void display();
    void display(Node *r);
    void remove(string name);
    void remove(Node *remove_node);
};
}; // namespace family
