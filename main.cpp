#include<bits/stdc++.h>

using namespace std;
typedef unsigned int ui;

map<int, string> genreMap = {
    {1, "FPS"},
    {2, "SPORTS"},
    {3, "STRATEGY"},
    {4, "SIMULATION"},
    {5, "MOBA"},
    {6, "ADVENTURE"},
    {7, "INDIE"},
    {8, "PLATFORMER"},
    {9, "PVP"},
    {10, "PVE"},
    {11, "SANDBOX"},
    {12, "ROGUELIKE"},
    {13, "OPENWORLD"},
    {14, "HORROR"},
};

map<Genre, string> genreToString = {
    {Genre::FPS, "FPS"},
    {Genre::SPORTS, "SPORTS"},
    {Genre::STRATEGY, "STRATEGY"},
    {Genre::SIMULATION, "SIMULATION"},
    {Genre::MOBA, "MOBA"},
    {Genre::ADVENTURE, "ADVENTURE"},
    {Genre::INDIE, "INDIE"},
    {Genre::PLATFORMER, "PLATFORMER"},
    {Genre::PVP, "PVP"},
    {Genre::PVE, "PVE"},
    {Genre::SANDBOX, "SANDBOX"},
    {Genre::ROGUELIKE, "ROGUELIKE"},
    {Genre::OPENWORLD, "OPENWORLD"},
    {Genre::HORROR, "HORROR"}
};

map<AgeRestriction, string> ageRestrictionToString = {
    {AgeRestriction::FFA, "FREE FOR ALL"},
    {AgeRestriction::A10, "10+"},
    {AgeRestriction::A12, "12+"},
    {AgeRestriction::A14, "14+"},
    {AgeRestriction::A16, "16+"},
    {AgeRestriction::A18, "18+"}
};

map<Review, string> reviewToString = {
    {Review::TERRIBLE, "TERRIBLE"},
    {Review::BAD, "BAD"},
    {Review::OK, "OK"},
    {Review::GOOD, "GOOD"},
    {Review::AWESOME, "AWESOME"}
};

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

        void fixDelete(TreeNode* x){

        }

        TreeNode* minimum(TreeNode* node){
            while(node->lchild != nil)
                node = node->lchild;
            return node;
        }

        void rbTransplant(TreeNode* x, TreeNode* y){
            if (x->parent == nullptr) {
                root = y;
            } else if (x == x->parent->lchild){
                x->parent->lchild = y;
            } else {
                x->parent->rchild = y;
            }
            y->parent = x->parent;
        }

        void deleteHelper(TreeNode* node, string gameName){
            TreeNode* aux = node;
            // node to be deleted
            TreeNode* dNode = nil;
            // node to hold onto the characteristics of the deleted node OR its predecessor
            TreeNode* dNodeHelper;
            // "successor" of the deleted node in case he's got only one child
            TreeNode* dNodeOnlyChild;

            while(aux != nil){
                if(aux->name == gameName){
                    dNode = aux;
                    break;
                }
                if(gameName < aux->name)
                    aux = aux->lchild;
                else
                    aux = aux->rchild;
            }

            if(dNode == nil){
                cout << "THE GAME YOU'RE TRYING TO DELETE WAS NOT FOUND, CHECK THE SPELLING\n";
                return;
            }

            dNodeHelper = dNode;
            Color ogcolor = dNodeHelper->color;
            if(dNode->lchild == nil && dNode->rchild == nil){
                if(dNode == root)
                    root = nil;
                else if(dNode == dNode->parent->lchild)
                    dNode->parent->lchild = nil;
                else
                    dNode->parent->rchild = nil;
            }else if(dNode->lchild == nil){
                dNodeOnlyChild = dNode->rchild;
                rbTransplant(dNode, dNode->rchild);
            }else if(dNode->rchild == nil){
                dNodeOnlyChild = dNode->lchild;
                rbTransplant(dNode, dNode->lchild);
            }else{
                dNodeHelper = minimum(dNode->rchild);
                ogcolor = dNodeHelper->color;
                dNodeOnlyChild = dNodeHelper->rchild;
                if (dNodeHelper->parent == dNode) {
                    dNodeOnlyChild->parent = dNodeHelper;
                } else {
                    rbTransplant(dNodeHelper, dNodeHelper->rchild);
                    dNodeHelper->rchild = dNode->rchild;
                    dNodeHelper->rchild->parent = dNodeHelper;
                }

                rbTransplant(dNode, dNodeHelper);
                dNodeHelper->lchild = dNode->lchild;
                dNodeHelper->lchild->parent = dNodeHelper;
                dNodeHelper->color = dNode->color;
            }

            free(dNode);
            if(ogcolor == Color::BLACK){
                fixDelete(dNodeOnlyChild);
            }
        }

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
            cout << node->name << ' ';
            inOrderHelper(node->rchild);
        }

        void preOrderHelper(TreeNode* node){
            if(node == nil) return;
            cout << node->name << ' ';
            preOrderHelper(node->lchild);
            preOrderHelper(node->rchild);
        }

        void postOrderHelper(TreeNode* node){
            if(node == nil) return;
            postOrderHelper(node->lchild);
            postOrderHelper(node->rchild);
            cout << node->name << ' ';
        }

    public:

        RBTree(){
            nil = new TreeNode(0, "", {}, Review::OK, AgeRestriction::FFA);
            nil->color = Color::BLACK;
            root = nil;
        }

        void deleteGame(string name){
            deleteHelper(root, name);
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
                if(newNode->name < curr->name)
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

        void getGame(string gameName){
            TreeNode* aux = root;
            while(aux != nil){
                if(aux->name == gameName)
                    break;
                if(gameName < aux->name)
                    aux = aux->lchild;
                else
                    aux = aux->rchild;
            }

            if(aux == nil){
                cout << "GAME NOT FOUND, CHECK THE SPELLING\n";
                return;
            }

            cout << "NAME: " << aux->name << '\n';
            cout << "TOTAL DOWNLOADS: " << aux->downloads << '\n';
            cout << "AGE RESTRICTION: " << ageRestrictionToString[aux->ageRestriction] << '\n';
            cout << "YOUR REVIEW: " << reviewToString[aux->review] << '\n';
            cout << "GENRES:";

            set<Genre> gs = aux->genres;

            for(Genre g : gs){
                cout << " " << genreToString[g];
            }

            cout << '\n';

        }
};

