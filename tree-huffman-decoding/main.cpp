/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/


void decode_huff(node * root,string s)
{
    int len = s.length();
    int i = 0;
    while(i < len){
        node *cur_node;
        cur_node = root;
        
        while(true){
            if(cur_node->left == NULL && cur_node->right == NULL){
                cout << cur_node->data;
                break;
            } 
            if(s[i] == '0') cur_node = cur_node->left;
            else if(s[i] == '1') cur_node = cur_node->right;
            i++;
        }
    }
    
}
