//#include<iostream.h>
#include "iomanip.h"
#include "iostream.h"
#include "fstream.h"
#include<conio.h>
//#include<fstream.h>
#include<stdio.h>
#include<string.h>
//#include<graphics.h>
#include<process.h>
#include<dos.h>
#include<time.h>
//#include<iomanip.h>
//book.dat for data contains all the books
//userdatabase.dat contains users data

int id=0;
void decrease_book_quantity();
void display_books();
void display_orders(int);
void rate_book();
void write_data();
void track_orders();
void add_to_cart();
void admin();
void User();
void add_book();
void delete_book();
void modify();
void view_rating();
void buy_book();

struct cart_item
{ //for one item of the cart
    char bookname[40];
    float cost;
    int quantity;
    int rating;
//add rati
} item;

class order
{ //for an order of a user
    int order_id;
    long int phonenumber; // for user id
    cart_item cart[10]; //cart array
    int cart_items; //number of items in cart
    float grandtotal;
    time_t order_time; //time_t is a datatype for time related operations

    public:
     void display();
     void place(cart_item source_cart[10], int source_cart_items, float total, long int phoneno,int id)
    {
	memcpy(cart,source_cart,sizeof(cart_item)*source_cart_items); //copy user cart to order cart

	cart_items=source_cart_items;
	phonenumber = phoneno;
	grandtotal = total;
	order_time = time(NULL);
	order_id=id;
    }
    time_t get_order_time()
    {
	return order_time;
    }

    long int get_phoneno()
    {
	return phonenumber;
    }
    int get_id()
	{
	return order_id;
	}
} order1;
void order::display()
{
		cout<<"ORDER: "<<order_id<<endl;
		cout<<"TIME: "<<asctime(localtime(&order_time));
		cout<<setw(10)<<"|BOOK NAME : "<<setw(10)<<" |COST : Rs."<<setw(10)<<" |QUANTITY : "<<setw(10)<<" |RATING : "<<endl;
		for(int i=0;i<cart_items;i++)
		{
			cout<<setw(10)<<cart[i].bookname<<setw(10)<<cart[i].cost<<setw(10)<<cart[i].quantity<<setw(10)<<cart[i].rating<<endl;
		}
		cout<<"GRAND TOTAL :Rs."<<grandtotal;
		getch();
}
class book
{
    char bookname[100];//name of book
    char author[100];//name of author
    char description[250];
    int booklength;//book length
    float cost;//cost of book
    int rating;//rating of book
    int quantity;//number of books in supply left
    int total_ratings;//number of ratings book has received
    char category[20]; //stores the category name
    public:
    char* get_bookname()
    {
	return bookname;
    }

    char* get_author()
    {
	return author;
    }

    int get_booklength()
    {
	return booklength;
    }

    float get_cost()
    {
	return cost;
    }
    char* get_category()
    {
	return category;
    }
    int get_quantity()
    {
	return quantity;
    }

    char* get_description()
    {
	return description;
    }

    int get_rating()
    {
	return rating;
    }

    int get_total_ratings()
    {
	return total_ratings;
    }

    void initial_rating()
    {
	total_ratings=0;
	rating=0;
    }
    void newquantity(char choice[12],int user_quantity)
    {   if(strcmp(choice,"cart_del")==0)         //cart_del if user deletes the book from their cart, supply increase
	quantity+=user_quantity;
	else if(strcmp(choice,"cart_add")==0)    //cart_add if user adds book to cart
	quantity-=user_quantity;
     }

     void rating1(int user_rating)
    {
		rating=((rating*total_ratings) + user_rating)/(total_ratings+1); //after first rating
		total_ratings++;
    }

    void fill()
    {
	cout<<"ENTER BOOK NAME :";
	gets(bookname);
	cout<<"\nENTER AUTHOR'S NAME :";
	gets(author);
	cout<<"\nENTER BOOK LENGTH :";
	cin>>booklength;
	cout<<"\nENTER BOOK COST :";
	cin>>cost;
	cout<<"\nENTER QUANTITY:";
	cin>>quantity;
	cout<<"\nENTER DESCRIPTION OF THE BOOK (SYNOPSIS OR BRIEF CONTENT)";
	cout<<endl;
	gets(description);
	cout<<"\nENTER CATEGORY:";
	add_category();
	initial_rating();
    }

    void set_name()
    {
	cout<<"ENTER BOOK NAME :";
	gets(bookname);
    }

    void set_author()
    {
	cout<<"\nENTER AUTHOR'S NAME :";
	gets(author);
    }

    void set_booklength()
    {
	cout<<"\nENTER BOOK LENGTH :";
	cin>>booklength;
    }

    void set_cost()
    {
	cout<<"\nENTER BOOK COST :";
	cin>>cost;
    }

    void set_quantity()
    {
	cout<<"\nENTER QUANTITY:";
	cin>>quantity;
    }

    void set_quantity(int qty)
    {
	quantity = qty;
    }

    void set_description()
    {
	cout<<"ENTER DESCRIPTION"<<endl;
	gets(description);
    }

    void display()
    {
	cout<<"BOOKNAME: "<<bookname<<endl;
	cout<<"AUTHOR: "<<author<<endl;
	cout<<"NO.OF PAGES: "<<booklength<<endl;
	cout<<"COST: "<<cost<<endl;
	cout<<"QUANTITY: "<<quantity<<endl;
	cout<<"CATEGORY: "<<category<<endl;
	cout<<"RATING: "<<rating<<" (OUT OF 5)"<<endl;
    }
    void add_category();

} b1, b2;//end of class book
void book::add_category()
{
	int choice;
	cout<<"CATEGORY CHOICES: \n1.FICTION \n2.NON FICTION \n3.EDUCATION \n4.SELF HELP \n5.OTHERS"<<endl;
	cin>>choice;
	switch(choice)
	{
		case 1:
		strcpy(category,"FICTION");
		break;
		case 2:
		strcpy(category,"NON FICTION");
		break;
		case 3:
		strcpy(category,"EDUCATION");
		break;
		case 4:
		strcpy(category,"SELF HELP");
		break;
		case 5:
		strcpy(category,"OTHER");
		break;
		default:
		cout<<"WRONG CHOICE.";
	 }
    }
