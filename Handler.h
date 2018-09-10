//
// Created by rwilbur on 8/27/18.
//

#ifndef LCM_CRYPT_HANDLER_H
#define LCM_CRYPT_HANDLER_H

#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include <boost/program_options.hpp>
#include "datatypes/broadcast_command_t.hpp"
#include <cstdio>
#include <stdlib.h>

class Handler {

public:
    ~Handler() {}

    void handleMessage(const lcm::ReceiveBuffer *rbuf,
                       const std::string &chan,
                       const datatypes::broadcast_command_t *msg) {
        const char *message = msg->data.c_str();
        printf("Received message on channel \"%s\":\n", chan.c_str());
        printf("Message: \"%s\":\n", message);

        std::system(message);


    }
};


#endif //LCM_CRYPT_HANDLER_H
