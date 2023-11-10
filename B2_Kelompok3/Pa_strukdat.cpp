#include <iostream>      // Digunakan untuk mengakses input dan output standar (misalnya std::cin dan std::cout).
#include <fstream>       // Digunakan untuk memanipulasi file, membaca dan menulis data ke dalam file.
#include <windows.h>     // Digunakan untuk mengakses fungsi-fungsi sistem operasi Windows
#include <string>        // Digunakan untuk mengakses kelas-kelas dan fungsi-fungsi yang berkaitan dengan manipulasi string.
#include <iomanip>       // Digunakan untuk mengakses manipulator-maniuplator I/O yang mempengaruhi format output.
#include <bits/stdc++.h> // Digunakan untuk mengakses semua pustaka standar C++

using namespace std;

// Username dan password Admin
string Admin[] = {"Muchlas", "Dea", "Lisa"};
string admin, user, username;
long long NIM[] = {82, 91, 89};
long long passAdmin, password, konfirmasiPass;

struct Petshop
{
    string nama, jenisKelamin;
    int umur;
    string ras;
    int harga, stok;
    int IdPetshop;

    Petshop *next = NULL;
};

struct User
{
    string username;
    long long password;
    User *next;
};

struct Customer
{
    Petshop data;
    User pelanggan;
    string nama;
    int jumlah;
    long long totalHarga;
    Customer *next;
};

Petshop *head = NULL; // head untuk data petshop
Customer *Front = NULL;
Customer *Rear = NULL;
User *Head = NULL; // Head untuk User
void dataToTxt(Petshop *head);
void txtToData(Petshop *&head);
void txtToUser(User *&head);
void nota(Petshop *head, Customer *front);
void tampil(Petshop *head);
void Order(Customer **Front, Customer **Rear, Petshop *&head);
void LihatAntrian(Customer *Front, Customer *Rear);
int signIn();

Petshop *newPetshop()
{
    Petshop *dataPetshop = new Petshop;

    cout << "Masukkan Nama Hewan    : ";
    fflush(stdin);
    getline(cin, dataPetshop->nama);
    cout << "Masukkan Jenis Kelamin : ";
    fflush(stdin);
    getline(cin, dataPetshop->jenisKelamin);
    cout << "Masukkan Umur Hewan    : ";
    while (!(cin >> dataPetshop->umur))
    {
        cout << "Input tidak valid, silahkan masukkan angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan Umur Hewan    : ";
    }
    cout << "Masukkan Ras Hewan     : ";
    fflush(stdin);
    getline(cin, dataPetshop->ras);
    cout << "Masukkan Harga Hewan   : ";
    while (!(cin >> dataPetshop->harga))
    {
        cout << "Input tidak valid, silahkan masukkan angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan Harga Hewan   : ";
    }
    cout << "Masukkan Stok Hewan    : ";
    while (!(cin >> dataPetshop->stok))
    {
        cout << "Input tidak valid, silahkan masukkan angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan Stok Hewan    : ";
    }
    cout << "Masukkan ID Petshop    : ";
    while (!(cin >> dataPetshop->IdPetshop))
    {
        cout << "Input tidak valid, silahkan masukkan angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan ID Petshop    : ";
    }
    return dataPetshop;
}

Customer *newCustomer(User *&Head)
{
    Customer *dataCustomer = new Customer();
    if (Head != NULL)
    {
        dataCustomer->pelanggan.username = Head->username;
        cout << "Hallo " << dataCustomer->pelanggan.username << endl;
        cout << "Masukkan Id Hewan Yang Ingin Anda Beli : ";
        while (!(cin >> dataCustomer->data.IdPetshop))
        {
            cout << "Input tidak valid, silahkan masukkan angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan Id Hewan Yang Ingin Anda Beli : ";
        }

        cout << "Masukkan Jumlah Yang Ingin Anda Beli : ";
        while (!(cin >> dataCustomer->jumlah))
        {
            cout << "Input tidak valid, silahkan masukkan angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan Jumlah Yang Ingin Anda Beli : ";
        }

        dataCustomer->totalHarga = 0;
    }
    else
    {
        cout << "Tidak ada pengguna yang login." << endl;
        // Atau Anda dapat melakukan tindakan lain sesuai dengan kebutuhan aplikasi Anda jika tidak ada pengguna yang login.
    }

    return dataCustomer;
}

void tampil(Petshop *head)
{
    Petshop *temp = head;
    int i = 0;
    if (head != NULL)
    {
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
        cout << "|";
        cout << " " << setw(4) << left << "N0"
             << " "
             << "|";
        cout << setw(6) << right << " "
             << "Nama Hewan" << setw(6) << left << " "
             << "|";
        cout << setw(2) << right << " "
             << "Jenis Kelamin" << setw(2) << left << " "
             << "|";
        cout << setw(1) << right << " "
             << "Umur (Tahun)" << setw(1) << left << " "
             << "|";
        cout << setw(3) << right << " "
             << "Ras Hewan" << setw(3) << left << " "
             << "|";
        cout << setw(4) << right << " "
             << "Harga" << setw(4) << left << " "
             << "|";
        cout << setw(1) << right << " "
             << "Stok" << setw(1) << left << " "
             << "|";
        cout << setw(1) << right << " "
             << "ID" << setw(1) << left << " "
             << "|" << endl;
        cout << "----------------------------------------------------------------------------------------------------------" << endl;
        while (temp != NULL)
        {
            cout << "|"
                 << " " << setw(4) << i + 1 << " "
                 << "|";
            cout << " " << setw(15) << temp->nama << setw(6) << left << " "
                 << "|";
            cout << " " << setw(10) << temp->jenisKelamin << setw(6) << left << " "
                 << "|";
            cout << " " << setw(4) << temp->umur << setw(9) << left << " "
                 << "|";
            cout << " " << setw(10) << temp->ras << setw(4) << left << " "
                 << "|";
            cout << " " << setw(10) << temp->harga << setw(2) << left << " "
                 << "|";
            cout << " " << setw(3) << temp->stok << setw(2) << left << " "
                 << "|";
            cout << " " << setw(2) << temp->IdPetshop << setw(1) << left << " "
                 << "|" << endl;
            cout << "----------------------------------------------------------------------------------------------------------" << endl;
            temp = temp->next;
            i++;
        }
    }
    else
    {
        cout << "Tidak Ada Data Petshop yang Tersedia" << endl;
    }
}

