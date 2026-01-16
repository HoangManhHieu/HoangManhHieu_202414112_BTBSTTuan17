#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node{
    int index;        
    char title[100];   
    struct Node *left;
    struct Node *right;
}Node;
Node* taoNode(int index, char *title) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->index = index;
    strcpy(newNode->title, title);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
int soSanh2Cay(Node *a, Node *b) {
    if (a == NULL && b == NULL) 
        return 1;
    if (a != NULL && b != NULL) {
        return (
            (a->index == b->index) &&           
            (strcmp(a->title, b->title) == 0) &&   
            soSanh2Cay(a->left, b->left) &&     
            soSanh2Cay(a->right, b->right)        
        );
    }
    return 0;
}
int main() {
    Node *book1 = taoNode(1, "Giai Thuat");
    book1->left = taoNode(2, "Chuong 1");
    book1->right = taoNode(3, "Chuong 2");
    book1->left->left = taoNode(4, "Muc 1.1");
    Node *book2 = taoNode(1, "Giai Thuat");
    book2->left = taoNode(2, "Chuong 1");
    book2->right = taoNode(3, "Chuong 2");
    book2->left->left = taoNode(4, "Muc 1.1");
    Node *book3 = taoNode(1, "Giai Thuat Copy");
    book3->left = taoNode(99, "Chuong Khac");
    if (soSanh2Cay(book1, book2)) {
        printf("Hai cuon sach 1 va 2 la ban copy cua nhau\n");
    } else {
        printf("Hai cuon sach 1 va 2 KHAC nhau\n");
    }
    if (soSanh2Cay(book1, book3)) {
        printf("Ket luan: Hai cuon sach 1 va 3 la ban copy cua nhau\n");
    } else {
        printf("Hai cuon sach 1 va 3 KHAC nhau\n");
    }
    return 0;
}