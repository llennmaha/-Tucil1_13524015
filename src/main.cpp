#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cctype>
#include <chrono>
using namespace std;

bool salin(const string& filename, vector<vector<char>>& array){
    filesystem::path p = filesystem::current_path() / "test" / (filename + ".txt");

    ifstream in(p);
    if (!in) {
        cout << "Tidak ada file bernama " << p << endl;
        return false;
    }

    string line;
    unordered_set<char> colours;
    while (getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        array.emplace_back(line.begin(), line.end());
        for (int i = 0; i < line.size(); ++i) {
            if (!isalpha(static_cast<unsigned char>(line[i]))) {
                cout << "Karakter tidak valid (harus alfabet): " << line[i] << endl;
                return false;
            }
            colours.insert(line[i]);
        }
    }

    if (array.empty()) {
        cout << "File kosong." << endl;
        return false;
    }

    if (array[1].size() != array.size()) {
        cout << "Isi file tidak berbentuk persegi.\n";
        return false;
    }

    if (colours.size() != array.size()) {
        cout << "Jumlah warna/alphabet harus tepat," << endl << "Besar array :  " << array.size() << endl << "Jumlah warna/alphabet :  " << colours.size() << "." << endl;
        return false;
    }

    for (const auto& row : array) {
        for (char ch : row){
            cout << ch;
        }
        cout << endl;
    }
    cout << endl;
    return true;
}

void solutionOptimization(vector<vector<char>> array){
    int n = array.size();
    int i = 0 , j = 0;

    vector<char> colour;
    vector<vector<bool>> queen(n, vector<bool>(n, false));
    int countqueen = 0;

    vector<int> rowposition(n, 0);

    int count = 0;
    auto start = chrono::high_resolution_clock::now();

    while ((countqueen < n) && (i < n) ){
        if (rowposition[0] >= n){
            cout<<"Tidak ada solusi\n";
            return;
        }else if (rowposition[i] >= n){
            rowposition[i] = 0;
            i -= 1;
            queen[i][rowposition[i]] = false;

            colour.pop_back();
            rowposition[i] += 1;
            countqueen -= 1;

            cout << endl << "Kembali ke baris " << i << ", coba posisi berikutnya: " << rowposition[i] << endl;
            count++;
            continue;
        }
        while (rowposition[i] < n) {
            bool conflict = false;

            for (int r = 0; r < i; ++r) {
                if (rowposition[r] == rowposition[i]) {
                    conflict = true;
                    break;
                }
            }
            if (conflict){ 
                rowposition[i]++; 
                count++;
                continue; 
            }

            for (char used : colour) {
                if (used == array[i][rowposition[i]]) {
                    conflict = true;
                    break;
                }
            }
            if (conflict){ 
                rowposition[i]++; 
                count++;
                continue; 
            }

            if (i != 0){
                if (abs(rowposition[i] - rowposition[i-1]) == 1){
                    conflict = true;
                }
                // if (rowposition[i] == 0){
                //     if (queen[i-1][rowposition[i] + 1] == true){
                //         conflict = true;
                //     }
                // }
                // else if (rowposition[i] == n-1){
                //     if (queen[i-1][rowposition[i] - 1] == true){
                //         conflict = true;
                //     }
                // }
                // else{
                //     if (queen[i-1][rowposition[i] - 1] == true || queen[i-1][rowposition[i] + 1] == true){
                //         conflict = true;
                //     }
                // }
            }

            if (conflict){ 
                rowposition[i]++; 
                count++;
                continue; 
            }

            break;
        }
        if (rowposition[i] >= n){
            continue;
        }

        queen[i][rowposition[i]] = true;
        countqueen += 1;
        colour.push_back(array[i][rowposition[i]]);
        i += 1;
        count++;


        for (int k = 0 ; k < n ; k++){
            for (int l = 0 ; l < n ; l++){
                if (queen[k][l] == true){
                    cout << "X";
                }else{
                    cout << array[k][l];
                }
            }
            cout << endl; 
        }
        cout << endl;
    }

    cout << "Hasil Akhir : \n";

    for (int k = 0 ; k < n ; k++){
        for (int l = 0 ; l < n ; l++){
            if (queen[k][l] == true){
                cout << "X";
            }else{
                cout << array[k][l];
            }
        }
        cout << endl; 
    }
    cout << endl << "Banyak kasus yang ditinjau: " << count << endl;

    auto finish = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    cout << "Waktu eksekusi brute force: " << duration << " ms" << endl;

    char choice;
    cout << "Apakah ingin menyimpan hasil ke folder result? (y/n): ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y'){
        string resultName;
        cout << "Masukkan nama file (tanpa .txt): ";
        cin >> resultName;

        filesystem::path resultLoc = filesystem::current_path() / "result";
        filesystem::create_directories(resultLoc);
        filesystem::path outPath = resultLoc / (resultName + ".txt");
        ofstream out(outPath);
        for (int k = 0 ; k < n ; k++){
            for (int l = 0 ; l < n ; l++){
                if (queen[k][l] == true){
                    out << "X";
                }else{
                    out << array[k][l];
                }
            }
            out << endl; 
        }
        out << endl;
        cout << "Hasil disimpan di " << outPath << endl;
    }
    return;
}

