#include <iostream>
using namespace std;

void hanoi(int n, char asal, char tujuan, char sementara) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari " << asal << " ke " << tujuan << endl;
    } else {
        hanoi(n - 1, asal, sementara, tujuan);
        cout << "Pindahkan piringan " << n << " dari " << asal << " ke " << tujuan << endl;
        hanoi(n - 1, sementara, tujuan, asal);
    }
}

int main() {
    int n = 3;  // Jumlah piringan
    hanoi(n, 'A', 'C', 'B');  // 'A' menara asal, 'C' menara tujuan, 'B' menara sementara
    return 0;
}