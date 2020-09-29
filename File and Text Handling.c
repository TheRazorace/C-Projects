#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "windows.h"

char title[20];
char vocab[20];
void readFile(FILE *fp)
{
  SetConsoleOutputCP(CP_UTF8);
  printf("Choose the title of the the file you want to read (add <.txt> at the end):");
  scanf("%s", &title);
  fp=fopen(title,"r");
  if (fp == NULL) {
  	    printf("No such file exists. Try again!\n");
        readFile(fp);
  }else{
  	printf("File succesfully read.\n\n");
  }
  fclose(fp);
}

void readVocabulary(FILE *v)
{
  SetConsoleOutputCP(CP_UTF8);
  printf("Warning. Program may fail if a big dictionary is inserted\n");
  printf("Choose the title of the the file you want to read (add <.txt> at the end):");
  scanf("%s", &vocab);
  v=fopen(vocab,"r");
  if (v == NULL) {
  	    printf("No such file exists. Try again!\n");
        readVocabulary(v);
  }else{
  	printf("Dictionary succesfully read\n\n");
  }
  fclose(v);
}

void writeFile(FILE *fp)
{ 
 
  int count = 0, pos; 
  char word[50], ch; 
  char **array = NULL;
  
  printf("Choose the title of the the file you want to write in (add <.txt> at the end):");
  scanf("%s", &title);
  fp = fopen(title, "w+");

  char term[6]= "TELOS";
  char *prnt = "print";
  printf("Input a string or input TELOS to end or input <print> to print text\n");

  while (strcmp(term, word) != 0 ){
  	
    scanf("%s", &word);
    if (strcmp(term, word) == 0){
    	fseeko(fp,-1,SEEK_END);
    	pos = ftello(fp);
    	ftruncate(fileno(fp), pos);
    	printf("File succesfully written\n\n");
	}

    if (strcmp(prnt, word) == 0){
       printf("Text:\n");

       int i;

       for (i=0; i<count; i++)
       {
         printf("%s ", array[i]);
         if(i%5==0 && i!=0){
         printf("\n");
       }
     }
      printf("\n");

    }
    else{
      count++;
      array = (char**)realloc(array, (count+1)*sizeof(*array));
      array[count-1] = (char*)malloc(sizeof(word));
      strcpy(array[count-1], word);
      
    
      if (strcmp(term, word) != 0){
        fprintf(fp,word);
        fprintf(fp," ");
	    }
    }

}

	fclose(fp);
}

void dash(int amount){
	int s;
	for(s=1; s<=amount; s++){
		printf("-");
	}
}

void space(int amount){
	int s;
	for(s=1; s<=amount; s++){
		printf(" ");
	}
}

