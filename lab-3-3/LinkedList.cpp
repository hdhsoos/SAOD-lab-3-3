#include "LinkedList.h"
#include <iostream>

using namespace std;
int count_inner_lists = 0;
int cur_inner_lists = 0;

bool isOuterEmpty(OuterNode* outerHead)
{
    return outerHead->nextOuterNode == NULL;
}
bool isInnerEmty(OuterNode* currentOuterNode)
{
    return currentOuterNode->firstInnerNode->next == NULL;
}

int chooseList(OuterNode* outerHead)
{
    cout << "В списке сейчас " << cur_inner_lists << " списков" << endl;
    OuterNode* currrentList = outerHead->nextOuterNode;
    while (currrentList != NULL)
    {
        cout << "ID: " << currrentList->firstInnerNode->data << endl;
        currrentList = currrentList->nextOuterNode;
    }
    int choice;
    cin >> choice;
    return choice;
}

InnerNode* findElement(OuterNode* outerHead, int data)
{

    OuterNode* currentOuterNode = outerHead->nextOuterNode;

    while (currentOuterNode != NULL)
    {
        if (!isInnerEmty(currentOuterNode))
        {
            InnerNode* currentInnerNode = currentOuterNode->firstInnerNode->next;
            while (currentInnerNode != NULL)
            {
                if (currentInnerNode->data == data)
                {
                    return currentInnerNode;
                }
                currentInnerNode = currentInnerNode->next;
            }
        }
        currentOuterNode = currentOuterNode->nextOuterNode;
    }
    return NULL;
}

InnerNode* findElementInParticularList(OuterNode* currentOuter, int data)
{
    InnerNode* currentInnerNode = currentOuter->firstInnerNode->next;
    while (currentInnerNode != NULL)
    {

        if (currentInnerNode->data == data)
        {
            return currentInnerNode;
        }
        currentInnerNode = currentInnerNode->next;
    }
    return currentInnerNode;
}

InnerNode* findPrevElementInParticularList(OuterNode* currentOuter, InnerNode* relativeElem)
{
    InnerNode* prev = currentOuter->firstInnerNode;
    InnerNode* currentInnerNode = currentOuter->firstInnerNode->next;
    while (currentInnerNode != NULL)
    {
        if (currentInnerNode == relativeElem)
        {
            break;
        }
        prev = currentInnerNode;
        currentInnerNode = currentInnerNode->next;
    }
    return prev;
}

OuterNode* findList(OuterNode* outerHead, int num)
{
    OuterNode* currentOuterNode = outerHead->nextOuterNode;
    while (currentOuterNode != NULL)
    {
        if (currentOuterNode->firstInnerNode->data == num)
        {
            break;
        }
        currentOuterNode = currentOuterNode->nextOuterNode;

    }
    return currentOuterNode;
}

OuterNode* findPrevList(OuterNode* outerHead, OuterNode* relativeList)
{
    OuterNode* currentNode = outerHead;
    while (currentNode->nextOuterNode != relativeList)
    {
        currentNode = currentNode->nextOuterNode;
    }
    return currentNode;
}

void printList(OuterNode* outerHead)
{
    if (!isOuterEmpty(outerHead))
    {
        OuterNode* currentOuterNode = outerHead->nextOuterNode;

        while (currentOuterNode != NULL)
        {
            int id = currentOuterNode->firstInnerNode->data;
            cout << "ID: " << id << "" << endl;
            if (!isInnerEmty(currentOuterNode))
            {
                InnerNode* currentInnerNode = currentOuterNode->firstInnerNode->next;
                while (currentInnerNode != NULL)
                {
                    cout << currentInnerNode->data << " ";
                    currentInnerNode = currentInnerNode->next;
                }
                cout << endl;
            }
            else
            {
                cout << "Список с id "  << id << " пуст" << endl;
            }
            currentOuterNode = currentOuterNode->nextOuterNode;

        }
    }
}

void addList(OuterNode* outerHead)
{
    OuterNode* newOuterNode = new OuterNode;
    outerHead->nextOuterNode = newOuterNode;
    newOuterNode->firstInnerNode = new InnerNode;
    newOuterNode->firstInnerNode->next = NULL;
    newOuterNode->firstInnerNode->data = count_inner_lists++;
    newOuterNode->nextOuterNode = NULL;
    cur_inner_lists += 1;
}

