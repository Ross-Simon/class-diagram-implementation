// Class Diagram Implementation (Eguia, Ross Simon S.)

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Product {
private:
    string productID;
    float productPrice;
    string productName;

public:
    Product(string id, string name, float price) : productID(id), productName(name), productPrice(price) {}

    string getID() { return productID; }
    string getName() { return productName; }
    float getPrice() { return productPrice; }

    void display() {
        cout << productID << setw(32 - productID.length()) << productName << setw(20) << productPrice << "\n";
    }
};

class CartItem {
public:
    Product product;
    int quantity;

    CartItem(Product prod) : product(prod), quantity(1) {}
};

class ShoppingCart {
private:
    CartItem* items[100];
    int itemCount = 0;

public:
    void addProduct(Product product) {
        for (int i = 0; i < itemCount; i++) {
            if (items[i]->product.getID() == product.getID()) {
                items[i]->quantity++;
                return;
            }
        }
        if (itemCount < 100) {
            items[itemCount++] = new CartItem(product);
        }
    }

    void viewCart() {
        cout << "Shopping Cart:\nProduct ID\tName\t\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++) {
            cout << items[i]->product.getID() << "\t\t" << items[i]->product.getName() << "\t" 
                 << items[i]->product.getPrice() << "\t" << items[i]->quantity << "\n";
        }
    }

    CartItem** getItems() {
        return items;
    }

    int getItemCount() {
        return itemCount;
    }

    double checkout() {
        double total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += items[i]->product.getPrice() * items[i]->quantity;
            delete items[i];
        }
        itemCount = 0;
        return total;
    }
};

class Order {
private:
    static int orderCounter;
    int orderId;
    double totalAmount;
    CartItem* items[100];
    int itemCount;

public:
    Order(ShoppingCart cart) : orderId(orderCounter++), totalAmount(cart.checkout()), itemCount(cart.getItemCount()) {
        for (int i = 0; i < itemCount; i++) {
            items[i] = new CartItem(cart.getItems()[i]->product);
            items[i]->quantity = cart.getItems()[i]->quantity;
        }
    }

    void display() {
        cout << "Order ID: " << orderId << "\n";
        cout << "Total Amount: $" << totalAmount << "\n";
        cout << "Order Details:\n";
        cout << "Product ID\tName\t\tPrice\tQuantity\n";
        for (int i = 0; i < itemCount; i++) {
            cout << items[i]->product.getID() << "\t\t" 
                 << items[i]->product.getName() << "\t" 
                 << items[i]->product.getPrice() << "\t" 
                 << items[i]->quantity << "\n";
        }
        cout << "\n";
    }
};

int Order::orderCounter = 1;

class OLStoreSystem {
private:
    Product products[5] = {
        Product("01A", "Laptop Bag", 350.00),
        Product("01B", "Wireless Mouse", 250.00),
        Product("01C", "Keyboard Cover", 150.00),
        Product("01D", "Laptop Charger", 350.00),
        Product("01E", "Cleaning Kit", 300.00)
    };

    ShoppingCart cart;
    Order* orders[100];
    int orderCount = 0;

public:
    void displayProducts() {
        cout << "\nList of Products\n";
        cout << "Product ID" << setw(15) << "Name" << setw(30) << "Price\n\n";
        for (int i = 0; i < 5; i++) {
            products[i].display();
        }
    }

    void menu() {
        int menuInput;
        do {
            cout << "__________________________________________\n";
            cout << "_     Laptop Essentials Online Store     -\n";
            cout << "__________________________________________\n\n";

            cout << "Menu: \n";
            cout << "1 - View and Order Products\n";
            cout << "2 - View Shopping Cart\n";
            cout << "3 - View Orders\n";
            cout << "4 - Exit\n";
            cout << "Kindly Enter [1-4]: ";
            cin >> menuInput;

            switch (menuInput) {
                case 1:
                    displayProducts();
                    addProductToCart();
                    break;
                case 2:
                    viewShoppingCart();
                    break;
                case 3:
                    viewOrders();
                    break;
                case 4:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid input. Please try again.\n";
            }
        } while (menuInput != 4);
    }

    void addProductToCart() {
        while (true) {
            string id;
            cout << "Enter the Product ID of the item you want to add to the shopping cart (0 to stop): ";
            cin >> id;
            if (id == "0") break;

            for (int i = 0; i < 5; i++) {
                if (products[i].getID() == id) {
                    cart.addProduct(products[i]);
                    cout << "Product added successfully!\n";
                    break;
                }
            }
        }
    }

    void viewShoppingCart() {
        cart.viewCart();
        char choice;
        cout << "Do you want to check out all the products? (Y/N): ";
        cin >> choice;
        if (choice == 'Y' || choice == 'y') {
            if (orderCount < 100) {
                orders[orderCount++] = new Order(cart);
                cout << "You have successfully checked out the products!\n";
            } else {
                cout << "Order limit reached!\n";
            }
        }
    }

    void viewOrders() {
        cout << "Orders:\n";
        for (int i = 0; i < orderCount; i++) {
            orders[i]->display();
        }
    }
};

int main() {
    OLStoreSystem system;
    system.menu();
    return 0;
}