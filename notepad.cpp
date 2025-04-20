#include <iostream>
#include <cstring>
using namespace std;

#define MAX 1000

// Stack tanpa STL
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

    void clear() { top = -1; }
};

// Text Editor dengan Undo, Redo, Formatting
class TextEditor {
private:
    char text[MAX];
    Stack undoStack;
    Stack redoStack;

public:
    TextEditor() { text[0] = '\0'; }

    void showText() {
        cout << "\n--NOTEPAD--\n";
        cout << text << endl;
    }

    void addText(const char* newText) {
        undoStack.push(text);
        strcat(text, newText);
        redoStack.clear();
    }

    void addStyledText(const char* newText, const char* style) {
        undoStack.push(text);
        if (strlen(text) > 0) strcat(text, " ");
        strcat(text, style);         // misal: "\033[1m"
        strcat(text, newText);       // teks yang ditambahkan
        strcat(text, "\033[0m");     // reset style
        redoStack.clear();
    }

    void deleteText(int count) {
        int len = strlen(text);
        if (count > len) count = len;
        undoStack.push(text);
        text[len - count] = '\0';
        redoStack.clear();
    }

    void undo() {
        if (!undoStack.isEmpty()) {
            redoStack.push(text);
            char temp[MAX];
            undoStack.pop(temp);
            strcpy(text, temp);
        } else {
            cout << "Tidak ada aksi untuk di-undo.\n";
        }
    }

    void redo() {
        if (!redoStack.isEmpty()) {
            undoStack.push(text);
            char temp[MAX];
            redoStack.pop(temp);
            strcpy(text, temp);
        } else {
            cout << "Tidak ada aksi untuk di-redo.\n";
        }
    }
};

int main() {
    TextEditor editor;
    char temp[MAX];
    int choice;

    while (1) {
        cout << "\n--- MENU ---\n";
        cout << "1. Tambah teks biasa\n";
        cout << "2. Tambah teks BOLD\n";
        cout << "3. Tambah teks UNDERLINE\n";
        cout << "4. Tambah teks ITALIC\n";
        cout << "5. Hapus teks (jumlah karakter)\n";
        cout << "6. Undo\n";
        cout << "7. Redo\n";
        cout << "8. Tampilkan teks\n";
        cout << "9. Keluar\n";
        cout << "Pilihan: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addText(temp);
                break;
            case 2:
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addStyledText(temp, "\033[1m"); // bold
                break;
            case 3:
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addStyledText(temp, "\033[4m"); // underline
                break;
            case 4:
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addStyledText(temp, "\033[3m"); // italic
                break;
            case 5:
                int jumlah;
                cout << "Jumlah karakter yang ingin dihapus: ";
                cin >> jumlah;
                cin.ignore();
                editor.deleteText(jumlah);
                break;
            case 6:
                editor.undo();
                break;
            case 7:
                editor.redo();
                break;
            case 8:
                editor.showText();
                break;
            case 9:
                return 0;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}
