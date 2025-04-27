#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

struct Person {
    int id;
    string name;
};

struct Meal {
    int id;
    string name;
    double price;
};

string loggedInAdmin;
string loggedInStudent;

void registerAdmin();
bool adminLogin();
void adminMenu();
void addStudent();
void addMeal();
void deleteMeal();
void viewMeals();
bool studentLogin();
void studentMenu();
void placeOrder();
void generateBill();
void giveFeedback();

const string adminFilePath = "D:\\PF LAb project Practices\\Group_no_3\\admin.txt";
const string studentFilePath = "D:\\PF LAb project Practices\\Group_no_3\\students.txt";
const string mealFilePath = "D:\\PF LAb project Practices\\Group_no_3\\meals.txt";
const string orderFilePath = "D:\\PF LAb project Practices\\Group_no_3\\orders.txt";
const string feedbackFilePath = "D:\\PF LAb project Practices\\Group_no_3\\feedback.txt";

int main() {
    int choice;
    do {
        cout << "======================================\n";
        cout << "|      Mess Management System        |\n";
        cout << "======================================\n";
        cout << "| 1. Admin Login                     |\n";
        cout << "| 2. Admin Register                  |\n";
        cout << "| 3. Student Login                   |\n";
        cout << "| 4. Exit                            |\n";
        cout << "======================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        while(cin.fail() || choice < 1 || choice > 4) {
            cout << "Invalid input. Please enter a valid choice (1-4): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                if (adminLogin()) adminMenu();
                break;
            case 2:
                registerAdmin();
                break;
            case 3:
                if (studentLogin()) studentMenu();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
    return 0;
}

void registerAdmin() {
    string username, password;

    cout << "=== Admin Registration ===\n";
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    ofstream adminFile(adminFilePath, ios::app);
    adminFile << username << " " << password << "\n";
    adminFile.close();

    cout << "Admin registered successfully!\n";
}

bool adminLogin() {
    string username, password, fileUser, filePass;

    cout << "=== Admin Login ===\n";
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    ifstream adminFile(adminFilePath);
    while (adminFile >> fileUser >> filePass) {
        if (fileUser == username && filePass == password) {
            loggedInAdmin = username;
            cout << "Login successful! Welcome, " << username << "!\n";
            return true;
        }
    }

    cout << "Invalid credentials.\n";
    return false;
}

void adminMenu() {
    int choice;
    do {
        cout << "====================================\n";
        cout << "|         Admin Dashboard          |\n";
        cout << "====================================\n";
        cout << "| 1. Add Student                   |\n";
        cout << "| 2. Add Meal                      |\n";
        cout << "| 3. Delete Meal                   |\n";
        cout << "| 4. View Meals                    |\n";
        cout << "| 5. Logout                        |\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        while(cin.fail() || choice < 1 || choice > 5) {
            cout << "Invalid input. Please enter a valid choice (1-5): ";
            cin.clear();
            cin.ignore(numeric_limits
            <streamsize>::max(), '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                addMeal();
                break;
            case 3:
                deleteMeal();
                break;
            case 4:
                viewMeals();
                break;
            case 5:
                cout << "Logging out...\n";
                loggedInAdmin.clear();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (!loggedInAdmin.empty());
}

void addStudent() {
    int id;
    string name;

    cout << "=== Add Student ===\n";
    cout << "Enter Student ID: ";
    cin >> id;
    cin.ignore();
    
    while(cin.fail() || id <= 0) {
        cout << "Invalid ID. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> id;
    }

    cout << "Enter Student Name: ";
    getline(cin, name);

    ofstream studentFile(studentFilePath, ios::app);
    studentFile << id << " " << name << "\n";
    studentFile.close();

    cout << "Student added successfully!\n";
}

void addMeal() {
    int id;
    string name;
    double price;

    cout << "=== Add Meal ===\n";
    cout << "Enter Meal ID: ";
    cin >> id;
    cin.ignore();
    
    while(cin.fail() || id <= 0) {
        cout << "Invalid Meal ID. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> id;
    }

    cout << "Enter Meal Name: ";
    getline(cin, name);

    cout << "Enter Meal Price: ";
    cin >> price;

    while(cin.fail() || price <= 0) {
        cout << "Invalid price. Please enter a valid price: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> price;
    }

    ofstream mealFile(mealFilePath, ios::app);
    mealFile << id << " " << name << " " << price << "\n";
    mealFile.close();

    cout << "Meal added successfully!\n";
}

void viewMeals() {
    cout << "=== Meal List ===\n";

    ifstream mealFile(mealFilePath);
    if (!mealFile) {
        cout << "No meals available.\n";
        return;
    }

    int id;
    string name;
    double price;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(10) << "Price" << "\n";
    cout << "-----------------------------------\n";

    while (mealFile >> id >> name >> price) {
        cout << left << setw(10) << id << setw(20) << name << setw(10) << price << "\n";
    }

    mealFile.close();
}

void deleteMeal() {
    int deleteId;
    cout << "=== Delete Meal ===\n";
    cout << "Enter Meal ID to delete: ";
    cin >> deleteId;

    ifstream mealFile(mealFilePath);
    ofstream tempFile("temp.txt");
    int id;
    string name;
    double price;
    bool found = false;

    while (mealFile >> id >> name >> price) {
        if (id == deleteId) {
            found = true;
            continue;
        }
        tempFile << id << " " << name << " " << price << "\n";
    }

    mealFile.close();
    tempFile.close();
    remove(mealFilePath.c_str());
    rename("temp.txt", mealFilePath.c_str());

    if (found) {
        cout << "Meal deleted successfully!\n";
    } else {
        cout << "Meal not found.\n";
    }
}

bool studentLogin() {
    int id;
    string name, fileName;
    cout << "=== Student Login ===\n";
    cout << "Enter Student ID: ";
    cin >> id;
    
    while(cin.fail() || id <= 0) {
        cout << "Invalid ID. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> id;
    }

    cin.ignore();
    cout << "Enter Student Name: ";
    getline(cin, name);

    ifstream studentFile(studentFilePath);
    bool found = false;

    while (studentFile >> id >> fileName) {
        if (fileName == name) {
            loggedInStudent = name;
            found = true;
            break;
        }
    }

    studentFile.close();

    if (!found) {
        cout << "Student not found. Please check your credentials.\n";
        return false;
    }

    cout << "Login successful! Welcome, " << name << "!\n";
    return true;
}

void studentMenu() {
    int choice;
    do {
        cout << "====================================\n";
        cout << "|        Student Dashboard         |\n";
        cout << "====================================\n";
        cout << "| 1. Place Order                   |\n";
        cout << "| 2. View Meals                    |\n";
        cout << "| 3. View Bill                     |\n";
        cout << "| 4. Give Feedback                 |\n";
        cout << "| 5. Logout                        |\n";
        cout << "====================================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        while(cin.fail() || choice < 1 || choice > 5) {
            cout << "Invalid input. Please enter a valid choice (1-5): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> choice;
        }

        switch (choice) {
            case 1:
                placeOrder();
                break;
            case 2:
                viewMeals();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                giveFeedback();
                break;
            case 5:
                cout << "Logging out...\n";
                loggedInStudent.clear();
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (!loggedInStudent.empty());
}

void placeOrder() {
    int mealId, quantity;
    cout << "=== Place Order ===\n";
    cout << "Enter Meal ID: ";
    cin >> mealId;

    while(cin.fail() || mealId <= 0) {
        cout << "Invalid Meal ID. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> mealId;
    }

    cout << "Enter Quantity: ";
    cin >> quantity;

    while(cin.fail() || quantity <= 0) {
        cout << "Invalid Quantity. Please enter a positive number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> quantity;
    }

    ifstream mealFile(mealFilePath);
    int id;
    string name;
    double price;
    bool found = false;

    while (mealFile >> id >> name >> price) {
        if (id == mealId) {
            found = true;
            ofstream orderFile(orderFilePath, ios::app);
            orderFile << loggedInStudent << " " << mealId << " " << quantity << " " << price * quantity << "\n";
            orderFile.close();
            cout << "Order placed successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "Meal not found.\n";
    }
    mealFile.close();
}

void generateBill() {
    ifstream orderFile(orderFilePath);
    string studentName;
    int mealId, quantity;
    double amount;

    cout << "=== View Bill ===\n";
    cout << "Student: " << loggedInStudent << "\n";
    cout << "----------------------------------\n";
    cout << left << setw(10) << "Meal ID" << setw(10) << "Quantity" << setw(10) << "Amount" << "\n";

    while (orderFile >> studentName >> mealId >> quantity >> amount) {
        if (studentName == loggedInStudent) {
            cout << left << setw(10) << mealId << setw(10) << quantity << setw(10) << amount << "\n";
        }
    }

    orderFile.close();
}

void giveFeedback() {
    string feedback;

    cout << "=== Give Feedback ===\n";
    cout << "Enter your feedback: ";
    getline(cin, feedback);

    ofstream feedbackFile(feedbackFilePath, ios::app);
    feedbackFile << loggedInStudent << ": " << feedback << "\n";
    feedbackFile.close();

    cout << "Feedback submitted successfully!\n";
}
