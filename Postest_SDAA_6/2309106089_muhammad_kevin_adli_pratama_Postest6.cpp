#include <iostream>
using namespace std;

const int Panjang_nama_max = 50;

struct Koin {
    char Nama[Panjang_nama_max];
    double Harga;
    Koin* next;
};

Koin* head = nullptr;
Koin* top = nullptr;
Koin* front = nullptr;
Koin* rear = nullptr;

// Fungsi  menghitung panjang string
int panjang_string(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Fungsi menyalin string
void Salin_nama(char* nama, const char* input) {
    int i = 0;
    while (input[i] != '\0' && i < Panjang_nama_max - 1) {
        nama[i] = input[i];
        i++;
    }
    nama[i] = '\0';
}

// Fungsi  membandingkan dua string (strcmp)
int bandingkan_string(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return (str1[i] - str2[i]);
        }
        i++;
    }
    // panjang string berbeda
    if (str1[i] != '\0' || str2[i] != '\0') {
        return (str1[i] - str2[i]);
    }
    return 0; // String sama
}

// Fungsi mencari nilai minimal
int min(int a, int b) {
    return (a < b) ? a : b;
}

// Fungsi  mencari akar kuadrat
double akar_kuadrat(double num) {
    double low = 0, high = num, mid;
    double epsilon = 0.00001; // ketelitian
    while (high - low > epsilon) {
        mid = (low + high) / 2;
        if (mid * mid > num) {
            high = mid;
        } else {
            low = mid;
        }
    }
    return (low + high) / 2;
}

// Fungsi menambahkan koin
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

// Fungsi menampilkan koin
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

