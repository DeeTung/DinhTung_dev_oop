#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct DonThuc {
    double heso;
    int somu;
};

struct DaThuc {
    vector<DonThuc> CacDonThuc;
};

DaThuc *Nhap() {
    DaThuc* dt = new DaThuc;
    int n;
    cout << "Nhap so luong don thuc: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        DonThuc don;
        cout << "Nhap he so va so mu cua don thuc thu " << i + 1 << ": ";
        cin >> don.heso >> don.somu;
        dt->CacDonThuc.push_back(don);
    }
    return dt;
}

void Xuat(const DaThuc& dt) {
    bool first = true;
    for (int i = 0; i < dt.CacDonThuc.size(); i++){
        const DonThuc &don1 = dt.CacDonThuc[i];
        if (don1.heso == 0) continue; 
        if (!first) {
            cout << (don1.heso < 0 ? "-" : "+");
        } else {
            if (don1.heso < 0) cout << "-";
            first = false;
        }
        if (abs(don1.heso) != 1 || don1.somu == 0) {
            cout << abs(don1.heso);
        }
        if (don1.somu != 0) {
            cout << "x";
            if (don1.somu != 1) {
                cout << "^" << don1.somu;
            }
        }
    }
    if (first) { 
        cout << "0";
    }
    cout << endl;
}

double TinhDaThuc(const DaThuc& dt, double x) {
    double res = 0;
    for (int i = 0; i < dt.CacDonThuc.size(); i++){
        const DonThuc &don2 = dt.CacDonThuc[i];
        res += don2.heso * pow(x, don2.somu);
    }
    return res;
}

DaThuc TinhTong (const DaThuc& A, const DaThuc &B){
    DaThuc res;
    int i = 0, j = 0;
    while (i < A.CacDonThuc.size() && j < B.CacDonThuc.size()){
        if (A.CacDonThuc[i].somu > B.CacDonThuc[j].somu){
            res.CacDonThuc.push_back(A.CacDonThuc[i]);
            i++;
        }
        if (A.CacDonThuc[i].somu < B.CacDonThuc[j].somu){
            res.CacDonThuc.push_back(B.CacDonThuc[j]);
            j++;
        }
        if (A.CacDonThuc[i].somu == B.CacDonThuc[j].somu){
            double tongheso = A.CacDonThuc[i].heso + B.CacDonThuc[j].heso;
            if (tongheso != 0) res.CacDonThuc.push_back({tongheso, A.CacDonThuc[i].somu});
            i++; j++;
        }
    }
    while (i < A.CacDonThuc.size()){
        res.CacDonThuc.push_back(A.CacDonThuc[i]);
    }
    while (j < B.CacDonThuc.size()){
        res.CacDonThuc.push_back(B.CacDonThuc[j]);
    }
    return res;
}

DaThuc TinhHieu (const DaThuc& A, const DaThuc &B){
    DaThuc res;
    int i = 0, j = 0;
    while (i < A.CacDonThuc.size() && j < B.CacDonThuc.size()){
        if (A.CacDonThuc[i].somu > B.CacDonThuc[j].somu){
            res.CacDonThuc.push_back(A.CacDonThuc[i]);
            i++;
        }
        if (A.CacDonThuc[i].somu < B.CacDonThuc[j].somu){
            res.CacDonThuc.push_back(B.CacDonThuc[j]);
            j++;
        }
        if (A.CacDonThuc[i].somu == B.CacDonThuc[j].somu){
            double tongheso = A.CacDonThuc[i].heso - B.CacDonThuc[j].heso;
            if (tongheso != 0) res.CacDonThuc.push_back({tongheso, A.CacDonThuc[i].somu});
            i++; j++;
        }
    }
    while (i < A.CacDonThuc.size()){
        res.CacDonThuc.push_back(A.CacDonThuc[i]);
    }
    while (j < B.CacDonThuc.size()){
        res.CacDonThuc.push_back(B.CacDonThuc[j]);
    }
    return res;
}

bool SoSanhDonThuc(const DonThuc& A, const DonThuc& B) {
    return A.somu > B.somu; 
}

DaThuc GopDaThuc (const DaThuc& dt){
    DaThuc res = dt;
    sort(res.CacDonThuc.begin(), res.CacDonThuc.end(), SoSanhDonThuc);
    vector <DonThuc> gop;
    for (size_t i = 0; i < res.CacDonThuc.size(); ++i) {
        if (gop.empty() || gop.back().somu != res.CacDonThuc[i].somu) {
            gop.push_back(res.CacDonThuc[i]);
        } else {
            gop.back().heso += res.CacDonThuc[i].heso;
        }
    }
    res.CacDonThuc = gop;
    return res;
}


DaThuc TinhTich (const DaThuc& A, const DaThuc &B){
    DaThuc res;
    for (int i = 0; i < A.CacDonThuc.size(); i++){
        for (int j = 0; j < B.CacDonThuc.size(); j++){
            DonThuc tich;
            tich.heso = A.CacDonThuc[i].heso * B.CacDonThuc[j].heso;
            tich.somu = A.CacDonThuc[i].somu + B.CacDonThuc[j].somu;
            res.CacDonThuc.push_back(tich);
        }
    }
    return GopDaThuc(res);
}

int main() {
    DaThuc* A = Nhap();
    DaThuc* B = Nhap();
    cout << "Da thuc vua nhap la: ";
    Xuat(*A);
    Xuat(*B);
    double x;
    cout << "\nNhap gia tri x: ";
    cin >> x;
    cout << "\nVoi x = " << x << ", gia tri da thuc la: " << setprecision(5) << TinhDaThuc(*A, x) << " va " << TinhDaThuc(*B, x) << endl;
    cout << "Tong cua 2 da thuc la: ";
    Xuat(TinhTong(*A, *B)); cout << endl;
    cout << "Hieu cua 2 da thuc la: ";
    Xuat(TinhHieu(*A, *B)); cout << endl;
    cout << "Tich cua 2 da thuc la: ";
    Xuat(TinhTich(*A, *B)); cout << endl;
    return 0;
}
