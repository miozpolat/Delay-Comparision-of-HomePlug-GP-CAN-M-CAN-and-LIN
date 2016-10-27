//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef SLAVE_H_
#define SLAVE_H_
#include <omnetpp.h>
#include "Frame_m.h"
#include "DataPacket_m.h"

class Slave : public cSimpleModule{
public:
    Slave(); // Class constructor
    virtual ~Slave(); // Class destructor
    virtual void initialize(); // Used to assign initial parameters.
    virtual void handleMessage(cMessage *msg); // Called when this object has received a message
    int ID; // Stores the ID of this object
     double Tbit1=0.00005; //50 us for 20 kbit/s transmission
    int N=8; // Number of data section in one frame(selected as maximum number)
    simtime_t frameRequestTime1=0; // A parameter to measure access delay
    simtime_t frameRequestTime2=0; // A parameter to measure access delay
    double arrivalSignal;   // Signal definition to publish.
};

#endif /* SLAVE_H_ */