class user
{
    char username[40];
    char address[100];
    long int phonenumber; //treated as user id (Primary key)
    char password[40];
    cart_item cart[10]; //cart array
    int cart_items; //number of items in cart

    public:

    char* get_username()
    {
	return username;
    }

    int get_cart_items()
    {
	return cart_items;
    }

    char* get_address()
    {
	return address;
    }

    long int get_phoneno()
    {
	return phonenumber;
    }

    char* get_password()
    {
	return password;
    }

    void setcart()
    { //sets cart items to 0 when user signs up
	cart_items=0;
    }

    void empty_cart(int);
    void add_to_cart();
    void fill();
    void delete_item();
    void display_cart();
    void place_order();
    void change_itemquantity();
} user1, loggedin_user;
//used to store info of the logged in user and to later search for his record to modify
//end of class user
void user::add_to_cart()
{
	cart[cart_items]=item;
	cart_items++;//increase items of cart by 1

}
void user::fill()
{

	cout<<"ENTER USER NAME : ";
	gets(username);
	cout<<"\nENTER PHONE NUMBER (10 DIGITS):  ";
	cin>>phonenumber;
	cout<<"\nENTER ADDRESS:";
	gets(address);
	cout<<"\nENTER PASSWORD :";
	gets(password);
}
void user::display_cart()
{
       cout<<setw(20)<<"|BOOK NAME "<<setw(20)<<" |QTY "<<setw(20)<<" |COST  Rs."<<endl;

	for(int i=0;i<cart_items; i++)
	{
		cout<<(i+1)<<": ";
		cout<<setw(15)<<cart[i].bookname<<setw(20)<<cart[i].quantity<<setw(20)<<cart[i].cost<<endl;
	}
}
void user::change_itemquantity()
{
 char name[50];
 int newquantity;
 if(cart_items==0)
	{
	    cout<<"CART IS EMPTY"<<endl;
	    return;
	}
	book o1;
	fstream fin3("book.dat",ios::binary|ios::in);
	fstream fout3("B.dat",ios::binary|ios::out);

	if(!fout3||!fin3)
	{
		cout<<"BOOK DATABASE NOT WORKING. PLEASE TRY TO DELETE ITEMS LATER.";
		return;
	}
	int flag=-1;
	cout<<"ENTER NAME OF BOOK WHOSE QUANTITY YOU WANT TO CHANGE:"<<endl;
	gets(name);
	for(int i=0;i<cart_items;i++)
	{

	    if(strcmp(cart[i].bookname,name)==0)
	     {
		flag++;
		cart_item temp;
		temp=cart[i];
		cout<<"CURRENT QUANTITY :"<<cart[i].quantity<<endl;
		cout<<"ENTER NEW QUANTITY: ";
		cin>>newquantity;
		while(fin3.read((char*)&o1,sizeof(o1)))
		{
			if(strcmp(o1.get_bookname(),name)==0)
			{
				if(newquantity>(o1.get_quantity()+temp.quantity))
				{
					cout<<"QUANTITY ENTERED IS MORE THAN QUANITY IN STORE."<<endl;
					cart[i].quantity=temp.quantity;
				}
				else
				{
				if(temp.quantity>cart[i].quantity)
				{
				 o1.newquantity("cart_del",(temp.quantity-cart[i].quantity));
				}
				else if(temp.quantity<cart[i].quantity)
				{
					 o1.newquantity("cart_add",(cart[i].quantity-temp.quantity));
				}
			}
			}
		       fout3.write((char*)&o1,sizeof(o1));
		 }
	   }
	   }
	   fin3.close();
	   fout3.close();
	   remove("book.dat");
	   rename("B.dat","book.dat");
       if(flag==-1)
	 cout<<"BOOK NOT FOUND IN CART.";
}
void user::delete_item()
{
	if(cart_items==0)
	{
	    cout<<"CART IS EMPTY"<<endl;
	    return;
	}
	book o1;
	fstream fin("book.dat",ios::binary|ios::in);
	fstream fout("B.dat",ios::binary|ios::out|ios::app);
	if(!fout||!fin)
	{
		cout<<"BOOK DATABASE NOT WORKING. PLEASE TRY TO DELETE ITEMS LATER.";
		return;
	}
	int flag=-1;
	char name[50];
	cout<<"ENTER NAME OF THE BOOK YOU WANT TO DELETE"<<endl;
	gets(name);
	for(int i=0;i<cart_items;i++)
	{
	    if(strcmp(cart[i].bookname,name)==0)
	     {
		flag++;
		cart_item temp;
		temp=cart[i];
		cart[i]=cart[cart_items-1];
		cart[cart_items-1]=temp;
		cart_items--;
		while(fin.read((char*)&o1,sizeof(o1)))
		{
			if(strcmp(o1.get_bookname(),name)==0)
			{
			       o1.newquantity("cart_del",temp.quantity);
			       fout.write((char *)&o1,sizeof(o1));
			}
			else
				fout.write((char*)&o1,sizeof(o1));
		}
		fin.close();
		fout.close();
		remove("book.dat");
		rename("B.dat","book.dat");
	  }
	}
	 if(flag==-1)
	 cout<<"BOOK NOT FOUND IN CART.";

}

