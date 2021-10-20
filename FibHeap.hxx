#ifndef FIB_HEAP
#define FIB_HEAP

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>

/* Autor: Kacper Druzdzel
Zrodla: 
"Wprowadzenie do Algorytmow" T.H.Cormen
www.geeksforgeeks.com
PDF zawarty w tresci projektu
www.programiz.com
*/

class Fib_heap{
    public:
    struct Node {
        
        int key;
        Node* parent;
        Node* left;
        Node* right;
        Node* child;
        bool mark;
        int degree;

        Node() = default;
        Node(int temp, Node* nparent, Node* nchild, Node* nleft, Node* nright, bool nmark, int ndegree);
        Node(const Node& node);
        Node(Node&& node);
        ~Node();

        Node& operator=(const Node& n);
        Node& operator=(Node&& n);
        bool operator==(const Node& n);
        bool operator==(Node&& n);
    };

    int number_of_nodes;
    Node* min_ptr;
    

    Fib_heap();
    ~Fib_heap();

    void push(int x);
    int pop();
    int top();
    int size();
    void remove(Node* x);
    void consolidate();
    void display_roots(Node* x);
    void decrease_key(Node* x,int k);
    void cut(Node* x,Node* y);
    void cascading(Node* y);
    void Fib_link(Node* x,Node* y);
    //dodatkowe
    void swap_node(Node** a,Node** b);
    Fib_heap& operator=(const Fib_heap& n);
    Fib_heap& operator=(Fib_heap&& n);
   
};

Fib_heap::Fib_heap() {
    Node* start = nullptr;
    min_ptr=start;
    number_of_nodes=0;
}

Fib_heap::~Fib_heap(){
    number_of_nodes=0;
    delete min_ptr;
    
}

Fib_heap& Fib_heap::operator=(const Fib_heap& n){ 
    number_of_nodes=n.number_of_nodes;
    min_ptr=n.min_ptr;
    
    return *this;
}

Fib_heap& Fib_heap::operator=(Fib_heap&& n){ 
    number_of_nodes=n.number_of_nodes;
    min_ptr=n.min_ptr;

    n.min_ptr=nullptr;
    n.number_of_nodes=0;
    
    return *this;
}


void Fib_heap::Fib_link(Node* x,Node* y) //Fiblink - usun node x z listy korzeni i uczyn korzen x, dzieckiem y
{
    (x->left)->right = x->right;
    (x->right)->left = x->left; //"usuwamy" node x (odpinamy go i ustawiamy jego left i right na jego samego)
    x->left = x->right = x;
    if (y->right == y){
        min_ptr = y;  //sprawdzenie czy drugi node nie jest jedynym
    }  
    x->parent = y;      //ustawienie x jako dziecka y
    if (y->degree==0){  //y->child == nullptr
        y->child = x;  //jezeli x bedzie jedynym dzieckiem y to ustawia na niego wartosc child
    }    
    x->right = y->child;  //tutaj nastepuje dodanie wezla x do listy dzieci y
    x->left = (y->child)->left;
    ((y->child)->left)->right = x;
    (y->child)->left = x;
    if (x->key < (y->child)->key){ //jezeli x ma mniejszy klucz to przestawiany jest wskaznik child
        y->child = x;
    }    
    y->degree++; //zwiekszenie licznika bezposrednich dzieci y
}

void Fib_heap::swap_node(Node** a,Node** b){
    Node* temp = *a;
    *a=*b;
    *b = temp;
}

