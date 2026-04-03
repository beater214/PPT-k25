#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int poly_n;
double poly_a[100];

double f_poly(double x) {
    double p = poly_a[0];
    for (int i = 1; i <= poly_n; i++) {
        p = p * x + poly_a[i];
    }
    return p;
}

double f1_sv(double x) { return exp(x) - 3.0 * x; }
double g1_sv(double x) { return exp(x) / 3.0; }

double f2_sv(double x) { return x - cos(x); }
double g2_sv(double x) { return cos(x); }

double f3_sv(double x) { return sin(x) - cos(x); }

double f4_sv(double x) { return pow(x, 3) - x - 1; }
double g4_sv(double x) { return cbrt(x + 1.0); }

void dl3(double a[], int n, double *x1, double *x2) {
    double m1 = fabs(a[n]);
    double m2 = fabs(a[0]);
    for (int i = 1; i < n; i++){
        double x = fabs(a[i]);
        if (x > m1) m1 = x;
        if (x > m2) m2 = x;
    }
    double an = fabs(a[n]);
    *x1 = an / (m2 + an);
    *x2 = 1 + m1 / fabs(a[0]);
}

int dl4(double a[], int n, double *N) {
    double b[100];
    for (int i = 0; i <= n; i++) b[i] = a[i];
    if (b[0] < 0) {
        for (int i = 0; i <= n; i++) b[i] = -b[i];
    }
    int m = -1;
    for (int i = 0; i <= n; i++){
        if (b[i] < 0){ m = i; break; }
    }
    if (m == -1) return -1;
    double ma = b[m];
    for(int i = m + 1; i <= n; i++){
        if (b[i] < 0 && ma > b[i]) ma = b[i];
    }
    *N = 1 + pow(-ma/b[0], 1.0/m);
    return 1;
}

void phi1(double a[], int n, double f[]) {
    for (int i = 0; i <= n; i++) f[i] = a[n-i];
}

void phi2(double a[], int n, double f[]) {
    int d = (n & 1 ? -1 : 1);
    for (int i = 0; i <= n; i++){
        f[i] = a[i] * d;
        d = -d;
    }
}

void phi3(double a[], int n, double f[]){
    int d = (n & 1 ? -1 : 1);
    for (int i = 0; i <= n; i++){
        f[i] = d * a[n-i];
        d = -d;
    }
}

void dl5(double a[], int n, double *x1, double *x2, double *x3, double *x4, int *am, int *duong) {
    double f[100], n0, n1, n2, n3;
    if (a[0] > 0 && dl4(a, n, &n0) != -1) { *x2 = n0; *duong = 1; } 
    else *x2 = 1e18;
    
    phi1(a, n, f);
    if (f[0] > 0 && dl4(f, n, &n1) != -1) *x1 = 1.0/n1;
    else *x1 = 0;
    
    phi2(a, n, f);
    if (f[0] > 0 && dl4(f, n, &n2) != -1) { *x3 = -n2; *am = 1; } 
    else *x3 = -1e18;
    
    phi3(a, n, f);
    if (f[0] > 0 && dl4(f, n, &n3) != -1) *x4 = -1.0/n3;
    else *x4 = 0;
}

double hoocne_tinh_gia_tri(double a[], int n, double c){
    double p = a[0];
    for (int i = 1; i <= n; i++) p = p * c + a[i];
    return p;
}

void hoocnetq(double a[], double b[], int n, double c){
    double p = 1;
    for(int i = 0; i <= n; i++) b[i] = a[i];
    for(int i = n; i >= 1; i--){
        p = b[0];
        for(int j = 1; j <= i; j++){
            p = p * c + b[j];
            b[j] = p;
        }
    }
}

void in_da_thuc_hoocner(double b[], int n, double c){
    printf("\n=> Da thuc moi P(y");
    if (c < 0) printf(" - %g", -c);
    else if (c > 0) printf(" + %g", c);
    printf("):\n   ");
    
    int first = 1;
    for (int i = 0; i <= n; i++) {
        int po = n - i; 
        double heso = fabs(b[i]);
        if (b[i] == 0) continue;
        
        if (first) {
            if (b[i] < 0) printf("-");
            first = 0;
        } else {
            if (b[i] > 0) printf(" + ");
            else printf(" - ");
        }
        
        if (heso != 1 || po == 0) printf("%g", heso);
        if (po > 0) printf("y");
        if (po > 1) printf("^%d", po);
    }
    printf("\n");
}

void pp_chia_doi(double (*f)(double)) {
    double a, b, eps, c;
    printf("Nhap khoang phan ly nghiem [a, b]:\n");
    printf("a = "); scanf("%lf", &a);
    printf("b = "); scanf("%lf", &b);
    printf("Nhap sai so (eps): "); scanf("%lf", &eps);
    
    if (f(a) * f(b) >= 0) {
        printf("\nf(a) va f(b) cung dau! Khong du dieu kien chia doi.\n");
        return;
    }
    
    printf("\n%-5s | %-12s | %-12s | %-12s | %-12s\n", "Buoc", "a", "b", "c", "f(c)");
    printf("----------------------------------------------------------------\n");
    
    int buoc = 1;
    while (fabs(b - a) > eps) {
        c = (a + b) / 2.0;
        printf("%-5d | %-12.6lf | %-12.6lf | %-12.6lf | %-12.6lf\n", buoc++, a, b, c, f(c));
        
        if (f(c) == 0) break;
        if (f(a) * f(c) < 0) b = c;
        else a = c;
    }
    printf("----------------------------------------------------------------\n");
    printf("\n=> Nghiem gan dung: x = %lf\n", c);
}

