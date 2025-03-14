#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>

using namespace std;

struct Item {
    int id;
    string name;
    int quantity;
    double price;
};

class Inventory {
private:
    vector<Item> items;
    int nextId = 1;
public:
    void addItem(string name, int quantity, double price) {
        items.push_back({nextId++, name, quantity, price});
        cout << "Item added successfully!" << endl;
    }

    void displayItems() {
        if (items.empty()) {
            cout << "No items in inventory." << endl;
            return;
        }
        cout << "\n----------------------------------------\n";
        cout << "ID\tName\t\tQuantity\tPrice\n";
        cout << "----------------------------------------\n";
        for (const auto& item : items) {
            cout << item.id << "\t" << item.name << "\t\t" << item.quantity << "\t\t" << item.price << endl;
        }
    }

    void updateQuantity(int id, int newQuantity) {
        for (auto& item : items) {
            if (item.id == id) {
                item.quantity = newQuantity;
                cout << "Quantity updated successfully!" << endl;
                return;
            }
        }
        cout << "Item not found!" << endl;
    }

    void deleteItem(int id) {
        char confirm;
        cout << "Are you sure you want to delete item ID " << id << "? (y/n): ";
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y') {
            for (auto it = items.begin(); it != items.end(); ++it) {
                if (it->id == id) {
                    items.erase(it);
                    cout << "Item deleted successfully!" << endl;
                    return;
                }
            }
            cout << "Item not found!" << endl;
        } else {
            cout << "Deletion canceled." << endl;
        }
    }

    void searchItem(string searchName) {
        bool found = false;
        for (const auto& item : items) {
            if (item.name == searchName) {
                cout << "Found: ID " << item.id << " - " << item.name << " - Quantity: " << item.quantity << " - Price: " << item.price << endl;
                found = true;
            }
        }
        if (!found) cout << "Item not found!" << endl;
    }

    void sortByPrice() {
        sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
            return a.price < b.price;
        });
        cout << "Items sorted by price!" << endl;
    }

    void calculateTotalValue() {
        double totalValue = 0;
        for (const auto& item : items) {
            totalValue += item.quantity * item.price;
        }
        cout << "Total Inventory Value: $" << totalValue << endl;
    }
};

int main() {
    Inventory inventory;
    int choice;
    
    do {
        cout << "\nInventory Management System" << endl;
        cout << "1. Add Item" << endl;
        cout << "2. Display Items" << endl;
        cout << "3. Update Quantity" << endl;
        cout << "4. Delete Item" << endl;
        cout << "5. Search Item" << endl;
        cout << "6. Sort Items by Price" << endl;
        cout << "7. Calculate Total Inventory Value" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int quantity;
                double price;
                cin.ignore(); // Ignore leftover newline
                cout << "Enter item name: ";
                getline(cin, name);
                cout << "Enter quantity: ";
                while (!(cin >> quantity)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Enter a valid number: ";
                }
                cout << "Enter price: ";
                while (!(cin >> price)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input! Enter a valid price: ";
                }
                inventory.addItem(name, quantity, price);
                break;
            }
            case 2:
                inventory.displayItems();
                break;
            case 3: {
                int id, newQuantity;
                cout << "Enter item ID: ";
                cin >> id;
                cout << "Enter new quantity: ";
                cin >> newQuantity;
                inventory.updateQuantity(id, newQuantity);
                break;
            }
            case 4: {
                int id;
                cout << "Enter item ID to delete: ";
                cin >> id;
                inventory.deleteItem(id);
                break;
            }
            case 5: {
                string searchName;
                cin.ignore();
                cout << "Enter item name to search: ";
                getline(cin, searchName);
                inventory.searchItem(searchName);
                break;
            }
            case 6:
                inventory.sortByPrice();
                break;
            case 7:
                inventory.calculateTotalValue();
                break;
            case 8:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);
    
    return 0;
}