void txtToUser(User *&head)
{
    User *tail = NULL;
    string line, string_password;
    ifstream file("users.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream iss(line); // Fungsi untuk memproses string menjadi tipe data yang sesuai

            // Membuat simpul baru untuk setiap baris
            User *dataUser = new User;

            getline(iss >> ws, dataUser->username, ',');
            getline(iss >> ws, string_password, ',');
            stringstream(string_password) >> dataUser->password;

            dataUser->next = NULL;

            if (head == NULL)
            {
                // Jika ini adalah simpul pertama, atur kepala ke simpul pertama
                head = dataUser;
                tail = dataUser;
            }
            else
            {
                // Jika bukan simpul pertama, tambahkan ke akhir linked list
                tail->next = dataUser;
                tail = dataUser;
            }
        }
        file.close();
    }
}

void userToTxt(string &username, long long &password)
{ // Fungsi untuk melakukan pendaftaran user baru
    ofstream file("users.txt", ios_base::app);
    file << username << "," << password << endl;
}

void txtToData(Petshop *&head)
{
    Petshop *tail = NULL;
    string line, umur_string, bonus_string, harga_string, stok_string, idPetshop_string;
    ifstream file("dataPetshop.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream iss(line);

            // Membuat simpul baru untuk setiap baris
            Petshop *dataPetshop = new Petshop;

            getline(iss >> ws, dataPetshop->nama, ',');
            getline(iss >> ws, dataPetshop->jenisKelamin, ',');
            getline(iss >> ws, umur_string, ',');
            stringstream(umur_string) >> dataPetshop->umur;
            getline(iss >> ws, dataPetshop->ras, ',');
            getline(iss >> ws, harga_string, ',');
            stringstream(harga_string) >> dataPetshop->harga;
            getline(iss >> ws, stok_string, ',');
            stringstream(stok_string) >> dataPetshop->stok;
            getline(iss >> ws, idPetshop_string, ',');
            stringstream(idPetshop_string) >> dataPetshop->IdPetshop;

            dataPetshop->next = NULL;

            if (head == NULL)
            {
                // Jika ini adalah simpul pertama, atur kepala ke simpul pertama
                head = dataPetshop;
                tail = dataPetshop;
            }
            else
            {
                // Jika bukan simpul pertama, tambahkan ke akhir linked list
                tail->next = dataPetshop;
                tail = dataPetshop;
            }
        }
        file.close();
    }
}

void dataToTxt(Petshop *head)
{
    ofstream file("dataPetshop.txt");
    if (file.is_open())
    {
        Petshop *dataPetshop = head;
        while (dataPetshop != NULL)
        {
            file << dataPetshop->nama << ",";
            file << dataPetshop->jenisKelamin << ",";
            file << dataPetshop->umur << ",";
            file << dataPetshop->ras << ",";
            file << dataPetshop->harga << ",";
            file << dataPetshop->stok << ",";
            file << dataPetshop->IdPetshop << endl;

            dataPetshop = dataPetshop->next;
        }
        file.close();
    }
    else
    {
        cout << "Gagal membuka file untuk penulisan." << endl;
    }
}

void txtToPesanan(Customer *&Front, Customer *&Rear, User *&userHead, Petshop *&petshopHead)
{
    string line, string_umur, string_harga, string_jumlah, string_total;
    ifstream file("dataPesanan.txt");
    if (file.is_open())
    {
        while (getline(file, line))
        {
            istringstream iss(line);    

            // Membuat simpul baru untuk setiap baris
            Customer *dataCustomer = new Customer;
            // Mengambil Data Pesanan
            getline(iss >> ws, dataCustomer->pelanggan.username, ',');
            getline(iss >> ws, dataCustomer->data.nama, ',');
            getline(iss >> ws, dataCustomer->data.jenisKelamin, ',');
            getline(iss >> ws, string_umur, ',');
            stringstream(string_umur) >> dataCustomer->data.umur;
            getline(iss >> ws, dataCustomer->data.ras, ',');
            getline(iss >> ws, string_harga, ',');
            stringstream(string_harga) >> dataCustomer->data.harga;
            getline(iss >> ws, string_jumlah, ',');
            stringstream(string_jumlah) >> dataCustomer->jumlah;
            getline(iss >> ws, string_total, ',');
            stringstream(string_total) >> dataCustomer->totalHarga;

            // Mencari Petshop dengan nama yang sesuai
            Petshop *dataPetshop = petshopHead;
            while (dataPetshop != NULL)
            {
                if (dataPetshop->nama == dataCustomer->data.nama)
                {
                    dataCustomer->data.jenisKelamin = dataPetshop->jenisKelamin; // Menyalin data Petshop ke dataCustomer
                    dataCustomer->data.umur = dataPetshop->umur;
                    dataCustomer->data.ras = dataPetshop->ras;
                    dataCustomer->data.harga = dataPetshop->harga;
                    break;
                }
                dataPetshop = dataPetshop->next;
            }

            // Mencari User dengan username yang sesuai
            User *dataUser = userHead;
            while (dataUser != NULL)
            {
                if (dataUser->username == dataCustomer->pelanggan.username)
                {
                    dataCustomer->pelanggan.username = dataUser->username; // Menyimpan data User pada Customer
                    break;
                }
                dataUser = dataUser->next;
            }

            dataCustomer->next = NULL;

            if (Front == NULL || Rear == NULL)
            {
                // Jika ini adalah simpul pertama, atur Front dan Rear ke simpul pertama
                Front = dataCustomer;
                Rear = dataCustomer;
            }
            else
            {
                // Jika bukan simpul pertama, tambahkan ke akhir linked list
                Rear->next = dataCustomer;
                Rear = dataCustomer;
            }
        }
        file.close();
    }
}

