# include "menu.h"

int main() {
    cout << "working dir" << std::filesystem::current_path() << endl;
    runMenu();
    return 0;
}