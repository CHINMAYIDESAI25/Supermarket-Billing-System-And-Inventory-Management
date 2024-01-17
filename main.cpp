#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <windows.h>

using namespace std;

class Customer_Details
{
protected :

  string name, contact_no, address, pay_method, bank_name;
  float amount = 0;

public :

  string readData()
  {
    cout << "Enter customer name : ";
    getline (cin >> ws, name);
    cout << "\nEnter customer contact no. : ";
    cin >> contact_no;
    cout << "\nEnter customer address : ";
    getline (cin >> ws, address);
    while (1)
    {
      cout << "\nPayment method" << endl;
      cout << "Enter   'OP' for Online payment\n\t'COD' for Cash On Delivery" << endl;
      cout << "Enter payment method : ";
      cin >> pay_method;
      if (pay_method == "OP" || pay_method == "op")
      {
        pay_method = "Online Payment";
        cout << "Enter bank name : ";
        cin >> bank_name;
        break;
      }
      else if (pay_method == "COD" || pay_method == "cod")
      {
        pay_method = "Cash On Delivery";
        break;
      }
      else
      {
        cout << "Please enter the correct choice!";
      }
    }
    return pay_method;
  }

  int selectCategory ()
  {
    int category;
    cout << "1 -> Beauty & Hygiene\n2 -> Beverages\n3 -> Dairy\n4 -> Fruits & Vegetables\n5 -> Snacks" << endl;
    cout << "Enter desired category : ";
    cin >> category;
    return category;
  }

  void displayData ()
  {
    cout << " CUSTOMER NAME : " << name << endl;
    cout << "|----------------------------------------|" << endl;
    cout << " CUSTOMER CONTACT NO. : " << contact_no << endl;
    cout << "|----------------------------------------|" << endl;
    cout << " CUSTOMER ADDRESS : " << address << endl;
    cout << "|----------------------------------------|" << endl;
    cout << " PAYMENT METHOD : " << pay_method << endl;
    cout << "|----------------------------------------|" << endl;
    if (pay_method == "Online Payment")
    {
      cout << " BANK NAME : " << bank_name << endl;
      cout << "|----------------------------------------|" << endl;
    }
    cout << "Item\tRate\tUnits\tCost" << endl;
    ifstream fin; //Sales.csv stores list of items selected by the customer
    string data;
    fin.open ("Sales.csv");
    while (fin.peek() != EOF)
    {
      getline (fin, data, ',');
      cout << data << "\t";
    }
    fin.close();
    int result = remove ("Sales.csv"); //Deletes the file Sales.csv after the bill has been displayed
  }
};

class Items : public Customer_Details
{
private :

  int choice, units_needed;

public :

  void update_record (string filename, map <int, string> item_list, int choice, int units_needed, int units_present[])
  {
    fstream fout;
    fout.open (filename, ios :: out); //Re-writes the files after the customer has selected a certain number of units for a particular item
    for(int i = 0; i < 5; i++)
    {
      if (choice == i + 1)
      {
        if (units_present[i] == 0)
        {
          cout << "Out of stock" << endl;
        }
        else if (units_present [i] < units_needed)
        {
          cout << "Insufficient items" << endl;
        }
        if (units_present[i] == 0 || units_present[i] < units_needed)
        {
          for (int i = 0; i < 5; i++)
          {
            fout << i + 1 << ',' << item_list[i + 1] << ',' << units_present [i] << '\n';
          }
        }
        else
        {
          for (int i = 0; i < 5; i++)
          {
            if (choice == i + 1)
            {
              units_present [i] -= units_needed;
            }
            fout << i + 1 << ',' << item_list[i + 1] << ',' << units_present [i] << '\n';
          }
        }
      }
    }
  }

