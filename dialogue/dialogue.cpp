#include "../cpu/include/processor.hpp"
#include "../asm/include/assembler.hpp"
#include "../instructions/include/commands.hpp"
#include "../instructions/include/operands.hpp"

void bye(){
    std::cout <<
    "==================================================================\n";
    std::cout << 
    "         ,_         _,\n"
    "         |\\.-\"\"\"\"-.//|\n"
    "         `\\         `/\n"
    "        /    _   _    \\\n"
    "        |    a _ a    |\n"
    "        '.=    Y    =.'\n"
    "          >._  ^  _.<\n" 
    "         /   `````   \\\n" 
    "         )           (                bye...\n" 
    "        ,(           ),\n" 
    "       / )   /   \\   ( \\\n" 
    "       ) (   )   (   ) (\n" 
    "       ( )   (   )   ( )\n" 
    "       )_(   )   (   )_(-.._\n" 
    "      (  )_  (._.)  _(  )_, `\\\n" 
    "       ``(   )   (   )`` .' .'\n" 
    "           ```     ```   ( (`\n" 
    "                         '-'\n" << std::endl;
    std::cout <<
    "==================================================================\n";
}

void sadBye(){
    std::cout <<
    "==================================================================\n\n";
    std::cout <<
    "                        ,/|         _.--''^``-...___.._.,;\n"
    "  it seems like       /, \'.     _-'          ,--,,,--'''\n"
    " something went      { \\\\    `_-''       '    /}\n"
    "   wrong...             `;;'             ;   ; ;\n"
    "                  ._.--''     ._,,, _..'  .;.'\n"
    "                  (,_....----'''     (,..--''\n" << std::endl; 
    std::cout <<
    "==================================================================\n";
}

void printCPUStat(CPUPtr& cpu) {
    std::cout <<
    "==================================================================\n";
    std::cout << "CPU stat:\n";
    std::cout << "flags:\n\tZF - " << (cpu->flags_[0] ? "true" : "false") << "\tCF - " << 
    (cpu->flags_[1] ? "true" : "false") << "\n\tSF - " << (cpu->flags_[2] ? "true" : "false") 
    << "\tOF - " << (cpu->flags_[3] ? "true" : "false") << std::endl;
    std::cout << 
    "------------------------------------------------------------------\n";
    cpu->ram_->print();
    cpu->registers_->print();
    std::cout <<
    "==================================================================\n";
}

///home/urtoach/Desktop/proc_model/tests/testdata/valid_file.txt

int main() {
    std::cout <<
    "==================================================================\n";
    std::cout << "enter file name:" <<std::endl << ">> ";
    std::string filename;
    std::cin >> filename;
    try {
        CPUPtr cpu = std::make_shared<CPU>();
        Assemble assembler(filename, cpu);
        ProgramMemory program = assembler.interpreter();
        cpu->loadProgram(program);

        std::cout << "\tbefore execute\n";
        printCPUStat(cpu);

        cpu->execute();

        std::cout << "\tafter execute\n";
        printCPUStat(cpu);

        //bye();
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument error: " << e.what() << std::endl;
        sadBye();
    } 
    catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        sadBye();    
    } 
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        sadBye();
    } 
    catch (...) {
        std::cerr << "Unknown exception occurred" << std::endl;
        sadBye();
    }
}