void pesananToTxt(Customer *Front)
{
    ofstream file("dataPesanan.txt");
    if (file.is_open())
    {
        Customer *dataCustomer = Front;
        while (dataCustomer != NULL)
        {
            file << dataCustomer->pelanggan.username << ",";
            file << dataCustomer->data.nama << ",";
            file << dataCustomer->data.jenisKelamin << ",";
            file << dataCustomer->data.umur << ",";
            file << dataCustomer->data.ras << ",";
            file << dataCustomer->data.harga << ",";
            file << dataCustomer->jumlah << ",";
            file << dataCustomer->totalHarga << endl;

            dataCustomer = dataCustomer->next;
        }

        file.close();
    }
}


// Tambah Data Di Awal
void addFirst(Petshop **head)
{
    Petshop *dataPetshop = newPetshop();
    dataPetshop->next = *head;
    *head = dataPetshop;
}

// Tambah Data Di Akhir
void addLast(Petshop **head)
{
    if (*head == NULL)
    {
        addFirst(head);
    }
    else
    {
        Petshop *temp = *head;
        Petshop *dataPetshop = newPetshop();
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = dataPetshop;
    }
}

// Tambah Data Di Tengah
void addMiddle(Petshop **head, int index)
{
    if (*head == NULL)
    {
        addFirst(head);
    }
    else
    {
        Petshop *temp = *head;
        Petshop *dataPetshop = newPetshop();
        for (int i = 1; i < index; i++)
        {
            temp = temp->next;
        }
        dataPetshop->next = temp->next;
        temp->next = dataPetshop;
    }
}

// Update Data Biasa
void update(Petshop **head)
{
    if (*head == NULL)
    {
        cout << "Data Petshop Masih Kosong" << endl;
        return;
    }
    int ubah;
    cout << "Masukkan Id Petshop yang ingin di ubah : ";
    cin >> ubah;
    Petshop *temp = (*head);
    while (temp != NULL)
    {
        if (temp->IdPetshop == ubah)
        {
            cout << "Masukkan Nama Hewan Baru    : ";
            fflush(stdin);
            getline(cin, temp->nama);
            cout << "Masukkan Jenis Kelamin Baru : ";
            fflush(stdin);
            getline(cin, temp->jenisKelamin);
            cout << "Masukkan Umur Hewan Baru    : ";
            while (!(cin >> temp->umur))
            {
                cout << "Input tidak valid, silahkan masukkan angka!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Masukkan Umur Hewan Baru   : ";
            }
            cout << "Masukkan Ras Hewan Baru     : ";
            fflush(stdin);
            getline(cin, temp->ras);
            cout << "Masukkan Harga Hewan Baru   : ";
            while (!(cin >> temp->harga))
            {
                cout << "Input tidak valid, silahkan masukkan angka!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Masukkan Harga Hewan Baru  : ";
            }
            cout << "Masukkan Stok Hewan Baru    : ";
            while (!(cin >> temp->stok))
            {
                cout << "Input tidak valid, silahkan masukkan angka!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Masukkan Stok Hewan Baru   : ";
            }
            cout << "Masukkan ID Petshop Baru    : ";
            while (!(cin >> temp->IdPetshop))
            {
                cout << "Input tidak valid, silahkan masukkan angka!" << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Masukkan ID Petshop    : ";
            }
            cout << "Data Berhasil Di Ubah!!!" << endl;
            system("pause");
            return;
        }
        temp = temp->next;
    }
}

// Update Data Spesifik
void updateSpesifik(Petshop **head, int idToUpdate)
{
    Petshop *temp = *head;
    while (temp != NULL && temp->IdPetshop != idToUpdate)
    {
        temp = temp->next;
    }
    if (temp == NULL)
    {
        cout << "ID Tertentu tidak ditemukan. Data tidak diperbarui." << endl;
        return;
    }

    int pilihan;
    cout << "===================================" << endl;
    cout << "Pilih atribut yang ingin diperbarui:" << endl;
    cout << "===================================" << endl;
    cout << " ***>>     [1] Nama         <<***  " << endl;
    cout << " ***>>     [2] Jen_Kel      <<***  " << endl;
    cout << " ***>>     [3] Umur         <<***  " << endl;
    cout << " ***>>     [4] Ras          <<***  " << endl;
    cout << " ***>>     [5] Harga        <<***  " << endl;
    cout << " ***>>     [6] Stok         <<***  " << endl;
    cout << " ***>>     [7] Id           <<***  " << endl;
    cout << "===================================" << endl;
    cout << "Pilihan Anda: ";
    cin >> pilihan;

    cin.ignore();

    switch (pilihan)
    {
    case 1:
        cout << "Masukkan Nama Baru: ";
        getline(cin, temp->nama);
        break;
    case 2:
        cout << "Masukkan Jenis Kelamin Baru: ";
        getline(cin, temp->jenisKelamin);
        break;
    case 3:
        cout << "Masukkan Umur Baru: ";
        cin >> temp->umur;
        break;
    case 4:
        cout << "Masukkan Ras Baru: ";
        cin >> temp->ras;
        break;
    case 5:
        cout << "Masukkan Harga Baru: ";
        cin >> temp->harga;
        break;
    case 6:
        cout << "Masukkan Stok Baru: ";
        cin >> temp->stok;
        break;
    case 7:
        cout << "Masukkan Id Baru: ";
        cin >> temp->IdPetshop;
        break;
    default:
        cout << "Pilihan tidak valid. Data tidak diperbarui." << endl;
        return;
    }

    cout << "Atribut berhasil diperbarui." << endl;
}

// Hapus Data Di Awal
void deleteFirst(Petshop **head)
{
    Petshop *hapus = *head;
    *head = (*head)->next;
    delete hapus;
}

// Hapus Data Di Akhir
void deleteLast(Petshop **head)
{
    if ((*head)->next == NULL)
    {
        deleteFirst(head);
    }
    else
    {
        Petshop *temp = *head;
        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }
        Petshop *hapus = temp->next;
        temp->next = NULL;
        delete hapus;
    }
}

// Hapus Data DI Tengah
void deleteMiddle(Petshop *head, int index)
{
    Petshop *temp = head;
    for (int i = 1; i < index - 1; i++)
    {
        temp = temp->next;
    }
    Petshop *hapus = temp->next;
    temp->next = hapus->next;
    delete hapus;
}

// Fungsi ini digunakan untuk menghitung panjang (jumlah elemen) dari linked list.
int hitungPanjangData(Petshop *head)
{
    int hitung = 0;
    Petshop *dataPetshop = head;
    while (dataPetshop != NULL)
    {
        hitung++;
        dataPetshop = dataPetshop->next;
    }
    return hitung;
}

