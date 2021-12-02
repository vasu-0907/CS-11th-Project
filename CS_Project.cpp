#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<ctype.h>

using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
 int acno;
 char name[50];
 int deposit, withdraw;
 char type;
 public:
	void create_account()
	{
	 cout<<"\nEnter the account No to be created  ::";
	 cin>>acno;
	 cout<<"\n\n\nEnter the Name of The account Holder  ::";
	 gets(name);
	 cout<<"\n\n\nEnter type of The account current or savings(c/s) ::";
	 cin>>type;
	 type=toupper(type);
	 cout<<"\n\n\nInitial amount to be deposited should be greater than Rs.500 for savings and \nRs.1000 for current account";
	 cout<<"\nAmount should not exceed 30000.\nVisit the nearest branch for more details";
	 cout<<"\n\nEnter amount ::";
	 cin>>deposit;
	 cout<<"\n\n\nAccount Created sucessfully..";
	 }

	void show_account()
	{
	 cout<<"\nAccount Number : "<<acno;
	 cout<<"\nAccount Holder Name : ";
	 puts(name);
	 cout<<"\nType of Account : "<<type;
	 cout<<"\nBalance amount : "<<deposit;
	 }

	void modify_account()
	{
	 cout<<"\nAccount No. : "<<acno;
	 cout<<"\nEnter Account Holder Name to be changed : ";
	 gets(name);
	 cout<<"\nModify Type of Account : ";cin>>type;
	 cout<<"\nEnter amount to be changed : ";cin>>deposit;
	 }

void dep(int x)
{
  deposit+=x;
}

void draw(int x)
{
  deposit-=x;
}

void report()
{
cout<<acno<<"\t"<<name<<"\t\t"<<type<<"\t\t"<<deposit<<endl;
}

  int  retacno()//accessor function to access private data member"acno"
		//outside the class
  {
  return acno;
  }

  int retdeposit()//accessor function to access private data member"deposit
		    //outside the class
  {
  return deposit;
  }

  char rettype()//accessor function to access private data member "type"
		//outside the class
  {
  return type;
  }

};         //class ends here



//***************************************************************
//    	global declaration for fstream object, account object
//****************************************************************

 fstream f1;//declaring the global variable accessable by entire program
 account ac;//declaring the global variable accessable by entire program


//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()//function
   {
    f1.open("account.dat",ios::out|ios::app);//creates a new data file to
					     //store or write records.
    ac.create_account();
    f1.write((char*)&ac,sizeof(ac));//writes bank holder details into
				    //the data file
    f1.close();
   }



//***************************************************************
//    	function to read specific record from file
//****************************************************************


void display_sp(int n)
{
    cout<<"\nBALANCE DETAILS\n";
    int flag=0;  //To check whether the account number is present
    f1.open("account.dat",ios::in);
    while(f1.read((char*)&ac,sizeof(ac)))//checks all the records
	{
	 if(ac.retacno()==n)
		{
		 ac.show_account();
		 flag=1;//changes to 1 if account is present
		}
	}
    f1.close();
if(flag==0)
 cout<<"\n\nSorry Account number does not exist";
    getch();
}


//***************************************************************
//    	function to modify record of file
//****************************************************************


void modify_account()//function to modify the existing data
{
    int no;
    int found=0;//to check for account presence
    cout<<"\n\n\tMODIFICATION PROCESS ";
    cout<<"\n\n\tEnter The account Number of the account to be modified=";
    cin>>no;
    f1.open("account.dat",ios::in|ios::out);//opens file in both in and out
					    //mode to modify and again write
					    //back the modified data to file.
    while(f1 && found==0)
	   {
	   int pos;
	   pos=f1.tellg();//used to store posotion of record
	   f1.read((char*)&ac,sizeof(ac));
	    if(ac.retacno()==no)//checking for user entered account number
		   {
		    ac.show_account();
		    cout<<"\nEnter The New Details of account"<<endl;
		    ac.modify_account();//calls the member function modify
		    f1.seekg(pos);
		    f1.write((char*)&ac,sizeof(ac));
		    cout<<"\n\n\t Record Updated";
		    found=1;
		   }
	     }
    f1.close();
    if(found==0)
    cout<<"\n\nSorry Record Not Found ";
    getch();
}


//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account()
   {
    int no;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nEnter The account no. of the customer You Want To Delete :";
    cin>>no;
    f1.open("account.dat",ios::in|ios::out);//opening in both modes
    fstream f2;
    f2.open("Temp.dat",ios::out);
    f1.seekg(0,ios::beg);
    while(f1.read((char*)&ac,sizeof(ac)))
	{
	 if(ac.retacno()!=no)
		{
		 f2.write((char*)&ac,sizeof(account));
		 }
	 }
    f2.close();
    f1.close();
    remove("account.dat");
    rename("Temp.dat","account.dat");
    cout<<"\n\n\tRecord Deleted successfully..";
    getch();
    }


