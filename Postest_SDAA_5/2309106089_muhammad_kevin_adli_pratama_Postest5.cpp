#include <iostream>
using namespace std;

const int Panjang_nama_max = 50;

// Struct untuk menyimpan informasi koin kripto
struct Koin {
    char Nama[Panjang_nama_max];
    double Harga;
    Koin* next;
};

// Pointer ke head
Koin* head = nullptr;
Koin* top = nullptr;
Koin* front = nullptr;
Koin* rear = nullptr;

// Fungsi menyalin nama koin 
void Salin_nama(char* nama, const char* input) {
    int i = 0;
    while (input[i] != '\0' && i < Panjang_nama_max - 1) {
        nama[i] = input[i];
        i++;
    }
    nama[i] = '\0';
}

// Fungsi  menambahkan koin baru ke dalam linked list
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
    cout << "Koin " << Nama << " berhasil ditambahkan ke daftar." << endl;
}

// Fungsi menampilkan daftar koin
void Tampilkan_koin() {
    if (head == nullptr) {
        cout << "Daftar koin kosong." << endl;
        return;
    }
    Koin* temp = head;
    cout << "Daftar Koin Kripto:" << endl;
    while (temp != nullptr) {
        cout << temp->Nama << " - $" << temp->Harga << endl;
        temp = temp->next;
    }
}

// Fungsi menghitung jumlah koin dalam linked list
int Hitung_koin() {
    int count = 0;
    Koin* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Fungsi untuk membagi linked list (untuk Merge Sort)
void Split_list(Koin* source, Koin** front, Koin** back) {
    Koin* fast = source->next;
    Koin* slow = source;

    while (fast != nullptr) {
        fast = fast->next;
        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *front = source;
    *back = slow->next;
    slow->next = nullptr;
}

// Fungsi Merge untuk mengurutkan secara ascending
Koin* Merge_ascending(Koin* a, Koin* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    Koin* result = nullptr;
    if (a->Harga <= b->Harga) {
        result = a;
        result->next = Merge_ascending(a->next, b);
    } else {
        result = b;
        result->next = Merge_ascending(a, b->next);
    }
    return result;
}

// Fungsi Merge Sort untuk mengurutkan koin secara ascending
void Merge_sort(Koin** head_ref) {
    Koin* head = *head_ref;
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Koin* a;
    Koin* b;
    Split_list(head, &a, &b);

    Merge_sort(&a);
    Merge_sort(&b);

    *head_ref = Merge_ascending(a, b);
}

// Fungsi untuk menyalin linked list ke array (untuk Shell Sort)
void Salin_ke_array(Koin* arr[]) {
    Koin* temp = head;
    int i = 0;
    while (temp != nullptr) {
        arr[i++] = temp;
        temp = temp->next;
    }
}

// Fungsi Shell Sort untuk mengurutkan secara descending
void Shell_sort(Koin* arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Koin* temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap]->Harga < temp->Harga; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
    cout << "Koin berhasil diurutkan secara descending menggunakan Shell Sort." << endl;
}

// Fungsi untuk menampilkan koin yang terurut
void Tampilkan_koin_terurut(Koin* arr[], int n) {
    cout << "Daftar Koin Terurut:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i]->Nama << " - $" << arr[i]->Harga << endl;
    }
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
        cout << "11. Urutkan (Merge Sort Ascending)" << endl;
        cout << "12. Urutkan (Shell Sort Descending)" << endl;
        cout << "13. Keluar" << endl;
        cout << "Pilih menu (1-13): ";
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
            case 11:
                Merge_sort(&head);
                Tampilkan_koin();
                break;
            case 12: {
                int n = Hitung_koin();
                Koin* arr[n];
                Salin_ke_array(arr);
                Shell_sort(arr, n);
                Tampilkan_koin_terurut(arr, n);
                break;
            }
            case 13:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                return 0;
        }
    }
    return 0;
}
