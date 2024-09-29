#include <iostream>
using namespace std;

const int Panjang_nama_max = 50;

// Struct untuk menyimpan informasi koin kripto
struct Koin {
    char Nama[Panjang_nama_max];
    double Harga;
    Koin* next;  // Pointer ke koin berikutnya
};

// Pointer ke head linked list
Koin* head = nullptr;

// Fungsi untuk menyalin nama koin 
void Salin_nama(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < Panjang_nama_max - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
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

// Fungsi untuk menambahkan koin baru
void Tambah_koin(const char* Nama, double Harga) {
    if (Harga < 0) {
        cout << "Harga koin tidak boleh negatif. Silakan masukkan harga yang valid." << endl;
        return;
    }

    // Membuat node baru
    Koin* Koin_baru = new Koin;
    Salin_nama(Koin_baru->Nama, Nama);
    Koin_baru->Harga = Harga;
    Koin_baru->next = nullptr;

    // Menambah ke list
    if (head == nullptr) {
        head = Koin_baru;
    } else {
        Koin* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = Koin_baru;
    }
    cout << "Koin " << Koin_baru->Nama << " berhasil ditambahkan." << endl;
}

// Prosedur untuk menampilkan semua koin
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

// Fungsi untuk mencari koin berdasarkan nama
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

// Prosedur untuk mengupdate harga koin
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

// Prosedur untuk menghapus koin
void Hapus_koin(const char* Nama) {
    if (head == nullptr) {
        cout << "Daftar koin kosong." << endl;
        return;
    }

    // Jika koin yang dihapus adalah head
    if (Bandingkan_nama(head->Nama, Nama)) {
        Koin* temp = head;
        head = head->next;
        delete temp;
        cout << "Koin " << Nama << " berhasil dihapus." << endl;
        return;
    }

    Koin* prev = head;
    Koin* temp = head->next;

    while (temp != nullptr) {
        if (Bandingkan_nama(temp->Nama, Nama)) {
            prev->next = temp->next;
            delete temp;
            cout << "Koin " << Nama << " berhasil dihapus." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    cout << "Koin " << Nama << " tidak ditemukan." << endl;
}

// Fungsi utama
int main() {
    int Pilihan;
    char Nama[Panjang_nama_max];
    double Harga;

    while (true) {
        cout << "\nProgram CRUD Daftar Koin Kripto" << endl;
        cout << "1. Tambah Koin" << endl;
        cout << "2. Tampilkan Daftar Koin" << endl;
        cout << "3. Update Harga Koin" << endl;
        cout << "4. Hapus Koin" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih menu (1-5): ";
        cin >> Pilihan;

        switch (Pilihan) {
            case 1:
                cout << "Masukkan nama koin: ";
                cin.ignore();
                for (int i = 0; i < Panjang_nama_max; i++) {
                    Nama[i] = '\0'; // Inisialisasi Nama kosong
                }
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
                cout << "Terima kasih telah menggunakan program ini." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }

    return 0;
}
