#include <iostream>
#include <casm/CASM_global_definitions.hh>
#include <casm/crystallography/Structure.hh>
#include <casm/crystallography/Lattice.hh>
#include <casm/crystallography/Site.hh>
#include <casm/clex/PrimClex.hh>
#include <casm/clex/Supercell.hh>
#include <casm/casm_io/VaspIO.hh>
//#include <fstream>

int main()
{
    /**
     * This is where you get to shine. Place all your code in here
     * and use the infrastructure of the repository to compile
     * and install.
     *
     * If you're interested in working with something more complicated
     * than a single main.cpp file is convenient for, check out
     * casm-utilities!
     * https://github.com/goirijo/casm-utilities
     */

    //std::cout<<"I am a sad sad executable incapable of anything"<<std::endl;
    std::cout<<"Here is the CASM logo:"<<std::endl;
    CASM::print_splash(std::cout);

    //read a pos, write to screen and a file
    CASM::Structure mypos("/home/harsha/casm_2x/casm-derived-template/files/Ti2O_hcp");
    CASM::VaspIO::PrintPOSCAR printer(mypos);
    printer.print(std::cout);
    std::ofstream file("/home/harsha/casm_2x/casm-derived-template/files/POSCAR");
    printer.print(file);
    file.close();

    //print point and factor group of poscar
    auto pt_grp = mypos.point_group();
    std::cout<<"Point Group Name:" << pt_grp.get_name()<<"\n";
    pt_grp.print(std::cout, CASM::FRAC);
    auto fact_grp = mypos.factor_group();
    fact_grp.print(std::cout, CASM::FRAC);

    //make a supercell and store in a file
    Eigen::Matrix3d trans_mat; 
    std::ifstream mat_file("/home/harsha/casm_2x/casm-derived-template/files/trans_mat");
    mat_file >> trans_mat;
    auto mylat_mat = mypos.lattice().lat_column_mat();
    CASM::Lattice suplat(mylat_mat*trans_mat);
    auto sup_pos = mypos.create_superstruc(suplat);
    CASM::VaspIO::PrintPOSCAR sup_printer(sup_pos);
    sup_printer.print(std::cout);

    //Find the primitive of the sup_pos
    CASM::BasicStructure<CASM::Site> true_prim;
    sup_pos.is_primitive(true_prim);
    CASM::VaspIO::PrintPOSCAR prim_printer(true_prim);
    prim_printer.print(std::cout);
    
    //Trying to use configuration.primitive() //does not do what you expected
    // CASM::PrimClex primclex(sup_pos);
    // CASM::Supercell supercell(&primclex,sup_pos.lattice());
    // CASM::Configuration config(supercell);
    // config.init_occupation();
    // std::cout << config.is_primitive()<<"\n";
    // auto prim_config = config.primitive();
    // CASM::VaspIO::PrintPOSCAR config_printer(prim_config);
    // config_printer.print(std::cout);
    
    return 0;
}
