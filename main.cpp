#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include <boost/program_options.hpp>
#include "datatypes/test_t.hpp"
#include <csignal>
#include <chrono>

namespace po = boost::program_options;



lcm::LCM *m_lcm;
std::string lcm_url = "udpm://239.255.76.67:7667?ttl=1";
datatypes::test_t test;


/**
 * Handles the interrupt (CTL + C)
 * @param signum
 */
void sigHandler(int signum);

/**
 *  Initializes LCM based off of the arguments
 * @param ac Argument count
 * @param av Argument vector
 */
void initialize(int ac, const char *av[]) __attribute__ ((cold));

/**
 * Used for retrieving the command to send via LCM
 * @return command to send
 */
std::string getCommand() {

    std::string command = "";
    std::cout << "Enter your command to be sent to all subscribed computers:" << std::endl;

    std::getline(std::cin, command);
    return command;

}


long int getUnixTime() {
    using namespace std::chrono;
    system_clock::time_point tp = system_clock::now();
    system_clock::duration dtn = tp.time_since_epoch();

    return duration_cast<milliseconds>(dtn).count();

}



int main(int ac, const char *av[])
{
    initialize(ac, av);
    signal(SIGINT, sigHandler);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        std::string cmd = getCommand();
        test.timestamp = getUnixTime();
        test.name = cmd;
        m_lcm->publish("TEST", &test);

    }
#pragma clang diagnostic pop





}

/**
 * Handles the interrupt (CTL + C)
 * @param signum
 */
void sigHandler(int signum){
    std::cout << "Exiting...\n";

    delete m_lcm;

    exit(signum);
}

/**
 *  Initializes LCM
 * @param ac
 * @param av
 */
void initialize(int ac, const char *av[] ){
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("lcm_url", po::value<std::string>(), "set LCM URL");

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
    } else {
        std::cout << "Using default LCM URL\n";
    }

    m_lcm = new lcm::LCM(lcm_url);
    if(!m_lcm->good()){
        std::cerr << "LCM Failed to initialize" << std::endl;
        exit(EXIT_FAILURE);
    }


}

