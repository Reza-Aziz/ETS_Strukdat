#include <iostream>
#include <cstring>
using namespace std;

void tambahText(char* buffer, const char* text){
    strcat(buffer, text);
}

void tambahStyle(char* buffer, const char* text, const char* style){
    if (strlen(buffer) > 0) strcat(buffer, " "); 
    strcat(buffer, style);
    strcat(buffer, text);
    strcat(buffer, "\033[0m");
}

int main(){
    char text[1000] = "";
    char temp[1000];
    int choice;

    while (1)
    {
        cout << "---pilih---\n";
        cout << "1. tambah teks\n";
        cout << "2. tambah teks bold\n";
        cout << "3. tambah teks underlined\n";
        cout << "4. tambah teks italic\n";
        cout << "5. tampilkan teks\n";
        cout << "pilihan : ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "masukkan teks : ";
            cin.getline(temp, sizeof(temp));
            tambahText(text, temp);
            break;
            case 2:
            cout << "masukkan teks : ";
            cin.getline(temp, sizeof(temp));
            tambahStyle(text, temp, "\033[1m");
            break;
            case 3:
            cout << "masukkan teks : ";
            cin.getline(temp, sizeof(temp));
            tambahStyle(text, temp, "\033[4m");
            break;
            case 4:
            cout << "masukkan teks : ";
            cin.getline(temp, sizeof(temp));
            tambahStyle(text, temp, "\033[3m");
            break;
            case 5:
            cout << "\n--NOTEPAD--\n";
            cout << text << endl;
            break;
            default:
            cout << "pilihan tidak ada\n";
        }
    }
    return 0;
}
