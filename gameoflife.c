#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#include"gol.c"

int isPositiveInt(char str[]){
	for(unsigned int c = 0; c < strlen(str); c++){

		
		if(str[c] != '\0'){
		
			if(!isdigit(str[c])){
				
				return 0;
				}
		
			if(str[c] == '-'){
				return 0;
				}
	
		}
	}
	return 1;
}


int main(int argc, char *argv[]){

  struct universe v; 
	int loop = 5;
	int stats = 0;
	int output_file = 0;
	int input_file = 0;
	int g = 0;
	int (*rule)(struct universe * u, int column, int row);
	rule = &will_be_alive;
	FILE *file;
	FILE *fo;

	for(int j = 1; (j < argc); j++){
		
		
		if(argv[j][0] == '-'){
			
			switch(argv[j][1]){
	
				case 'i': if(input_file == 1){
								fprintf(stderr, "%s", "Error, conflicting input files. \n");
								exit(-1);
							}
							file = fopen(argv[j+1],"r");
							if(!file){
								fprintf(stderr, "%s", "Error opening input file. \n");
								exit(-1);
							}else{
							input_file = 1;
							}
							break;
				case 'o': if(output_file == 1){
								fprintf(stderr, "%s", "Error, conflicting output files. \n");
								exit(-1);
							}
							fo = fopen(argv[j+1], "w");
							if(!fo){
								fprintf(stderr, "%s", "Error opening output file. \n");
								exit(-1);
							}else{
							output_file = 1;
							}
							break;
				case 'g': 		if(g == 1){
									fprintf(stderr, "%s", "Error, conflicting generation inputs. \n");
									exit(-1);
									}		
									if(j+1 == argc){
									fprintf(stderr, "%s", "Invalid generation input. Please enter a positive integer. \n");
									exit(-1);
									}
								if(!(isPositiveInt(argv[j+1]))){
									fprintf(stderr, "%s", "Invalid generation input. Please enter a positive integer. \n");
									exit(-1);
									}			
								loop = atoi(argv[j+1]);
								g = 1;
								break;
				case 's': stats = 1;
							break;
				case 't': rule = &will_be_alive_torus;
								break;
							}
						}
					}
				
					
					
					if(input_file == 0){
							
							read_in_file(stdin, &v);
							
						}else{
							
							read_in_file(file, &v); 
						}
								
					for(int j = 0; j < loop; j++){
						
						evolve(&v, rule);
					}
					
					if(stats == 1){
							print_statistics(&v);
						}	

					if(output_file == 1){
						
						write_out_file(fo, &v);
						
						}else{
							
						write_out_file(stdout, &v);
							
						}
						
						

	return 0;
}
