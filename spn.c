#include<stdio.h>
#include<math.h>
#include<stdlib.h>
void binary(unsigned int); 
void sbox_f();
void pbox_f();
void sbox_d(int []);
void pbox_d(int []);
void decrypt();

int sbox[16][4]= {{1,1,1,0},{0,1,0,0},{1,1,0,1},{0,0,0,1},{0,0,1,0},{1,1,1,1},{1,0,1,1},{1,0,0,0},{0,0,1,1},{1,0,1,0},{0,1,1,0},{1,1,0,0},
{0,1,0,1},{1,0,0,1},{0,0,0,0},{0,1,1,1}};

int sbox_decr[16][4]= {{1,1,1,0},{0,0,1,1},{0,1,0,0},{1,0,0,0},{0,0,0,1},{1,1,0,0},{1,0,1,0},{1,1,1,1},{0,1,1,1},{1,1,0,1},{1,0,0,1},{0,1,1,0},
{1,0,1,1},{0,0,1,0},{0,0,0,0},{0,1,0,1}};

int pbox[16]={1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
//int pbox_decr[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int outsbox[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int outpbox[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//int outsbox_decr[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//int outpbox_decr[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int a[100],j,r,i=0,xor[16],x=0,r1[16],rpbox[16];
int key[5][16]={{0,0,1,1,1,0,1,0,1,0,0,1,0,1,0,0},{1,0,1,0,1,0,0,1,0,1,0,0,1,1,0,1},{1,0,0,1,0,1,0,0,1,1,0,1,0,1,1,0},{0,1,0,0,1,1,0,1,0,1,1,0,0,0,1,1},{1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1}};
void main()
{
	unsigned int num;
	printf("Enter Plaintext in decimal : ");
	scanf("%u",&num);
	binary(num); // Function Call
	//while(round<5) {
	printf("\n\n-------ENCRYPTION-----\n\n");
	    printf("key: ");
	  for(r=0;r<4;r++){
	    printf("\nRound %d:\nkey:",r+1);
	    for(j=0;j<16;j++)
                printf("%d",key[r][j]);
	    printf("\n");

	    for(j=0;j<i;j++)
		xor[x++]=a[j]^key[r][j];
	    printf("xor operation: ");
	    for(j=0;j<x;j++)
	       printf("%d",xor[j]);
	     printf("\n");

	    sbox_f();
            pbox_f();
            printf("sbox_out=");
            for(i=0;i<16;i++) {
                printf("%d ",outsbox[i]);
            }
            printf("\n");
	 if(r<3) {
	    printf("pbox_out=");
	    
            for(i=0;i<16;i++) {
                printf("%d ",outpbox[i]);
            }
	    }
	    for(i=0;i<16;i++)
	        a[i]=outpbox[i];
            printf("\n");
	    //round++;
	    x=0;
	    }
	 for(j=0;j<16;j++)
                xor[x++]=outsbox[j]^key[r][j];
	 printf(" Ciphertext: ");
         for(i=0;i<16;i++) {
                printf("%d ",xor[i]);
         }
	 printf("\n\n----DECRYPTION----\n");
	decrypt();

}
void binary(unsigned int num)
{
	unsigned int mask=32768; 
	printf("Binary Equivalent of Plaintext : ");
	while(mask > 0)
	 {
	 if((num & mask) == 0 )
	 {
	printf("0");
	 a[i++]=0;
	 }
	 else
         {
	 printf("1");
	 a[i++]=1;
	 }
	mask = mask >> 1 ; // Right Shift
	 }
	printf("\n");
	for(j=0;j<i;j++)
	    printf("%d",a[j]);
	printf("\n");
}
void sbox_f() {
        int i,j,k,l,m,sum=0,count=-1,n=3;
        for(i=0;i<16;i++) {
                sum = sum + (xor[i]*pow(2,n));
                if (n==0) {
                        //printf("sum=%d\n",sum);
                        //printf("sbox_4bits=");
                        //for(m=0;m<4;m++)
                        //        printf("%d,",sbox[sum][m]);
//                        printf("\n");
                        l=i-3;
                        for(k=0;k<4;k++) {
                                outsbox[l]=sbox[sum][k];
                                l++;
                        }
                        sum=0;
                        n=3;
                }
                else {
                        n--;
                }
        }
}
void pbox_f() {
        int i;
        for (i=0;i<16;i++) {
                outpbox[(pbox[i]-1)]=outsbox[i];
        }
	
}

void decrypt()
{
	int r,j,x=0;
	for(r=4;r>0;r--) {
            printf("\n------key:");
            for(j=0;j<16;j++)
		printf("%d",key[r][j]);
            printf("\n");
            for(j=0;j<16;j++)
                r1[x++]=xor[j]^key[r][j];

	    printf("xor of key and text:");
	    for(j=0;j<16;j++)
                printf("%d",r1[j]);
	    printf("\n");

	    if(r!=4){
	    	pbox_d(r1);
		for(i=0;i<16;i++){
                    r1[i]=rpbox[i];
                }

	    	sbox_d(r1);
	    }
	    else
		sbox_d(r1);
	    for(i=0;i<16;i++){
               xor[i]=outsbox[i];
             }
	     x=0;

	}
	printf("\n\nplain text: ");
	for(i=0;i<16;i++){
             printf("%d",xor[i]^key[r][i]);
        }
	printf("\n");

}

void sbox_d(int r1[16])
{
	int i,j,k,l,m,sum=0,count=-1,n=3;
        for(i=0;i<16;i++) {
                sum = sum + (r1[i]*pow(2,n));
                if (n==0) {
                        //printf("sum=%d\n",sum);
                        printf("sbox_4bits=");
                        for(m=0;m<4;m++)
                                printf("%d,",sbox_decr[sum][m]);
                        printf("\n");
                        l=i-3;
                        for(k=0;k<4;k++) {
                                outsbox[l]=sbox_decr[sum][k];
                                l++;
                        }
                        sum=0;
                        n=3;
                }
                else {
                        n--;
                }
        }

	
}

void pbox_d(int r1[16])
{
	int i;
        for (i=0;i<16;i++) {
                rpbox[(pbox[i]-1)]=r1[i];
        }
	printf("pbox: ");
	for (i=0;i<16;i++) 
	    printf("%d",rpbox[i]);
	printf("\n");
}