void showOptionsMenu(){
    cout << "SELECT AN OPTION\n";
    cout << "1. INSERT NEW GAME\n";
    cout << "2. DELETE A GAME\n";
    cout << "3. SHOW ALL GAMES\n";
    cout << "4. SEARCH FOR A SPECIFIC GAME\n";
    cout << "5. QUIT\n";
}

void showGenres(){
    cout << "\033[36m"; // switches output color to cyan
    for(auto it = genreMap.begin(); it != genreMap.end(); it++){
        cout << it->first << ". " << it->second << '\n';
    }
    cout << "\033[0m"; // switches output color to white
}

void showReview(){
    cout << "\033[36m"; // switches output color to cyan
    cout << "1. TERRIBLE\n";
    cout << "2. BAD\n";
    cout << "3. OK\n";
    cout << "4. GOOD\n";
    cout << "5. AWESOME\n";
    cout << "\033[0m"; // switches output color to white
}

void showAgeRestriction(){
    cout << "\033[36m"; // switches output color to cyan
    cout << "1. FREE FOR ALL PUBLIC\n";
    cout << "2. 10+\n";
    cout << "3. 12+\n";
    cout << "4. 14+\n";
    cout << "5. 16+\n";
    cout << "6. 18+\n";
    cout << "\033[0m"; // switches output color to white
}

set<Genre> intvectorToGenreset(vector<int> &v){
    set<Genre> s;
    for(int i : v){
        if(genreMap.find(i) != genreMap.end()){
            switch(i){
                case 1:
                    s.insert(Genre::FPS);
                    break;

                case 2:
                    s.insert(Genre::SPORTS);
                    break;
                
                case 3:
                    s.insert(Genre::STRATEGY);
                    break;

                case 4:
                    s.insert(Genre::SIMULATION);
                    break;

                case 5:
                    s.insert(Genre::MOBA);
                    break;

                case 6:
                    s.insert(Genre::ADVENTURE);
                    break;

                case 7:
                    s.insert(Genre::INDIE);
                    break;
                case 8:
                    s.insert(Genre::PLATFORMER);
                    break;

                case 9:
                    s.insert(Genre::PVP);
                    break;

                case 10:
                    s.insert(Genre::PVE);
                    break;

                case 11:
                    s.insert(Genre::SANDBOX);
                    break;

                case 12:
                    s.insert(Genre::ROGUELIKE);
                    break;

                case 13:
                    s.insert(Genre::OPENWORLD);
                    break;

                case 14:
                    s.insert(Genre::HORROR);
                    break;
            }
        }
    }
    return s;
}

