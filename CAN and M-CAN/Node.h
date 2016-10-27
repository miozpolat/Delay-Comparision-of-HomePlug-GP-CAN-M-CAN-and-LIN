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

#ifndef NODE_H_
#define NODE_H_
#include <omnetpp.h>
#include "PriorityBit_m.h"
#include "DataPacket_m.h"
#include "Ack_m.h"
#include <vector>

class Node :public cSimpleModule{
public:
   Node(); //Class constructor
   virtual ~Node();//Class destructor
   virtual void initialize(); // Used to assign initial parameters and
   virtual void handleMessage(cMessage *msg); // Called when this object receives a message
   virtual  simtime_t RandomAccessTime(); // Called to get a random time that schedules sending time of message
   std::vector<int> priorityBits; //Stores 11 bit of identifier
   virtual std::vector<int> priorityGenerator(); // Generates randomly 11 bit identifier for each message
   bool isLostContention=false; // Boolean to check if this object lost contention
   bool resetAccesDelay=true; // After every succesful transmision, this boolean set as true
   double Tbit1=0.000004; // Bit time for 1Mbit/s ,4 for 250k
   double Tbit2=0.000004; // Bit time for 125 Kbit/s
   double entireCanFrameSize=136; //136 bit for entire can frame
   int identifierLength=11; // CAN bus identifier length
   simtime_t InitialBusCheckTime=0; // A variable to measure access delay
   simtime_t LostContentionTime=0; // A variable to measure access delay
   double AccessDelay=0; // Stores access delay
   double arrivalSignal; // The signal to publish access delay
   int i=0; //Counter
   int NumberOfNodes=10; // Number of nodes in the network
};
#endif /* NODE_H_ */
