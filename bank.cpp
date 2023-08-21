#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
using namespace std;

int complete_profile(char *s);
void inputProfileDetails(char *s);
void Last_five_transactions(char *a);
void account_features(char *acc);
void displayprofile(char *a);
void register_user();
int check_user(char *s);
void loginuser(char *acc);
void assign_account_number(char *ac);
long int no_of_lines();
void login(char *acc);
void forget();
void displayprofile(char *a);
long long string_to_no(string s);
struct UserProfile
{
    string accountNumber;
    string accountType;
    string name;
    string Gender;
    string ifscCode;
    string branchName;
    string phoneNumber;
    string address;
};

class bankFeature
{
private:
    long long balance = 0;
    long long amount = 0;
    long long arr[5][2];

    char p[16];

public:
    void display()
    {
        for (int i = 0; i < 5; i++)
        {
            cout << arr[i][0] << " ";
            if (arr[i][1] == 'D')
            {
                cout << "Deposit";
            }
            else if (arr[i][1] == 'W')
            {
                cout << "Withdraw";
            }
            if (arr[i][1] == 'N')
            {
                cout << "New Account";
            }
            cout << endl;
        }
    }
    void deposit()
    {
        cout << "\nEnter amount to be Deposited\n";
        cin >> amount;
        balance = balance + amount;
        for (int i = 0; i < 4; i++)
        {
            arr[i][0] = arr[i + 1][0];
            arr[i][1] = arr[i + 1][1];
        }
        arr[4][0] = amount;
        arr[4][1] = 'D';
        exit_las();
    }
    void showBalance()
    {
        cout << "\nTotal balance is: " << balance << endl;
    }
    void withdrawl()
    {
        int a;
        cout << "Enter amount to withdraw\n";
        cin >> a;
        if (a > balance)
        {
            cout << "Insufficient Balance!" << endl;
            return;
        }

        balance = balance - a;
        cout << "Available Balance is" << balance;
        for (int i = 0; i < 4; i++)
        {
            arr[i][0] = arr[i + 1][0];
            arr[i][1] = arr[i + 1][1];
        }
        arr[4][0] = a;
        arr[4][1] = 'W';
        exit_las();
    }
    void init_las()
    {
        fstream user;
        ofstream temp;
        int k;
        string str, bal;
        user.open(p);
        temp.open("temp.txt");
        if (user.is_open())
        {
            while (getline(user, str))
            {
                fflush(stdin);
                temp << str << endl;
                if (str == "Balance")
                    break;
            }
            while (getline(user, str))
            {
                if (str == "LFT")
                    break;
            }
            for (int i = 0; i < 5; i++)
            {
                getline(user, str);

                for (k = 0; str[k] != ' '; k++)
                {
                    bal = bal + str[k];
                }

                arr[i][0] = string_to_no(bal);
                k++;
                arr[i][1] = str[k];
                bal.clear();
            }
            user.close();
            temp.close();
        }
    }
    void exit_las()
    {
        ofstream user;
        ifstream temp;
        int k;
        string str, bal;
        user.open(p);
        temp.open("temp.txt");
        if (user.is_open())
        {
            while (getline(temp, str))
            {
                user << str << endl;
                if (str == "END")
                    break;
                fflush(stdin);
            }
            user << balance << endl
                 << "LFT" << endl;
            for (int i = 0; i < 5; i++)
            {
                user << arr[i][0] << " ";
                if (arr[i][1] == 'D')
                {
                    user << "Deposit" << endl;
                }
                else if (arr[i][1] == 'W')
                {
                    user << "Withdrawal" << endl;
                }
                else
                {
                    user << "New Account" << endl;
                }
            }
        }
        user.close();
        temp.close();
    }
    bankFeature() {}
    bankFeature(char *a)
    {
        char s[16], t[5] = ".txt";
        int i, j;
        strcpy(s, a);
        strcat(s, t);
        strcpy(p, s);
        fstream user;
        string str;
        char bal[20];
        user.open(p);
        if (user.is_open())
        {
            while (getline(user, str))
            {
                if (str == "Balance")
                    break;
            }
            getline(user, str);

            balance = string_to_no(str);
        }
        user.close();
        init_las();
    }
};

long long string_to_no(string s)
{
    char c[20];
    int j = 0;
    for (auto i = s.begin(); i != s.end(); j++, i++)
    {
        c[j] = *i;
    }
    long long b = atof(c);
    return b;
}