// Fungsi update harga koin
void Update_harga_koin(const char* Nama, double Harga_baru) {
    if (head == nullptr) {
        cout << "Daftar koin kosong." << endl;
        return;
    }
    Koin* temp = head;
    while (temp != nullptr) {
        if (bandingkan_string(temp->Nama, Nama) == 0) {
            temp->Harga = Harga_baru;
            cout << "Harga koin " << Nama << " berhasil diperbarui." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Koin tidak ditemukan." << endl;
}

// Fungsi menghapus koin
void Hapus_koin(const char* Nama) {
    if (head == nullptr) {
        cout << "Daftar koin kosong." << endl;
        return;
    }
    Koin* temp = head;
    Koin* prev = nullptr;
    
    while (temp != nullptr) {
        if (bandingkan_string(temp->Nama, Nama) == 0) {
            if (prev == nullptr) {
                head = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Koin " << Nama << " berhasil dihapus." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Koin tidak ditemukan." << endl;
}

// Fungsi  menghitung jumlah koin di linked list
int Hitung_koin() {
    int count = 0;
    Koin* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Fungsi untuk membagi linked list  dengan menggunakan sorting Merge Sort
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

// Fungsi Merge Sort mengurutkan koin secara ascending
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

// Fungsi  menyalin linked list ke array dengan menggunakan Shell Sort
void Salin_ke_array(Koin* arr[]) {
    Koin* temp = head;
    int i = 0;
    while (temp != nullptr) {
        arr[i++] = temp;
        temp = temp->next;
    }
}

// Fungsi Shell Sort  mengurutkan secara descending
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

// Fungsi  menampilkan koin yang terurut
void Tampilkan_koin_terurut(Koin* arr[], int n) {
    cout << "Daftar Koin Terurut:" << endl;
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i]->Nama << " - $" << arr[i]->Harga << endl;
    }
}

// Fungsi Fibonacci Search manual
int Fibonacci_Search(int arr[], int n, int x) {
    int fibMMm2 = 0;  // (m-2)'th Fibonacci
    int fibMMm1 = 1;  // (m-1)'th Fibonacci
    int fibM = fibMMm2 + fibMMm1;

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;

    while (fibM > 1) {
        int i = min(offset + fibMMm2, n - 1);

        if (arr[i] < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        }
        else if (arr[i] > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        }
        else return i;
    }

    if (fibMMm1 && arr[offset + 1] == x) return offset + 1;

    return -1;
}

// Fungsi Jump Search manual
int Jump_Search(int arr[], int n, int x) {
    int step = (int)akar_kuadrat(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < x) {
        prev = step;
        step += (int)akar_kuadrat(n);
        if (prev >= n) return -1;
    }

    while (arr[prev] < x) {
        prev++;
        if (prev == min(step, n)) return -1;
    }

    if (arr[prev] == x) return prev;

    return -1;
}

// Fungsi untuk Boyer-Moore manual
void Boyer_Moore_Search(const char* text, const char* pattern) {
    int n = panjang_string(text);
    int m = panjang_string(pattern);

    int badChar[256];

    for (int i = 0; i < 256; i++) badChar[i] = -1;
    for (int i = 0; i < m; i++) badChar[(int)pattern[i]] = i;

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[s + j]) j--;

        if (j < 0) {
            cout << "Pattern ditemukan pada indeks " << s << endl;
            s += (s + m < n) ? m - badChar[(int)text[s + m]] : 1;
        } else {
            s += max(1, j - badChar[(int)text[s + j]]);
        }
    }
}

// Fungsi Push ke stack
void Push_stack(const char* Nama, double Harga) {
    Koin* Koin_baru = new Koin;
    Salin_nama(Koin_baru->Nama, Nama);
    Koin_baru->Harga = Harga;
    Koin_baru->next = top;
    top = Koin_baru;
    cout << "Koin " << Nama << " berhasil ditambahkan ke stack." << endl;
}

// Fungsi Pop dari stack
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

// Fungsi untuk menampilkan stack
void Tampilkan_stack() {
    if (top == nullptr) {
        cout << "Stack kosong." << endl;
        return;
    }
    Koin* temp = top;
    cout << "Daftar Koin di Stack:" << endl;
    while (temp != nullptr) {
        cout << temp->Nama << " - $" << temp->Harga << endl;
        temp = temp->next;
    }
}

// Fungsi Enqueue ke queue
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

// Fungsi Dequeue dari queue
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

// Fungsi menampilkan queue
void Tampilkan_queue() {
    if (front == nullptr) {
        cout << "Queue kosong." << endl;
        return;
    }
    Koin* temp = front;
    cout << "Daftar Koin di Queue:" << endl;
    while (temp != nullptr) {
        cout << temp->Nama << " - $" << temp->Harga << endl;
        temp = temp->next;
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
        cout << "11. Urutkan (Merge Sort Ascending)" << endl;
        cout << "12. Urutkan (Shell Sort Descending)" << endl;
        cout << "13. Fibonacci Search untuk harga koin" << endl;
        cout << "14. Jump Search untuk harga koin" << endl;
        cout << "15. Boyer-Moore Search untuk nama koin" << endl;
        cout << "16. Keluar" << endl;
        cout << "Pilih menu (1-16): ";
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
                cout << "Masukkan nama koin yang ingin diperbarui: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                cout << "Masukkan harga baru: ";
                cin >> Harga;
                Update_harga_koin(Nama, Harga);
                break;
            case 4:
                cout << "Masukkan nama koin yang ingin dihapus: ";
                cin.ignore();
                cin.getline(Nama, Panjang_nama_max);
                Hapus_koin(Nama);
                break;
            case 5:
                cout << "Masukkan nama koin: ";
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
                cout << "Masukkan nama koin: ";
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
            case 13: {
                int n = Hitung_koin();
                int arr[n];
                Koin* temp = head;
                for (int i = 0; i < n; i++) {
                    arr[i] = (int)temp->Harga;
                    temp = temp->next;
                }
                int x;
                cout << "Masukkan harga yang ingin dicari: ";
                cin >> x;
                int result = Fibonacci_Search(arr, n, x);
                if (result != -1) cout << "Harga ditemukan pada indeks " << result << endl;
                else cout << "Harga tidak ditemukan." << endl;
                break;
            }
            case 14: {
                int n = Hitung_koin();
                int arr[n];
                Koin* temp = head;
                for (int i = 0; i < n; i++) {
                    arr[i] = (int)temp->Harga;
                    temp = temp->next;
                }
                int x;
                cout << "Masukkan harga yang ingin dicari: ";
                cin >> x;
                int result = Jump_Search(arr, n, x);
                if (result != -1) cout << "Harga ditemukan pada indeks " << result << endl;
                else cout << "Harga tidak ditemukan." << endl;
                break;
            }
            case 15: {
                char text[100], pattern[50];
                cout << "Masukkan nama koin: ";
                cin.ignore();
                cin.getline(text, 100);
                cout << "Masukkan nama pattern: ";
                cin.getline(pattern, 50);
                Boyer_Moore_Search(text, pattern);
                break;
            }
            case 16:
                cout << "Terima kasih telah menggunakan program ini." << endl;
                return 0;
        }
    }
    return 0;
}
