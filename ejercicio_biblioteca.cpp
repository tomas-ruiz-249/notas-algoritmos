#include <iostream>
#include <string>
#include "linked_list.cpp"

using namespace std;

class Loan{
public:
    Loan(){
        user = -1;
        book = -1;
        genre = -1;
    }

    Loan(int user, int book, int genre){
        this->user = user;
        this->book = book;
        this->genre = genre;
    }

    int getUser(){
        return user;
    }

    int getBook(){
        return book;
    }

    int getGenre(){
        return genre;
    }

    void setUser(int user){
        this->user = user;
    }

    void setBook(int book){
        this->book = book;
    }

    void setGenre(int genre){
        this-> book = book;
    }

    string to_string() const {
        return std::to_string(user) + ", " + std::to_string(book) + ", " + std::to_string(genre);
    }

    friend std::ostream& operator<<(std::ostream& os, const Loan& loan) {
        return os << loan.to_string();
    }
private:
    int user;
    int book;
    int genre;
};

int ** createMatrix(int y, int x){
    int ** m = new int*[y];
    for (int i = 0; i < y; i++){
        m[i] = new int[x];
        for(int j = 0; j < x; j++){
            m[i][j] = 0;
        }
    }
    return m;
}

void deleteMatrix(int** matrix, int y){
    for(int i = 0; i < y; i++){
        delete [] matrix[i];
    }
    delete matrix;
}

void printMatrix(int** matrix, int y, int x){
    for(int i = 0; i < y; i++){
        cout << "[ ";
        for(int j = 0; j < x; j++){
            cout << matrix[i][j];
            if(j != x - 1){
                cout << ", ";
            }
        }
        cout << " ]\n";
    }
}

class Library{
public:
    Library(int userCount, int bookCount, int genreCount, int loanCount){
        numUsers = userCount;
        numBooks = bookCount;
        numGenres = genreCount;
        numLoans = loanCount;
        matrix = createMatrix(numGenres, numBooks);
    }

    Library(){
        numUsers = 100;
        numBooks = 100;
        numGenres = 100;
        numLoans = 1000;
        matrix = createMatrix(numGenres, numBooks);
    }

    void initList(){
        int* genreList = new int[numBooks]();
        for(int k = 0; k < numBooks; k++){
            genreList[k] = rand() % numGenres;
        }
        for(int i = 0; i < numLoans; i++){
            int user = rand() % numUsers;
            int book = rand() % numBooks;
            int genre = genreList[book];
            Loan loan(user, book, genre);
            loans.append(loan);
        }
        delete[] genreList;
        loans.print();
        cout << "generated " << loans.getSize() << " loans\n";
    }

    void fillMatrix(){
        Node<Loan>* ptr = loans.getHead();
        for (int i = 0; i < numLoans; i++) {
            matrix[ptr->getData().getGenre()][ptr->getData().getBook()]++;
            ptr = ptr->getNext();
        }
        cout << "Matriz de libros x  por género y : " << endl;
        printMatrix(matrix, numGenres, numBooks);
    }
private:
    LinkedList<Loan> loans;
    int** matrix;
    int numUsers;
    int numBooks;
    int numGenres;
    int numLoans;
};

int main(){
    srand(time(0));
    Library lib(10,10,10,100);
    lib.initList();
    lib.fillMatrix();
    return 0;
}