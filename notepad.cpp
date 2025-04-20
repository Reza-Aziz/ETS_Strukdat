// Library yang dibutuhkan untuk program
#include <iostream>     // Untuk input output seperti cout, cin
#include <cstring>     // Untuk manipulasi string seperti strcpy, strcat
#include <string>      // Untuk menggunakan tipe data string
using namespace std;

// Menentukan ukuran maksimal array yang akan digunakan (1000)
#define MAX 1000

// Kelas Stack untuk menyimpan history perubahan teks (untuk fitur undo/redo)
class Stack {
private:
    // Array 2D untuk menyimpan teks-teks sebelumnya
    char data[MAX][MAX];
    // Penanda posisi teratas dari stack
    int top;

public:
    // Constructor: Inisialisasi stack kosong
    Stack() { top = -1; }

    // Fungsi untuk mengecek apakah stack kosong
    bool isEmpty() { return top == -1; }

    // Fungsi untuk mengecek apakah stack penuh
    bool isFull() { return top == MAX - 1; }

    // Fungsi untuk menambah teks ke dalam stack
    void push(const char* str) {
        if (isFull()) return;
        strcpy(data[++top], str);
    }

    // Fungsi untuk mengambil teks teratas dari stack
    void pop(char* str) {
        if (isEmpty()) return;
        strcpy(str, data[top--]);
    }

    // Fungsi untuk mengosongkan stack
    void clear() { top = -1; }
};

// Kelas utama untuk text editor
class TextEditor {
private:
    // Variabel untuk menyimpan teks utama
    char text[MAX];
    // Stack untuk menyimpan history untuk fitur undo
    Stack undoStack;
    // Stack untuk menyimpan history untuk fitur redo
    Stack redoStack;

public:
    // Constructor: Inisialisasi text editor dengan teks kosong
    TextEditor() { text[0] = '\0'; }

    // Fungsi untuk menampilkan teks yang ada di editor
    void showText() {
        cout << "\n--NOTEPAD--\n";
        cout << text << endl;
    }

    // Fungsi untuk menambah teks biasa
    void addText(const char* newText) {
        undoStack.push(text);        // Simpan teks sebelumnya ke undo stack
        strcat(text, newText);       // Tambahkan teks baru
        redoStack.clear();           // Hapus semua history redo
    }

    // Fungsi untuk menambah teks dengan format (bold, italic, underline)
    void addStyledText(const char* newText, const char* style) {
        undoStack.push(text);        // Simpan teks sebelumnya ke undo stack
        if (strlen(text) > 0) strcat(text, " ");  // Tambah spasi jika ada teks sebelumnya
        strcat(text, style);         // Tambah kode format (bold/italic/underline)
        strcat(text, newText);       // Tambah teks baru
        strcat(text, "\033[0m");     // Reset format ke normal
        redoStack.clear();           // Hapus semua history redo
    }

    // Fungsi untuk menghapus teks dari belakang
    void deleteText(int count) {
        int len = strlen(text);
        if (count < 0) count = 0;
        if (count > len) count = len;
        undoStack.push(text);        // Simpan teks sebelumnya ke undo stack
        text[len - count] = '\0';    // Hapus teks sebanyak count karakter
        redoStack.clear();           // Hapus semua history redo
        showText();                  // Tampilkan hasil
    }

    // Fungsi untuk membatalkan perubahan terakhir (undo)
    void undo() {
        if (!undoStack.isEmpty()) {
            redoStack.push(text);    // Simpan teks sekarang ke redo stack
            char temp[MAX];
            undoStack.pop(temp);     // Ambil teks sebelumnya dari undo stack
            strcpy(text, temp);      // Terapkan teks sebelumnya
        } else {
            cout << "Tidak ada aksi untuk di-undo.\n";
        }
    }

    // Fungsi untuk mengulangi perubahan yang dibatalkan (redo)
    void redo() {
        if (!redoStack.isEmpty()) {
            undoStack.push(text);    // Simpan teks sekarang ke undo stack
            char temp[MAX];
            redoStack.pop(temp);     // Ambil teks yang dibatalkan dari redo stack
            strcpy(text, temp);      // Terapkan teks yang dibatalkan
        } else {
            cout << "Tidak ada aksi untuk di-redo.\n";
        }
    }
};

// Fungsi utama program
int main() {
    TextEditor editor;           // Buat objek text editor
    char temp[MAX];             // Variabel sementara untuk menyimpan input
    int choice;                 // Variabel untuk menyimpan pilihan menu

    // Loop utama program
    while (true) {
        // Tampilkan menu
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

        // Baca input pilihan menu
        string input;
        getline(cin, input);

        // Validasi input (harus angka 1-9)
        if (input.length() != 1 || input[0] < '1' || input[0] > '9') {
            cout << "Pilihan tidak valid!\n";
            continue;
        }

        // Ubah input string menjadi angka
        choice = input[0] - '0';

        // Proses pilihan menu
        switch (choice) {
            case 1:     // Tambah teks biasa
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addText(temp);
                break;
            case 2:     // Tambah teks bold
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addStyledText(temp, "\033[1m");
                break;
            case 3:     // Tambah teks underline
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addStyledText(temp, "\033[4m");
                break;
            case 4:     // Tambah teks italic
                cout << "Masukkan teks: ";
                cin.getline(temp, sizeof(temp));
                editor.addStyledText(temp, "\033[3m");
                break;
            case 5: {   // Hapus teks
                int jumlah;
                cout << "Jumlah karakter yang ingin dihapus: ";
                if (!(cin >> jumlah)) {
                    cout << "Input tidak valid!\n";
                    cin.clear();
                    cin.ignore(1000, '\n');
                    break;
                }
                cin.ignore();    // Bersihkan buffer input
                editor.deleteText(jumlah);
                break;
            }
            case 6:     // Undo perubahan terakhir
                editor.undo();
                break;
            case 7:     // Redo perubahan yang dibatalkan
                editor.redo();
                break;
            case 8:     // Tampilkan teks
                editor.showText();
                break;
            case 9:     // Keluar dari program
                cout << "Keluar dari program...\n";
                return 0;
        }
    }
}
