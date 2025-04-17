#include <iostream>
#include <cstring>
using namespace std;

#define MAX 1000

// Stack implementation (tanpa STL)
class Stack {
private:
    char data[MAX][MAX];
    int top;

public:
    Stack() { top = -1; }

    bool isEmpty() { return top == -1; }

    bool isFull() { return top == MAX - 1; }

    void push(const char* str) {
        if (isFull()) return;
        strcpy(data[++top], str);
    }

    void pop(char* str) {
        if (isEmpty()) return;
        strcpy(str, data[top--]);
    }
};

// Queue (tidak digunakan di core undo/redo, tapi bisa untuk fitur tambahan seperti antrian perubahan)
class Queue {
private:
    char data[MAX][MAX];
    int front, rear;

public:
    Queue() { front = rear = -1; }

    bool isEmpty() { return front == -1; }

    bool isFull() { return (rear + 1) % MAX == front; }

    void enqueue(const char* str) {
        if (isFull()) return;
        if (isEmpty()) front = 0;
        rear = (rear + 1) % MAX;
        strcpy(data[rear], str);
    }

    void dequeue(char* str) {
        if (isEmpty()) return;
        strcpy(str, data[front]);
        if (front == rear)
            front = rear = -1;
        else
            front = (front + 1) % MAX;
    }
};

class TextEditor {
private:
    char text[MAX];
    Stack undoStack;
    Stack redoStack;

public:
    TextEditor() { text[0] = '\0'; }

    void showText() {
        cout << "Current Text: " << text << endl;
    }

    void typeText(const char* newText) {
        undoStack.push(text);
        strcat(text, newText);
        redoStack = Stack(); // Clear redo stack
    }

    void deleteText(int count) {
        int len = strlen(text);
        if (count > len) count = len;
        undoStack.push(text);
        text[len - count] = '\0';
        redoStack = Stack();
    }

    void undo() {
        if (!undoStack.isEmpty()) {
            redoStack.push(text);
            char temp[MAX];
            undoStack.pop(temp);
            strcpy(text, temp);
        }
    }

    void redo() {
        if (!redoStack.isEmpty()) {
            undoStack.push(text);
            char temp[MAX];
            redoStack.pop(temp);
            strcpy(text, temp);
        }
    }
};

int main() {
    TextEditor editor;

    editor.typeText("Hello");
    editor.showText();

    editor.typeText(" World");
    editor.showText();

    editor.undo();
    editor.showText();

    editor.redo();
    editor.showText();

    editor.deleteText(6);
    editor.showText();

    editor.undo();
    editor.showText();

    return 0;
}
