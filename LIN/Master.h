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

#ifndef MASTER_H_
#define MASTER_H_
#include <omnetpp.h>
#include "Frame_m.h"
#include "DataPacket_m.h"

class Master : public cSimpleModule {
public:
    Master(); // Class constructor
    virtual ~Master(); // Class destructor
    virtual void initialize(); // Used to assign inital parameters
    virtual void handleMessage(cMessage *msg); // Called when this node receives a message
    virtual void regenerateLDF(); // Called to regenerate LDF in order to make simulatior run forever
    cMessage *frameSlot; // Schedulet to trigger a tranmission
    Frame *frameRequest[12]; //Represent 12 frame requests to form LDF
    int counter=0; // A variable to check if the a period of LDF finished
    int ID; // Stores ID of this object
    int NumberOfNodes=10; // number of nodes;
     double Tbit1=0.00005; //50 us for 20 kbit/s transmission
    int N=8; // Number of data section in one frame(selected as maximum number)
    simtime_t frameRequestTime1=0; //A variable to measure access delay
    simtime_t frameRequestTime2=0; // A variable to measure acces delay
    double arrivalSignal; // A variable to publish access delay
};

#endif /* MASTER_H_ */
