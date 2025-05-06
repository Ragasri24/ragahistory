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
        Node* curr;
    public:
       
    BrowserHistory() : head(nullptr), curr(nullptr) {}

    void visitPage(const string& url) {
        while (curr && curr->next) {
            Node* temp = curr->next;
            curr->next = temp->next;
            if (temp->next) temp->next->prev = curr;
            delete temp;
        }
    
        Node* newNode = new Node(url);
        if (curr) {
            curr->next = newNode;
            newNode->prev = curr;
        } else {
            head = newNode;
        }
        curr = newNode;
    
        cout << "Visited: " << url << endl;
    }
    
    void back() {
        if (curr && curr->prev) {
            curr = curr->prev;
            cout << "Went back to: " << curr->url << endl;
        } else {
            cout << "No previous page.\n";
        }
    }
    void forward() {
        if (curr && curr->next) {
            curr = curr->next;
            cout << "Went forward to: " << curr->url << endl;
        } else {
            cout << "No forward page.\n";
        }
    }

    void printHistory() const {
        Node* temp = head;
        cout << "\nFull Browsing History:\n";
        while (temp) {
            if (temp == curr) {
                cout << "-> " << temp->url << endl;
            } else {
                cout << "   " << temp->url << endl;
            }
            temp = temp->next;
        }
    }
    
    void removeCurrentPage() {
        if (!curr) return;
    
        if (curr->prev)
            curr->prev->next = curr->next;
        else
            head = curr->next;
    
        if (curr->next)
            curr->next->prev = curr->prev;
    
        Node* toDelete = curr;
        curr = curr->next ? curr->next : curr->prev;
    
        delete toDelete;
        cout << "Current page removed.\n";
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

void clearHistory() {
    Node* temp = head;
    while (temp) {
        Node* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }
    head = nullptr;
    curr = nullptr;
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
    browser.visitPage("https://leetcode.com");
    browser.visitPage("https://github.com");
    browser.visitPage("https://google.com");
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


