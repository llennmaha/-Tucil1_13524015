Tugas Kecil 1 IF2211 Strategi Algoritma

Mahatma Brahmana/13524015

# Puzzle Queen

Program ini menyelesaikan puzzle penempatan n queen pada papan n×n berisi huruf/warna, dengan aturan:
- Tepat 1 queen per baris (implisit dari representasi solusi).
- Tidak boleh ada 2 queen di kolom yang sama.
- Tidak boleh ada 2 queen di warna/huruf yang sama.
- Tidak boleh ada yang bersebelahan, termasuk diagonal.

Program menyediakan 2 metode:
1. Brute force murni (utama) → enumerasi semua kemungkinan `n^n`.
2. Optimisasi (Backtracking) → lebih cepat karena ada backtrack



Program ini menggunakan C++ dan membutuhkan compiler C++ untuk menjalankan program


## Struktur Folder

root/  
│  
├─ bin/  
│ ├─ main.exe  
├─ doc/  
│ ├─  Tucil1_13524015.pdf  
├─ result/  
│ ├─ result.txt  
├─ src/  
│ ├─ main.cpp  
├─ test/  
│ ├─ input.txt  

## Catatan
1. File input berisi karakter n baris, setiap baris panjangnya n karakter.  
Contoh (5×5):  
AABBC  
AABBC  
DDEEC  
DDEEC  
FFFFG  
2. Huruf yang sama dianggap warna yang sama.
3. Program mengasumsikan papan persegi.
4. Input wajib diletakkan di folder test
5. Output akan diletakkan di folder result
   
## Cara Kompilasi : 
1. Jalankan `g++ -o bin/main src/main.cpp` di Terminal
2. Jalankan `./bin/main` di Terminal

## Cara Run :
1. Masukkan file .txt ke folder test
2. Jalankan `./bin/main` di Terminal
3. Akan diminta nama file yang ingin dibuka, masukkan nama file sesuai keinginan
4. Pilih metode penyelesaian
5. Tunggu, proses komputasi sedang berlangsung
6. Didapat hasil, dan ada pilihan untuk menyimpan hasil ke folder result, pilih y/n
7. Jika memilih y, maka perlu input nama file hasil
8. Maka file hasil sudah selesai dibuat
