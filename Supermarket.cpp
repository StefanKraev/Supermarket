#include <iostream>
#include <fstream>
#include <cstring>
#include "Citation.h"
#include "Worker.h"
#include "Cashier.h"
#include "Manager.h"
#include "Utilities.cpp"
#include <cstdlib>
#include <cstdio>
#include "Product.h"
#include <ctime>

void saveManager(const char* fileName, const Manager& manager);
void saveCashier(const char* fileName, const Cashier& cashier);
void printWorkerId(int id);
void printAllWorkers();
void printAllProducts();
void printCategoryById(int id);
void printProductByCategory(int CategoryId);
void printPendingCashiers();
bool chechIfManager(int id);
bool checkManagerCode(const char* code, int id);
void approveCashier(int id);
void declineCashier(int id);
void fireCashierHelpFunc(int id);
void fireCashier(int id);
void addCategory();
void deleteCategory(int catId);
void addProduct(const Product& product);
Product createProduct(const MyString& name, double price, int categoryId, double left);
void deleteProduct(const MyString& productName);
char* generateAuthentificationCode();
char* generateVaucherCode();
void promoteCashier(int id);
void warnCashier(int id, int points);
void listWarnedCashiers(int minPoints);
double editProductQuantity(const MyString&, double quantity);
void printProductsForSell();
void sell(int id);
int changeTransId();
int getTransId();
double findVoucher(const MyString& voucherCode, double totalSum);
bool checkProductCategoryId(const MyString& product, int categoryId);
double findProductPrice(const MyString& product);
int getPercentage(const MyString& voucherCode);
int getProductsCount(); 
void addTransactionToCashier(int casheirId);

