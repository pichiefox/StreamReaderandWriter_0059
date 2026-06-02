#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>

using namespace std;

class TokoElektronik {
private:
    array<string, 3> etalase;

public:
    // Constructor
    TokoElektronik() {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Tablet";
    }

    string ambilProduk(size_t nomorRak) {
        try {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&) {
            throw string(
                "Gagal Mengambil Barang : Rak nomor "
                + to_string(nomorRak)
                + " kosong atau tidak tersedia!"
            );
        }
    }
};

const string NAMA_FILE = "gudang.txt";

void tampilkanBarang() {
    ifstream file(NAMA_FILE);

    cout << "\n===== DAFTAR BARANG GUDANG =====\n";

    string barang;
    int no = 1;

    while (getline(file, barang)) {
        cout << no++ << ". " << barang << endl;
    }

    if (no == 1) {
        cout << "Gudang masih kosong.\n";
    }

    file.close();
}

void tambahBarang() {
    ofstream file(NAMA_FILE, ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang : ";
    getline(cin, barang);

    file << barang << endl;

    file.close();

    cout << "Barang berhasil ditambahkan.\n";
}

void updateBarang() {
    ifstream file(NAMA_FILE);

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "\nPilih nomor barang yang akan diubah : ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    cin.ignore();

    cout << "Masukkan nama barang baru : ";
    getline(cin, data[nomor - 1]);

    ofstream tulis(NAMA_FILE);

    for (string item : data) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Data berhasil diperbarui.\n";
}

void hapusBarang() {
    ifstream file(NAMA_FILE);

    vector<string> data;
    string barang;

    while (getline(file, barang)) {
        data.push_back(barang);
    }

    file.close();

    if (data.empty()) {
        cout << "Gudang kosong.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "\nPilih nomor barang yang akan dihapus : ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size()) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    data.erase(data.begin() + (nomor - 1));

    ofstream tulis(NAMA_FILE);

    for (string item : data) {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Data berhasil dihapus.\n";
}

void simulasiEtalase() {
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    // Skenario 1
    try {
        cout << "\nSkenario 1\n";
        cout << "Mengambil rak indeks 1...\n";

        string barang = toko.ambilProduk(1);

        cout << "Berhasil mengambil : "
             << barang << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }

    // Skenario 2
    try {
        cout << "\nSkenario 2\n";
        cout << "Mengambil rak indeks 5...\n";

        string barang = toko.ambilProduk(5);

        cout << "Berhasil mengambil : "
             << barang << endl;
    }
    catch (string pesan) {
        cout << pesan << endl;
    }
}

int main() {

    int pilihan;

    do {

        cout << "\n=============================================\n";
        cout << " SISTEM MANAJEMEN TOKO ELEKTRONIK GIBRAN JAYA\n";
        cout << "===============================================\n";

        tampilkanBarang();

        cout << "\nMenu:\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Update Barang\n";
        cout << "3. Hapus Barang\n";
        cout << "4. Simulasi Etalase\n";
        cout << "0. Keluar\n";

        cout << "\nPilih menu : ";
        cin >> pilihan;

        switch (pilihan) {

        case 1:
            tambahBarang();
            break;

        case 2:
            updateBarang();
            break;

        case 3:
            hapusBarang();
            break;

        case 4:
            simulasiEtalase();
            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak tersedia.\n";
        }

    } while (pilihan != 0);

    return 0;
}