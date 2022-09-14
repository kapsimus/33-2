#include <iostream>
#include <memory>
#include <ctime>

class FishCaughtException: std::exception {
public:
    const char * what() const noexcept override {
        return "You caught the fish.";
    }
};

class BootCaughtException: std::exception {
public:
    const char * what() const noexcept override {
        return "You caught the boot.";
    }
};

class BaseObject {
public:
    virtual void Message() = 0;
};

class Fish: public BaseObject {
    void Message() override {
        throw FishCaughtException();
    }
};

class Boot: public BaseObject {
    void Message() override {
        throw BootCaughtException();
    }
};

int main() {
    std::shared_ptr<BaseObject> field[9];
    std::srand(std::time(nullptr));
    field[std::rand() % 9] = std::make_shared<Fish>();
    int count  = 3;
    do {
        int index = std::rand() % 9;
        if (field[index] == nullptr) {
            field[index] = std::make_shared<Boot>();
            count--;
        }
    } while (count > 0);

    count = 0;
    int number;
    while (true) {
        std::cout << "Enter number of sector (0-8):" << std::endl;
        std::cin >> number;
        if (std::cin.fail()) {
            std::cout << "Invalid number." << std::endl;
            std::cin.clear();
        } else if (number < 0 || number > 8) {
            std::cout << "Invalid number." << std::endl;
        } else {
            count++;
            try {
                if (field[number] != nullptr) {
                    field[number]->Message();
                } else {
                    std::cout << "Empty sector. Try again." << std::endl;
                }
            } catch (const BootCaughtException &ex) {
                std::cout << ex.what() << std::endl;
                break;
            } catch (const FishCaughtException &ex) {
                std::cout << ex.what() << std::endl;
                std::cout << "Number of attempts: " << count << std::endl;
                break;
            }
        }
    }
    return 0;
}