  float selectItems (int category, int bnh_units[], int bv_units[], int dr_units[], int fnv_units[], int sn_units[], ofstream& f)
  {
    if (category == 1)
    {
        while (1)
        {
          map <int, float> bnh_cost;
          bnh_cost [1] = 296;
          bnh_cost [2] = 120;
          bnh_cost [3] = 150;
          bnh_cost [4] = 395;
          bnh_cost [5] = 314;
          map <int, string> bnh_item;
          bnh_item [1] = "Soap";
          bnh_item [2] = "Serum";
          bnh_item [3] = "HairOil";
          bnh_item [4] = "Perfume";
          bnh_item [5] = "Shampoo";
          cout << "BEAUTY & HYGIENE" << endl;
          cout << "1 -> Soap\t\tRs. 296" << endl;
          cout << "2 -> Serum\t\tRs. 120" << endl;
          cout << "3 -> HairOil\t\tRs. 150" << endl;
          cout << "4 -> Perfume\t\tRs. 395" << endl;
          cout << "5 -> Shampoo\t\tRs. 314" << endl;
          cout << "\nSelect item number : ";
          cin >> choice;
          cout << "Enter number of units : ";
          cin >> units_needed;
          update_record ("Beauty & Hygiene.csv", bnh_item, choice, units_needed, bnh_units);
          if (bnh_units[choice - 1] > units_needed && bnh_units[choice - 1] != 0)
          {
            f.open ("Sales.csv", ios :: app); //Appends a new row containing item name, rate, units purchased and cost in file Sales.csv
            f << bnh_item[choice] << ',' << bnh_cost[choice] << ',' << units_needed << ',' << bnh_cost[choice] * units_needed << endl;
            f.close();
            amount += units_needed * bnh_cost [choice];
          }
          char item_choice;
          cout << "Continue shopping from this category?";
          cin >> item_choice;
          if (item_choice == 'n')
          break;
        }
    }
    else if (category == 2)
    {
        while (1)
        {
          map <int, float> bv_cost;
          bv_cost [1] = 228;
          bv_cost [2] = 300;
          bv_cost [3] = 33;
          bv_cost [4] = 101;
          bv_cost [5] = 20;
          map <int, string> bv_item;
          bv_item [1] = "Tea";
          bv_item [2] = "Coffee";
          bv_item [3] = "Drink";
          bv_item [4] = "Juice";
          bv_item [5] = "Water";
          cout << "BEVERAGES" << endl;
          cout << "1 -> Tea\t\tRs. 228" << endl;
          cout << "2 -> Coffee\t\tRs. 300" << endl;
          cout << "3 -> Drink\t\tRs. 33" << endl;
          cout << "4 -> Juice\t\tRs. 101" << endl;
          cout << "5 -> Water\t\tRs. 20" << endl;
          cout << "\nSelect item number : ";
          cin >> choice;
          cout << "Enter number of units : ";
          cin >> units_needed;
          update_record ("Beverages.csv", bv_item, choice, units_needed, bv_units);
          if (bv_units[choice - 1] > units_needed && bv_units[choice - 1] != 0)
          {
            f.open ("Sales.csv", ios :: app);
            f << bv_item[choice] << ',' << bv_cost[choice] << ',' << units_needed << ',' << bv_cost[choice] * units_needed << endl;
            f.close();
            amount += units_needed * bv_cost [choice];
          }
          char item_choice;
          cout << "Continue shopping from this category?";
          cin >> item_choice;
          if (item_choice == 'n')
          break;
        }
    }
    else if (category == 3)
    {
        while (1)
        {
          map <int, float> dr_cost;
          dr_cost [1] = 133;
          dr_cost [2] = 120;
          dr_cost [3] = 90;
          dr_cost [4] = 98;
          dr_cost [5] = 2023;
          map <int, string> dr_item;
          dr_item [1] = "Cheese";
          dr_item [2] = "Yogurt";
          dr_item [3] = "Paneer";
          dr_item [4] = "Butter";
          dr_item [5] = "Ghee";
          cout << "DAIRY" << endl;
          cout << "1 -> Cheese\t\tRs. 133" << endl;
          cout << "2 -> Yogurt\t\tRs. 120" << endl;
          cout << "3 -> Paneer\t\tRs. 90" << endl;
          cout << "4 -> Butter\t\tRs. 98" << endl;
          cout << "5 -> Ghee\t\tRs. 2023" << endl;
          cout << "\nSelect item number :\t";
          cin >> choice;
          cout << "Enter number of units: ";
          cin >> units_needed;
          update_record ("Dairy.csv", dr_item, choice, units_needed, dr_units);
          if (dr_units[choice - 1] > units_needed && dr_units[choice - 1] != 0)
          {
            f.open ("Sales.csv", ios :: app);
            f << dr_item[choice] << ',' << dr_cost[choice] << ',' << units_needed << ',' << dr_cost[choice] * units_needed << endl;
            f.close();
            amount += units_needed * dr_cost [choice];
          }
          char item_choice;
          cout << "Continue shopping from this category?";
          cin >> item_choice;
          if (item_choice == 'n')
          break;
        }
    }
    else if (category == 4)
    {
        while (1)
        {
          map <int, float> fnv_cost;
          fnv_cost [1] = 27;
          fnv_cost [2] = 38;
          fnv_cost [3] = 15;
          fnv_cost [4] = 96;
          fnv_cost [5] = 162;
          map <int, string> fnv_item;
          fnv_item [1] = "Onion";
          fnv_item [2] = "Potato";
          fnv_item [3] = "Tomato";
          fnv_item [4] = "Banana";
          fnv_item [5] = "Apple";
          cout << "FRUITS & VEGETABLES" << endl;
          cout << "1 -> Onion\t\tRs. 27" << endl;
          cout << "2 -> Potato\t\tRs. 38" << endl;
          cout << "3 -> Tomato\t\tRs. 15" << endl;
          cout << "4 -> Banana\t\tRs. 96" << endl;
          cout << "5 -> Apple\t\tRs. 162" << endl;
          cout << "\nSelect item number :\t";
          cin >> choice;
          cout << "Enter number of units : ";
          cin >> units_needed;
          update_record ("Fruits & Vegetables.csv", fnv_item, choice, units_needed, fnv_units);
          if (fnv_units[choice - 1] > units_needed && fnv_units[choice - 1] != 0)
          {
            f.open ("Sales.csv", ios :: app);
            f << fnv_item[choice] << ',' << fnv_cost[choice] << ',' << units_needed << ',' << fnv_cost[choice] * units_needed << endl;
            f.close();
            amount += units_needed * fnv_cost [choice];
          }
          char item_choice;
          cout << "Continue shopping from this category?";
          cin >> item_choice;
          if (item_choice == 'n')
          break;
        }
    }
    else if (category == 5)
    {
      while (1)
      {
        map <int, float> sn_cost;
        sn_cost [1] = 82;
        sn_cost [2] = 249;
        sn_cost [3] = 200;
        sn_cost [4] = 20;
        sn_cost [5] = 10;
        map <int, string> sn_item;
        sn_item [1] = "Bread";
        sn_item [2] = "Cereal";
        sn_item [3] = "Candy";
        sn_item [4] = "Chips";
        sn_item [5] = "Maggie";
        cout << "SNACKS" << endl;
        cout << "1 -> Bread\t\tRs. 82" << endl;
        cout << "2 -> Cereal\t\tRs. 249" << endl;
        cout << "3 -> Candy\t\tRs. 200" << endl;
        cout << "4 -> Chips\t\tRs. 20" << endl;
        cout << "5 -> Maggi\t\tRs. 10" << endl;
        cout << "\nSelect item number :\t";
        cin >> choice;
        cout << "Enter number of units : ";
        cin >> units_needed;
        update_record ("Snacks.csv", sn_item, choice, units_needed, sn_units);
        if (bnh_units[choice - 1] > units_needed && sn_units[choice - 1] != 0)
        {
          f.open ("Sales.csv", ios :: app);
          f << sn_item[choice] << ',' << sn_cost[choice] << ',' << units_needed << ',' << sn_cost[choice] * units_needed << endl;
          f.close();
          amount += units_needed * sn_cost [choice];
        }
        char item_choice;
        cout << "Continue shopping from this category?";
        cin >> item_choice;
        if (item_choice == 'n')
        break;
      }
    }
    else
    {
      cout << "You selected the wrong category number!" << endl;
    }
    return amount;
  }

