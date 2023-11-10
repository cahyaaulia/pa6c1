#include <iostream>
#include <string>
#include <cmath>
#include <limits>  
#include <iomanip>
#include <queue>
using namespace std;

struct Pengguna {
    string username;
    string password;
    bool isAdmin;
};


struct Tiket {
    string keberangkatan;
    string tujuan;
    string jam;
    int kursi;
    double harga;
    string nomorBus; 
    Tiket* next;
};

const int MAX_USERS = 100;
Pengguna users[MAX_USERS];
int numUsers = 0;
Tiket tikets[100];   // Array untuk menyimpan tiket
int numTikets = 0;   // Jumlah tiket yang disimpan

// Gunakan queue untuk menyimpan data pengguna
queue<Pengguna> userQueue;


// Fungsi untuk menampilkan data pengguna dari antrian
void TampilkanDataUser()
{
    if (userQueue.empty()) //untuk mengecek jika antria kosong atau tidak
    {
        cout << "Tidak ada user yang terdaftar.\n";
        return; //jika tidak ada maka system akan mengembalikan(return) dari fungsi
    }

    const int usernameWidth = 20; //ini untuk mengatur lebar kolom pada username di tampilan  
    queue<Pengguna> tempQueue; //membuat sebuah antrian sementara dan menyimpan salinan data pengguna dari antrian

    cout << "\nDaftar User Terdaftar:\n";
    cout << "+" << string(usernameWidth, '-') << "+\n";
    cout << "| " << left << setw(usernameWidth - 2) << "Username"
         << " |\n";
    cout << "+" << string(usernameWidth, '-') << "+\n";
        //mencetak baris pemisah dengan lebar yang sesuai dengan usernameWidth
    while (!userQueue.empty())
    {
        Pengguna currentUser = userQueue.front(); //program mengambil data pengguna pertama dari antrian users menggunakan front(), program mengambil data pengguna pertama dari antrian users menggunakan front()
        cout << "| " << left << setw(usernameWidth - 2) << currentUser.username << " |\n"; //untuk menampilkan 
        userQueue.pop(); // Setelah user ditampilkan user tersebut dihapus dari antrian users dengan menggunakan pop(), dan dipindahkan ke antrian sementara tempQueue
        tempQueue.push(currentUser); //data akan disimpan kembali ke antrian tempQueue, ini agar urutan data pengguna di antrian sementara sesuai dengan urutan asli di antrian users
    }

    cout << "+" << string(usernameWidth, '-') << "+\n"; // untuk menampilkan 

    // Mengembalikan user ke queue asli
    while (!tempQueue.empty()) //ini akan mengeloop dan berjalan selama antrian sementara tempQueue masih berisi elemen
    {
        userQueue.push(tempQueue.front());// selama loop, elemen pertama dari antrian sementara (tempQueue) diambil menggunakan front(), dan di kembalikan ke antrian users menggunakan push()
        tempQueue.pop(); //ini di gunakan untuk menghapus antrian sementara, setelah data di pindah ke antrian Users
    }
}


void DequeueUser()
{
    if (userQueue.empty()) // Memeriksa apakah antrian users kosong.
    {
        cout << "Antrian user kosong, tidak ada user untuk di-dequeue.\n";
        return;
    }

    Pengguna removedUser = userQueue.front();
    userQueue.pop(); // Menghapus elemen pertama (front) dari antrian users dan menyimpannya dalam "removedUser".
    cout << "User " << removedUser.username << " telah di-dequeue dari antrian.\n";
}


// Fungsi untuk melakukan login
Pengguna lakukanLogin() {
    Pengguna user;
    cout << "Masukkan username: ";
    cin >> user.username;
    cout << "Masukkan password: ";
    cin >> user.password;

    // Contoh pengecekan login admin (username dan password admin)
    if (user.username == "admin" && user.password == "admin") {
        user.isAdmin = true;
    } else {
        user.isAdmin = false;
    }

    // Tambahkan pengguna ke dalam antrian
    userQueue.push(user);

    return user;
}

// Fungsi untuk melakukan pendaftaran
Pengguna lakukanPendaftaran() {
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    if (numUsers >= MAX_USERS) {
        cout << "Batas pengguna telah tercapai. Pendaftaran gagal." << endl;
        return { "", "", false }; // Pengguna tidak valid
    }

    // Periksa apakah pengguna dengan username yang sama sudah ada
    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            cout << "Pengguna dengan username tersebut sudah terdaftar. Pendaftaran gagal." << endl;
            return { "", "", false }; // Pengguna tidak valid
        }
    }

    // Tambahkan pengguna ke dalam antrian
    Pengguna newUser = {username, password, false};
    userQueue.push(newUser);

    // Tambahkan pengguna ke dalam array pengguna
    users[numUsers] = newUser;
    numUsers++;

    cout << "Pendaftaran berhasil. Silakan login dengan username dan password yang baru." << endl;
    return newUser;
}


void buatAkunAdmin() {
    if (numUsers < MAX_USERS) {
        string username = "admin";
        string password = "admin";
        users[numUsers] = {username, password, true}; // Tandai sebagai admin
        numUsers++;
    } else {
        cout << "Batas pengguna telah tercapai. Tidak dapat membuat akun admin." << endl;
    }
}

class TiketLinkedList {
private:
    Tiket* head;

public:
    TiketLinkedList() {
        head = NULL;
    }

Tiket* getHead() {
        return head;
    }



void addTiket(const string& keberangkatan, const string& tujuan, const string& jam, int kursi, double harga, const string& nomorBus, int nomorUrutan) {
    // Tambahkan validasi harga di sini
    if (harga <= 0) {
        cout << "Harga tiket harus lebih dari 0." << endl;
        return;
    }
    
    // Tambahkan validasi format jam di sini
    if (jam.length() != 5 || jam[2] != ':') {
        cout << "Format jam tidak valid. Gunakan format 24 jam seperti 'HH:MM'." << endl;
        return;
    }

    int hour = stoi(jam.substr(0, 2));
    int minute = stoi(jam.substr(3, 2));

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        cout << "Jam tidak valid. Gunakan format 24 jam seperti 'HH:MM'." << endl;
        return;
    }

    Tiket* newTiket = new Tiket;

    newTiket->keberangkatan = keberangkatan;
    newTiket->tujuan = tujuan;
    newTiket->jam = jam;
    newTiket->kursi = kursi;
    newTiket->harga = harga;
    newTiket->nomorBus = nomorBus;
    newTiket->next = NULL;

    if (nomorUrutan == 1) {
        newTiket->next = head;
        head = newTiket;
        cout << "Tiket berhasil ditambahkan di awal." << endl;
    } else {
        Tiket* current = head;
        int urutan = 1;

        while (current != NULL) {
            if (urutan == nomorUrutan - 1) {
                newTiket->next = current->next;
                current->next = newTiket;
                cout << "Tiket berhasil ditambahkan di posisi " << nomorUrutan << "." << endl;
                return;
            }
            current = current->next;
            urutan++;
        }

        if (nomorUrutan == urutan + 1) {
            // Menambahkan tiket di akhir jika nomorUrutan melebihi nomor data yang ada
            current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newTiket;
            cout << "Tiket berhasil ditambahkan di akhir." << endl;
        } else {
            cout << "Nomor urutan tiket tidak valid. Tiket tidak ditambahkan." << endl;
        }
    }
}


