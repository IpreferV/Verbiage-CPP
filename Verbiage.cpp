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
    void status_set(std::string status) {
        this->status = status;
    }
};
void welcome_screen();
void roach();
void bug_manual();
void bug_manage_details(int id);
void bug_manage();
void bug_manage_login();
void bug_report_details();
int bug_details_display();
void bug_list();
void bug_report_confirm_exit();
void bug_report_submit(std::string &platform, std::string &version, std::string &title, std::string &description, std::string &steps, std::string &status);
void bug_report_confirm(std::string &platform, std::string &version, std::string &title, std::string &description, std::string &steps, std::string &status);
void bug_report_review(std::string &platform, std::string &version, std::string &title, std::string &description, std::string &steps);
void bug_report_write();
void bug_report();
void main_menu();
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
        std::cout << ui.screen_clear;

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
    void bug_details_update(int id)  {
        std::cout << "What is the new priority level of this report?" << std::endl;
        std::cout << ui.tx_cyan << "1. Pending Review | 2. Low | 3. Medium | 4. High | 5. Critical | 6. Resolved | 7. Working As Intended\n-> " << ui.bg_tx_reset;
        int choice_update;
        std::cin >> choice_update;

        Report *update = &bug.at(id);

        switch (choice_update)
        {
        case 1:
            update->status_set("Pending Review");
            break;
        case 2:
            update->status_set("Low");
            break;
        case 3: 
            update->status_set("Medium");
            break;
        case 4:
            update->status_set("High");
            break;
        case 5:
            update->status_set("Critical");
            break;
        case 6: 
            update->status_set("Resolved");
            break;
        case 7: 
            update->status_set("WAI");
            break;
        default:
            bug_details_update(id);
            break;
        }

        std::cout << "Status successfully updated." << std::endl;

        std::cout << ui.tx_cyan << "\nPress any number to Manage Bugs -> " << ui.bg_tx_reset;
        int temp;
        std::cin >> temp;

        bug_manage();
    }
    void bug_details_delete(int id) {
        std::cout << ui.tx_red << "Deleting a report." << ui.bg_tx_reset << " Are you sure?" << std::endl;
        std::cout << "1. Yes | 2. No (Back to List) -> ";
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                bug.erase(id);
                std::cout << "Report successfully removed.";
                bug_manage();
                break;
            case 2:
                bug_manage();
                break;
            default:
                bug_details_delete(id);
                break;
        }
    }
};
Bug report;