int main()
{

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
            char result[8]{};
            strcpy_s(result, generateAuthentificationCode());
            Manager newManager = { firstName, lastName, phoneNumber, age, password, result};
            //delete[] specialCode;

            std::ofstream authFile("AuthentificationCodes.txt", std::ios::app);

            if (!authFile.is_open())
            {
                std::cout << "File does not open";
            }

            authFile << newManager.id << ' ' << result << '\n';

            authFile.close();

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
            char code[8]{};
            std::cin >> code;
            if (isManager)
                if (checkManagerCode(code, Id))
            printPendingCashiers();
        }
        else if (input == "approve_cashier")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
                if (checkManagerCode(code, Id));
                {
                std::cout << "Please, enter cashier ID" << '\n';
                    int cashierId = -1;
                    std::cin >> cashierId;
                    approveCashier(cashierId);
                    std::cout << "Cashier approved!" << '\n';
                }
        }
        else if (input == "decline_cashier")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please, enter cashier ID!" << std::endl;
                    int cashierId = -1;
                    std::cin >> cashierId;
                    declineCashier(cashierId);
                    std::cout << "Cashier declined!" << '\n';
                }
            }
        }
        else if (input == "fire_cashier")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please, enter cashier ID!" << std::endl;
                    int cashierId = -1;
                    std::cin >> cashierId;
                    fireCashier(cashierId);
                    std::cout << "Cashier fired!" << '\n';
                }
            }
        }
        else if (input == "add_category")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    addCategory();
                    std::cout << "Category added!" << '\n';
                }
            }
        }
        else if (input == "delete_category")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please, enter category Id" << std::endl;
                    int categoryId = 0;
                    std::cin >> categoryId;
                    deleteCategory(categoryId);
                    std::cout << "Category successfully deleted!" << std::endl;
                }
            }
        }
        else if (input == "add_product")
        {
            MyString name;
            double price = 0;
            int categoryId = -1;
            double left = 0;
            std::cout << "Please, enter product name, price, categoryId and quntity left!" << std::endl;
            std::cin >> name >> price >> categoryId >> left;
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    Product newProdcut = createProduct(name, price, categoryId, left);
                    addProduct(newProdcut);
                    std::cout << "Product added!" << '\n';
                }
            }
        }
        else if (input == "delete_product")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please enter prodcut name!" << '\n';
                    MyString productName;
                    std::cin >> productName;
                    deleteProduct(productName);
                    std::cout << "Product deleted!" << '\n';
                }
            }
        }
        else if (input == "promote_cashier")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please, enter cashier Id" << std::endl;
                    int categoryId = 0;
                    std::cin >> categoryId;
                    promoteCashier(categoryId);
                    std::cout << "Cashier promoted!" << std::endl;
                }
            }
        }
        else if (input == "warn_cashier")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please, enter cashier Id and poits deduction" << std::endl;
                    int categoryId, points = 0;
                    std::cin >> categoryId >> points;
                    warnCashier(categoryId, points);
                    std::cout << "Cashier warned!" << std::endl;
                }
            }
        }
        else if (input == "list_warned_cashiers")
        {
            std::cout << "Please, enter your authentification code" << std::endl;
            char code[8]{};
            std::cin >> code;
            if (isManager)
            {
                if (checkManagerCode(code, Id))
                {
                    std::cout << "Please, enter minimum points!" << std::endl;
                    int minPoints = 0;
                    std::cin >> minPoints;
                    listWarnedCashiers(minPoints);
                }
            }
        }
        else if (input == "sell")
        {
            if (!isManager)
            {
                sell(Id);
            }
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
        if (file.peek() == -1)
            break;
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
        if (fileM.peek() == -1)
            break;
        int currentId = -1;
        fileM >> currentId;
        if (true)
        {
            MyString firstName;
            MyString lastName;
            MyString num;
            size_t age;
            MyString password;
            fileM >> firstName >> lastName >> num >> age >> password;
            std::cout << firstName << ' ' << lastName << ' ' << num << ' ' << age << ' ' << password << ' ' << std::endl;
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

bool checkProductCategoryId(const MyString& product, int categoryId)
{
    std::ifstream productsFile("products.txt");
    if (!productsFile.is_open())
    {
        std::cout << "File does not open";
        return false;
    }

    while (!productsFile.eof())
    {
        if (productsFile.peek() == -1)
            break;

        MyString productName;
        double price = -1;
        int categoryyId = -1;
        double left = -1;

        productsFile >> productName >> price >> categoryyId >> left;
        if (productName == product)
        {
            if (categoryyId == categoryId)
            {
                productsFile.close();
                return true;
            }
            else
            {
                productsFile.close();
                return false;
            }
        }

        productsFile.ignore();
    }

    productsFile.close();
    return false;
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
        if (file.peek() == -1)
            break;
        char c[1000] = {};
        file.getline(c, 1000);

        std::cout << c << std::endl;
    }

    file.close();
}

bool chechIfManager(int id)
{
    std::ifstream fileA("AuthentificationCodes.txt", std::ios::app);

    if (!fileA.is_open())
        return false;

    while (!fileA.eof())
    {
        if (fileA.peek() == -1)
            break;
        int currentId = 0;
        fileA >> currentId;
        if (currentId == id)
        {
            if (currentId == id)
                return true;
        }

        char c[100]{};
        fileA.getline(c, 100);
    }

    fileA.close();

    return false;
}

bool checkManagerCode(const char* code, int id)
{
    std::ifstream file("AuthentificationCodes.txt", std::ios::app);
    
    if (!file.is_open())
        return false;

    while (!file.eof())
    {
        int currentId = 0;
        file >> currentId;
        if (currentId == id)
        {
            char currentCode[8]{};
            file >> currentCode;
            if (std::strcmp(currentCode, code) == 0)
            {
                return true;
            }
        }
    }

    file.close();

    return false;
}

void approveCashier(int id)
{
    std::ifstream file("eventual_cashiers.txt", std::ios::app);
    std::ofstream fileCashiers("cashiersTransactionsCitations.txt", std::ios::app);

    if (!file.is_open() || !fileCashiers.is_open())
    {
        std::cout << "Not opening";
        return;
    }
    while (!file.eof())
    {
        if (file.peek() == -1)
            break;
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

            fileCashiers << currentId << ' ' << numOfTransactions << ' ' << 0 << '\n';


            std::ofstream newFile("cashiers.txt", std::ios::app);
            std::ofstream ids("id_password.txt", std::ios::app);
            if (!newFile.is_open() || !ids.is_open())
            {
                std::cout << "Not opening";
                return;
            }

            newFile << id << ' ' << firstName << ' ' << lastName << ' ' << num << ' ' << age << ' ' << password << ' ' << numOfTransactions << std::endl;
            ids << id << ' ' << password << std::endl;

            ids.close();
            newFile.close();
        }
        else
        {
            char c[1000] = {};
            file.getline(c, 1000);
        }
    }

    fileCashiers.close();
    file.close();

    declineCashier(id);
}