// Fungsi untuk menampilkan data tiket
void tampilkanDataTiket() {
        Tiket* current = head;
        int nomorUrutan = 1;

        if (current == NULL) {
            cout << "Belum ada tiket yang terdaftar." << endl;
        } else {
            cout << "============================================================================================================" << endl;
            cout << "No  | Nomor Bus | Keberangkatan        | Tujuan                | Jam        | Kursi     | Harga            |" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            while (current != NULL) {
                printf("%-3d | %-9s | %-20s | %-21s | %-9s | %-6d | %-13.2f |\n", nomorUrutan, current->nomorBus.c_str(), current->keberangkatan.c_str(), current->tujuan.c_str(), current->jam.c_str(), current->kursi, current->harga);
                nomorUrutan++;
                current = current->next;
            }
            cout << "============================================================================================================" << endl;
        }
    }

void updateTiket(int nomorUrutan) {
    Tiket* current = head;
    int nomor = 1;

    while (current != NULL) {
        if (nomor == nomorUrutan) {
            string keberangkatan, tujuan, jam;
            int kursi;
            double harga;
            cin.ignore(); // Membersihkan buffer
            cout << "Masukkan Kota Keberangkatan tiket yang akan diperbarui: ";
            getline(cin, keberangkatan);
            cout << "Masukkan Kota Tujuan tiket yang akan diperbarui: ";
            getline(cin, tujuan);

            // Error handling untuk format jam
            do {
                cout << "Masukkan Jam Keberangkatan tiket yang akan diperbarui (format 24 jam HH:MM): ";
                cin >> jam;

                if (jam.length() != 5 || jam[2] != ':' || stoi(jam.substr(0, 2)) < 0 || stoi(jam.substr(0, 2)) > 23 || stoi(jam.substr(3, 2)) < 0 || stoi(jam.substr(3, 2)) > 59) {
                    cout << "Format jam tidak valid. Gunakan format 24 jam seperti 'HH:MM'" << endl;
                } else {
                    break;
                }
            } while (true);

            do {
                cout << "Masukkan Jumlah Kursi Baru: ";
                cin >> kursi;

                if (kursi <= 0) {
                    cout << "Jumlah kursi harus lebih dari 0. Masukkan kembali." << endl;
                } else {
                    break;
                }
            } while (true);

            do {
                cout << "Masukkan Harga Baru: ";
                cin >> harga;

                if (harga <= 0) {
                    cout << "Harga harus lebih dari 0. Masukkan kembali." << endl;
                } else {
                    break;
                }
            } while (true);

            current->keberangkatan = keberangkatan;
            current->tujuan = tujuan;
            current->jam = jam;
            current->kursi = kursi;
            current->harga = harga;

            cout << "Data tiket berhasil diperbarui." << endl;
            return;
        }
        nomor++;
        current = current->next;
    }
    cout << "Tiket dengan nomor urutan tersebut tidak ditemukan, data tidak dapat diperbarui" << endl;
}

