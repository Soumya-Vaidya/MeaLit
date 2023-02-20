#include <iostream>
#include <regex>  //login testcases
#include "input.hpp" //to mask the password
#include<fstream> 
#include<stdio.h>
#include <string.h>
#include <iostream> 
#include <typeinfo>  //to check var type
#include <vector>
#include <cstdio>
#include<bits/stdc++.h>
#include <algorithm>

using namespace std;
class restaurant;
class customer
{
  string name, email, phone, address, password;
  public:
  int flag = true;
  void Register()
  {
    int f1 = true, f2 = true, f3 = true;
    cout << endl << "REGISTRATION" << endl;
    cout << "Name: ";
    getline(cin >> ws, name);
    while (f1)
    {
      cout << "Email: ";
      cin >> email;
      const regex pattern1("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
      if(regex_match(email, pattern1))
      {
        f1 = false;
        break;
      }
      else
      {
        cout << "Invalid Email-Id." << endl;
      }
    }
    while (f2)
    {
      const regex pattern2("(0|91)?[7-9][0-9]{9}");
      cout << "Phone Number: ";
      cin >> phone;
      if(regex_match(phone, pattern2))
      {
        f2 = false;
        break;
      }
      else
      {
        cout << "Invalid Phone Number." << endl;
      }
    }
    cout << "Address: ";
    getline(cin>>ws,address);
    while(f3)
    {
      cout << "Password: ";
      cin >> password;
      bool hasLower = false, hasUpper = false;
      bool hasDigit = false, specialChar = false;
      string normalChars = "abcdefghijklmnopqrstu" "vwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890 ";
      for (int i = 0; i < password.length(); i++) 
      {
        if (islower(password[i]))
          hasLower = true;
        if (isupper(password[i]))
          hasUpper = true;
        if (isdigit(password[i]))
          hasDigit = true;
        size_t special = password.find_first_not_of(normalChars);
        if (special != string::npos)
          specialChar = true;
      }
      if (hasDigit == true && hasLower == true && hasUpper == true && specialChar == true && password.length() > 6 && password.length() < 15)
      {
        f3 = false;
        cout<<endl<<"You have been registered sucessfully!"<<endl<<"Proceed to Login with the registered phone number."<< endl;
        break;
      }
      else
      {
        cout << "Invalid Password." << endl;
        cout<<"Password should have a length of 7 characters and atmax 15 characters. It should also contain uppercase characters, lowercase characters, digits and special characters."<<endl;
      }
    }
    details(name, phone, password);
  }

  void details(string name, string phone, string password)
  {
    ofstream file;
    file.open("database/customer.txt" , ios::app);
    vector <string> details;
    {
      details.push_back(name);
      details.push_back(phone);
      details.push_back(password);
    }
    for(string i:details)
    {
      file << i << endl;
    }
    file.close();
  }

  int login()
  {
    string no;
    cout << endl << "LOGIN" << endl;
    cout<<"Enter Phone Number: ";
    cin>>no;
    g:
    char c=' ';
    string pass="";
    cout<<"Enter Password: ";
    while(c!=10)
    {
      c=getch();
      if(c!=10)
      {
        pass=pass+c;
        cout<<"*";
      }
    }

    ifstream op("database/customer.txt");
    if(!op.is_open()) std::cout << "ERROR: File Open" <<endl;
    cout<<endl<< "----------------------"<<endl;
    string name1, phone1, password1, name;
    int w=0;
    while(op.peek()!=EOF)
    {
      getline(op, name1);
      getline(op, phone1);
      getline(op, password1);
      if(phone1 == no)
      {
        phone = phone1;
        password = password1;
        name = name1;
        //w=1;
      }
    }
    if(no!=phone&&pass!=password)
    {
      cout<<endl<<"The phone number and password entered are not registered on system. Please enter the information again."<<endl;
      login();
    }
    else if(no!=phone&&pass==password)
    {
      cout<<endl<<"The phone number entered is not registered on system. Please enter the information again."<<endl;
      login();
    }
    else if(no==phone&&pass!=password)
    {
      cout<<endl <<"The password entered is invalid. Please enter the information again."<<endl;
      goto g;
    }
    else
    {
      cout<<endl<<endl<<"Log-in Successful!"<<endl;
      cout<<"Welcome to MeaLit, "<<name<<"!"<<endl<<endl;
    }
    return 1;
  }
  /*  
  void orderhist()
  {
    string rest1, item1, quantity1, price1;
    ifstream op("database/orderhistory.txt");
    if(!op.is_open()) std::cout << "ERROR: File Open" <<endl;
    cout<<endl<< "----------------------"<<endl;
    while(op.peek()!=EOF)
    {
      //char*output;
      //if(output  == '*')
      getline(op, rest1);
      getline(op, item1);
      getline(op, price1);
      getline(op, quantity1);
      cout << rest1 << endl;
      cout << item1 << endl;
      cout <<price1 << endl;
      cout<<endl;
    }
    op.close();
  }
  */
};

class restaurant
{
  string id, rname, add, cuisine, veg, cost, delivery, stars, rating, votes;
  public:
  void retrieve(ifstream& ip)
  {
    getline(ip,id,',');
    getline(ip,rname,',');
    getline(ip,add,',');
    getline(ip,cuisine,',');
    getline(ip,veg,',');
    getline(ip,cost,',');
    getline(ip,delivery,',');
    getline(ip,stars,',');
    getline(ip,rating,',');
    getline(ip,votes,'\n');
  }
  