// Fungsi ini digunakan untuk mencari elemen dalam linked list berdasarkan indeks.
Petshop *cariPetshop(Petshop *head, int idx)
{
    Petshop *dataPetshop = head;
    for (int i = 0; i < idx; i++)
    {
        dataPetshop = dataPetshop->next;
    }
    return dataPetshop;
}

struct Petshop *getTail(struct Petshop *dataPetshop) // Fungsi ini digunakan untuk mendapatkan elemen terakhir dari linked list.
{
    while (dataPetshop != NULL && dataPetshop->next != NULL)
        dataPetshop = dataPetshop->next;
    return dataPetshop;
}

// Fungsi ini digunakan dalam algoritma Quick Sort untuk mempartisi linked list berdasarkan pivot.
Petshop *partisi(struct Petshop *head, struct Petshop *end, struct Petshop **newHead, struct Petshop **newEnd, bool ascending, int idPetshop)
{
    struct Petshop *pivot = end;
    struct Petshop *prev = NULL, *cur = head, *tail = pivot;

    while (cur != pivot)
    {
        if (idPetshop == 1)
        {
            if (ascending)
            {
                if (cur->IdPetshop < pivot->IdPetshop)
                {
                    if ((*newHead) == NULL)
                        (*newHead) = cur;
                    prev = cur;
                    cur = cur->next;
                }
                else
                {
                    if (prev)
                        prev->next = cur->next;
                    struct Petshop *tmp = cur->next;
                    cur->next = NULL;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
            else
            {
                if (cur->IdPetshop > pivot->IdPetshop)
                {
                    if ((*newHead) == NULL)
                        (*newHead) = cur;
                    prev = cur;
                    cur = cur->next;
                }
                else
                {
                    if (prev)
                        prev->next = cur->next;
                    struct Petshop *tmp = cur->next;
                    cur->next = NULL;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
        }
        else
        {
            if (ascending)
            {
                if (cur->umur < pivot->umur)
                {
                    if ((*newHead) == NULL)
                        (*newHead) = cur;
                    prev = cur;
                    cur = cur->next;
                }
                else
                {
                    if (prev)
                        prev->next = cur->next;
                    struct Petshop *tmp = cur->next;
                    cur->next = NULL;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
            else
            {
                if (cur->umur > pivot->umur)
                {
                    if ((*newHead) == NULL)
                        (*newHead) = cur;
                    prev = cur;
                    cur = cur->next;
                }
                else
                {
                    if (prev)
                        prev->next = cur->next;
                    struct Petshop *tmp = cur->next;
                    cur->next = NULL;
                    tail->next = cur;
                    tail = cur;
                    cur = tmp;
                }
            }
        }
    }
    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}

// Fungsi ini merupakan implementasi rekursif dari algoritma Quick Sort untuk mengurutkan linked list.
Petshop *quickSortRecursive(struct Petshop *head, struct Petshop *end, bool ascending, int jenis)
{
    if (!head || head == end)
        return head;
    Petshop *newHead = NULL, *newEnd = NULL;
    struct Petshop *pivot = partisi(head, end, &newHead, &newEnd, ascending, jenis);
    if (newHead != pivot)
    {
        struct Petshop *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortRecursive(newHead, tmp, ascending, jenis);
        tmp = getTail(newHead);
        tmp->next = pivot;
    }
    pivot->next = quickSortRecursive(pivot->next, newEnd, ascending, jenis);
    return newHead;
}

// Fungsi rekursif untuk mengurutkan linked list menggunakan algoritma Quick Sort
void quickSort(Petshop **low, bool ascending, int jenis)
{
    (*low) = quickSortRecursive(*low, getTail(*low), ascending, jenis);
    return;
}

// Fungsi ini merupakan implementasi dari algoritma Jump Search yang digunakan untuk mencari elemen dengan nilai umur tertentu dalam linked list.
int jumpSearch(Petshop *head, int x, int n)
{
    int step = sqrt(n); // jarak lompatannyan
    int prev = 0;       // indesk ke 0 data pertamanya

    int idx = min(step, n) - 1;              // rumus jump search
    while (cariPetshop(head, idx)->umur < x) // untuk mencari Petshop baru diambuil nilai nimnya lalu dibandingkan sama si x
    {
        prev = step;
        step += sqrt(n);
        idx = min(step, n) - 1;
        if (prev >= n) // maka tdk ada data yg dicari
        {
            return -1;
        }
    }
    while (cariPetshop(head, prev)->umur < x) // perulangan secara linear
    {
        prev++;
    }
    cout << endl;
    if (cariPetshop(head, prev)->umur == x)
    {
        return prev;
    }
    return -1;
}

const int NUMBER_CHAR = 256;

// Fungsi ini digunakan untuk mengisi heuristik tabel karakter buruk (badChar) berdasarkan pola yang dicari.
void badCharHeuristic(string str, int size, int badChar[NUMBER_CHAR])
{
    // Inisialisasi semua nilai di badChar sebagai -1
    for (int i = 0; i < NUMBER_CHAR; i++)
    {
        badChar[i] = -1;
    }
    // Isi nilai aktual dari badChar untuk karakter yang ada
    for (int i = 0; i < size; i++)
    {
        badChar[(int)str[i]] = i;
    }
}

// Fungsi ini merupakan implementasi dari algoritma pencarian string Boyer-Moore untuk mencari pola dalam linked list yang berisi data hewan peliharaan.
void boyermoore(Petshop *head, string pat)
{
    int m = pat.size();
    Petshop *temp = head;
    int count = 0;
    while (temp != NULL)
    {
        int n = temp->nama.size();
        int badChar[NUMBER_CHAR];
        badCharHeuristic(pat, m, badChar);
        int s = 0; // s adalah shift dari pola sehubungan

        while (s <= (n - m))
        {
            int j = m - 1;
            // Kurangi indeks j dari pola sampai karakter dari

            while (j >= 0 && pat[j] == temp->nama[s + j])
            {
                j--;
            }
            if (j < 0)
            {
                cout << "Nama Hewan    : " << temp->nama << endl;
                cout << "Jenis Kelamin : " << temp->jenisKelamin << endl;
                cout << "Umur Hewan    : " << temp->umur << endl;
                cout << "Ras Hewan     : " << temp->ras << endl;
                cout << "Harga Hewan   : " << temp->harga << endl;
                cout << "Stok Hewan    : " << temp->stok << endl;
                cout << "ID Petshop    : " << temp->IdPetshop << endl;
                count++;
                break;
            }
            else
            {
                // Geser pola sehingga karakter yang tidak
                s += max(1, j - badChar[temp->nama[s + j]]);
            }
        }
        temp = temp->next;
    }
    if (count == 0)
    {
        cout << "data tidak ditemukan" << endl;
    }
}

// Sorting Berdasarkan ID
int sortingIdPetshop(Petshop *head)
{
    int pilihan;
    string input;
    hitungPanjangData(head);
    while (pilihan != 3)
    {
        system("cls");
        system("color 09");
        cout << "===========================" << endl;
        cout << "||   SORTING ID PETSHOP  ||" << endl;
        cout << "===========================" << endl;
        cout << "||    1. ASCENDING       ||" << endl;
        cout << "||    2. DESCENDING      ||" << endl;
        cout << "||    3. KEMBALI         ||" << endl;
        cout << "===========================" << endl;
        cout << "Pilihan Anda: ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            quickSort(&head, true, 1);
            dataToTxt(head);
            tampil(head);
            cout << "Data Petshop telah diurutkan secara Ascending berdasarkan ID Petshop." << endl;
            system("pause");
            break;
        case 2:
            quickSort(&head, false, 1);
            dataToTxt(head);
            tampil(head);
            cout << "Data Petshop telah diurutkan secara Descending berdasarkan ID Petshop." << endl;
            system("pause");
            break;
        case 3:
            cout << "Kembali ke Menu Utama" << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

// Sorting Berdasarkan Umur
int sortingUmur(Petshop *head)
{
    int pilihan;
    string input;
    hitungPanjangData(head);
    while (pilihan != 3)
    {
        system("cls");
        system("color 09");
        cout << "===========================" << endl;
        cout << "||   SORTING UMUR HEWAN  ||" << endl;
        cout << "===========================" << endl;
        cout << "||    1. ASCENDING       ||" << endl;
        cout << "||    2. DESCENDING      ||" << endl;
        cout << "||    3. KEMBALI         ||" << endl;
        cout << "===========================" << endl;
        cout << "Pilihan Anda: ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            quickSort(&head, true, 2);
            dataToTxt(head);
            tampil(head);
            cout << "Data Petshop telah diurutkan secara Ascending berdasarkan Umur Hewan." << endl;
            system("pause");
            break;
        case 2:
            quickSort(&head, false, 2);
            dataToTxt(head);
            tampil(head);
            cout << "Data Petshop telah diurutkan secara Descending berdasarkan Umur Hewan." << endl;
            system("pause");
            break;
        case 3:
            cout << "Kembali ke Menu Utama" << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

int hitungJumlahPesanan(Customer *Front)
{
    int jumlahPesanan = 0;
    Customer *dataCustomer = Front;
    while (dataCustomer != NULL)
    {
        jumlahPesanan++;
        dataCustomer = dataCustomer->next;
    }
    return jumlahPesanan;
}

// Fungsi User Membuat Pesanan
void Order(Customer **Front, Customer **Rear, Petshop *&head)
{
    tampil(head);
    Customer *dataCustomer = newCustomer(Head);
    Petshop *dataPetshop = head;
    while (dataPetshop != NULL)
    {
        if (dataPetshop->IdPetshop == dataCustomer->data.IdPetshop)
        {
            if (dataPetshop->stok >= dataCustomer->jumlah)
            {
                // Hewan ditemukan dan jumlah yang dibeli masih tersedia dalam stok
                dataCustomer->data.nama = dataPetshop->nama;
                dataCustomer->data.jenisKelamin = dataPetshop->jenisKelamin;
                dataCustomer->data.umur = dataPetshop->umur;
                dataCustomer->data.ras = dataPetshop->ras;
                dataCustomer->data.harga = dataPetshop->harga;
                dataPetshop->stok -= dataCustomer->jumlah;
                dataCustomer->totalHarga = dataPetshop->harga * dataCustomer->jumlah;
                if (*Front == NULL || *Rear == NULL) // enqueue
                {
                    *Front = dataCustomer;
                    *Rear = dataCustomer;
                }
                else
                {
                    (*Rear)->next = dataCustomer;
                    *Rear = dataCustomer;
                }
                cout << "Pesanan Diterima. Stok Tersisa : " << dataPetshop->stok << endl;
                system("pause");
            }
            else if (dataPetshop->stok > 0)
            {
                cout << "Stok hewan " << dataPetshop->nama << " tidak cukup untuk memenuhi permintaan. Stok tersisa: " << dataPetshop->stok << endl;
                system("pause");
            }
            else
            {
                cout << "Stok hewan " << dataPetshop->nama << " telah habis." << endl;
                system("pause");
            }
            return;
        }
        dataPetshop = dataPetshop->next;
    }

    // Jika hewan tidak ditemukan berdasarkan ID
    cout << "Hewan dengan ID " << dataCustomer->data.IdPetshop << " tidak ditemukan dalam stok." << endl;
    system("pause");
}

// Mengkonfirmasi Pesanan
void TakeOrder(Customer **Front, Customer **Rear, Petshop *head)
{
    if (*Front == NULL)
    {
        cout << "Tidak Ada Orderan" << endl;
        return;
    }
    Customer *temp = *Front;
    *Front = (*Front)->next;
    // nota(head, temp);
    delete temp;
}

// menampilkan Nota Pesanan
void nota(Petshop *head, Customer *front)
{
    Customer *dataCustomer = front;
    if (dataCustomer == NULL)
    {
        cout << "Data pelanggan kosong." << endl;
        system("pause");
        return;
    }
    Petshop *dataPetshop = head;
    cout << "----------------------------------" << endl;
    cout << "|        LIMUDE'S PETSHOP        |" << endl;
    cout << "----------------------------------" << endl;
    cout << "| Nama Pembeli  : " << setw(14) << left << dataCustomer->pelanggan.username << " "
         << "|" << endl;
    cout << "| Nama Hewan    : " << setw(14) << left << dataCustomer->data.nama << " "
         << "|" << endl;
    cout << "| Jenis Kelamin : " << setw(14) << left << dataCustomer->data.jenisKelamin << " "
         << "|" << endl;
    cout << "| Umur Hewan    : " << setw(2) << left << dataCustomer->data.umur << " (Tahun)" << setw(5) << left << " "
         << "|" << endl;
    cout << "| Ras Hewan     : " << setw(14) << left << dataCustomer->data.ras << " "
         << "|" << endl;
    cout << "| Harga         : " << setw(14) << left << dataCustomer->data.harga << " "
         << "|" << endl;
    cout << "| Jumlah Beli   : " << setw(14) << left << dataCustomer->jumlah << " "
         << "|" << endl;
    cout << "| Total Harga   : " << setw(14) << left << dataCustomer->totalHarga << " "
         << "|" << endl;
    cout << "----------------------------------" << endl;
}

void LihatAntrian(Customer *Front, Customer *Rear)
{
    Customer *dataCustomer = Front;
    int i = 1;
    if (dataCustomer == NULL)
    {
        cout << "Tidak Ada Antrian" << endl;
        return;
    }
    cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "|";
    cout << " " << setw(4) << left << "N0"
         << " "
         << "|";
    cout << setw(5) << right << " "
         << "Nama Pembeli" << setw(5) << left << " "
         << "|";
    cout << setw(4) << right << " "
         << "Nama Hewan" << setw(4) << left << " "
         << "|";
    cout << setw(2) << right << " "
         << "Jenis Kelamin" << setw(2) << left << " "
         << "|";
    cout << setw(1) << right << " "
         << "Umur (Tahun)" << setw(1) << left << " "
         << "|";
    cout << setw(3) << right << " "
         << "Ras Hewan" << setw(3) << left << " "
         << "|";
    cout << setw(4) << right << " "
         << "Harga" << setw(4) << left << " "
         << "|";
    cout << setw(1) << right << " "
         << "Jumlah" << setw(1) << left << " "
         << "|";
    cout << setw(1) << right << " "
         << "Total Harga" << setw(1) << left << " "
         << "|" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
    while (dataCustomer != NULL)
    {
        cout << "|"
             << " " << setw(4) << i << " "
             << "|";
        cout << " " << setw(15) << dataCustomer->pelanggan.username << setw(6) << left << " "
             << "|";
        cout << " " << setw(11) << dataCustomer->data.nama << setw(6) << left << " "
             << "|";
        cout << " " << setw(10) << dataCustomer->data.jenisKelamin << setw(6) << left << " "
             << "|";
        cout << " " << setw(4) << dataCustomer->data.umur << setw(9) << left << " "
             << "|";
        cout << " " << setw(10) << dataCustomer->data.ras << setw(4) << left << " "
             << "|";
        cout << " " << setw(10) << dataCustomer->data.harga << setw(2) << left << " "
             << "|";
        cout << " " << setw(3) << dataCustomer->jumlah << setw(4) << left << " "
             << "|";
        cout << " " << setw(10) << dataCustomer->totalHarga << setw(2) << left << " "
             << "|" << endl;
        cout << "----------------------------------------------------------------------------------------------------------------------------------------" << endl;
        dataCustomer = dataCustomer->next;
        i++;
    }
}

int sorting(Petshop *head)
{
    int pilihan;
    string input;
    hitungPanjangData(head);
    while (pilihan != 3)
    {
        system("cls");
        system("color 09");
        cout << "========================" << endl;
        cout << "||    MENU SORTING    ||" << endl;
        cout << "========================" << endl;
        cout << "||   1. ID PETSHOP    ||" << endl;
        cout << "||   2. UMUR HEWAN    ||" << endl;
        cout << "||   3. KEMBALI       ||" << endl;
        cout << "========================" << endl;
        cout << "Pilihan Anda: ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            sortingIdPetshop(head);
            system("pause");
            break;
        case 2:
            sortingUmur(head);
            system("pause");
            break;
        case 3:
            cout << "Kembali ke Menu Utama" << endl;
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

void searchJump(Petshop *head)
{
    int cari;
    hitungPanjangData(head);
    system("cls");
    system("color 09");
    tampil(head);
    cout << "====================" << endl;
    cout << "||   JUMP SEARCH  ||" << endl;
    cout << "====================" << endl;
    cout << "||  Keterangan :  ||" << endl;
    cout << "||  Umur Hewan    ||" << endl;
    cout << "====================" << endl;
    cout << "Masukkan Umur Hewan Yang Ingin Di Cari : ";
    while (!(cin >> cari))
    {
        cout << "Input tidak valid, silahkan masukkan angka!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Masukkan Umur Hewan Yang Ingin Di Cari : ";
    }
    quickSort(&head, true, 2);
    dataToTxt(head);
    int idx = jumpSearch(head, cari, hitungPanjangData(head));
    if (idx == -1)
    {
        cout << "Data Tidak Ditemukan" << endl;
    }
    else
    {
        cout << "Nama Hewan    : " << cariPetshop(head, idx)->nama << endl;
        cout << "Jenis Kelamin : " << cariPetshop(head, idx)->jenisKelamin << endl;
        cout << "Umur Hewan    : " << cariPetshop(head, idx)->umur << endl;
        cout << "Ras Hewan     : " << cariPetshop(head, idx)->ras << endl;
        cout << "Harga Hewan   : " << cariPetshop(head, idx)->harga << endl;
        cout << "Stok Hewan    : " << cariPetshop(head, idx)->stok << endl;
        cout << "ID Petshop    : " << cariPetshop(head, idx)->IdPetshop << endl;
    }
}

void searchBoyerMoore(Petshop *head)
{
    string cari;
    hitungPanjangData(head);
    system("cls");
    system("color 09");
    tampil(head);
    cout << "====================" << endl;
    cout << "||   BOYER MOORE  ||" << endl;
    cout << "====================" << endl;
    cout << "||  Keterangan :  ||" << endl;
    cout << "||  Nama Hewan    ||" << endl;
    cout << "====================" << endl;
    cout << "Masukkan Nama Hewan Yang Ingin Di Cari : ";
    fflush(stdin);
    getline(cin, cari);
    boyermoore(head, cari);
}

int searching(Petshop *head)
{
    int pilihan;
    string input;
    hitungPanjangData(head);
    while (pilihan != 3)
    {
        system("cls");
        system("color 09");
        cout << "=======================" << endl;
        cout << "||   MENU SEARCHING  ||" << endl;
        cout << "=======================" << endl;
        cout << "||  1. JUMP SEARCH   ||" << endl;
        cout << "||  2. BOYER MOORE   ||" << endl;
        cout << "||  3. KEMBALI       ||" << endl;
        cout << "=======================" << endl;
        cout << "Pilihan Anda: ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            searchJump(head);
            system("pause");
            break;
        case 2:
            searchBoyerMoore(head);
            system("pause");
            break;
        case 3:
            cout << "Kembali ke Menu Utama" << endl;
            system("pause");
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

int menuAdmin()
{
    int pilihan;
    char masuk = 'n';
    string input;
    int index;
    while (pilihan != 8)
    {
        system("cls");
        system("color 09");
        cout << "===========================================" << endl;
        cout << "||           LIMUDE'S PETSHOP            ||" << endl;
        cout << "===========================================" << endl;
        cout << "===========================================" << endl;
        cout << "|| ***>>      [1] Add  Data              ||" << endl;
        cout << "|| ***>>      [2] Display                ||" << endl;
        cout << "|| ***>>      [3] Update                 ||" << endl;
        cout << "|| ***>>      [4] Delete                 ||" << endl;
        cout << "|| ***>>      [5] Sorting                ||" << endl;
        cout << "|| ***>>      [6] Searching              ||" << endl;
        cout << "|| ***>>      [7] Read Queue             ||" << endl;
        cout << "|| ***>>      [8]. Exit                  ||" << endl;
        cout << "===========================================" << endl;
        cout << "Pilihan Anda: ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 8." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 8)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2, 3, 4, 5, 6, 7 atau 8" << endl;
            continue;
        }

        switch (pilihan)
        {
        case 1:
            cout << "===============================" << endl;
            cout << "||        Tambah Data        ||" << endl;
            cout << "===============================" << endl;
            cout << "|[1] Add First                |" << endl;
            cout << "|[2] Add Middle               |" << endl;
            cout << "|[3] Add Last                 |" << endl;
            cout << "===============================" << endl;
            cout << "Pilihan Anda: ";
            cin >> index;
            switch (index)
            {
            case 1:
                addFirst(&head);
                break;
            case 2:
                tampil(head);
                cout << "Tambahkan data setelah nomor : ";
                cin >> index;
                addMiddle(&head, index);
                break;
            case 3:
                addLast(&head);
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
            dataToTxt(head);
            system("pause");
            break;
        case 2:
            tampil(head);
            system("pause");
            break;
        case 3:
            tampil(head);
            cout << "===============================" << endl;
            cout << "||         Ubah Data         ||" << endl;
            cout << "===============================" << endl;
            cout << "|[1] Update Semua Data        |" << endl;
            cout << "|[2] Update Spesifik          |" << endl;
            cout << "===============================" << endl;
            cout << "Pilihan Anda: ";
            cin >> index;
            switch (index)
            {
            case 1:
                update(&head);
                break;
            case 2:
                int idToUpdate;
                cout << "Masukkan Id yang ingin di Update : ";
                cin >> idToUpdate;
                updateSpesifik(&head, idToUpdate);
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
            dataToTxt(head);
            break;
        case 4:
            tampil(head);
            cout << "===============================" << endl;
            cout << "||         Hapus Data         ||" << endl;
            cout << "===============================" << endl;
            cout << "===============================" << endl;
            cout << "|[1] Delete First              |" << endl;
            cout << "|[2] Delete Middle             |" << endl;
            cout << "|[3] Delete Last               |" << endl;
            cout << "================================" << endl;
            cout << "Pilihan Anda: ";
            cin >> index;
            switch (index)
            {
            case 1:
                deleteFirst(&head);
                break;
            case 2:
                cout << "Hapus data nomor : ";
                cin >> index;
                deleteMiddle(head, index);
                break;
            case 3:
                deleteLast(&head);
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
            }
            dataToTxt(head);
            break;
        case 5:
            sorting(head);
            break;
        case 6:
            searching(head);
            dataToTxt(head);
            break;
        case 7:
            cout << "================================" << endl;
            cout << "||    Konfirmasi Pemesanan    ||" << endl;
            cout << "================================" << endl;
            cout << "|  Jumlah Pesanan Saat Ini :   |" << endl;
            cout << "|      Lihat Pesanan  [" << hitungJumlahPesanan(Front) << "]      |" << endl;
            cout << "================================" << endl;
            cout << "Ingin Melihat ? (Y/N): ";
            cin >> masuk;
            if (masuk == 'y' || masuk == 'Y')
            {
                LihatAntrian(Front, Rear);
                system("pause");
                cout << "Lakukan Konfirmasi Antrian Pertama ? (Y/N): ";
                cin >> masuk;
                if (masuk == 'y' || masuk == 'Y')
                {
                    TakeOrder(&Front, &Rear, head);
                    pesananToTxt(Front);
                    LihatAntrian(Front, Rear);
                    system("pause");
                }
            }
            break;
        case 8:
            cout << "Kembali ke Menu Utama" << endl;
            return 1;
            system("pause");
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

// Fungsi untuk menampilkan menu user
int menuUser()
{
    // txtToPesanan(Front, Rear);
    int pilihan;
    string input;
    while (pilihan != 3){
        system("cls");
        system("color 09");
        cout << "===============================" << endl;
        cout << "||         MENU USER         ||" << endl;
        cout << "===============================" << endl;
        cout << "===============================" << endl;
        cout << "||      1. Lihat Data        ||" << endl;
        cout << "||      2. Pesan             ||" << endl;
        cout << "||      3. Logout            ||" << endl;
        cout << "===============================" << endl;
        cout << "Pilihan Anda : ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            tampil(head);
            system("pause");
            break;
        case 2:
            Order(&Front, &Rear, head);
            nota(head, Front);
            dataToTxt(head);
            pesananToTxt(Front);
            system("pause");
            break;
        case 3:
            cout << "Kembali ke Menu Utama" << endl;
            return 1;
            system("pause");
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    return 0;
}

int signUp(User *&head)
{
    bool valid = false;
    // Meminta input username dari user, mengecek apakah username sudah terdaftar
    do
    {
        system("cls");
        cout << "=============" << endl;
        cout << ">> SIGN UP <<" << endl;
        cout << "=============" << endl;
        cout << "Masukkan Username : ";
        fflush(stdin);
        getline(cin, username);
        // Mengecek apakah username sudah terdaftar
        User *dataUser = head;
        while (dataUser != NULL)
        {
            if (dataUser->username == username)
            {
                cout << "Username sudah terdaftar. Silahkan masukkan username lain." << endl;
                break;
            }
            dataUser = dataUser->next;
        }
        if (dataUser == NULL)
        {
            valid = true;
        }
    } while (!valid);

    // Meminta input password dari user dan konfirmasi password
    do
    {
        cout << "Masukkan Password : ";
        while (!(cin >> password && password > 0))
        {
            cout << "Input tidak valid, silahkan masukkan angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan Password : ";
        }
        cout << "Konfirmasi Password : ";
        while (!(cin >> konfirmasiPass && konfirmasiPass > 0))
        {
            cout << "Input tidak valid, silahkan masukkan angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Konfirmasi Password : ";
        }
        if (password != konfirmasiPass)
        {
            cout << "Password tidak cocok. Silahkan masukkan password yang sama pada kedua kolom." << endl;
        }
        else
        {
            valid = true;
        }
    } while (!valid);

    // Mendaftarkan user baru
    userToTxt(username, password);
    cout << "Pendaftaran berhasil. Silahkan login dengan username dan password anda." << endl;

    return 0;
}

int loginAdmin()
{
    int kesempatan = 3;
    int login; // tempat menyimpan nilai kembalian jika user login atau logout
    while (kesempatan != 0)
    {
        system("cls");
        cout << "===========" << endl;
        cout << ">> ADMIN <<" << endl;
        cout << "===========" << endl;
        cout << "Masukkan Username : ";
        fflush(stdin);
        getline(cin, admin);
        cout << "Masukkan Password : ";
        while (!(cin >> passAdmin && passAdmin > 0))
        {
            cout << "Input tidak valid, silahkan masukkan angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan Password : ";
        }
        int i = 0;
        bool found = false;
        while (i < 3 && !found)
        {
            if ((Admin[i] == admin) && (NIM[i] == passAdmin))
            {
                cout << "Anda Berhasil Login" << endl;
                found = true;
                cout << "Selamat datang, " << admin << "!" << endl;
                system("pause");
                login = menuAdmin();
            }
            i++;
        }
        if (login == 1)
        {
            kesempatan = 0;
        }
        
        if (!found)
        {
            cout << "Username atau Password yang anda masukkan salah" << endl;
            kesempatan--;
        }
    }
    return 0;
}

int loginUser(User *&head)
{
    txtToUser(head);
    int kesempatan = 3;
    bool found = false;
    while (kesempatan != 0 && !found)
    {
        system("cls");
        cout << "===========" << endl;
        cout << ">> User <<" << endl;
        cout << "===========" << endl;
        cout << "Masukkan Username : ";
        fflush(stdin);
        getline(cin, username);
        cout << "Masukkan Password : ";
        while (!(cin >> password && password > 0))
        {
            cout << "Input tidak valid, silahkan masukkan angka!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Masukkan Password : ";
        }

        User *dataUser = head;
        while (dataUser != NULL && !found)
        {
            if (dataUser->username == username && dataUser->password == password)
            {
                found = true;
            }
            dataUser = dataUser->next;
        }

        if (found)
        {
            cout << "Anda Berhasil Login" << endl;
            cout << "Selamat datang, " << username << "!" << endl;
            system("pause");
            int resultLogin = menuUser();
            if (resultLogin == 0)
            {
                return 0;
            }
            
        }
        else
        {
            cout << "Username atau Password yang anda masukkan salah" << endl;
            kesempatan--;
            system("pause");
        }
    }
    system("pause");
    return 0;
}

int signIn()
{
    int pilihan;
    string input;
    while (pilihan != 3)
    {
        system("cls");
        cout << "=================================" << endl;
        cout << ">>>>>>>>> LOGIN SEBAGAI <<<<<<<<<" << endl;
        cout << "=================================" << endl;
        cout << "=================================" << endl;
        cout << "||          1. ADMIN           ||" << endl;
        cout << "||          2. USER            ||" << endl;
        cout << "||          3. KEMBALI         ||" << endl;
        cout << "=================================" << endl;
        cout << "Pilihan : ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            loginAdmin();
            break;
        case 2:
            loginUser(Head);
            break;
        case 3:
            return 0;
        default:
            break;
        }
    }
    return 0;
}

int main()
{
    txtToData(head);
    txtToPesanan(Front, Rear, Head, head);
    int pilihan;
    string input;

    while (pilihan != 3)
    {
        system("cls");
        cout << "=================================================" << endl;
        cout << "||      SELAMAT DATANG DI LIMUDE'S PETSHOP     ||" << endl;
        cout << "=================================================" << endl;
        cout << "=================================================" << endl;
        cout << "||          1. REGISTER (SIGN UP)              ||" << endl;
        cout << "||          2. LOGIN    (SIGN IN)              ||" << endl;
        cout << "||          3. KELUAR   (EXIT)                 ||" << endl;
        cout << "=================================================" << endl;
        cout << "Pilihan : ";
        fflush(stdin);
        getline(cin, input);
        stringstream ss(input);
        if (!(ss >> pilihan))
        {
            cout << "Input tidak valid. Masukkan angka dari 1 hingga 3." << endl;
            continue;
        }
        if (pilihan < 1 || pilihan > 3)
        {
            cout << "Pilihan Tidak Ada, Silahkan Masukkan Pilihan 1, 2 atau 3" << endl;
            continue;
        }
        switch (pilihan)
        {
        case 1:
            signUp(Head);
            break;
        case 2:
            signIn();
            break;
        case 3:
            cout << "=================================================" << endl;
            cout << "||        TERIMA KASIH TELAH BERKUNJUNG        ||" << endl;
            cout << "=================================================" << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}