void Fib_heap::consolidate(){
    int degree_of_node;
    int node_arr_size = (std::floor(log(number_of_nodes)/log((1+sqrt(5))/2))); //Wedlug "Wprowadzenie do algorytmow" T.H.Cormena (str.531)                                             
    Node* RANKS[node_arr_size+1]; //D(n) <= floor( log o podstawie z boskiej proporcji (1,61803..) z n ), gdzie n to liczba wezlow w kopcu
    std::fill_n(RANKS,node_arr_size+1,nullptr);  //[0...node_arr_size]
    Node* curr_node = min_ptr; //tworzymy "iterator", ktorym bedziemy sie poruszac po liscie korzeni
    Node* node_from_arr; //w tym node* przechowujemy node z tablicy RANKS
    do{
        degree_of_node=curr_node->degree; //pobranie ilosci dzieci wezla
        while(RANKS[degree_of_node]!=nullptr){ // wykonujemy aż nie będzie dwoch korzeni o takiej samej liczbie dzieci
            node_from_arr = RANKS[degree_of_node];  
            if(curr_node->key > node_from_arr->key){   //tutaj bierzemy pod uwage to, ze dzieckiem musi byc wiekszy element a korzeniem mniejszy
                swap_node(&curr_node,&node_from_arr);
            }
            if(node_from_arr==min_ptr){
                min_ptr=curr_node; //zabezpieczenie przed przylaczeniem min_ptr do listy dzieci
            }
            Fib_link(node_from_arr,curr_node); 
            if(curr_node->right==curr_node){ //sprawdzenie czy w liscie korzeni nie zostal tylko 1 element
                min_ptr = curr_node;
            }
            RANKS[degree_of_node]=nullptr; //po polaczeniu dwoch wezlow o tej samej liczbie dzieci, mamy pewnosc ze oba juz nie maja tej samej rangi, wiec wstawiamy nullptr
            degree_of_node++;
        }
        RANKS[degree_of_node]=curr_node; //wstawienie wezla do tablicy ranks
        curr_node= curr_node->right; //przejscie do kolejnego wezla
    } while (curr_node!=min_ptr);
    min_ptr=nullptr; //przepisanie na nowo kopca wedlug tablicy RANKS
    for (int j = 0; j <= node_arr_size; j++) {
        if (RANKS[j] != nullptr) {
            RANKS[j]->left = RANKS[j];
            RANKS[j]->right = RANKS[j];
            if (min_ptr != nullptr) {
                (min_ptr->left)->right = RANKS[j]; //jezeli jest juz jakis wezel w kopcu to nastepuje ich powiazanie oraz przy porownaniu kluczy, nastapi zmiana min_ptr
                RANKS[j]->right = min_ptr;
                RANKS[j]->left = min_ptr->left;
                min_ptr->left = RANKS[j];
                if (RANKS[j]->key < min_ptr->key){
                    min_ptr = RANKS[j];
                }
            }
            else {
                min_ptr = RANKS[j]; //jezeli nowy kopiec jest puste wstawiany jest do niego pierwszy element
            }
        }
    }

}

void Fib_heap::push(int x){
    Node* temp = new Node(x,nullptr,nullptr,nullptr,nullptr,false,0); //tworzymy pustego node
    if(min_ptr==nullptr){
        min_ptr = temp; //jezeli jest wstawiany jako pierwszy to min_ptr wskazuje na niego
        min_ptr->left = temp;
        min_ptr->right = temp;
    }
    else{
        (min_ptr->left)->right = temp;
        temp->right = min_ptr;
        temp->left = min_ptr->left; //jezeli nie jest to jest dolaczany z lewej strony od min_ptr
        min_ptr->left = temp;
        if (temp->key < min_ptr->key){
            min_ptr = temp;
        }  
    }
    number_of_nodes++; 
}

int Fib_heap::pop() {
    if (min_ptr == nullptr)    {
        std::cout << "The Fibonacci heap is empty" << std::endl;
    }    
    else {
        Node* temp_min = min_ptr;
        Node* child_iterator;
        child_iterator = temp_min;
        Node* x;
        if (temp_min->child != nullptr) { //po pierwsze nalezy przylaczyc kazde dziecko wezla min do listy korzeni, oraz usunac rodzica
 
            x = temp_min->child;
            do {
                child_iterator = x->right;//przejscie do kolejnego dziecka
                (min_ptr->left)->right = x;  //przylaczenie obecnego dziecka z lewej strony min_ptr
                x->right = min_ptr;
                x->left = min_ptr->left;
                min_ptr->left = x;
                if (x->key < min_ptr->key){ //aktualizacja min_ptr
                    min_ptr = x;
                }
                x->parent = nullptr; //usuwanie powiązania z min_ptr
                x = child_iterator;
            } while (child_iterator != temp_min->child);
        }
        (temp_min->left)->right = temp_min->right; //nastepnie usuwamy pierwszy min_ptr (przed wykonaniem operacji)
        (temp_min->right)->left = temp_min->left;
        if (temp_min == temp_min->right && temp_min->child == nullptr)
            min_ptr = nullptr; //jezeli to jest jedyny element, zwyczajnie go usuwamy
        else {
            min_ptr = temp_min->right; //jezeli sa jeszcze jakies wezly 
            consolidate();
        }
        number_of_nodes--;
        return temp_min->key;
    }
}

void Fib_heap::cut(Node* x,Node* y){ //x - dziecko , y - rodzic || tutaj nastepuje odciecie dziecka y i przylaczenie go do listy korzeni
    if(y->degree==1){
        y->child=nullptr; //jezeli jest jedynym dzieckiem to ustawiamy dziecko y na nullptr
    }
    else{
        y->child=x->right; //przepinanie na dziecko obok wskaznika
    }
    y->degree--; //zmniejszenie liczby dzieci o 1
    (x->right)->left = x->left;
    (x->left)->right = x->right; //tutaj odlaczamy x
    x->right=x->left=x;
    x->left=y->left;
    (y->left)->right=x; //dodajemy go na lewo od y, do listy korzeni
    y->left = x;
    x->right = y;
    x->parent=nullptr;
    x->mark=false; // ustawiamy mark na false
}

