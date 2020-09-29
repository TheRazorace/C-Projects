#include <stdio.h>
#include <stdlib.h>

void gates(){
	char log[10];
	scanf("%s", &log);
	if(strcmp(log,"not")==0){
		printf("0 : 1\n");
		printf("1 : 0\n");
	}
	else if(strcmp(log,"and")==0){
		printf("0 0 : 0\n");
		printf("0 1 : 0\n");
		printf("1 0 : 0\n");
		printf("1 1 : 1\n");
	}
	else if(strcmp(log,"or")==0){
		printf("0 0 : 0\n");
		printf("0 1 : 1\n");
		printf("0 1 : 1\n");
		printf("1 1 : 1\n");
	}
	else if(strcmp(log,"xor")==0){
		printf("0 0 : 0\n");
		printf("0 1 : 1\n");
		printf("1 0 : 1\n");
		printf("1 1 : 0\n");
	}
	else if(strcmp(log,"nand")==0){
		printf("0 0 : 1\n");
		printf("0 1 : 1\n");
		printf("1 0 : 1\n");
		printf("1 1 : 0\n");
	}
	else if(strcmp(log,"nor")==0){
		printf("0 0 : 1\n");
		printf("0 1 : 0\n");
		printf("1 0 : 0\n");
		printf("1 1 : 0\n");
	}
	else if(strcmp(log,"xnor")==0){
		printf("0 0 : 1\n");
		printf("0 1 : 0\n");
		printf("1 0 : 0\n");
		printf("1 1 : 1\n");
	}
	else{
		printf("Wrong word! Try again.\n");
		gates();
	}
	
}

void specific_gates(){
	char log[10];
	int n1,n2;
	while(1){
	scanf("%s", &log);
    if(strcmp(log,"and")==0){
		scanf("%d ", &n1);
		scanf("%d", &n2);
		if(n1==0 && n2==0) printf("and out 0\n");
		else if(n1==0 && n2==1) printf("and out 0\n");
		else if(n1==1 && n2==0) printf("and out 0\n");
		else if(n1==1 && n2==1) printf("and out 1\n");
        else printf("uknown gate\n");
	}
	else if(strcmp(log,"or")==0){
		scanf("%d ", &n1);
		scanf("%d", &n2);
		if(n1==0 && n2==0) printf("or out 0\n");
		else if(n1==0 && n2==1) printf("or out 1\n");
		else if(n1==1 && n2==0) printf("or out 1\n");
		else if(n1==1 && n2==1) printf("or out 1\n");
        else printf("uknown gate\n");
	}
	else if(strcmp(log,"xor")==0){
		scanf("%d ", &n1);
		scanf("%d", &n2);
		if(n1==0 && n2==0) printf("xor out 0\n");
		else if(n1==0 && n2==1) printf("xor out 1\n");
		else if(n1==1 && n2==0) printf("xor out 1\n");
		else if(n1==1 && n2==1) printf("xor out 0\n");
        else printf("uknown gate\n");
	}
	else if(strcmp(log,"nand")==0){
		scanf("%d ", &n1);
		scanf("%d", &n2);
		if(n1==0 && n2==0) printf("nand out 1\n");
		else if(n1==0 && n2==1) printf("nand out 1\n");
		else if(n1==1 && n2==0) printf("nand out 1\n");
		else if(n1==1 && n2==1) printf("nand out 0\n");
        else printf("uknown gate\n");
	}
	else if(strcmp(log,"nor")==0){
		scanf("%d ", &n1);
		scanf("%d", &n2);
		if(n1==0 && n2==0) printf("nor out 1\n");
		else if(n1==0 && n2==1) printf("nor out 0\n");
		else if(n1==1 && n2==0) printf("nor out 0\n");
		else if(n1==1 && n2==1) printf("nor out 0\n");
        else printf("uknown gate\n");
	}
	else if(strcmp(log,"xnor")==0){
		scanf("%d ", &n1);
		scanf("%d", &n2);
		if(n1==0 && n2==0) printf("xnor out 1\n");
		else if(n1==0 && n2==1) printf("xnor out 0\n");
		else if(n1==1 && n2==0) printf("xnor out 0\n");
		else if(n1==1 && n2==1) printf("xnor out 1\n");
        else printf("uknown gate\n");
	}else{
		printf("Wrong word! Try again.\n");
		break;
	}}
}

