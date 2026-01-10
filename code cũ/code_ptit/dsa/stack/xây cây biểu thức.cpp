#include <bits/stdc++.h>
using namespace std;
struct Node{
    char data;
    Node *left;
    Node *right;
    Node(char n){
        data = n;
        left = nullptr;
        right = nullptr;
    }
};
bool isop(char c){
    return c == '+' ||c == '/' ||c == '*' ||c == '-' ;
}
void preorder(Node *root){
    if(root == nullptr) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);

}
void inorder(Node *root){
    if(root == nullptr) return;
    
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);

}
void postorder(Node *root){
    if(root == nullptr) return;
    
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";

}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        stack<Node*> st;
        for(int i = 0; i < s.size(); i++) {
            if(isop(s[i])) {
                // Tạo node toán tử
                Node *root = new Node(s[i]);
                
                // Lấy 2 cụm cây (hoặc node lá) từ stack ra làm con
                root->right = st.top(); st.pop(); // Phải lấy trước làm con PHẢI
                root->left = st.top(); st.pop();  // Trái lấy sau làm con TRÁI
                
                // Đẩy cả cụm cây mới này lại vào stack
                st.push(root);
            } else {
                // Nếu là toán hạng, tạo node lá và đẩy vào stack
                st.push(new Node(s[i]));
            }
        }
        inorder(st.top());
        cout << "\n";
    }
    
}