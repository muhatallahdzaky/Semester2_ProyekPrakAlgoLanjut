#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
using namespace std;

const int MAKS_NASABAH = 10000;
const string FILE_NASABAH = "all_data_nasabah_bank_jawa.txt";
const string PROVINSI_JAWA[6] = {"DKI Jakarta", "Jawa Barat", "Jawa Tengah", "Jawa Timur", "Banten", "DI Yogyakarta"};

struct Nasabah
{
    string norek;
    string nama;
    string jeniskelamin;
    string provinsi;
    double penghasilan;
    double saldo;
};

void menu();
void inputDataNasabah();
void simpanDataNasabah(const Nasabah array[], int n, const string &filenasabah, bool ketemu = true);
int loadDataNasabah(Nasabah array[], const string &filenasabah);
void lihatDataNasabah();
void sortingDataNasabah();
void searchingDataNasabah();
void updateDataNasabah();
void hapusDataNasabah();
void filterDataNasabah();
void eksporPerProvinsi(const Nasabah array[], int n);
void eksporPerJenisKelamin(const Nasabah array[], int n);
void eksporLaporanRapi(const Nasabah array[], int n);
void swap(Nasabah *a, Nasabah *b);
void bubbleSort(Nasabah array[], int n, int field, bool ascending);
int rekursifCariNama(const Nasabah array[], int n, const string &keyword, int idx, int hasil[]);
int rekursifCariProvinsi(const Nasabah array[], int n, const string &prov, int idx, int hasil[]);

int main()
{
    menu();
    return 0;
}

void menu()
{
    int pilih;
    do
    {
        system("cls");
        cout << "===================================================================================================================\n";
        cout << "                                       SELAMAT DATANG DI APLIKASI BANK JAWA\n";
        cout << "                                               ~Jawa adalah Koentji~\n";
        cout << "===================================================================================================================\n";
        cout << "[1] Input Data Nasabah\n";
        cout << "[2] Lihat Seluruh Data Nasabah\n";
        cout << "[3] Sorting Data Nasabah\n";
        cout << "[4] Searching Data Nasabah\n";
        cout << "[5] Filter dan Ekspor Data Nasabah\n";
        cout << "[6] Update Data Nasabah\n";
        cout << "[7] Hapus Data Nasabah\n";
        cout << "[8] Keluar\n";
        cout << "-------------------------------------------------------------------------------------------------------------------\n";
        cout << "Silakan pilih menu yang ingin Anda pilih. Masukan pilihan : ";
        cin >> pilih;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid! Masukkan angka sesuai menu.\n";
            system("pause");
            pilih = 0;
            continue;
        }
        cin.ignore();

        switch (pilih)
        {
        case 1:
            inputDataNasabah();
            break;
        case 2:
            lihatDataNasabah();
            break;
        case 3:
            sortingDataNasabah();
            break;
        case 4:
            searchingDataNasabah();
            break;
        case 5:
            filterDataNasabah();
            break;
        case 6:
            updateDataNasabah();
            break;
        case 7:
            hapusDataNasabah();
            break;
        case 8:
            system("cls");
            cout << "===================================================================================================================\n";
            cout << "                                                 APLIKASI BANK JAWA\n";
            cout << "                                               ~Jawa adalah Koentji~\n";
            cout << "===================================================================================================================\n";
            cout << "                               Terimakasih telah menggunakan program ini. Program keluar~\n";
            cout << "===================================================================================================================\n";
            system("pause");
            break;
        default:
            cout << "Pilihan tidak valid! Silahkan pilih menu yang tersedia.\n";
            system("pause");
        }
    } while (pilih != 8);
}

void inputDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    int tambah = 0;
    cout << "===================================================================================================================\n";
    cout << "                                             MENU INPUT DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Masukkan jumlah data nasabah yang ingin ditambahkan: ";
    cin >> tambah;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid! Masukkan angka.\n";
        system("pause");
        return;
    }
    cin.ignore();
    if (tambah < 1 || tambah > MAKS_NASABAH)
    {
        cout << "Jumlah tidak valid!\n";
        system("pause");
        return;
    }
    for (int i = 0; i < tambah; ++i)
    {
        cout << endl;
        cout << endl;
        string norekbaru;
        bool duplikat;
        do
        {
            cout << "===================================================================================================================\n";
            cout << "                                           INPUT DATA NASABAH KE-" << (i + 1) << "\n";
            cout << "===================================================================================================================\n";
            duplikat = false;
            cout << "Nomor Rekening                 : ";
            getline(cin, norekbaru);
            if (norekbaru.empty())
            {
                cout << "Nomor rekening tidak boleh kosong!\n";
                duplikat = true;
                continue;
            }
            bool norekSudahAda = false;
            for (int j = 0; j < n; ++j)
            {
                if (array[j].norek == norekbaru)
                {
                    cout << endl;
                    cout << "ERROR! Nomor rekening sudah ada! Silakan masukkan nomor rekening yang berbeda.\n";
                    cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
                    char kembali;
                    cin >> kembali;
                    cin.ignore();
                    if (kembali == 'y' || kembali == 'Y')
                    {
                        return;
                    }
                    cout << "Baik, silahkan lanjutkan input data nasabah.\n";
                    system("pause");
                    system("cls");
                    cout << endl;
                    duplikat = true;
                    norekSudahAda = true;
                    break;
                }
            }
            if (norekSudahAda)
                continue;
            for (int j = n; j < n + i; ++j)
            {
                if (array[j].norek == norekbaru)
                {
                    cout << endl;
                    cout << "ERROR! Nomor rekening sudah diinput pada sesi ini! Silakan masukkan nomor rekening yang berbeda.\n";
                    cout << "Apakah Anda ingin kembali ke menu utama? (y/n): ";
                    char kembali;
                    cin >> kembali;
                    cin.ignore();
                    if (kembali == 'y' || kembali == 'Y')
                    {
                        return;
                    }
                    system("pause");
                    system("cls");
                    duplikat = true;
                    break;
                }
            }
        } while (duplikat);
        array[n + i].norek = norekbaru;

        cout << "Nama Nasabah                   : ";
        getline(cin, array[n + i].nama);

        while (true)
        {
            cout << "Jenis Kelamin (L/P)            : ";
            getline(cin, array[n + i].jeniskelamin);
            if (array[n + i].jeniskelamin == "L" || array[n + i].jeniskelamin == "l")
            {
                array[n + i].jeniskelamin = "Laki-laki";
                break;
            }
            else if (array[n + i].jeniskelamin == "P" || array[n + i].jeniskelamin == "p")
            {
                array[n + i].jeniskelamin = "Perempuan";
                break;
            }
            else
            {
                cout << "Input tidak valid! Masukkan 'L/l' untuk Laki-laki atau 'P/p' untuk Perempuan.\n";
            }
        }
        cout << endl;
        cout << "Pilih Provinsi Domisili:\n";
        for (int j = 0; j < 6; ++j)
        {
            cout << "[" << (j + 1) << "] " << PROVINSI_JAWA[j] << endl;
        }
        cout << "Pilih nomor provinsi (1-6)     : ";
        int provinsiIndex;
        while (true)
        {
            cin >> provinsiIndex;
            if (cin.fail() || provinsiIndex < 1 || provinsiIndex > 6)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Pilihan tidak valid! Masukkan angka 1-6.\n";
            }
            else
            {
                cin.ignore();
                break;
            }
        }
        array[n + i].provinsi = PROVINSI_JAWA[provinsiIndex - 1];
        cout << endl;
        cout << "Penghasilan per Bulan          : ";
        cin >> array[n + i].penghasilan;
        cin.ignore();
        cout << "Saldo                          : ";
        cin >> array[n + i].saldo;
        cin.ignore();
    }
    simpanDataNasabah(array + n, tambah, FILE_NASABAH, true);
    cout << "\nData berhasil disimpan!\n";
    system("pause");
}

