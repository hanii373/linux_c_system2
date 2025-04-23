#include <stdio.h>
#include <stdlib.h> 
int main(int argc, char *argv[]) {
	int product = 1;
        if (argc < 2) {
        printf("Produit : %d\n", product);
        return 0;
    }
 
        for (int i = 1; i < argc; i++) {
        int number = atoi(argv[i]); 
        product *= number;         
    }

       printf("Product of the arguments: %d\n", product);

    return 0;
}

