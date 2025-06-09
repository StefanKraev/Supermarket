#include <iostream>
#include <fstream>
#include "Citation.h"
#include "Worker.h"
#include "Cashier.h"
#include "Manager.h"
#include "Utilities.cpp"
#include <cstdlib>

void saveManager(const char* fileName, const Manager& manager);
void saveCashier(const char* fileName, const Cashier& cashier);
void printWorkerId(int id);
void printAllWorkers();
void printAllProducts();
void printCategoryById(int id);
void printProductByCategory(int CategoryId);
void printPendingCashiers();
bool chechIfManager(int id);
bool checkManagerCode(int code, int id);

int main()
{
    /*MyString firstName = "Eva";
    MyString lastName = "Paujolite";
    MyString password = "passworD";
    size_t nums[10] = {0, 8, 9, 6, 7, 8, 7 ,1, 8, 2};

    Citation citation;
    Citation citations[1] = { citation };
    Cashier cashierA = { "Eva", "Paujolite" , nums, 20, password, 3,  citations, 1};

    Manager manager = { "Eva", "Paujolite" , nums, 20, password, "auCode", "Pass"};
    std::cout << manager.id;*/


logout:
    
    std::cout << "Please, log in or register in the system" << std::endl;
    int input = -1;
    std::cin >> input;
    int Id = 0;
    if (input == 0)
    {
        std::cout << "Please, enter your id and password!" << std::endl;
        int id = 0;
        MyString password;
        std::cin >> id >> password;

        std::ifstream file("id_password.txt");

        if (!file.is_open())
        {
            return -1;
        }


        bool succesfullLogin = false;
        int currentId = 0;
        MyString currentPassword;
        while (!file.eof())
        {
            file >> currentId >> currentPassword;
            if ((currentId == id) && (currentPassword == password))
            {
                succesfullLogin = true;
                Id = id;
            }
        }

        file.close();

        if (!succesfullLogin)
            goto logout;
    }
    else if (input == 1)
    {
        std::cout << "Please, enter your role(Cashier or Manager), first name, last name, phone number, age, and password!" << std::endl;
        MyString role, firstName, lastName, password, phoneNumber;
        size_t age = 0;
        std::cin >> role >> firstName >> lastName >> phoneNumber >> age >> password;

        if (role == "Cashier")
        {
            Citation citation;
            Citation citations[1] = { citation };
            Cashier newCashier = { firstName, lastName, phoneNumber, age, password, 0, citations, 0 };

            std::ofstream file("id_password.txt", std::ios::app);

            if (!file.is_open())
            {
                return -1;
            }

            /*file << newCashier.id << ' ' << password << "\n";*/
            std::cout << "Profile succesfully created! Your id and passowrd are " << newCashier.id << ' ' << newCashier.password << std::endl;
            saveCashier("eventual_cashiers.txt", newCashier);
            Id = newCashier.id;

            file.close();
        }
        else if (role == "Manager")
        {
            srand(time(0));
            int specialCode = rand() + 1234;
            Manager newManager = { firstName, lastName, phoneNumber, age, password, specialCode};

            std::ofstream file("id_password.txt", std::ios::app);

            if (!file.is_open())
            {
                return -1;
            }

            file << newManager.id << ' ' << password << "\n";
            std::cout << "Profile succesfully created! Your id and passowrd are " << newManager.id << ' ' << newManager.password << std::endl;
            saveManager("managers.txt", newManager);
            Id = newManager.id;

            file.close();
        }
    }
    bool isManager = chechIfManager(Id);

    while (true)
    {
        MyString input;
        std::cin >> input;
        if (input == "leave")
        {
            break;
        }
        else if (input == "logout")
        {
            goto logout;
        }
        else if (input == "list_user_data")
        {
            printWorkerId(Id);
        }
        else if (input == "list_workers")
        {
            printAllWorkers();
        }
        else if (input == "list_products")
        {
            printAllProducts();
        }
        else if (input == "list_product_id")
        {
            int id = -1;
            std::cin >> id;
            printProductByCategory(id);
        }
        else if (input == "list_transactions")
        {

        }
        else if (input == "list_pending")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            int authenticationCode = -1;
            std::cin >> authenticationCode;
            if (isManager)
                if (checkManagerCode(authenticationCode, Id));
            printPendingCashiers();
        }
        else if (input == "approve")
        {
            int authenticationCode = -1;
            std::cin >> authenticationCode;
            if (isManager)
                if (checkManagerCode(authenticationCode, Id));
            printPendingCashiers();
        }
    }
}

void saveManager(const char* fileName, const Manager& manager)
{
    if (!fileName)
    {
        return;
    }

    std::ofstream file(fileName, std::ios::app);

    if (!file.is_open())
    {
        return;
    }

    file << manager.id << ' ' << manager.firstName << ' ' << manager.lastName << ' ' << manager.number << ' ' << manager.age << ' ' << manager.password << ' ' << manager.authentificationCode << "\n";
    std::cout << "Manager saved"  << std::endl;


    file.close();
}

void saveCashier(const char* fileName, const Cashier& cashier)
{
    if (!fileName)
    {
        return;
    }

    std::ofstream file(fileName, std::ios::app);

    if (!file.is_open())
    {
        return;
    }

    file << cashier.id << ' ' << cashier.firstName << ' ' << cashier.lastName << ' ' << cashier.number << ' ' << cashier.age << ' ' << cashier.password << ' ' << cashier.numOfTransactions << '\n';
    std::cout << "Cashier saved" << std::endl;


    file.close();
}

