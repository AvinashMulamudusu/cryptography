#include<stdio.h>
#include<conio.h>
#include<math.h>
int main(){
        int q,b,Xa,Xb,Ya,Yb,K1,K2,temp1,temp2,temp3,temp4;
        printf("Enter the value of q : ");
        scanf("%d",&q);
        printf("Enter the value of alpha : ");
        scanf("%d",&b);
        printf("Enter the value of Xa : ");
        scanf("%d",&Xa);
        printf("Enter the value of Xb : ");
        scanf("%d",&Xb);
        temp1=(pow(b,Xa));
        Ya=temp1%q;
        printf("Ya = %d\n",Ya);
        temp2=(pow(b,Xb));
        Yb=temp2%q;
        printf("Yb = %d\n",Yb);
        temp3=(pow(Yb,Xa));
        K1=temp3%q;
        temp4=(pow(Ya,Xb));
        K2=temp4%q;
        if(K1==K2){
                printf("The value of K = %d",K1);
        }
        return 0;
}
