#include <memory>
#include <iostream>

#include "parser_context.h"
#include "vm/virtual_machine.h"

extern int yyparse(apus::ParserContext* pctx);
extern FILE* yyin;

void PrintUsage() {

    std::cerr << "Usage: apus [options] <binary file>" << std::endl;
    std::cerr << "-f, --file=FILE    Use FILE as apus script"<<std::endl;

}

int main(int argc, char** argv) {

    if (argc < 2) {
        PrintUsage();
        return -1;
    }

    std::string binary_file_name("");

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == '-') {

            switch (argv[i++][1]) {

                case 'f':
                    if ( !(yyin = fopen(argv[i], "r")) ) {
                        std::cerr << "File open error : " << argv[i] << std::endl;
                        return -1;
                    }
                    break;

                default:
                    std::cerr << "Unknown option : " << argv[i] << std::endl;
                    continue;
            }
        }

        else {
            binary_file_name = std::string(argv[i]);
        }

    }

    if (binary_file_name.size() == 0) {
        std::cerr << "Binary file path not set " << std::endl;
        return -1;
    }

    std::shared_ptr<apus::VirtualMachine> vm = std::make_shared<apus::VirtualMachine>();
    apus::ParserContext pctx(vm);

    int result = yyparse(&pctx);

    if (result == 0) {
        vm->Run(binary_file_name);
    }

    return 0;
}
