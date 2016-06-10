#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Person {
	private:
		string name;
		string lastname;
		int user_id;
		int age;
	public: 	
		Person() {
			this->name=this->lastname="";
			this->user_id=0;
		}
		Person(string name, string lastname, int user_id, int age) {
			this->name=name;
			this->lastname=lastname;
			this->user_id=user_id;
			this->age=age;
		}
		void setName(string name) {
			this->name=name;
		}
		string getName() {
			return this->name;
		}
		void setLastName(string lastname) {
			this->lastname=lastname;
		}
		string getLastName() {
			return this->lastname;
		}
		string getFullName() {
			return this->name + " " + this->lastname;
		}
		void setUserId(int user_id) {
			this->user_id=user_id;
		}
		int getUserId() {
			return this->user_id;
		}
		void setAge(int age) {
			this->age=age;
		}
		int getAge() {
			return this->age;
		}
		void info() {
			cout << "Name: " << getName() << endl;
			cout << "Last Name: " << getLastName() << endl;
			cout << "User ID: " << getUserId() << endl;
			cout << "Age: " << getAge() << endl;
		}
};

class Account {
	private:
		int account_number;
		Person person;
		double balance;
	public:
		Account(int account_number=0) {
			this->account_number=account_number;
			this->balance=0;			
		}
		Account(int account_number, double  balance) {
			this->account_number=account_number;
			this->balance=balance;
			
		}
		Account(int account_number, Person person) {
			this->account_number=account_number;
			this->person=person;
			this->balance=0;
		}
		Account(int account_number, Person person, double balance) {
			this->account_number=account_number;
			this->person=person;
			this->balance=balance;
		}
		
		void setAccountNumber(int account_number) {
			this->account_number=account_number;
		}
		int getAccountNumber() {
			return this->account_number;
		}
		void setBalance(double balance) {
			this->balance=balance;
		}
		double getBalance() {
			return this->balance;
		}
		void setPerson(Person person) {
			this->person=person;
		}		
		Person getPerson() {
			return this->person;
		}
		void info() {
			cout << "Account Number: " << this->account_number << endl;
			this->person.info();
			cout << "Balance: " << this->balance << endl;
		}
	    virtual void deposit(double amount){}		
		virtual void retire(double amount){}	
};

class Savings : public Account {
	private:
		double rate;
	public:
		Savings(int account_number, Person person, double balance, double rate):
			Account(account_number, person, balance) {				
				this->rate=rate;
			} 	
		void deposit(double amount) {
			if(amount < 100) {
					cout << "The minimum quota is 100$"<< endl;
				}
			else {
					setBalance(getBalance()+amount*(1+this->rate));	
			}
		}
		void  retire(double amount) {
			if(getBalance()>=amount) {
				setBalance(getBalance()-amount);	
			}
			else {
				cout << "\nInsufficient Funds. Try later." << endl;
			}
		}
		void info() {
			cout <<"=================================" << endl; 
			Account::info();
			cout << "Rate: " << this->rate << endl;
			cout <<"=================================" << endl; 
		}
	
};

class Checking : public Account {
	private:
		float rate;
	public: 	
		Checking(int account_number, Person person, double balance, double rate):
			Account(account_number, person, balance) {				
				this->rate=rate;
			}			
		void deposit(double amount) {
			if(amount < 100) {
					cout << "The minimum quota is 100$"<< endl;
				}
			else {
					setBalance(getBalance()+amount);
			}
		}
		void retire(double amount) {
			if(getBalance()>(amount*(1+this->rate))) {
				setBalance(getBalance()-(amount*(1+this->rate)));
			}
			else {
				cout << "\nInsufficient Funds. Try later." << endl;
			}
		}
		void setRate(float rate) {
			this->rate=rate;
		}	
		float getRate() {
			return rate;
		}
		void info() {
			cout <<"=================================" << endl; 
			Account::info();
			cout << "Rate: " << this->rate << endl;	
			cout <<"=================================" << endl; 		
		}	
};

class Node{
    private:
        Account *account;
        Node *next;

    public:
        Node(Account *account, Node *next=NULL){
            this->account = account;
            this->next = next;
        }

        void setAccount(Account *account){
            this->account = account;
        }
		Account *getAccount(){
			return this->account;
		}
        void setNext(Node *next){
            this->next = next;
        }
        Node *getNext(){
            return this->next;
        }
};

class List{
    private:
        Node *head; //Primer elemento de la lista

    public:
        List(){
            this->head = NULL; //La lista parte sin nada
        }

        void setHead(Node *node){
            this->head = node;
        }
        Node *getHead(){
            return this->head;
        }

        Node *getLast(){
            Node *aux;
            aux = this->head;
            if(aux){
                while(aux->getNext() != NULL){
                    aux = aux->getNext();
                }
            }
            return aux;
        }

