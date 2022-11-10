// Program ini adalah  dan database perkutut airline

// DEKLARASI PUSTAKA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>

// DEKLARASI STRUCT
// STRUCT / MODEL UNTUK TIPE PENERBANGAN
typedef struct {
	char kode[10];
	char tujuan[20];
	int harga_dewasa_bisnis;
	int harga_kids_bisnis;
	int harga_dewasa_ekonomi;
	int harga_kids_ekonomi;
} Tipe_Penerbangan;

// STRUCT / MODEL UNTUK TIKET PEMBELIAN
typedef struct{
	char NIK[11];
	char nama[120];
	char tgl_lhr[20];
	char tmpt_lhr[20];
	char kelamin;
	char alamat[120];
	char agama[120];
	char is_nikah;
	char is_pp; // apakah tiket berupa pulang pergi
	char pekerjaan[120];
	char kewarganegaraan[120];
	char no_tel[12];
	char kelas;
	int kode_penerbangan;
	char tgl_keberangkatan[12];
	char jam_keberangkatan[12];
	char jam_tiba[12];
	int jml_dewasa;
	int jml_kids;
	int total_penumpang;
	long long harga_total;
} Tiket;

// STRUCT / MODEL UNTUK KEUANGAN PERKUTUT AIRLINE
typedef struct {
  long long total_uang;
  long long harga_terendah;
  char terendah_oleh[120];
  long long harga_tertinggi;
  char tetinggi_oleh[120];
} Keuangan;