  void calcDiscount ()
  {
    float discount;
    float topay;
    cout << endl;
    cout << " TOTAL : Rs." << amount << endl;
    cout << "|----------------------------------------|" << endl;
    if (amount <= 100)
    {
      cout << "  DISCOUNT RECEIVED = No discount" << endl;
      cout << "|----------------------------------------|" << endl;
      topay = amount;
    }
    else
   {
      if(amount > 100 && amount <= 200)
      {
         cout << " DISCOUNT RECEIVED = 5%" << endl;
         discount = (amount * 5) / 100;
      }
      else if(amount > 200 && amount <= 400)
      {
         cout << " DISCOUNT RECEIVED = 10%" << endl;
         discount = (amount * 10) / 100;
      }
      else if(amount > 400 && amount <= 800)
      {
         cout<< " DISCOUNT RECEIVED = 20%" << endl;
         discount = (amount * 20) / 100;
      }
      else
      {
         cout<< " DISCOUNT RECEIVED = 25%" << endl;
         discount = (amount * 25) / 100;
      }
      topay = amount - discount;
   }
      cout << "|----------------------------------------|" << endl;
      cout << "  Amount to be paid : Rs." << topay << endl;
      cout << endl;
  }
};

class Admin
{

private :

  string username, password;
  int admin_choice, admin_choice1, admin_choice2;

public :

