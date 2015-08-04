#include <iostream>

extern int yyparse(void);
extern FILE *yyin;

int main(int argc, char** argv) {

    if (argc < 2) {

        std::cout << "missing input file" << std::endl;
        return -1;

    }
    else {

        FILE *input_file = fopen(argv[1], "r");

        if(!input_file) {
            printf("can't open file\n");
            return -1;
        }

        yyin = input_file;
        if(yyparse()) {
            fprintf(stderr, "Error!\n");
            exit(1);
        }
    }

    return 0;
}