int main()
{

    char acc[12];
    char flag = '1';
    fstream abc("users.txt");
    if (abc.is_open())
    {
    }
    else
    {
        ofstream xyz;
        xyz.open("users.txt");
        xyz << "abc def 10000000001" << endl;
        xyz.close();
    }
    abc.close();
    do
    {
        acc[0] = '0';
        system("cls");
        login(acc);
        while (acc[0] == '0')
        {
            login(acc);
        }

        cout << "\t\tWelcome!" << endl
             << "Your Profile Details is :" << endl;
        displayprofile(acc);
        while (flag == '1' || flag == '2')
        {
            if (complete_profile(acc) == 0)
            {
                cout << "Complete your details :" << endl;
                char s[16], t[5] = ".txt";
                strcpy(s, acc);
                strcat(s, t);
                inputProfileDetails(s);
            }
            cout << "Press [1] for account features [2] to see last 5 transactions any other key to logout :\t";
            fflush(stdin);
            cin >> flag;
            switch (flag)
            {
            case '1':
                account_features(acc);
                break;
            case '2':
                Last_five_transactions(acc);
                break;
            default:
                cout << "Logout!" << endl;
            }
        }
        flag = '1';

    } while (flag);

    return 0;
}

void login(char *acc)
{
    char label, flag = '1';
    while (flag)
    {
        flag = '1';
        cout << "press 1 to login as existing user :\n";
        cout << "press 2 to Register as new user :\n";
        cout << "Press 3 to forget password :\n";
        fflush(stdin);
        cin >> label;
        switch (label)
        {
        case '1':
            while (flag == '1')
            {
                loginuser(acc);
                if (acc[0] == '0')
                {
                    cout << "Incorrect Login" << endl;
                    cout << "Press 1 to try again or any other key to go back to main menu:\t";
                    fflush(stdin);
                    cin >> flag;
                }
                else
                {

                    flag = '0';
                    return;
                }
            }
            break;
        case '2':
            register_user();
            acc[0] = '0';
            return;
        case '3':
            forget();
            break;
        }
    }
}

void loginuser(char *acc)
{
    int i, j;
    ifstream user("users.txt");
    string check;
    char username[21], password[21], us[21], pa[21];
    cout << "Enter Username :\t";
    cin >> username;
    cout << "Enter Password :\t";
    fflush(stdin);
    cin >> password;

    if (user.is_open())
    {

        while (getline(user, check))
        {

            for (i = 0; check[i] != ' '; i++)
            {
                us[i] = check[i];
            }
            us[i++] = '\0';
            if (!strcmp(us, username))
            {
                for (j = 0; check[i] != ' '; j++, i++)
                {
                    pa[j] = check[i];
                }
                pa[j] = '\0';
            }
            if (!strcmp(pa, password))
            {
                for (i++, j = 0; j < 11; j++, i++)
                {
                    acc[j] = check[i];
                }
                acc[j] = '\0';
                break;
            }
            else
            {
                for (j = 0; j < 11; j++)
                {
                    acc[j] = '0';
                }
                acc[j] = '\0';
            }
        }
    }
    user.close();
}

int complete_profile(char *a)
{
    char s[16], t[5] = ".txt";
    int i, j;
    strcpy(s, a);
    strcat(s, t);
    fstream user;
    string str;
    user.open(s);
    while (getline(user, str))
    {
        if (str == "LFT")
        {
            user.close();
            return 1;
        }
    }
    user.close();
    return 0;
}
void register_user()
{
    int i;
    char flag = '0';
    char us[21], password[21], acc[16];
    cout << "Enter a new username:\t";
    fflush(stdin);
    cin >> us;
    while (check_user(us))
    {
        cout << "User already present , to return to main menu press 1\t";
        fflush(stdin);
        cin >> flag;
        if (flag == '1')
            return;
        cout << "Enter a new username:\t";
        fflush(stdin);
        cin >> us;
    }
    cout << "Enter a strong password :\t";
    fflush(stdin);
    cin >> password;
    ofstream user;
    user.open("users.txt", ios::app);
    user << us << " " << password << " ";
    cout << endl
         << "Register Successful\t Now complete your profile Details\n"
         << endl;
    user.close();
    assign_account_number(acc);
    inputProfileDetails(acc);
    cout << "You have successfully registered your account!" << endl;
}

int check_user(char *s)
{
    string str;
    ifstream user("users.txt");
    char a[22];
    int i;
    if (user.is_open())
    {
        while (getline(user, str))
        {
            for (i = 0; str[i] != ' '; i++)
            {
                a[i] = str[i];
            }
            a[i] = '\0';
            if (strcmp(a, s) == 0)
            {
                return 1;
            }
        }
    }
    user.close();
    return 0;
}
void assign_account_number(char *ac)
{
    int i;
    string str;
    ofstream user;
    user.open("users.txt", ios::app);
    long long acc = 10000000000 + no_of_lines();
    user << acc << endl;
    ofstream abc;
    string account = to_string(acc);
    account.append(".txt");
    char a[16];
    for (i = 0; i < 15; i++)
    {
        a[i] = account[i];
    }
    a[i] = '\0';
    strcpy(ac, a);
    abc.open(a);
    user.close();
}

long int no_of_lines()
{
    fstream user("users.txt");
    int line = 1;
    string l;
    if (user.is_open())
    {
        while (getline(user, l))
        {
            line++;
        }
    }
    user.close();
    return line;
}