  void create_account()
  {
    while (1)
    {
      cout << "USERNAME" << endl;
      cout << "Username should have minimum 6 and maximum 10 characters" << endl;
      cout << "Enter username : ";
      cin >> username;
      if (username.length() >= 6 && username.length() <= 10)
      {
        cout << "Username Accepted!" << endl;
        break;
      }
      else if (username.length() < 6)
      {
        cout << "Username entered has less than 6 characters" << endl;
        cout << "Enter username again" << endl;
      }
      else if (username.length() > 10)
      {
        cout << "Username entered has more than 10 characters" << endl;
        cout << "Enter username again" << endl;
      }
    }
    while (1)
    {
      cout << "PASSWORD" << endl;
      cout << "Password should have exactly 2 special characters, atmost 3 numeric characters and should have 8 or more characters" << endl;
      cout << "Enter password : ";
      cin >> password;
      int sc_count = 0, n_count = 0;
      for (int i = 0; i < password.length(); i++)
      {
        char c = password.at(i);
        if (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '&' || c == '*')
        {
          sc_count++;
        }
        if (isdigit(c))
        {
          n_count++;
        }
      }
      if (sc_count == 2 && n_count <= 3 && password.length() >= 8)
      {
        cout << "Password accepted!" << endl;
        break;
      }
      else
      {
        if (sc_count != 2)
        {
          cout << "Password entered does not have exactly 2 special characters" << endl;
          cout << "Enter password again" << endl;
        }
        if (n_count > 3)
        {
          cout << "Password entered has more than 3 numeric characters" << endl;
          cout << "Enter password again" << endl;
        }
        if (password.length() < 8)
        {
          cout << "Password entered has less than 8 characters" << endl;
          cout << "Enter password again" << endl;
        }
      }
    }
  }
  void display_record (string filename)
  {
    cout << "ItemNo.\tName\tUnits" << endl;
    ifstream fin;
    string data;
    fin.open (filename);
    while (fin.peek() != EOF)
    {
      getline (fin, data, ',');
      cout << data << "\t";
    }
    fin.close();
  }

  void display_bnh()
  {
    cout << "\nBEAUTY & HYGIENE" << endl;
    display_record ("Beauty & Hygiene.csv");
  }

  void display_bv()
  {
    cout << "\nBEVERAGES" << endl;
    display_record ("Beverages.csv");
  }

  void display_dr()
  {
    cout << "\nDAIRY" << endl;
    display_record ("Dairy.csv");
  }

  void display_fnv()
  {
    cout << "\nFRUITS & VEGETABLES" << endl;
    display_record ("Fruits & Vegetables.csv");
  }

  void display_sn()
  {
    cout << "\nSNACKS" << endl;
    display_record ("Snacks.csv");
  }

