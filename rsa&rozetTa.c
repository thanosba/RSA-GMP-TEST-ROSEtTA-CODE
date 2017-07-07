#include<stdio.h> 
#include<curses.h> 
#include<stdlib.h> 
#include<math.h> 
#include<string.h>
#include <gmp.h>
 
long int p,q,n,t,flag,e[100],d[100],temp[100],j,m[100],en[100],i; 
char msg[100]; 
int prime(long int); 
void ce(); 
long int cd(long int); 
void encrypt(); 
void decrypt();
int main() {
clear(); 
  
int input ;  
 
printf("Press 1 or 2 : ");
scanf( "%d", &input );

if (input ==1) {
printf("\nENTER FIRST PRIME NUMBER\n"); 
scanf("%d",&p); 
flag=prime(p); 
if(flag==0) 
{ 
    printf("\nWRONG INPUT\n"); 
    getch(); 
    exit(1); 
} 
printf("\nENTER ANOTHER PRIME NUMBER\n"); 
scanf("%d",&q); 
flag=prime(q); 
if(flag==0||p==q) 
{ 
    printf("\nWRONG INPUT\n"); 
    getch(); 
    exit(1); 
} 
printf("\nENTER MESSAGE\n"); 
fflush(stdin); 
scanf("%s",msg); 
for(i=0;msg[i]!=NULL;i++) 
m[i]=msg[i]; 
n=p*q; 
t=(p-1)*(q-1); 
ce(); 
printf("\nPOSSIBLE VALUES OF e AND d ARE\n"); 
for(i=0;i<j-1;i++) 
printf("\n%ld\t%ld",e[i],d[i]); 
encrypt(); 
decrypt(); 
getch(); 
 
}

if (input ==2) {
mpz_t n, d, e, pt, ct;
 
    mpz_init(pt);
    mpz_init(ct);
    mpz_init_set_str(n, "9516311845790656153499716760847001433441357", 10);
    mpz_init_set_str(e, "65537", 10);
    mpz_init_set_str(d, "5617843187844953170308463622230283376298685", 10);
 
    const char *plaintext = “XXXXXXXX”;
    mpz_import(pt, strlen(plaintext), 1, 1, 0, 0, plaintext);
 
    if (mpz_cmp(pt, n) > 0)
        abort();
 
    mpz_powm(ct, pt, e, n);
    gmp_printf("Encoded:   %Zd\n", ct);
 
    mpz_powm(pt, ct, d, n);
    gmp_printf("Decoded:   %Zd\n", pt);
 
    char buffer[64];
    mpz_export(buffer, NULL, 1, 1, 0, 0, pt);
    printf("As String: %s\n", buffer);
 
    mpz_clears(pt, ct, n, e, d, NULL);
 } 
return 0 ;
}

int prime(long int pr) 
{ 
int i; 
j=sqrt(pr); 
for(i=2;i<=j;i++) 
{ 
    if(pr%i==0) 
    return 0; 
} 
return 1; 
} 
void ce() 
{ 
int k; 
k=0; 
for(i=2;i<t;i++) 
{ 
    if(t%i==0) 
    continue; 
    flag=prime(i); 
    if(flag==1&&i!=p&&i!=q) 
    { 
        e[k]=i; 
        flag=cd(e[k]); 
        if(flag>0) 
        { 
            d[k]=flag; 
            k++; 
        } 
        if(k==99) 
        break; 
    } 
} 
} 
long int cd(long int x) 
{ 
long int k=1; 
while(1) 
{ 
    k=k+t; 
    if(k%x==0) 
    return(k/x); 
} 
} 
void encrypt() 
{ 
long int pt,ct,key=e[0],k,len; 
i=0; 
len=strlen(msg); 
while(i!=len) 
{ 
    pt=m[i]; 
    pt=pt-96; 
    k=1; 
    for(j=0;j<key;j++) 
    { 
        k=k*pt; 
        k=k%n; 
    } 
    temp[i]=k; 
    ct=k+96; 
    en[i]=ct; 
    i++; 
} 
en[i]=-1; 
printf("\nTHE ENCRYPTED MESSAGE IS\n"); 
for(i=0;en[i]!=-1;i++) 
printf("%c",en[i]); 
} 
void decrypt() 
{ 
long int pt,ct,key=d[0],k; 
i=0; 
while(en[i]!=-1) 
{ 
    ct=temp[i]; 
    k=1; 
    for(j=0;j<key;j++) 
    { 
        k=k*ct; 
        k=k%n; 
    } 
    pt=k+96; 
    m[i]=pt; 
    i++; 
} 
m[i]=-1; 
printf("\nTHE DECRYPTED MESSAGE IS\n"); 
for(i=0;m[i]!=-1;i++) 
printf("%c",m[i]); 
}