void inputProfileDetails(char *s)
{
    UserProfile user;
    int i;
    ofstream abc;
    char b[16];
    abc.open(s);
    for (i = 0; i < 11; i++)
    {
        b[i] = s[i];
    }
    b[i] = '\0';

    abc << "Account Number: " << b << endl;

    cout << "Enter Account Type: ";
    cin >> user.accountType;
    abc << "Account Type : " << user.accountType << endl;

    cout << "Enter Name: ";
    fflush(stdin);
    getline(cin, user.name);
    abc << "Name : " << user.name << endl;

    cout << "Enter Gender: ";
    getline(cin, user.Gender);
    abc << "Gender : " << user.Gender << endl;

    cout << "Enter IFSC Code: ";
    getline(cin, user.ifscCode);
    abc << "IFSC Code : " << user.ifscCode << endl;

    cout << "Enter Branch Name: ";
    getline(cin, user.branchName);
    abc << "Branch Name : " << user.branchName << endl;

    cout << "Enter Phone Number: ";
    getline(cin, user.phoneNumber);
    abc << "Phone Number : " << user.phoneNumber << endl;

    cout << "Enter Address: ";
    fflush(stdin);
    getline(cin, user.address);
    abc << "Address : " << user.address << endl;
    abc << endl
        << "Balance" << endl
        << 0.00 << endl
        << "LFT" << endl;
    abc << 0.00 << " New Account" << endl
        << 0.00 << " New Account" << endl
        << 0.00 << " New Account" << endl
        << 0.00 << " New Account" << endl
        << 0.00 << " New Account" << endl;
    abc.close();
}

void Last_five_transactions(char *a)
{
    char s[16], t[5] = ".txt";
    int i;
    strcpy(s, a);
    strcat(s, t);
    fstream user;
    string str;
    user.open(s);
    if (user.is_open())
    {
        while (getline(user, str))
        {
            if (str == "LFT")
                break;
        }
        while (getline(user, str))
        {
            cout << str << endl;
        }
    }
    user.close();
}

void displayprofile(char *a)
{
    char s[16], t[5] = ".txt";
    strcpy(s, a);
    strcat(s, t);
    fstream user;
    string str;
    user.open(s);
    if (user.is_open())
    {
        while (getline(user, str))
        {
            if (str == "Balance")
            {
                cout << endl;
                break;
            }
            cout << str << endl;
        }
    }
    user.close();
}

void account_features(char *acc)
{
    bankFeature b(acc);
    char choice = '1';
    while (choice != '4')
    {
        cout << "Enter Your Choice\n";

        cout << "\t1. Deposit Money\n";
        cout << "\t2. Show Total balance\n";
        cout << "\t3. Withdraw Money\n";
        cout << "\t4. Cancel\n";
        fflush(stdin);
        cin >> choice;
        switch (choice)
        {
        case '1':
            b.deposit();
            break;
        case '2':
            b.showBalance();
            break;
        case '3':
            b.withdrawl();
            break;
        case '4':
            break;
        default:
            cout << "\nInvalid choice\n";
        }
    }
}

void forget()
{
    int j = 0, flag, label = 0;
    fstream user("users.txt");
    ofstream temp("temp.txt");
    string check, cpy;
    char username[21], password[12], us[21], pa[21], pass[21], acc[12];
    cout << "Enter Username :\t";
    cin >> username;
    cout << "Enter account no :\t";
    fflush(stdin);
    cin >> password;
    strcpy(acc, password);

    if (user.is_open())
    {

        while (getline(user, check))
        {
            cpy.clear();
            j = 0;
            auto i = check.begin();
            for (; *i != ' '; j++, i++)
            {
                us[j] = *i;
                cpy = cpy + *i;
            }
            us[j] = '\0';

            if (!strcmp(us, username))
            {
                cpy = cpy + ' ';
                for (i++; *i != ' '; i++)
                {
                }

                for (i++, j = 0; i != check.end(); j++, i++)
                {
                    pa[j] = *i;
                }
                pa[j] = '\0';
                if (!strcmp(pa, password))
                {
                    cout << "Enter new password :\t";
                    fflush(stdin);
                    cin >> pass;
                    cpy = cpy + pass;
                    cpy = cpy + " ";
                    cpy = cpy + acc;
                    flag = 0;
                    temp << cpy << endl;
                    label = 1;
                    continue;
                }
            }
            us[0] = '\0';
            temp << check << endl;
        }
    }
    user.close();
    temp.close();
    if (label == 1)
    {
        fstream temp("temp.txt");
        ofstream user("users.txt");
        if (temp.is_open())
        {
            while (getline(temp, check))
            {
                user << check << endl;
            }
            cout << "Password changed !" << endl;
        }
    }
    if (label == 0)
    {
        cout << "Enter correct details! " << endl;
    }
}