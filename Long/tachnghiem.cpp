#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void input(double a[], int *n) {
    printf("Nhap bac da thuc cua ham p(x): ");
    if (scanf("%d", n) != 1) {
        printf("Bac da thuc phai la so nguyen!\n");
        exit(1);
    }
    if (*n <= 0) {
        printf("Bac da thuc n phai lon hon 0!\n");
        exit(1);
    }
    printf("Nhap %d he so (tu bac cao nhat den bac 0): ", *n + 1);
    for (int i = 0; i <= *n; i++) {
        if (scanf("%lf", &a[i]) != 1) {
            printf("He so a[%d] khong hop le\n", i);
            exit(1);
        }
    }
    if (fabs(a[0]) < 1e-9) {
        printf("a[0] phai khac 0\n");
        exit(1);
    }
}

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
    for (int i = 0; i <= n; i++)
        b[i] = a[i];
        
    if (b[0] < 0)
        for (int i = 0; i <= n; i++)
            b[i] = -b[i];
    
    int m = -1;
    for (int i = 0; i <= n; i++){
        if (b[i] < 0){
            m = i;
            break;
        }
    }
    
    if (m == -1)
        return -1;
        
    double ma = b[m];
    for(int i = m + 1; i <= n; i++)
        if (b[i] < 0 && ma > b[i])
            ma = b[i];
            
    *N = 1 + pow(-ma/b[0], 1.0/m);
    return 1;
}

void phi1(double a[], int n, double f[]) {
    for (int i = 0; i <= n; i++)
        f[i] = a[n-i];
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
    double f[100];
    double n0, n1, n2, n3;
    if (a[0] > 0 && dl4(a, n, &n0) != -1) {
        *x2 = n0;
        *duong = 1;
    } else *x2 = 1e18;
    
    phi1(a, n, f);
    if (f[0] > 0 && dl4(f, n, &n1) != -1) {
        *x1 = 1.0/n1;
    } else
        *x1 = 0;
    
    phi2(a, n, f);
    if (f[0] > 0 && dl4(f, n, &n2) != -1) {
        *x3 = -n2;
        *am = 1;
    } else
        *x3 = -1e18;
    
    phi3(a, n, f);
    if (f[0] > 0 && dl4(f, n, &n3) != -1)
        *x4 = -1.0/n3;
    else
        *x4 = 0;
}

void menu() {
    printf("1. Tim khoang nghiem (dinh li 3)\n");
    printf("2. Tim can tren cua nghiem duong (dinh li 4)\n");
    printf("3. Tim khoang nghiem (dinh li 5)\n");
    printf("4. Nhap mot da thuc khac\n");
    printf("0. Thoat!\n");
}

int main(){
    int n;
    double a[100];
    input(a, &n);
    menu();
    while(1){
        int lc;
        printf("Nhap lua chon: ");
        if (scanf("%d", &lc) != 1) {
            printf("Lua chon khong hop le, vui long nhap lai\n");
            while (getchar() != '\n'); 
            continue;
        }
        if (lc < 0 || lc > 4) {
            printf("Lua chon khong hop le, vui long nhap lai\n");
            continue;
        }
        printf("\n");
        if(lc == 0) break;
        if(lc == 1){
            double x1, x2;
            dl3(a, n, &x1, &x2);
            printf("Khoang nghiem cua pt : %g <= |x| <= %g\n\n", x1 ,x2);
        }
        if(lc == 2){
            double N;
            int check = dl4(a, n, &N);
            if (check == -1)
                printf("pt khong co can tren cua nghiem duong!\n\n");
            else
                printf("Can tren cua nghiem duong: N = %g\n\n", N);
        }
        if(lc == 3){
            int am = 0, duong = 0;
            double x1, x2, x3, x4;
            dl5(a, n, &x1, &x2, &x3, &x4, &am, &duong);
            
            if(duong)
                printf("Khoang nghiem duong: (%g, %g)\n", x1, x2);
            else
                printf("Khong xac dinh duoc nghiem duong!\n");

            if(am)
                printf("Khoang nghiem am: (%g, %g)\n\n", x3, x4);
            else
                printf("Khong xac dinh duoc nghiem am!\n\n");
        }
        if (lc == 4) {
            input(a, &n);
        }
    }
    return 0;
}