void welcome_screen() {
    std::cout << ui.screen_clear;

    std::cout << "Welcome to " << ui.tx_cyan << "Verbiage" << ui.bg_tx_reset << "!" << std::endl;
}
void roach() {
    std::cout << ui.screen_clear;

        std::cout << "                     ░░";
        std::cout << "                       ░░                                    ░░";
        std::cout << "                         ░░                                  ░░";
        std::cout << "                           ░░                              ░░";
        std::cout << "                             ░░                ░░        ▒▒";
        std::cout << "                                               ░░      ▒▒";
        std::cout << "                                       ░░      ▒▒░░░░░░▒▒        ▓▓▒▒";
        std::cout << "                                         ░░▓▓▓▓░░██▓▓▓▓▓▓▓▓▒▒░░░░▒▒  ▒▒░░";
        std::cout << "                                         ▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒    ░░▓▓░░";
        std::cout << "                     ░░░░░░░░░░░░░░░░░    ████▒▒▓▓▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▒▒░░    ░░▓▓";
        std::cout << "                                         ▒▒▓▓▓▓██▒▒▓▓▒▒▒▒▒▒▒▒▓▓▓▓▒▒▓▓▓▓▒▒      ░░";
        std::cout << "                                           ░░▓▓▓▓▓▓██▓▓▓▓▒▒▒▒▓▓▒▒▒▒▓▓▓▓▒▒▒▒▒▒";
        std::cout << "                                           ░░▒▒▒▒▓▓▓▓██▓▓▓▓▓▓▓▓▒▒▒▒▓▓▓▓▓▓▒▒▒▒▒▒";
        std::cout << "                                           ▒▒  ░░▒▒▒▒▒▒▓▓██▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▒▒▒▒░░";
        std::cout << "                                         ░░      ▒▒░░░░░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒░░";
        std::cout << "                                         ░░      ░░▒▒    ░░▓▓▒▒▒▒▒▒▒▒▓▓▓▓▓▓▒▒▒▒░░";
        std::cout << "                                                   ░░░░  ░░▓▓░░  ░░░░░░▒▒░░░░░░";
        std::cout << "                                                     ░░    ▓▓▓▓▒▒░░";
        std::cout << "                                                         ░░      ░░░░▒▒▓▓";
        std::cout << "                                                                             ░░";
}
void bug_manual() {
        std::cout << ui.screen_clear;

        std::cout << ui.tx_cyan << "Verbiage Manual\n" << ui.bg_tx_reset << std::endl;

        std::cout << ui.tx_cyan << "Verbiage" << ui.bg_tx_reset << ", an issue tracking system for developers.\n" << std::endl;

        std::cout << "This system simply asks the users about the issue they encountered when using a particular application. The developers of the app can then track the issues encountered by their users easily.\n" << std::endl;

        std::cout << "How it works: " << ui.tx_magenta << "Reporter POV" << ui.bg_tx_reset << std::endl;

        std::cout << "Upon welcome screen, select 1 to write a report, or 2 to see the list of bugs. \nUpon selecting 1, the user will be asked a series of questions. Answer accordingly. \nAfterwards, a confirmation message will be prompted whether to publish the report or disregard.\n" << std::endl;

        std::cout << "How it works: " << ui.tx_blue << "Developer POV" << ui.bg_tx_reset << std::endl;

        std::cout << "The Developer POV is similar to the Reporter POV, but with elevated permissions.\nUpon selecting 3, the user will be prompted with a password login before being permitted system access.\n" << std::endl;

        report.bug_display();

        std::cout << "\nSpecific operations may be done by the developer." << std::endl;

        std::cout << ui.tx_cyan << "Update status, Read a report, Delete a report" << ui.bg_tx_reset << std::endl;

        std::cout << "\nAbove operations will be based on the ID of the report." << std::endl;

        std::cout << ui.tx_cyan << "Proceed to Menu? (1. Yes) \n-> " << ui.bg_tx_reset;
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << ui.screen_clear;
            main_menu();
        } else {
            bug_manual();
        }
}
void bug_manage_details(int id) {
    id = bug_details_display();

    std::cout << ui.tx_cyan << "\n1. Update Status | 2. Delete Report | 3. Return to List\n-> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            report.bug_details_update(id);
            break;
        case 2:
            report.bug_details_delete(id);
            break;
        case 3:
            bug_manage();
            break;
        default:
            bug_manage_details(id);
            break;
    }
}
void bug_manage() {
    std::cout << ui.screen_clear;

    std::cout << ui.tx_green << "Welcome!" << ui.bg_tx_reset << " Here are all of the reproted bugs as of the moment." << std::endl;

    report.bug_display();

    std::cout << ui.tx_cyan << "\n1. See Report & Manage Report | 2. Logout \n-> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            bug_manage_details(0);
            break;
        case 2:
            main_menu();
            break;
        default:
            bug_manage();
            break;
    }

}
void bug_manage_login() {
    std::cout << ui.screen_clear;

    std::cout << "To manage bugs, you must login.";
    std::cout << ui.tx_cyan << "\nEnter 0 to return to menu.\n\n" << ui.bg_tx_reset;

    std::cout << "Username: ";
    std::cin.ignore();
    std::string username;
    std::getline(std::cin, username);
    std::cout << "Password: ";
    std::string password;
    std::getline(std::cin, password);

    if (username == "Vault Air" && password == "0000") {
        bug_manage();
    } else if (username == "0") {
        main_menu();
    } else {
        bug_manage_login();
    }
}
void bug_report_details() {
    bug_details_display();

    std::cout << ui.tx_cyan << "\n\n1. Back to Menu | 2. Back to List -> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            main_menu();
            break;
        case 2:
            bug_list();
            break;
        default:
            bug_report_details();
            break;
    }
}
int bug_details_display() {
    int id;
    do {
        std::cout << "\nEnter the ID to see details -> ";
        std::cin >> id;
        if (report.contains_key(id)) {
            report.bug_details(id);
        } else {
            std::cout << ui.tx_magenta << "Please enter a valid ID." << ui.bg_tx_reset;
        }
    } while (!report.contains_key(id));
    return id;
}
void bug_list() {
    std::cout << ui.screen_clear;

    report.bug_display();

    std::cout << ui.tx_cyan << "\n1. Back to Menu | 2. See report \n-> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << ui.screen_clear;
            main_menu();
        case 2:
            bug_report_details();
            break;
        default:
            bug_list();
            break;
    }
}
void bug_report_confirm_exit() {
    std::cout << ui.tx_cyan << "\nPress 1 to access Menu | 2 to Bug Lists\n-> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            main_menu();
            break;
        case 2:
            bug_list();
            break;
        default:
            bug_report_confirm_exit();
            break;
    }
}
void bug_report_submit(std::string &platform, std::string &version, std::string &title, std::string &description, std::string &steps, std::string &status) {
    report.bug_add(platform, version, title, description, steps, status);
    std::cout << ui.tx_green << "\nReport successfully submitted!" << ui.bg_tx_reset;
}
void bug_report_confirm(std::string &platform, std::string &version, std::string &title, std::string &description, std::string &steps, std::string &status) {
    std::cout << "\nAre you sure?" << ui.tx_cyan << "\n1. Yes (Publish) | 2. No (Re-write the report) -> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            bug_report_submit(platform, version, title, description, steps, status);
            break;
        case 2:
            bug_report_write();
            break;
        default:
            bug_report_confirm(platform, version, title, description, steps, status);
            break;
    }
    bug_report_confirm_exit();
}
void bug_report_review(std::string &platform, std::string &version, std::string &title, std::string &description, std::string &steps) {
    std::cout << ui.screen_clear;

    std::cout << "Are these information correct?" << std::endl;

    std::cout << ui.tx_cyan << "Platform: " << ui.bg_tx_reset << platform << std::endl;
    std::cout << ui.tx_cyan << "Version: " << ui.bg_tx_reset << version << std::endl;
    std::cout << ui.tx_cyan << "Title: " << ui.bg_tx_reset << title << std::endl;
    std::cout << ui.tx_cyan << "Description: " << ui.bg_tx_reset << description << std::endl;
    std::cout << ui.tx_cyan << "Steps: " << ui.bg_tx_reset << steps << std::endl;

    std::string status = "Pending Review";

    std::cout << ui.tx_cyan << "\n1. Yes (Submit) | 2. No (Disregard the Report)" << ui.bg_tx_reset << " -> ";
    int choice;
    std::cin >> choice;
    switch (choice) {
        case 1:
            bug_report_confirm(platform, version, title, description, steps, status);
            break;
        case 2:
            bug_report();
            break;
        default:
            bug_report_review(platform, version, title, description, steps);
            break;
    }
}
void bug_report_write() {
    std::cout << ui.screen_clear;

    std::cout << "1. What platform are you on?" << ui.tx_cyan << " (1. Android | 2. Windows | 3. iOS | 4. Mac)" << "\n-> " << ui.bg_tx_reset;
    int choice;
    std::cin >> choice;

    std::string platform;

    switch (choice) {
        case 1:
            platform = "Android";
            break;
        case 2:
            platform = "Windows";
            break;
        case 3:
            platform = "iOS";
            break;
        case 4:
            platform = "Mac";
            break;
        default:
            bug_report_write();
            break;
    }

    std::cout << "2. What is the version of the application you are using?" << ui.tx_cyan << " (App version can be found on the settings of the app) \n-> " << ui.bg_tx_reset;
    std::string version;
    std::cin.ignore();
    std::getline(std::cin, version);

    std::cout << ui.tx_cyan << "3. What is the bug about?\n-> " << ui.bg_tx_reset;
    std::string title;
    std::getline(std::cin, title);

    std::cout << ui.tx_cyan << "4. What is the issue or the problem? \n-> " << ui.bg_tx_reset;
    std::string description;
    std::getline(std::cin, description);

    std::cout << ui.tx_cyan << "5. How can this bug be recreated? \n-> " << ui.bg_tx_reset;
    std::string steps;
    std::getline(std::cin, steps);

    bug_report_review(platform, version, title, description, steps);
}
void bug_report() {
    std::cout << ui.screen_clear;

    std::cout << "You want to report a bug. Is that correct?\n" << ui.tx_green << "1. Yes (Proceed) |" << ui.tx_magenta << " 2. No (Back to Menu)" << ui.bg_tx_reset;

    std::cout << "Select an Iperation:\n-> ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            bug_report_write();
            break;
        case 2:
            std::cout << ui.screen_clear;
            main_menu();
            break;
        default:
            bug_report();
    }
}
void main_menu() {
    std::cout << ui.tx_blue << "\n1. Report a Bug" << ui.tx_green << " | 2. See Existing Bugs" << ui.tx_magenta << " | 3. Manage Bugs (Login as a Developer)" << ui.bg_tx_reset << " | 4. Read Manual" << " | 5. Exit" << std::endl;

    int choice = 0;
    std::cout << "Select an Operation:\n-> ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            bug_report();
            break;
        case 2:
            bug_list();
            break;
        case 3:
            bug_manage_login();
            break;
        case 4: 
            bug_manual();
            break;
        case 5:
            std::exit(0);
            break;
        default:
            break;
    }
}
int main() {
    //draft data
    report.bug_add("Android", "v0.1a", "Duplicate Reports Upon Submission", "When submitting reports, the submission gets duplicated when it should not.", "1. File a report. 2. Submit the report. 3. See the duplicated report.", "Resolved");
    report.bug_add("Mac", "v0.2a", "Cannot Login with Proper Credentials", "I am locked out of my account.", "Try to login, nothing will happen", "High");
    report.bug_add("iOS", "v0.2a", "Crash Upon Startup", "Opening the program exits instantly.", "Open the application", "Critical");
    report.bug_add("Windows", "v0.2a", "Table is one pixel off", "The table is lacking one space in the See Reports tab.", "Start the app and see the reports.", "Low");
    report.bug_add("Android", "v0.3a", "User inputs have no validation", "There are cases when a number is required, a user can input a text and the program will accept it.", "Open a part of the program then try putting a character instead of a number.", "Medium");
    report.bug_add("Windows", "v0.3a", "Working as Intended Test", "TESTING WaI", "none", "WAI");
    report.bug_add("Android", "v0.3a", "Invalid user inputs crashes the program", "The program ends unexpectedly when a wrong input is entered.", "Open a part of the program then put a character when a number is asked.", "Pending Review");

    welcome_screen();
    main_menu();

    return 0;
}