bool nextCombination(vector<int>& col, int n) {
    int i = 0;
    while (i < col.size()) {
        if (col[i] + 1 < n) {
            ++col[i];
            return true;
        }
        col[i] = 0;
        ++i;
    }
    return false; 
}


bool isValid(const vector<int>& col, const vector<vector<char>>& array){
    int n = array.size();
    vector<bool> queenCol(n, false);
    unordered_set<char> colours;

    for (int i = 0; i < n; ++i){

        if (col[i] < 0 || col[i] >= n){
            return false;
        }

        if (queenCol[col[i]]){
            return false;
        }
        queenCol[col[i]] = true;

        char colour = array[i][col[i]];
        if (colours.count(colour)){
            return false;
        }
        colours.insert(colour);

        if (i > 0 && abs(col[i] - col[i - 1]) == 1){
            return false;
        }
    }

    return true;
}


void printResult(const vector<int>& col, const vector<vector<char>>& array){
    int n = array.size();
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            if (col[i] == j){
                cout << 'X';
            }else{
                cout << array[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;
}


void solutionBruteForce(vector<vector<char>> array){
    int n = array.size();
    vector<int> col(n, 0);
    long long count = 0;
    auto start = chrono::high_resolution_clock::now();

    do {
        ++count;
        if (isValid(col, array)){
            cout << "Hasil Akhir (brute force):" << endl;
            printResult(col, array);
            cout << "Banyak kasus yang ditinjau : " << count << endl;
            auto finish = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
            cout << "Waktu eksekusi brute force: " << duration << " ms" << endl;
            char choice;
            cout << "Apakah ingin menyimpan hasil ke folder result? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y'){
                string resultName;
                cout << "Masukkan nama file (tanpa .txt): ";
                cin >> resultName;

                filesystem::path resultLoc = filesystem::current_path() / "result";
                filesystem::create_directories(resultLoc);
                filesystem::path outPath = resultLoc / (resultName + ".txt");
                ofstream out(outPath);
                for (int i = 0; i < n; ++i){
                    for (int j = 0; j < n; ++j){
                        if (col[i] == j){
                            out << 'X';
                        }else{
                            out << array[i][j];
                        }
                    }
                    out << endl;
                }
                out << endl;
                cout << "Hasil disimpan di " << outPath << endl;
            }
            return;
        }
        if (count % 1000 == 0){
            cout << "Sudah meninjau " << count << " kasus." << endl;
            printResult(col, array);
        }
    } while (nextCombination(col, n));

    cout << "Tidak ada solusi dengan brute force." << endl;
    cout << "Banyak kasus yang ditinjau : " << count << endl;
    auto finish = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(finish - start).count();
    cout << "Waktu eksekusi brute force: " << duration << " ms" << endl;

}


int main() {
    string filename;
    cout<<"Masukkan nama file yang ingin dibuka: ";
    cin>>filename;

    vector<vector<char>> array;
    if (!salin(filename, array)) {
        return 1;
    }

    int pilihan;
    cout << "Pilih metode penyelesaian:\n";
    cout << "1. Optimisasi (backtracking)\n";
    cout << "2. Brute force murni\n";
    cout << "Masukkan pilihan (1/2): ";
    cin >> pilihan;

    cout << endl;

    if (pilihan == 2){
        solutionBruteForce(array);
    }else if (pilihan == 1){
        solutionOptimization(array);
    }else{
        cout << "Pilihan tidak valid." << endl;
        return 1;
    }
    return 0;
}