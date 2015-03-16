#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

// Clang doesn't like something that openbabel does with std::string
using drew_string = std::string;

#include <openbabel-2.0/openbabel/obconversion.h>
#include <openbabel-2.0/openbabel/builder.h>
#include <openbabel-2.0/openbabel/mol.h>


int main(int argc, char** argv) {
    int num_middle_units;
    drew_string my_out_file;

    if (argc == 3) {
        num_middle_units = std::stoi(argv[1]);
        my_out_file = argv[2];
    } else {
        std::cout << "Usages is: ./program num_middle_units out.xyz" << std::endl;
        return 1;
    }

    constexpr char mid_unit = 'C';
    std::stringstream mol_stream("C");

    for(auto i = 0; i < num_middle_units; ++i){
        mol_stream << mid_unit;
    }
    std::cout << "Mol string = " << mol_stream.str() << std::endl;

    std::ofstream out(my_out_file.c_str());

    if (!out) {
        std::cout << "Could not open out file " << std::endl;
        return 1;
    }

    OpenBabel::OBConversion conv(&mol_stream, &out);
    if (!conv.SetInAndOutFormats("SMI", "XYZ")) {
        std::cout << "Could not convert smi to xyz" << std::endl;
        return 1;
    }

    OpenBabel::OBMol in_mol;

    if(conv.Read(&in_mol)){
        OpenBabel::OBBuilder mol_builder;
        mol_builder.Build(in_mol);
        in_mol.AddHydrogens();
        conv.Write(&in_mol);
    }

    return 0;
}
