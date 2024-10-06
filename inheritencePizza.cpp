#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <vector>

class Pizza{

private:
	std::string size;
	std::string type;
	std::vector<std::string> toppings;
	double price;
	
	void calculateCost() {
		double wholePrice;
        if (size == "small") {
            price = 10.00;
        } else if (size == "medium") {
            price = 14.00;
        } else if (size == "large") {
            price = 17.00;
        }

        price += toppings.size() * 2.00;
        
    }
	
	
public:
	
	Pizza(std::string size, std::string type, std::vector<std::string> toppings, double price) {
        this->size = size;
        this->type = type;
        this->toppings = toppings;
        this->price = price;
        calculateCost();
    }
	
	
	
    std::string getSize(){
        return size;
    }

    std::string getType(){
        return type;
    }

    std::vector<std::string> getToppings(){
        return toppings;
    }

    double getPrice(){
        return price;
    }
    
   virtual double getDeliveryFee(){
    	return 0.0;
	}
    
    void calculatePizzaCost() {
        calculateCost();
    }
	
};//end of pizza class

class DeliveredPizza : public Pizza {
	
private:
    double deliveryFee;
    double totalPrice;
    std::string deliveryAddress;

public:
	
	DeliveredPizza(std::string size, std::string type, std::vector<std::string> toppings, double price, std::string deliveryAddress)
    : Pizza(size, type, toppings, price) {
	    this->deliveryAddress = deliveryAddress;

	    calculatePizzaCost();
	
	    if (price > 20.00) {
	        this->deliveryFee = 3.50;
	    } else {
	        this->deliveryFee = 5.00;
	    }
		
		
	    this->totalPrice = getPrice() + this->deliveryFee;
	}
    
    double getDeliveryFee(){
        return deliveryFee;
    }

    double getTotalPrice(){
        return totalPrice;
    }

    std::string getDeliveryAddress(){
        return deliveryAddress;
    }
    
    
};//end of delivered pizza class

//protoypes
void getPizzaDetails(std::string& size, std::string& type, std::vector<std::string>& toppings, std::string availableToppings[], std::string& address, int numToppings);
std::ostream& operator<<(std::ostream& outPut, Pizza& pizza);
std::ostream& operator<<(std::ostream& outPut, DeliveredPizza& pizza);



int main(){
	
	std::cout<< std::setprecision(2)<<std::fixed;
	
	std::string size;
    std::string type;
    std::vector<std::string> toppings;
    std::string address;
    double price;

    std::string availableToppings[] = {"Pepperoni", "Mushrooms", "Onions", "Green pepper", "Tomatoes", "Jalapenos"};
    int numToppings = sizeof(availableToppings) / sizeof(availableToppings[0]);

    getPizzaDetails(size, type, toppings, availableToppings, address, numToppings);



    

    
    

    if (!address.empty()) {
        DeliveredPizza deliveredPizza(size, type, toppings, price, address);
        std::cout<< "\nPizza details: \n";
        std::cout<< deliveredPizza;
    } else {
    	Pizza pizza(size, type, toppings, price);
        std::cout<< "\nPizza Details: \n";
        std::cout<< pizza;
    }

    
 
	
	return 0;
}


void getPizzaDetails(std::string& size, std::string& type, std::vector<std::string>& toppings, std::string availableToppings[], std::string& address, int numToppings) {
    std::cout<< "What size pizza would you like to order?\n1.Small\n2.Medium\n3.Large : \n";
    std::cout<<"-------> ";
    int userSize;
    std::cin>> userSize;
        while (std::cin.fail() || userSize < 1 || userSize > 3) {
	        std::cin.clear();
	        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	        std::cout<<"Invalid input. Please enter a valid size: ";
	        std::cin>>userSize;
    	}
    
     switch (userSize) {
        case 1:
            size = "small";
            break;
        case 2:
            size = "medium";
            break;
        case 3:
            size = "large";
            break;
        default:
            size = "small";
            break;
	}

    std::cout<< "What type of crust would you like to order? \n1.Classic\n2.Deep dish\n3.Thin crust: \n";
    int userType;
    std::cout<<"-------> ";
    std::cin>>userType;
        while (std::cin.fail() || userType < 1 || userType > 3) {
	        std::cin.clear();
	        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	        std::cout<<"Invalid input. Please enter a valid choice: ";
	        std::cin>>userType;
    	}
    
     switch (userType) {
        case 1:
            type = "classic";
            break;
        case 2:
            type = "deep dish";
            break;
        case 3:
            type = "thin crust";
            break;
        default:
            type = "classic";
            break;
    }
    

    std::cout<< "Enter the number of toppings you would like: \n";
    std::cout<<"-------> ";
    int numUserToppings;
    std::cin>>numUserToppings;
        while (std::cin.fail() || numUserToppings < 0) {
	        std::cin.clear();
	        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	        std::cout<<"Invalid input. Please enter a valid choice: ";
	        std::cin>>numUserToppings;
    	}

    std::cout<< "Available toppings:\n";
    for (int i = 0; i < numToppings; i++) {
        std::cout << (i + 1) << ": " << availableToppings[i] << std::endl;
    }

    for (int i = 0; i < numUserToppings; i++) {
        int toppingIndex;
        std::cout<< "\nEnter topping #" << (i + 1) << ": ";
        std::cin>> toppingIndex;
        toppingIndex--;
        if (toppingIndex >= 0 && toppingIndex < numToppings) {
            toppings.push_back(availableToppings[toppingIndex]);
        }
    }
    
    std::cout<< "\nChoose an option:\n";
    std::cout<< "1. Pick-up\n";
    std::cout<< "2. Delivery\n";
    std::cout<<"-------> ";
    int option;
    std::cin>> option;
        while (std::cin.fail() || option < 1 || option > 2) {
	        std::cin.clear();
	        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	        std::cout<<"Invalid input. Please enter a valid choice: ";
	        std::cin>>option;
    	}

    if (option == 2) {
        std::cout<< "Enter delivery address: \n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<"-------> ";
        std::getline(std::cin, address);
    }
}


std::ostream& operator<<(std::ostream& outPut, Pizza& pizza) {
    outPut<< "You ordered a " << pizza.getSize() << " " << pizza.getType() << " with these toppings: ";
    for (std::string& topping : pizza.getToppings()) {
        outPut << topping << " ";
    }
    outPut<< std::endl;
    outPut<< std::fixed << std::setprecision(2);
    outPut<< "Total: $" << pizza.getPrice() <<std::endl;

    return outPut;
}


std::ostream& operator<<(std::ostream& outPut, DeliveredPizza& pizza) {
    outPut<< "You ordered a " << pizza.getSize() << " " << pizza.getType() << " with these toppings: ";
    for (std::string& topping : pizza.getToppings()) {
        outPut << topping << " ";
    }
    outPut<< std::endl;
    outPut<< std::fixed << std::setprecision(2);
    outPut<< "Delivery fee: " << pizza.getDeliveryFee() <<std::endl;
    outPut<< "Total: $" << pizza.getTotalPrice() <<std::endl;
    outPut<< "Address: " << pizza.getDeliveryAddress() <<std::endl;

    return outPut;
}

