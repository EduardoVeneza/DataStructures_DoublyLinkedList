#include <iostream>
#include <cstdlib>

struct Node
{
    std::string word;
    Node * ant;
    Node * prox;
};


class RoundList {
    private:
        Node * Start;
        Node * End;
        Node * Current;
    public:
        RoundList(){
            Start = nullptr;
            Current = nullptr;
            End = nullptr;
        }

        void insert(const std::string word)
        {
            Node * novo = new Node;
            novo->word = word;

            //Inicialização para o primeiro nó
            if(Start == nullptr && End == nullptr)
            {
                novo->ant = nullptr;
                novo->prox = nullptr;
                this->Start = novo;
                this->End = novo;
                this->Current = novo;
            } 
            else if (this->Current == this->End) //Adicionando no final da frase
            {
                this->Current->prox = novo;
                novo->ant = Current;
                Current = Current->prox;
                this->End = Current;

                //Ligando de forma circular
                this->Start->ant = this->End;
                this->End->prox = this->Start;
            } 
            else 
            {
                //Adicionando no meio
                Node * aux = Current->prox;
                Current->prox = novo;
                novo->ant = Current;
                novo->prox = aux;
                aux->ant = novo;
            }
        }

        void modify(const std::string word)
        {
            if (Current){this->Current->word = word;}    
        }

        void erase()
        {
            Node * aux = Current;

            //Se só existe um nó
            if (this->Start == this->End)
            {
                this->Start = nullptr;
                this->End = nullptr;
                this->Current = nullptr;
                delete aux;
            } 
            else if (this->Current == Start)
            {
                //Apagando o do começo
                this->Start = this->Start->prox;
                this->Start->ant = this->End;
                this->End->prox = this->Start;
                this->Current = this->Start;
                delete aux;
            } 
            else if (this->Current == End)
            {
                //Apagando o último
                this->End = this->End->ant;
                this->Start->ant = this->End;
                this->End->prox = this->Start;
                this->Current = this->End;
                delete aux;
            } else {
                //apagando no meio
                Node * backCurrent = Current->ant;
                Node * frontCurrent = Current->prox;

                backCurrent->prox = frontCurrent;
                frontCurrent->ant = backCurrent;
                this->Current = backCurrent;

                delete aux;
            }
        }

        void walkNext()
        {
            if (Current){this->Current = this->Current->prox;}
        }
        
        void walkBack()
        {
            if (Current){this->Current = this->Current->ant;}
        }

        std::string getCurrentWord()
        {
            if (Current == nullptr)
            {
                return "There is no current word";
            }
            return Current->word;
        }

        void showPhrase()
        {
            if (Current == nullptr)
            {
                std::cout << "There is no phrase now";
            } else 
            {
                
                if (Current->prox == nullptr || Current->ant == nullptr)
                {
                    std::cout << Current->word << " ";
                } else {
                    Node * aux = this->Start;
                    do
                    {
                        std::cout << aux->word << " ";
                        aux = aux->prox;
                    } while (aux != Start);
                }
            }
        }
};

void inserirMenu()
{
    std::cout << "\nDigite a palavra: ";
}

int main (int argc, char *argv[])
{
    RoundList phrase;
    bool isRunning = true;
    char option;
    while (isRunning)
    {
        std::string word;
        system("clear");
        std::cout << "Frase: ";
        phrase.showPhrase();
        std::cout << "\n\n" << "Current: " << phrase.getCurrentWord() << "\n\n";
        std::cout << "E: Editar Mensagem" << std::endl;
        std::cout << "D: Inserir (depois da palavra atual)" << std::endl;
        std::cout << "S: Eliminar palavra" << std::endl;
        std::cout << "<: Palavra anterior" << std::endl;
        std::cout << ">: Palavra posterior" << std::endl;
        std::cout << "X: Sair" << std::endl;
        std::cout << "Digite sua opção: ";
        std::cin >> option;

        switch (option)
        {
        case 'E':
        case 'e':
            inserirMenu();
            std::cin >> word;
            phrase.modify(word);
            break;
        case 'D':
        case 'd':
            inserirMenu();
            std::cin >> word;
            phrase.insert(word);
            break;
        case 'S':
        case 's':
            phrase.erase();
            break;
        case '<':
        case ',':
            phrase.walkBack();
            break;
        case '>':
        case '.':
            phrase.walkNext();
            break;
        case 'x':
        case 'X':
            isRunning = false;
            break;
        default:
            break;
        }
    }
    return 0;
}