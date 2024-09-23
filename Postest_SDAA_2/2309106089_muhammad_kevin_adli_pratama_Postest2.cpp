#include <iostream>
using namespace std;

const int Jumlah_max_koin = 100;
const int Panjang_nama_max = 50;

// Struct untuk menyimpan informasi koin kripto
struct Koin {
    char Nama[Panjang_nama_max];
    double Harga;
};

// Array untuk menyimpan daftar koin
Koin List_koin[Jumlah_max_koin];
int Jumlah_koin = 0;

// Fungsi untuk menambahkan koin baru
void Tambah_koin(const char* Nama, double Harga) {
    if (Harga < 0) {
        cout << "Harga koin tidak boleh negatif. Silakan masukkan harga yang valid." << endl;
        return;
    }

    if (Jumlah_koin < Jumlah_max_koin) {
        Koin& Koin_baru = List_koin[Jumlah_koin];
        int i;
        for (i = 0; i < Panjang_nama_max - 1 && Nama[i] != '\0'; ++i) {
            Koin_baru.Nama[i] = Nama[i];
        }
        Koin_baru.Nama[i] = '\0';
        Koin_baru.Harga = Harga;
        Jumlah_koin++;
        cout << "Koin " << Koin_baru.Nama << " berhasil ditambahkan." << endl;
    } else {
        cout << "Daftar koin penuh. Tidak bisa menambahkan koin baru." << endl;
    }
}

// Prosedur untuk menampilkan semua koin
void Tampilkan_koin() {
    if (Jumlah_koin == 0) {
        cout << "Daftar koin kosong." << endl;
        return;
    }
    
    cout << "Daftar Koin Kripto:" << endl;
    for (int i = 0; i < Jumlah_koin; i++) {
        cout << i+1 << ". " << List_koin[i].Nama << " - $" << List_koin[i].Harga << endl;
    }
}

// Fungsi untuk mencari indeks koin berdasarkan nama
int Cari_index_koin(const char* Nama) {
    for (int i = 0; i < Jumlah_koin; i++) {
        bool cocok = true;
        for (int j = 0; j < Panjang_nama_max && List_koin[i].Nama[j] != '\0' && Nama[j] != '\0'; j++) {
            if (List_koin[i].Nama[j] != Nama[j]) {
                cocok = false;
                break;
            }
        }
        if (cocok) {
            return i;
        }
    }
    return -1;
}

// Prosedur untuk mengupdate harga koin
void Update_harga_koin(const char* Nama, double Harga_baru) {
    if (Harga_baru < 0) {
        cout << "Harga baru tidak boleh negatif. Silakan masukkan harga yang valid." << endl;
        return;
    }

    int index = Cari_index_koin(Nama);
    if (index != -1) {
        List_koin[index].Harga = Harga_baru;
        cout << "Harga koin " << Nama << " berhasil diupdate menjadi $" << Harga_baru << endl;
    } else {
        cout << "Koin " << Nama << " tidak ditemukan." << endl;
    }
}

// Prosedur untuk menghapus koin
void Hapus_koin(const char* Nama) {
    int index = Cari_index_koin(Nama);
    if (index != -1) {
        for (int i = index; i < Jumlah_koin - 1; i++) {
            List_koin[i] = List_koin[i + 1];
        }
        Jumlah_koin--;
        cout << "Koin " << Nama << " berhasil dihapus." << endl;
    } else {
        cout << "Koin " << Nama << " tidak ditemukan." << endl;
    }
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