  void display()
  {
    int i=0; //so that we get the display from 2nd row of database
    ifstream ip("database/RestaurantDatabase.csv"); //ip is object of file
    if(!ip.is_open()) std::cout << "ERROR: File Open" <<endl;
    while(ip.peek()!=EOF) //runs until we reach end of file
    {
      retrieve(ip);
      if(i!=0)
      {
        cout<<"Restaurant Name: "<<rname<<endl;
        cout<<"Address: "<<add<<endl;
        cout<<"Cuisine: "<<cuisine<<endl;
        cout<<"Veg: "<<veg<<endl;
        cout<<"Average Cost: Rs."<<cost<<"/-"<<endl;
        cout<<"Delivering Now: "<<delivery<<endl;
        cout<<"Stars: "<<stars<<endl;
        cout<<"Rating: "<<rating<<endl;
        cout<<"Votes: "<<votes<<endl;
        cout<< "-------------------"<<endl;
      }
      i = i+1;
  }
  ip.close();
  }

  void search()
  {
    ifstream ip("database/RestaurantDatabase.csv");
    if(!ip.is_open()) std::cout << "ERROR: File Open" <<endl;

    int a;
    string n;
    cout << endl << "Search by:" << endl << "1. Name of Restaurant" <<endl << "2. Cuisine" << endl;
    cin >> a;
    while(a !=1 && a!=2)
    {
      cout<<"Value entered is invalid. Please enter again:"<<endl;
      cin >> a;
    }
    if(a==1)
    {
      enter_rname:
      ifstream ip("database/RestaurantDatabase.csv");
      cout << endl << "Enter Restaurant Name: "<< endl;
      int f=0;
      getline(cin>>ws,n);
      transform(n.begin(), n.end(), n.begin(), ::tolower);
      while(ip.peek()!=EOF)
      {
        retrieve(ip);
        string temp=rname;
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        if(temp == n)
        {
          f=1;
          cout<<endl<<"Restaurant Name: "<<rname<<endl;
          cout<<"Address: "<<add<<endl;
          cout<<"Cuisine: "<<cuisine<<endl;
          cout<<"Veg: "<<veg<<endl;
          cout<<"Average Cost: Rs."<<cost<<"/-"<<endl;
          cout<<"Delivering Now: "<<delivery<<endl;
          cout<<"Stars: "<<stars<<endl;
          cout<<"Rating: "<<rating<<endl;
          cout<<"Votes: "<<votes<<endl;
          cout<< "-------------------"<<endl;
          break;
        }
      }
      if(f==0)
      {
        cout<<"Sorry! No results found for this restaurant. Please try for another place."<<endl<<endl;
        goto enter_rname;
      }
    }
    if(a==2)
    {
      enter_cuisine:
      ifstream ip("database/RestaurantDatabase.csv");
      cout << endl << "Enter Cuisine: "<< endl;
      int f=0;
      getline(cin>>ws,n);
      transform(n.begin(), n.end(), n.begin(), ::tolower);
      while(ip.peek()!=EOF)
      {
        retrieve(ip);
        string c=cuisine;
        stringstream iss(c);
        while(iss>>c)
        {
          transform(c.begin(), c.end(), c.begin(), ::tolower);
          if(c == n)
          {
            f=1;
            cout<<endl<<"Restaurant Name: "<<rname<<endl;
            cout<<"Address: "<<add<<endl;
            cout<<"Cuisine: "<<cuisine<<endl;
            cout<<"Veg: "<<veg<<endl;
            cout<<"Average Cost: Rs."<<cost<<"/-"<<endl;
            cout<<"Delivering Now: "<<delivery<<endl;
            cout<<"Stars: "<<stars<<endl;
            cout<<"Rating: "<<rating<<endl;
            cout<<"Votes: "<<votes<<endl;
            cout<< "-------------------"<<endl;
            break;
          }
        }
      }
      if(f==0)
      {
        cout<<"Sorry! No results found for this cuisine. Please try for another cuisine."<<endl<<endl;
        goto enter_cuisine;
      }
    }
    ip.close();
  }
};


class order
{
  int total;
  string sno, name, price;
  public:
  int x=0; //to check for wrong serial number
  void retrieve(ifstream& ip)
  {
    getline(ip,sno,',');
    getline(ip,name,',');
    getline(ip,price,'\n');
  }
  
