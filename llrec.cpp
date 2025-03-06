#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot (Node*& head, Node*& smaller, Node*& larger, int pivot) {
  if(!head) {
    smaller = nullptr;
    larger = nullptr;
    return;
  }
  Node* nextNode = head->next;

  if(head->val <= pivot) {
    smaller = head;
    smaller->next = nullptr;
    llpivot(nextNode, smaller->next, larger, pivot);
  }
  else {
    larger = head;
    larger->next = nullptr;
    llpivot(nextNode, smaller, larger->next, pivot);
  }
  head = nullptr;
}