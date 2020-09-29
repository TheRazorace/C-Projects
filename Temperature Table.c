 #include <stdio.h>
#include <stdlib.h>

void read_array(float table[10][20], float top, float bottom, float left, float right);
void sides(float table[10][20], float top, float bottom, float left, float right);
void corners(float table[10][20], float top, float bottom, float left, float right);
void time_change(float table[10][20], float new_array[10][20], float top, float bottom, float left, float right);
void find_permanent(float table[10][20], float new_array[10][20], float top, float bottom, float left, float right);
void dash(int amount);
void space(int amount);
void print_array(float table[10][20]);
void climax(float table[10][20], float scale[10][20], float top, float bottom, float left, float right);
void print_climax(float scale[10][20]);
void print_web(float scale[10][20]);

int main(){
	int k, time;
	float table[10][20], new_array[10][20], scale[10][20];
	float top, bottom, left, right;	
	printf("Welcome!!!\n");
	printf("Choose the temperature for the top side:") ; 
	scanf("%f", &top);
	printf("Choose the temperature for the bottom side:") ; 
	scanf("%f", &bottom);
	printf("Choose the temperature for the left side:") ; 
	scanf("%f", &left);
	printf("Choose the temperature for the right side:") ; 
	scanf("%f", &right);
	read_array(table, top, bottom, left, right);
	sides(table, top, bottom, left, right);
	corners(table, top, bottom, left, right);  
	printf("Temperature: 0 seconds\n");                                                                    
	print_array(table); 
	printf("\n");
	climax(table, scale, top, bottom, left, right);
	printf("Scale 0-9:\n");
	print_climax(scale);
	printf("\n");
	print_web(scale);
	printf("\n");
	printf("\n");
	while(time){
		find_permanent(table,new_array, top, bottom, left, right);
		printf("Choose the moment you want to check the temperature (or press 0 to exit):");
		scanf("%d", &time);
		if(time==0){
			printf("Goodbye!");
			break;
		}
		printf("Temperature: %d second(s)\n", time);
		for(k=1; k<=time; k++){
			if(k%2!=0){
				time_change(table,new_array, top, bottom, left, right);
				climax(new_array, scale, top, bottom, left, right);
				if(k==time){
					print_array(new_array);
					printf("\n");
					printf("Scale 0-9:\n");
					print_climax(scale);
					printf("\n");
					print_web(scale);
					printf("\n");
					printf("\n");
				}	
			}else{
				time_change(new_array,table, top, bottom, left, right);
				climax(table, scale, top, bottom, left, right);
				if(k==time){
					print_array(table);
					printf("\n");
					printf("Scale 0-9:\n");
					print_climax(scale);
					printf("\n");
					print_web(scale);
					printf("\n");
					printf("\n");
				}
			
			}
	}read_array(table, top, bottom, left, right);
	sides(table, top, bottom, left, right);
	corners(table, top, bottom, left, right);
	read_array(new_array, top, bottom, left, right);
}   
	return 0;                                       
}

//Initiates table prices
void read_array(float table[10][20], float top, float bottom, float left, float right){
	int i,j;								
	for(i=0; i<10; i++){
		for(j=0; j<20; j++){
			table[i][j]=(top+bottom+left+right)/4;						  
		}
	}
}

//initiates sides' prices
void sides(float table[10][20], float top, float bottom, float left, float right){
	int i;
	for(i=1; i<19; i++){
		table[0][i]=top;
	}for(i=1; i<19; i++){
		table[9][i]=bottom;
	}for(i=1; i<9; i++){
		table[i][0]=left;
	}for(i=1; i<9; i++){
		table[i][19]=right;
	}
}

//Initiates corners' prices
void corners(float table[10][20], float top, float bottom, float left, float right){
	table[0][0]=(top+left)/2;
	table[0][19]=(top+right)/2;
	table[9][0]=(left+bottom)/2;
	table[9][19]=(bottom+right)/2;
}

//Changes table's prices by time
void time_change(float table[10][20], float new_array[10][20], float top, float bottom, float left, float right){
	int i,j;
	for(i=0; i<10; i++){
		for(j=0; j<20; j++){
			new_array[i][j]=(table[i-1][j-1]+table[i-1][j]+table[i-1][j+1]+table[i][j-1]+
			2*table[i][j]+table[i][j+1]+table[i+1][j-1]+table[i+1][j]+table[i+1][j+1])/10;
			
			sides(new_array, top, bottom, left, right);
			corners(new_array, top, bottom, left, right);
			
		}
	}	
}

//Calculates the permanent state of the table
void find_permanent(float table[10][20], float new_array[10][20], float top, float bottom, float left, float right){
	int i, j, k, s=0;
	float dif;
	for(k=1; k<=500; k++){
		if(k%2!=0){
			dif=0;
			for(i=0; i<10; i++){
				for(j=0; j<20; j++){
					new_array[i][j]=(table[i-1][j-1]+table[i-1][j]+table[i-1][j+1]+table[i][j-1]+
					2*table[i][j]+table[i][j+1]+table[i+1][j-1]+table[i+1][j]+table[i+1][j+1])/10;
			
					sides(new_array, top, bottom, left, right);
					corners(new_array, top, bottom, left, right);
					if(new_array[i][j]>=table[i][j]){
						dif=dif + (new_array[i][j] - table[i][j]);
					}else{
						dif=dif + (table[i][j] - new_array[i][j]);
					}	
				}
			}if(dif>1){s++;}
		}else{
			dif=0;
			for(i=0; i<10; i++){
				for(j=0; j<20; j++){
					table[i][j]=(new_array[i-1][j-1]+new_array[i-1][j]+new_array[i-1][j+1]+new_array[i][j-1]+
					2*new_array[i][j]+new_array[i][j+1]+new_array[i+1][j-1]+new_array[i+1][j]+new_array[i+1][j+1])/10;
			
					sides(table, top, bottom, left, right);
					corners(table, top, bottom, left, right);
					if(new_array[i][j]>=table[i][j]){
						dif=dif + (new_array[i][j] - table[i][j]);
					}else{
						dif=dif + (table[i][j] - new_array[i][j]);
					}
				}
			}if(dif>1){s++;}
		}
	}read_array(table, top, bottom, left, right);
	sides(table, top, bottom, left, right);
	corners(table, top, bottom, left, right);
	read_array(new_array, top, bottom, left, right);
	printf("Permanent temperature at %d seconds!\n", s+1);
}

