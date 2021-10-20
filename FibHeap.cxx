#include "FibHeap.hxx"

int main()
{
    int operacja,liczba;
    Fib_heap kopiec;
    Fib_heap::Node* it = kopiec.min_ptr;
    while(true){
        std::cout<<"===============================\n";
        std::cout<<"      Fibonacci heap\n\n";
        kopiec.display_roots(it);
        if(kopiec.min_ptr!=nullptr){
            std::cout<<"\n\nCurrently choosen node: "<<it->key<<"\n\n";
        }
        std::cout<<"\n\nChoose operation:\n";
        std::cout<<"1) Push\n";
        std::cout<<"2) Pop\n";
        std::cout<<"3) Remove\n";
        std::cout<<"4) Top\n";
        std::cout<<"5) Size\n";
        std::cout<<"6) ToLeft\n";
        std::cout<<"7) ToRight\n";
        std::cout<<"8) ToChild\n";
        std::cout<<"9) ToParent\n";
        std::cout<<"0) EXIT\n\n";
        std::cout<<"Choose: ";
        std::cin>>operacja;
        system("clear");
        switch (operacja){

        case 1:
            system("clear");
            std::cout<<"Write element to push: ";
            std::cin>>liczba;
            kopiec.push(liczba);
            it=kopiec.min_ptr;
            system("clear");
            break;
        case 2:
            kopiec.pop();
            it=kopiec.min_ptr;
            break;
        case 3:
            kopiec.remove(it);
            it=kopiec.min_ptr;
            break;
        case 4:
            if(kopiec.min_ptr==nullptr){
                std::cout<<"--------------------------------------\n";
                std::cout<<"Heap is empty!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            else{
                std::cout<<"--------------------------------------\n";
                std::cout<<"Element on top (min_ptr): "<<kopiec.top();
                std::cout<<"\n--------------------------------------\n\n";
            }
            break;
        case 5:
            std::cout<<"--------------------------------------\n";
            std::cout<<"Size of Fibonacci heap: "<<kopiec.size();
            std::cout<<"\n--------------------------------------\n\n";
            break;
        case 6:
            if(kopiec.min_ptr==nullptr){
                std::cout<<"--------------------------------------\n";
                std::cout<<"Heap is empty!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            else if(it->left!=nullptr){
                it=it->left;
            }
            else{
                std::cout<<"--------------------------------------\n";
                std::cout<<"Can't go left!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            break;
        case 7:
            if(kopiec.min_ptr==nullptr){
                std::cout<<"--------------------------------------\n";
                std::cout<<"Heap is empty!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            else if(it->right!=nullptr){
                it=it->right;
            }
            else{
                std::cout<<"--------------------------------------\n";
                std::cout<<"Can't go right!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            break;
        case 8:
            if(kopiec.min_ptr==nullptr){
                std::cout<<"--------------------------------------\n";
                std::cout<<"Heap is empty!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            else if(it->child!=nullptr){
                it=it->child;
            }
            else{
                std::cout<<"--------------------------------------\n";
                std::cout<<"Element doesnt't have children";
                std::cout<<"\n--------------------------------------\n\n";
            }
            break;
        case 9:
            if(kopiec.min_ptr==nullptr){
                std::cout<<"--------------------------------------\n";
                std::cout<<"Heap is empty!";
                std::cout<<"\n--------------------------------------\n\n";
            }
            else if(it->parent!=nullptr){
                it=it->parent;
            }
            else{
                std::cout<<"--------------------------------------\n";
                std::cout<<"Element doesn't have parent";
                std::cout<<"\n--------------------------------------\n\n";
            }
            break;
        case 0:
            exit(0);
            break;
        
        
        default:
            break;
        }

    }

    //--------------------------------------------------------------------------------------------
    //Pytanie do projektu

    /* wynik dla wstawienia liczb 1-10 oraz uzycia remove na najmniejszym elemencie (1)
        2 --- 10
       /|\ 
      / | \                      
     3  4  6
        |  |\
        5  | \
           7  8
               \
                9
      
      
      
      */
    return 0;
}