void declineCashier(int id)
{
    int index = 0;
    bool skip = true;
    std::ifstream file("eventual_cashiers.txt", std::ios::app);
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
            skip = false;
            break;
        }
        index++;
        file.ignore();
        char c[100] = {};
        file.getline(c, 100);
    }

    if (skip)
        return;

    file.close();

    std::ifstream filee("eventual_cashiers.txt", std::ios::app);
    std::ofstream tempFile("temp.txt", std::ios::app);

    if (!filee.is_open() || !tempFile.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    int counter = 0;
    while (!filee.eof())
    {
        if (filee.peek() == -1)
            break;
        int currentId = -1;
        if (counter == index)
        {
            char c[100] = {};
            filee.getline(c, 100);
            counter++;
            continue;
        }
        else
        {
            char c[100] = {};
            filee.getline(c, 100);
            tempFile << c << '\n';
        }
        counter++;
    }

    filee.close();
    tempFile.close();

    std::remove("eventual_cashiers.txt");
    std::rename("temp.txt", "eventual_cashiers.txt");
}

void fireCashier(int id)
{
    fireCashierHelpFunc(id);
    int index = 0;
    bool skip = true;
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
            skip = false;
            break;
        }
        index++;
        file.ignore();
        char c[100] = {};
        file.getline(c, 100);
    }

    if (skip)
        return;

    file.close();

    std::ifstream filee("cashiers.txt", std::ios::app);
    std::ofstream tempFile("temp.txt", std::ios::app);

    if (!filee.is_open() || !tempFile.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    int counter = 0;
    while (!filee.eof())
    {
        if (filee.peek() == -1)
            break;
        int currentId = -1;
        if (counter == index)
        {
            char c[100] = {};
            filee.getline(c, 100);
            counter++;
            continue;
        }
        else
        {
            char c[100] = {};
            filee.getline(c, 100);
            tempFile << c << '\n';
        }
        counter++;
    }

    filee.close();
    tempFile.close();

    std::remove("cashiers.txt");
    std::rename("temp.txt", "cashiers.txt");

    int indexx = 0;
    bool skipp = true;
    std::ifstream anotherFile("id_password.txt", std::ios::app);
    if (!anotherFile.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!anotherFile.eof())
    {
        int currentId = -1;
        anotherFile >> currentId;
        if (currentId == id)
        {
            skipp = false;
            break;
        }
        indexx++;
        anotherFile.ignore();
        char c[100] = {};
        anotherFile.getline(c, 100);
    }

    if (skipp)
        return;

    anotherFile.close();

    std::ifstream first("id_password.txt", std::ios::app);
    std::ofstream second("temp.txt", std::ios::app);

    if (!first.is_open() || !second.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    int counterr = 0;
    while (!first.eof())
    {
        if (first.peek() == -1)
            break;
        int currentId = -1;
        if (counterr == indexx)
        {
            char c[100] = {};
            first.getline(c, 100);
            counterr++;
            continue;
        }
        else
        {
            char c[100] = {};
            first.getline(c, 100);
            second << c << '\n';
        }
        counterr++;
    }

    first.close();
    second.close();

    std::remove("id_password.txt");
    std::rename("temp.txt", "id_password.txt");
}

void fireCashierHelpFunc(int id)
{
    std::ifstream first("cashiersTransactionsCitations.txt", std::ios::app);
    std::ofstream second("temp.txt", std::ios::app);

    if (!first.is_open() || !second.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!first.eof())
    {
        if (first.peek() == -1)
            break;

        int currentId = 0;
        int numOfTransactions = 0;
        int numOfCitations = 0;

        first >> currentId >> numOfTransactions >> numOfCitations;
        if (!(currentId == id))
        {
            second << currentId << ' ' << numOfTransactions << ' ' << numOfCitations << std::endl;
        }
        for (int i = 0; i < numOfCitations; i++)
        {
            first.ignore();
            char sender[100];
            first.getline(sender, 100);

            char description[100];
            first.getline(description, 100);

            first.ignore();
            int points = 0;
            first >> points;

            if (!(currentId == id))
            {
                second << sender << std::endl;
                second << description << std::endl;
                second << points << std::endl;
            }
        }
        first.ignore();
    }

    first.close();
    second.close();

    std::remove("cashiersTransactionsCitations.txt");
    std::rename("temp.txt", "cashiersTransactionsCitations.txt");
}

void addCategory()
{
    srand(time(0));
    int cateogryId = rand();
    std::cout << "Please type categoryName and description: " << std::endl;
    MyString name;
    std::cin >> name;

    std::cin.ignore();
    char c[100];
    std::cin.getline(c, 100);

    std::ofstream file("CategoryIds.txt", std::ios::app);
    if (!file.is_open())
    {
        std::cout << "File does not open";
        return;
    }

    file << cateogryId << std::endl;
    file << name << std::endl;
    file << c << std::endl;

    file.close();
}

void deleteCategory(int catId)
{
    std::ifstream source("CategoryIds.txt", std::ios::app);
    std::ofstream temp("temp.txt", std::ios::app);

    if (!source.is_open() || !temp.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!source.eof())
    {
        if (source.peek() == -1)
            break;
        
        int currentId = -1;
        source >> currentId;
        source.ignore();
        if (currentId != catId)
            temp << currentId << '\n';
        for (int i = 0; i < 2; i++)
        {
            if (currentId == catId)
            {
                char c[100] = {};
                source.getline(c, 100);
            }
            else
            {
                char c[100] = {};
                source.getline(c, 100);
                temp << c << '\n';
            }
        }
    }

    source.close();
    temp.close();

    std::remove("CategoryIds.txt");
    std::rename("temp.txt", "CategoryIds.txt");
}

Product createProduct(const MyString& name, double price, int categoryId, double left)
{
    Product result = { name, price, categoryId, left };
    return result;
}

void addProduct(const Product& product)
{
    std::ofstream file("products.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "File does not open";
        return;
    }

    file << product.getProductName() << ' ' << product.getProductPrice() << ' '
        << product.getProductCategoryId() << ' ' << product.getProductLeft() << '\n';

    file.close();
}

void deleteProduct(const MyString& productName)
{
    std::ifstream source("products.txt", std::ios::app);
    std::ofstream temp("temp.txt", std::ios::app);

    if (!source.is_open() || !temp.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!source.eof())
    {
        if (source.peek() == -1)
            break;

        MyString name;
        source >> name;
        source.ignore();
        if (name != productName)
        {
            temp << name << ' ';
            char c[100] = {};
            source.getline(c, 100);
            temp << c << '\n';
        }
        else
        {
            char c[100] = {};
            source.getline(c, 100);
        }
    }

    source.close();
    temp.close();

    std::remove("products.txt");
    std::rename("temp.txt", "products.txt");
}

char* generateAuthentificationCode()
{
    char result[8] = {};
    for (int i = 0; i < 8; i++)
    {
        if (i == 0 || i == 3 || i == 4 || i == 5)
        {
            std::srand(std::time(nullptr));
            int digit = std::rand() % 10;
            char currentDigit = digit + '0';
            result[i] = currentDigit;
        }
        else if (i == 6)
        {
            std::srand(std::time(nullptr));
            int digit = std::rand() % 26;
            char currentDigit = digit + 'a';
            result[i] = currentDigit;
        }
        else
        {
            std::srand(std::time(nullptr));
            int digit = std::rand() % 26;
            char currentDigit = digit + 'A';
            result[i] = currentDigit;
        }
    }
    result[7] = '\0';

    return result;
}

char* generateVaucherCode()
{
    std::ifstream file("transactionsIds.txt");

    if (!file.is_open())
    {
        std::cout << "File does not open!" << std::endl;
    }

    int transactionId = 0;
    int vaucherId = 0;
    file >> transactionId >> vaucherId;

    char* result = new char;

    std::srand(std::time(nullptr));
    int firstDigit = std::rand() % 10;
    char currentDigit = firstDigit + '0';
    result[0] = currentDigit;

    std::srand(std::time(nullptr));
    int firstLetter = std::rand() % 26;
    char currentLetter = firstLetter + 'A';
    result[1] = currentLetter;

    int counter = 0;
    int copy = vaucherId;
    while (true)
    {
        if (copy == 0)
            break;

        copy /= 10;
        counter++;
    }

    int nextIndex = 2;
    for (int i = counter; i > 0; i--)
    {
        int powerOfTen = 1;
        for (int j = 1; j < i; j++)
        {
            powerOfTen *= 10;
        }

        int copyCopy = vaucherId;
        for (int j = 1; j < i; j++)
        {
            copyCopy /= 10;
        }


        int currDig = vaucherId % powerOfTen;
        char currChar = copyCopy + '0';
        result[nextIndex++] = currChar;
        vaucherId %= powerOfTen;
    }

    std::srand(std::time(nullptr));
    int secondLetter = std::rand() % 26;
    char currenttLetter = secondLetter + 'A';
    result[nextIndex++] = currenttLetter;

    std::srand(std::time(nullptr));
    int secondDigit = std::rand() % 10;
    char currenttDigit = secondDigit + '0';
    result[nextIndex++] = currenttDigit;

    file.close();

    return result;

    delete[] result;
}

void promoteCashier(int id)
{
    int index = 0;
    bool skip = true;
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
            skip = false;
            break;
        }
        index++;
        file.ignore();
        char c[100] = {};
        file.getline(c, 100);
    }

    if (skip)
        return;

    file.close();

    int CashierId = 0;
    MyString firstName;
    MyString lastName;
    MyString number;
    size_t age = 0;
    MyString password;
    int numOfTransactions;

    std::ifstream filee("cashiers.txt", std::ios::app);
    std::ofstream tempFile("temp.txt", std::ios::app);

    if (!filee.is_open() || !tempFile.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    int counter = 0;
    while (!filee.eof())
    {
        if (filee.peek() == -1)
            break;
  
        if (counter == index)
        {
            filee >> CashierId >> firstName >> lastName >> number >> age >> password >> numOfTransactions;
            filee.ignore();
            counter++;

            continue;
        }
        else
        {
            char c[100] = {};
            filee.getline(c, 100);
            tempFile << c << '\n';
        }
        counter++;
    }

    filee.close();
    tempFile.close();

    std::remove("cashiers.txt");
    std::rename("temp.txt", "cashiers.txt");

 
    std::ofstream fileManagers("managers.txt", std::ios::app);

    if (!fileManagers.is_open())
    {
        std::cout << "File does not open!";
        return;
    }

    fileManagers << CashierId << ' ' << firstName << ' ' << lastName << ' ' <<
        number << ' ' << age << ' ' << password << std::endl;

    fileManagers.close();

    std::ofstream fileCodes("AuthentificationCodes.txt", std::ios::app);

    if (!fileCodes.is_open())
    {
        std::cout << "File does not open!";
        return;
    }

    char result[8]{};
    strcpy_s(result, generateAuthentificationCode());

    fileCodes << CashierId << ' ' << result << std::endl;

    fileCodes.close();
}