        void *print( ){
            Node *aux;
            aux = this->head;
            while(aux){
				Checking *checking = dynamic_cast<Checking*>(aux->getAccount());
				Savings *savings = dynamic_cast<Savings*>(aux->getAccount());
				if(checking) {
					checking->info();
				}
				else if(savings) {
					savings->info();
				}
                else {
					//Should be one of the cases above
				}
                aux = aux->getNext();
            }
			return 0;
        }
		
		Account *searchByUserId(int user_id){
			Node *aux;
			Account *result;
			aux = this->head;
			while(aux){
				if(aux->getAccount()->getPerson().getUserId()==user_id) {
					result = aux->getAccount();
					return result;
				}
				aux = aux->getNext();
			}
			return new Account();
		}
		
		Account *searchByAccountNumber(int account_number){
			Node *aux;
			Account *result;
			aux = this->head;
			while(aux){
				if(aux->getAccount()->getAccountNumber()==account_number) {
					result = aux->getAccount();
					return result;
				}
				aux = aux->getNext();
			}
			return new Account();
		}

        void *insert(Account *account) {
            Node *newNode, *aux;
            newNode = new Node(account);
            aux = this->getLast();
            if(aux)
                aux->setNext(newNode);
            else
                this->setHead(newNode);			
			return 0;
        }
};

