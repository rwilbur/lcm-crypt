#include <iostream>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <lcm/lcm-cpp.hpp>
#include <boost/program_options.hpp>



using namespace std;
namespace po = boost::program_options;


lcm::LCM *m_lcm;
std::string lcm_url = "udpm://239.255.76.67:7667?ttl=1";


void initialize(){
    m_lcm = new lcm::LCM(lcm_url);
    if(!m_lcm->good()){
        cerr << "LCM Failed to initialize" << std::endl;
    }

}

int main(int ac, const char *av[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("lcm_url", po::value<string>(), "set LCM URL")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
        return 1;
    }
    if (vm.count("lcm_url")) {
        cout << "LCM URL was set to "
     << vm["lcm_url"].as<string>() << ".\n";
        lcm_url = vm["lcm_url"].as<string>();
    }
    else {
        cout << "Using default LCM URL";
    }

 initialize();





}

