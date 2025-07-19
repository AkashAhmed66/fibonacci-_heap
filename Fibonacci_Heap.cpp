#include <bits/stdc++.h>

using namespace std;

struct node {
    int n;
    int degree;
    node *parent;
    node *child;
    node *left;
    node *right;
    char mark;
    char C;
};

class FibonacciHeap {
    private:
        int Head_number;
        node *H;

    public:
        node *Build_Heap();
        int Fibonnaci_link(node *, node *, node *);
        node *Build_node(int);
        node *Insert(node *, node *);
        node *Union(node *, node *);
        node *Extract_Min(node *);
        int Consolidate(node *);
        int Traverse(node *);
        node *Find(node *, int);
        int Decrease_key(node *, int, int);
        int Delete_element(node *, int);
        int Cut(node *, node *, node *);
        int Cascase_cut(node *, node *);

        FibonacciHeap() {
            H = Build_Heap();
        }
};

node *FibonacciHeap::Build_Heap() {
    node *Node;
    Node = NULL;
    return Node;
}

node *FibonacciHeap::Build_node(int val) {
    node *Node = new node();
    Node->n = val;
    return Node;
}

node *FibonacciHeap::Insert(node *Head, node *Node) {

    Node->degree = 0;

    Node->child = Node->parent = NULL;
    Node->left = Node->right = Node;

    Node->mark = 'F';
    Node->C = 'N';

    if (Head != NULL) {
        (Head->left)->right = Node;
        Node->right = Head;
        Node->left = Head->left;
        Head->left = Node;
        if (Node->n < Head->n)
            Head = Node;
    } else {
        Head = Node;
    }

    Head_number++;

    return Head;
}

int FibonacciHeap::Fibonnaci_link(node *Head, node *Node1, node *Node2) {
    (Node1->left)->right = Node1->right;
    (Node1->right)->left = Node1->left;

    if(Node2->right == Node2) Head = Node2;

    Node1->left = Node1->right = Node1;
    Node1->parent = Node2;

    if (Node2->child == NULL) Node2->child = Node1;

    Node1->right = Node2->child;
    Node1->left = (Node2->child)->left;

    ((Node2->child)->left)->right = (Node2->child)->left = Node1;

    if(Node1->n < (Node2->child)->n) Node2->child = Node1;

    Node2->degree++;
}

node *FibonacciHeap::Union(node *Head1, node *Head2) {

    node *temp;
    node *Head = Build_Heap();

    Head = Head1;
    (Head->left)->right = Head2;
    (Head2->left)->right = Head;
    temp = Head->left;
    Head->left = Head2->left;
    Head2->left = temp;

    return Head;
}

int FibonacciHeap::Traverse(node *Head) {
    node *temp = Head;
    if(temp == NULL) {
        cout << "Empty Heap \n";
        return 0;
    }

    cout << "Root Nodes are : \n";

    do {
        cout << temp->n;
        temp = temp->right;
        if(temp != Head) {
            cout << "-->";
        }
    } while(temp != Head && temp->right != NULL);

    cout << "\n";
}

node *FibonacciHeap::Extract_Min(node *Head) {
    node *minimum, *ptr, *Node1;

    minimum = ptr = Node1 = Head;

    if (Node1 == NULL) return Node1;

    node *Node2, *curr;

    Node2 = NULL;

    if (Node1->child != NULL) Node2 = Node1->child;

    if(Node2 != NULL) {
        ptr = Node2;
        do {
            curr = Node2->right;
            (Head->left)->right = Node2;
            Node2->right = Head;
            Node2->left = Head->left;
            Head->left = Node2;

            if (Node2->n < Head->n) Head = Node2;

            Node2->parent = NULL;
            Node2 = curr;
        } while(curr != ptr);
    }

    (Node1->left)->right = Node1->right;
    (Node1->right)->left = Node1->left;
    Head = Node1->right;

    if(Node1 == Node1->right && Node1->child == NULL) {
        H = NULL;
    } else {
        Head = Node1->right;
        Consolidate(Head);
    }
    Head_number--;

    return minimum;
}

