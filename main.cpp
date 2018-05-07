#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include <boost/program_options.hpp>
#include "datatypes/test_t.hpp"
#include <csignal>

namespace po = boost::program_options;



lcm::LCM *m_lcm;
std::string lcm_url = "udpm://239.255.76.67:7667?ttl=1";
datatypes::test_t test;


void sigHandler(int signum);
void initialize(int ac, const char *av[]) __attribute__ ((cold));

int main(int ac, const char *av[]);

void send_test();

int main(int ac, const char *av[])
{
    initialize(ac, av);
    signal(SIGINT, sigHandler);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        test.timestamp = 0;
        m_lcm->publish("TEST", &test);

        usleep(5);



    }
#pragma clang diagnostic pop





}


void sigHandler(int signum){
    std::cout << "Exiting...\n";

    delete m_lcm;

    exit(signum);
}

void initialize( int ac, const char *av[] ){
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("lcm_url", po::value<std::string>(), "set LCM URL")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(ac, av, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        exit(1);
    }
    if (vm.count("lcm_url")) {
        std::cout << "LCM URL was set to "
                  << vm["lcm_url"].as<std::string>() << ".\n";
        lcm_url = vm["lcm_url"].as<std::string>();
    }
    else {
        std::cout << "Using default LCM URL";
    }

    m_lcm = new lcm::LCM(lcm_url);
    if(!m_lcm->good()){
        std::cerr << "LCM Failed to initialize" << std::endl;
        exit(EXIT_FAILURE);
    }



}

