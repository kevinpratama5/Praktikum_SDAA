#include <iostream>
using namespace std;

const int Panjang_nama_max = 50;

// Struct untuk menyimpan informasi koin kripto
struct Koin {
    char Nama[Panjang_nama_max];
    double Harga;
    Koin* next;
};

// Pointer ke head linked list, stack, dan queue
Koin* head = nullptr;
Koin* top = nullptr;
Koin* front = nullptr;
Koin* rear = nullptr;

// Fungsi untuk menyalin nama koin 
void Salin_nama(char* nama, const char* input) {
    int i = 0;
    while (input[i] != '\0' && i < Panjang_nama_max - 1) {
        nama[i] = input[i];
        i++;
    }
    nama[i] = '\0';
}

// Fungsi untuk membandingkan dua nama koin 
bool Bandingkan_nama(const char* nama1, const char* nama2) {
    int i = 0;
    while (nama1[i] != '\0' && nama2[i] != '\0') {
        if (nama1[i] != nama2[i]) {
            return false;
        }
        i++;
    }
    return (nama1[i] == '\0' && nama2[i] == '\0');
}

// Fungsi untuk menambahkan koin baru ke linked list
void Tambah_koin(const char* Nama, double Harga) {
    if (Harga < 0) {
        cout << "Harga koin tidak boleh negatif. Silakan masukkan harga yang valid." << endl;
        return;
    }

    Koin* Koin_baru = new Koin;
    Salin_nama(Koin_baru->Nama, Nama);
    Koin_baru->Harga = Harga;
    Koin_baru->next = nullptr;

    if (head == nullptr) {
        head = Koin_baru;
    } else {
        Koin* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = Koin_baru;
    }
    cout << "Koin " << Koin_baru->Nama << " berhasil ditambahkan ke daftar." << endl;
}

// Prosedur untuk menampilkan semua koin dalam linked list
void Tampilkan_koin() {
    if (head == nullptr) {
        cout << "Daftar koin kosong." << endl;
        return;
    }
    
    Koin* temp = head;
    cout << "Daftar Koin Kripto:" << endl;
    int index = 1;
    while (temp != nullptr) {
        cout << index << ". " << temp->Nama << " - $" << temp->Harga << endl;
        temp = temp->next;
        index++;
    }
}