void circuit(){
	int n1,n2,n3,n4,n5;
	int p1,p2,p3,p4;
	while(1){
	scanf("%d", &n1);
	if(n1!=0 && n1!=1){
		printf("Invalid number!\n");
		break;
	}
	scanf("%d", &n2);
		if(n2!=0 && n2!=1){
		printf("Invalid number!\n");
		break;
	}
	scanf("%d", &n3);
		if(n3!=0 && n3!=1){
		printf("Invalid number!\n");
		break;
	}
	scanf("%d", &n4);
		if(n4!=0 && n4!=1){
		printf("Invalid number!\n");
		break;
	}
	scanf("%d", &n5);
		if(n5!=0 && n5!=1){
		printf("Invalid number!\n");
		break;
	}
		if(n1==0 && n2==0) p1=0;
		if(n1==0 && n2==1) p1=0;
		if(n1==1 && n2==0) p1=0;
		if(n1==1 && n2==1) p1=1;
		
		if(n3==0 && n4==0) p2=0;
		if(n3==0 && n4==1) p2=1;
		if(n3==1 && n4==0) p2=1;
		if(n3==1 && n4==1) p2=0;
		
		if(p1==0 && p2==0) p3=1;
		if(p1==0 && p2==1) p3=1;
		if(p1==1 && p2==0) p3=1;
		if(p1==1 && p2==1) p3=0;
		
		if(p3==0 && n5==0) p4=0;
		if(p3==0 && n5==1) p4=1;
		if(p3==1 && n5==0) p4=1;
		if(p3==1 && n5==1) p4=1;
		printf("out : %d\n",p4);
	}
}