int FibonacciHeap::Consolidate(node *Head) {
    int it, i;
    float frac = (log(Head_number)) / (log(2));
    int sz = frac;

    node *arr_node[sz];

    for(i = 0; i <= sz; i++) arr_node[i] = NULL;

    node *Node1 = Head;
    node *Node2, *temp, *pt = Node1;

    do {
        pt = pt->right;
        it = Node1->degree;
        while(arr_node[it] != NULL) {
            Node2 = arr_node[it];

            if (Node1->n > Node2->n) {
                temp = Node1;
                Node1 = Node2;
                Node2 = temp;
            }

            if (Node2 == Head) Head = Node1;

            Fibonnaci_link(Head, Node2, Node1);

            if (Node1->right == Node1) Head = Node1;

            arr_node[it] = NULL;
            it++;
        }

        arr_node[it] = Node1;
        Node1 = Node1->right;

    } while (Node1 != Head);

    H = NULL;

    for (int j = 0; j <= sz; j++) {
        if (arr_node[j] != NULL) {

            arr_node[j]->left = arr_node[j];
            arr_node[j]->right = arr_node[j];

            if (H != NULL) {

                (H->left)->right = arr_node[j];
                arr_node[j]->right = H;
                arr_node[j]->left = H->left;
                H->left = arr_node[j];

                if (arr_node[j]->n < H->n) H = arr_node[j];

            } else  H = arr_node[j];

            if (H == NULL) H = arr_node[j];
            else if (arr_node[j]->n < H->n) H = arr_node[j];

        }
    }
}

int FibonacciHeap::Decrease_key(node *Head, int prev, int cur) {
    node *Node;
    if (Head == NULL) {
        cout << "Heap is Empty \n";
        return 0;
    }
    node *ptr = Find(Head, prev);
    if (ptr == NULL) {
        cout << "Node not found \n";
        return 1;
    }

    if (ptr->n < cur) {
        cout << "Entered key is greater than current key \n";
        return 0;
    }
    ptr->n = cur;
    Node = ptr->parent;
    if (Node != NULL && ptr->n < Node->n) {
        Cut(Head, ptr, Node);
        Cascase_cut(Head, Node);
    }

    if (ptr->n < H->n) H = ptr;

    return 0;
}

int FibonacciHeap::Cut(node *Head, node *Node1, node *Node2) {
    if (Node1 == Node1->right) Node2->child = NULL;

    (Node1->left)->right = Node1->right;
    (Node1->right)->left = Node1->left;

    if (Node1 == Node2->child) Node2->child = Node1->right;

    Node2->degree = Node2->degree - 1;
    Node1->right = Node1->left = (Head->left)->right = Node1;

    Node1->right = Head;
    Node1->left = Head->left;

    Head->left = Node1;

    Node1->parent = NULL;
    Node1->mark = 'F';
}

int FibonacciHeap::Cascase_cut(node *Head, node *Node) {
    node *par = Node->parent;

    if (par != NULL) {
        if (Node->mark == 'F') {
            Node->mark = 'T';
        } else {
            Cut(Head, Node, par);
            Cascase_cut(Head, par);
        }
    }
}

node *FibonacciHeap::Find(node *Head, int val) {
    node *curr = Head;
    curr->C = 'Y';
    node *Node = NULL;

    if (curr->n == val) {
        Node = curr;
        curr->C = 'N';
        return Node;
    }

    if (Node == NULL) {
        if (curr->child != NULL) Node = Find(curr->child, val);

        if ((curr->right)->C != 'Y') Node = Find(curr->right, val);
    }

    curr->C = 'N';

    return Node;
}

int FibonacciHeap::Delete_element(node *Head, int val) {

    node *Node = NULL;

    int t = Decrease_key(Head, val, -5000);

    if (!t) Node = Extract_Min(H);

    if (Node != NULL) cout << "Key Deleted \n";
    else cout << "Key not Deleted \n";

    return 0;
}

int main() {

    FibonacciHeap FH;

    node *Node;
    node *Head;

    Head = FH.Build_Heap();

    Node = FH.Build_node(9);
    Head = FH.Insert(Head, Node);

    Node = FH.Build_node(5);
    Head = FH.Insert(Head, Node);

    Node = FH.Build_node(21);
    Head = FH.Insert(Head, Node);

    Node = FH.Build_node(35);
    Head = FH.Insert(Head, Node);

    FH.Traverse(Head);

    Node = FH.Extract_Min(Head);

    if (Node != NULL) cout << "Minimum element is : " << Node->n << "\n";
    else cout << "Heap is empty !!!\n";

    return 0;
}