//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

    void display_all()//
    {
     f1.open("account.dat",ios::in);
     if(!f1)
     {
       cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
       getch();
       return;
     }

     cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	  cout<<"====================================================\n";
	  cout<<"A/c no.\tNAME\t\tType\t\tBalance\n";
	  cout<<"====================================================\n";

      while(f1.read((char*)&ac,sizeof(ac)))
	 {
	   ac.report();
	}
     f1.close();
}


//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int option)
{
    int no,found=0;
    float amt;
    cout<<"\n\n\tEnter The account No.";
    cin>>no;
    f1.open("account.dat",ios::in|ios::out);
    while(!f1.eof() && found==0)
       {
       f1.read((char*)&ac,sizeof(ac));
	    if(ac.retacno()==no)
	   {
		    ac.show_account();
		    if(option==1)
		       {
			cout<<"\n\n\tTO DEPOSIT AMOUNT ";
			cout<<"\n\nEnter The amount to be deposited:";
			cin>>amt;
			float p;
			p=ac.retdeposit()+amt;
			if(amt>30000||p>30000)
			{
			cout<<"\nSorry you have exceeded your limit";
			cout<<"\nReach out to nearest branch for more details";
			}
			else
			{
			int x;
			x=int(amt);
			ac.dep(x);//calls the function dep()
			}
		       }
		     if(option==2)
		       {
			cout<<"\n\n\tTO WITHDRAW AMOUNT ";
			cout<<"\n\nEnter The amount to be withdrawn=";
			cin>>amt;
			 int bal=ac.retdeposit()-amt;
			 if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
			      cout<<"Sorry Insufficient balance";
				   else
			       ac.draw(amt);
		      }
			 int pos=-1*sizeof(ac);//stores the negativevalue of
					 //entire size of the object of class
			 f1.seekp(pos,ios::cur);//It moves the pointer to the
			 //position from the current cursor position to the
			 //size of the class subtracted from the current pos.
			 f1.write((char*)&ac,sizeof(account));
			 cout<<"\n\n\t Record Updated";
			 found=1;
	       }
	 }
    f1.close();
    if(found==0)
    cout<<"\n\n Record Not Found ";
    getch();
}
/*For example if the size of the class is 30 bytes and the current position
of the pointer will be in the end of the record after searching. So to bring
the position of the pointer to the starting the record to rewrite some of its
fields we use seekg(-1*sizeof(x),ios::cur). This ios cur has the current pos
of the record and it gets moved backward by the size of the class as it is in
negative sign. This is used to write the record without any problem*/

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
 cout<<"**";
 cout<<"BANKING";//process.h
 cout<<"TRANSACTIONS";//process.h
 cout<<"SYSTEM";//process.h
 cout<<"**";
 cout<<"\n\n\nMADE BY : Vasu";
 cout<<"\n\n\nSCHOOL : Sishya school";
 getch();

}



//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
  char ch;
  intro();
  do
    {
	  cout<<"\n\n\n\tMAIN MENU";
	  cout<<"\n\n\t01. NEW ACCOUNT";
	  cout<<"\n\n\t02. DEPOSIT AMOUNT";
	  cout<<"\n\n\t03. WITHDRAW AMOUNT";
	  cout<<"\n\n\t04. BALANCE ENQUIRY";
	  cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
	  cout<<"\n\n\t06. CLOSE AN ACCOUNT";
	  cout<<"\n\n\t07. MODIFY AN ACCOUNT";
	  cout<<"\n\n\t08. EXIT";
	  cout<<"\n\n\tSelect Your Option (1-8) ";
	  ch=getche();
	  switch(ch)
	  {
		case '1': 
			  write_account();
			  getch();
			break;
		case '2': 
			  deposit_withdraw(1);
			  break;
		case '3': 
			  deposit_withdraw(2);
			  getch();
			  break;
		case '4': int num;
			  cout<<"\n\n\tEnter The account No. ";
			  cin>>num;
			  display_sp(num);
			  break;
		case '5': 
			  display_all();
			getch();
			 break;
		case '6': delete_account();
			  break;
		 case '7': 
			   modify_account();
			   getch();
			   break;
		  case '8':exit(0);
		  default :cout<<"\a";
	}
    }while(ch!='8');

    return 0;
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************