void user::empty_cart(int mode = 0)
{
// 0:empty, place
    int temp = cart_items;
    cart_items = 0;
    if(mode==1) return;
    book o1;
    for(int i = 0; i < temp; i++) {
	fstream fout("B.dat",ios::binary|ios::out|ios::app);
	fstream fin("book.dat",ios::binary|ios::in);
	while(fin.read((char*)&o1,sizeof(o1)))
	{
	    if(strcmp(o1.get_bookname(),cart[i].bookname)==0)
	    {
		o1.newquantity("cart_del",cart[i].quantity);
		fout.write((char *)&o1,sizeof(o1));
	    }
	    else
		fout.write((char*)&o1,sizeof(o1));
	}
	fin.close();
	fout.close();
	remove("book.dat");
	rename("B.dat","book.dat");
    }
}
void user::place_order()
{
	float grandtotal=0;
	float total_cost=0;

	for(int i=0;i<cart_items;i++)
	{
	    total_cost += cart[i].cost*cart[i].quantity;
	}
	float tax=(0.1)*total_cost;
	grandtotal=total_cost+tax;
	cout<<"YOUR FINAL AMOUNT (INCLUSIVE OF READER'S TAX): Rs."<<grandtotal<<endl;
	fstream fout("orders.dat",ios::app|ios::binary); //to get id of placed order
	if(!fout)
	{
		cout<<"ERROR IN PLACING ORDER"<<endl;
	    return;
	}
	fout.seekg(0,ios::end);
	id=fout.tellg()/sizeof(order1);
	id=id+1;
	cout<<"\nYOUR ORDER ID :"<<id<<endl;
	order1.place(cart,cart_items,grandtotal,phonenumber,id);
      fout.write((char*)&order1,sizeof(order1));
      fout.close();
}
void add_to_cart()
{
    loggedin_user.add_to_cart();
}
void track_orders()
{
    fstream fin("orders.dat",ios::in|ios::binary);
    if(!fin)
    {
	cout<<"ERROR IN DISPLAYING ORDERS";
	return;
    }
    cout<<"ENTER ORDER ID:"<<endl;
    cin>>id;
    int flag=-1;//to check order id
    while(fin.read((char*)&order1,sizeof(order1)))
    {
	if(order1.get_id()==id)
	{
	    if(order1.get_phoneno()==loggedin_user.get_phoneno())
	    {   flag++;
		break;
	    }

	    else
	    {
		cout<<"CANNOT ACCESS ANOTHER USER'S DATA !"<<endl;
		return;
	    }
	}
    }
    getch();
    fin.close();
    if(flag!=-1)
    {
    double difference = difftime(time(NULL),order1.get_order_time());
    difference/=60;
    if(difference>=4)
	cout<<"ORDER DELIVERED"<<endl;
    else if(difference>=3)
	cout<<"ORDER SHIPPED"<<endl;
    else if(difference>=2)
	cout<<"ORDER DISPATCHED"<<endl;
    else
	cout<<"ORDER PLACED"<<endl;
   }
   else cout<<"ORDER ID DOES NOT EXIST, OR ORDER HAS NO BEEN PLACED YET"<<endl;
}

void display_orders(int mode = 0)
{
    fstream fin("orders.dat",ios::in|ios::binary | ios::out);
    if(!fin)
    {
		cout<<"ERROR IN DISPLAYING ORDERS";
		return;
    }
    //0:user, 1:admin
    int flag=-1;//to validate phone
    if(mode == 0) {
	while(fin.read((char*)&order1,sizeof(order1)))
	{
		if(order1.get_phoneno()==loggedin_user.get_phoneno())
		{
			flag++;
			order1.display();
			cout<<endl;
		}
	}
    }
    else
	{
		long int phoneno;
		cout<<"ENTER PHONE NUMBER OF USER"<<endl;
		cin>>phoneno;

		while(fin.read((char*)&order1,sizeof(order1)))
		{
			if(order1.get_phoneno()==phoneno)
			{
				flag++;
				order1.display();
				cout<<endl;
			}
		}
	}
	if(flag==-1)
		  cout<<"USER NOT FOUND"<<endl;
    getch();
    fin.close();
}

void view_cart()
{ //to display cart

	if(loggedin_user.get_cart_items()==0)
	{
	    cout<<"EMPTY CART !"<<endl;
	    return;
	}
	//cart menu
	do {
	    clrscr();
	     cout<<"\t\t\t\tCART ITEMS"<<endl;
	     loggedin_user.display_cart();

	     cout<<endl;

	    cout<<"1.DELETE ITEM FROM CART"<<endl;
	    cout<<"2.EMPTY CART"<<endl;
	    cout<<"3.CHANGE QUANITY OF ITEM"<<endl;
	    cout<<"4.PLACE ORDER AND CHECKOUT"<<endl;
	    cout<<"5.EXIT CART"<<endl;
	    char ch;//choice
	    cin>>ch;
	    switch(ch) {
		case '1': loggedin_user.delete_item();
			getch();
			if(loggedin_user.get_cart_items()==0)
			    return;
			break;
		case '2': loggedin_user.empty_cart();
			getch();
			return;
		case '3':
			loggedin_user.change_itemquantity();
			return;
		case '4':
			loggedin_user.place_order();
			loggedin_user.empty_cart(1);
			cout<<"YOUR ORDER HAS BEEN PLACED. THANK YOU FOR SHOPPING WITH US!"<<endl;
			getch();
			return;
		case '5': return;
		default: cout<<"WRONG CHOICE ! ENTER AGAIN"<<endl;
	    }
	} while(1);
}

