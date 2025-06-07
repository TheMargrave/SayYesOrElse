#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Helper function to replace all instances of a substring
void replaceAll(string &data, const string &from, const string &to) {
    size_t start_pos = 0;
    while ((start_pos = data.find(from, start_pos)) != string::npos) {
        data.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Move past the replacement
    }
}

int main() {
    string name;

    // Get user input for name only
    cout << "Enter the recipient's name: ";
    getline(cin, name);

    // Read index.html instead of template.html
    ifstream templateFile("index.html");
    if (!templateFile.is_open()) {
        cerr << "Error: Could not open index.html" << endl;
        return 1;
    }

    string htmlContent((istreambuf_iterator<char>(templateFile)), istreambuf_iterator<char>());
    templateFile.close();

    // Replace only the {{name}} placeholder
    replaceAll(htmlContent, "{{name}}", name);

    // Write to output.html
    ofstream outputFile("output.html");
    if (!outputFile.is_open()) {
        cerr << "Error: Could not create output.html" << endl;
        return 1;
    }

    outputFile << htmlContent;
    outputFile.close();

    cout << "\n✅ Confession page generated successfully as 'output.html'!\n";
    cout << "Open it in your browser to see the result.\n";

    return 0;
}
