#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class book; // defined to use it in the borrower and returner classR

class borrower{
	protected:
		string borrowerName;
		string NIC;
		long int phoneNumber;
		string address;
		int borrowedBookCount;
		string *borrowedBookName;
		int *borrowedBookId;
		int returnedBookId;
	public:
		borrower(){
    		borrowedBookId = nullptr;
    		borrowedBookName = nullptr;
    		borrowedBookCount = 0;
		}
		~borrower(){
    		if (borrowedBookId != nullptr)
        		delete[] borrowedBookId;

    		if (borrowedBookName != nullptr)
        		delete[] borrowedBookName;
		}
		void bookData(book* books, int numberOfBooks); // to record the data of the book borrwed by the borrower
		void setData(string n, string nic, long int p, string add, int count); // to set the data of the borrower
		void chooseBook(book* books, int numberOfBooks); // to choose the book to borrow and update the available copies of the book
		void setNameAndId(book* books, int numberOfBooks, int j); // to set the name and id of the book borrowed by the borrower
		friend void borrowerData(book* books, int numberOfBooks, string nameToSearch, int numberOfBorrowers, borrower* b); // to search the data of the borrower by name and display the data of the book borrowed by the borrower
		void returnBook(book* books, int numberOfBooks);
};

void borrower :: setData(string n, string nic, long int p, string add, int count){
	borrowerName = n;
	NIC = nic;
	phoneNumber = p;
	address = add;
	borrowedBookCount = count;
	borrowedBookName = new string[count];
	borrowedBookId = new int[count];
}



class book{
	string name;
	string genre;
	string authorName;
	int id;
	int availableCopies;
	public:
		void setData(string n, int i, string g, string a, int c);
		friend void displayAvailableBooks(book *books, int numberOfBooks);
		friend void borrower :: setNameAndId(book* books, int numberOfBooks, int y);
		friend void borrower :: chooseBook(book* books, int numberOfBooks);
		friend void borrower :: returnBook(book* books, int numberOfBooks);
		friend void borrower ::bookData(book *books, int numberOfBooks);
};

void book :: setData(string n, int i, string g, string a, int c){
	name = n;
	id = i;
	genre = g;
	authorName = a;
	availableCopies = c;
}

void displayAvailableBooks(book *books, int numberOfBooks){
	cout<<"The list of the books avaible in the library is: "<<endl;
	cout<<left;
	cout<<setw(20)<<"Available Copies"
		<<setw(20)<<"Name"
		<<setw(15)<<"ID"<<endl;
		int count = 1;
	for (int i = 0;i<numberOfBooks;i++){
		if (books[i].availableCopies > 0){
			cout<<left;
			cout<<setw(20)<<books[i].availableCopies
				<<setw(20)<<books[i].name
				<<setw(15)<<books[i].id<<endl;
				count++;
		}
	}
}

void borrower :: setNameAndId(book* books, int numberOfBooks, int j){
	int idToBorrow;
	cout<<"Enter id of the book borrowed: ";
	cin>>idToBorrow;
	cin.ignore(1000, '\n');
	for (int i = 0;i<numberOfBooks;i++){
		if(books[i].id == idToBorrow){
			borrowedBookId[j] = idToBorrow;
			borrowedBookName[j] = books[i].name;
			break;
		}
	}
}

void borrower :: chooseBook(book* books, int numberOfBooks){
    int idToBorrow;
    cout<<"Enter id of the book you want: ";
    cin>>idToBorrow;
    cin.ignore(1000, '\n');
    for (int i = 0;i<numberOfBooks;i++){
        if(books[i].id == idToBorrow && books[i].availableCopies > 0){
            int* tempId = new int[borrowedBookCount + 1];
            string* tempName = new string[borrowedBookCount + 1];
            for(int j = 0; j < borrowedBookCount; j++){
                tempId[j] = borrowedBookId[j];
                tempName[j] = borrowedBookName[j];
            }
            tempId[borrowedBookCount] = idToBorrow;
            tempName[borrowedBookCount] = books[i].name;
            delete[] borrowedBookId;
            delete[] borrowedBookName;
            borrowedBookId = tempId;
            borrowedBookName = tempName;
            borrowedBookCount++;
            books[i].availableCopies--;
            cout<<"Book Borrowed Succesfully."<<endl;
            return;
        }
    }
    cout<<"The book is not available."<<endl;
}

void borrower :: returnBook(book* books, int numberOfBooks){
	int idToReturn;
	cout<<"Enter the id of the book you wants to return: ";
	cin>>idToReturn;
	cin.ignore(1000, '\n');
	for(int i = 0;i<borrowedBookCount;i++){
		if (borrowedBookId[i] == idToReturn){
			for (int j = 0;j<numberOfBooks;j++){
				if(books[j].id == idToReturn){
					books[j].availableCopies++;
					break;
				}
			}
			for (int k = i;k<borrowedBookCount-1;k++){
				borrowedBookId[k] = borrowedBookId[k+1];
				borrowedBookName[k] = borrowedBookName[k+1];
			}
			borrowedBookCount--;
			cout<<"Book Returned Succesfully."<<endl;
			return;
		}
	}
	cout<<"You Don't have book of id: "<<idToReturn<<endl;
	
}

