#include <iostream>

struct Node
{
    int data;
    Node *ant;
    Node *prox;
};

class DoublyLinkedList
{
private:
    Node *begin;
    Node *end;

public:
    DoublyLinkedList()
    {
        this->begin = nullptr;
        this->end = nullptr;
    }

    void push_back(int data)
    {
        Node *novo = new Node;
        novo->data = data;
        bool isTheFirstNode = this->begin == nullptr && this->end == nullptr;
        if (isTheFirstNode)
        {
            this->begin = novo;
            this->end = novo;

            novo->ant = nullptr;
            novo->prox = nullptr;
        }
        else
        {
            this->end->prox = novo;
            novo->ant = this->end;
            novo->prox = nullptr;
            this->end = this->end->prox;
        }
    }

    int pop_back()
    {
        if (this->end == nullptr)
        {
            return 0;
        }

        Node *aux;

        if (this->end->ant == nullptr)
        {
            aux = this->end;
            this->end = nullptr;
            this->begin = nullptr;
        }
        else
        {
            aux = this->end;
            this->end = this->end->ant;
            this->end->prox = nullptr;
        }

        int data = aux->data;

        delete aux;
        return data;
    }

    void imprimirLista()
    {
        Node * aux = this->begin;
        

        if (aux == nullptr)
        {
            std::cout << "Lista está vazia" << std::endl;
            return;
        }

        std::cout << "Lista: ";
        do
        {
            std::cout << aux->data << "-> ";
            aux = aux->prox;
        } while (aux->prox != nullptr);

        std::cout << aux->data << std::endl;        
    }
    

    void removeAntSus(int data)
    {
        if (this->begin == nullptr){return;}

        Node * aux = this->begin;

        while (aux->prox != nullptr)
        {
            if (aux->data == data)
            {
                std::cout << "\nNúmero encontrado na lista!\n";
                break;
            }
            aux = aux->prox;
        }
        if (aux->prox == nullptr && aux->data != data)
        {
            std::cout << "\nNúmero não encontrado na lista!\n";
            return;
        }
        //A partir daqui eu garanto que ele achou algum número na lista! E aux aponta pra esse número

        if (aux->ant == nullptr && aux->prox == nullptr){return;}
        
        Node * antecessor;
        Node * sucessor;

        if (aux->ant == nullptr) // O número é o primeiro
        {
            sucessor = aux->prox;
            if (!(sucessor->prox == nullptr))
            {
                aux->prox = sucessor->prox;
                sucessor->prox->ant = aux;
            }
            delete sucessor;
        } 
        else if (aux->prox == nullptr) // O número é o ultimo
        {
            antecessor = aux->ant;
            if (!(antecessor->ant == nullptr))
            {
                aux->ant = antecessor->ant;
                antecessor->ant->prox = aux;
            }
            delete antecessor;
        } 
        else if (aux->prox->prox == nullptr) // O número é o penultimo
        {
            sucessor = this->end;
            antecessor = aux->ant;
            this->end = end->ant;
            this->end->ant = antecessor->ant;
            antecessor->ant->prox = this->end;
            this->end->prox = nullptr;

            delete sucessor;
            delete antecessor;
        } 
        else if (aux->ant->ant == nullptr) // O número é o segundo
        {
            antecessor = this->begin;
            sucessor = aux->prox;
            this->begin = this->begin->prox;
            this->begin->prox = sucessor->prox;
            this->begin->ant = nullptr;

            delete sucessor;
            delete antecessor;
        }
        else // todos os casos padrões
        {
            antecessor = aux->ant;
            sucessor = aux->prox;

            aux->ant = antecessor->ant;
            antecessor->ant->prox = aux;

            aux->prox = sucessor->prox;
            sucessor->prox->ant = aux;

            delete antecessor;
            delete sucessor;
        }
    }
};

int main()
{
    DoublyLinkedList list;
    bool isRunning = true;
    while (isRunning)
    {
        int option;
        int data;
        system("clear");
        std::cout << "O que quer fazer?\n";
        std::cout << "1: Push_back\n";
        std::cout << "2: Pop_Back\n";
        std::cout << "3: List\n";
        std::cout << "4: Remover Ant Sus\n";
        std::cout << "5: Exit\n";
        std::cout << "Digite: ";

        std::cin >> option;

        switch (option)
        {
        case 1:
            std::cout << "Digite o valor: ";
            std::cin >> data;
            list.push_back(data);
            system("clear");
            break;
        case 2:
            std::cout << "Você retirou o " << list.pop_back() << " da lista!";
            break;
        case 3:
            char wait;
            list.imprimirLista();
            std::cout << "\n\nDigite qualquer caractere para continuar ";
            std::cin >> wait;
            break;
        case 4:
            std::cout << "Digite o valor: ";
            std::cin >> data;
            list.removeAntSus(data);
            break;
        case 5:
            isRunning = false;
            break;
        default:
            break;
        }   
    }
}