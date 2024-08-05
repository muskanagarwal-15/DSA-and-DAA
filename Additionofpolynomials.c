#include<stdio.h>
struct terms{
    int coeff, exp;
};
typedef struct polynomial{
    int n_term;
    struct terms term[10];
}poly;
int main(){
    poly p[10];
    int n_poly,n_term,total_terms;
    printf("How many polynomials?");
    scanf("%d",&n_poly);
    int i,j,m,k;
    for(i=0;i<n_poly;i++){
	printf("\nEnter the %dth polynomial",i+1);
	printf("\nHow many terms?");
	scanf("%d",&p[i].n_term);
	for(j=0;j<p[i].n_term;j++){
            printf("\nEnter coeff and exp");
            scanf("%d %d",&p[i].term[j].coeff,&p[i].term[j].exp);
	}
    }
    for(i=0;i<n_poly;i++){
	printf("Polynomial %d\n", i+1);
	for(j=0;j<p[i].n_term;j++){
	    if(p[i].term[j].exp==0) // for displaying constants
	    printf("%d",p[i].term[j].coeff);
	else
	    printf("%dx^%d",p[i].term[j].coeff,p[i].term[j].exp);
	if(j<p[i].n_term-1) 
	printf(" + ");
	}
	printf("\n");
    }
    for(i=0;i<n_poly;i++){
	for(m=0;m<p[i].n_term;m++){
	    for(j=i+1;j<n_poly;j++){
	    	for(k=0;k<p[j].n_term;k++){
		    if(p[i].term[m].coeff>0 && p[j].term[k].coeff>0 &&(p[i].term[m].exp==p[j].term[k].exp)){
			p[i].term[m].coeff+= p[j].term[k].coeff;
			p[j].term[k].coeff=0;
		    }
		}
	    }
	}
    }
    printf("\nAdded Polynomial is:");
    for(i=0;i<n_poly;i++){
	for(j=0;j<p[i].n_term;j++){
	    if (p[i].term[j].coeff!=0){
		if (p[i].term[j].exp==0)
		printf("%d + ",p[i].term[j].coeff);
	    else if (j == p[i].n_term - 1) 
		printf("%dx^%d  ",p[i].term[j].coeff,p[i].term[j].exp);
	    else 
	        printf("%dx^%d + ",p[i].term[j].coeff,p[i].term[j].exp);
  	    }
	}
    }
}