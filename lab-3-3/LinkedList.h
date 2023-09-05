#pragma once

struct InnerNode
{
    int data;
    InnerNode* next;
};
struct OuterNode
{
    OuterNode* nextOuterNode;
    InnerNode* firstInnerNode;
};

void menu();
int failure();
bool isOuterEmpty(OuterNode* outerHead);
bool isInnerEmty(OuterNode* currentOuterNode);
int chooseList(OuterNode* outerHead);
InnerNode* findElement(OuterNode* outerHead, int data);
InnerNode* findElementInParticularList(OuterNode* currentOuter, int data);
InnerNode* findPrevElementInParticularList(OuterNode* currentOuter, InnerNode* relativeElem);
OuterNode* findList(OuterNode* outerHead, int num);
OuterNode* findPrevList(OuterNode* outerHead, OuterNode* relativeList);
void printList(OuterNode* outerHead);
void addList(OuterNode* outerHead);
void insertListAfter(OuterNode* relativeList);
void insertListBefore(OuterNode* outerHead, OuterNode* relativeList);
void addElement(OuterNode* currentOuter, int data);
void insertElementAfter(InnerNode* relativeElement, int data);
void insertElementBefore(OuterNode* currentOuter, InnerNode* relativeElement, int data);
void deleteList(OuterNode*& outerHead, OuterNode* listToDelete);
void deleteElement(OuterNode* outerHead, int data);
void deleteElementFromParticularList(OuterNode* currentOuter, int data);
void clearList(OuterNode* outerHead);
