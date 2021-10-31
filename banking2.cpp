/*Design a project to represent a bank account and its relevant operations, where following details can be maintained: 
1. Depositor name, 
2. account number(you may define any starting number), 
3. type of account, 
4. balance amount in the account. 
5. Any other attribute required you may add it by your own. 
*/


#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;


//    	function declaration

void write_account();	//function to write record in binary file
void search(int n); //function to display search 
void lastentry(); //function is to display last account entered
void display_special(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account

// CLASS USED IN PROJECT

class bank
{
	int acc_no;
	char name[50];
	int deposit;
	char type;
	char addr[50];
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular form
	int retacno() const;	//function to return account number
	int retdeposit() const;	//function to return balance amount
	char rettype() const;	//function to return type of bank
};         //class ends here

void bank::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acc_no;
	cout<<"\n\nEnter The Name of The bank Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account credit or savings choose -> (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for Credit ) : ";
	cin>>deposit;
	cout<<"\n Enter your address : ";
	cin.ignore();
	cin.getline(addr,50);
	cout<<"\n\n\nAccount Created..";
}

void bank::show_account() const
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance Amount : "<<deposit;
	cout<<"\nAddress :";
	cout<<addr;
}



void bank::modify()
{
	cout<<"\nAccount No. : "<<acc_no;
	cout<<"\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance Amount : ";
	cin>>deposit;
}

	
void bank::dep(int x)
{
	deposit+=x;
}
	
void bank::draw(int x)
{
	deposit-=x;
}
	
void bank::report() const
{
	cout<<acc_no<<setw(10)<<" "<<name<<setw(10)<<" "<<setw(6)<<deposit<<endl;
}

	
int bank::retacno() const
{
	return acc_no;
}

int bank::retdeposit() const
{
	return deposit;
}

char bank::rettype() const
{
	return type;
}






//    	THE MAIN FUNCTION OF PROGRAM

int main()
{
	int ch;
	int acc;

	do
	{
		system("cls");
		cout<<"\n\n\n\tWELCOME TO OUR BANK";
		cout<<"\n\n\t01. OPEN NEW bank";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. CHECK YOUR BALANCE";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. SEARCH IF YOUR ACCOUNT EXIST OR NOT";
		cout<<"\n\n\t09.  CHECK THE LASTEST ENTRY";
		cout<<"\n\n\t10.EXIT";
		cout<<"\n\n\tSelect Your Option (1-10) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case 1:
			write_account();
			break;
		case 2:
			cout<<"\n\n\tEnter The account No. : "; cin>>acc;
			deposit_withdraw(acc, 1);
			break;
		case 3:
			cout<<"\n\n\tEnter The bank No. : "; cin>>acc;
			deposit_withdraw(acc, 2);
			break;
		case 4: 
			cout<<"\n\n\tEnter The account No. : "; cin>>acc;
			display_special(acc);
			break;
		case 5:
			display_all();
			break;
		case 6:
			cout<<"\n\n\tEnter The account No. : "; cin>>acc;
			delete_account(acc);
			break;
		 case 7:
			cout<<"\n\n\tEnter The account No. : "; cin>>acc;
			modify_account(acc);
			break;
		 case 8: 
		 	cout<<"\n\n\tEnter The account No. : "; cin>>acc;
		 	search(acc);
		 	break;
		 case 10:
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		case 9: 
			cout<<"Last entry :";
			lastentry();
			break;
		 default :cout<<"Invalid choice";
		 
		}
		cin.ignore();
		cin.get();
	}while(ch!='0');
	return 0;
}
//function to add interest

//    	function to write in file


void write_account()
{
	bank ac;
	ofstream outFile;
	outFile.open("account.txt",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(bank));
	outFile.close();
}


//    	function to read specific record from file


void display_special(int n)
{
	bank ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(bank)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}



// function to modify record of file


void modify_account(int n)
{
	bool found=false;
	bank ac;
	fstream File;
	File.open("account.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(bank));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nEnter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(bank));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(bank));
			cout<<"\n\n\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

//    	function to delete record of file



void delete_account(int n)
{
	bank ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(bank)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.txt");
	rename("Temp.txt","account.txt");
	cout<<"\n\n\tRecord Deleted ..";
}

// function to search the account 

void  search(int n){
		bank ac;
	fstream File;
	bool found=false;
	File.open("account.txt", ios::binary|ios::in|ios::out);
	
	
	while(!File.eof() && found==false){
	File.read(reinterpret_cast<char *> (&ac), sizeof(bank));
	if(ac.retacno()==n){
		ac.show_account();
		found=true;
		
	}

	}
	File.close();
	if(found==false)
	cout<<"\n account not found";
}

//function to display all accounts deposit list


void display_all()
{
	bank ac;
	ifstream inFile;
	inFile.open("account.txt",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tbank HOLDER LIST\n\n";
	cout<<"****************************************************************\n";
	cout<<"A/c no.        NAME           Balance\n";
	cout<<"****************************************************************\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(bank)))
	{
		
		ac.report();
	}
	inFile.close();
}

//function to check the last entry


void lastentry(){



	bank ac;
	fstream File;
	int n;
	File.open("account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof())
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(bank));
		ac.retacno();
	}
	
	
	
	cout<<ac.retacno();
	File.close();
}

//    	function to deposit and withdraw amounts


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	bank ac;
	fstream File;
	File.open("account.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(bank));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw : ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(bank));
			cout<<"\n\n\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n account not found ";
}

//    			END OF PROJECT

		