  void addItems (string filename, map <int, string> item_list, int choice, int units_added, int units_present[])
  {
    fstream fout;
    fout.open (filename, ios :: out); //Re-writes the files with the added units for a particular item
    for (int i = 0; i < 5; i++)
    {
      if (choice == i + 1)
      {
        units_present [i] += units_added;
      }
      fout << i + 1 << ',' << item_list[i + 1] << ',' << units_present [i] << '\n';
    }
  }

  void viewCategories()
  {
    cout << "[1] View Beauty & Hygiene category\n[2] View Beverages category\n[3] View Dairy category\n[4] View Fruits & Vegetables category\n[5] View Snacks category\n[Any other number] View all categories" << endl;
    cout << "Enter choice : ";
    cin >> admin_choice1;
    switch (admin_choice1)
    {
    case 1 :
      {
        display_bnh();
        break;
      }
    case 2 :
      {
        display_bv();
        break;
      }
    case 3 :
      {
        display_dr();
        break;
      }
     case 4 :
      {
        display_fnv();
        break;
      }
      case 5 :
      {
        display_sn();
        break;
      }
      default :
      {
        display_bnh();
        display_bv();
        display_dr();
        display_fnv();
        display_sn();
        break;
      }
     }
   }

   void updateCategories(int bnh_units[], int bv_units[], int dr_units[], int fnv_units[], int sn_units[])
   {
     cout << "[1] Update Beauty & Hygiene category\n[2] Update Beverages category\n[3] Update Dairy category\n[4] Update Fruits & Vegetables category\n[5] Update Snacks category" << endl;
     cout << "Enter choice : ";
     cin >> admin_choice1;
     int units_added;
     switch (admin_choice1)
     {
     case 1 :
       {
         map <int, string> bnh_item;
         bnh_item [1] = "Soap";
         bnh_item [2] = "Serum";
         bnh_item [3] = "HairOil";
         bnh_item [4] = "Perfume";
         bnh_item [5] = "Shampoo";
         display_bnh();
         cout << "\nEnter choice : ";
         cin >> admin_choice2;
         cout << "Enter no. of units to be added : ";
         cin >> units_added;
         addItems ("Beauty & Hygiene.csv", bnh_item, admin_choice2, units_added, bnh_units);
         break;
       }
      case 2 :
        {
          map <int, string> bv_item;
          bv_item [1] = "Tea";
          bv_item [2] = "Coffee";
          bv_item [3] = "Drink";
          bv_item [4] = "Juice";
          bv_item [5] = "Water";
          display_bv();
          cout << "\nEnter choice : ";
          cin >> admin_choice2;
          cout << "Enter no. of units to be added : ";
          cin >> units_added;
          addItems ("Beverages.csv", bv_item, admin_choice2, units_added, bv_units);
          break;
         }
        case 3 :
         {
           map <int, string> dr_item;
           dr_item [1] = "Cheese";
           dr_item [2] = "Yogurt";
           dr_item [3] = "Paneer";
           dr_item [4] = "Butter";
           dr_item [5] = "Ghee";
           display_dr();
           cout << "\nEnter choice : ";
           cin >> admin_choice2;
           cout << "Enter no. of units to be added : ";
           cin >> units_added;
           addItems ("Dairy.csv", dr_item, admin_choice2, units_added, dr_units);
           break;
         }
         case 4 :
         {
           map <int, string> fnv_item;
           fnv_item [1] = "Onion";
           fnv_item [2] = "Potato";
           fnv_item [3] = "Tomato";
           fnv_item [4] = "Banana";
           fnv_item [5] = "Apple";
           display_fnv();
           cout << "\nEnter choice : ";
           cin >> admin_choice2;
           cout << "Enter no. of units to be added : ";
           cin >> units_added;
           addItems ("Fruits & Vegetables.csv", fnv_item, admin_choice2, units_added, fnv_units);
           break;
         }
         case 5 :
         {
           map <int, string> sn_item;
           sn_item [1] = "Bread";
           sn_item [2] = "Cereal";
           sn_item [3] = "Candy";
           sn_item [4] = "Chips";
           sn_item [5] = "Maggie";
           display_sn();
           cout << "\nEnter choice : ";
           cin >> admin_choice2;
           cout << "Enter no. of units to be added : ";
           cin >> units_added;
           addItems ("Snacks.csv", sn_item, admin_choice2, units_added, sn_units);
           break;
          }
         }
      }