void pp_day_cung(double (*f)(double)) {
    double a, b, eps, x;
    printf("Nhap khoang phan ly nghiem [a, b]:\n");
    printf("a = "); scanf("%lf", &a);
    printf("b = "); scanf("%lf", &b);
    printf("Nhap sai so (eps): "); scanf("%lf", &eps);
    
    if (f(a) * f(b) >= 0) {
        printf("\nf(a) va f(b) cung dau! Khong the dung day cung.\n");
        return;
    }
    
    printf("\n%-5s | %-15s | %-15s\n", "Buoc", "x", "Sai so |f(x)|");
    printf("-----------------------------------------\n");
    int j = 1;
    do {
        x = a - (f(a) * (b - a)) / (f(b) - f(a));
        printf("%-5d | %-15.6lf | %-15.6lf\n", j, x, fabs(f(x)));
        
        if (f(a) * f(x) < 0) b = x;
        else a = x;
        
        j++;
        if (j > 1000) {
            printf("\nPhuong trinh phan ky hoac lap vo han!\n");
            return;
        }
    } while (fabs(f(x)) > eps);
    printf("-----------------------------------------\n");
    printf("\n=> Nghiem gan dung: x = %lf\n", x);
}

void pp_lap(double (*g)(double)) {
    double x0, eps, x, y, hieu;
    printf("Nhap gia tri bat dau x0: "); scanf("%lf", &x0);
    printf("Nhap sai so (eps): "); scanf("%lf", &eps);
    
    x = x0;
    int lap = 1, max_lap = 100;
    printf("\n%-5s | %-15s | %-15s | %-15s\n", "Buoc", "x", "g(x)", "Sai so");
    printf("----------------------------------------------------------\n");
    
    do {
        y = g(x);
        hieu = fabs(y - x);
        printf("%-5d | %-15.6lf | %-15.6lf | %-15.6lf\n", lap, x, y, hieu);
        x = y; 
        lap++;
    } while (hieu >= eps && lap <= max_lap);
    
    if (lap > max_lap) {
        printf("\nQua so lan lap cho phep! Ham g(x) co the khong hoi tu.\n");
    } else {
        printf("----------------------------------------------------------\n");
        printf("\n=> Nghiem gan dung: x = %lf\n", x);
    }
}

void in_da_thuc(double a[], int n) {
    printf("P(x) = ");
    int first = 1, zr = 1;
    for (int i = 0; i <= n; i++) if (a[i] != 0) zr = 0;
    if (zr) { printf("0\n"); return; }
    
    for (int i = 0; i <= n; i++) {
        int bac = n - i;
        if (a[i] == 0) continue;
        if (first) {
            if (a[i] < 0) printf("-");
            first = 0;
        } else {
            if (a[i] > 0) printf(" + ");
            else printf(" - ");
        }
        double heso = fabs(a[i]);
        if (bac == 0) printf("%g", heso);
        else {
            if (heso != 1) printf("%g", heso);
            if (bac == 1) printf("x");
            else printf("x^%d", bac);
        }
    }
    printf("\n");
}

void nhap_da_thuc() {
    printf("\n--- NHAP DA THUC P(X) ---\n");
    printf("Nhap bac cua da thuc: ");
    while (scanf("%d", &poly_n) != 1 || poly_n <= 0) {
        printf("Bac phai la so nguyen > 0. Nhap lai: ");
        while(getchar() != '\n'); 
    }
    printf("Nhap cac he so tu bac %d xuong bac 0:\n", poly_n);
    for (int i = 0; i <= poly_n; i++) {
        printf("He so a[%d] (tuong ung x^%d): ", i, poly_n - i);
        scanf("%lf", &poly_a[i]);
    }
    if (poly_a[0] == 0) {
        printf("\nCanh bao: He so a[0] = 0 khong tao thanh da thuc bac %d dung nghia.\n", poly_n);
    }
}