void simpanDataNasabah(const Nasabah array[], int n, const string &filenasabah, bool ketemu)
{
    ofstream file;
    if (ketemu)
        file.open(filenasabah, ios::app);
    else
        file.open(filenasabah);
    for (int i = 0; i < n; ++i)
    {
        file << array[i].norek << ";"
             << array[i].nama << ";"
             << array[i].jeniskelamin << ";"
             << array[i].provinsi << ";"
             << array[i].penghasilan << ";"
             << array[i].saldo << endl;
    }
    file.close();
}

int loadDataNasabah(Nasabah array[], const string &filenasabah)
{
    ifstream file(filenasabah);
    string line;
    int n = 0;
    while (getline(file, line) && n < MAKS_NASABAH)
    {
        stringstream ss(line);
        getline(ss, array[n].norek, ';');
        getline(ss, array[n].nama, ';');
        getline(ss, array[n].jeniskelamin, ';');
        getline(ss, array[n].provinsi, ';');
        string temp;
        getline(ss, temp, ';');
        array[n].penghasilan = stod(temp);
        getline(ss, temp, ';');
        array[n].saldo = stod(temp);
        ++n;
    }
    file.close();
    return n;
}

void lihatDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    cout << "===================================================================================================================\n";
    cout << setw(75) << "MENU LIHAT DATA SEMUA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Jumlah data nasabah yang tersedia: " << n << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(15) << "No.Rekening"
         << setw(40) << "Nama"
         << setw(15) << "J.Kelamin"
         << setw(15) << "Provinsi"
         << setw(15) << "Penghasilan"
         << setw(15) << "Saldo" << endl;
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < n; ++i)
    {
        cout << left << setw(15) << array[i].norek
             << setw(40) << array[i].nama
             << setw(15) << array[i].jeniskelamin
             << setw(15) << array[i].provinsi
             << setw(15) << fixed << setprecision(2) << array[i].penghasilan
             << setw(15) << fixed << setprecision(2) << array[i].saldo << endl;
    }
    system("pause");
}

void sortingDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    int field, urut;
    cout << "===================================================================================================================\n";
    cout << "                                             MENU SORTING DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Urutkan Data Nasabah berdasarkan:\n";
    cout << "[1] Nomor Rekening\n";
    cout << "[2] Saldo\n";
    cout << "[3] Penghasilan per Bulan\n";
    cout << "[4] Kembali ke Menu Utama\n";
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    cout << "Pilihan: ";
    cin >> field;
    if (cin.fail() || field < 1 || field > 4)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Pilihan tidak valid!. Silakan pilih 1-4.\n";
        system("pause");
        return;
    }
    if (field == 4)
    {
        return;
    }
    cout << endl;
    cout << "Urutan:\n[1] Ascending\n[2] Descending\nPilihan: ";
    cin >> urut;
    if (cin.fail() || (urut != 1 && urut != 2))
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Pilihan urutan tidak valid!\n";
        system("pause");
        return;
    }
    bool asc = (urut == 1);
    bubbleSort(array, n, field, asc);

    system("cls");
    cout << endl;
    cout << "===================================================================================================================\n";
    cout << "                                             HASIL SORTING DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << left << setw(15) << "No.Rekening"
         << setw(40) << "Nama"
         << setw(15) << "J.Kelamin"
         << setw(15) << "Provinsi"
         << setw(15) << "Penghasilan"
         << setw(15) << "Saldo" << endl;
    cout << string(115, '-') << endl;
    for (int i = 0; i < n; ++i)
    {
        cout << left << setw(15) << array[i].norek
             << setw(40) << array[i].nama
             << setw(15) << array[i].jeniskelamin
             << setw(15) << array[i].provinsi
             << setw(15) << fixed << setprecision(2) << array[i].penghasilan
             << setw(15) << fixed << setprecision(2) << array[i].saldo << endl;
    }
    system("pause");
}