      void login(int bnh_units[], int bv_units[], int dr_units[], int fnv_units[], int sn_units[])
      {
        string user, pass;
        cout << "LOGIN" << endl;
        cout << "Username : ";
        cin >> user;
        cout << "Password : ";
        cin >> pass;
        int i = 1;
        while (i != 3)
        {
          if (username == user && password == pass)
          {
            cout << "Successfully logged in!" << endl;
            cout << "[1] View Inventory\n[2] Update Units" << endl;
            cout << "Enter choice : ";
            cin >> admin_choice;
            switch (admin_choice)
            {
            case 1 :
              {
                viewCategories();
                break;
              }
            case 2 :
              {
                updateCategories(bnh_units, bv_units, dr_units, fnv_units, sn_units);
                break;
              }
            }
            break;
          }
          else
          {
            int choice;
            cout << "Either the username or the password is wrong" << endl;
            cout << "[1] Username\n[2] Password\n[3] Both" << endl;
            cout << "Which one do you want to re-enter?";
            cin >> choice;
            switch (choice)
            {
            case 1 :
              {
                cout << "Re-enter username : ";
                cin >> user;
                break;
              }
            case 2 :
              {
                cout << "Re-enter password : ";
                cin >> pass;
                break;
              }
            case 3 :
              {
                cout << "Re-enter username : ";
                cin >> user;
                cout << "Re-enter password : ";
                cin >> pass;
              }
            }
          }
          i++;
        }
      }
};

int main ()
{
  system("Color F0");
  int bnh_units[] = {20, 20, 20, 20, 20};
  int bv_units[] = {20, 20, 20, 20, 20};
  int dr_units[] = {20, 20, 20, 20, 20};
  int fnv_units[] = {20, 20, 20, 20, 20};
  int sn_units[] = {20, 20, 20, 20, 20};

  ofstream f;

  Admin a;
  while (1)
  {
    cout << endl << endl;
    cout << "[1] Customer" << endl;
    cout << "[2] Admin" << endl;
    cout << "[0] Exit" << endl;
    int choice;
    cout << "Enter choice : ";
    cin >> choice;
    switch (choice)
    {
    case 1 :
      {
        Customer_Details cd;
        fstream newFile;
        newFile.open ("Sales.csv"); //creates a new file Sales.csv to store list of items selected by the customer
        cd.readData();
        Items it;
        while (1)
        {
          int category = cd.selectCategory ();
          it.selectItems(category, bnh_units, bv_units, dr_units, fnv_units, sn_units, f);
          char choice;
          cout << "Do you wish to add more items to your cart? (Y/N) :";
          cin >> choice;
          if (choice == 'N' || choice == 'n')
          {
          break;
          }
        }
        cout << endl;
        cout << endl;
        cout << " ________________________________________"  << endl;
        cout << "|                                        |" << endl;
        cout << "|           CHS SUPERMARKET              |" << endl;
        cout << "|----------------------------------------|" << endl;
        cout << "|              INVOICE                   |" << endl;
        cout << "|----------------------------------------|" << endl;
        cd.displayData ();
        it.calcDiscount();
        cout << "|________________________________________|"  << endl;
        cout << "|                                        |" << endl;
        cout << "|    Thankyou! Please Visit Again :)     |" << endl;
        cout << "|                                        |" << endl;
        cout << "|________________________________________|"  << endl;
        break;
      }
    case 2:
      {
        char choice;
        cout << "Do you wish to create new account? (Y/N) : ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
          a.create_account();
        }
        else
        {
          a.login(bnh_units, bv_units, dr_units, fnv_units, sn_units);
        }
        break;
      }
    case 0:
      {
        cout << "Exit application" << endl;
        exit(0);
      }
    default :
      cout << "Entered wrong choice" << endl;
  }
  }

  return 0;
}
