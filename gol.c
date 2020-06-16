#include<stdio.h>
#include<stdlib.h>
#include"gol.h"


void read_in_file(FILE *infile, struct universe *u){

		char ch;
		(*u).c = 0;
		(*u).r = 0;
		u->gen = 1;
		int current_check = 0;
		int former_check = 0;
	
		while(1)
		{
			ch = getc(infile);
			if(ch == EOF){
				break;
				}
			if(ch != '.'  && ch != '*' && ch != '\n'){
				fprintf(stderr, "%s", "Error, invalid characters in input. \n");
				exit(-1);
				}else{
					(*u).c++;
					current_check++;
				}
			if(ch == '\n'){
				u->r++;
				if(current_check != former_check && former_check != 0){
					fprintf(stderr, "%s", "Error, invalid dimensions in input. \n");
					exit(-1);
					}else{
				former_check = current_check;
				current_check = 0;
			}
		}
					}
		
		
		if(u->c == 0){
			fprintf(stderr, "%s", "Error, input cannot be empty. \n");
			exit(-1);
			}

		rewind(infile);

				
	(*u).c = (*u).c/(*u).r;
	if((int)u->c != u->c){
		fprintf(stderr, "%s", "Error, invalid dimensions in input. \n");
		exit(-1);
		}
		
	if(u->c > 512){
		fprintf(stderr, "%s", "Error, too many columns in input. \n");
		exit(-1);}
	

	u->cells = (char**)malloc(u->r * u->c * sizeof(char));
	for(int i=0; i<(*u).r; i++){
		u->cells[i] = (char*)malloc((*u).c * sizeof(char));							
		}
		
			rewind(infile);


		for(int i=0; i<(*u).r; i++){
			for(int j=0; j<(*u).c; j++){
				if(ch == '.' || '*'){
				ch = getc(infile);
				u->cells[i][j] = ch;
			}
		}
	}

	fclose(infile);
	
	for(int i = 0; i < u->r; i++){
		for(int j =0; j < u->c-1; j++){
			u->total++;
			if(u->cells[i][j] == '*'){
				u->current++;
				}
			}
		}
	u->current = u->current/u->total * 100;
	u->average = u->current;

}

void write_out_file(FILE *outfile, struct universe *u){
	
	
	for(int j = 0; j < u->r; j++){
		for(int i = 0; i < u->c; i++){
				fputc(u->cells[j][i], outfile);
		}
		
//		fputc("\n", outfile);
		
	}

	fclose(outfile);
}


int is_alive(struct universe *u, int column, int row){

    if(u->cells[row][column] == '*'){
    return 1;
    }else{
    return 0;
	}
}

int will_be_alive(struct universe *u, int column, int row){

    int neighbours = 0;

	if(column != u->c-2 && row != u->r-1 && column != 0 && row != 0){
//			printf("first case\n");
			if(is_alive(u, column-1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row+1)){
			neighbours = neighbours + 1;}
					}

	if(column == 0 && row == 0){
//		printf("second case\n");
		if(is_alive(u, column+1, row+1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row+1)){
		neighbours = neighbours + 1;}
			}

	if(column == u->c-2 && row == u->r-1){
//		printf("third case\n");
		if(is_alive(u, column-1, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column-1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row-1)){
		neighbours = neighbours + 1;}
			}

	if(column == u->c-2 && row == 0){
//		printf("fourth case\n");
		if(is_alive(u, column-1, row+1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column-1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row+1)){
		neighbours = neighbours + 1;}
			}

	if(column == 0 && row == u->r-1){
//		printf("fifth case\n");
		if(is_alive(u, column+1, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row-1)){
		neighbours = neighbours + 1;}
			}

	if(column == u->c-2 && row < u->r-1 && row > 0){
//		printf("sixth case\n");
		if(is_alive(u, column-1, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column-1, row+1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column-1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row+1)){
		neighbours = neighbours + 1;}
		}	

	if(row == u->r-1 && column != u->c-2 && column != 0){
//		printf("seventh case\n");
		if(is_alive(u, column-1, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column-1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row-1)){
		neighbours = neighbours + 1;}
		}

	if(row == 0 && column != u->c-2 && column != 0){
//		printf("eighth case\n");
		if(is_alive(u, column-1, row+1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row+1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column-1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row+1)){
		neighbours = neighbours + 1;}
		}

	if(column == 0 && row != u->r-1 && row != 0){
//		printf("ninth case\n");
		if(is_alive(u, column+1, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row-1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row+1)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column+1, row)){
		neighbours = neighbours + 1;}
		if(is_alive(u, column, row+1)){
		neighbours = neighbours + 1;}
		}	

    if(u->cells[row][column] == '*')
    {
        if(neighbours == 2 || neighbours == 3){
        return 1;
        }else{
        return 0;
		}
    }

    if(u->cells[row][column] == '.')
    {
 //   	printf("cell [%d, %d] has %d neighbours \n", row, column, neighbours);
        if(neighbours == 3){
        return 1;
        }else{
        return 0;
		}
    }

	return 0;

}