void insertListAfter(OuterNode* relativeList)
{
    OuterNode* newList = new OuterNode;
    newList->nextOuterNode = relativeList->nextOuterNode;
    relativeList->nextOuterNode = newList;
    newList->firstInnerNode = new InnerNode;
    newList->firstInnerNode->next = NULL;
    newList->firstInnerNode->data = count_inner_lists++;
    cur_inner_lists += 1;
}

void insertListBefore(OuterNode* outerHead, OuterNode* relativeList)
{
    OuterNode* newList = new OuterNode;
    OuterNode* prevList = findPrevList(outerHead, relativeList);
    newList->nextOuterNode = relativeList;
    prevList->nextOuterNode = newList;
    newList->firstInnerNode = new InnerNode;
    newList->firstInnerNode->next = NULL;
    newList->firstInnerNode->data = count_inner_lists++;
    cur_inner_lists += 1;
}

void addElement(OuterNode* currentOuter, int data)
{

    InnerNode* newInnerNode = new InnerNode;
    newInnerNode->data = data;
    newInnerNode->next = NULL;
    InnerNode* currentInnerNode = currentOuter->firstInnerNode;
    while (currentInnerNode->next != NULL)
    {
        currentInnerNode = currentInnerNode->next;
    }
    currentInnerNode->next = newInnerNode;
}

void insertElementAfter(InnerNode* relativeElement, int data)
{
    InnerNode* newElement = new InnerNode;
    newElement->next = relativeElement->next;
    relativeElement->next = newElement;
    newElement->data = data;
}

void insertElementBefore(OuterNode* currentOuter, InnerNode* relativeElement, int data)
{
    InnerNode* newElement = new InnerNode;
    InnerNode* prevElement = findPrevElementInParticularList(currentOuter, relativeElement);
    newElement->next = relativeElement;
    prevElement->next = newElement;
    newElement->data = data;
}

void deleteList(OuterNode*& outerHead, OuterNode* listToDelete)
{
    OuterNode* prev = findPrevList(outerHead, listToDelete);
    prev->nextOuterNode = listToDelete->nextOuterNode;

    InnerNode* currentInnerNode = listToDelete->firstInnerNode->next;
    InnerNode* temp;
    while (currentInnerNode != NULL)
    {
        temp = currentInnerNode;
        currentInnerNode = currentInnerNode->next;
        delete temp;
    }
    delete listToDelete->firstInnerNode;
    delete listToDelete;
    cur_inner_lists -= 1;
}

void deleteElement(OuterNode* outerHead, int data)
{
    int flag = false;
    OuterNode* currentList = outerHead->nextOuterNode;
    while (currentList != NULL)
    {
        if (flag)
        {
            break;
        }
        InnerNode* prev = currentList->firstInnerNode;
        InnerNode* currentElement = currentList->firstInnerNode->next;
        while (currentElement != NULL)
        {
            if (currentElement->data == data)
            {
                flag = true;
                prev->next = currentElement->next;
                delete currentElement;
                break;
            }
            prev = currentElement;
            currentElement = currentElement->next;
        }
        currentList = currentList->nextOuterNode;
    }
}

void deleteElementFromParticularList(OuterNode* currentOuter, int data)
{
    bool flag = false;
    InnerNode* prev = currentOuter->firstInnerNode;
    InnerNode* currentElement = currentOuter->firstInnerNode->next;
    while (currentElement != NULL)
    {
        if (currentElement->data == data)
        {
            flag = true;
            prev->next = currentElement->next;
            delete currentElement;
            break;
        }
        prev = currentElement;
        currentElement = currentElement->next;
    }
    if (!flag)
    {
        cout << "Такого элемента в списке нет" << endl;
    }

}

void clearList(OuterNode* outerHead)
{
    OuterNode* currentOuter;
    InnerNode* currentInner;
    while (outerHead != NULL)
    {
        currentOuter = outerHead;
        while (currentOuter->firstInnerNode != NULL)
        {
            currentInner = currentOuter->firstInnerNode;
            currentOuter->firstInnerNode = currentOuter->firstInnerNode->next;
            delete currentInner;
        }

        outerHead = currentOuter->nextOuterNode;
        delete currentOuter;
    }
    cur_inner_lists = 0;
}