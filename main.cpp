#include <iostream>

using namespace std;

struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

void init(List &l) {
    l.first = l.last = NULL;
}

int soSanhMa(char s1[], char s2[]) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

bool laTrungNgay(Ngay n1, Ngay n2) {
    return (n1.ngay == n2.ngay && n1.thang == n2.thang && n1.nam == n2.nam);
}

void insertSorted(List &l, SinhVien sv) {
    Node* p = new Node;
    p->data = sv;
    p->link = NULL;

    if (l.first == NULL || soSanhMa(sv.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        if (l.last == NULL) l.last = p;
    } else {
        Node* curr = l.first;
        while (curr->link != NULL && soSanhMa(curr->link->data.maSV, sv.maSV) < 0) {
            curr = curr->link;
        }
        p->link = curr->link;
        curr->link = p;
        if (p->link == NULL) l.last = p;
    }
}

void inCungNgaySinh(List l) {
    bool coTrung = false;
    for (Node* p = l.first; p != NULL; p = p->link) {
        bool timThayCap = false;
        for (Node* q = l.first; q != NULL; q = q->link) {
            if (p != q && laTrungNgay(p->data.ngaySinh, q->data.ngaySinh)) {
                timThayCap = true;
                break;
            }
        }
        if (timThayCap) {
            cout << "Trung NS: " << p->data.maSV << " - " << p->data.hoTen << endl;
            coTrung = true;
        }
    }
    if (!coTrung) cout << "khong tim thay sinh vien cung ngay sinh" << endl; //
}

void xoaTrungNgaySinh(List &l) {
    if (l.first == NULL) return;

    Node* curr = l.first;
    Node* prev = NULL;

    while (curr != NULL) {
        bool biTrung = false;
        for (Node* temp = l.first; temp != NULL; temp = temp->link) {
            if (curr != temp && laTrungNgay(curr->data.ngaySinh, temp->data.ngaySinh)) {
                biTrung = true;
                break;
            }
        }

        if (biTrung) {
            Node* toDelete = curr;
            if (prev == NULL) {
                l.first = curr->link;
                curr = l.first;
            } else {
                prev->link = curr->link;
                curr = prev->link;
            }
            if (toDelete == l.last) l.last = prev;
            delete toDelete;
        } else {
            prev = curr;
            curr = curr->link;
        }
    }
}


void nhapSV(SinhVien &sv) {
    cout << "Ma SV: "; cin >> sv.maSV;
    cin.ignore();
    cout << "Ho ten: "; cin.getline(sv.hoTen, 50);
    cout << "Gioi tinh (0-Nu, 1-Nam): "; cin >> sv.gioiTinh;
    cout << "Ngay sinh (dd mm yyyy): "; cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore();
    cout << "Lop: "; cin >> sv.lop;
    cout << "Khoa: "; cin >> sv.khoa;
}

void xuatDS(List l) {
    if (l.first == NULL) {
        cout << "(Danh sach trong)" << endl;
        return;
    }
    for (Node *p = l.first; p != NULL; p = p->link) {
        cout << "[" << p->data.maSV << "] " << p->data.hoTen
             << " | NS: " << p->data.ngaySinh.ngay << "/" << p->data.ngaySinh.thang << "/" << p->data.ngaySinh.nam << endl;
    }
}

int main() {
    List ds;
    init(ds);
    int n;
    cout << "So luong SV: "; cin >> n;

    for(int i = 0; i < n; i++) {
        SinhVien sv;
        cout << "\nNhap SV " << i+1 << ":\n";
        nhapSV(sv);
        insertSorted(ds, sv);
    }

    cout << "\n--- DANH SACH DA SAP XEP ---" << endl;
    xuatDS(ds);

    cout << "\n--- KIEM TRA NGAY SINH BI TRUNG ---" << endl;
    inCungNgaySinh(ds);

    cout << "\n--- TIEN HANH XOA TRUNG NGAY SINH ---" << endl;
    xoaTrungNgaySinh(ds);

    cout << "\n--- DANH SACH SAU KHI XOA ---" << endl;
    xuatDS(ds);

    return 0;
}