void printWorkerId(int id)
{
    std::ifstream file("cashiers.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!file.eof())
    {
        int currentId = -1;
        file >> currentId;
        if (currentId == id)
        {
            MyString firstName;
            MyString lastName;
            MyString num;
            size_t age;
            MyString password;
            size_t numOfTransactions;
            file >> firstName >> lastName >> num >> age >> password >> numOfTransactions;
            std::cout << firstName << ' ' << lastName << ' ' << num << ' ' << age << ' ' << password << ' ' << numOfTransactions << std::endl;
        }
        char c[100] = {};
        file.getline(c, 100);
    }

    file.close();

    std::ifstream fileM("managers.txt", std::ios::app);

    if (!fileM.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!fileM.eof())
    {
        int currentId = -1;
        fileM >> currentId;
        if (currentId == id)
        {
            MyString firstName;
            MyString lastName;
            MyString num;
            size_t age;
            MyString password;
            int numOfTransactions;
            fileM >> firstName >> lastName >> num >> age >> password >> numOfTransactions;
            std::cout << firstName << ' ' << lastName << ' ' << num << ' ' << age << ' ' << password << ' ' << numOfTransactions << std::endl;
        }
        char c[100] = {};
        fileM.getline(c, 100);
    }

    fileM.close();

    return;
}

void printAllWorkers()
{
    std::ifstream file("cashiers.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!file.eof())
    {
        int currentId = -1;
        file >> currentId;
        if (true)
        {
            MyString firstName;
            MyString lastName;
            MyString num;
            size_t age;
            MyString password;
            size_t numOfTransactions;
            file >> firstName >> lastName >> num >> age >> password >> numOfTransactions;
            std::cout << firstName << ' ' << lastName << ' ' << num << ' ' << age << ' ' << password << ' ' << numOfTransactions << std::endl;
        }
        char c[100] = {};
        file.getline(c, 100);
    }

    file.close();

    std::ifstream fileM("managers.txt", std::ios::app);

    if (!fileM.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!fileM.eof())
    {
        int currentId = -1;
        fileM >> currentId;
        if (true)
        {
            MyString firstName;
            MyString lastName;
            MyString num;
            size_t age;
            MyString password;
            int numOfTransactions;
            fileM >> firstName >> lastName >> num >> age >> password >> numOfTransactions;
            std::cout << firstName << ' ' << lastName << ' ' << num << ' ' << age << ' ' << password << ' ' << numOfTransactions << std::endl;
        }
        char c[100] = {};
        fileM.getline(c, 100);
    }

    fileM.close();

    return;
}

void printAllProducts()
{
    std::ifstream file("products.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "File does not open!";
        return;
    }

    while (!file.eof())
    {
        MyString productName;
        double price = -1;
        int categoryId = -1;
        double left = -1;

        file >> productName >> price >> categoryId >> left;



        std::cout << "product name: " << productName << " Price:" << price << ' ';
        printCategoryById(categoryId);
        std::cout << "Amount/Number left: " << left << std::endl;
    }

    file.close();
}

void printCategoryById(int id)
{
    std::ifstream file("CategoryIds.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "File does not open!";
        return;
    }
    
    int control = 1;
    bool found = false;
    while (!file.eof())
    {
        if (control % 3 == 1)
        {
            int currentId = 0;
            file >> currentId;
            if (currentId == id)
            {
                found = true;
                /*MyString name;
                file >> name;
                std::cout << name << ' ';

                char c[1000] = {};
                file.getline(c, 1000);
                std::cout << c << ' ';
                break;*/
                control++;
            }
            else
            {
                control++;
                continue;
            }
        }
        else if (control % 3 == 2)
        {
            if (found)
            {
                file.ignore();
                char c[1000] = {};
                file.getline(c, 1000);
                std::cout << "Category name: " << c << ' ';
                control++;
            }
            else
            {
                file.ignore();
                char c[1000] = {};
                file.getline(c, 1000);
                control++;
            }
        }
        else if (control % 3 == 0) 
        {
            if (found)
            {
                file.ignore();
                char c[1000] = {};
                file.getline(c, 1000);
                std::cout << "Descripiton: ]" << c << ' ';
                break;
            }
            else
            {
                file.ignore();
                char c[1000] = {};
                file.getline(c, 1000);
                control++;
            }
        }
    }

    file.close();
}

void printProductByCategory(int CategoryId)
{
    std::ifstream file("products.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "File does not open!";
        return;
    }

    while (!file.eof())
    {
        MyString productName;
        double price = -1;
        int categoryId = -1;
        double left = -1;

        file >> productName >> price >> categoryId >> left;

        if (CategoryId == categoryId)
        {
            std::cout << "product name: " << productName << " Price:" << price << ' ';
            printCategoryById(categoryId);
            std::cout << "Amount/Number left: " << left << std::endl;
        }
    }

    file.close();
}

void printPendingCashiers()
{
    std::ifstream file("eventual_cashiers.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "File does not open!";
        return;
    }

    while (!file.eof())
    {
        char c[1000] = {};
        file.getline(c, 1000);

        std::cout << c << std::endl;
    }

    file.close();
}

bool chechIfManager(int id)
{
    std::ifstream fileA("managers.txt", std::ios::app);

    if (!fileA.is_open())
        return false;

    while (!fileA.eof())
    {
        int currentId = 0;
        fileA >> currentId;
        if (currentId == id)
        {
            return true;
        }

        char c[100] = {};
        fileA.getline(c, 100);
    }

    fileA.close();

    return false;
}

bool checkManagerCode(int code, int id)
{
    std::ifstream file("managers.txt", std::ios::app);
    
    if (!file.is_open())
        return false;

    while (!file.eof())
    {
        int Id = 0;
        MyString firstName;
        MyString lastName;
        MyString num;
        size_t age;
        MyString password;
        int specialCode;

        file >> Id >> firstName >> lastName >> num >> age >> password >> specialCode;

        if (id == Id)
        {
            if (code == specialCode)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    file.close();
}