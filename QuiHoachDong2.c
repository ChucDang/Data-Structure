#include<stdio.h>
#include<malloc.h>
typedef int Bang[50][100];
typedef struct{
	char ten[25];
	int TL, GT,SL;
	float DG;
	int PA;
}DoVat;
DoVat *Read(int *n, int *TL){
	FILE *f=fopen("QHD_CaiBalo2.inp","r");
	int i=0;
	fscanf(f,"%d",TL);
	DoVat *dsdv=(DoVat *)malloc(sizeof(DoVat));
	while(!feof(f)){
		fscanf(f,"%d%d%d%[^\n]",&dsdv[i].TL, &dsdv[i].GT,&dsdv[i].SL, &dsdv[i].ten);
		dsdv[i].DG=dsdv[i].GT*1.0/dsdv[i].TL;
		dsdv[i].PA=0;
		i++;
		dsdv=(DoVat *)realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	*n=i-2;
	fclose(f);
	return dsdv;
}
void swap(DoVat *a, DoVat *b){
	DoVat temp;
	temp =*a;
	*a=*b;
	*b=temp;
}
int min(int a, int b){
	return a> b?b:a;
}
void TaoBang(DoVat *dsdv,int n,int W, Bang F,Bang X){
 	int xk, yk, k;
 	int FMax, XMax, V;
// Dien h�ng dau tien cua hai bang
 	for(V= 0; V<=W; V++) {
 		int temp = min(V/dsdv[0].TL,dsdv[0].SL);
 		X[0][V] = temp;
 		F[0][V] = X[0][V] * dsdv[0].GT;
 	}
// �ien c�c d�ng c�n lai
 	for(k= 1; k<=n; k++){
 		for(V=0; V<=W; V++) {
 			FMax = F[k-1][V] ;
 			XMax = 0;
 			yk=min(dsdv[k].SL, V/dsdv[k].TL);
 			for(xk = 1; xk<=yk; xk++)
 				if(F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT>FMax){
 					FMax=F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
 					XMax= xk;
 				}
 			F[k][V] = FMax;
 			X[k][V] = XMax;
 		}
	}
}
void InBang(int n, int W, Bang F, Bang X){
	int V, k;
	for(k=0; k<=n; k++){
 		for(V=0; V<=W; V++){
 			printf("|%4d%2d",F[k][V], X[k][V]);
		 }
 		printf("\n");	
 	}
}
void TraBang(DoVat *dsdv, int n, int W, Bang X) {
 	int k, V;
 	V = W;
 	for(k= n; k>=0; k--) {
 		dsdv[k].PA = X[k][V];
 		V = V - X[k][V] * dsdv[k].TL;
 	}
}
void main(){
	DoVat *dsdv;
	int n,TGT = 0, TTL=0, i, TL;
	dsdv=Read(&n, &TL);
	Bang F,X;
	TaoBang(dsdv, n,TL,F,X);
	printf("Bang du lieu: \n");
	InBang(n,TL,F,X);
	printf("Danh sach truoc khi sap xep la: \n");
	printf("|    Ten do vat   |  Trong luong | Gia tri | So luong | Don gia | Phuong an|\n");
	TraBang(dsdv,n,TL,X);
	for(i=0; i<=n; i++){
		TGT+=dsdv[i].PA*dsdv[i].GT;
		TTL+=dsdv[i].PA*dsdv[i].TL;
		printf("|%17s|%14d|%9d|%10d|%9.2f|%10d|\n", dsdv[i].ten, dsdv[i].TL, dsdv[i].GT,dsdv[i].SL,dsdv[i].DG, dsdv[i].PA);
	}
	printf("X={");
	for(i=0; i<=n; i++){
		printf(" %d",dsdv[i].PA);
	}
	printf("}\n");
	printf("Tong gia tri: %d\n", TGT);
	printf("Tong trong luong: %d\n", TTL);
	free(dsdv);
}
