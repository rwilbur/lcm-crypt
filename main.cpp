#include <iostream>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <lcm/lcm-cpp.hpp>
#include <boost/program_options.hpp>



using namespace std;
namespace po = boost::program_options;



lcm::LCM m_lcm("udpm://239.255.76.67:7667?ttl=1");

void initialize(){



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
     << vm["lcm_ur;"].as<string>() << ".\n";
    } else {
        cout << "Using default LCM URL";
    }

 initialize();





}