void warnCashier(int id, int points)
{
    std::ifstream first("cashiersTransactionsCitations.txt", std::ios::app);
    std::ofstream second("temp.txt", std::ios::app);

    if (!first.is_open() || !second.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!first.eof())
    {
        if (first.peek() == -1)
            break;

        int currentId = 0;
        int numOfTransactions = 0;
        int numOfCitations = 0;

        first >> currentId >> numOfTransactions >> numOfCitations;
        if (currentId == id)
        second << currentId << ' ' << numOfTransactions << ' ' << numOfCitations + 1 << std::endl;
        else
            second << currentId << ' ' << numOfTransactions << ' ' << numOfCitations << std::endl;
     
        for (int i = 0; i < numOfCitations; i++)
        {
            first.ignore();
            char sender[100];
            first.getline(sender, 100);

            char description[100];
            first.getline(description, 100);

            int points = 0;
            first >> points;

            second << sender << std::endl;
            second << description << std::endl;
            second << points << std::endl;
        }
        first.ignore();
        if (currentId == id)
        {
            std::cout << "Please, enter the sender of the citation!" << '\n';
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            char sender[100];
            std::cin.getline(sender, 100);

            std::cout << "Please, give a desctiption of the citation!" << '\n';
            char description[100];
            std::cin.getline(description, 100);

            second << sender << std::endl;
            second << description << std::endl;
            second << points << std::endl;
        }
    }

    first.close();
    second.close();

    std::remove("cashiersTransactionsCitations.txt");
    std::rename("temp.txt", "cashiersTransactionsCitations.txt");
}