void Fib_heap::cascading(Node* y){
    Node* z = y->parent;
    if(z!=nullptr){
        if(!y->mark){
            y->mark=true; //"wedrowanie" w gore, az znajdzie sie na liscie korzeni
        }
        else{
            cut(y,z);  //inaczej powtarzamy funkcje dla parent po odcieciu wezla y od wezla z i przylaczenia go.
            cascading(z);
        }
    }
}

void Fib_heap::decrease_key(Node* x,int k){
    if (min_ptr==nullptr){
        std::cerr<<"decrease_key(): Cannot decrease empty heap!\n";
    }
    else if(k>x->key){
        std::cerr<<"decrease_key(): New value can't be higher than current value!\n";
        exit(EXIT_FAILURE);
    }
    else{
        x->key=k;
        Node* y=x->parent;
        if(y!=nullptr && x->key<y->key){// jezeli porzadek kopcowy zostal naruszony, zaczynamy od odciecia wezla x oraz czyniac go korzeniem
            cut(x,y);
            cascading(y);
        }
        if(x->key<min_ptr->key){ //jezeli warunek jest spelniony to nie ma potrzeby zmian w strukturze kopca
            min_ptr = x;
        }
    }
}

void Fib_heap::display_roots(Node* x){
    if(x==nullptr){
        std::cerr<<"Wrong node or heap is empty!\n";
    }
    else{
        Node* temp=x;
        do{ 
            std::cout<<temp->key;
            temp=temp->right;
            if(temp!=x){
                std::cout<<" <--> "; //wyswietlanie listy na danym poziomie
            }
        } while (temp!=x);
        std::cout<<"\n";
    }
}

void Fib_heap::remove(Node* x){
    decrease_key(x,-(std::numeric_limits<int>::infinity())); //ustawienie klucza wezla na najmniejszy mozliwy
    pop(); //usuniecie go funkcja pop()
}

static Fib_heap* union_heap(Fib_heap* a,Fib_heap* b){
    if(a->min_ptr==nullptr && b->min_ptr == nullptr){
        return nullptr;
    }
    else if(a->min_ptr==nullptr){
        return b;
    }
    else if (b->min_ptr==nullptr){
        return a;
    }
    else{
        Fib_heap* temp = new Fib_heap();
        temp->min_ptr = a->min_ptr;
        temp->min_ptr->right->left = b->min_ptr->left;
        b->min_ptr->left->right = temp->min_ptr->right;
        temp->min_ptr->right = b->min_ptr;
        b->min_ptr->left = temp->min_ptr;

        if(temp->min_ptr->key>b->min_ptr->key){
            temp->min_ptr=b->min_ptr;
        }
        temp->number_of_nodes=a->number_of_nodes+b->number_of_nodes;

        return temp;
    }
}

int Fib_heap::top(){return min_ptr->key;}

int Fib_heap::size(){return number_of_nodes;}


//---------------------------------------------------------------NODE-----------------------------------------------------------

Fib_heap::Node::Node(int temp, Node* nparent, Node* nchild, Node* nleft, Node* nright, bool nmark, int ndegree) : key(temp), parent(nparent), child(nchild) ,left(nleft), right(nright), mark(nmark), degree(ndegree) {}

Fib_heap::Node::Node(const Node& node){
    key = node.key;
    child = node.child;
    parent = node.parent;
    left = node.left;
    right = node.right;
    mark = node.mark;
    degree = node.degree;
}

Fib_heap::Node::Node(Node&& node){
    key = node.key;
    child = node.child;
    parent = node.parent;
    left = node.left;
    right = node.right;
    mark = node.mark;
    degree = node.degree;

    node.parent = nullptr;
    node.right = nullptr;
    node.left = nullptr;
    node.child = nullptr;
}

Fib_heap::Node::~Node() {
    parent=nullptr;
    left=nullptr;
    right=nullptr;
    child=nullptr;
}

Fib_heap::Node& Fib_heap::Node::operator=(const Node& node) {
    key = node.key;
    child = node.child;
    parent = node.parent;
    left = node.left;
    right = node.right;
    mark = node.mark;
    degree = node.degree;

    return *this;
}

bool Fib_heap::Node::operator==(const Node& node) {
    return (key==node.key && left==node.left && right==node.right && parent==node.parent && child == node.child && mark==node.mark && degree==node.degree);
}

bool Fib_heap::Node::operator==(Node&& node) {
    return (key==node.key && left==node.left && right==node.right && parent==node.parent && child == node.child && mark==node.mark && degree==node.degree);
}

Fib_heap::Node& Fib_heap::Node::operator=(Node&& node) {
    key = node.key;
    child = node.child;
    parent = node.parent;
    left = node.left;
    right = node.right;
    mark = node.mark;
    degree = node.degree;

    node.parent = nullptr;
    node.right = nullptr;
    node.left = nullptr;
    node.child = nullptr;

    return *this;
}


#endif