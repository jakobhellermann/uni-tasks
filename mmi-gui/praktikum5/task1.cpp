#include <string>
#include <iostream>
#include <fstream>
#include <vector>


class ShoppingCartEntry {
public:
    std::string name;

    ShoppingCartEntry(std::string name) : name(name) {
    }

    virtual std::string getDescription() = 0;

    virtual double getPrice() = 0;

    virtual ~ShoppingCartEntry() = default;
};


class ItemEntry : public ShoppingCartEntry {
    int count;
    double pricePerItem;

public:
    ItemEntry(std::string name, int count, double pricePerItem): ShoppingCartEntry(name),
                                                                 count(count),
                                                                 pricePerItem(pricePerItem) {
    }

    std::string getDescription() override;

    double getPrice() override;
};


std::string ItemEntry::getDescription() {
    return name + " quantity " + std::to_string(count) + ", item price: " + std::to_string(pricePerItem);
}

double ItemEntry::getPrice() {
    return count * pricePerItem;
}


class BulkGoodEntry : public ShoppingCartEntry {
    double weight;
    double pricePerKg;

public:
    BulkGoodEntry(std::string name, double weight, double pricePerKg): ShoppingCartEntry(name),
                                                                       weight(weight),
                                                                       pricePerKg(pricePerKg) {
    }

    std::string getDescription() override;

    double getPrice() override;
};


std::string BulkGoodEntry::getDescription() {
    return name + " weight " + std::to_string(weight) + ", price per kg: " + std::to_string(pricePerKg);
}

double BulkGoodEntry::getPrice() {
    return pricePerKg * weight;
}

class VolumeEntry : public ShoppingCartEntry {
    double length, width, height;
    double pricePerMeterCubed;

public:
    VolumeEntry(std::string name, double length, double width, double height,
                double pricePerMeterCubed): ShoppingCartEntry(name),
                                            length(length),
                                            width(width),
                                            height(height),
                                            pricePerMeterCubed(pricePerMeterCubed) {
    }

    std::string getDescription() override;

    double getPrice() override;
};


std::string VolumeEntry::getDescription() {
    return name + ": volume (" + std::to_string(length) + "," + std::to_string(width) + "," + "," +
           std::to_string(height) + "), price per m^3: " + std::to_string(pricePerMeterCubed);
}

double VolumeEntry::getPrice() {
    double volume = length * width * height;
    return volume * pricePerMeterCubed;
}

class ShoppingCart {
    std::vector<ShoppingCartEntry *> entries;

public:
    // was created with new, passes ownership
    void addEntry(ShoppingCartEntry *entry) {
        entries.push_back(entry);
    }


    void print() const {
        printInner(std::cout);
    }

    static void writeToFile(const ShoppingCart &cart, const std::string &fileName) {
        std::ofstream outfile;
        outfile.open(fileName);
        cart.printInner(outfile);
        outfile.close();
        if (outfile.fail()) {
            throw std::runtime_error("Could not write to file " + fileName);
        }
    }

    ~ShoppingCart() {
        for (auto entry: entries) {
            delete entry;
        }
    }

private:
    void printInner(std::ostream &o) const {
        for (auto entry: entries) {
            o << "- " << entry->getDescription() << " -> price: " << entry->getPrice() << std::endl;
        }
    }
};


int main() {
    auto cart = ShoppingCart();
    cart.addEntry(new ItemEntry("Kiwi", 2, 1.5));
    cart.addEntry(new BulkGoodEntry("Sugar", 0.5, 2));
    cart.addEntry(new VolumeEntry("?", 1, 2, 3, 4));

    cart.print();

    ShoppingCart::writeToFile(cart, "out.txt");
}