void countWords(FILE *fp){
   char ch, p[50][100], str1[20], ptr1[50][100], del[] = ",  .!@#%:;'?/)(*'";
   static char data[30000][30000], str[30000];
   char *where=str;
   int i, size, climax ,sz1, sz2 ,c = 0, j = 0, k, s = 0, ccount = 0, wcount = 0, ucount=1,a=0;
   int plus=0, v=0, count1=0, count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0, count10=0, count11=0;
   fp=fopen(title,"r");
   if (fp == NULL) {
  	    printf("No such file exists. Try again!\n");
        exit(1);
   }
   fseek(fp, 0L, SEEK_END);
   sz1 = ftell(fp);
   fseek(fp, 0L, SEEK_SET);
   
   while ((ch = fgetc(fp)) != EOF){
   		ccount++;
   		plus++;
   		sz2++;
   		if(ch==' '){
   			wcount++;
		}if (ch=='.' || ch==',' || ch=='!' || ch==':' || ch=='?' || ch=='"' ){
			v++;
		}
        if ((ch == ' ' && v==0) || ch=='.' || ch==',' || ch=='!' || ch==':' || ch=='?' || ch=='"' || sz2==sz1){
        	plus--;
        	if(sz1==sz2){plus++;}
        	if(plus==1)count1++;
        	if(plus==2)count2++;
        	if(plus==3)count3++;
        	if(plus==4)count4++;
        	if(plus==5)count5++;
        	if(plus==6)count6++;
        	if(plus==7)count7++;
        	if(plus==8)count8++;
        	if(plus==9)count9++;
        	if(plus==10)count10++;
        	if(plus>10)count11++;
        	plus=0;
		}
		v=0;
   }wcount++;

    fseek(fp, 0, SEEK_END);
	size = ftell(fp);
    rewind(fp);
    fread(str,1,size,fp);    
    for(i=0 ; i<size; i++) str[i] = tolower(str[i]);
    
    where = strtok(str,del);
    while((where=strtok(NULL,del))!=NULL){
    	strcpy(data[a],where);
    	a++;
	}
	
	
	for(i=0; i<a; i++){
		for(k=0; k<(a-1)-i; k++){
			if(strcmp(data[i],data[i+k+1])==0) c++;
		}
		if(c==0){
			ucount++; 
		} 
		c=0;
	}
	
	
    
   printf("The text contains %d characters!\n", ccount);
   printf("The text contains %d words!\n", wcount);
   printf("The text contains %d unique words!\n\n", ucount);
   
   printf("%d word contain 1 letter\n", count1);
   printf("%d words contain 2 letters\n", count2);
   printf("%d words contain 3 letters\n", count3);
   printf("%d words contain 4 letters\n", count4);
   printf("%d words contain 5 letters\n", count5);
   printf("%d words contain 6 letters\n", count6);
   printf("%d words contain 7 letters\n", count7);
   printf("%d words contain 8 letters\n", count8);
   printf("%d words contain 9 letters\n", count9);
   printf("%d words contain 10 letters\n", count10);
   printf("%d words contain more than 10 letters\n", count11);
   
   printf("\n");
   
   for(i=1; i<=10; i++){
   	    if(count4>100*i){
   	    	climax=i+1;
		}else(climax=1);
   }
   if(count4>1000) {
   		climax=15;
   }
	printf("Word length diagram\n");
	if(climax>1){
		printf("Scale set to 1/%d because text is too big\n", climax);
	}	
	space(5); dash(count1/climax); printf("\n");
	space(2); printf("1"); space(2); dash(count1/climax);  printf("\n"); 
	space(5); dash(count1/climax); printf("\n"); printf("\n"); 
	space(5); dash(count2/climax); printf("\n");
	space(2); printf("2"); space(2); dash(count2/climax); printf("\n");
	space(5); dash(count2/climax); printf("\n"); printf("\n");
	space(5); dash(count3/climax); printf("\n");
	space(2); printf("3"); space(2); dash(count3/climax); printf("\n");
	space(5); dash(count3/climax); printf("\n"); printf("\n");
	space(5); dash(count4/climax); printf("\n");
	space(2); printf("4"); space(2); dash(count4/climax); printf("\n");
	space(5); dash(count4/climax); printf("\n"); printf("\n");
	space(5); dash(count5/climax); printf("\n");
	space(2); printf("5"); space(2); dash(count5/climax); printf("\n");
	space(5); dash(count5/climax); printf("\n"); printf("\n");
	space(5); dash(count6/climax); printf("\n");
	space(2); printf("6"); space(2); dash(count6/climax); printf("\n");
	space(5); dash(count6/climax); printf("\n"); printf("\n");
	space(5); dash(count7/climax); printf("\n");
	space(2); printf("7"); space(2); dash(count7/climax); printf("\n");
	space(5); dash(count7/climax); printf("\n"); printf("\n");
	space(5); dash(count8/climax); printf("\n");
	space(2); printf("8"); space(2); dash(count8/climax); printf("\n");
	space(5); dash(count8/climax); printf("\n"); printf("\n");
	space(5); dash(count9/climax); printf("\n");
	space(2); printf("9"); space(2); dash(count9/climax); printf("\n");
	space(5); dash(count9/climax); printf("\n"); printf("\n");
	space(5); dash(count10/climax); printf("\n");
	space(1); printf("10"); space(2); dash(count10/climax); printf("\n");
	space(5); dash(count10/climax); printf("\n"); printf("\n");
	space(5); dash(count11/climax); printf("\n");
    printf(">10"); space(2); dash(count11/climax); printf("\n");
	space(5); dash(count11/climax); printf("\n"); printf("\n");
	
	fp=fopen("Statistics.txt", "w");
	fprintf(fp,"%s statistics:\n\n",title);
	fprintf(fp,"The text contains %d characters!\n", ccount);
    fprintf(fp,"The text contains %d words!\n", wcount);
    fprintf(fp,"The text contains %d unique words!\n\n", ucount);
    fprintf(fp,"%d word contain 1 letter\n", count1);
    fprintf(fp,"%d words contain 2 letters\n", count2);
    fprintf(fp,"%d words contain 3 letters\n", count3);
    fprintf(fp,"%d words contain 4 letters\n", count4);
    fprintf(fp,"%d words contain 5 letters\n", count5);
    fprintf(fp,"%d words contain 6 letters\n", count6);
    fprintf(fp,"%d words contain 7 letters\n", count7);
    fprintf(fp,"%d words contain 8 letters\n", count8);
    fprintf(fp,"%d words contain 9 letters\n", count9);
    fprintf(fp,"%d words contain 10 letters\n", count10);
    fprintf(fp,"%d words contain more than 10 letters\n", count11);
    
    printf("Statistics succesfully saved in <Statistics.txt> file!\n\n");
    fclose(fp);
}

