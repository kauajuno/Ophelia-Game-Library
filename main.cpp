#include<bits/stdc++.h>

using namespace std;
typedef unsigned int ui;

enum Color{
    RED,
    BLACK
};

enum Genre{
    FPS,
    SPORTS,
    STRATEGY,
    SIMULATION,
    MOBA,
    ADVENTURE,
    INDIE,
    PLATFORMER,
    PVP,
    PVE,
    SANDBOX,
    ROGUELIKE,
    OPENWORLD,
    HORROR
};

enum Review{
    TERRIBLE,
    BAD,
    OK,
    GOOD,
    AWESOME
};

enum AgeRestriction{
    FFA,
    A10,
    A12,
    A14,
    A16,
    A18
};

class TreeNode{
    public:
    TreeNode* lchild;
    TreeNode* rchild;
    TreeNode* parent;
    ui downloads;
    string name;
    set<Genre> genres;
    Review review;
    AgeRestriction ageRestriction;
    Color color;
    TreeNode(ui d, string n, set<Genre> sg, Review r, AgeRestriction ar):
        downloads(d),
        name(n),
        genres(sg),
        review(r),
        ageRestriction(ar),
        parent(nullptr),
        color(Color::RED)
    {}
};

class RBTree{
    private:

        TreeNode* root;
        TreeNode* nil;

        void rightRotate(TreeNode* k){
            TreeNode* j = k->lchild;
            k->lchild = j->rchild;
            if(j->rchild != nil){
                j->rchild->parent = k;
            }
            j->parent = k->parent;
            if(k->parent == nullptr){
                root = j;
            }else if(k == k->parent->rchild){
                k->parent->rchild = j;
            }else{
                k->parent->lchild = j;
            }

            j->rchild = k;
            k->parent = j;
        }

        void leftRotate(TreeNode* k){
            TreeNode* j = k->rchild;
            k->rchild = j->lchild;
            if(j->lchild != nil){
                j->lchild->parent = k;
            }
            j->parent = k->parent;
            if(k->parent == nullptr){
                root = j;
            }else if(k == k->parent->rchild){
                k->parent->rchild = j;
            }else{
                k->parent->lchild = j;
            }

            j->lchild = k;
            k->parent = j;
        }

        void arrange(TreeNode* k){
            TreeNode* uncle;
            while(k->parent->color == Color::RED){
                if(k->parent == k->parent->parent->rchild){
                    uncle = k->parent->parent->lchild;
                    if(uncle->color == Color::RED){
                        uncle->color = Color::BLACK;
                        k->parent->color = Color::BLACK;
                        k->parent->parent->color = Color::RED;
                        k = k->parent->parent;
                    }else{
                        if(k == k->parent->lchild){
                            k = k->parent;
                            rightRotate(k);
                        }
                        k->parent->color = Color::BLACK;
                        k->parent->parent->color = Color::RED;
                        leftRotate(k->parent->parent);
                    }
                }else{
                    uncle = k->parent->parent->rchild;
                    if(uncle->color == Color::RED){
                        uncle->color = Color::BLACK;
                        k->parent->color = Color::BLACK;
                        k->parent->parent->color = Color::RED;
                        k = k->parent->parent;
                    }else{
                        if(k == k->parent->rchild){
                            k = k->parent;
                            leftRotate(k);
                        }
                        k->parent->color = Color::BLACK;
                        k->parent->parent->color = Color::RED;
                        rightRotate(k->parent->parent);
                    }
                }
                if(k == root)
                    break;
            }
            root->color = Color::BLACK;
        }

        void inOrderHelper(TreeNode* node){
            if(node == nil) return;
            inOrderHelper(node->lchild);
            cout << node->downloads << ' ';
            inOrderHelper(node->rchild);
        }

        void preOrderHelper(TreeNode* node){
            if(node == nil) return;
            cout << node->downloads << ' ';
            preOrderHelper(node->lchild);
            preOrderHelper(node->rchild);
        }

        void postOrderHelper(TreeNode* node){
            if(node == nil) return;
            postOrderHelper(node->lchild);
            postOrderHelper(node->rchild);
            cout << node->downloads << ' ';
        }

    public:

        RBTree(){
            nil = new TreeNode(0, "", {}, Review::OK, AgeRestriction::FFA);
            nil->color = Color::BLACK;
            root = nil;
        }

        void inOrderDFS(){
            inOrderHelper(root);
        }

        void preOrderDFS(){
            preOrderHelper(root);
        }

        void postOrderDFS(){
            postOrderHelper(root);
        }

        // BFS function to get all the games
        vector<TreeNode*> getAllGames(){
            TreeNode* aux = root;
            stack<TreeNode*> s;
            vector<TreeNode*> v;
            while(aux != nil || !s.empty()){
                v.push_back(aux);
                if(aux->rchild != nil)
                    s.push(aux->rchild);
                if(aux->lchild != nil)
                    s.push(aux->lchild);
                if(!s.empty()){
                    aux = s.top();
                    s.pop();
                }else{
                    aux = nil;
                }
            }
            return v;
        }

        void insert(ui downloads, string name, set<Genre> genre, Review review, AgeRestriction ageRestriction){
            TreeNode* newNode = new TreeNode(downloads, name, genre, review, ageRestriction);
            newNode->lchild = newNode->rchild = nil;
            
            TreeNode* prev = nullptr;
            TreeNode* curr = root;

            while(curr != nil){
                prev = curr;
                if(newNode->downloads < curr->downloads)
                    curr = curr->lchild;
                else
                    curr = curr->rchild;
            }

            newNode->parent = prev;

            if(prev == nullptr){
                newNode->color = Color::BLACK;
                root = newNode;
                return;
            }
            else if(newNode->downloads < prev->downloads)
                prev->lchild = newNode;
            else
                prev->rchild = newNode;

            if(newNode->parent->parent == nullptr)
                return;

            arrange(newNode);
            
        }
};

int main(){

    RBTree rbt = RBTree();

    rbt.insert(2, "The Witcher 3", {Genre::ADVENTURE, Genre::OPENWORLD}, Review::AWESOME, AgeRestriction::A16);
    rbt.insert(3, "Garten of BanBan", {Genre::INDIE, Genre::HORROR}, Review::TERRIBLE, AgeRestriction::A12);
    rbt.insert(4, "Bloons TD 6", {Genre::INDIE, Genre::PVE}, Review::GOOD, AgeRestriction::FFA);

    rbt.inOrderDFS();
    cout << '\n';
    rbt.preOrderDFS();
    cout << '\n';
    rbt.postOrderDFS();
    cout << '\n';

    vector<TreeNode*> vtest = rbt.getAllGames();
    for(TreeNode* t : vtest)
        cout << t->downloads << ' ';
    
    return 0;
}