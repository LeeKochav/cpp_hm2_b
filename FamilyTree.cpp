#include "FamilyTree.hpp"
#include <stdexcept>

using namespace family;

void Node::setFather(Node *father)
{
    this->m_father = father;
}
void Node::setMother(Node *mother)
{
    this->m_mother = mother;
}
Node *Node::getFather()
{
    return this->m_father;
}
Node *Node::getMother()
{
    return this->m_mother;
}
void Node::setLevel(int level)
{
    this->m_level = level;
}
int Node::getLevel()
{
    return this->m_level;
}
string Node::getName()
{
    return this->m_name;
}
string Node::getRe()
{
    return this->m_relation;
}
void Node::setRe(string gender)
{
    string res_relation = "";
    if (gender == "Male")
    {
        res_relation = "father";
    }
    else if (gender == "Female")
    {
        res_relation = "mother";
    }
    if (this->getLevel() == 1)
    {
        this->m_relation = res_relation;
    }
    else if (this->getLevel() == 2)
    {
        this->m_relation = "grand" + res_relation;
    }
    else
    {
        res_relation = "grand" + res_relation;
        string concat_great = "";
        int tmp = this->getLevel() - 2;
        for (int i = 0; i < tmp; i++)
        {
            concat_great += "great-";
        }
        this->m_relation = concat_great + res_relation;
    }
}
Tree::Tree(string name)
{
    root = new Node(name);
    root->setLevel(0);
};

Node *Tree::findChild(Node *root, string child)
{
    if (root == NULL)
        return NULL;

    if (root->getName() == child)
        return root;

    return findChild(root->getFather(), child) ?: findChild(root->getMother(), child);
}

Node *Tree::findRelation(Node *root, string relation)
{
    if (root == NULL)
        return NULL;

    if (root->getRe() == relation)
        return root;

    return findRelation(root->getFather(), relation) ?: findRelation(root->getMother(), relation);
}

Tree &Tree::addFather(string child, string father)
{
    string gender = "Male";
    Node *f_child = findChild(root, child);

    if (f_child == NULL)
    {
        throw runtime_error("Child is not in the tree");
    }
    else if (f_child->getFather() != NULL)
    {
        throw runtime_error("Child already has a father");
    }
    Node *new_father = new Node(father);
    new_father->setLevel(f_child->getLevel() + 1);
    new_father->setRe(gender);
    f_child->setFather(new_father);
    return *this;
};

Tree &Tree::addMother(string child, string mother)
{
    string gender = "Female";
    Node *f_child = findChild(root, child);

    if (f_child == NULL)
    {
        throw runtime_error("Child is not in the tree");
    }
    else if (f_child->getMother() != NULL)
    {
        throw runtime_error("Child already has a mother");
    }
    Node *new_mother = new Node(mother);
    new_mother->setLevel(f_child->getLevel() + 1);
    new_mother->setRe(gender);
    f_child->setMother(new_mother);
    return *this;
};

string Tree::relation(string name)
{
    Node *res = findChild(root, name);
    if (res == NULL)
    {
        return "unrelated";
    }
    else
    {
        return res->getRe();
    }
}
string Tree::find(string relation)
{
    Node *res = findRelation(root, relation);
    if (res == NULL)
    {
        throw runtime_error("Relation was not found");
    }
    else
    {
        return res->getName();
    }
};

void Tree::display(Node *r)
{
    if (r == NULL)
        return;
    cout << r->getName() << ",";
    display(r->getFather());
    display(r->getMother());
}
void Tree::display()
{
    display(root);
    cout << endl;
};

void Tree::remove(Node *remove_node)
{

    if (remove_node == NULL)
        return;

    remove(remove_node->getFather());
    remove(remove_node->getMother());

    delete remove_node;
}

void Tree::remove(string name)
{
    Node *rem = findChild(root, name);

    if (rem == NULL)
    {
        throw runtime_error("Child is not in the tree");
    }
    if (rem->getLevel() == 0)
    {
        throw runtime_error("Cannot delete root");
    }
    int child_gender = -1;
    Node *children = findByParent(root, rem->getName(), child_gender);
    if (child_gender == 0)
        children->setFather(NULL);
    if (child_gender == 1)
        children->setMother(NULL);
    remove(rem);
}

Node *Tree::findByParent(Node *root, string child, int &gender)
{
    if (root == NULL)
        return NULL;

    if (root->getFather() != NULL && root->getFather()->getName() == child)
    {
        gender = 0;
        return root;
    }

    else if (root->getMother() != NULL && root->getMother()->getName() == child)
    {
        gender = 1;
        return root;
    }

    return findByParent(root->getFather(), child, gender) ?: findByParent(root->getMother(), child, gender);
}