// DEKLARASI KONSTANTA
const int HARI_PADA_BULAN[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // berisi hari dalam bulan untuk validasi input tanggal
const int MAX_PENUMPANG = 4; // jumlah maksimal penumpang per tiket
Tipe_Penerbangan TIPE[5] = { // inisialisasi db tipe / rute penerbangan
	{ "PAL001", "Semarang", 800000, 600000, 500000, 400000 }, 
	{ "PAL002", "Solo", 850000, 650000, 550000, 450000 }, 
	{ "PAL003", "Yogyakarta", 850000, 650000, 550000, 450000 }, 
	{ "PAL004", "Surabaya", 1000000, 800000, 700000, 600000 }, 
	{ "PAL005", "Bali", 1200000, 1000000, 800000, 700000 }
};

// DEKLARASI GLOBAL VARIABLE
int i, x; // digunakan untuk index dalam loop
int idx_pembeli = 0; // untuk mengkeep-track jumlah pembeli
int input_menu = 0; // untuk menyimpan input pilihan menu dari user
int len_nama_terpanjang; // untuk menyimpang nama dengan length string terpanjang
Keuangan data_keuangan = { 0 , 0, "", 0, "" }; // untuk menyimpan data keuangan perkutut airline
Tiket db[200]; // insialisasi database pembelian tiket

// DEKLARASI PROSEDUR
// PROSEDUR VIEWS BERTIPE MENU
void menu_pembelian_tiket();
void menu_router_utama(int *input_menu); // untuk mengarahkan ke menu pembelian tiket dan database
void menu_router_db(int *input_menu);  // untuk mengarahkan ke db rute penerbangan dan data pembelian

// PROSEDUR VIEWS BERTIPE FORM
void form_input_data_ktp();
void form_input_data_penerbangan();

// PROSEDUR VIEWS BERTIPE TABEL
void tabel_tipe_penerbangan();
void tabel_data_pembelian();
void tabel_detail_tiket();

// PROSEDUR BERTIPE UTILTIY
void util_update_keuangan(char *cust_name, int harga_tiket, Keuangan *data); // untuk mengupdate keuangan setiap ada pembelian tiket
void util_print_repeat(char *prefix, char *str, int amount, char *suffix); // mencetak str sebanyak amount kali
void util_print_center(char *prefix, char *str, char *div, int len, char *suffix); // mencetak str di posisi tengah dengan panjang 'len'
void util_back_to_prev_menu(); // menampilkan tulisan "tekan apa saja untuk kembali ke menu utama" 
// AKHIR DEKLARASI PROSEDUR

// DEKLARASI FUNGSI
// FUNGSI BERTIPE UTILITY
bool util_is_date_valid(char *date);
bool util_is_time_valid(char *time);
// AKHIR DEKLARASI FUNGSI

// DEKLARASI ALGORITMA
int main() {
  menu_router_utama(&input_menu); //	Memanggil menu utama untuk memulai aplikasi

  // jika user keluar dari program
	system("cls");
  util_print_repeat("+", "-", 100, "+\n");
  util_print_center("|", "Terima Kasih Telah Menggunakan Jasa Perkutut Airline", " ", 100, "|\n");
  util_print_repeat("+", "-", 100, "+\n");
	return 0;
}
				
// DEFINSI PROSEDUR BERTIPE MENU
void menu_router_utama(int *input_menu) {
	while (true) {
		system("cls");
    
    // mencetak tampilan menu utama
    util_print_center("+", "PERKUTUT AIRLINE", "-", 24, "+\n");
		printf("| 1. Menu Input Tiket    |\n");
		printf("| 2. Menu Lihat Database |\n");
		printf("| 3. Keluar Dari Program |\n");
    util_print_repeat("+", "-", 24, "+\n");

    // menerima input menu dari user
		printf("\nInput: "); fflush(stdin); scanf("%i", input_menu);

    // router untuk menu pembelian dan menu database
		if (*input_menu == 1) 
			menu_pembelian_tiket();
    else if (*input_menu == 2) 
			menu_router_db(input_menu);
    else if (*input_menu == 3) 
			break;
	} ;
} 
void menu_router_db(int *input_menu) {
  while (true) {
    system("cls");
    // mencetak tampilan menu utama
    util_print_center("", "DATABASE PERKUTUT AIRLINE", "-", 33, "\n");
    printf("| 1. Lihat Rute Penerbangan     |\n");
    printf("| 2. Lihat Data Pembelian Tiket |\n");
    printf("| 3. Kembali Ke Menu Utama      |\n");
    util_print_repeat("", "-", 33, "\n");

    // menerima input menu dari user
    printf("\nInput: "); fflush(stdin); scanf("%i", input_menu);
    system("cls");

    // router menu database
    if (*input_menu == 1) {
      tabel_tipe_penerbangan();
      util_back_to_prev_menu();
    } else if (*input_menu == 2) {
      tabel_data_pembelian();
      util_back_to_prev_menu();
    } else if (*input_menu == 3) {
      break;
    }
  }
} 
void menu_pembelian_tiket() {  
  // memanggil form untuk menerima data terkait dengan tiket
  form_input_data_ktp();
  form_input_data_penerbangan();
	
  // update data keuangan
  util_update_keuangan(db[idx_pembeli].nama, db[idx_pembeli].harga_total, &data_keuangan);

  // mencetak detail tiket
  system("cls");
  tabel_detail_tiket();
  util_back_to_prev_menu();

  // menambahkan jumlah pembeli yang terimput	
	idx_pembeli += 1;
} 

// DEFINSI PROSEDUR BERTIPE FORM
void form_input_data_ktp() {
	system("cls");
  
  // mencetak header form input data ktp
  util_print_center("", "FORM INPUT DATA KTP", " ", 40, "\n");	
  util_print_repeat("", "-", 40, "\n");

	// MULAI INPUT DATA KTP	
	do {
		printf("1. Masukkan NIK [10 digit]: ");
		fflush(stdin); gets(db[idx_pembeli].NIK);
	} while (strlen(db[idx_pembeli].NIK) != 10);
	
	do {
		printf("2. Masukkan Nama Anda: ");
		fflush(stdin); gets(db[idx_pembeli].nama);

    // mengubah nilai variabel penampung panjang string nama terpanjang
    if (strlen(db[idx_pembeli].nama) > len_nama_terpanjang) {
      len_nama_terpanjang = strlen(db[idx_pembeli].nama);
    }
	} while (strlen(db[idx_pembeli].nama) == 0);
	
	do {
		printf("3. Masukkan tanggal lahir [yyyy-mm-dd]: ");
		fflush(stdin); gets(db[idx_pembeli].tgl_lhr);
	} while (strlen(db[idx_pembeli].tgl_lhr) == 0 || !util_is_date_valid(db[idx_pembeli].tgl_lhr));
	
	do {
		printf("4. Masukkan Jenis Kelamin [P/W]: ");
		fflush(stdin); scanf("%c", &db[idx_pembeli].kelamin);
    
    // mengubah ke huruf kecil jika user memasukkan huruf kapital
    db[idx_pembeli].kelamin = tolower(db[idx_pembeli].kelamin); 
	} while (db[idx_pembeli].kelamin != 'p' && db[idx_pembeli].kelamin != 'w');
	
	do {
		printf("5. Masukkan Alamat Anda: ");
		fflush(stdin); gets(db[idx_pembeli].alamat);
	} while (strlen(db[idx_pembeli].alamat) == 0);	
	
	do {
		printf("6. Masukkan Agama Anda: ");
		fflush(stdin); gets(db[idx_pembeli].agama);
	} while (strlen(db[idx_pembeli].agama) == 0);
	
	do {
		printf("7. Apakah Anda Sudah Menikah [Y/N]: ");
		fflush(stdin); scanf("%c", &db[idx_pembeli].is_nikah);
    
    // mengubah ke huruf kecil jika user memasukkan huruf kapital
    db[idx_pembeli].is_nikah = tolower(db[idx_pembeli].is_nikah); 
	} while (db[idx_pembeli].is_nikah != 'y' && db[idx_pembeli].is_nikah != 'n');
	
	do {
		printf("8. Masukkan Pekerjaan Anda: ");
		fflush(stdin); gets(db[idx_pembeli].pekerjaan);
	} while (strlen(db[idx_pembeli].pekerjaan) == 0);
	
	do {
		printf("9. Masukkan Kewarganegaraan Anda: ");
		fflush(stdin); gets(db[idx_pembeli].kewarganegaraan);
	} while (strlen(db[idx_pembeli].kewarganegaraan) == 0);
	
	do {
		printf("10. Masukkan Nomor Telepon Anda [10 digit]: ");
		fflush(stdin); gets(db[idx_pembeli].no_tel);
	} while (strlen(db[idx_pembeli].no_tel) != 10);
	// AKHIR INPUT DATA KTP	
}
void form_input_data_penerbangan() {
  int sisa_kursi = MAX_PENUMPANG; // menampung sisa kursi setelah jumlah penumpang dewasa di input
  int flight_code_temp; // untuk mempersingkat kode dikala menghitung harga tiket pada akhir prosedur ini

  // mencetak tabel TIPE penerbangan dan header form input data penerbangan
  system("cls");
	tabel_tipe_penerbangan();
  util_print_center("\n\n", "FORM INPUT DATA PENERBANGAN", " ", 30, "\n");	
  util_print_repeat("", "-", 30, "\n");
	
	// MULAI INPUT DATA PENERBANGAN
	do {
		printf("1. Masukkan Kode Penerbangan [1-5]: ");
		fflush(stdin); scanf("%i", &db[idx_pembeli].kode_penerbangan);
    
    // menyesuaikan input no urut dengan index pada array tipe penerbangan
    db[idx_pembeli].kode_penerbangan -= 1;
    flight_code_temp = db[idx_pembeli].kode_penerbangan;
	} while (db[idx_pembeli].kode_penerbangan < 0 || db[idx_pembeli].kode_penerbangan > 5);	

	do {
		printf("2. Masukkan Kelas Penerbangan [E/B]: ");
		fflush(stdin); scanf("%c", &db[idx_pembeli].kelas);
    
    // mengubah ke huruf kecil jika user memasukkan huruf kapital
    db[idx_pembeli].kelas = tolower(db[idx_pembeli].kelas); 
	} while (db[idx_pembeli].kelas != 'e' && db[idx_pembeli].kelas != 'b');
	
	do {
		printf("3. Masukkan Tanggal Keberangkatan [yyyy-mm-dd]: ");
		fflush(stdin); gets(db[idx_pembeli].tgl_keberangkatan);
	} while (strlen(db[idx_pembeli].tgl_keberangkatan) == 0 || !util_is_date_valid(db[idx_pembeli].tgl_keberangkatan));
	
	do {
		printf("4. Masukkan Jam Keberangkatan [hh:mm:ss]: ");
		fflush(stdin); gets(db[idx_pembeli].jam_keberangkatan);
	} while (strlen(db[idx_pembeli].jam_keberangkatan) == 0 || !util_is_time_valid(db[idx_pembeli].jam_keberangkatan));
	
	do {
		printf("5. Masukkan Jam Tiba [hh:mm:ss]: ");
		fflush(stdin); gets(db[idx_pembeli].jam_tiba);
	} while (strlen(db[idx_pembeli].jam_tiba) == 0 || !util_is_time_valid(db[idx_pembeli].jam_tiba));
	
	while (true) {	
		printf("6. Masukkan Jumlah Penumpang Dewasa (MAX. 4): ");
		fflush(stdin); scanf("%i", &db[idx_pembeli].jml_dewasa);
		
		// mengecek apakah input jumlah penumpang dewasa kurang dari sama dengan 4
		if (db[idx_pembeli].jml_dewasa <= sisa_kursi) {
      sisa_kursi = sisa_kursi - db[idx_pembeli].jml_dewasa;
			break;
		}
	};
	
	do {
    if (sisa_kursi == 0) break;
		printf("7. Masukkan Jumlah Penumpang Anak-Anak (MAX. %i): ", sisa_kursi);
		fflush(stdin); scanf("%i", &db[idx_pembeli].jml_kids);
	} while (db[idx_pembeli].jml_kids > sisa_kursi);
	
  // Menentukan harga akhir tiket
  if (db[idx_pembeli].kelas == 'e') {
    db[idx_pembeli].harga_total = 
      (TIPE[flight_code_temp].harga_dewasa_ekonomi * db[idx_pembeli].jml_dewasa) 
      + (TIPE[flight_code_temp].harga_kids_ekonomi * db[idx_pembeli].jml_kids); 
  } else {
    db[idx_pembeli].harga_total =  
      (TIPE[flight_code_temp].harga_dewasa_bisnis * db[idx_pembeli].jml_dewasa) 
      + (TIPE[flight_code_temp].harga_kids_bisnis * db[idx_pembeli].jml_kids);
  }
  // AKHIR INPUT DATA PENERBANGAN
}

// DEFINSI PROSEDUR BERTIPE TABEL
void tabel_tipe_penerbangan() { 
	// mencetak header table	
	util_print_center("+", "TABEL TIPE PENERBANGAN", "-", 83, "+\n");
	printf("| NO %-1s| %-2s Kode %-2s | %-1s Tujuan %-1s | %-4s Tiket Bisnis %-5s | %-4s Tiket Ekonomi %-4s |\n", "", "", "", "", "", "", "", "", "");
	printf("|	%-23s | %-1s Dewasa %-1s | Anak-Anak  | %-1s Dewasa %-1s | Anak-Anak  |\n", "", "", "", "", "", "", "");
	util_print_repeat("+", "-", 83, "+");

	// meloop seisi array data TIPE penerbangan
	for (i = 0; i < 5; i++) {
		printf("\n| %-3i | %-10s | %-10s | Rp.%-7li | Rp.%-7li | Rp.%-7li | Rp.%-7li |",
						i + 1, TIPE[i].kode, TIPE[i].tujuan, TIPE[i].harga_dewasa_bisnis, TIPE[i].harga_kids_bisnis
						, TIPE[i].harga_dewasa_ekonomi, TIPE[i].harga_kids_ekonomi 
					);
	}
	
	// footer table
	util_print_repeat("\n", "-", 85, "\n");
} 
void tabel_data_pembelian() {
  const int LEBAR_DEFAULT = 5 + 4 + 10 + 10 + 19 + 18 + 15 + 15 + 15 + 14;
  float rata_rata_harga;
  int lebar_tabel_dinamis = len_nama_terpanjang + LEBAR_DEFAULT;
  char temp[10]; // untuk menampung hasil konversi int to string

  //	mencetak header table	
  util_print_center("+", "TABEL PEMBELIAN TIKET", "-", lebar_tabel_dinamis, "+\n");
  util_print_center("| ", "NO", " ", 3, " | ");
  util_print_center("", "Nama Pembeli", " ", len_nama_terpanjang + 5, " | ");
  util_print_center("", "Kode", " ", 6, " | ");
  util_print_center("", "Tanggal", " ", 10, " | ");
  util_print_center("", "Keberangkatan", " ", 15, " | ");
  util_print_center("", "Kedatangan", " ", 13, " | ");
  util_print_center("", "Kelas", " ", 11, " | ");
  util_print_center("", "Dewasa", " ", 11, " | ");
  util_print_center("", "Anak-Anak", " ", 11, " | ");
  util_print_center("", "Harga", " ", 11, " |");
  util_print_repeat("\n+", "-", lebar_tabel_dinamis, "+\n");

  // pengecekan jumlah pembeli 
  if (idx_pembeli == 0) {
    util_print_center("|", "BELUM ADA PEMBELI !", " ", lebar_tabel_dinamis, "|\n");
  } else {
    // menghitung rata-rata harga jika sudah ada minimal 1 tiket yang terjual
    rata_rata_harga = data_keuangan.total_uang / idx_pembeli;

    // mencetak seluruh data penerbangan 
    for (x = 0; x < idx_pembeli; x++) {
      // mencetak no urut pada database
      sprintf(temp, "%i", x + 1); util_print_center("| ", temp, " ", 3, " | "); strcpy(temp, "");

      // mencetak data lain yang tidak butuh konversi angka ke string
      util_print_center("", db[x].nama, " ", len_nama_terpanjang + 5, " | ");
      util_print_center("", TIPE[db[x].kode_penerbangan].kode, " ", 6, " | ");
      util_print_center("", db[x].tgl_keberangkatan, " ", 10, " | ");
      util_print_center("", db[x].jam_keberangkatan, " ", 15, " | ");
      util_print_center("", db[x].jam_tiba, " ", 13, " | ");
      util_print_center("", db[x].kelas == 'e' ? "Ekonomi" : "Bisnis", " ", 11, " | ");

      // mencetak jumlah penumpang dewasa
      sprintf(temp, "%i", db[x].jml_dewasa); util_print_center("", temp, " ", 11, " | "); strcpy(temp, ""); 
      
      // mencetak jumlah penumpang anak-anak
      sprintf(temp, "%i", db[x].jml_kids); util_print_center("", temp, " ", 11, " | "); strcpy(temp, "");
      
      // mencetak harga total
      sprintf(temp, "Rp.%i", db[x].harga_total); util_print_center("", temp, " ", 11, " |\n"); strcpy(temp, "");
    }
  }

  // footer table
  util_print_repeat("+", "-", len_nama_terpanjang + LEBAR_DEFAULT, "+\n\n");

  // detail tentang harga tiket 
  printf("Pembayaran Rata-Rata: Rp.%.2f\n", rata_rata_harga);
  printf("Pembayaran Tertinggi: Rp.%lli | Oleh: %s\n", data_keuangan.harga_tertinggi, data_keuangan.tetinggi_oleh);
  printf("Pembayaran Terendah: Rp.%lli | Oleh: %s\n", data_keuangan.harga_terendah, data_keuangan.terendah_oleh);
} 
void tabel_detail_tiket() { 
  util_print_center("", "DETAIL TIKET", "-", 43, "\n");
  printf("1. Nama Pembeli: %s \n", db[idx_pembeli].nama);
  printf("2. Kode: %s \n", TIPE[db[idx_pembeli].kode_penerbangan]);
  printf("3. Kelas: %s  \n", db[idx_pembeli].kelas == 'e' ? "Ekonomi" : "Bisnis");
  printf("4. Rute: Jakarta - %s \n", TIPE[db[idx_pembeli].kode_penerbangan].tujuan);
  printf("5. Tanggal Keberangkatan: %s \n", db[idx_pembeli].tgl_keberangkatan);
  printf("6. Jam Keberangkatan: %s \n", db[idx_pembeli].jam_keberangkatan);
  printf("7. Jam Tiba: %s \n", db[idx_pembeli].jam_tiba);
  printf("8. Penumpang Dewasa: %i Orang   \n", db[idx_pembeli].jml_dewasa);
  printf("9. Penumpang Anak-Anak: %i Orang  \n", db[idx_pembeli].jml_kids);
  printf("10. Harga Total: Rp.%lli \n", db[idx_pembeli].harga_total); 
  util_print_repeat("", "-", 43, "");
}

// DEFINSI PROSEDUR BERTIPE UTILITY
void util_update_keuangan(char *cust_name, int harga_tiket, Keuangan *data) { 
  // update total uang perusahaan
  data->total_uang += harga_tiket;

  // update pembelian termurah jika harga tiket baru lebih murah dari sebelumnya
  if (harga_tiket < data->harga_terendah || data->harga_terendah == 0) {
    data->harga_terendah = harga_tiket;
    strcpy(data->terendah_oleh, cust_name);
  }
  
  // update pembelian termahal jika harga tiket baru lebih mahal dari sebelumnya
  if (harga_tiket > data->harga_tertinggi || data->harga_tertinggi == 0) {
    data->harga_tertinggi = harga_tiket;
    strcpy(data->tetinggi_oleh, cust_name);
  }
}
void util_print_repeat(char *prefix, char *str, int amount, char *suffix) { 
	printf("%s", prefix); // mencetak karakter awalan 
  for (i = 0; i < amount; i++) printf("%s", str); // mencetak string sebanyak 'amount' kali
	printf("%s", suffix); // mencetak karakter akhiran 
}
void util_print_center(char *prefix, char *str, char *div, int len, char *suffix) {
	int spasi = len - strlen(str);
  int spasi_kiri = spasi % 2 != 0 ? spasi / 2 + 1 : spasi / 2;
  int spasi_kanan = spasi / 2;

  // proses percetakan
	printf("%s", prefix); // mencetak karakter awalan
  for (i = 0; i < spasi_kiri; i++) printf("%s", div); // mencetak spasi kiri
  printf("%s", str); // mencetak string di posisi tengah
  for (i = 0; i < spasi_kanan; i++) printf("%s", div); // mencetak spasi kanan
	printf("%s", suffix); // mencetak karakter akhiran 
}
void util_back_to_prev_menu() { 
  printf("\n\nTekan apa saja untuk kembali ke menu sebelumnya !"); getche(); 
}
  
// DEFINISI FUNGSI BERTIPE UTILITY
bool util_is_date_valid(char *date) {
	bool is_valid = true;
  char date_str[9];
  strcpy(date_str, date);


  // jika panjang string tidak 10 maka tidak valid 
  if (strlen(date_str) != 10) return !is_valid;

	int tahun = atoi(strtok(date_str, "-"));
	int bulan = atoi(strtok(NULL, "-"));
	int hari = atoi(strtok(NULL, "-"));

	// Validasi Tahun
	if (!tahun) return !is_valid;
	
	// validasi Bulan
	if (bulan <= 0 || bulan > 12) return !is_valid;
	
	// Validasi Hari
	if (hari <= 0 || hari > HARI_PADA_BULAN[bulan - 1]) return !is_valid;
	 
	// Validasi hari pada tahun kabisat
	if (tahun % 4 == 0 && HARI_PADA_BULAN[bulan - 1] && hari > 29) return !is_valid;
	
	//	Jika tanggal berhasil melewati validasi
	return is_valid;
}
bool util_is_time_valid(char *time) {
	bool is_valid = true;
  char time_str[9];
  strcpy(time_str, time);

  // jika panjang string tidak 8 maka tidak valid 
  if (strlen(time_str) != 8) return !is_valid;

	int jam = atoi(strtok(time_str, ":"));
	int menit = atoi(strtok(NULL, ":"));
	int detik = atoi(strtok(NULL, ":"));

  // Validasi Jam
	if (jam > 24) return !is_valid;
	
	// Validasi Menit
	if (menit > 60 || menit < 0) return !is_valid;
	
	// Validasi Detika
	if (detik > 60 || detik < 0) return !is_valid;

	// Jika tanggal berhasil melewati validasi
	return is_valid;
}