void spellCheck(FILE *fp, FILE *v){
	int size,vsize,n=0,choice,i=1,j=1,iv=1,jv=1,q,b=0,c=0;
	char  *where, *vwhere, word[20], *del=",  .!@#%:;'?/)(*'", *data[70000], *voc[100000], *str, *vstr;
	fp = fopen(title,"r");
	if (fp == NULL) {
  	    printf("No such file exists. Try again!\n");
        exit(1);
   }
   
   fseek(fp, 0, SEEK_END);
   size = ftell(fp);
   rewind(fp);
   str=calloc(size+1,1);
   fread(str,1,size,fp);   
   for(q=0; q<size; q++){
   	    if(str[q]=='A') str[q]='a';
   	    if(str[q]=='B') str[q]='b';
   	    if(str[q]=='C') str[q]='c';
   	    if(str[q]=='D') str[q]='d';
   	    if(str[q]=='E') str[q]='e';
   	    if(str[q]=='F') str[q]='f';
   	    if(str[q]=='G') str[q]='g';
   	    if(str[q]=='H') str[q]='h';
   	    if(str[q]=='I') str[q]='i';
   	    if(str[q]=='J') str[q]='j';
   	    if(str[q]=='K') str[q]='k';
   	    if(str[q]=='L') str[q]='l';
   	    if(str[q]=='M') str[q]='m';
   	    if(str[q]=='N') str[q]='n';
   	    if(str[q]=='O') str[q]='o';
		if(str[q]=='P') str[q]='p';
		if(str[q]=='Q') str[q]='q';
		if(str[q]=='R') str[q]='r';
		if(str[q]=='S') str[q]='s';
		if(str[q]=='T') str[q]='t';
		if(str[q]=='U') str[q]='u';
		if(str[q]=='V') str[q]='v';
		if(str[q]=='W') str[q]='w';
		if(str[q]=='X') str[q]='x';
		if(str[q]=='Y') str[q]='y';
		if(str[q]=='Z') str[q]='z';
   } 
    
   where = strtok(str,del);
   data[0]=where;
   while((where=strtok(NULL,del))!=NULL){
    	data[i]=where;
   	    i++;
   	    j++;
   }
	fclose(fp);
	
	v = fopen(vocab, "r");
	if (fp == NULL) {
  	    printf("No dictionary file exists. Try again!\n");
        exit(1);
   }

    fseek(v, 0, SEEK_END);
	vsize = ftell(v);
    rewind(v);
    vstr=calloc(vsize+1,1);
    fread(vstr,1,vsize,v);    
    
    vwhere = strtok(vstr,del);
    voc[0]=vwhere;
    while((vwhere=strtok(NULL,del))!=NULL){
    	voc[iv]=vwhere;
    	iv++;
    	jv++;
	}
	fclose(v);
	
	printf("Scanning your text to find wrong words...\n");
	for(i=0; i<j; i++){
		for(iv=0; iv<jv; iv++){
			if(strcmp(voc[iv],data[i])==0){
				n++;	
			}
		}
		if(n==0){
			printf("<%s> is wrong!\n", data[i]);
			printf("Press 0 to replace the wrong word\n");
			printf("Press 1 to add the wrong word to the vocabulary\n");
			printf("Press 2 to keep scanning for wrong words\n");
			printf("Press 3 to end scanning\n");
			scanf("%d", &choice);
			
			if(choice==0){
				fp = fopen(title, "r+");
				printf("Choose the word you want to put in its place:");
				scanf("%s", &word);
				for(q=0; q<i+1; q++){
					b=b+strlen(data[q]);
					c=c+b+1;
				}
				fseek(fp,b,SEEK_SET);
				fwrite(word,strlen(word),1,fp);
	        //	fwrite(" ",1,1,fp);
				fclose(fp);
				printf("Word was succesfully replaced.\n");	
			}
			else if(choice==1){
				v = fopen(vocab, "a");
				fprintf(v," ");
				fprintf(v,data[i]);
				fclose(v);
				printf("Word was succesfully added to the dictionary.\n");
			}else if(choice==2){
				printf("Searching for other wrong words...\n");
			}else if(choice==3){
				printf("Scanning for words ended.\n");
				break;
			}
		}n=0;
	}
	printf("All wrong words found.\n\n");
}
void guide(){
	printf("Press 0 to exit\n");
	printf("Press 1 read a file from your computer\n");
	printf("Press 2 set a file from your computer as the vocabulary(dictionary)\n");
	printf("Press 3 to scan your file for wrong words\n");
	printf("Press 4 to write your own file\n");
	printf("Press 5 to calculate the statistics of your file and save them in another file\n");
}

int main(){
	int choice;
	FILE *fp;
	FILE *v;
	guide();
	scanf("%d", &choice);
	if(choice==0){
		printf("Goodbye!!\n");}
	else if(choice==1){
        readFile(fp);
		main();
	}else if(choice==2){
		readVocabulary(v);
		main();
	}else if(choice==3){
	    spellCheck(fp,v);
		main();
	}else if(choice==4){
		writeFile(fp);
		main();
	}else if(choice==5){
		countWords(fp);
		main();
	}else{
		printf("Wrong number! Try again\n");
		main();
	} 
}