// Fungsi untuk menghapus tiket di awal linked list
void deleteTiket(int posisi, const string& targetKeberangkatan) {
    if (head != NULL) {
        if (posisi == 1) {
            Tiket* temp = head;
            head = head->next;
            delete temp;
            cout << "Tiket di awal berhasil dihapus." << endl;
        } else if (posisi == 3) {
            if (head->next == NULL) {
                Tiket* temp = head;
                head = NULL;
                delete temp;
                cout << "Tiket di akhir berhasil dihapus." << endl;
            } else {
                Tiket* current = head;
                Tiket* prev = NULL;
                while (current->next != NULL) {
                    prev = current;
                    current = current->next;
                }
                prev->next = NULL;
                delete current;
                cout << "Tiket di akhir berhasil dihapus." << endl;
            }
        } else if (posisi == 2) {
            if (head->keberangkatan == targetKeberangkatan) {
                Tiket* temp = head;
                head = head->next;
                delete temp;
                cout << "Tiket di tengah berhasil dihapus." << endl;
            } else {
                Tiket* current = head;
                Tiket* prev = NULL;
                while (current != NULL) {
                    if (current->keberangkatan == targetKeberangkatan) {
                        prev->next = current->next;
                        delete current;
                        cout << "Tiket di tengah berhasil dihapus." << endl;
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
                cout << "Kota keberangkatan tiket tidak ditemukan. Tiket tidak dihapus." << endl;
            }
        } else {
            cout << "Posisi penghapusan tiket tidak valid." << endl;
        }
    } else {
        cout << "Tidak ada tiket untuk dihapus." << endl;
    }
}

    ~TiketLinkedList() {
        while (head != NULL) {
            Tiket* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Implementasi Jump Sort Ascending
void ShellSortAscending(TiketLinkedList &tiketList) {
    Tiket* current = tiketList.getHead();
    int n = 0;

    // Menghitung jumlah tiket dalam linked list
    while (current != NULL) {
        n++;
        current = current->next;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            current = tiketList.getHead();

            // Mencari tiket yang akan dipindahkan
            for (int j = 0; j < i; j++) {
                if (current != NULL) {
                    current = current->next;
                }
            }

            if (current != NULL) {
                Tiket temp = *current;  // Simpan tiket sementara
                int j = i;

                // Geser tiket yang lebih besar ke posisi yang sesuai
                while (j >= gap) {
                    current = tiketList.getHead();
                    for (int k = 0; k < j - gap; k++) {
                        if (current != NULL) {
                            current = current->next;
                        }
                    }

                    if (current != NULL) {
                        if (temp.harga >= current->harga) {
                            break;
                        }
                    }

                    j -= gap;
                }

                current = tiketList.getHead();
                for (int k = 0; k < j; k++) {
                    if (current != NULL) {
                        current = current->next;
                    }
                }

                if (current != NULL) {
                    current->next = new Tiket(temp);  // Salin tiket
                }
            }
        }
    }
}

void menuAdmin(Pengguna &currentUser, TiketLinkedList &tiketList) {
    bool kembaliKeMenuUtama = false;

    do {
        cout << "====================================" << endl;
        cout << "|              MENU ADMIN:         |" << endl;
        cout << "====================================" << endl;
        cout << "| 1. Tambah Tiket                  |" << endl;
        cout << "| 2. Tampilkan Data Tiket          |" << endl;
        cout << "| 3. Update Tiket                  |" << endl;
        cout << "| 4. Hapus Tiket                   |" << endl;
        cout << "| 5. Urutkan Tiket (Shell Sort)    |" << endl;
        cout << "| 6. Tampilkan User yang regis     |" << endl;
        cout << "| 7. Hapus User                    |" << endl;
        cout << "| 8. Kembali ke Menu Utama         |" << endl;
        cout << "====================================" << endl;
        cout << "Pengguna saat ini: " << currentUser.username << (currentUser.isAdmin ? " (Admin)" : " (User)") << endl;
        cout << "Pilih Menu : ";
        int pilihan;
        cin >> pilihan;
        cin.ignore(1000, '\n'); // Hapus newline dari input

        switch (pilihan) {
            case 1: // Tambah Tiket
                if (currentUser.isAdmin) {
                    string keberangkatan, tujuan, jam, nomorBus;
                    int kursi;
                    double harga;

                cout << "Masukkan Nomor Bus (angka di atas 0): ";
                cin >> nomorBus;

                // Error handling untuk nomor bus
                while (true) {
                    bool isNumber = true;
                    for (char c : nomorBus) {
                        if (!isdigit(c)) {
                            isNumber = false;
                            break;
                        }
                    }

                    if (!isNumber || stoi(nomorBus) <= 0) {
                        cout << "Nomor Bus harus berupa angka di atas 0" << endl;
                        cout << "Masukkan Nomor Bus (angka di atas 0): ";
                        cin >> nomorBus;
                    } else {
                        break;
                    }
                }

                cout << "Masukkan Kota Keberangkatan (hanya huruf): ";
                cin >> keberangkatan;

                // Error handling untuk kota keberangkatan
                while (true) {
                    bool isAlphabetic = true;
                    for (char c : keberangkatan) {
                        if (!isalpha(c)) {
                            isAlphabetic = false;
                            break;
                        }
                    }

                    if (!isAlphabetic) {
                        cout << "Kota Keberangkatan harus berisi huruf" << endl;
                        cout << "Masukkan Kota Keberangkatan (hanya huruf): ";
                        cin >> keberangkatan;
                    } else {
                        break;
                    }
                }

                cout << "Masukkan Kota Tujuan (hanya huruf): ";
                cin >> tujuan;

                // Error handling untuk kota tujuan
                while (true) {
                    bool isAlphabetic = true;
                    for (char c : tujuan) {
                        if (!isalpha(c)) {
                            isAlphabetic = false;
                            break;
                        }
                    }

                    if (!isAlphabetic) {
                        cout << "Kota Tujuan harus berisi huruf" << endl;
                        cout << "Masukkan Kota Tujuan (hanya huruf): ";
                        cin >> tujuan;
                    } else {
                        break;
                    }
                }

                // Error handling untuk format jam
                do {
                    cout << "Masukkan Jam Keberangkatan (format 24 jam HH:MM): ";
                    cin >> jam;

                    if (jam.length() != 5 || jam[2] != ':' || stoi(jam.substr(0, 2)) < 0 || stoi(jam.substr(0, 2)) > 23 || stoi(jam.substr(3, 2)) < 0 || stoi(jam.substr(3, 2)) > 59) {
                        cout << "Format jam tidak valid Gunakan format 24 jam seperti 'HH:MM'" << endl;
                    } else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Masukkan Harga Tiket (angka di atas 0): ";
                    cin >> harga;

                    if (harga <= 0) {
                        cout << "Harga Tiket harus angka di atas 0" << endl;
                        cout << "Masukkan Harga Tiket (angka di atas 0): ";
                    } else {
                        break;
                    }
                } while (true);

                cout << "Masukkan Jumlah Kursi Tersedia: ";
                cin >> kursi;

                cout << "Pilih posisi penambahan tiket (1: Awal, 2: Tengah, 3: Akhir): ";
                int posisi;
                cin >> posisi;

                if (posisi == 2) {
                    int nomorUrutan;
                    cout << "Masukkan nomor urutan tiket yang menjadi posisi tengah: ";
                    cin >> nomorUrutan;
                    tiketList.addTiket(keberangkatan, tujuan, jam, kursi, harga, nomorBus, nomorUrutan);
                } else {
                    tiketList.addTiket(keberangkatan, tujuan, jam, kursi, harga, nomorBus, posisi);
                }
            } else {
                cout << "Anda tidak memiliki izin untuk menambahkan tiket" << endl;
            }
            case 2:
                tiketList.tampilkanDataTiket();
                break;

            case 3:
                int nomor_urutan;
                cout << "Masukkan nomor urutan tiket yang akan diperbarui: ";
                cin >> nomor_urutan;
                tiketList.updateTiket(nomor_urutan);
                break;

            case 4:
                if (currentUser.isAdmin) {
                    cout << "Pilih posisi penghapusan tiket (1: Awal, 2: Tengah, 3: Akhir): ";
                    int posisiHapus;
                    cin >> posisiHapus;

                    if (posisiHapus == 1) {
                        tiketList.deleteTiket(1, "");
                    } else if (posisiHapus == 2) {
                        string targetKeberangkatan;
                        cout << "Masu1kkan Kota Keberangkatan Tiket yang akan dihapus: ";
                        cin >> targetKeberangkatan;
                        tiketList.deleteTiket(2, targetKeberangkatan);
                    } else if (posisiHapus == 3) {
                        tiketList.deleteTiket(3, "");
                    } else {
                        cout << "Posisi penghapusan tiket tidak valid" << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki izin untuk menghapus tiket" << endl;
                }
                break;

            case 5:
                if (currentUser.isAdmin) {
                    cout << "Urutkan Tiket:" << endl;
                    cout << "1. Ascending (Harga terendah ke tertinggi)" << endl;
                    cout << "Pilih urutan: ";
                    int urutan;
                    cin >> urutan;

                    if (urutan == 1) {
                        ShellSortAscending(tiketList);
                        cout << "Data tiket berhasil diurutkan berdasarkan harga tiket secara ascending menggunakan Shell Sort" << endl;
                    } else {
                        cout << "Pilihan urutan tidak valid" << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki izin untuk mengurutkan tiket" << endl;
                }
                break;

            case 6:
                if (currentUser.isAdmin) {
                    TampilkanDataUser();
                } else {
                    cout << "Anda tidak memiliki izin untuk melihat data pengguna" << endl;
                }
                break;

            case 7:
                DequeueUser();
                break;

            case 8:
                return;
            default:
                cout << "Pilihan tidak valid Silakan coba lagi" << endl;
        }

        if (kembaliKeMenuUtama) {
            break; // Keluar dari loop jika pengguna memilih kembali ke menu utama
        }
    } while (true);
}

void BoyerMooreSearch(TiketLinkedList &tiketList, const string &kotaKeberangkatan) {
    Tiket* current = tiketList.getHead();
    int nomorUrutan = 1;
    bool ditemukan = false;

    while (current != NULL) {
        int m = kotaKeberangkatan.length();
        int n = current->keberangkatan.length();

        int badChar[256]; // Tabel karakter buruk
        for (int i = 0; i < 256; i++) {
            badChar[i] = m; // Inisialisasi semua karakter dengan panjang pola
        }

        // Isi karakter buruk
        for (int i = 0; i < m - 1; i++) {
            badChar[kotaKeberangkatan[i]] = m - 1 - i;
        }

        int s = 0; // Posisi pencocokan dalam teks

        while (s <= (n - m)) {
            int j = m - 1;

            // Mengecek karakter dari belakang ke depan
            while (j >= 0 && kotaKeberangkatan[j] == current->keberangkatan[s + j]) {
                j--;
            }

            if (j < 0) {
                // Keseluruhan pola cocok
                if (!ditemukan) {
                    cout << "Tiket dengan keberangkatan " << kotaKeberangkatan << " ditemukan:" << endl;
                    ditemukan = true;
                }

                // Tampilkan tiket yang cocok
                cout << "Nomor Urutan: " << nomorUrutan << endl;
                cout << "Nomor Bus: " << current->nomorBus << endl;
                cout << "Keberangkatan: " << current->keberangkatan << endl;
                cout << "Tujuan: " << current->tujuan << endl;
                cout << "Jam: " << current->jam << endl;
                cout << "Kursi: " << current->kursi << endl;
                cout << "Harga: " << current->harga << endl;
                cout << "=============================" << endl;
                break;
            }

            s += max(1, j - badChar[current->keberangkatan[s + j]]);
        }

        current = current->next;
        nomorUrutan++;
    }

    if (!ditemukan) {
        cout << "Tiket dengan keberangkatan " << kotaKeberangkatan << " tidak ditemukan" << endl;
    }
}

void beliTiket(Pengguna &currentUser, TiketLinkedList &tiketList, int &jumlahTiket, int &totalHarga) {
    string nomorBus;
    cout << "Masukkan Nomor Bus tiket yang akan dibeli : ";
    cin >> nomorBus;

    Tiket* current = tiketList.getHead();
    while (current != NULL) {
        if (current->nomorBus == nomorBus) {
            if (current->kursi > 0) {
                // ... (kode pembelian yang sudah ada)

                // Menyimpan informasi tiket yang dibeli
                jumlahTiket = 1;
                totalHarga = current->harga;

                // Kurangi jumlah kursi yang tersedia
                current->kursi--;

                // Update linked list dan keluar dari fungsi
                tiketList.updateTiket(0);
                return;
            } else {
                cout << "Maaf, tiket untuk Nomor Bus " << nomorBus << " sudah habis" << endl;
                return;
            }
        }
        current = current->next;
    }
    // Jika nomor bus tidak ditemukan
    cout << "Nomor Bus " << nomorBus << " tidak ditemukan" << endl;
}

void tampilkanMenuPembayaran(Pengguna &currentUser, TiketLinkedList &tiketList) {
    cout << "====================================" << endl;
    cout << "|           MENU PEMBAYARAN         |" << endl;
    cout << "====================================" << endl;
    cout << "| 1. Transfer Bank                  |" << endl;
    cout << "| 2. Kartu Kredit                   |" << endl;
    cout << "| 3. Uang Elektronik (e-Wallet)     |" << endl;
    cout << "| 4. Kembali ke Menu Utama          |" << endl;
    cout << "====================================" << endl;
    cout << "Pilih metode pembayaran: ";
    int pilihan;
        cin >> pilihan;
}

void tampilkanStrukPembayaran(Tiket tiket, int jumlahTiket, int totalHarga, string metodePembayaran) {
    cout << "\n====================================" << endl;
    cout << "           STRUK PEMBAYARAN          " << endl;
    cout << "====================================" << endl;
    cout << "Tujuan            : " << tiket.tujuan << endl;
    cout << "Jumlah Tiket      : " << jumlahTiket << endl;
    cout << "Harga per Tiket   : " << tiket.harga << endl;
    cout << "Metode Pembayaran : " << metodePembayaran << endl;
    cout << "Total Harga       : " << totalHarga << endl;
    cout << "====================================" << endl;
    cout << "Terima kasih telah melakukan pembayaran!" << endl;
}

// Fungsi utama untuk menangani pembayaran tiket
void prosesPembayaran(Tiket tiket, int jumlahTiket, int totalHarga, Pengguna &currentUser, TiketLinkedList &tiketList) {
    tampilkanMenuPembayaran(currentUser, tiketList);

    int pilihanPembayaran;
    cin >> pilihanPembayaran;

    string metodePembayaran;

    switch (pilihanPembayaran) {
        case 1:
            metodePembayaran = "Transfer Bank";
            break;

        case 2:
            metodePembayaran = "Kartu Kredit";
            break;

        case 3:
            metodePembayaran = "Uang Elektronik (e-Wallet)";
            break;

        case 4:
            return;

        default:
            cout << "Pilihan pembayaran tidak valid. Silakan coba lagi" << endl;
            return;
    }

    // Tampilkan struk pembayaran
    tampilkanStrukPembayaran(tiket, jumlahTiket, totalHarga, metodePembayaran);

    // Kembali ke menu utama setelah pembayaran
    cout << "Pembayaran berhasil! Kembali ke Menu Utama." << endl;
    return;
}

void menuPelanggan(Pengguna &currentUser, TiketLinkedList &tiketList) {
    bool kembaliKeMenuUtama = false;
    int jumlahTiket = 0;  // Tambahkan variabel jumlahTiket dan totalHarga di sini
    int totalHarga = 0;

    do {
        cout << "====================================" << endl;
        cout << "|              MENU :              |" << endl;
        cout << "====================================" << endl;
        cout << "| 1. Tampilkan Tiket               |" << endl;
        cout << "| 2. Cari Tiket Berdasarkan Kota   |" << endl;
        cout << "| 3. Pembayaran                    |" << endl;  // Tambahkan opsi pembayaran
        cout << "| 4. Exit                          |" << endl;
        cout << "====================================" << endl;
        cout << "Pengguna yang saat ini : " << currentUser.username << (currentUser.isAdmin ? " (Admin)" : " (User)") << endl;
        cout << "Pilih Menu : ";
        int pilihan;
        cin >> pilihan;
        cin.ignore(1000, '\n'); // Hapus newline dari input

        switch (pilihan) {
            case 1:
                tiketList.tampilkanDataTiket();
                break;

            case 2: 
            {
                string kotaKeberangkatan;
                cout << "Masukkan Kota Keberangkatan yang ingin Anda cari: ";
                cin.ignore();
                getline(cin, kotaKeberangkatan);

                BoyerMooreSearch(tiketList, kotaKeberangkatan);
                break;
            }

            case 3:
            {
                beliTiket(currentUser, tiketList, jumlahTiket, totalHarga);
                Tiket *tiket = tiketList.getHead();
                if (tiket != NULL) {
                    prosesPembayaran(*tiket, jumlahTiket, totalHarga, currentUser, tiketList);
                } else {
                    cout << "Tiket tidak tersedia" << endl;
                }
                // Kembali ke menu utama setelah pembayaran
                kembaliKeMenuUtama = true;
                break;
            }

            case 4:
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi" << endl;
        }

    } while (true);
}

void tampilkanMenuSetelahLogin(Pengguna &currentUser, TiketLinkedList &tiketList) {
    bool kembaliKeMenuUtama = false;

    do {
        if (currentUser.isAdmin) {
            menuAdmin(currentUser, tiketList);
        } else {
            menuPelanggan(currentUser, tiketList);
        }

        cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
        char pilihan;
        cin >> pilihan;
        cin.ignore(1000, '\n');

        if (pilihan == 'y' || pilihan == 'Y') {
            kembaliKeMenuUtama = true;
        }
    } while (!kembaliKeMenuUtama);
}

int getMenuOption() {
    int option; 
    cout << "Pilih Menu: ";

    while (!(cin >> option) || option < 1 || option > 3) {
        cout << "Input tidak valid. Masukkan angka antara 1 dan 3" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return option;
}

int main() {
    Pengguna currentUser;
    TiketLinkedList tiketList;
    int percobaanLogin = 3;

    while (percobaanLogin > 0) {
        if (currentUser.username.empty()) {
            cout << "====================================" << endl;
            cout << "|              MENU :              |" << endl;
            cout << "====================================" << endl;
            cout << "| 1. Register                      |" << endl;
            cout << "| 2. Login                         |" << endl;
            cout << "| 3. Keluar                        |" << endl;
            cout << "====================================" << endl;

            int menu_utama = getMenuOption();
            cin.ignore(1000, '\n');

            switch (menu_utama) {
                case 1:
                    lakukanPendaftaran();
                    break;
                case 2:
                    currentUser = lakukanLogin();
                    if (currentUser.username.empty()) {
                        percobaanLogin--;
                        cout << "Sisa percobaan login: " << percobaanLogin << endl;
                        if (percobaanLogin == 0) {
                            cout << "Anda telah menggunakan semua percobaan login. Program berhenti." << endl;
                            exit(0);
                        }
                    } else if (currentUser.isAdmin) {
                        // Jika login sebagai admin, tampilkan menu admin
                        menuAdmin(currentUser, tiketList);
                        // Lakukan logika untuk menu admin
                        // Setelah selesai, logout admin
                        currentUser = Pengguna();
                    }
                    break;
                case 3:
                    cout << "Keluar dari program" << endl;
                    exit(0);
                default:
                    cout << "Pilihan tidak valid. Coba lagi" << endl;
            }
        } else {
            // Tampilkan menu setelah login (user atau admin)
            // ...
            currentUser = Pengguna();  // Mengosongkan data pengguna setelah keluar dari menu setelah login
        }
    }

    return 0;
}
#include <iostream>
#include <string>
#include <cmath>
#include <limits>  
#include <iomanip>
#include <queue>
using namespace std;

struct Pengguna {
    string username;
    string password;
    bool isAdmin;
};


struct Tiket {
    string keberangkatan;
    string tujuan;
    string jam;
    int kursi;
    double harga;
    string nomorBus; 
    Tiket* next;
};

const int MAX_USERS = 100;
Pengguna users[MAX_USERS];
int numUsers = 0;
Tiket tikets[100];   // Array untuk menyimpan tiket
int numTikets = 0;   // Jumlah tiket yang disimpan

// Gunakan queue untuk menyimpan data pengguna
queue<Pengguna> userQueue;


// Fungsi untuk menampilkan data pengguna dari antrian
void TampilkanDataUser()
{
    if (userQueue.empty()) //untuk mengecek jika antria kosong atau tidak
    {
        cout << "Tidak ada user yang terdaftar.\n";
        return; //jika tidak ada maka system akan mengembalikan(return) dari fungsi
    }

    const int usernameWidth = 20; //ini untuk mengatur lebar kolom pada username di tampilan  
    queue<Pengguna> tempQueue; //membuat sebuah antrian sementara dan menyimpan salinan data pengguna dari antrian

    cout << "\nDaftar User Terdaftar:\n";
    cout << "+" << string(usernameWidth, '-') << "+\n";
    cout << "| " << left << setw(usernameWidth - 2) << "Username"
         << " |\n";
    cout << "+" << string(usernameWidth, '-') << "+\n";
        //mencetak baris pemisah dengan lebar yang sesuai dengan usernameWidth
    while (!userQueue.empty())
    {
        Pengguna currentUser = userQueue.front(); //program mengambil data pengguna pertama dari antrian users menggunakan front(), program mengambil data pengguna pertama dari antrian users menggunakan front()
        cout << "| " << left << setw(usernameWidth - 2) << currentUser.username << " |\n"; //untuk menampilkan 
        userQueue.pop(); // Setelah user ditampilkan user tersebut dihapus dari antrian users dengan menggunakan pop(), dan dipindahkan ke antrian sementara tempQueue
        tempQueue.push(currentUser); //data akan disimpan kembali ke antrian tempQueue, ini agar urutan data pengguna di antrian sementara sesuai dengan urutan asli di antrian users
    }

    cout << "+" << string(usernameWidth, '-') << "+\n"; // untuk menampilkan 

    // Mengembalikan user ke queue asli
    while (!tempQueue.empty()) //ini akan mengeloop dan berjalan selama antrian sementara tempQueue masih berisi elemen
    {
        userQueue.push(tempQueue.front());// selama loop, elemen pertama dari antrian sementara (tempQueue) diambil menggunakan front(), dan di kembalikan ke antrian users menggunakan push()
        tempQueue.pop(); //ini di gunakan untuk menghapus antrian sementara, setelah data di pindah ke antrian Users
    }
}


void DequeueUser()
{
    if (userQueue.empty()) // Memeriksa apakah antrian users kosong.
    {
        cout << "Antrian user kosong, tidak ada user untuk di-dequeue.\n";
        return;
    }

    Pengguna removedUser = userQueue.front();
    userQueue.pop(); // Menghapus elemen pertama (front) dari antrian users dan menyimpannya dalam "removedUser".
    cout << "User " << removedUser.username << " telah di-dequeue dari antrian.\n";
}


// Fungsi untuk melakukan login
Pengguna lakukanLogin() {
    Pengguna user;
    cout << "Masukkan username: ";
    cin >> user.username;
    cout << "Masukkan password: ";
    cin >> user.password;

    // Contoh pengecekan login admin (username dan password admin)
    if (user.username == "admin" && user.password == "admin") {
        user.isAdmin = true;
    } else {
        user.isAdmin = false;
    }

    // Tambahkan pengguna ke dalam antrian
    userQueue.push(user);

    return user;
}

// Fungsi untuk melakukan pendaftaran
Pengguna lakukanPendaftaran() {
    string username, password;
    cout << "Masukkan username: ";
    cin >> username;
    cout << "Masukkan password: ";
    cin >> password;

    if (numUsers >= MAX_USERS) {
        cout << "Batas pengguna telah tercapai. Pendaftaran gagal." << endl;
        return { "", "", false }; // Pengguna tidak valid
    }

    // Periksa apakah pengguna dengan username yang sama sudah ada
    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == username) {
            cout << "Pengguna dengan username tersebut sudah terdaftar. Pendaftaran gagal." << endl;
            return { "", "", false }; // Pengguna tidak valid
        }
    }

    // Tambahkan pengguna ke dalam antrian
    Pengguna newUser = {username, password, false};
    userQueue.push(newUser);

    // Tambahkan pengguna ke dalam array pengguna
    users[numUsers] = newUser;
    numUsers++;

    cout << "Pendaftaran berhasil. Silakan login dengan username dan password yang baru." << endl;
    return newUser;
}


void buatAkunAdmin() {
    if (numUsers < MAX_USERS) {
        string username = "admin";
        string password = "admin";
        users[numUsers] = {username, password, true}; // Tandai sebagai admin
        numUsers++;
    } else {
        cout << "Batas pengguna telah tercapai. Tidak dapat membuat akun admin." << endl;
    }
}

class TiketLinkedList {
private:
    Tiket* head;

public:
    TiketLinkedList() {
        head = NULL;
    }

Tiket* getHead() {
        return head;
    }



void addTiket(const string& keberangkatan, const string& tujuan, const string& jam, int kursi, double harga, const string& nomorBus, int nomorUrutan) {
    // Tambahkan validasi harga di sini
    if (harga <= 0) {
        cout << "Harga tiket harus lebih dari 0." << endl;
        return;
    }
    
    // Tambahkan validasi format jam di sini
    if (jam.length() != 5 || jam[2] != ':') {
        cout << "Format jam tidak valid. Gunakan format 24 jam seperti 'HH:MM'." << endl;
        return;
    }

    int hour = stoi(jam.substr(0, 2));
    int minute = stoi(jam.substr(3, 2));

    if (hour < 0 || hour > 23 || minute < 0 || minute > 59) {
        cout << "Jam tidak valid. Gunakan format 24 jam seperti 'HH:MM'." << endl;
        return;
    }

    Tiket* newTiket = new Tiket;

    newTiket->keberangkatan = keberangkatan;
    newTiket->tujuan = tujuan;
    newTiket->jam = jam;
    newTiket->kursi = kursi;
    newTiket->harga = harga;
    newTiket->nomorBus = nomorBus;
    newTiket->next = NULL;

    if (nomorUrutan == 1) {
        newTiket->next = head;
        head = newTiket;
        cout << "Tiket berhasil ditambahkan di awal." << endl;
    } else {
        Tiket* current = head;
        int urutan = 1;

        while (current != NULL) {
            if (urutan == nomorUrutan - 1) {
                newTiket->next = current->next;
                current->next = newTiket;
                cout << "Tiket berhasil ditambahkan di posisi " << nomorUrutan << "." << endl;
                return;
            }
            current = current->next;
            urutan++;
        }

        if (nomorUrutan == urutan + 1) {
            // Menambahkan tiket di akhir jika nomorUrutan melebihi nomor data yang ada
            current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newTiket;
            cout << "Tiket berhasil ditambahkan di akhir." << endl;
        } else {
            cout << "Nomor urutan tiket tidak valid. Tiket tidak ditambahkan." << endl;
        }
    }
}


// Fungsi untuk menampilkan data tiket
void tampilkanDataTiket() {
        Tiket* current = head;
        int nomorUrutan = 1;

        if (current == NULL) {
            cout << "Belum ada tiket yang terdaftar." << endl;
        } else {
            cout << "============================================================================================================" << endl;
            cout << "No  | Nomor Bus | Keberangkatan        | Tujuan                | Jam        | Kursi     | Harga            |" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            while (current != NULL) {
                printf("%-3d | %-9s | %-20s | %-21s | %-9s | %-6d | %-13.2f |\n", nomorUrutan, current->nomorBus.c_str(), current->keberangkatan.c_str(), current->tujuan.c_str(), current->jam.c_str(), current->kursi, current->harga);
                nomorUrutan++;
                current = current->next;
            }
            cout << "============================================================================================================" << endl;
        }
    }

void updateTiket(int nomorUrutan) {
    Tiket* current = head;
    int nomor = 1;

    while (current != NULL) {
        if (nomor == nomorUrutan) {
            string keberangkatan, tujuan, jam;
            int kursi;
            double harga;
            cin.ignore(); // Membersihkan buffer
            cout << "Masukkan Kota Keberangkatan tiket yang akan diperbarui: ";
            getline(cin, keberangkatan);
            cout << "Masukkan Kota Tujuan tiket yang akan diperbarui: ";
            getline(cin, tujuan);

            // Error handling untuk format jam
            do {
                cout << "Masukkan Jam Keberangkatan tiket yang akan diperbarui (format 24 jam HH:MM): ";
                cin >> jam;

                if (jam.length() != 5 || jam[2] != ':' || stoi(jam.substr(0, 2)) < 0 || stoi(jam.substr(0, 2)) > 23 || stoi(jam.substr(3, 2)) < 0 || stoi(jam.substr(3, 2)) > 59) {
                    cout << "Format jam tidak valid. Gunakan format 24 jam seperti 'HH:MM'" << endl;
                } else {
                    break;
                }
            } while (true);

            do {
                cout << "Masukkan Jumlah Kursi Baru: ";
                cin >> kursi;

                if (kursi <= 0) {
                    cout << "Jumlah kursi harus lebih dari 0. Masukkan kembali." << endl;
                } else {
                    break;
                }
            } while (true);

            do {
                cout << "Masukkan Harga Baru: ";
                cin >> harga;

                if (harga <= 0) {
                    cout << "Harga harus lebih dari 0. Masukkan kembali." << endl;
                } else {
                    break;
                }
            } while (true);

            current->keberangkatan = keberangkatan;
            current->tujuan = tujuan;
            current->jam = jam;
            current->kursi = kursi;
            current->harga = harga;

            cout << "Data tiket berhasil diperbarui." << endl;
            return;
        }
        nomor++;
        current = current->next;
    }
    cout << "Tiket dengan nomor urutan tersebut tidak ditemukan, data tidak dapat diperbarui" << endl;
}

// Fungsi untuk menghapus tiket di awal linked list
void deleteTiket(int posisi, const string& targetKeberangkatan) {
    if (head != NULL) {
        if (posisi == 1) {
            Tiket* temp = head;
            head = head->next;
            delete temp;
            cout << "Tiket di awal berhasil dihapus." << endl;
        } else if (posisi == 3) {
            if (head->next == NULL) {
                Tiket* temp = head;
                head = NULL;
                delete temp;
                cout << "Tiket di akhir berhasil dihapus." << endl;
            } else {
                Tiket* current = head;
                Tiket* prev = NULL;
                while (current->next != NULL) {
                    prev = current;
                    current = current->next;
                }
                prev->next = NULL;
                delete current;
                cout << "Tiket di akhir berhasil dihapus." << endl;
            }
        } else if (posisi == 2) {
            if (head->keberangkatan == targetKeberangkatan) {
                Tiket* temp = head;
                head = head->next;
                delete temp;
                cout << "Tiket di tengah berhasil dihapus." << endl;
            } else {
                Tiket* current = head;
                Tiket* prev = NULL;
                while (current != NULL) {
                    if (current->keberangkatan == targetKeberangkatan) {
                        prev->next = current->next;
                        delete current;
                        cout << "Tiket di tengah berhasil dihapus." << endl;
                        return;
                    }
                    prev = current;
                    current = current->next;
                }
                cout << "Kota keberangkatan tiket tidak ditemukan. Tiket tidak dihapus." << endl;
            }
        } else {
            cout << "Posisi penghapusan tiket tidak valid." << endl;
        }
    } else {
        cout << "Tidak ada tiket untuk dihapus." << endl;
    }
}

    ~TiketLinkedList() {
        while (head != NULL) {
            Tiket* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Implementasi Jump Sort Ascending
void ShellSortAscending(TiketLinkedList &tiketList) {
    Tiket* current = tiketList.getHead();
    int n = 0;

    // Menghitung jumlah tiket dalam linked list
    while (current != NULL) {
        n++;
        current = current->next;
    }

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            current = tiketList.getHead();

            // Mencari tiket yang akan dipindahkan
            for (int j = 0; j < i; j++) {
                if (current != NULL) {
                    current = current->next;
                }
            }

            if (current != NULL) {
                Tiket temp = *current;  // Simpan tiket sementara
                int j = i;

                // Geser tiket yang lebih besar ke posisi yang sesuai
                while (j >= gap) {
                    current = tiketList.getHead();
                    for (int k = 0; k < j - gap; k++) {
                        if (current != NULL) {
                            current = current->next;
                        }
                    }

                    if (current != NULL) {
                        if (temp.harga >= current->harga) {
                            break;
                        }
                    }

                    j -= gap;
                }

                current = tiketList.getHead();
                for (int k = 0; k < j; k++) {
                    if (current != NULL) {
                        current = current->next;
                    }
                }

                if (current != NULL) {
                    current->next = new Tiket(temp);  // Salin tiket
                }
            }
        }
    }
}

void menuAdmin(Pengguna &currentUser, TiketLinkedList &tiketList) {
    bool kembaliKeMenuUtama = false;

    do {
        cout << "====================================" << endl;
        cout << "|              MENU ADMIN:         |" << endl;
        cout << "====================================" << endl;
        cout << "| 1. Tambah Tiket                  |" << endl;
        cout << "| 2. Tampilkan Data Tiket          |" << endl;
        cout << "| 3. Update Tiket                  |" << endl;
        cout << "| 4. Hapus Tiket                   |" << endl;
        cout << "| 5. Urutkan Tiket (Shell Sort)    |" << endl;
        cout << "| 6. Tampilkan User yang regis     |" << endl;
        cout << "| 7. Hapus User                    |" << endl;
        cout << "| 8. Kembali ke Menu Utama         |" << endl;
        cout << "====================================" << endl;
        cout << "Pengguna saat ini: " << currentUser.username << (currentUser.isAdmin ? " (Admin)" : " (User)") << endl;
        cout << "Pilih Menu : ";
        int pilihan;
        cin >> pilihan;
        cin.ignore(1000, '\n'); // Hapus newline dari input

        switch (pilihan) {
            case 1: // Tambah Tiket
                if (currentUser.isAdmin) {
                    string keberangkatan, tujuan, jam, nomorBus;
                    int kursi;
                    double harga;

                cout << "Masukkan Nomor Bus (angka di atas 0): ";
                cin >> nomorBus;

                // Error handling untuk nomor bus
                while (true) {
                    bool isNumber = true;
                    for (char c : nomorBus) {
                        if (!isdigit(c)) {
                            isNumber = false;
                            break;
                        }
                    }

                    if (!isNumber || stoi(nomorBus) <= 0) {
                        cout << "Nomor Bus harus berupa angka di atas 0" << endl;
                        cout << "Masukkan Nomor Bus (angka di atas 0): ";
                        cin >> nomorBus;
                    } else {
                        break;
                    }
                }

                cout << "Masukkan Kota Keberangkatan (hanya huruf): ";
                cin >> keberangkatan;

                // Error handling untuk kota keberangkatan
                while (true) {
                    bool isAlphabetic = true;
                    for (char c : keberangkatan) {
                        if (!isalpha(c)) {
                            isAlphabetic = false;
                            break;
                        }
                    }

                    if (!isAlphabetic) {
                        cout << "Kota Keberangkatan harus berisi huruf" << endl;
                        cout << "Masukkan Kota Keberangkatan (hanya huruf): ";
                        cin >> keberangkatan;
                    } else {
                        break;
                    }
                }

                cout << "Masukkan Kota Tujuan (hanya huruf): ";
                cin >> tujuan;

                // Error handling untuk kota tujuan
                while (true) {
                    bool isAlphabetic = true;
                    for (char c : tujuan) {
                        if (!isalpha(c)) {
                            isAlphabetic = false;
                            break;
                        }
                    }

                    if (!isAlphabetic) {
                        cout << "Kota Tujuan harus berisi huruf" << endl;
                        cout << "Masukkan Kota Tujuan (hanya huruf): ";
                        cin >> tujuan;
                    } else {
                        break;
                    }
                }

                // Error handling untuk format jam
                do {
                    cout << "Masukkan Jam Keberangkatan (format 24 jam HH:MM): ";
                    cin >> jam;

                    if (jam.length() != 5 || jam[2] != ':' || stoi(jam.substr(0, 2)) < 0 || stoi(jam.substr(0, 2)) > 23 || stoi(jam.substr(3, 2)) < 0 || stoi(jam.substr(3, 2)) > 59) {
                        cout << "Format jam tidak valid Gunakan format 24 jam seperti 'HH:MM'" << endl;
                    } else {
                        break;
                    }
                } while (true);

                do {
                    cout << "Masukkan Harga Tiket (angka di atas 0): ";
                    cin >> harga;

                    if (harga <= 0) {
                        cout << "Harga Tiket harus angka di atas 0" << endl;
                        cout << "Masukkan Harga Tiket (angka di atas 0): ";
                    } else {
                        break;
                    }
                } while (true);

                cout << "Masukkan Jumlah Kursi Tersedia: ";
                cin >> kursi;

                cout << "Pilih posisi penambahan tiket (1: Awal, 2: Tengah, 3: Akhir): ";
                int posisi;
                cin >> posisi;

                if (posisi == 2) {
                    int nomorUrutan;
                    cout << "Masukkan nomor urutan tiket yang menjadi posisi tengah: ";
                    cin >> nomorUrutan;
                    tiketList.addTiket(keberangkatan, tujuan, jam, kursi, harga, nomorBus, nomorUrutan);
                } else {
                    tiketList.addTiket(keberangkatan, tujuan, jam, kursi, harga, nomorBus, posisi);
                }
            } else {
                cout << "Anda tidak memiliki izin untuk menambahkan tiket" << endl;
            }
            case 2:
                tiketList.tampilkanDataTiket();
                break;

            case 3:
                int nomor_urutan;
                cout << "Masukkan nomor urutan tiket yang akan diperbarui: ";
                cin >> nomor_urutan;
                tiketList.updateTiket(nomor_urutan);
                break;

            case 4:
                if (currentUser.isAdmin) {
                    cout << "Pilih posisi penghapusan tiket (1: Awal, 2: Tengah, 3: Akhir): ";
                    int posisiHapus;
                    cin >> posisiHapus;

                    if (posisiHapus == 1) {
                        tiketList.deleteTiket(1, "");
                    } else if (posisiHapus == 2) {
                        string targetKeberangkatan;
                        cout << "Masu1kkan Kota Keberangkatan Tiket yang akan dihapus: ";
                        cin >> targetKeberangkatan;
                        tiketList.deleteTiket(2, targetKeberangkatan);
                    } else if (posisiHapus == 3) {
                        tiketList.deleteTiket(3, "");
                    } else {
                        cout << "Posisi penghapusan tiket tidak valid" << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki izin untuk menghapus tiket" << endl;
                }
                break;

            case 5:
                if (currentUser.isAdmin) {
                    cout << "Urutkan Tiket:" << endl;
                    cout << "1. Ascending (Harga terendah ke tertinggi)" << endl;
                    cout << "Pilih urutan: ";
                    int urutan;
                    cin >> urutan;

                    if (urutan == 1) {
                        ShellSortAscending(tiketList);
                        cout << "Data tiket berhasil diurutkan berdasarkan harga tiket secara ascending menggunakan Shell Sort" << endl;
                    } else {
                        cout << "Pilihan urutan tidak valid" << endl;
                    }
                } else {
                    cout << "Anda tidak memiliki izin untuk mengurutkan tiket" << endl;
                }
                break;

            case 6:
                if (currentUser.isAdmin) {
                    TampilkanDataUser();
                } else {
                    cout << "Anda tidak memiliki izin untuk melihat data pengguna" << endl;
                }
                break;

            case 7:
                DequeueUser();
                break;

            case 8:
                return;
            default:
                cout << "Pilihan tidak valid Silakan coba lagi" << endl;
        }

        if (kembaliKeMenuUtama) {
            break; // Keluar dari loop jika pengguna memilih kembali ke menu utama
        }
    } while (true);
}

void BoyerMooreSearch(TiketLinkedList &tiketList, const string &kotaKeberangkatan) {
    Tiket* current = tiketList.getHead();
    int nomorUrutan = 1;
    bool ditemukan = false;

    while (current != NULL) {
        int m = kotaKeberangkatan.length();
        int n = current->keberangkatan.length();

        int badChar[256]; // Tabel karakter buruk
        for (int i = 0; i < 256; i++) {
            badChar[i] = m; // Inisialisasi semua karakter dengan panjang pola
        }

        // Isi karakter buruk
        for (int i = 0; i < m - 1; i++) {
            badChar[kotaKeberangkatan[i]] = m - 1 - i;
        }

        int s = 0; // Posisi pencocokan dalam teks

        while (s <= (n - m)) {
            int j = m - 1;

            // Mengecek karakter dari belakang ke depan
            while (j >= 0 && kotaKeberangkatan[j] == current->keberangkatan[s + j]) {
                j--;
            }

            if (j < 0) {
                // Keseluruhan pola cocok
                if (!ditemukan) {
                    cout << "Tiket dengan keberangkatan " << kotaKeberangkatan << " ditemukan:" << endl;
                    ditemukan = true;
                }

                // Tampilkan tiket yang cocok
                cout << "Nomor Urutan: " << nomorUrutan << endl;
                cout << "Nomor Bus: " << current->nomorBus << endl;
                cout << "Keberangkatan: " << current->keberangkatan << endl;
                cout << "Tujuan: " << current->tujuan << endl;
                cout << "Jam: " << current->jam << endl;
                cout << "Kursi: " << current->kursi << endl;
                cout << "Harga: " << current->harga << endl;
                cout << "=============================" << endl;
                break;
            }

            s += max(1, j - badChar[current->keberangkatan[s + j]]);
        }

        current = current->next;
        nomorUrutan++;
    }

    if (!ditemukan) {
        cout << "Tiket dengan keberangkatan " << kotaKeberangkatan << " tidak ditemukan" << endl;
    }
}

void beliTiket(Pengguna &currentUser, TiketLinkedList &tiketList, int &jumlahTiket, int &totalHarga) {
    string nomorBus;
    cout << "Masukkan Nomor Bus tiket yang akan dibeli : ";
    cin >> nomorBus;

    Tiket* current = tiketList.getHead();
    while (current != NULL) {
        if (current->nomorBus == nomorBus) {
            if (current->kursi > 0) {
                // ... (kode pembelian yang sudah ada)

                // Menyimpan informasi tiket yang dibeli
                jumlahTiket = 1;
                totalHarga = current->harga;

                // Kurangi jumlah kursi yang tersedia
                current->kursi--;

                // Update linked list dan keluar dari fungsi
                tiketList.updateTiket(0);
                return;
            } else {
                cout << "Maaf, tiket untuk Nomor Bus " << nomorBus << " sudah habis" << endl;
                return;
            }
        }
        current = current->next;
    }
    // Jika nomor bus tidak ditemukan
    cout << "Nomor Bus " << nomorBus << " tidak ditemukan" << endl;
}

void tampilkanMenuPembayaran(Pengguna &currentUser, TiketLinkedList &tiketList) {
    cout << "====================================" << endl;
    cout << "|           MENU PEMBAYARAN         |" << endl;
    cout << "====================================" << endl;
    cout << "| 1. Transfer Bank                  |" << endl;
    cout << "| 2. Kartu Kredit                   |" << endl;
    cout << "| 3. Uang Elektronik (e-Wallet)     |" << endl;
    cout << "| 4. Kembali ke Menu Utama          |" << endl;
    cout << "====================================" << endl;
    cout << "Pilih metode pembayaran: ";
    int pilihan;
        cin >> pilihan;
}

void tampilkanStrukPembayaran(Tiket tiket, int jumlahTiket, int totalHarga, string metodePembayaran) {
    cout << "\n====================================" << endl;
    cout << "           STRUK PEMBAYARAN          " << endl;
    cout << "====================================" << endl;
    cout << "Tujuan            : " << tiket.tujuan << endl;
    cout << "Jumlah Tiket      : " << jumlahTiket << endl;
    cout << "Harga per Tiket   : " << tiket.harga << endl;
    cout << "Metode Pembayaran : " << metodePembayaran << endl;
    cout << "Total Harga       : " << totalHarga << endl;
    cout << "====================================" << endl;
    cout << "Terima kasih telah melakukan pembayaran!" << endl;
}

// Fungsi utama untuk menangani pembayaran tiket
void prosesPembayaran(Tiket tiket, int jumlahTiket, int totalHarga, Pengguna &currentUser, TiketLinkedList &tiketList) {
    tampilkanMenuPembayaran(currentUser, tiketList);

    int pilihanPembayaran;
    cin >> pilihanPembayaran;

    string metodePembayaran;

    switch (pilihanPembayaran) {
        case 1:
            metodePembayaran = "Transfer Bank";
            break;

        case 2:
            metodePembayaran = "Kartu Kredit";
            break;

        case 3:
            metodePembayaran = "Uang Elektronik (e-Wallet)";
            break;

        case 4:
            return;

        default:
            cout << "Pilihan pembayaran tidak valid. Silakan coba lagi" << endl;
            return;
    }

    // Tampilkan struk pembayaran
    tampilkanStrukPembayaran(tiket, jumlahTiket, totalHarga, metodePembayaran);

    // Kembali ke menu utama setelah pembayaran
    cout << "Pembayaran berhasil! Kembali ke Menu Utama." << endl;
    return;
}

void menuPelanggan(Pengguna &currentUser, TiketLinkedList &tiketList) {
    bool kembaliKeMenuUtama = false;
    int jumlahTiket = 0;  // Tambahkan variabel jumlahTiket dan totalHarga di sini
    int totalHarga = 0;

    do {
        cout << "====================================" << endl;
        cout << "|              MENU :              |" << endl;
        cout << "====================================" << endl;
        cout << "| 1. Tampilkan Tiket               |" << endl;
        cout << "| 2. Cari Tiket Berdasarkan Kota   |" << endl;
        cout << "| 3. Pembayaran                    |" << endl;  // Tambahkan opsi pembayaran
        cout << "| 4. Exit                          |" << endl;
        cout << "====================================" << endl;
        cout << "Pengguna yang saat ini : " << currentUser.username << (currentUser.isAdmin ? " (Admin)" : " (User)") << endl;
        cout << "Pilih Menu : ";
        int pilihan;
        cin >> pilihan;
        cin.ignore(1000, '\n'); // Hapus newline dari input

        switch (pilihan) {
            case 1:
                tiketList.tampilkanDataTiket();
                break;

            case 2: 
            {
                string kotaKeberangkatan;
                cout << "Masukkan Kota Keberangkatan yang ingin Anda cari: ";
                cin.ignore();
                getline(cin, kotaKeberangkatan);

                BoyerMooreSearch(tiketList, kotaKeberangkatan);
                break;
            }

            case 3:
            {
                beliTiket(currentUser, tiketList, jumlahTiket, totalHarga);
                Tiket *tiket = tiketList.getHead();
                if (tiket != NULL) {
                    prosesPembayaran(*tiket, jumlahTiket, totalHarga, currentUser, tiketList);
                } else {
                    cout << "Tiket tidak tersedia" << endl;
                }
                // Kembali ke menu utama setelah pembayaran
                kembaliKeMenuUtama = true;
                break;
            }

            case 4:
                return;

            default:
                cout << "Pilihan tidak valid. Silakan coba lagi" << endl;
        }

    } while (true);
}

void tampilkanMenuSetelahLogin(Pengguna &currentUser, TiketLinkedList &tiketList) {
    bool kembaliKeMenuUtama = false;

    do {
        if (currentUser.isAdmin) {
            menuAdmin(currentUser, tiketList);
        } else {
            menuPelanggan(currentUser, tiketList);
        }

        cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
        char pilihan;
        cin >> pilihan;
        cin.ignore(1000, '\n');

        if (pilihan == 'y' || pilihan == 'Y') {
            kembaliKeMenuUtama = true;
        }
    } while (!kembaliKeMenuUtama);
}

int getMenuOption() {
    int option; 
    cout << "Pilih Menu: ";

    while (!(cin >> option) || option < 1 || option > 3) {
        cout << "Input tidak valid. Masukkan angka antara 1 dan 3" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return option;
}

int main() {
    Pengguna currentUser;
    TiketLinkedList tiketList;
    int percobaanLogin = 3;

    while (percobaanLogin > 0) {
        if (currentUser.username.empty()) {
            cout << "====================================" << endl;
            cout << "|              MENU :              |" << endl;
            cout << "====================================" << endl;
            cout << "| 1. Register                      |" << endl;
            cout << "| 2. Login                         |" << endl;
            cout << "| 3. Keluar                        |" << endl;
            cout << "====================================" << endl;

            int menu_utama = getMenuOption();
            cin.ignore(1000, '\n');

            switch (menu_utama) {
                case 1:
                    lakukanPendaftaran();
                    break;
                case 2:
                    currentUser = lakukanLogin();
                    if (currentUser.username.empty()) {
                        percobaanLogin--;
                        cout << "Sisa percobaan login: " << percobaanLogin << endl;
                        if (percobaanLogin == 0) {
                            cout << "Anda telah menggunakan semua percobaan login. Program berhenti." << endl;
                            exit(0);
                        }
                    } else if (currentUser.isAdmin) {
                        // Jika login sebagai admin, tampilkan menu admin
                        menuAdmin(currentUser, tiketList);
                        // Lakukan logika untuk menu admin
                        // Setelah selesai, logout admin
                        currentUser = Pengguna();
                    }
                    break;
                case 3:
                    cout << "Keluar dari program" << endl;
                    exit(0);
                default:
                    cout << "Pilihan tidak valid. Coba lagi" << endl;
            }
        } else {
            // Tampilkan menu setelah login (user atau admin)
            // ...
            currentUser = Pengguna();  // Mengosongkan data pengguna setelah keluar dari menu setelah login
        }
    }
    return 0;
}