void insertNewGame(RBTree rbt){

    string name;

    ui downloads;

    string genresHolder;
    int auxGenre;
    vector<int> genresIndexes;
    set<Genre> genres;

    Review review;
    int reviewIndex;

    AgeRestriction ageRestriction;
    int ageRestrictionIndex;


    cout << "INSERT THE NAME OF THE GAME\n";
    getline(cin, name);


    cout << "HOW MANY DOWNLOADS DOES IT HAVE?\n";
    cin >> downloads;
    getchar();


    cout << "WHICH GENRES FITS THIS GAME THE MOST? (INVALID INDEXES WILL BE DISREGARDED\n";
    showGenres();

    getline(cin, genresHolder);

    // 14

    for(char c : genresHolder){
        if(isdigit(c))
            auxGenre = auxGenre * 10 + (c - '0');
        else{
            if(auxGenre != 0){
                genresIndexes.push_back(auxGenre);
                auxGenre = 0;
            }
        }
    }

    if(auxGenre != 0)
        genresIndexes.push_back(auxGenre);

    genres = intvectorToGenreset(genresIndexes);


    cout << "HOW WOULD YOU RATE THIS GAME SO FAR?\n";
    showReview();
    while(cin >> reviewIndex){
        if(reviewIndex < 0 || reviewIndex > 5){
            cout << "INVALID INDEX! INPUT A VALID ONE\n";
        }else{
            break;
        }
    }
    switch(reviewIndex){
        case 1:
            review = Review::TERRIBLE;
            break;

        case 2:
            review = Review::BAD;
            break;

        case 3:
            review = Review::OK;
            break;

        case 4:
            review = Review::GOOD;
            break;

        case 5:
            review = Review::AWESOME;
            break;
    }


    cout << "WHAT'S THE AGE RESTRICTION FOR THIS GAME?\n";
    showAgeRestriction();
    while(cin >> ageRestrictionIndex){
        if(ageRestrictionIndex < 0 || ageRestrictionIndex > 6){
            cout << "INVALID INDEX! INPUT A VALID ONE\n";
        }else{
            break;
        }
    }
    switch(ageRestrictionIndex){
        case 1:
            ageRestriction = AgeRestriction::FFA;
            break;

        case 2:
            ageRestriction = AgeRestriction::A10;
            break;

        case 3:
            ageRestriction = AgeRestriction::A12;
            break;

        case 4:
            ageRestriction = AgeRestriction::A14;
            break;

        case 5:
            ageRestriction = AgeRestriction::A16;
            break;

        case 6:
            ageRestriction = AgeRestriction::A18;
            break;
    }

    rbt.insert(downloads, name, genres, review, ageRestriction);

    cout << "GAME ADDED TO YOUR LIBRARY WITH SUCCESS!\n";
    
}

int main(){

    RBTree rbt = RBTree();
    vector<TreeNode*> games;
    int option;

    while(true){
        cout << "\033[35m"; // switches output color to magenta
        cout << "====================\n";
        cout << "WELCOME TO OPHELIAGL\n";
        cout << "====================\n\n";
        cout << "\033[0m"; // switches output color to white

        showOptionsMenu();

        while(cin >> option){
            getchar();

            switch(option){
                case 1:
                    insertNewGame(rbt);
                    break;

                case 2:
                    cout << "WORK IN PROGRESS\n";
                    break;

                case 3:
                    cout << "WORK IN PROGRESS\n";
                    break;

                case 4:
                    cout << "WORK IN PROGRESS\n";
                    break;

                case 5:
                    cout << "\033[35m";
                    cout << "THANK YOU FOR USING OPHELIAGL\n";
                    cout << "SEE YOU LATER!\n";
                    return 0;

                default:
                    cout << "INVALID OPTION, PLEASE TRY AGAIN\n";
                    break;
            }

            cout << '\n';
            showOptionsMenu();
        }

        
    }

    /*
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
    */    
    
    return 0;
}