void file_inputs(){
	char title[20];
	int in,out,i=0,r=0,k=0,l=0,row=0,w;
	int n1,n2,n3,n4,n5;
	int p1,p2,p3,p4;
	FILE *fp;
	printf("Choose the name of the file you want to read(add <.txt> at the end):");
	scanf("%s", &title);
	fp=fopen(title,"r");
	if(fp == NULL){
		printf("No such file exists. Try again!\n");
		file_inputs();
	}
	fscanf (fp, "%d", &in);  
	printf("%d\n", in);
	fscanf (fp, "%d", &out);  
	printf("%d\n", out);
	if(in==2){
		while(!feof(fp)){
			fscanf (fp, "%d", &n1);
			printf("%d ", n1);
			fscanf (fp, "%d", &n2);
			printf("%d ", n2);
			fscanf (fp, "%d", &p1);
			printf("%d ", p1);
			row++;
			if(n1==0 && n2==0 && p1!=0) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(n1==0 && n2==1 && p1!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(n1==1 && n2==0 && p1!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(n1==1 && n2==1 && p1!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else printf("\n");
			
		}
	}else if(in==3){
		while(!feof(fp)){
			fscanf (fp, "%d", &n1);
			printf("%d ", n1);
			fscanf (fp, "%d", &n2);
			printf("%d ", n2);
			fscanf (fp, "%d", &n3);
			printf("%d ", n3);
			fscanf (fp, "%d", &p2);
			printf("%d ", p2);
			row++;
			
			if(n1==0 && n2==0) p1=1;
		    if(n1==0 && n2==1) p1=1;
		    if(n1==1 && n2==0) p1=1;
		    if(n1==1 && n2==1) p1=0;
		    
		    if(p1==0 && n3==0 && p2!=0) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p1==0 && n3==1 && p2!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p1==1 && n3==0 && p2!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p1==1 && n3==1 && p2!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else printf("\n");
			
		}
	}else if(in==4){
		while(!feof(fp)){
			fscanf (fp, "%d", &n1);
			printf("%d ", n1);
			fscanf (fp, "%d", &n2);
			printf("%d ", n2);
			fscanf (fp, "%d", &n3);
			printf("%d ", n3);
			fscanf (fp, "%d", &n4);
			printf("%d ", n4);
			fscanf (fp, "%d", &p3);
			printf("%d ", p3);
			row++;
			
			if(n1==0 && n2==0) p1=0;
			if(n1==0 && n2==1) p1=0;
			if(n1==1 && n2==0) p1=0;
			if(n1==1 && n2==1) p1=1;
			
			if(n3==0 && p1==0) p2=1;
			if(n3==0 && p1==1) p2=1;
			if(n3==1 && p1==0) p2=1;
			if(n3==1 && p1==1) p2=0;
			
			if(p2==0 && n4==0 && p3!=0) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p2==0 && n4==1 && p3!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p2==1 && n4==0 && p3!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p2==1 && n4==1 && p3!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else printf("\n");
		}
	}else if(in==5){
		while(!feof(fp)){
			fscanf (fp, "%d", &n1);
			printf("%d ", n1);
			fscanf (fp, "%d", &n2);
			printf("%d ", n2);
			fscanf (fp, "%d", &n3);
			printf("%d ", n3);
			fscanf (fp, "%d", &n4);
			printf("%d ", n4);
			fscanf (fp, "%d", &n5);
			printf("%d ", n5);
			fscanf (fp, "%d", &p4);
			printf("%d ", p4);
			row++;
			
			if(n1==0 && n2==0) p1=0;
			if(n1==0 && n2==1) p1=0;
			if(n1==1 && n2==0) p1=0;
			if(n1==1 && n2==1) p1=1;
		
			if(n3==0 && n4==0) p2=0;
			if(n3==0 && n4==1) p2=1;
			if(n3==1 && n4==0) p2=1;
			if(n3==1 && n4==1) p2=0;
		
			if(p1==0 && p2==0) p3=1;
			if(p1==0 && p2==1) p3=1;
			if(p1==1 && p2==0) p3=1;
			if(p1==1 && p2==1) p3=0;
			
			if(p3==0 && n5==0 && p4!=0) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p3==0 && n5==1 && p4!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p3==1 && n5==0 && p4!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else if(p3==1 && n5==1 && p4!=1) {printf("This row is wrong(row %d)\n",row); i++;}
			else printf("\n");
			
		}
	}if(i==0) printf("File is completely correct!\n");
	
    fclose (fp);    
    printf("\n");    
}

void circuit_info(){
	printf("In order to build a circuit you must know:\n");
	printf("1)The number of inputs\n");
	printf("2)The logic gates between inputs\n");
	printf("3)The number of outputs\n\n");
	printf("For example, the given circuit has 5 inputs, 4 logic gates and 1 output.\n");
}

int main() {
	int num;
	printf("Press 0 to exit\n");
	printf("Press 1 to choose a gate and print the truth table\n");
	printf("Press 2 to print the truth table for specific numbers\n");
	printf("Press 3 to calculate the output of the circuit\n");
	printf("Press 4 to scan file containing inputs and outputs\n");
	printf("Press 5 to 'build' a circuit\n");
	scanf("%d", &num);
	if(num==0) printf("Goodbye!");
	else if(num==1){
		gates();
		main();
	} 
	else if(num==2){
		specific_gates();
		main();
	} 
	else if(num==3){
		circuit();
		main();
	}else if(num==4){
		file_inputs();
		main();
	}else if(num==5){
		circuit_info();
		main();
	}  
	else{
		printf("Wrong number! Try again.\n");
		main();
	} 
	return 0;
}
