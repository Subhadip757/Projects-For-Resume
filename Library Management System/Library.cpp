#include<bits/stdc++.h>
using namespace std;

class Books{
public:
    int id;
    char name[120];
    char author[120];
    bool available;

    void getBooks(){
        available = true;
        cout<<"\nEnter id: "; cin >> id;
        cout<<"\nEnter name: ";
        cin.ignore();
        cin.getline(name, 120);
        cout<<"\nEnter author Name: "; 
        cin.getline(author, 120);
    }

    void display(){
        cout<<"\nID: "<<id<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Author name: "<<author<<endl;
        if(available){
            cout<<"Available"<<endl;
        }
        else{
            cout<<"Not Available"<<endl;
        }
    }
};

Books book;

bool isBookIdExists(int id) {
    ifstream file("BookDetails.txt", ios::binary);
    if (!file) {
        cout << "File not found!" << endl;
        return false;
    }

    Books tempBook;
    while (file.read(reinterpret_cast<char*>(&tempBook), sizeof(tempBook))) {
        if (tempBook.id == id) {
            return true;
        }
    }

    file.close();
    return false; 
}

void addBook() {
    system("cls");
    book.getBooks();

    if (isBookIdExists(book.id)) {
        cout << "Book with ID " << book.id << " already exists!" << endl;
        return;
    }
    ifstream temp("BookDetails.txt", ios::binary);
    ofstream file("BookDetails.txt", ios::binary | ios::app);
    if (file) {
        file.write(reinterpret_cast<char*>(&book), sizeof(book));

        while(temp.read(reinterpret_cast<char*>(&book), sizeof(book))){
            if(book.id)
        }

        cout << "\nBook successfully added!" << endl;
    } else {
        cout << "File doesn't exist!" << endl;
    }
    file.close();
}

void updateBook(int uid){
    system("cls");
    ifstream file("BookDetails.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    bool found = false;

    if(!file){
        cout<<"File not found!!"<<endl;
    }
    if(!temp){
        cout<<"File not found!!"<<endl;
    }

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book))){
        cout<<"\nUpdating details for book ->"<<endl;
        book.display();

        cout<<"\nEnter new details for the book ->"<<endl;
        book.getBooks();
        found = true;
    }
    file.close();
    temp.close();

    if(found){
        remove("BookDetails.txt");
        rename("temp.txt", "BookDetails.txt");
        cout<<"Book details updated succussfully!!"<<endl;
    }
    else{
        remove("temp.txt");
        cout<<"Book with id "<<uid<<" not found"<<endl;
    }

}

void searchBook(int sid){
    system("cls");
    ifstream file("BookDetails.txt", ios::binary);
    bool found = false;

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book))){
        if(book.id == sid){
            found = true;
            cout<<"Book Found!!"<<endl;
            book.display();
        }
    }
    if(!found){
        cout<<"\nBook not found!!"<<endl;
    }
    file.close();
}

void deleteBook(int did){
    system("cls");
    ifstream file("BookDetails.txt", ios::binary);
    ofstream temp("temp.txt", ios::binary);
    bool found = false;

    if(!file){
        cout<<"File not present!!"<<endl;
    }

    if(!temp){
        cout<<"File not present!!"<<endl;
    }

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book))){
        if(book.id != did){
            temp.write(reinterpret_cast<char*>(&book), sizeof(book));
        }
        else{
            found = true;
        }
    }
    file.close();
    temp.close();

    if(found){
        remove("BookDetails.txt");
        rename("temp.txt","BookDetails.txt");
        cout<<"Book deleted succussfully!!"<<endl;
    }
    else{
        cout<<"Book with id "<<did<<" not found!!"<<endl;
    }

}

void displayAllBook(){
    system("cls");
    ifstream file("BookDetails.txt", ios::binary);
    if(file){
        file.seekg(0);

        while(file.read(reinterpret_cast<char*>(&book), sizeof(book))){
            book.display();
            cout<<"--------------------------------"<<endl;
        }
    }
    else{
        cout<<"File not found!!"<<endl;
    }
    file.close();
}