void listWarnedCashiers(int minPoints)
{
    std::ifstream file("cashiersTransactionsCitations.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!file.eof())
    {
        if (file.peek() == -1)
            break;

        int currentId = 0;
        int numOfTransactions = 0;
        int numOfCitations = 0;

        file >> currentId >> numOfTransactions >> numOfCitations;

        int pointsSum = 0;
        for (int i = 0; i < numOfCitations; i++)
        {
            file.ignore();
            char sender[100];
            file.getline(sender, 100);

            char description[100];
            file.getline(description, 100);

            //file.ignore();
            int points = 0;
            file >> points;

            pointsSum += points;
        }
        if (pointsSum >= minPoints)
        {
            std::cout << "Cashier with id: " << currentId << " has " << pointsSum << " points!" << '\n';
        }

        file.ignore();
    }

    file.close();
}

double editProductQuantity(const MyString& producttName, double quantity)
{
    double result = 0;
    std::ifstream file("products.txt", std::ios::app);
    std::ofstream temp("temp.txt", std::ios::app);

    if (!file.is_open() || !temp.is_open())
    {
        std::cout << "File does not open!";
        return -1;
    }

    while (!file.eof())
    {
        if (file.peek() == -1)
            break;
        MyString productName;
        double price = -1;
        int categoryId = -1;
        double left = -1;

        file >> productName >> price >> categoryId >> left;

        if (producttName == productName)
        {
            if (quantity > left)
            {
                std::cout << "There is not enouth of the product available!" << '\n';
                temp << productName << ' ' << price << ' ' << categoryId << ' ' << left << '\n';
            }
            else if (quantity == left)
            {
                result += quantity * price;
                temp << productName << ' ' << price << ' ' << categoryId << ' ' << left - quantity << '\n';
            }
            else
            {
                temp << productName << ' ' << price << ' ' << categoryId << ' ' << left - quantity << '\n';
                result += quantity * price;
            }
        }
        else
            temp << productName << ' ' << price << ' ' << categoryId << ' ' << left << '\n';
        file.ignore();
    }

    file.close();
    temp.close();

    std::remove("products.txt");
    std::rename("temp.txt", "products.txt");

    return result;
}

void printProductsForSell()
{
    std::ifstream file("products.txt", std::ios::app);

    if (!file.is_open())
    {
        std::cout << "File does not open!";
        return;
    }

    int index = 1;
    while (!file.eof())
    {
        if (file.peek() == -1)
            break;

        MyString productName;
        double price = -1;
        int categoryId = -1;
        double left = -1;

        file >> productName >> price >> categoryId >> left;



        std::cout << '\t' << index++ << ". " << productName << " : " << price << ' '
            << " : " << left << std::endl;
        file.ignore();
    }

    file.close();
}

int changeTransId()
{
    std::ifstream transFile("transactionsIds.txt");

    if (!transFile.is_open())
    {
        std::cout << "File does not open!";
        return -2;
    }
     
    int transId = -1;
    double left = -1;

    transFile >> transId >> left;

    transFile.close();

    std::ofstream transsFile("transactionsIds.txt");

    if (!transsFile.is_open())
    {
        std::cout << "File does not open!";
        return -2;
    }

    transsFile << transId + 1 << ' ' << left;

    transsFile.close();

    return transId;
}

int getTransId()
{
    std::ifstream transFile("transactionsIds.txt");

    if (!transFile.is_open())
    {
        std::cout << "File does not open!";
        return -2;
    }

    int transId = -1;
    double left = -1;

    transFile >> transId >> left;

    transFile.close();
    return transId - 1;
}

double findProductPrice(const MyString& product)
{
    std::ifstream productsFile("products.txt");
    if (!productsFile.is_open())
    {
        std::cout << "File does not open";
        return false;
    }

    while (!productsFile.eof())
    {
        if (productsFile.peek() == -1)
            break;

        MyString productName;
        double price = -1;
        int categoryyId = -1;
        double left = -1;

        productsFile >> productName >> price >> categoryyId >> left;
        if (productName == product)
        {
            productsFile.close();
            return price;
        }

        productsFile.ignore();
    }

    productsFile.close();
    return 0;
}

double findCurrentDisscount(int categoryId)
{
    std::ifstream currentTransaction("currentTransaction.txt");
    if (!currentTransaction.is_open())
    {
        std::cout << "Does not open!";
        return -1;
    }

    double result = 0;
    while (!currentTransaction.eof())
    {
        if (currentTransaction.peek() == -1)
            break;

        MyString product;
        int quantity = 0;
        currentTransaction >> product >> quantity;
        if (checkProductCategoryId(product, categoryId))
        {
            result += findProductPrice(product) * quantity;
        }


        currentTransaction.ignore();
    }

    currentTransaction.close();
    return result;
}

int getProductsCount()
{
    std::ifstream file("products.txt");
    if (!file.is_open())
    {
        std::cout << "File does not open";
        return -1;
    }

    int counter = 0;
    while (!file.eof())
    {
        if (file.peek() == -1)
            break;

        MyString productName;
        double price = -1;
        int categoryyId = -1;
        double left = -1;

        file >> productName >> price >> categoryyId >> left;

        counter++;
        file.ignore();
    }

    file.close();
    return counter;
}

int getPercentage(const MyString& voucherCode)
{
    std::ifstream voucherFile("VouchersCodes.txt");

    if (!voucherFile.is_open())
    {
        std::cout << "File does not open!";
        return -1;
    }

    int result = -1;
    while (!voucherFile.eof())
    {
        if (voucherFile.peek() == -1)
            break;

        MyString currentCode;
        voucherFile >> currentCode;
        int type = -1;
        voucherFile >> type;

        switch (type)
        {
            case 0:
            {
                int categoryId = -1;
                voucherFile >> categoryId;
                int percantage = 0;
                voucherFile >> percantage;
                if (voucherCode == currentCode)
                    return percantage;
            }
            break;
            case 1:
            {
                int index = 0;
                voucherFile >> index;
                for (int i = 0; i < index; i++)
                {
                    int catId = -1;
                    voucherFile >> catId;
                }
                int percentage = -1;
                voucherFile >> percentage;
                if (voucherCode == currentCode)
                    return percentage;
            }
                break;
            case 2:
            {
                int percentage = -1;
                voucherFile >> percentage;
                if (voucherCode == currentCode)
                    return percentage;
            }
                break;
        }

        voucherFile.ignore();
    }

    voucherFile.close();

    return result;
}

double findVoucher(const MyString& voucherCode, double totalSum)
{
    std::ifstream voucherFile("VouchersCodes.txt");

    if (!voucherFile.is_open())
    {
        std::cout << "File does not open!";
        return -1;
    }

    double result = 0;
    while (!voucherFile.eof())
    {
        if (voucherFile.peek() == -1)
            break;

        MyString currentCode;
        voucherFile >> currentCode;
        int type = -1;
        voucherFile >> type;

        switch (type)
        {
            case 0:
            {
                int categoryId = -1;
                voucherFile >> categoryId;
                int percantage = 0;
                voucherFile >> percantage;
                if (voucherCode == currentCode)
                {
                    double sum = findCurrentDisscount(categoryId);
                    result = (percantage * sum) * 1.0 / 100;
                }
            }
                 break;
            case 1:
            {
                int index = 0;
                voucherFile >> index;
                for (int i = 0; i < index; i++)
                {
                    int catId = -1;
                    voucherFile >> catId;
                    if (voucherCode == currentCode)
                    {
                        double sum = findCurrentDisscount(catId);
                        result += sum;
                    }
                }
                int percentage = -1;
                voucherFile >> percentage;
                if (voucherCode == currentCode)
                {
                    result = (percentage * result) * 1.0 / 100;
                }
            }
                break;
            case 2:
            {
                int percentage = -1;
                voucherFile >> percentage;
                if (voucherCode == currentCode)
                {
                    result = (percentage * totalSum) * 1.0 / 100;
                }
            }
                break;
        }

        voucherFile.ignore();
    }

    voucherFile.close();

    return result;
}

void sell(int id)
{
    std::ofstream currrentTransaction("currentTransaction.txt");
    if (!currrentTransaction.is_open())
    {
        std::cout << "File does not open!";
        return;
    }
    double totalSum = 0;
    while (true)
    {
        std::cout << "Products:" << '\n';
        printProductsForSell();
        std::cout << '\n';

        int transId = changeTransId();
        std::cout << "Transaction ID: " << transId << '\n';
        std::cout << "Price: " << totalSum << '\n';
        std::cout << '\n';
        std::cout << "Enter product NAME to sell:. Enter END to end the transaction:" << '\n';
        MyString input;
        std::cin >> input;

        if (input == "END")
            break;
        currrentTransaction << input << ' ';

        std::cout << "Enter quantity:" << '\n';
        int quantity = 0;
        std::cin >> quantity;
        currrentTransaction << quantity << std::endl;

        double currentSum = editProductQuantity(input, quantity);
        totalSum += currentSum;
    }

    std::cout << "Add voucher: (Y/N)? ";
    bool wantVoucher = false;
    std::cin >> wantVoucher;
    if (wantVoucher)
    {
        std::cout << "Enter voucher: ";;
        MyString voucherCode;
        std::cin >> voucherCode;
        totalSum = totalSum - findVoucher(voucherCode, totalSum);

        int percent = getPercentage(voucherCode);
        std::cout << percent << "% applied! ";
    }

    std::cout << "Transaction complete!" << '\n';
    std::cout << '\n';

    int transId = getTransId();
    char* buffer = new char[50];
    std::snprintf(buffer, 50, "%d", transId);

    char first[50] = "receipt_";
    char second[6] = ".txt";
    strcat_s(first, buffer);
    strcat_s(first, second);
    
    std::cout << "Receipt saved as " << first << '\n';
    std::cout << "Total: " << totalSum << " euro :)";
    std::cout << '\n';
    
    addTransactionToCashier(id);
    currrentTransaction.close();

    char filePath[120] = "D:\\university programming\\Supermarket\\Supermarket\\ReceiptsAreHere\\";
    strcat_s(filePath, first);
    std::ofstream receipt(filePath);
    std::ifstream currTrans("currentTransaction.txt");

    if (!receipt.is_open() || !currTrans.is_open())
    {
        std::cout << "File does not open";
        return;
    }

    receipt << "RECEIPT" << '\n';
    receipt << '\n';
    receipt << "TRANSACTION_ID: " << transId << '\n';
    receipt << '\n';
    receipt << "CASHIER_ID: " << id << '\n';
    receipt << '\n';
    receipt << "Date: " << "today" << '\n';
    receipt << '\n';
    receipt << "--------------------" << '\n';
    
    double totSum = 0;
    while (!currTrans.eof())
    {
        if (currTrans.peek() == -1)
            break;

        receipt << '\n';
        MyString productname;
        int quantity = 0;
        currTrans >> productname >> quantity;

        double currPrice = findProductPrice(productname);
        double currSum = currPrice * quantity;
        totSum += currSum;

        receipt << productname << '\n';
        receipt << '\n';
        receipt << quantity << '*' << currPrice << '-' << currSum;
        receipt << '\n';

        currTrans.ignore();
    }
    receipt << '\n';
    receipt << "TOTAL:" << totSum << '\n';

    receipt.close();
    currTrans.close();
    std::ofstream filee("currentTransaction.txt", std::ios::trunc);
    filee.close();
}

void addTransactionToCashier(int cashierId)
{
    std::ifstream first("cashiersTransactionsCitations.txt", std::ios::app);
    std::ofstream second("temp.txt", std::ios::app);

    if (!first.is_open() || !second.is_open())
    {
        std::cout << "Not opening";
        return;
    }

    while (!first.eof())
    {
        if (first.peek() == -1)
            break;

        int currentId = 0;
        int numOfTransactions = 0;
        int numOfCitations = 0;

        first >> currentId >> numOfTransactions >> numOfCitations;
        if(cashierId == currentId)
        second << currentId << ' ' << numOfTransactions + 1 << ' ' << numOfCitations << std::endl;
        else
        second << currentId << ' ' << numOfTransactions + 1 << ' ' << numOfCitations << std::endl;

        int index = 0;
        if (cashierId == currentId)
            if ((numOfTransactions + 1) % 3 == 0)
                index = numOfCitations - 1;
            else
            {
                index = numOfCitations;
            }
        else
        {
            index = numOfCitations;
        }
        for (int i = 0; i < index; i++)
        {
            first.ignore();
            char sender[100];
            first.getline(sender, 100);

            char description[100];
            first.getline(description, 100);

            int points = 0;
            first >> points;

            second << sender << std::endl;
            second << description << std::endl;
            second << points << std::endl;
        }
        if (cashierId == currentId)
        {
            first.ignore();
            char sender[100];
            first.getline(sender, 100);

            char description[100];
            first.getline(description, 100);

            int points = 0;
            first >> points;
        }
        first.ignore();
    }

    first.close();
    second.close();

    std::remove("cashiersTransactionsCitations.txt");
    std::rename("temp.txt", "cashiersTransactionsCitations.txt");
}