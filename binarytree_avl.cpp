#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

// Ham tra ve chieu cao cua node
int height(Node* N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Ham tao mot node moi
Node* makeNode(int data) {
    Node* node = new Node();
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // node moi duoc them vao la node la"
    return node;
}


// Ham xoay phai
Node* xoayphai(Node*k2) {
   Node *k1 = k2->left;
   k2->left = k1->right;
   k1->right = k2;
   // cap nhat chieu cao
   k2->height = max(height(k2->left),height(k2->right)) +1;
   k1 -> height = max(height(k1->left),k2->height) +1;
   
   return k1;
}

// Ham xoay trái
Node* xoaytrai(Node* k2) {
    Node *k1 = k2->right;
    k2->right= k1->left;
    k1->left= k2;

    // Cap nhat chieu cao
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;

    // Tra ve node moi sau khi xoay
    return k1;
}

// Ham tra ve su can bang cua node
int canbang(Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Ham chen mot node moi vao cay AVL
Node* insertNode(Node* node, int data) {
    // 1. Chen binh thuong vao cay nhi phan tim kiem
    if (node == NULL)
        return makeNode(data);

    if (data < node->data)
        node->left = insertNode(node->left, data);
    else if (data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node; // khong cho phep gia tri trung nhau

    // 2. Cap nhat chieu cao cau node goc
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Kiem tra su can bang cua node goc va thuc hien xoay neu can thiet
    int balance = canbang(node);

    // TH trai trai
    if (balance > 1 && data < node->left->data)
        return xoayphai(node);

    // TH phai phai
    if (balance < -1 && data > node->right->data)
        return xoaytrai(node);

    // TH trai phai
    if (balance > 1 && data > node->left->data) {
        node->left = xoaytrai(node->left);
        return xoayphai(node);
    }

    // TH phai trai
    if (balance < -1 && data < node->right->data) {
        node->right = xoayphai(node->right);
        return xoaytrai(node);
    }

    return node; // Tra ve node neu khong thay doi neu khong can xoay
}

// Ham duyet cay theo thu tu truoc (Preorder Traversal)
void duyettruoc(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        duyettruoc(root->left);
        duyettruoc(root->right);
    }
}

int main() {
    Node* root = NULL;
    int n;
    cout << " nhap so phan tu cua mang:";
    cin >> n;
    int arr[n];
    cout << " nhap cac phan tu cua mang: ";
    for(int i=0; i<n; i++){
    	cin>>arr[i];
	}
    for(int i=0; i< n; i++){
    	root =insertNode(root,arr[i]);
	}

    cout << "duyet theo thu tu truoc la: ";
    duyettruoc(root);

    return 0;
}