void takeBook() {
    system("cls");
    fstream file("BookDetails.txt", ios::binary | ios::in | ios::out);
    bool found = false;

    if (!file) {
        cout << "\nFile not found!!" << endl;
        return;
    }

    cout<<"Here is the list of all the books"<<endl;
    cout<<"----------------------------------"<<endl;

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book))){
        book.display();
        cout<<"-------------------------------------------------"<<endl;
    }

    int tid;
    cout<<"Enter book id you want to take: ";cin>>tid;cout<<endl;

    file.clear();
    file.seekp(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
        if (book.id == tid) {
            if (book.available) {
                book.available = false;
                
                // Move the file pointer back to the beginning of the current record
                file.seekp(-static_cast<int>(sizeof(book)), ios::cur);
                file.write(reinterpret_cast<char*>(&book), sizeof(book));
                cout << "\nBook " << book.name << " taken successfully!" << endl;
            } else {
                cout << "\nBook " << book.name << " is already taken!" << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nBook with id " << tid << " not found!" << endl;
    }
    file.close();
}

void returnBook() {
    system("cls");
    fstream file("BookDetails.txt", ios::binary | ios::in | ios::out);
    bool found = false;

    if (!file) {
        cout << "\nFile not found!!" << endl;
        return;
    }

    while(file.read(reinterpret_cast<char*>(&book), sizeof(book))){
        if(!book.available){
            cout<<"Book id: "<<book.id<<endl;
            cout<<"Book Name: "<<book.name<<endl;
            cout<<"-------------------------------------------------"<<endl;
        }
    }

    int rid;
    cout<<"Enter book id you want to return: ";cin>>rid;cout<<endl;

    file.clear();
    file.seekp(0, ios::beg);

    while (file.read(reinterpret_cast<char*>(&book), sizeof(book))) {
        if (book.id == rid) {
            if (!book.available) {
                book.available = true;
                file.seekp(-static_cast<int>(sizeof(book)), ios::cur);
                file.write(reinterpret_cast<char*>(&book), sizeof(book));
                cout << "\nBook " << book.name << " returned successfully!" << endl;
            } else {
                cout << "\nBook " << book.name << " is already available!" << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nBook with id " << rid << " not found!" << endl;
    }
    file.close();
}

void MainMenu();

void adminMenu(){
    system("cls");
    int choice;
    do{
        cout<<"\n1. Add Book"<<endl;
        cout<<"2. Update Book"<<endl;
        cout<<"3. Search Book"<<endl;
        cout<<"4. Delete Book"<<endl;
        cout<<"5. Display Books"<<endl;
        cout<<"6. Return to MainMenu"<<endl;
        cout<<"Enter your choice: ";cin>>choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            int uid;
            cout<<"Enter book id you want to update: ";cin>>uid;
            updateBook(uid);
            break;
        case 3:
            int sid;
            cout<<"Enter book id you want to search: ";cin>>sid;
            searchBook(sid);
            break;
        case 4:
            int did;
            cout<<"Enter book id you want to delete: ";cin>>did;
            deleteBook(did);
            break;
        case 5:
            displayAllBook();
            break;
        case 6:
            MainMenu();
        
        default:
            cout<<"\nInvalid choice!!"<<endl;
        }
    }while(choice != 3);
}

void studentMenu(){
    system("cls");
    int choice;
    do{
        cout<<"\n1. Take Book"<<endl;
        cout<<"2. Return Book"<<endl;
        cout<<"3. Return to MainMenu"<<endl;
        cout<<"Enter your choice: ";cin>>choice;

        switch (choice)
        {
        case 1:
            takeBook();
            break;
        case 2:
            returnBook();
            break;
        case 3:
            MainMenu();
            break;
        
        default:
            cout<<"\nInvalid choice!!"<<endl;
        }
    }while(choice != 3);
}

void MainMenu(){
    system("cls");
    int choice;
    do{
        cout<<"\n1. Student Menu"<<endl;
        cout<<"2. Admin Menu"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Enter your choice: "; cin>>choice;

        switch (choice)
        {
        case 1:
            studentMenu();
            break;
        case 2:
            adminMenu();
            break;
        case 3:
            cout<<"Exiting...."<<endl;
            break;

        default:
            cout<<"\nInvalid Choice"<<endl;
        }
    }while(choice != 3);
}



int main(){
    MainMenu();
}