#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
// CÂU 1: Định nghĩa cấu trúc Khách hàng
// ==========================================
struct KhachHang {
    int maKH;               // Mã khách hàng (kiểu số nguyên)
    string tenKH;           // Tên khách hàng (kiểu chuỗi)
    string soDienThoai;     // Số điện thoại (kiểu chuỗi)
    double tongTien;        // Tổng tiền thanh toán (kiểu số)
};

// ==========================================
// CÂU 2: Viết hàm nhập mảng n khách hàng
// ==========================================
void nhapDS(vector<KhachHang> &ds, int n) {
    for (int i = 0; i < n; i++) {
        KhachHang kh;
        cout << "\n--- Nhap thong tin khach hang thu " << i + 1 << " ---\n";
        
        cout << "Ma khach hang (So nguyen): ";
        cin >> kh.maKH;
        
        cin.ignore(); // Xóa bộ nhớ đệm trước khi nhập chuỗi
        cout << "Ten khach hang: ";
        getline(cin, kh.tenKH);
        
        cout << "So dien thoai: ";
        getline(cin, kh.soDienThoai);
        
        cout << "Tong tien thanh toan: ";
        cin >> kh.tongTien;
        
        ds.push_back(kh);
    }
}

// ==========================================
// CÂU 3: Viết hàm xuất mảng n khách hàng
// ==========================================
void xuatKhachHang(const KhachHang &kh) {
    cout << left << setw(10) << kh.maKH 
         << setw(25) << kh.tenKH 
         << setw(15) << kh.soDienThoai 
         << right << setw(15) << fixed << setprecision(2) << kh.tongTien << endl;
}

void xuatDS(const vector<KhachHang> &ds) {
    cout << "\n" << string(65, '=') << endl;
    cout << left << setw(10) << "Ma KH" 
         << setw(25) << "Ten Khach Hang" 
         << setw(15) << "So Dien Thoai" 
         << right << setw(15) << "Tong Tien" << endl;
    cout << string(65, '-') << endl;
    
    for (const auto &kh : ds) {
        xuatKhachHang(kh);
    }
    cout << string(65, '=') << endl;
}

// ==========================================
// CÂU 4: Thuật toán Sắp xếp chèn trực tiếp (Insertion Sort)
// Sắp xếp tăng dần theo Tổng tiền thanh toán
// ==========================================
void insertionSort(vector<KhachHang> &ds) {
    int n = ds.size();
    for (int i = 1; i < n; i++) {
        KhachHang key = ds[i];
        int j = i - 1;

        // Dời các phần tử có tongTien lớn hơn key.tongTien về phía sau
        while (j >= 0 && ds[j].tongTien > key.tongTien) {
            ds[j + 1] = ds[j];
            j--;
        }
        ds[j + 1] = key;
    }
}

// ==========================================
// CÂU 5: Tìm kiếm nhị phân (Chia để trị)
// Tìm các khách hàng có tổng tiền thanh toán bằng X
// ==========================================
int binarySearchFirst(const vector<KhachHang> &ds, double X) {
    int left = 0, right = ds.size() - 1;
    int res = -1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ds[mid].tongTien == X) {
            res = mid;
            right = mid - 1; // Tiếp tục tìm vị trí đầu tiên phía bên trái
        } else if (ds[mid].tongTien < X) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return res;
}

void timKiemTheoTongTien(const vector<KhachHang> &ds, double X) {
    int firstIdx = binarySearchFirst(ds, X);
    
    if (firstIdx == -1) {
        cout << "\n[!] Khong tim thay khach hang nao co tong tien thanh toan bang " << X << endl;
        return;
    }
    
    cout << "\n=== DANH SACH KHACH HANG CO TONG TIEN BANG " << X << " ===";
    cout << "\n" << string(65, '=') << endl;
    cout << left << setw(10) << "Ma KH" 
         << setw(25) << "Ten Khach Hang" 
         << setw(15) << "So Dien Thoai" 
         << right << setw(15) << "Tong Tien" << endl;
    cout << string(65, '-') << endl;
    
    // In toàn bộ các khách hàng liên tiếp có cùng tổng tiền X
    for (int i = firstIdx; i < (int)ds.size() && ds[i].tongTien == X; i++) {
        xuatKhachHang(ds[i]);
    }
    cout << string(65, '=') << endl;
}

// ==========================================
// CÂU 6: Hàm chính (main)
// ==========================================
int main() {
    int n;
    vector<KhachHang> ds;

    // 1. Nhập n khách hàng và hiển thị các khách hàng vừa nhập
    cout << "Nhap so luong khach hang n: ";
    cin >> n;
    while (n <= 0) {
        cout << "So luong phai > 0. Nhap lai n: ";
        cin >> n;
    }

    nhapDS(ds, n);

    cout << "\n=== DANH SACH KHACH HANG VUA NHAP ===";
    xuatDS(ds);

    // 2. Sắp xếp n khách hàng theo chiều tăng dần của tổng tiền thanh toán bằng Insertion Sort
    insertionSort(ds);
    cout << "\n=== DANH SACH KHACH HANG SAU KHI SAP XEP TANG DAN THEO TONG TIEN ===";
    xuatDS(ds);

    // 3. Sử dụng hàm tìm kiếm hiển thị các khách hàng có tổng tiền thanh toán bằng X
    double X;
    cout << "\nNhap tong tien thanh toan X can tim: ";
    cin >> X;
    timKiemTheoTongTien(ds, X);

    return 0;
}
