#include <stdio.h>
#include <math.h>
#define EXP 0.001
void fx(int n, int a[]) {
    int i;
    
    printf("Nhap he so mu:\n");
    for (i = 0; i <= n; i++) {
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }
    
    printf("f(x) = ");
    int first_term = 1; 
    int b = n;          
    
    for (i = 0; i <= n; i++) {
        if (a[i] == 0) {
            b--;
            continue; 
        }
        if (first_term) {   
            if (a[i] < 0) printf("-");
            first_term = 0; 
        } else {
            if (a[i] > 0) printf(" + ");
            else printf(" - ");
        }
        int abs_coeff = a[i] < 0 ? -a[i] : a[i];   
        
        if (b == 0) {           
            printf("%d", abs_coeff);
        } else {          
            if (abs_coeff != 1) {
                printf("%d*", abs_coeff);   
            }

            if (b == 1) {
                printf("x");      
            } else {
                printf("x^%d", b); 
            }
        }
        b--;
    }
    
    if (first_term == 1) {
        printf("0");
    }
    printf("\n");
}

int main() {
    int n;
    int a[100]; 
    
    printf("Nhap co so mu: ");
    scanf("%d", &n);
    //Nhap ham fx
    fx(n, a);
    //Xet khoang nghiem
    float x1, x2;
    int i;
    float kqx1 ,kqx2;
    printf("Nhap khoang nghiem phuong trinh tren:\n");
    do{
    	kqx1 = 0;
        printf("Nhap x1 = "); scanf("%f", &x1);
    	for(i = 0; i <= n; i++) {
        	  kqx1 += a[i] * pow(x1, n - i); 
    	}
	}while (kqx1 >= 0 );
	do{
    	kqx2 = 0;
        printf("Nhap x2 = "); scanf("%f", &x2);
    	for(i = 0; i <= n; i++) {
        	  kqx2 += a[i] * pow(x2, n - i);
    	}
	}while (kqx2 <= 0 );
    printf("\nKet qua tinh toan:\n");
    printf("f(%f) = %f\n", x1, kqx1);
    printf("f(%f) = %f\n", x2, kqx2);
    //Phuong phap chia doi 
    float c;
    while (fabs(x2-x1) > EXP){
    	 c=((x1+x2)/2);
    	float kq = 0;
    	for(i = 0; i <= n; i++) {
        	  kq += a[i] * pow(c, n - i);
    	}
    	if(kq < 0) x1=c;
		else x2=c ;
	}
	printf("Vay nghiem cua phuong trinh tren la: %f",c);
    
    return 0;
}
