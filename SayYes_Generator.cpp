#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Replace all instances of 'from' with 'to' in 'data'
void replaceAll(string &data, const string &from, const string &to) {
    size_t start_pos = 0;
    while ((start_pos = data.find(from, start_pos)) != string::npos) {
        data.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

int main() {
    string question, reply;

    // Input collection
    cout << "Enter the question you want to ask:\n> ";
    getline(cin, question);

    cout << "\nEnter the reply that will be shown when 'Yes' is clicked:\n> ";
    getline(cin, reply);

    // ---------- Process index.html ----------
    ifstream htmlTemplate("index.html");
    if (!htmlTemplate.is_open()) {
        cerr << "❌ Error: Could not open index.html" << endl;
        return 1;
    }

    string htmlContent((istreambuf_iterator<char>(htmlTemplate)), istreambuf_iterator<char>());
    htmlTemplate.close();

    replaceAll(htmlContent, "{{question}}", question);

    ofstream htmlOut("output.html");
    if (!htmlOut.is_open()) {
        cerr << "❌ Error: Could not create output.html" << endl;
        return 1;
    }

    htmlOut << htmlContent;
    htmlOut.close();

    // ---------- Process script.js ----------
    ifstream jsTemplate("script.js");
    if (!jsTemplate.is_open()) {
        cerr << "❌ Error: Could not open script.js" << endl;
        return 1;
    }

    string jsContent((istreambuf_iterator<char>(jsTemplate)), istreambuf_iterator<char>());
    jsTemplate.close();

    // Escape backslashes and quotes in reply for JavaScript string safety
    replaceAll(reply, "\\", "\\\\");
    replaceAll(reply, "\"", "\\\"");
    replaceAll(jsContent, "{{reply}}", "\"" + reply + "\"");

    ofstream jsOut("output.js");
    if (!jsOut.is_open()) {
        cerr << "❌ Error: Could not create output.js" << endl;
        return 1;
    }

    jsOut << jsContent;
    jsOut.close();

    // ---------- Done ----------
    cout << "\n✅ Files generated successfully!" << endl;
    cout << "📄 output.html (with custom question)" << endl;
    cout << "📜 output.js (with custom reply for Yes button)" << endl;
    cout << "👉 Open 'output.html' in your browser to see it in action.\n";

    return 0;
}