int will_be_alive_torus(struct universe *u, int column, int row){

    int neighbours = 0;

	if(column != u->c-2 && row != u->r-1 && column != 0 && row != 0){
//			printf("first case\n");
			if(is_alive(u, column-1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row+1)){
			neighbours = neighbours + 1;}
					}

	if(column == 0 && row == 0){
//		printf("second case\n");
			if(is_alive(u, u->c-2, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, u->c-2, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, u->c-2, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row+1)){
			neighbours = neighbours + 1;}
					}

	if(column == u->c-2 && row == u->r-1){
//		printf("third case\n");
			if(is_alive(u, column-1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, 0)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, 0)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, 0)){
			neighbours = neighbours + 1;}
					}

	if(column == u->c-2 && row == 0){
//		printf("fourth case\n");
			if(is_alive(u, column-1, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row+1)){
			neighbours = neighbours + 1;}
					}

	if(column == 0 && row == u->r-1){
//		printf("fifth case\n");
			if(is_alive(u, u->c-2, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, u->c-2, 0)){
			neighbours = neighbours + 1;}
			if(is_alive(u, u->c-2, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, 0)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, 0)){
			neighbours = neighbours + 1;}
					}

	if(column == u->c-2 && row < u->r-1 && row > 0){
//		printf("sixth case\n");
			if(is_alive(u, column-1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, 0, row+1)){
			neighbours = neighbours + 1;}
					}

	if(row == u->r-1 && column != u->c-2 && column != 0){
//		printf("seventh case\n");
			if(is_alive(u, column-1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, 0)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, 0)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, 0)){
			neighbours = neighbours + 1;}
					}

	if(row == 0 && column != u->c-2 && column != 0){
//		printf("eighth case\n");
			if(is_alive(u, column-1, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column-1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, u->r-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row+1)){
			neighbours = neighbours + 1;}
					}

	if(column == 0 && row != u->r-1 && row != 0){
//		printf("ninth case\n");
			if(is_alive(u, u->c-2, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, u->c-2, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, u->c-2, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row-1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column, row+1)){
			neighbours = neighbours + 1;}
			if(is_alive(u, column+1, row+1)){
			neighbours = neighbours + 1;}
					}

    if(u->cells[row][column] == '*')
    {
        if(neighbours == 2 || neighbours == 3){
        return 1;
        }else{
        return 0;
		}
    }

    if(u->cells[row][column] == '.')
    {
 //   	printf("cell [%d, %d] has %d neighbours \n", row, column, neighbours);
        if(neighbours == 3){
        return 1;
        }else{
        return 0;
		}
    }

	return 0;

}


void evolve(struct universe *u, int (*rule)(struct universe *u, int column, int row)){
	
	u->current = 0;
	u->gen++;
	
	int temp[u->r][u->c];

	for(int j =0; j < u->r; j++){
		for(int i=0; i < u->c-1; i++){
			if((*rule)(u, i, j)){
				temp[j][i] = 1;
			}else{
				temp[j][i] = 0;
			}
		}
	}

	for(int j =0; j < u->r; j++){
		for(int i=0; i < u->c-1; i++){
			if(temp[j][i] == 1){
				u->cells[j][i] = '*';
			}else{
				u->cells[j][i] = '.';
			}
		}
	}
	
	for(int i = 0; i < u->r; i++){
		for(int j =0; j < u->c; j++){
			if(u->cells[i][j] == '*'){
				u->current++;
				}
			}
		}
	u->current = (u->current/u->total)*100;
	u->average = u->average + u->current;
	
	
}

void print_statistics(struct universe *u){

	printf("%.3f%% of cells currently alive \n", u->current);	
	u->average = u->average/u->gen;
	printf("%.3f%% of cells alive on average \n", u->average);

}



//gcc -Wl,--defsym=main=read_in_file gol.c -o x