void menu_dai_so() {
    nhap_da_thuc();
    while(1) {
        printf("\n");
        printf("==========================================\n");
        printf("      XU LY PHUONG TRINH DAI SO P(X)      \n");
        printf("==========================================\n");
        in_da_thuc(poly_a, poly_n);
        printf("\n");
        printf(" 1. Tim khoang phan ly nghiem (DL 3, 4, 5)\n");
        printf(" 2. Tinh toan voi Hoocner\n");
        printf(" 3. Tim nghiem bang PP Chia Doi\n");
        printf(" 4. Tim nghiem bang PP Day Cung\n");
        printf(" 5. Nhap lai da thuc khac\n");
        printf(" 0. Quay lai menu chinh\n");
        printf("------------------------------------------\n");
        
        int chon;
        printf("Nhap lua chon cua ban: ");
        if (scanf("%d", &chon) != 1) {
            while(getchar() != '\n'); continue;
        }
        
        if (chon == 0) break;
        
        switch(chon) {
            case 1: {
                printf("\n--- KIEM TRA KHOANG NGHIEM ---\n");
                double x1, x2, x3, x4, N;
                int am = 0, duong = 0;
                dl3(poly_a, poly_n, &x1, &x2);
                printf("+ DL3 (Moi nghiem x deu thuoc): %g <= |x| <= %g\n", x1, x2);
                
                if (dl4(poly_a, poly_n, &N) != -1)
                    printf("+ DL4 (Can tren nghiem duong): N = %g\n", N);
                else printf("+ DL4: Khong co can tren nghiem duong!\n");
                
                dl5(poly_a, poly_n, &x1, &x2, &x3, &x4, &am, &duong);
                if (duong) printf("+ DL5 (Khoang nghiem duong): (%g, %g)\n", x1, x2);
                if (am) printf("+ DL5 (Khoang nghiem am): (%g, %g)\n", x3, x4);
                break;
            }
            case 2: {
                printf("\n--- SO DO HOOCNER ---\n");
                double c;
                printf("Nhap gia tri c: "); scanf("%lf", &c);
                printf("Gia tri P(%g) = %g\n", c, hoocne_tinh_gia_tri(poly_a, poly_n, c));
                
                double b[100];
                hoocnetq(poly_a, b, poly_n, c);
                in_da_thuc_hoocner(b, poly_n, c);
                break;
            }
            case 3:
                printf("\n--- PP CHIA DOI ---\n");
                pp_chia_doi(f_poly);
                break;
            case 4:
                printf("\n--- PP DAY CUNG ---\n");
                pp_day_cung(f_poly);
                break;
            case 5:
                nhap_da_thuc();
                break;
            default:
                printf("Lua chon khong hop le!\n");
        }
    }
}

void menu_sieu_viet() {
    while(1) {
        printf("\n");
        printf("==========================================\n");
        printf("     GIAI PHUONG TRINH CO SAN (F(x)=0)    \n");
        printf("==========================================\n");
        printf(" 1. f(x) = e^x - 3x\n");
        printf(" 2. f(x) = x - cos(x)\n");
        printf(" 3. f(x) = sin(x) - cos(x)\n");
        printf(" 4. f(x) = x^3 - x - 1\n");
        printf(" 0. Quay lai menu chinh\n");
        printf("------------------------------------------\n");
        
        int chon_ham;
        printf("Chon phuong trinh: ");
        if (scanf("%d", &chon_ham) != 1) {
            while(getchar() != '\n'); continue;
        }
        if (chon_ham == 0) break;
        if (chon_ham < 1 || chon_ham > 4) {
            printf("Lua chon khong hop le!\n");
            continue;
        }
        
        printf("\n--- CHON PHUONG PHAP GIAI ---\n");
        printf(" 1. PP Chia doi\n");
        printf(" 2. PP Day cung\n");
        if (chon_ham != 3) printf(" 3. PP Lap\n"); 
        
        int chon_pp;
        printf("Nhap phuong phap: ");
        scanf("%d", &chon_pp);
        
        double (*ham_f)(double) = NULL;
        double (*ham_g)(double) = NULL;
        
        if (chon_ham == 1) { ham_f = f1_sv; ham_g = g1_sv; }
        else if (chon_ham == 2) { ham_f = f2_sv; ham_g = g2_sv; }
        else if (chon_ham == 3) { ham_f = f3_sv; ham_g = NULL; }
        else if (chon_ham == 4) { ham_f = f4_sv; ham_g = g4_sv; }
        
        if (chon_pp == 1) pp_chia_doi(ham_f);
        else if (chon_pp == 2) pp_day_cung(ham_f);
        else if (chon_pp == 3 && ham_g != NULL) pp_lap(ham_g);
        else printf("Phuong phap khong hop le hoac chua duoc ho tro cho ham nay!\n");
    }
}

int main() {
    while(1) {
        printf("\n");
        printf("##########################################\n");
        printf("#       HE THONG GIAI PHUONG TRINH       #\n");
        printf("##########################################\n");
        printf("# 1. Giai phuong trinh Da Thuc (Dai So)  #\n");
        printf("# 2. Giai phuong trinh Sieu Viet / Mau   #\n");
        printf("# 0. Thoat chuong trinh                  #\n");
        printf("##########################################\n");
        
        int lc;
        printf("=> Nhap lua chon cua ban: ");
        if (scanf("%d", &lc) != 1) {
            while(getchar() != '\n'); continue;
        }
        
        if (lc == 0) {
            printf("Tam biet! Hen gap lai.\n");
            break;
        }
        else if (lc == 1) menu_dai_so();
        else if (lc == 2) menu_sieu_viet();
        else printf("Lua chon khong hop le!\n");
    }
    return 0;
}