class Bank { 
	private:		
		List *account_list;
	public: 
		Bank() {
			this->account_list = new List();
		}
		void transfer (Account *a, Account *b, double amount) { 
			if(amount<100) {
				cout << "The minimun quota is $100" << endl;
			}
			
			else {
				if ((*a).getBalance() >= amount) { 
					(*a).retire(amount); 
				(*b).deposit(amount);			 
					cout<<"Transaction Success"<<endl; 
				} else { 
					cout<<"\n Insufficient Funds"<<endl; 
				} 
			}			
		}
		void createAccountMenu() {
			string name, lastname;
			int age, user_id, i;
			double balance;
			system("cls");
			cout << "Let's open your account:"  << endl;
			cout << "\nWe'll require the following information: " << endl;
			cout << "Name: ";
			cin >> name;
			cout << "Last name: ";
			cin >> lastname;
			cout << "ID: ";
			cin >> user_id;	
			cout << "Age: ";
			cin >> age;		
			Person newPerson = Person(name, lastname, user_id, age);			
			cout << "First Deposit Amount ($): ";
			cin >> balance;
			cout << "\n\nPick the type of account below:" << endl;
			cout << "\n1 - Checking" << endl;
			cout << "2 - Savings" << endl;
			do {				
				cout << "\nPick an option: ";
				cin >> i;
				switch(i) {		
					case 1: {
						int account_number;
						do {
							account_number = rand()%100000;
						} while(this->account_list->searchByAccountNumber(account_number)->getAccountNumber()>0);
						Checking *newCheckingAccount = new Checking(account_number,newPerson,balance,0.1);
						this->account_list->insert(newCheckingAccount);
						break;
					}
					case 2:
						int account_number;
						do {
							account_number = rand()%100000;
						} while(this->account_list->searchByAccountNumber(account_number)->getAccountNumber()>0);
						Savings *newSavingsAccount = new Savings(account_number,newPerson,balance,0.1);	
						this->account_list->insert(newSavingsAccount);					
						break;
				}
			} while(i<1 || i>2);	
		}
		void accountMenu(Account *account) {
			int i;
			do {			
				system("cls");
				cout << "Welcome Back " << account->getPerson().getFullName() << "." << endl;	
				cout << "How can we help you today?" << endl;
				cout << "\n1 - Deposit" << endl;			
				cout << "2 - Retire" << endl;		
				cout << "3 - Transfer" << endl;	
				cout << "4 - Account's info" << endl;
				cout << "0 - Exit" << endl;
				cout << "\nPick an option: ";	
				cin >> i;
				switch(i) {
					case 1: {
						double amount;
						system("cls");
						cout << "How much do you want to deposit ($): ";
						cin >> amount;
						Checking *checking = dynamic_cast<Checking*>(account);
						Savings *savings = dynamic_cast<Savings*>(account);
						if(checking) {
							checking->deposit(amount);
						}
						else if(savings) {
							savings->deposit(amount);
						}
						else {
							//Should be one of the cases above
						}						
						system("pause");
						break;
					}
					case 2: {
						double amount;
						system("cls");
						cout << "How much do you want to retire ($): ";
						cin >> amount;
						Checking *checking = dynamic_cast<Checking*>(account);
						Savings *savings = dynamic_cast<Savings*>(account);
						if(checking) {
							checking->retire(amount);
						}
						else if(savings) {
							savings->retire(amount);
						}
						else {
							//Should be one of the cases above
						}						
						system("pause");
						break;
					}
					case 3: {
						int i;
						Account *account2;
						do {
							system("cls");
							cout << "Who would you like to transfer?\n" << endl;
							cout << "1 - User ID" << endl;
							cout << "2 - Account Number" << endl;
							cout << "0 - Exit" << endl;				
							cout << "\nPick an option: ";
							cin >> i;
							switch(i) {		
								case 1:
									int user_id;
									cout << "\nUser ID: ";
									cin >> user_id;
									account2 = this->account_list->searchByUserId(user_id);
									if(account2->getAccountNumber()>0) {
										double amount;
										cout << "\nHow much would you like to transfer? ($): ";
										cin >> amount;
										Checking *checking = dynamic_cast<Checking*>(account);
										Savings *savings = dynamic_cast<Savings*>(account);
										Checking *checking2 = dynamic_cast<Checking*>(account2);
										Savings *savings2 = dynamic_cast<Savings*>(account2);
										if(checking) {
											if(checking2) {
												transfer(checking,checking2,amount);
											}
											else if(savings2) {
												transfer(checking,savings2,amount);											
											}
											else {
												//Should be one of the cases above
											}
										}
										else if(savings) {
											if(checking2) {
												transfer(savings,checking2,amount);											
											}
											else if(savings2) {
												transfer(savings,savings2,amount);											
											}
											else {
												//Should be one of the cases above
											}
										}
										else {
											//Should be one of the cases above
										}
									}
									else {							
										cout << "No Account with this User ID." << endl;
									}									
									system("pause");
									break;
								case 2:
									int account_number;
									cout << "\nAccount Number: ";
									cin >> account_number;
									account2 = this->account_list->searchByAccountNumber(account_number);
									if(account2->getAccountNumber()>0) {									
										double amount;
										cout << "\nHow much would you like to transfer? ($): ";
										cin >> amount;
										Checking *checking = dynamic_cast<Checking*>(account);
										Savings *savings = dynamic_cast<Savings*>(account);
										Checking *checking2 = dynamic_cast<Checking*>(account2);
										Savings *savings2 = dynamic_cast<Savings*>(account2);
										if(checking) {
											if(checking2) {
												transfer(checking,checking2,amount);
											}
											else if(savings2) {
												transfer(checking,savings2,amount);											
											}
											else {
												//Should be one of the cases above
											}
										}
										else if(savings) {
											if(checking2) {
												transfer(savings,checking2,amount);											
											}
											else if(savings2) {
												transfer(savings,savings2,amount);											
											}
											else {
												//Should be one of the cases above
											}
										}
										else {
											//Should be one of the cases above
										}				
									}
									else {							
										cout << "No Account with this Account Number." << endl;
									}									
									system("pause");
									break;
							}
						}  while(i<0 || i>2);
						break;
					}
					case 4:
						system("cls");
						Checking *checking = dynamic_cast<Checking*>(account);
						Savings *savings = dynamic_cast<Savings*>(account);
						if(checking) {
							checking->info();
						}
						else if(savings) {
							savings->info();
						}
						else {
							//Should be one of the cases above
						}
						system("pause");
						break;
				}
				
			} while(i!=0);
			
		}
		void accessAccountMenu() {
			int i;
			Account *account;
			do {
				system("cls");
				cout << "Pick any of the access methods below\n" << endl;
				cout << "1 - By User ID" << endl;
				cout << "2 - By Account Number" << endl;
				cout << "0 - Exit" << endl;				
				cout << "\nPick an option: ";
				cin >> i;
				switch(i) {		
					case 1:
						int user_id;
						cout << "\nUser ID: ";
						cin >> user_id;
						account = this->account_list->searchByUserId(user_id);
						if(account->getAccountNumber()>0) {
							accountMenu(account);
						}
						else {							
							cout << "No Account with this User ID." << endl;
							system("pause");
						}
						break;
					case 2:
						int account_number;
						cout << "\nAccount Number: ";
						cin >> account_number;
						account = this->account_list->searchByAccountNumber(account_number);
						if(account->getAccountNumber()>0) {
							accountMenu(account);
						}
						else {							
							cout << "No Account with this Account Number." << endl;
							system("pause");
						}
						break;
				}
			}  while(i<0 || i>2);
		}
		void mainMenu() {			
			int i;
			do {
				system("cls");
				cout << "The Greatest Bank" << endl;
				cout << "1 - Open Account" << endl;
				cout << "2 - Access Accont" << endl;
				cout << "3 - Show All Accounts (These privacy policies tho)" << endl;
				cout << "0 - Exit" << endl;
				cout << "\nPick an option: ";
				cin >> i;
				switch(i) {		
				case 1:
					this->createAccountMenu();
					break;
				case 2:
					this->accessAccountMenu();
					break;
				case 3:					
					system("cls");
					cout << "Accounts List:" << endl;
					this->account_list->print();
					system("pause");
					break;
				}
			} while(i!=0);	
		}
}; 

int main() {
	srand(time(NULL));
	Bank myBank = Bank();
	myBank.mainMenu();
	return 0;
}
