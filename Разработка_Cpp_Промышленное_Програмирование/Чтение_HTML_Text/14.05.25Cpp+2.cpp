#include <iostream>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

class HTML {
    string body;
    bool correct = false;

public:
    HTML(const string& body) : body(body) {}

    bool proverca() {
        stack<string> tags;
        size_t pos = 0;
        while (pos < body.length()) {
            size_t start_pos = body.find('<', pos);
            if (start_pos == string::npos) {
                break;
            }
            size_t end_pos = body.find('>', start_pos);
            if (end_pos == string::npos) {
                return false;
            }

            string tag_content = body.substr(start_pos + 1, end_pos - start_pos - 1);
            size_t first_non_space = tag_content.find_first_not_of(" \t\n\r");
            if (first_non_space != string::npos)
                tag_content = tag_content.substr(first_non_space);

            bool is_closing = false;
            if (!tag_content.empty() && tag_content[0] == '/') {
                is_closing = true;
                tag_content = tag_content.substr(1);
            }

            if (tag_content.empty()) {
                return false;
            }

            if (is_closing) {
                if (tags.empty()) {
                    return false;
                }
                string last_open_tag = tags.top();
                if (last_open_tag != tag_content) {
                    return false;
                }
                tags.pop();
            }
            else {
                size_t space_pos = tag_content.find(' ');
                if (space_pos != string::npos) {
                    tag_content = tag_content.substr(0, space_pos);
                }
                tags.push(tag_content);
            }

            pos = end_pos + 1;
        }

        return tags.empty();
    }
};

string read_from_file(const string& path) {
    string content;
    ifstream rd(path);
    if (!rd.is_open()) {
        cout << "Error open file :(" << endl;
        return "";
    }
    char symbol;
    while (rd.get(symbol)) {
        content += symbol;
    }
    return content;
}

int main() {
    string file_path;
    setlocale(LC_ALL, "");
    cout << "Введите путь к HTML-файлу: ";
    getline(cin, file_path);

    string content = read_from_file(file_path);
    if (content.empty()) {
        cout << file_path << " - Пустое или не удалось прочитать содержимое файла." << endl;
    }

    HTML html(content);
    if (html.proverca()) {
        cout << "HTML-файл валиден." << endl;
    }
    else {
        cout << "HTML-файл невалиден." << endl;
        cout << "Содержимое файла:\n" << content << endl;
    }
}
/*Примеры:
Содержимое валидного файла
<html>
<body>To be or not to be</body>
</html>
<html>
<body To be or not to be</body>
</html>*/

// C:\Users\A\source\repos\14.05.25Cpp+2\14.05.25Cpp+2\html.txt