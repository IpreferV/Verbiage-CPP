#include <iostream>
#include <map>

typedef class UI {
public:
    std::string screen_clear = "\033[H\033[2J";
    std::string tx_green = "\u001B[32m";
    std::string tx_red = "\u001B[31m";
    std::string tx_blue = "\u001B[34m";
    std::string tx_magenta = "\u001B[35m";
    std::string tx_cyan = "\u001B[36m";
    std::string bg_black = "\u001B[40m";
    std::string bg_white = "\u001B[47m";
    std::string bg_yellow = "\u001B[43m";
    std::string bg_red = "\u001B[41m";
    std::string bg_magenta = "\u001B[45m";
    std::string bg_blue = "\u001B[44m";
    std::string bg_green = "\u001B[42m";
    std::string bg_tx_reset = "\u001B[0m";

    void dash() {
        for (int i = 0; i <= 104; ++i) {
            std::cout << "-";
        }
        std::cout << '\n';
    }
} Vanity;
Vanity ui;
class Report {
protected:
    std::string platform;
    std::string version;
    std::string title;
    std::string description;
    std::string steps;
    std::string status;
public:
    Report(std::string platform, std::string version, std::string title, std::string description, std::string steps, std::string status) {
        this->platform = platform;
        this->version = version;
        this->title = title;
        this->description = description;
        this->steps = steps;
        this->status = status;
    }
    std::string platform_get() {
        return platform;
    }
    std::string version_get() {
        return version;
    }
    std::string title_get() {
        return title;
    }
    std::string description_get() {
        return description;
    }
    std::string steps_get() {
        return steps;
    }
    std::string status_get() {
        return status;
    }
};
class Bug {
protected:
    std::map<int, Report> bug;
    int id;
public:
    Bug() : id(0) {}

    bool contains_key(int id) {
        return bug.find(id) != bug.end();
    }
    void bug_add(std::string platform, std::string version, std::string title, std::string description, std::string steps, std::string status) {
        bug.emplace(++id, Report(platform, version, title, description, steps, status));
    }
    void bug_status(int id) {
        std::string status = bug.at(id).status_get();
        if (status == "Pending Review") {
            std::cout << ui.bg_black;
            std::printf(" %-15s ", "Pending Review");
            std::cout << ui.bg_tx_reset;
        } else if (status == "Low") {
            std::cout << ui.bg_white;
            std::printf(" %-15s ", "Low");
            std::cout << ui.bg_tx_reset;
        } else if (status == "Medium") {
            std::cout << ui.bg_yellow;
            std::printf(" %-15s ", "Medium");
            std::cout << ui.bg_tx_reset;
        } else if (status == "High") {
            std::cout << ui.bg_red;
            std::printf(" %-15s ", "High");
            std::cout << ui.bg_tx_reset;
        } else if (status == "Critical") {
            std::cout << ui.bg_magenta;
            std::printf(" %-15s ", "Critical");
            std::cout << ui.bg_tx_reset;
        } else if (status == "Resolved") {
            std::cout << ui.bg_green;
            std::printf(" %-15s ", "Resolved");
            std::cout << ui.bg_tx_reset;
        } else if (status == "WAI") {
            std::cout << ui.bg_blue;
            std::printf(" %-15s ", "WAI");
            std::cout << ui.bg_tx_reset;
        } else {
            std::cout << "null";
        }
    }
    void bug_display() {
        ui.dash();
        std::printf("| %-3s | %-15s | %-12s | %-8s | %-51s |\n","ID", "Priority", "Platform", "Version", "Title");
        ui.dash();

        for (auto pair : bug) {
            std::printf("| %3i |", pair.first);

            bug_status(pair.first);
            
            std::printf("| %-12s | %-8s | %-51.50s |\n", pair.second.platform_get().c_str(), pair.second.version_get().c_str(), pair.second.title_get().c_str());
        }
        ui.dash();
    }
    void bug_details(int id) {
        ui.screen_clear;

        ui.dash();
        std::cout << "ID: " << id << " | Title: " << ui.bg_white << bug.at(id).title_get() << ui.bg_tx_reset;
        std::cout << ui.tx_cyan <<"\nDescription: " << ui.bg_tx_reset << bug.at(id).description_get();
        std::cout << ui.tx_cyan << "\n\nSteps to Recreate: " << ui.bg_tx_reset << bug.at(id).steps_get() << std::endl;
        ui.dash();

        std::cout << "Platform: " << bug.at(id).platform_get() << std::endl;
        std::cout << "Version: " << bug.at(id).version_get() << std::endl;
        std::cout << "Status: ";
        bug_status(id);
    }
};

void welcome_screen() {
    std::cout << ui.screen_clear;

    std::cout << "Welcome to " << ui.tx_cyan << "Verbiage" << ui.bg_tx_reset << "!" << std::endl;
}
void main_menu() {
    std::cout << ui.tx_blue << "\n1. Report a Bug" << ui.tx_green << " | 2. See Existing Bugs" << ui.tx_magenta << " | 3. Manage Bugs (Login as a Developer)" << ui.bg_tx_reset << " | 4. Read Manual" << " | 5. Exit" << std::endl;

    int choice = 0;
    std::cout << "Select an Operation:\n-> ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        /* code */
        break;
    case 2:

        break;
    case 3:

        break;
    case 4: 

        break;
    case 5:
        std::exit(0);
        break;
    default:
        break;
    }
}
int main() {
    // welcome_screen();
    // main_menu();

    Bug repottttt;

    repottttt.bug_add("Windows", "v1.0a", "Title1", "description", "steps", "Low");
    repottttt.bug_add("Mac", "v1.0a", "Title2", "description", "steps", "Medium");

    repottttt.bug_details(1);

    return 0;
}