void swap(Nasabah *a, Nasabah *b)
{
    Nasabah temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort(Nasabah array[], int n, int field, bool ascending)
{
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            bool tukar = false;
            if (field == 1)
            {
                if (ascending)
                    tukar = array[j].norek > array[j + 1].norek;
                else
                    tukar = array[j].norek < array[j + 1].norek;
            }
            else if (field == 2)
            {
                if (ascending)
                    tukar = array[j].saldo > array[j + 1].saldo;
                else
                    tukar = array[j].saldo < array[j + 1].saldo;
            }
            else if (field == 3)
            {
                if (ascending)
                    tukar = array[j].penghasilan > array[j + 1].penghasilan;
                else
                    tukar = array[j].penghasilan < array[j + 1].penghasilan;
            }
            if (tukar)
                swap(&array[j], &array[j + 1]);
        }
    }
}

void searchingDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    int pilih;
    cout << "===================================================================================================================\n";
    cout << "                                           MENU SEARCHING DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Cari Data Nasabah berdasarkan:\n";
    cout << "[1] Nama (mengandung kata)\n";
    cout << "[2] Provinsi Domisili\n";
    cout << "[3] Kembali ke Menu Utama\n";
    cout << "-------------------------------------------------------------------------------------------------------------------\n";
    cout << "Pilihan: ";
    cin >> pilih;
    cin.ignore();
    if (pilih == 1)
    {
        string keyword;
        cout << "Masukkan keyword Nama: ";
        getline(cin, keyword);
        int hasil[MAKS_NASABAH], jum = 0;
        jum = rekursifCariNama(array, n, keyword, 0, hasil);
        if (jum == 0)
            cout << "\nMohon maaf, data Nasabah dengan keyword: " << keyword << ", tidak ditemukan.\n";
        else
        {
            system("cls");
            cout << "===================================================================================================================\n";
            cout << "                                           HASIL SEACHING DATA NASABAH\n";
            cout << "===================================================================================================================\n";
            cout << "Ditemukan " << jum << " data dengan keywod " << keyword << ":\n";
            cout << "-------------------------------------------------------------------------------------------------------------------\n";
            cout << left << setw(15) << "No.Rekening"
                 << setw(40) << "Nama"
                 << setw(15) << "J.Kelamin"
                 << setw(15) << "Provinsi"
                 << setw(15) << "Penghasilan"
                 << setw(15) << "Saldo" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------\n";
            for (int i = 0; i < jum; ++i)
            {
                int idx = hasil[i];
                cout << left << setw(15) << array[idx].norek
                     << setw(40) << array[idx].nama
                     << setw(15) << array[idx].jeniskelamin
                     << setw(15) << array[idx].provinsi
                     << setw(15) << fixed << setprecision(2) << array[i].penghasilan
                     << setw(15) << fixed << setprecision(2) << array[i].saldo << endl;
            }
        }
    }
    else if (pilih == 2)
    {
        string prov;
        cout << endl;
        cout << "Pilih provinsi domisili:\n";
        for (int i = 0; i < 6; ++i)
        {
            cout << "[" << (i + 1) << "] " << PROVINSI_JAWA[i] << endl;
        }
        cout << "Masukkan nomor provinsi (1-6): ";
        int provinsiIndex;
        cin >> provinsiIndex;
        cin.ignore();
        if (provinsiIndex < 1 || provinsiIndex > 6)
        {
            cout << "Pilihan provinsi tidak valid!\n";
            return;
        }
        prov = PROVINSI_JAWA[provinsiIndex - 1];
        int hasil[MAKS_NASABAH], jum = 0;
        jum = rekursifCariProvinsi(array, n, prov, 0, hasil);
        if (jum == 0)
            cout << "\nMohon maaf, data Nasabah dari provinsi " << prov << ", tidak ditemukan.\n";
        else
        {
            system("cls");
            cout << "===================================================================================================================\n";
            cout << "                                           HASIL SEACHING DATA NASABAH\n";
            cout << "===================================================================================================================\n";
            cout << "Ditemukan " << jum << " data dari provinsi " << prov << ":\n";
            cout << "-------------------------------------------------------------------------------------------------------------------\n";
            cout << left << setw(15) << "No.Rekening"
                 << setw(40) << "Nama"
                 << setw(15) << "J.Kelamin"
                 << setw(15) << "Provinsi"
                 << setw(15) << "Penghasilan"
                 << setw(15) << "Saldo" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------\n";
            for (int i = 0; i < jum; ++i)
            {
                int idx = hasil[i];
                cout << left << setw(15) << array[idx].norek
                     << setw(40) << array[idx].nama
                     << setw(15) << array[idx].jeniskelamin
                     << setw(15) << array[idx].provinsi
                     << setw(15) << fixed << setprecision(2) << array[i].penghasilan
                     << setw(15) << fixed << setprecision(2) << array[i].saldo << endl;
            }
        }
    }
    else if (pilih == 3)
    {
        return;
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
    }
    system("pause");
}

void updateDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    if (n == 0)
    {
        cout << "Mohon maaf, Data nasabah kosong!\n";
        system("pause");
        return;
    }
    cout << "===================================================================================================================\n";
    cout << "                                           MENU UPDATE DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "              Untuk mengupdate data nasabah, silakan masukkan nomor rekening nasabah yang ingin diupdate.\n";
    cout << "--------------------------------------------------------------------------------------------------------------------\n";
    cout << "Masukkan Nomor Rekening nasabah yang ingin diupdate: ";
    string norek;
    getline(cin, norek);
    int idx = -1;
    for (int i = 0; i < n; ++i)
    {
        if (array[i].norek == norek)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        cout << "Mohon maaf, Nomor rekening " << norek << " tidak ditemukan!\n";
        system("pause");
        return;
    }
    cout << "===================================================================================================================\n";
    cout << "                                           UPDATE DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Data Lama Nasabah " << norek << ":\n";
    cout << "Nama           : " << array[idx].nama << endl;
    cout << "Jenis Kelamin  : " << array[idx].jeniskelamin << endl;
    cout << "Provinsi       : " << array[idx].provinsi << endl;
    cout << "Penghasilan    : " << fixed << setprecision(2) << array[idx].penghasilan << endl;
    cout << "Saldo          : " << fixed << setprecision(2) << array[idx].saldo << endl;

    cout << " ==================================================================================================================\n";
    cout << "                                          MASUKKAN DATA BARU NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "                            Silakan masukkan data baru untuk nasabah " << norek << ".\n";
    cout << "                                   (tekan enter jika tidak ingin mengubah)\n";
    cout << "===================================================================================================================\n";
    string input;
    cout << "Nama [" << array[idx].nama << "]: ";
    getline(cin, input);
    if (!input.empty())
        array[idx].nama = input;
    while (true)
    {
        cout << "Jenis Kelamin (L/P) [" << array[idx].jeniskelamin << "]: ";
        getline(cin, input);
        if (input.empty())
        {
            break;
        }
        if (input == "L" || input == "l")
        {
            array[idx].jeniskelamin = "Laki-laki";
            break;
        }
        else if (input == "P" || input == "p")
        {
            array[idx].jeniskelamin = "Perempuan";
            break;
        }
        else
        {
            cout << "Input tidak valid! Masukkan 'L/l' untuk Laki-laki atau 'P/p' untuk Perempuan, atau tekan enter untuk tidak mengubah.\n";
        }
    }
    cout << "Provinsi [" << array[idx].provinsi << "]: ";
    cout << endl;
    cout << "Pilih Provinsi Domisili:\n";
    for (int j = 0; j < 6; ++j)
    {
        cout << "[" << (j + 1) << "] " << PROVINSI_JAWA[j] << endl;
    }
    cout << "Masukkan nomor provinsi (1-6) atau tekan enter untuk tidak mengubah: ";
    getline(cin, input);
    if (!input.empty())
    {
        int provinsiIndex = stoi(input);
        if (provinsiIndex >= 1 && provinsiIndex <= 6)
            array[idx].provinsi = PROVINSI_JAWA[provinsiIndex - 1];
        else
            cout << "Pilihan provinsi tidak valid! Provinsi tidak diubah.\n";
    }
    getline(cin, input);
    if (!input.empty())
        array[idx].provinsi = input;

    cout << "Penghasilan per Bulan [" << array[idx].penghasilan << "]: ";
    getline(cin, input);
    if (!input.empty())
        array[idx].penghasilan = stod(input);

    cout << "Saldo [" << array[idx].saldo << "]: ";
    getline(cin, input);
    if (!input.empty())
        array[idx].saldo = stod(input);

    simpanDataNasabah(array, n, FILE_NASABAH, false);
    cout << "===================================================================================================================\n";
    cout << "Data nasabah berhasil diupdate!\n";
    system("pause");
}

void hapusDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    if (n == 0)
    {
        cout << "Mohon maaf, Data nasabah kosong!\n";
        system("pause");
        return;
    }
    cout << "===================================================================================================================\n";
    cout << "                                           HAPUS DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Masukkan Nomor Rekening nasabah yang ingin dihapus: ";
    string norek;
    getline(cin, norek);
    int idx = -1;
    for (int i = 0; i < n; ++i)
    {
        if (array[i].norek == norek)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        cout << "Mohon maaf, Nomor rekening " << norek << " tidak ditemukan!\n";
        system("pause");
        return;
    }
    cout << "===================================================================================================================\n";
    cout << "                                           KONFIRMASI PENGHAPUSAN DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Data Nasabah yang akan dihapus:\n";
    cout << "Nomor Rekening                 : " << array[idx].norek << endl;
    cout << "Nama Nasabah                   : " << array[idx].nama << endl;
    cout << "Jenis Kelamin                  : " << array[idx].jeniskelamin << endl;
    cout << "Provinsi Domisili              : " << array[idx].provinsi << endl;
    cout << "Penghasilan per Bulan          : " << fixed << setprecision(2) << array[idx].penghasilan << endl;
    cout << "Saldo                          : " << fixed << setprecision(2) << array[idx].saldo << endl;
    cout << "===================================================================================================================\n";
    cout << "Data nasabah dengan Nomor Rekening " << array[idx].norek << " atas nama " << array[idx].nama << " akan dihapus.\n";
    cout << "Yakin ingin menghapus? (y/n): ";
    char yakin;
    cin >> yakin;
    cin.ignore();
    if (yakin == 'y' || yakin == 'Y')
    {
        for (int i = idx; i < n - 1; ++i)
        {
            array[i] = array[i + 1];
        }
        n--;
        simpanDataNasabah(array, n, FILE_NASABAH, false);
        cout << "Data nasabah berhasil dihapus!\n";
    }
    else
    {
        cout << "Penghapusan dibatalkan.\n";
    }
    system("pause");
}

int rekursifCariNama(const Nasabah array[], int n, const string &keyword, int idx, int hasil[])
{
    if (idx >= n)
        return 0;
    int found = 0;
    string nama = array[idx].nama, key = keyword;
    for (char &c : nama)
        c = tolower(c);
    for (char &c : key)
        c = tolower(c);
    if (nama.find(key) != string::npos)
    {
        hasil[0] = idx;
        found = 1;
    }
    int next = rekursifCariNama(array, n, keyword, idx + 1, hasil + found);
    return found + next;
}

int rekursifCariProvinsi(const Nasabah array[], int n, const string &prov, int idx, int hasil[])
{
    if (idx >= n)
        return 0;
    int found = 0;
    string prov1 = array[idx].provinsi, prov2 = prov;
    for (char &c : prov1)
        c = tolower(c);
    for (char &c : prov2)
        c = tolower(c);
    if (prov1.find(prov2) != string::npos)
    {
        hasil[0] = idx;
        found = 1;
    }
    int next = rekursifCariProvinsi(array, n, prov, idx + 1, hasil + found);
    return found + next;
}