void borrowerData(book* books, int numberOfBooks, string nameToSearch, int numberOfBorrowers, borrower* b){
	int borrowersCount = 0;
	for (int i = 0;i<numberOfBorrowers;i++){
		if (nameToSearch == b[i].borrowerName){
			borrowersCount++;
		}
	}
	if (borrowersCount == 0){
		cout<<"There is no borrower named: "<<nameToSearch<<endl;
		return;
	}
	if (borrowersCount == 1){
		for (int i = 0;i<numberOfBorrowers;i++){
			if (nameToSearch == b[i].borrowerName){
				cout<<" 			"<<b[i].borrowerName<<" 			"<<endl;
				cout<<left;
				cout<<setw(20)<<"Name"
					<<setw(15)<<"ID"<<endl;
				for(int j = 0; j < b[i].borrowedBookCount; j++){
					cout<<setw(20)<<b[i].borrowedBookName[j]
					    <<setw(10)<<b[i].borrowedBookId[j]<<endl;
				}
				return;
			}
		}
	}
	int checkNic = 0;
	string nicToSearch;
	cout<<"Enter the NIC To search: ";
	getline(cin, nicToSearch);
	if(borrowersCount > 1){
		cout<<"We have multiple borrowers named: "<<nameToSearch<<endl;
		for (int i = 0;i<numberOfBorrowers;i++){
			if (nicToSearch == b[i].NIC){
				cout<<" 			"<<b[i].borrowerName<<" 			"<<endl;
				cout<<left;
				cout<<setw(20)<<"Name"
					<<setw(15)<<"ID"<<endl;
				for(int j = 0; j < b[i].borrowedBookCount; j++){
					cout<<setw(20)<<b[i].borrowedBookName[j]
					    <<setw(10)<<b[i].borrowedBookId[j]<<endl;
				}
					checkNic = 1;
				return;
			}
		}
		if (checkNic == 0){
			cout<<"There is no borrower with NIC number: "<<nicToSearch<<endl;
			return;
		}
	}
}

int main (){
	int numberOfBooks;
	cout<<"Enter the number of books: ";
	cin>>numberOfBooks;
	cin.ignore(1000, '\n');
	book *books = new book[numberOfBooks];
	cout<<"Enter the data of the book: "<<endl;
	for (int i = 0;i<numberOfBooks;i++){
		string name;
		string genre;
		string authorName;
		int id;
		int availableCopies;
		cout<<"Enter the name of the book "<<i+1<<": ";
		getline(cin, name);
		cout<<"Enter the genre of the book: ";
		getline(cin, genre);
		cout<<"Enter the name of the author of the book: ";
		getline(cin, authorName);
		cout<<"Enter the id of the book: ";
		cin>>id;
		cin.ignore(1000, '\n');
		cout<<"Enter the available copies of the book: ";
		cin>>availableCopies;
		cin.ignore(1000, '\n');
		books[i].setData(name, id, genre, authorName, availableCopies);
	}

	int numberOfBorrowers;
	cout<<"Enter the number of borrowers: ";
	cin>>numberOfBorrowers;
	cin.ignore(1000, '\n');
	borrower *borrowers = new borrower[numberOfBorrowers];
	for(int i = 0;i<numberOfBorrowers;i++){
		string name;
		cout<<"Enter the name of the borrower("<<i+1<<"): ";
		getline(cin,name);
		string nic;
		cout<<"Enter the nic of the borrower("<<i+1<<"): ";
		getline(cin,nic);
		long int number;
		cout<<"Enter the phone number of the borrower("<<i+1<<"): ";
		cin>>number;
		cin.ignore(1000, '\n');
		string address;
		cout<<"Enter the address of the borrower("<<i+1<<"): ";
		getline(cin, address);
		int borrowedBookCount = 0;
		cout<<"Enter the number of books borrowed by: "<<name<<endl;
		cin>>borrowedBookCount;
		cin.ignore(1000, '\n');
		if (borrowedBookCount > numberOfBooks){
			cout<<"Library don't have this much books."<<endl;
			continue;
		}else{
			borrowers[i].setData(name, nic, number, address, borrowedBookCount);
			for (int j = 0;j<borrowedBookCount;j++){
			borrowers[i].setNameAndId(books, numberOfBooks, j);
			}
		}	
	}

	displayAvailableBooks(books, numberOfBooks);
	borrowers[0].chooseBook(books, numberOfBooks);

	cout<<"Do you want to search the data of a borrower? (y/n): ";
	string choice;
	getline(cin, choice);
	if (choice == "y" || choice == "Y"){
		string nameToSearch;
		cout<<"Enter the name of the borrower to search: ";
		getline(cin, nameToSearch);
		borrowerData(books, numberOfBooks, nameToSearch, numberOfBorrowers, borrowers);
	}
	borrowers[0].returnBook(books, numberOfBooks);
	displayAvailableBooks(books, numberOfBooks);
	delete[] books;
	delete[] borrowers;
	return 0;
}
