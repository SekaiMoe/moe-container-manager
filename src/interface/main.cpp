#include "main.hpp"
#include "function.hpp"

using namespace func;

int main(int argc, char *argv[]) {

    if (argc < 2)  {
        cout << "Error: No inputs.\n"
        << "Please use 'interface -h' to learn how to use.\n";
        return -1;
    } else if (argc > 4){
        cout << "Error: Too many inputs.\n";
        return -2;
    }

   // Main options
    for(int i = 1;i < argc; ++i){
        char *pchar = argv[i];
        switch(pchar[0]){
            case '-':{
                switch(pchar[1]){
                    case 'v':
                        version();
                        return 0;
                    case 'h':
                        usage();
                        return 0;
                    case 'c':
                        create();
                        return 0;
                    case 'l':
                        readc();
                        return 0;
                    case 'r':
                        remove();
                        return 0;
                    default:
                        cerr<<proj::prog_name<<":error:unrecognition option -:"<<pchar<<endl;
                        usage();
                        return -1;
                    }
                break;
            }
        }
    }
}