void filterDataNasabah()
{
    system("cls");
    Nasabah array[MAKS_NASABAH];
    int n = loadDataNasabah(array, FILE_NASABAH);
    int pilih;
    cout << "===================================================================================================================\n";
    cout << "                                           MENU FILTER DAN EKSPOR DATA NASABAH\n";
    cout << "===================================================================================================================\n";
    cout << "Filter & Ekspor berdasarkan:\n";
    cout << "[1] Jenis Kelamin\n";
    cout << "[2] Provinsi Domisili\n";
    cout << "[3] Ekspor Semua Data Nasabah (Rapi)\n";
    cout << "[4] Kembali ke Menu Utama\n";
    cout << "Pilihan: ";
    cin >> pilih;
    if (pilih == 1)
    {
        if (n == 0)
        {
            cout << "Data nasabah kosong, tidak dapat mengekspor.\n";
        }
        else
        {
            eksporPerJenisKelamin(array, n);
        }
    }
    else if (pilih == 2)
    {
        if (n == 0)
        {
            cout << "Data nasabah kosong, tidak dapat mengekspor.\n";
        }
        else
        {
            eksporPerProvinsi(array, n);
        }
    }
    else if (pilih == 3)
    {
        if (n == 0)
        {
            cout << "Data nasabah kosong, tidak dapat mengekspor.\n";
        }
        else
        {
            eksporLaporanRapi(array, n);
        }
    }
    else if (pilih == 4)
    {
        return;
    }
    else
    {
        cout << "Pilihan tidak valid!\n";
    }
    system("pause");
}

void eksporPerJenisKelamin(const Nasabah array[], int n)
{
    ofstream fileL("nasabah_bank_jawa_laki.txt");
    ofstream fileP("nasabah_bank_jawa_perempuan.txt");
    for (int i = 0; i < n; ++i)
    {
        if (array[i].jeniskelamin == "Laki-laki")
            fileL << array[i].norek << ";" << array[i].nama << ";" << array[i].provinsi << ";" << array[i].penghasilan << ";" << array[i].saldo << endl;
        else if (array[i].jeniskelamin == "Perempuan")
            fileP << array[i].norek << ";" << array[i].nama << ";" << array[i].provinsi << ";" << array[i].penghasilan << ";" << array[i].saldo << endl;
    }
    fileL.close();
    fileP.close();
    cout << "Data berhasil diekspor ke nasabah_bank_jawa_laki.txt dan nasabah_bank_jawa_perempuan.txt\n";
}

void eksporPerProvinsi(const Nasabah array[], int n)
{
    ofstream fileProv[6];
    string namaFileProv[6] = {
        "bank_jawa_dkijakarta.txt", "bank_jawa_jawabarat.txt", "bank_jawa_jawatengah.txt", "bank_jawa_jawatimur.txt", "bank_jawa_banten.txt", "bank_jawa_diyogyakarta.txt"};
    for (int i = 0; i < 6; ++i)
        fileProv[i].open(namaFileProv[i]);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            string prov1 = array[i].provinsi, prov2 = PROVINSI_JAWA[j];
            for (char &c : prov1)
                c = tolower(c);
            for (char &c : prov2)
                c = tolower(c);
            if (prov1 == prov2)
            {
                fileProv[j] << array[i].norek << ";" << array[i].nama << ";" << array[i].jeniskelamin << ";" << array[i].penghasilan << ";" << array[i].saldo << endl;
                break;
            }
        }
    }
    for (int i = 0; i < 6; ++i)
        fileProv[i].close();
    cout << "Data berhasil diekspor ke file per provinsi.\n";
}

void eksporLaporanRapi(const Nasabah array[], int n)
{
    ofstream file("laporan_nasabah_bank_jawa_rapi.txt");
    if (!file.is_open())
    {
        cout << "Gagal membuka file laporan_nasabah_bank_jawa_rapi.txt\n";
        return;
    }
    file << left << setw(15) << "No.Rekening"
         << setw(40) << "Nama"
         << setw(15) << "J.Kelamin"
         << setw(15) << "Provinsi"
         << setw(15) << "Penghasilan"
         << setw(15) << "Saldo" << endl;
    file << string(115, '-') << endl;
    for (int i = 0; i < n; ++i)
    {
        file << left << setw(15) << array[i].norek
             << setw(40) << array[i].nama
             << setw(15) << array[i].jeniskelamin
             << setw(15) << array[i].provinsi
             << setw(15) << fixed << setprecision(2) << array[i].penghasilan
             << setw(15) << fixed << setprecision(2) << array[i].saldo << endl;
    }
    file.close();
    cout << "Laporan nasabah rapi berhasil diekspor ke laporan_nasabah_bank_jawa_rapi.txt\n";
}