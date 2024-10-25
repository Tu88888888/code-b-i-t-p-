#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 // phấn 1. Khai báo cấu trúc dữ liệu cho bài toán

typedef struct Ngay // Lưu trữ thông tin ngày sinh kiểu struct
{
    int ngay, thang, nam; // Khoi tạo biến interger cho ngay rhansg và năm
} Ngay;

typedef struct Sinhvien // Cau truc liuu trữ thông tin sinh vien
{
   char msSV[100];
   char hoTen[100];
   int gioiTinh;
   Ngay ngaySinh;
   char diaChi[100];
   char lop[100];
   char khoa[100];
} Sinhvien;

typedef struct Node  // Cấu trúc 1 nút
{
    Sinhvien data;
    struct Node *link;

} Node;

typedef struct list
{
    struct Node *first; // con trỏ trỏ tới nút đầu tiên
    struct Node *last; // con trỏ trỏ tới nút cuối
} list;

 // phần 2. Nhập vào Danh sách sinh viên ListSV, và in ra Danh sách sinh viên được sắp xếp tăng dần theo mã sinh viên.
 // VÀ, Hãy viết hàm thêm một sinh viên mới vào danh sách ListSV đã sắp xếp và SV được sắp xếp theo đúng thứ tự ở DS mới

 //ham khoi tao danh sách
 void initList( list*l) //hàm nhận con trỏ l trỏ tới cấu trúc list
 {
       l->first = NULL; // ban đầu danh sách rỗng
       l->last = NULL; // ban đầu danh sách rỗng
 }

 // ham tao 1 nút mới chúa thông tin sv

 Node *createNode(Sinhvien sv) // trả về 1 con trỏ trỏ tới 1 đối tượng có cấu trúc là node
 {
     Node *newNode = (Node*)malloc(sizeof(Node)); // yêu cầu cấp phát động để chứa 1 node, vì node mới là khởi tạo 1 con trỏ, cho nên ép kiểu (NOde*)
    newNode->data = sv;// Gán dữ liệu sinh viên (sv) vào thuộc tính data của newNode, data là data của nút nới
    newNode->link = NULL; // gán con trỏ nút mới ( phần liên kết)  = NULL
    return newNode; // TRẢ về địa chỉ của nút mới vừa được tạo
 }
 // HÀm nhạp thong tin sinh vine
 Sinhvien nhapSinhvien() {

    Sinhvien sv;
    printf("Nhap ma so sinh vien: ");
    scanf("%s", sv.msSV);
    printf("Nhap ho ten: ");
    scanf(" %[^\n]", sv.hoTen);
    printf("Nhap gioi tinh (0: Nu, 1: Nam): ");
    scanf("%d", &sv.gioiTinh);
    printf("Nhap ngay sinh (ngay/thang/nam): ");
    scanf("%d/%d/%d", &sv.ngaySinh.ngay, &sv.ngaySinh.thang, &sv.ngaySinh.nam);
    printf("Nhap dia chi: ");
    scanf(" %[^\n]", sv.diaChi);
    printf("Nhap lop: ");
    scanf("%s", sv.lop);
    printf("Nhap khoa: ");
    scanf("%s", sv.khoa);
    return sv;
}

//Hàm thêm sinh viên vào danh sách và sắp xếp theo mã sinh viên
void themSinhvien(list *l, Sinhvien sv) {
    Node* newNode = createNode(sv);
    // Trường hợp danh sách rỗng
    if (l->first == NULL || strcmp(sv.msSV, l->first->data.msSV) < 0) {
        newNode->link = l->first;
        l->first = newNode;
        if (l->last == NULL) {
            l->last = newNode;
        }
        return;
    }

    // Trường hợp thêm vào vị trí giữa hoặc cuối danh sách
    Node* nuthientai = l->first;
    while (nuthientai->link != NULL && strcmp(nuthientai->link->data.msSV, sv.msSV) < 0) {
        nuthientai = nuthientai->link;
    }
    newNode->link = nuthientai->link;
    nuthientai->link = newNode;
    if (newNode->link == NULL) {
        l->last = newNode;
    }
}

// Phần 3. Loại bỏ các sinh viên có cùng ngày sinh ra khỏi danh sách ListSV
// Hàm in sinh viên cùng ngày sinh

void inSinhvienCungNgaySinh(list l, Ngay ngaySinh) {
    Node* p = l.first;
    int found = 0;
    while (p != NULL) {
        if (p->data.ngaySinh.ngay == ngaySinh.ngay &&
            p->data.ngaySinh.thang == ngaySinh.thang &&
            p->data.ngaySinh.nam == ngaySinh.nam) {

            printf("Ma SV: %s\n", p->data.msSV);
            printf("Ho ten: %s\n", p->data.hoTen);
            printf("Dia chi: %s\n", p->data.diaChi);

            found = 1;
        }
        p = p->link;
    }
    if (!found) {
        printf("Khong tim thay sinh vien cung ngay sinh.\n");
    }
}

// PHẦN 4. Loại bỏ các sinh viên có cùng ngày sinh ra khỏi danh sách ListSV
//Hàm xóa sinh viên có cùng ngày sinh
void xoaSinhvienCungNgaySinh(list *l, Ngay ngaySinh) {
    Node *nuthientai = l->first;
    Node *nutquakhu = NULL;

    while (nuthientai != NULL) {
        // dieu kiện check nếu sinh viên trung lặp có cùng ngày sinh
        if (nuthientai->data.ngaySinh.ngay == ngaySinh.ngay &&
            nuthientai->data.ngaySinh.thang == ngaySinh.thang &&
            nuthientai->data.ngaySinh.nam == ngaySinh.nam) {

            if (nutquakhu == NULL) {
                l->first = nuthientai->link;  // Xóa nút đầu tiên
            } else {
                nutquakhu->link = nuthientai->link; // Xóa nút ở giữa hoặc cuối
            }

            // Nếu xóa nút cuối cùng
            if (nuthientai->link == NULL) {
                l->last = nutquakhu;
            }

            // Giải phóng bộ nhớ
            Node* temp = nuthientai;
            nuthientai = nuthientai->link;
            free(temp);
        } else {
            // Duyệt đến nút tiếp theo
            nutquakhu = nuthientai;
            nuthientai = nuthientai->link;
        }
    }
}


//ket hop tat ca vao ham main
int main() {
    list danhSach;
    initList(&danhSach);

    // Nhập sinh viên
    int n;
    printf("Nhap so luong sinh vien: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Sinhvien sv = nhapSinhvien();
        themSinhvien(&danhSach, sv);
    }

    // In danh sách sinh viên
    printf("\nDanh sach sinh vien:\n");
    printlist(danhSach);

    // Tìm sinh viên cùng ngày sinh
    Ngay ngaySinh;
    printf("\n Nhap ngay thang năm: ");
    scanf("%d/%d/%d", &ngaySinh.ngay, &ngaySinh.thang, &ngaySinh.nam);

    printf("\n Sinh vien cung ngay sinh:\n");
    inSinhVienCungNgaySinh(danhSach, ngaySinh);

    printf("\n Xoa sinh vien cung ngay sinh\n");
    xoaSinhVienCungNgaySinh(&danhSach, ngaySinh);// Xóa sinh viên cùng ngày sinh
    printf("\n Danh sach sinh vien sau khi xoa:\n");
    printlist(danhSach);// In lại danh sách sau khi xóa

    return 0;
}


