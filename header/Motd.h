//
// Created by Aymen Ben Rkhis on 7/18/15.
//

#ifndef OS32_MOTD_H
#define OS32_MOTD_H
#include "string"
#include "Motd.h"
#include "FileSystem.h"

using namespace std;

namespace Utilities{

    class Motd : public Utilities{

    public:
        Motd();
        ~Motd();
        void execute();
        void generateMOTD();
    };

}

#endif //OS32_MOTD_H