//Prints dashes
void dash(int amount){
	int s;
	for(s=1; s<=amount; s++){
		printf("-");
	}
}

//Prints spaces
void space(int amount){
	int s;
	for(s=1; s<=amount; s++){
		printf(" ");
	}
}

//Prints the given table
void print_array(float table[10][20]){
	int i,j;										
	for(i=0; i<10; i++){
		for(j=0; j<20; j++){
			printf("%7.2f", table[i][j]); 
		}printf("\n");                              
	}
}

//Makes the normalized table
void climax(float table[10][20], float scale[10][20], float top, float bottom, float left, float right){
	int i, j;
	float min,max,s;
	if (top>=bottom && top>= left && top>=right){max=top;}
	else if(bottom>=top && bottom>=left && bottom>=right){max=bottom;}
	else if(left>=top && left>=bottom && left>=right){max=left;}
	else{max=right;}
	
	if (top<=bottom && top<= left && top<=right){min=top;}
	else if(bottom<=top && bottom<=left && bottom<=right){min=bottom;}
	else if(left<=top && left<=bottom && left<=right){min=left;}
	else{min=right;}
	
	if(max<0){s=min-max;}
	else{s=max-min;}
	
	
	for(i=0; i<10; i++){
		for(j=0; j<20; j++){
			if(table[i][j]<min+(s/10)){scale[i][j]=0;}
			else if(table[i][j]<min+2*(s/10)){scale[i][j]=1;}
			else if(table[i][j]<min+3*(s/10)){scale[i][j]=2;}
			else if(table[i][j]<min+4*(s/10)){scale[i][j]=3;}
			else if(table[i][j]<min+5*(s/10)){scale[i][j]=4;}
			else if(table[i][j]<min+6*(s/10)){scale[i][j]=5;}
			else if(table[i][j]<min+7*(s/10)){scale[i][j]=6;}
			else if(table[i][j]<min+8*(s/10)){scale[i][j]=7;}
			else if(table[i][j]<min+9*(s/10)){scale[i][j]=8;}
			else{scale[i][j]=9;}
		}
	}
}

//Prints the normalized table
void print_climax(float scale[10][20]){
	int i,j;
	for(i=0; i<10; i++){
		for(j=0; j<20; j++){
			printf("%1.0f  ", scale[i][j]);
	}printf("\n");}}

//Prints the bar diagram
void print_web(float scale[10][20]){
	int i, j, count0=0, count1=0, count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0, count9=0;
	for(i=0; i<10; i++){
		for(j=0; j<20; j++){
			if(scale[i][j]==0){count0++;}
			else if(scale[i][j]==1){count1++;}
			else if(scale[i][j]==2){count2++;}
			else if(scale[i][j]==3){count3++;}
			else if(scale[i][j]==4){count4++;}
			else if(scale[i][j]==5){count5++;}
			else if(scale[i][j]==6){count6++;}
			else if(scale[i][j]==7){count7++;}
			else if(scale[i][j]==8){count8++;}
			else{count9++;}
		}
	}
	printf("\n");
	printf("Bar diagram (Prices are halved):\n");
	space(5); dash(count0/2); printf("\n");
	space(2); printf("0"); space(2); dash(count0/2);  printf("\n"); 
	space(5); dash(count0/2); printf("\n"); printf("\n"); 
	space(5); dash(count1/2); printf("\n");
	space(2); printf("1"); space(2); dash(count1/2); printf("\n");
	space(5); dash(count1/2); printf("\n"); printf("\n");
	space(5); dash(count2/2); printf("\n");
	space(2); printf("2"); space(2); dash(count2/2); printf("\n");
	space(5); dash(count2/2); printf("\n"); printf("\n");
	space(5); dash(count3/2); printf("\n");
	space(2); printf("3"); space(2); dash(count3/2); printf("\n");
	space(5); dash(count3/2); printf("\n"); printf("\n");
	space(5); dash(count4/2); printf("\n");
	space(2); printf("4"); space(2); dash(count4/2); printf("\n");
	space(5); dash(count4/2); printf("\n"); printf("\n");
	space(5); dash(count5/2); printf("\n");
	space(2); printf("5"); space(2); dash(count5/2); printf("\n");
	space(5); dash(count5/2); printf("\n"); printf("\n");
	space(5); dash(count6/2); printf("\n");
	space(2); printf("6"); space(2); dash(count6/2); printf("\n");
	space(5); dash(count6/2); printf("\n"); printf("\n");
	space(5); dash(count7/2); printf("\n");
	space(2); printf("7"); space(2); dash(count7/2); printf("\n");
	space(5); dash(count7/2); printf("\n"); printf("\n");
	space(5); dash(count8/2); printf("\n");
	space(2); printf("8"); space(2); dash(count8/2); printf("\n");
	space(5); dash(count8/2); printf("\n"); printf("\n");
	space(5); dash(count9/2); printf("\n");
	space(2); printf("9"); space(2); dash(count9/2); printf("\n");
	space(5); dash(count9/2); printf("\n"); printf("\n");
}

