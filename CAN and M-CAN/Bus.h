
#ifndef BUS_H_
#define BUS_H_
#include <omnetpp.h>
#include <list>
#include "PriorityBit_m.h"
#include "Ack_m.h"
#include "DataPacket_m.h"
#include <vector>
class Bus :public cSimpleModule {
public:
    Bus(); // Class Constructor
    virtual ~Bus(); // Class Destructor
    virtual void initialize(); // Used to assign initial values and call initial functions
    virtual void handleMessage(cMessage *msg); // Called when this object receives a message
    std::vector<int> heap; // The heap to store all the dominant and recessive bits
    int NumberOfNodes=10; //Variable to store number of nodes in the network
    double Tbit1=0.000004; //Bit time for250 Kbit/s
    double Tbit2=0.000004; // Bit time for 250 Kbit/s
    int identifierLength=11; // CAN bus identifier length
    int BitIndex=0; //Stores index of CAN identifier
    std::vector<int> reccesiveBitHeap; //Stores gates which is received recessive bit from senders
    bool isHeapAvailable=true; //Booelan for cheking availibility for new transmission.
    bool isContention=false; // Boolean for checking contention state
    enum {DOMINANT = 0, RECESSIVE = 1, IDLE = 2} busSate; // State of the medium
    int n; //Temporary variable to store bit value of message
    simtime_t  busTime; // Stores arrival time of message. It is used calculate access delay
};

#endif /* BUS_H_ */
