#include <stdio.h>
#include <stdlib.h>
//First Lab
//Could not write comments in greek



//Secondary fuctions

//Prints spaces
void space(int amount){
	int i;
	for(i=1; i<=amount; i++){
		printf(" ");}
}

//Prints stars
void stars(int amount){
	int i;
	for(i=1; i<=amount; i++){
		printf("*");}
}

//Prints new line
void new_line(int amount){
	int i;
	for(i=1; i<=amount; i++){
		printf("\n");}
}


//Primary fuctions

//Square fuction
void square(int size){
	int i;
	printf("Size: %d     Square\n", size);                                
	for(i=1; i<=size; i++){                                   
		if(i==1 || i==size){                                     
			stars(size);
		}else{
			stars(1);
			space(size-2);
			stars(1);
		}new_line(1);}
}

//Parallelogram fuction
void parallelogram(int size){
	int i;
	printf("Size: %d     Parallelogram\n", size);
	for(i=1; i<=size*2+1; i++){
		if(i==1 || i==size*2+1){
			space(size-1);
			stars(size);
		}else if(i==size || i==size+2){
			stars(size);		
		}else if(i>1 && i<size){
			space(size-i);
			stars(1);
			space(size-2);
			stars(1);
		}else if(i==size+1){
			printf(".....\n");
		}else{
			space(i-size-2);
			stars(1);
			space(size-2);
			stars(1);
		}new_line(1);}
}

//Arrow fuction
void arrow(int size){
	int i;
	if((size-1)%3==0){
		printf("Change size from %d to: %d\n", size,size-1);
		size=size-1;                                                //Change size method
	}else if((size+1)%3==0){
		printf("Change size from %d to: %d\n", size,size+1);            
		size=size+1;}                                              //Change size method
	printf("Size: %d     Arrow\n", size);
	
	if (size%2!=0){                                   //If size is an even number
		for(i=1; i<=(size*2)+1; i++){
			if(i==1|| i==(size*2)+1){
				space(size/3);
				stars(size/3);
			}
			else if((i>1 && i<=size/2) || (i<(size*2)+1) && i>(size+(size/2)+2)){
				space(size/3);
				stars(1);
				space(size/3-2);
				stars(1);
			}else if(i==(size/2+1) || i==size+2+(size/2)){
				stars((size/3)+1);
				space((size/3)-2);
				stars((size/3)+1);		
			}else if(i==size+1){
				printf(".....\n");
			}
			else if(i==size || i==size+2){
				space((size/2));
				stars(1);		
			}
			else if(i>size/2 && i<size+1){
				space(i-(size/2)-1);
				stars(1);
				space(size-2-(2*(i-(size/2)-1)));
				stars(1);
			}
			else{
				space(size+(size/2)+2-i);
				stars(1);
				space(2*i-size-(size)-5);
				stars(1);
			}new_line(1);
			}
	}else{                                  //If size is an odd number
		for(i=1; i<=(size*2)+1; i++){
			if(i==1|| i==(size*2)+1){
				space(size/3);
				stars(size/3);
			}
			else if((i>1 && i<=size/2) || (i<(size*2)+1) && i>(size+(size/2)+1)){
				space(size/3);
				stars(1);
				space(size/3-2);
				stars(1);
			}else if(i==(size/2+1) || i==size+1+(size/2)){
				stars((size/3)+1);
				space((size/3)-2);
				stars((size/3)+1);		
			}else if(i==size+1){
				printf(".....\n");
			}
			else if(i==size || i==size+2){
				space((size/2)-1);
				stars(2);			
			}
			else if(i>size/2 && i<size+1){
				space(i-(size/2)-1);
				stars(1);
				space(size-2-(2*(i-(size/2)-1)));
				stars(1);
			}
			else{
				space(size+(size)/2+1-i);
				stars(1);
				space(2*(i-size-2));
				stars(1);
			}new_line(1);
			}
			}
}

void double_square(int size){
	int i;
	if((size-1)%3==0){
		printf("Change size from %d to: %d\n", size,size-1);
		size=size-1;                                                      //Change size method                                                                
	}else if((size+1)%3==0){
		printf("Change size from %d to: %d\n", size,size+1);            
		size=size+1;}                                                     //Change size method
	printf("Size: %d     Double Square\n", size);
		
	for(i=1; i<=size; i++){
		if(i==1 || i==size){
			stars(size);
		}else if(i==(size/3)+1 || i==2*(size/3)){
			stars(1);
			space((size/3)-1);
			stars(size/3);
			space((size/3)-1);
			stars(1);
		}else if((i>1 && i<=size/3) || (i>2*(size/3) && i<size)){
			stars(1);
			space(size-2);
			stars(1);
		}else{
			stars(1);
			space((size/3)-1);
			stars(1);
			space((size/3)-2);
			stars(1);
			space((size/3)-1);
			stars(1);
		}new_line(1);
	}
}

int main(){
	int size, choice;
	printf("*             * ******  *        *****    ******    *       * ******\n");
	printf(" *           *  *       *       *        *      *   * *   * * *\n");
	printf("  *    *    *   ***     *      *        *        *  *   *   * ***\n");
	printf("   *  * *  *    *       *       *        *      *   *       * *\n");
	printf("    *    *      ******  ******   *****    ******    *       * ******\n");
	while(choice){
		printf("Choose a shape:\n");
		printf("Press 1 for square, 2 for parallelogram, 3 for arrows, 4 for double square\n");
		printf("Press 0 to stop!\n");
		scanf("%d", &choice);
		if(choice==0){
			printf("Goodbye!");
			break;
		}
		printf("Choose size for your shape:");
		scanf("%d", &size);
		if(choice==1){
			square(size);
		}else if(choice==2){
			parallelogram(size);
		}else if(choice==3){
			arrow(size);
		}else if(choice==4){
			double_square(size);
		}else{
			printf("Oops! You picked a wrong number. Try again!\n\n");}
		}
    return 0;
}