// Fungsi untuk mencari koin berdasarkan nama dalam linked list
Koin* Cari_koin(const char* Nama) {
    Koin* temp = head;
    while (temp != nullptr) {
        if (Bandingkan_nama(temp->Nama, Nama)) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Prosedur untuk mengupdate harga koin dalam linked list
void Update_harga_koin(const char* Nama, double Harga_baru) {
    if (Harga_baru < 0) {
        cout << "Harga baru tidak boleh negatif. Silakan masukkan harga yang valid." << endl;
        return;
    }

    Koin* koin_ditemukan = Cari_koin(Nama);
    if (koin_ditemukan != nullptr) {
        koin_ditemukan->Harga = Harga_baru;
        cout << "Harga koin " << Nama << " berhasil diupdate menjadi $" << Harga_baru << endl;
    } else {
        cout << "Koin " << Nama << " tidak ditemukan." << endl;
    }
}

// Prosedur untuk menghapus koin dari linked list
void Hapus_koin(const char* Nama) {
    if (head == nullptr) {
        cout << "Daftar koin kosong." << endl;
        return;
    }

    if (Bandingkan_nama(head->Nama, Nama)) {
        Koin* temp = head;
        head = head->next;
        delete temp;
        cout << "Koin " << Nama << " berhasil dihapus dari daftar." << endl;
        return;
    }

    Koin* prev = head;
    Koin* temp = head->next;

    while (temp != nullptr) {
        if (Bandingkan_nama(temp->Nama, Nama)) {
            prev->next = temp->next;
            delete temp;
            cout << "Koin " << Nama << " berhasil dihapus dari daftar." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Koin " << Nama << " tidak ditemukan dalam daftar." << endl;
}

// Fungsi untuk menambahkan koin ke stack
void Push_stack(const char* Nama, double Harga) {
    Koin* Koin_baru = new Koin;
    Salin_nama(Koin_baru->Nama, Nama);
    Koin_baru->Harga = Harga;
    Koin_baru->next = top;
    top = Koin_baru;
    cout << "Koin " << Nama << " berhasil ditambahkan ke stack." << endl;
}

// Fungsi untuk menghapus koin dari stack
void Pop_stack() {
    if (top == nullptr) {
        cout << "Stack kosong." << endl;
        return;
    }
    Koin* temp = top;
    top = top->next;
    cout << "Koin " << temp->Nama << " berhasil dihapus dari stack." << endl;
    delete temp;
}

// Prosedur untuk menampilkan semua koin dalam stack
void Tampilkan_stack() {
    if (top == nullptr) {
        cout << "Stack kosong." << endl;
        return;
    }
    
    Koin* temp = top;
    cout << "Isi Stack (dari atas ke bawah):" << endl;
    int index = 1;
    while (temp != nullptr) {
        cout << index << ". " << temp->Nama << " - $" << temp->Harga << endl;
        temp = temp->next;
        index++;
    }
}

// Fungsi untuk menambahkan koin ke queue
void Enqueue(const char* Nama, double Harga) {
    Koin* Koin_baru = new Koin;
    Salin_nama(Koin_baru->Nama, Nama);
    Koin_baru->Harga = Harga;
    Koin_baru->next = nullptr;

    if (rear == nullptr) {
        front = rear = Koin_baru;
    } else {
        rear->next = Koin_baru;
        rear = Koin_baru;
    }
    cout << "Koin " << Nama << " berhasil ditambahkan ke queue." << endl;
}

// Fungsi untuk menghapus koin dari queue
void Dequeue() {
    if (front == nullptr) {
        cout << "Queue kosong." << endl;
        return;
    }
    Koin* temp = front;
    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    cout << "Koin " << temp->Nama << " berhasil dihapus dari queue." << endl;
    delete temp;
}

// Prosedur untuk menampilkan semua koin dalam queue
void Tampilkan_queue() {
    if (front == nullptr) {
        cout << "Queue kosong." << endl;
        return;
    }
    
    Koin* temp = front;
    cout << "Isi Queue (dari depan ke belakang):" << endl;
    int index = 1;
    while (temp != nullptr) {
        cout << index << ". " << temp->Nama << " - $" << temp->Harga << endl;
        temp = temp->next;
        index++;
    }
}

// Fungsi utama
int main() {
    int Pilihan;
    char Nama[Panjang_nama_max];
    double Harga;

    while (true) {
        cout << "\nProgram Manajemen Koin Kripto" << endl;
        cout << "1. Tambah Koin ke Daftar" << endl;
        cout << "2. Tampilkan Daftar Koin" << endl;
        cout << "3. Update Harga Koin" << endl;
        cout << "4. Hapus Koin dari Daftar" << endl;
        cout << "5. Push Koin ke Stack" << endl;
        cout << "6. Pop Koin dari Stack" << endl;
        cout << "7. Tampilkan Stack" << endl;
        cout << "8. Enqueue Koin" << endl;
        cout << "9. Dequeue Koin" << endl;
        cout << "10. Tampilkan Queue" << endl;
        cout << "11. Keluar" << endl;
        cout << "Pilih menu (1-11): ";
        cin >> Pilihan;

        switch (Pilihan) {
            case 1:
                cout << "Masukkan nama koin: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                cout << "Masukkan harga koin: ";
                cin >> Harga;
                Tambah_koin(Nama, Harga);
                break;
            case 2:
                Tampilkan_koin();
                break;
            case 3:
                cout << "Masukkan nama koin yang akan diupdate: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                cout << "Masukkan harga baru: ";
                cin >> Harga;
                Update_harga_koin(Nama, Harga);
                break;
            case 4:
                cout << "Masukkan nama koin yang akan dihapus: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                Hapus_koin(Nama);
                break;
            case 5:
                cout << "Masukkan nama koin untuk push ke stack: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                cout << "Masukkan harga koin: ";
                cin >> Harga;
                Push_stack(Nama, Harga);
                break;
            case 6:
                Pop_stack();
                break;
            case 7:
                Tampilkan_stack();
                break;
            case 8:
                cout << "Masukkan nama koin untuk enqueue: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                cout << "Masukkan harga koin: ";
                cin >> Harga;
                Enqueue(Nama, Harga);
                break;
            case 9:
                Dequeue();
                break;
            case 10:
                Tampilkan_queue();
                break;
            case 11:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}