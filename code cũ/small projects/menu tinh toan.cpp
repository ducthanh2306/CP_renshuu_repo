#include <stdio.h> // khong viet hoa chu cai dau trong prinf
#include <math.h>  // quen ko co break
int main(){        //loi cu phap khi dung %d cho a,b (double)
	double result; //chua hieu dieu kien chia cho khong phai la b(so bi chia)==0
	int choice;    //input scanf thi ghi nhu printf:))
	double a, b;
	printf (" chao ban den voi menu tinh toan cua chung toi\n");
	printf(" hay nhap gia tri cua a: ");
	scanf("%lf",&a );
	printf(" ok tiep tuc, hay nhap gia tri cua b: ");
	scanf("%lf",&b );
	printf(" ban co 4 lua chon:\n");
	printf(" 1. Tinh tong a + b\n");
	printf(" 2. Tinh hieu a - b\n");
	printf(" 3. Tinh tich a * b\n");
	printf(" 4. Tinh thuong a / b\n");
	printf(" hay lua chon phep tinh can tinh: ");
    recalculation:
	scanf("%d",&choice);
	switch(choice){
		case 1:
			result = a + b;
			 printf (" %.2lf + %.2lf = %.2lf. Vay ket qua la %.2lf", a ,b, result, result);
			 break;
             
		case 2: 
		result = a - b;
			 printf (" %.2lf - %.2lf = %.2lf. Vay ket qua la %.2lf", a ,b, result, result);
			 break;
             
		case 3: 
		result = a * b;
			 printf (" %.2lf * %.2lf = %.2lf. Vay ket qua la %.2lf", a ,b, result, result);
			 break;
             
		case 4: 
		if (b !=0){
		result = a / b;
			 printf (" %.2lf / %.2lf = %.2lf. Vay ket qua la %.2lf", a ,b, result, result);
             
		} else{
			printf(" m ngu vi chia cho 0");
            
		}
		break;
		default:
			printf(" lua chon ko hop le");
			
	}
    printf("\n ban co tiep tuc tinh ? hay chon lai: ");
    goto recalculation;
}