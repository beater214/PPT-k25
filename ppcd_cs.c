#include <stdio.h>
#define EXP 0.001
#include <math.h>

int main (){
	int lua_chon;
	float a,b,c,f1,f2,kq,f;
	do {
		printf("============================================\n");
		printf("Nhap lua chon cua ban: \n");
		printf("\n");
		printf("1.f(x)= x^3 - 4x -9 \n");
		printf("2.f(x)= e^x - 3x \n");
		printf("3.f(x)= sin(x) - cos(x) \n");
		printf("4.Thoat chuong trinh \n");
		printf("\n");
		printf("Nhap: ");
		scanf("%d",&lua_chon);
		
		switch (lua_chon){
			case 1:{
				printf("Nhap khoang nghiem : \n");
				printf("a = ");
				scanf("%f",&a );
				printf("b = ");
				scanf("%f",&b );
				f1 = pow(a,3) - 4*a -9 ;
				f2 = pow(b,3) - 4*b -9 ;
				printf("Thay a vao f(x)= %f \n",f1);
				printf("Thay b vao f(x)= %f \n",f2);
				while ((fabs(b-a)) > EXP){
					c = (a+b)/2.0 ;
					f = pow(c,3) - 4*c -9 ;
					if (f1 * f < 0) b=c;
					else {
						a=c;
						f1=f;
					}
				}
				printf("\n");
				printf("Nghiem cua phuong trinh nay la: %f\n",c);
				printf("\n");
				break;
			}
			case 2:{
				printf("Nhap khoang nghiem : \n");
				printf("a = ");
				scanf("%f",&a );
				printf("b = ");
				scanf("%f",&b );
				f1 = exp(a) - 3*a ;
				f2 = exp(b) - 3*b ;
				printf("Thay a vao f(x)= %f \n",f1);
				printf("Thay b vao f(x)= %f \n",f2);
				while ((fabs(b-a)) > EXP){
					c = (a+b)/2.0 ;
					f = exp(c) - 3*c ;
					if (f1 * f < 0) b=c;
					else {
						a=c;
						f1=f;
					}
				}
				printf("\n");
				printf("Nghiem cua phuong trinh nay la: %f\n",c);
				printf("\n");
				break;
			}
			case 3:{
				printf("Nhap khoang nghiem : \n");
				printf("a = ");
				scanf("%f",&a );
				printf("b = ");
				scanf("%f",&b );
				f1 = sin(a) - cos(a) ;
				f2 = sin(b) - cos(b) ;
				printf("Thay a vao f(x)= %f \n",f1);
				printf("Thay b vao f(x)= %f \n",f2);
				while ((fabs(b-a)) > EXP){
					c = (a+b)/2.0 ;
					f = sin(c) - cos(c) ;
					if (f1 * f < 0) b=c;
					else {
						a=c;
						f1=f;
					}
				}
				printf("\n");
				printf("Nghiem cua phuong trinh nay la: %f\n",c);
				printf("\n");
				break;
			}
			default :
				if (lua_chon != 4) {
					printf("\nLua chon khong hop le !\n");
				} else {
					printf("\nCam on ban !\n");
				}
				break;
		}
	}while (lua_chon != 4);
	return 0;
}
