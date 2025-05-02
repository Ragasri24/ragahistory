#include <iostream>
#include <string>
using namespace std;
class Node {
    friend class BrowserHistory;
    private :
    string url;
    Node* prev;
    Node* next;
    public :
    Node(const string& u) : url(u), prev(nullptr), next(nullptr) {}
};
class BrowserHistory {
    private:
        Node* head;
        Node* current;
    public:
       
    BrowserHistory() : head(nullptr), current(nullptr) {}

    void visitPage(const string& url) {
        Node* newNode = new Node(url);
        if (current && current->next) {
            Node* temp = current->next;
            while (temp) {
                Node* toDelete = temp;
                temp = temp->next;
                delete toDelete;
            }
            current->next = nullptr;
        }
        if (current) {
            current->next = newNode;
            newNode->prev = current;
        } else {
            head = newNode;
        }
        current = newNode;

        cout << "Visited: " << url << endl;
    }
    void back() {
        if (current && current->prev) {
            current = current->prev;
            cout << "Went back to: " << current->url << endl;
        } else {
            cout << "No previous page.\n";
        }
    }
    void forward() {
        if (current && current->next) {
            current = current->next;
            cout << "Went forward to: " << current->url << endl;
        } else {
            cout << "No forward page.\n";
        }
    }

    void printHistory() const {
        Node* temp = head;
        cout << "\nFull Browsing History:\n";
        while (temp) {
            if (temp == current) {
                cout << "-> " << temp->url << endl;
            } else {
                cout << "   " << temp->url << endl;
            }
            temp = temp->next;
        }
    }
    
    int historySize() {
    int count = 0;
    Node* temp = head;
    while (temp) {
        ++count;
        temp = temp->next;
    }
    return count;
}
void removeCurrentPage() {
    if (!current) return;

    if (current->prev)
        current->prev->next = current->next;
    else
        head = current->next;  // Removing head

    if (current->next)
        current->next->prev = current->prev;

    Node* toDelete = current;
    current = current->next ? current->next : current->prev;
    delete toDelete;

    cout << "Current page removed.\n";
}

void clearHistory() {
    Node* temp = head;
    while (temp) {
        Node* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
    head = nullptr;
    current = nullptr;
    cout << "Browsing history cleared.\n";
}

    ~BrowserHistory() {
        Node* temp = head;
        while (temp) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }
};
int main() {
    BrowserHistory browser;
    browser.visitPage("https://google.com");
    browser.visitPage("https://openai.com");
    browser.visitPage("https://github.com");
    browser.back(); browser.back(); browser.forward();
    browser.visitPage("https://cplusplus.com");
    browser.printHistory();
    cout << "History size: " << browser.historySize() << endl;
    browser.removeCurrentPage();
    browser.printHistory();
    browser.clearHistory();
    browser.printHistory();
    return 0;
}