  void display(ifstream& ip)
  {
    while(ip.peek()!=EOF) //runs until we reach end of file
    {
      retrieve(ip);
      cout<<endl<<"Sr No: "<< sno << endl;
      cout<<"Name: " << name << endl;
      cout<<"Price: Rs. " <<price << endl;
      cout<< "-------------------"<<endl;
    }
    ip.close();
  }  

  void add()
  {
    int on,q;
    string n,b,m;
    char ch = 'y';
    g1:
    cout << endl<<"Enter Restaurant Name: "<< endl;
    b="";
    getline(cin >> ws, n);
    transform(n.begin(), n.end(), n.begin(), ::tolower);
    m=n;
    stringstream iss(n);
    while(iss>>n)
    {
      b=b+n;
    }
    b="database/"+b+".csv";
    ifstream ip(b); //ip iss
    if(!ip.is_open()) 
    {
      std::cout << "ERROR: File Open" <<endl;
      cout << "Sorry! No results found for this restaurant. Please try for another place." << endl;
      goto g1;
    }

    display(ip);
    
    while(ch=='Y' || ch == 'y')
    {
      select_serialno:
      //x=1;
      cout << endl<<"Select Serial Number: ";
      cin >> on; 
      cout<<"Select Quantity: ";
   	  cin >> q;
      ifstream jp(b);
      bill(on,q,jp);
      if(x == 0)
      {
        cout << "Wrong Serial Number! Try another option."<< endl;
        goto select_serialno;
      }
      cout <<endl<< "Do you wish to add something else: ";
      cin >> ch;
    }

    cout << endl << "Generating Bill..."<< endl;

    string item1, quantity1, price1;
    ifstream op("database/order.txt");
    if(!op.is_open()) std::cout << "ERROR: File Open" <<endl;
    cout<<endl<< "----------------------"<<endl;
    //cout << "Name               Quantity"<<  endl;
    cout <<endl << "Restaurant Name: " << m << endl << endl;
    while(op.peek()!=EOF)
    {
      getline(op, item1);
      getline(op, price1);
      getline(op, quantity1);
      cout<< item1<< "   x "<<quantity1 << endl;
      cout <<"Rs. " <<price1 << endl;
      cout<<endl;
    }
    cout << endl << "Total Bill: Rs. "<<total;
    cout << endl << "----------------------"<<endl;
    cout << endl << "Proceed to payment" << endl ;
    string line;
    
    ifstream ini_file {"database/order.txt"};
    ofstream out_file {"database/orderhistory.txt", ios::app};
 
    if(ini_file && out_file)
    {
      string  p = '*' + m;
      out_file <<p << "\n";
      while(getline(ini_file,line))
      {
        out_file << line << "\n";
      }
    } 
    else 
    {
      printf("Cannot read File");
    }
    ini_file.close();
    out_file.close();
    
    op.close();
    ofstream file;
    file.open("database/order.txt");
    file.close();
  }

