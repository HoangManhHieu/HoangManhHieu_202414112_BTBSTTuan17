#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    char title[100];      
    int sotrang;       
    int tongtrang;    
    struct Node *firstChild;
    struct Node *next;
} Node;
Node* createNode(char *title, int tongtrang) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->title, title);
    newNode->sotrang = tongtrang;
    newNode->tongtrang = tongtrang; 
    newNode->firstChild = NULL;
    newNode->next = NULL;
    return newNode;
}
void themnode(Node *nodecha, Node *nodecon) {
    if (nodecha->firstChild == NULL) {
        nodecha->firstChild = nodecon;
    } else {
        Node *temp = nodecha->firstChild;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nodecon;
    }
}
int updatepage(Node *root) {
    if (root == NULL) return 0;
    int sum = root->sotrang;
    Node *child = root->firstChild;
    while (child != NULL) {
        sum += updatepage(child);
        child = child->next;
    }
    root->tongtrang = sum;
    return sum;
}
int sochuong(Node *book) {
    int sum = 0;
    Node *chapter = book->firstChild;
    while (chapter != NULL) {
        sum++;
        chapter = chapter->next;
    }
    return sum;
}
Node* searchnode(Node *book) {
    Node *chuong = book->firstChild;
    Node *maxx = NULL;
    int maxmuc = -1;
    while (chuong != NULL) {
        if (chuong->tongtrang > maxmuc) {
            maxmuc = chuong->tongtrang;
            maxx = chuong;
        }
        chuong = chuong->next;
    }
    return maxx;
}
int xoanode(Node *nodeCha, char *muccanxoa) {
    if (nodeCha == NULL || nodeCha->firstChild == NULL) 
        return 0;
    Node *current = nodeCha->firstChild;
    Node *tmp = NULL;
    while (current != NULL) {
        if (strcmp(current->title, muccanxoa) == 0) {
            if (tmp == NULL) {
                nodeCha->firstChild = current->next;
            } else {
                tmp->next = current->next;
            }
            free(current); 
            return 1;
        }
        if (xoanode(current, muccanxoa)) {
            return 1;
        }
        tmp = current;
        current = current->next;
    }
    return 0;
}
void timChuong(Node *book, char *deMuc) {
    Node *chapter = book->firstChild;
    while (chapter != NULL) {
        if (strcmp(chapter->title, deMuc) == 0) {
            printf("%s - Tong so trang: %d\n", chapter->title, chapter->tongtrang);
            return;
        }
        chapter = chapter->next;
    }
    printf("Khong tim thay chuong: %s\n", deMuc);
}
int main() {
    Node *book = createNode("Sach Lap Trinh C", 0);
    Node *chap1 = createNode("Chuong 1: Gioi thieu", 5);
    Node *chap2 = createNode("Chuong 2: Cau truc du lieu", 10);
    Node *chap3 = createNode("Chuong 3: Giai thuat", 8);
    themnode(book, chap1);
    themnode(book, chap2);
    themnode(book, chap3);
    themnode(chap1, createNode("Muc 1.1: Lich su C", 3));
    themnode(chap1, createNode("Muc 1.2: Cai dat", 2));
    themnode(chap2, createNode("Muc 2.1: Array", 4));
    themnode(chap2, createNode("Muc 2.2: Pointer", 6));
    updatepage(book);
    printf("1. So chuong cua cuon sach: %d\n", sochuong(book));
    Node *longest = searchnode(book);
    if (longest) printf("2. Chuong dai nhat la: %s (%d trang)\n", longest->title, longest->tongtrang);
    printf("3. Xoa 'Muc 2.2: Pointer'...\n");
    if (xoanode(book, "Muc 2.2: Pointer")) {
        updatepage(book); 
        longest = searchnode(book);
        if (longest) printf("Chuong dai nhat hien tai: %s (%d trang)\n", longest->title, longest->tongtrang);
    } else {
        printf("Khong tim thay muc can xoa.\n");
    }
    printf("4. Tim kiem 'Chuong 1: Gioi thieu':\n   ");
    timChuong(book, "Chuong 1: Gioi thieu");

    return 0;
}