void password(char pass[])
{ //renaming the input variable to avoid confusion
    int i=0; //loop counter
    char temp; //a Temp char
    for(i=0; ; )
    { //infinite loop
	temp=getch(); //stores char typed in temp
	if((temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z')||(temp>='0'&&temp<='9')) {
	//check if a is numeric or alphabet
	    pass[i]=temp; //stores temp in pass
	    ++i;
	    cout<<"*";
	}
	if(temp=='\b'&& i>=1)
	{//if user typed backspace
	//i should be greater than 1.
	    cout<<"\b \b"; //delete the character behind the cursor.
	    --i;
	}
	if(temp=='\r') {//if enter is pressed
	    pass[i]='\0'; //null means end of string.
	     break; //break the loop
	}
    }
} //end of password function

void login()
{
    cout<<"1.LOGIN AS ADMINISTRATOR"<<endl;
    cout<<"2.LOGIN AS USER"<<endl;
    cout<<"ENTER CHOICE"<<endl;
    char choice;
    cin>>choice;
    char admin_password[50];
    switch(choice)
    {
	case '1':
			cout<<"ENTER PASSWORD"<<endl;
			int admin_attempts=3;
			while(admin_attempts>0)
			{
			admin_attempts--;
			password(admin_password);
			if(strcmp(admin_password,"bookstore123")==0)
			{
			    admin(); //calls admin function which handles all operations of admin
			    return;
			}
			else cout<<"\nINCORRECT PASSWORD : TRY AGAIN!"<<endl;
			}
		    if(admin_attempts==0)
		    {
			cout<<"ERROR : TOO MANY ATTEMPTS!"<<endl;
			getch();
			exit(0);
		    }
		    break;

	case '2':   long int phone;
		    char pass[40]; //temporary variable to store entered password
		    int attempts=3;
		    while(attempts>0)
		    {
			fstream fin("userdatabase.dat", ios::binary|ios::in|ios::out);
			if(!fin)
			{
				cout<<"ERROR IN OPENING FILE"<<endl;
				return;
			}
			cout<<"ENTER YOUR PHONE NUMBER  AND PASSWORD"<<endl;
			cout<<"PHONE NO :";
			cin>>phone;
			cout<<"PASSWORD :";
			password(pass);
			attempts--;
			while(fin.read((char*)&user1,sizeof(user1)))
			{
			    if((user1.get_phoneno()==phone) && strcmp(user1.get_password(),pass)==0)
			     {

					cout<<"\nSUCCESSFUL LOGIN! PRESS ANY KEY TO CONTINUE!"<<endl;
					loggedin_user=user1;
					getch();
					User();
					return;

			    }
			}
			cout<<"\nINCORRECT PHONE NUMBER  OR PASSWORD! TRY AGAIN!"<<endl;
			fin.close();
		    }//end of attempts loop
		    cout<<"TOO MANY ATTEMPTS! LOGIN FAILED!"<<endl;
		    getch();
    }
} // END OF LOGIN()

void signup()
{
	phone:
	fstream fin("userdatabase.dat",ios::binary | ios::in|ios::out);
	user o1;
	int invalid_ph=0;

	if(!fin)
	{
		cout<<"ERROR IN OPENING FILE"<<endl;
		return;
	}
	 user1.fill();
	 if(!fin)
	 {
		 cout<<"DATABASE NOT WORKING. TRY TO SIGN UP LATER."<<endl;
		 return;
	 }
	 while(fin.read((char*)&o1,sizeof(o1)))
	 {
		if(user1.get_phoneno()==o1.get_phoneno())
		{
			invalid_ph++;
			break;
		}
	 }
	 fin.close();
	 if(invalid_ph==0)
	 {
		ofstream fout("userdatabase.dat", ios::binary | ios::app);
		user1.setcart();
		fout.write((char*)&user1,sizeof(user1));
		fout.close();
		cout<<"\nDATA SUCCESSFULLY SAVED"<<endl;
	 }
	 else
	 {
		     cout<<"PHONE NUMBER ALREADY REGISTERED. TRY AGAIN!"<<endl;
		     goto phone;
	 }

}//end of signup

void admin()
{
    cout<<"\t\t\t\tBOOK MENU"<<endl;
    do {
	clrscr();
	cout<<"\t\t\t\tWELCOME BOSS!!"<<endl;
	cout<<"1.ADD BOOK "<<endl;
	cout<<"2.DELETE BOOK"<<endl;
	cout<<"3.MODIFY BOOK DETAILS"<<endl;
	cout<<"4.VIEW RATING"<<endl;
	cout<<"5.VIEW BOOKS"<<endl;
	cout<<"6.VIEW USER ORDERS"<<endl;
	cout<<"7.LOG OUT"<<endl;
	int ch;
	cout<<"ENTER CHOICE"<<endl;
	cin>>ch;
	switch(ch) {
	    case 1:
	    {
			add_book();
			getch();
			break;
	    }
	    case 2:
	    {
			delete_book();
			getch();
			break;
	    }
	    case 3:
	    {
			modify();
			getch();
			break;
	    }
	    case 4:
	    {
			view_rating();
			getch();
			break;
	    }
	    case 5:
	    {
			display_books();
			getch();
			break;
	    }
	    case 6: {
			display_orders(1);
			getch();
			break;
	    }
	    case 7:
	    {
		     char choice;
		     cout<<"ARE YOU SURE YOU WANT TO LOG OUT? (Y OR N)"<<endl;
		     label:
		     cin>>choice;
		     if(choice=='y' || choice=='Y')
		     {
				return;
		     }
		     else if(choice=='n'|| choice=='N')
		     {
				break;
		     }
		     else
		     {
			cout<<"WRONG CHOICE! - TRY AGAIN"<<endl;
			goto label;
		     }
	    }
	    default:
	    {
			cout<<"WRONG CHOICE"<<endl;
			getch();
	    }
	}
    } while(1);
} // end of admin()

void User()
{
    do {
	clrscr();
	cout<<"\t\t\t\t \t  WELCOME !"<<endl;
	cout<<"\t\t\t\t WHAT WOULD YOU LIKE TO DO??"<<endl;
	cout<<"1.BUY BOOK "<<endl;
	cout<<"2.DISPLAY BOOKS"<<endl;
	cout<<"3.VIEW CART"<<endl;
	cout<<"4.TRACK YOUR ORDERS"<<endl;
	cout<<"5.RATE A BOOK"<<endl;
	cout<<"6.DISPLAY PREVIOUS ORDERS"<<endl;
	cout<<"7.LOG OUT"<<endl;
	int ch;
	cout<<"ENTER CHOICE"<<endl;
	cin>>ch;//for user menu
	switch(ch) {
	    case 1:     clrscr();
			buy_book();
			getch();
			break;
	    case 2:     display_books();
			getch();
			break;
	    case 3:     view_cart();
			getch();
			break;
	    case 4:     track_orders();
			getch();
			break;
	    case 5:     rate_book();
			getch();
			break;
	    case 6: 	display_orders();
			getch();
			break;
	    case 7:     write_data();
			return;
	    default:    cout<<"WRONG CHOICE"<<endl;
			getch();
	}
    } while(1);
} //end of User()

void rate_book()
{
	char name[50];//book name to be rated
	int rating;
	fstream fin("book.dat",ios::binary|ios::in);
	fstream fout("temp.dat",ios::binary|ios::out);
	if(!fin||!fout)
	{
		cout<<"ERROR IN OPENING FILE"<<endl;
		return;
	}
	cout<<"ENTER THE NAME OF THE BOOK YOU WANT TO RATE"<<endl;
	gets(name);
	while(fin.read((char*)&b1,sizeof(b1)))
	{
		if(strcmpi(b1.get_bookname(),name)==0)
		{
			if(b1.get_rating()==0)
			{
				cout<<"BE THE FIRST TO RATE THIS BOOK!"<<endl;
			}
			do{
				cout<<"ENTER RATING"<<endl;
				cin>>rating;
				if(rating >5)
				{
				   cout<<"INVALID RATING.ENTER A RATING BELOW 5"<<endl;
				}
				else
				{
					cout<<"THANK YOU FOR RATING!"<<endl;
				}
			}while(rating > 5);
			b1.rating1(rating);
		}
		fout.write((char*)&b1,sizeof(b1));
	}
	fin.close();
	fout.close();
	remove("book.dat");
	rename("temp.dat","book.dat");
}

void write_data()
{
	fstream fin("userdatabase.dat",ios::binary|ios::in);
	fstream fout("temp.dat",ios::binary|ios::out);
	if(!fin||!fout)
	{
		cout<<"ERROR IN OPENING FILE"<<endl;
		return;
	}
	while(fin.read((char*)&user1,sizeof(user1)))
	{
		if(user1.get_phoneno()==loggedin_user.get_phoneno())
		{
		    user1=loggedin_user;
		}
		fout.write((char*)&user1,sizeof(user1));
	}
	fin.close();
	fout.close();
	remove("userdatabase.dat");
	rename("temp.dat","userdatabase.dat");
}

void add_book()
{
    int flag=0;
    fstream fin1("book.dat",ios::binary|ios::in);
    fstream fout("temp.dat",ios::binary|ios::out);
    cout<<"\nENTER DATA :";
    b2.fill();
    if(!fout) {
	cout<<"ERROR OPENING FILE"<<endl;
	return;
    }

    //following is adding book in sorted alphabetical order
    while(fin1.read((char*)&b1,sizeof(b1))) {
	if(strcmp(b1.get_bookname(),b2.get_bookname())<0)
	    fout.write((char*)&b1,sizeof(b1));
	else {
	    flag++;
	    fout.write((char*)&b2,sizeof(b2));
	    fout.write((char*)&b1,sizeof(b1));
	    break;
	}
    }
    while(fin1.read((char*)&b1,sizeof(b1))) {
	fout.write((char*)&b1,sizeof(b1));
    }
    if(flag==0)
	fout.write((char*)&b2,sizeof(b2));
    fin1.close();
    fout.close();
    cout<<"BOOK ADDED"<<endl;
    remove("book.dat");
    rename("temp.dat","book.dat");
} //end of add_book()

void delete_book()
{
    int flag=0,foundbook=0;
    char name[50];//book name to be deleted
    fstream fin1("book.dat",ios::binary|ios::in);
    fstream fout("temp.dat",ios::binary|ios::out);
    if(!fin1||!fout) {
	cout<<"THERE ARE NO BOOKS TO BE DELETED."<<endl;
	return ;
    }
    cout<<"ENTER THE NAME OF THE BOOK YOU WANT TO DELETE"<<endl;
    gets(name);
    while(fin1.read((char*)&b1,sizeof(b1))) {
	if(strcmp(b1.get_bookname(),name)==0) {
	    foundbook=1;
	    flag++;
	    cout<<"THE BOOK BEING DELETED IS :"<<endl;
	    b1.display();
	    continue;
	}
	fout.write((char*)&b1,sizeof(b1));
    }
    if(!foundbook)
    {
	cout<<"BOOK NOT FOUND"<<endl;
    }
    fin1.close();
    fout.close();
    remove("book.dat");
    rename("temp.dat","book.dat");
} //end of delete_book()

void display_books()
{ //display books in chosen sorted order
    cout<<"1.DISPLAY IN ALPHABETICAL ORDER"<<endl;
    cout<<"2.DISPLAY IN ORDER OF RATING"<<endl;
    cout<<"3.DISPLAY BY CATEGORY"<<endl;
    int ch;//choice
    cin>>ch;
    fstream fin1("book.dat", ios::binary | ios::in);
    if(!fin1)
    {
	cout<<"Error in accessing books!"<<endl;
	return;
    }
    int count=0;
    while(fin1.read((char*)&b1,sizeof(b1)))
    {
	 count=1;//to check if empty
    }
    fin1.close();
    fin1.open("book.dat",ios::binary|ios::in);
    if(!count)//when file exists but there are no books
    {
	cout<<"NO BOOKS IN STORE"<<endl;
	return;
    }

    switch(ch) {

	case 1:
	cout<<setw(10)<<"|BOOK NAME "<<setw(10)<<" |COST Rs.  "<<setw(10)<<"|QUANTITY |"<<endl;
	while(fin1.read((char*)&b1,sizeof(b1)))
	{
			cout<<setw(10)<<b1.get_bookname()<<setw(10)<<b1.get_cost()<<setw(10)<<b1.get_quantity();
			if(b1.get_rating()==0)
				cout<<endl<<"THERE ARE NO USER RATINGS TO DISPLAY.";
			else
			{
				int stars=b1.get_rating();
				cout<<endl<<"USER RATING (rated by "<<b1.get_total_ratings()<<" user): ";
				for(int k=1;k<=stars;k++)
					cout<<"*";
			}
			cout<<endl;
		    }
		    fin1.close();
		    break;
	case 2:     while(fin1.read((char*)&b1,sizeof(b1)))
	{
			if(b1.get_rating()==5)
			{
			    cout<<b1.get_bookname()<<"(*****)"<<" Rs : "<<b1.get_cost()<<" Quantity : "<<b1.get_quantity();
			    cout<<endl;
			}
		    }
		    fin1.close();
		    fstream fin2("book.dat", ios::binary | ios::in);
		    while(fin2.read((char*)&b1,sizeof(b1)))
		    {
			if(b1.get_rating()==4)
			{
			    cout<<b1.get_bookname()<<"(****)"<<" Rs : "<<b1.get_cost()<<" Quantity : "<<b1.get_quantity();
			    cout<<endl;
			}
		    }
		    fin2.close();
		    fstream fin3("book.dat", ios::binary | ios::in);
		    while(fin3.read((char*)&b1,sizeof(b1)))
		    {
			if(b1.get_rating()==3)
			{
			    cout<<b1.get_bookname()<<"(***)"<<" Rs :"<<b1.get_cost()<<" Quantity : "<<b1.get_quantity();
			    cout<<endl;
			}
		    }
		    fin3.close();
		    fstream fin4("book.dat", ios::binary | ios::in);
		    while(fin4.read((char*)&b1,sizeof(b1)))
		    {
			if(b1.get_rating()==2)
			{
			    cout<<b1.get_bookname()<<"(**)"<<" Rs : "<<b1.get_cost()<<" Quantity : "<<b1.get_quantity();
			    cout<<endl;
			}
		    }
		    fin4.close();
		    fstream fin5("book.dat", ios::binary | ios::in);
		    while(fin5.read((char*)&b1,sizeof(b1)))
		    {
			if(b1.get_rating()==1)
			{
			    cout<<b1.get_bookname()<<"(*)"<<" Rs  : "<<b1.get_cost()<<" Quantity : "<<b1.get_quantity();
			    cout<<endl;
			}
		    }
		    fin5.close();
		    fstream fin6("book.dat", ios::binary | ios::in);

		    while(fin6.read((char*)&b1,sizeof(b1)))
		    {
			if(b1.get_rating()==0)
			{
			    cout<<b1.get_bookname()<<" (NOT YET RATED) "<<" Rs : "<<b1.get_cost()<<" Quantity  : "<<b1.get_quantity();
			    cout<<endl;
			}
		    }
		    fin6.close();
		    break;
	case 3:
	{
	int category_ch;
	int count_fiction=0;
	int count_nonfiction=0;
	int count_edu=0;
	int count_sh=0;
	int count_other=0;
	cout<<"ENTER CATEGORY YOU WISH TO LOOK FOR: \n1.FICTION \n2.NON-FICTION \n3.EDUCATION \n4.SELF HELP \n5.OTHER"<<endl;
	cin>>category_ch; //category_ch is a variable for storing user's choice
	switch(category_ch)
	{
		case 1:
		{
			cout<<"CATEGORY: FICTION"<<endl;
			fstream book_by_category("book.dat",ios::binary | ios::in);
			if(!book_by_category)
			{
				cout<<"ERROR IN DISPLAYING BOOKS."<<endl;
				break;
			}
			while(book_by_category.read((char*)&b1,sizeof(b1)))
			{
				if(strcmpi(b1.get_category(),"FICTION")==0)
				{
					cout<<"BOOK NAME :"<<b1.get_bookname()<<"  : "<<"RS. "<<b1.get_cost()<<" : "<<"QUANTITY "<<b1.get_quantity();
					count_fiction++;
					if(b1.get_rating()==0)
					cout<<endl<<"THERE ARE NO USER RATINGS TO DISPLAY.";
					else
					{
						int stars=b1.get_rating();
						cout<<endl<<"USER RATING (rated by "<<b1.get_total_ratings()<<" user): ";
						for(int k=1;k<=stars;k++)
						cout<<"*";
					}
					cout<<endl;
				 }
			}
			if(count_fiction==0)
			{
				cout<<"NO FICTION BOOKS."<<endl;
			}
			book_by_category.close();
			break;
	  }
	  case 2:
		{
			cout<<"CATEGORY:NON FICTION"<<endl;
			fstream book_by_category("book.dat",ios::binary | ios::in);
			if(!book_by_category)
			{
				cout<<"ERROR IN DISPLAYING BOOKS."<<endl;
				break;
			}
			while(book_by_category.read((char*)&b1,sizeof(b1)))
			{
				if(strcmpi(b1.get_category(),"NON FICTION")==0)
				{
					cout<<"BOOK NAME :"<<b1.get_bookname()<<"  : "<<"RS. "<<b1.get_cost()<<" : "<<"QUANTITY "<<b1.get_quantity();
					count_nonfiction++;
					if(b1.get_rating()==0)
					cout<<endl<<"THERE ARE NO USER RATINGS TO DISPLAY.";
					else
					{
						int stars=b1.get_rating();
						cout<<endl<<"USER RATING (rated by "<<b1.get_total_ratings()<<" user): ";
						for(int k=1;k<=stars;k++)
						cout<<"*";
					}
					cout<<endl;
				  }
			}
			if(count_nonfiction==0)
			{
				cout<<"NO NON FICTION BOOKS."<<endl;
			}
			book_by_category.close();
			break;
	  }
	  case 3:
		{
			cout<<"CATEGORY: EDUCATION"<<endl;
			fstream book_by_category("book.dat",ios::binary | ios::in);
			if(!book_by_category)
			{
				cout<<"ERROR IN DISPLAYING BOOKS."<<endl;
				break;
			}
			while(book_by_category.read((char*)&b1,sizeof(b1)))
			{
				if(strcmpi(b1.get_category(),"EDUCATION")==0)
				{
					cout<<"BOOK NAME :"<<b1.get_bookname()<<"  : "<<"RS. "<<b1.get_cost()<<" : "<<"QUANTITY "<<b1.get_quantity();
					count_edu++;
					if(b1.get_rating()==0)
					cout<<endl<<"THERE ARE NO USER RATINGS TO DISPLAY.";
					else
					{
						int stars=b1.get_rating();
						cout<<endl<<"USER RATING (rated by "<<b1.get_total_ratings()<<" user): ";
						for(int k=1;k<=stars;k++)
						cout<<"*";
					}
					cout<<endl;
				    }
			}
			if(count_edu==0)
			{
				cout<<"NO EDUCATION BOOKS."<<endl;
			}
			book_by_category.close();
			break;
	  }
	  case 4:
		{
			cout<<"CATEGORY: SELF HELP"<<endl;
			fstream book_by_category("book.dat",ios::binary | ios::in);
			if(!book_by_category)
			{
				cout<<"ERROR IN DISPLAYING BOOKS."<<endl;
				break;
			}
			while(book_by_category.read((char*)&b1,sizeof(b1)))
			{
				if(strcmpi(b1.get_category(),"FICTION")==0)
				{
					cout<<"BOOK NAME :"<<b1.get_bookname()<<"  : "<<"RS. "<<b1.get_cost()<<" : "<<"QUANTITY "<<b1.get_quantity();
					count_sh++;
					if(b1.get_rating()==0)
					cout<<endl<<"THERE ARE NO USER RATINGS TO DISPLAY.";
					else
					{
						int stars=b1.get_rating();
						cout<<endl<<"USER RATING (rated by "<<b1.get_total_ratings()<<" user): ";
						for(int k=1;k<=stars;k++)
						cout<<"*";
					}
					cout<<endl;

				}
			}
			if(count_sh==0)
			{
				cout<<"NO SELF HELP BOOKS."<<endl;
			}
			book_by_category.close();
			break;
	  }
	  case 5:
		{
			cout<<"CATEGORY: OTHER"<<endl;
			fstream book_by_category("book.dat",ios::binary | ios::in);
			if(!book_by_category)
			{
				cout<<"ERROR IN DISPLAYING BOOKS."<<endl;
				break;
			}
			while(book_by_category.read((char*)&b1,sizeof(b1)))
			{
				if(strcmpi(b1.get_category(),"OTHER")==0)
				{
					cout<<"BOOK NAME :"<<b1.get_bookname()<<"  : "<<"RS. "<<b1.get_cost()<<" : "<<"QUANTITY "<<b1.get_quantity();
					count_other++;
					if(b1.get_rating()==0)
					cout<<endl<<"THERE ARE NO USER RATINGS TO DISPLAY.";
					else
					{
						int stars=b1.get_rating();
						cout<<endl<<"USER RATING (rated by "<<b1.get_total_ratings()<<" user): ";
						for(int k=1;k<=stars;k++)
						cout<<"*";
					}
					cout<<endl;
			       }
			}
			if(count_other==0)
			{
				cout<<"NO OTHER BOOKS."<<endl;
			}
			book_by_category.close();
			break;
	  }
	  default:
	  cout<<"THIS CATEGORY DOES NOT EXIST."<<endl;
	 }
	 break;
	 default:
	 cout<<"WRONG CATEGORY."<<endl;
	}
     }
}
void modify()
{
    char name[50];//book name to be modified
    book tempBook;
    int flag = 0,foundbook=0;
    fstream fin1("book.dat",ios::binary|ios::in);
    fstream fout("temp.dat",ios::binary|ios::out);
    if(!fin1||!fout) {
	cout<<"THERE ARE NO BOOKS TO BE MODIFIED."<<endl;
	return;
    }
    cout<<"ENTER THE NAME OF THE BOOK YOU WANT TO MODIFY"<<endl;
    gets(name);
    while(fin1.read((char*)&tempBook,sizeof(tempBook)))
    {
	if(strcmpi(tempBook.get_bookname(), name)==0)
	{
		foundbook=1;
	    do {
		cout<<"MODIFY MENU "<<endl;
		cout<<"1.AUTHOR"<<endl;
		cout<<"2.DESCRIPTION"<<endl;
		cout<<"3.COST"<<endl;
		cout<<"4.QUANTITY"<<endl;
		cout<<"5.BOOK NAME"<<endl;
		cout<<"6.BACK TO PREVIOUS MENU"<<endl;
		char ch;
		cout<<"ENTER CHOICE"<<endl;
		cin>>ch;
		switch(ch) {

		    case '1':     tempBook.set_author();
				break;
		    case '2':     tempBook.set_description();
				break;
		    case '3':     tempBook.set_cost();
				break;
		    case '4':     tempBook.set_quantity();
				break;
		    case '5':	  tempBook.set_name();
				break;
		    case '6':     flag++;
				break;
		    default:    cout<<"WRONG CHOICE"<<endl;
		}
	    } while(flag==0);
	}
	fout.write((char*)&tempBook,sizeof(tempBook));
    }
    if(!foundbook)
    {
	cout<<"BOOK NOT FOUND"<<endl;
    }
    fin1.close();
    fout.close();
    remove("book.dat");
    rename("temp.dat","book.dat");
} //end of modify()   */

void view_rating()
{ //admin function
    char bookname[50];
    cout<<"ENTER THE NAME OF THE BOOK YOU WANT TO VIEW RATING ABOUT"<<endl;
    gets(bookname);
    fstream fin1("book.dat",ios::binary|ios::in);
    if(!fin1)
    {
	cout<<"THERE ARE NO BOOKS TO VIEW THE RATINGS OF"<<endl;
	return;
    }
    int foundbook=0;
    while(fin1.read((char*)&b1,sizeof(b1)))
    {
	if(strcmp(b1.get_bookname(),bookname)==0)
	{
	 if(b1.get_rating()==0)
	 {
		cout<<"BOOK HAS NOT YET BEEN RATED"<<endl;
	 }
	 else
	 {
		cout<<"THE RATING OF THE BOOK IS : "<<b1.get_rating()<<" OUT OF  5 "<<endl;
	 }
	 foundbook=1;
	}
    }
    if(!foundbook)
    {
	cout<<"BOOK NOT FOUND"<<endl;
    }
    fin1.close();
}

void decrease_book_quantity(cart_item item)
{
    fstream fin("book.dat",ios::binary|ios::in|ios::out);
    if(!fin)
    {
	cout<<"ERROR!"<<endl;
	return;
    }
    while(fin.read((char*)&b1,sizeof(b1)))
    {
	if(strcmp(b1.get_bookname(),item.bookname)==0)
	{
	    int temp_qty = b1.get_quantity() - (item.quantity);
	    b1.set_quantity(temp_qty);
	}
	fin.seekp(fin.tellp()-1*sizeof(b1));
	fin.write((char*)&b1,sizeof(b1));
    }
}

void buy_book()
{
    if(user1.get_cart_items()==10)
    {
	cout<<"CART FULL!\n";
	return;
    }
    char searched_book[100];
    int req_quantity;
    int flag = -1; //for searching book
    char choice1;
    cout<<"\t\t\t\t\"BUY BOOK\""<<endl;
    cout<<"\nWHICH BOOK ARE YOU LOOKING FOR?"<<endl;
    gets(searched_book);
    fstream fin1("book.dat", ios::in | ios::binary);
    if(!fin1) {
	cout<<"ERROR IN OPENING FILE."<<endl;
    }
    while(fin1.read((char*)&b1,sizeof(b1)))
     {
	if((strcmp(b1.get_bookname(),searched_book)) == 0 && b1.get_quantity() > 0)
	{
	    flag = 1;
	    cout<<searched_book<<" IS IN STORE"<<endl;
	    cout<<"DETAILS OF THE BOOK: "<<endl;
	    b1.display();
	    if(b1.get_quantity() < 5)
	    {
		cout<<"\n\tBUY SOON! BEFORE IT GOES OUT OF STOCK."<<endl;
	    }
	    cout<<"TO BUY THIS BOOK, PRESS Y"<<endl;
	    cin>>choice1;
	    if(choice1 == 'y' || choice1 == 'Y')
	    {
		strcpy(item.bookname,searched_book);
		int req_quantity;
		do {
		    cout<<"ENTER QUANTITY:"<<endl;
		    cin>>req_quantity;
		    if(b1.get_quantity()<req_quantity)
			cout<<"ENTERED QUANTITY IS GREATER THAN THE CURRENT AVAILABLE STOCK. TRY AGAIN.";
		    else
		    {   book o1;
			fstream fin("book.dat",ios::binary|ios::in);
			fstream fout("B.dat",ios::binary|ios::out|ios::app);
			if(!fout||!fin)
			   {
				cout<<"BOOK DATABASE NOT WORKING. PLEASE TRY TO ADD ITEMS LATER.";
				return;
			   }
			   while(fin.read((char*)&o1,sizeof(o1)))
			    {
				if(strcmp(o1.get_bookname(),searched_book)==0)
				{
					o1.newquantity("cart_add",req_quantity);
					fout.write((char *)&o1,sizeof(o1));
				}
				else
				fout.write((char*)&o1,sizeof(o1));
			    }
			    fin.close();
			    fout.close();
			    remove("book.dat");
			    rename("B.dat","book.dat");
		    }
		} while(b1.get_quantity()<req_quantity || req_quantity<=0);
		item.quantity=req_quantity;
		item.cost=b1.get_cost();
		//b1.decrease_quantity(item);
		add_to_cart(); //passes the book to the cart
	    }
	    else
		return;
	}
	else if(b1.get_quantity()==0 && flag ==0)
	{
		cout<<"WE'RE SORRY! BOOK OUT OF STOCK"<<endl;
		flag=0;
	}
    }
    clrscr();
    if(flag == -1)
    {
	cout<<"BOOK NOT FOUND\n";
    }
    fin1.close();

    cout<<"\nWANT TO SEARCH FOR ANOTHER BOOK? \nPRESS 'Y' TO CONTINUE OR PRESS 'N' TO LEAVE."<<endl;
    char choice2;
    label:
    cin>>choice2;
    if(choice2 == 'Y' || choice2 == 'y')
    {
	buy_book();
    }
    else if(choice2 == 'N' || choice2 =='n')
    {
	return;
    }
    else
    {
	cout<<"\tWRONG CHOICE"<<endl;
	cout<<"PLEASE ENTER AGAIN!"<<endl;
	goto label;
    }
    //fin1.close();
}

void main()
{ //main function
    clrscr();
    char option; //for login
    do {
	clrscr();
	cout<<"\t\t\t\tAUTHOR'S ATTIC "<<endl;
	cout<<"\t\t\t\t---------------"<<endl;
	cout<<"\t\t\t\t   WELCOME!"<<endl;
	cout<<"1.LOGIN\n2.SIGNUP\n3.EXIT"<<endl;
	cin>>option;
	switch(option) {
	    case '1':
			login();
			break;
	    case '2':
			signup();
			break;
	    case '3':
			exit(0);
	    default:
			cout<<"PLEASE ENTER A CORRECT OPTION."<<endl;
			break;
	}
    } while(1); //do while loop ends here
} //end of main