  void bill(int p, int q, ifstream& jp)
  {
    ofstream file;
    file.open("database/order.txt",ios::app);
    vector <string> food;
    string quan = to_string(q);
    while(jp.peek()!=EOF)
    {
      retrieve(jp);
      if(p == stoi(sno))
      {
        x=1;
        food.push_back(name);
        food.push_back(price);
        food.push_back(quan);
        total = total + (stof(price) * q);
      }
    }
    for(string i:food)
    {
      file << i << endl;
    }
    jp.close();
    file.close();
  }
  
};

int main() 
{
  customer obj1;
  restaurant obj2;
  order obj3;
  bool flag1 = true;
  bool flag2 = true;
  int c=0,success=0,x, a;
  cout << endl<<"Welcome to MeaLit!"<<endl<<endl;
  cout<<"Do you wish to:\n1. Register\n2. Login\n";
  cin>>c;
  while(c!=1&&c!=2)
  {
    cout<<"Value entered is invalid. Please enter again:"<<endl;
    cin>>c;
  }
  if(c==1)
  {
    obj1.Register();
    success=obj1.login();
  }
  else //c=2
  success=obj1.login();
  if(success==1)
  {
    home:
    cout<<endl<<"-------Home Page-------"<<endl <<endl;
    cout<<"1. View List of Restaurants"<<endl;
    cout<<"2. Search for a Restaurant" << endl;
    cout<<"3. View Cart (Upcoming!)"<<endl;
    cout<<"4. View Order History"<<endl;
    cout<<"5. View Profile (Upcoming!)"<<endl;
    cout<<endl<<"-----------------------"<<endl;
    cout<<endl<<"Enter Choice: ";
    cin>>x;
    cout<<endl;
    switch(x)
    {
      case 1:
      obj2.display();
      while (flag2 == true)
      {
        cout << endl<<"Do you wish to:" <<endl <<"1. Select Restaurant"<< endl << "2. Browse for something else"<< endl;
        cin >> a;
        while(a!=1 && a!=2)
        {
          cout<<"Invalid Choice!. Please enter again:"<<endl;
          cin>>a;
        }
        if(a==1)
        {
          obj3.add();
          flag2 = false;
        }
        else if(a==2)
        {
          obj2.search();
        }
        //break;
      }
      break;
      case 2:
      obj2.search();
      while (flag2 == true)
      {
        cout << endl<<"Do you wish to:" <<endl <<"1. Select Restaurant"<< endl << "2. Browse for something else"<< endl;
        cin >> a;
        while(a!=1 && a!=2)
        {
          cout<<"Invalid Choice!. Please enter again:"<<endl;
          cin>>a;
        }
        if(a==1)
        {
          obj3.add();
          flag2 = false;
        }
        else if(a==2)
        {
          obj2.search();
        }
      }
      break;
      /*case 4:
      cout<<"Your Order History is as follows: "<<endl;
      obj1.orderhist();
      break;*/
      default:
      cout<<"Choice entered is not valid!"<<endl;
      goto home;
    }
  }
}