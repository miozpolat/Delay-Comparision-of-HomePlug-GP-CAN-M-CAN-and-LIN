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

#include <Bus.h>
Define_Module(Bus); //It is required to see this object in the simulation interface

Bus::Bus() {
    // TODO Auto-generated constructor stub

}

Bus::~Bus() {
    // TODO Auto-generated destructor stub
}

void Bus::initialize()
{
    //Filling the identifier heap with IDLE value
    heap.reserve(identifierLength);
    for(int i=0; i<identifierLength; i++){
        heap[i] =IDLE;
    }
}
void Bus::handleMessage(cMessage *msg)
{
   if( isHeapAvailable==true &&!strcmp(msg->getName(), "busCheck"))
   {
               cMessage *busEmpty =new cMessage("busEmpty");
               int  a = msg->getArrivalGate()->getIndex();
               busTime=msg->getArrivalTime();
               send(busEmpty,"g$o",a);
               isHeapAvailable=false;
   }
   else if(!strcmp(msg->getName(), "busCheck")&& msg->getArrivalTime()==busTime )
   {
       cMessage *busEmpty =new cMessage("busEmpty");
       int  a = msg->getArrivalGate()->getIndex();
       busTime=msg->getArrivalTime();
       send(busEmpty,"g$o",a);
       isHeapAvailable=false;

   }
   else if(msg->getArrivalTime()==busTime && strcmp(msg->getName(),"bit")&&isContention==false)
   {
       cMessage *busEmpty =new cMessage("busEmpty");
       int  a = msg->getArrivalGate()->getIndex();
       busTime=msg->getArrivalTime();
       send(busEmpty,"g$o",a);
       isHeapAvailable=false;
   }
   else if(!strcmp(msg->getName(),"bit"))
   {
       isContention=true;
       isHeapAvailable=false;
       PriorityBit *temp = check_and_cast<PriorityBit *>(msg); // Cast the message to a PriorityBit
       if(BitIndex!=temp->getBitIndex()) //If bit Index has changed like from 3th bit to 4th bit of CAN identifer bits
       {
           reccesiveBitHeap.clear();
           BitIndex++;
       }
       int k=heap[temp->getBitIndex()];
        n=(int)(temp->getBit());

       if(k==IDLE)  // If the heap is IDLE, replace the bit with received message bit.
       {
           heap[temp->getBitIndex()]=temp->getBit();

           if(n==RECESSIVE) //if the received bit is recessive bit, store it in the recessiveBitHeap
           {
               reccesiveBitHeap.push_back(msg->getArrivalGate()->getIndex());
           }
       }
       else if (k==RECESSIVE && n==RECESSIVE) // if current index and message are recessive, add it to recesiveBitHeap
       {
           heap[temp->getBitIndex()]=temp->getBit();
           reccesiveBitHeap.push_back(msg->getArrivalGate()->getIndex());
       }
       else if(k==DOMINANT && n==DOMINANT) //if current index and message are dominant, replace it
       {
           heap[temp->getBitIndex()]=temp->getBit();
       }
       else if(k==DOMINANT && n==RECESSIVE) // if the current index is dominant and messege is recessive, send lostContention
       {
           cMessage *lostContention=new cMessage("lostContention");

           int  a = msg->getArrivalGate()->getIndex();
           send(lostContention,"g$o",a);
       }
       // if the current index is recessive and message is dominant, replace the bit and lost contention
       // to the nodes in the recessiveBitHeap
       else if(k==RECESSIVE && n==DOMINANT)
       {
           heap[temp->getBitIndex()]=temp->getBit();
           for(int i=0; i<(int)reccesiveBitHeap.size(); i++)
           {
               cMessage *lostContention=new cMessage("lostContention");
               send(lostContention,"g$o",reccesiveBitHeap[i]);
            }
           reccesiveBitHeap.clear();
       }
       //if 11 bit has been received, sends the wonContention to the winner node
      if(temp->getBitIndex()==(identifierLength-1))
      {
          BitIndex=0;
          cMessage *wonContention=new cMessage("wonContention");
          int  a = msg->getArrivalGate()->getIndex();
          send(wonContention,"g$o",a);
      }
   }
   else if(!strcmp(msg->getName(),"RtrAndControlBits"))
   {
  //  delete(msg);
   }
   else if(!strcmp(msg->getName(),"data"))
   {
       reccesiveBitHeap.clear();
       DataPacket *tempData=check_and_cast<DataPacket *>(msg);
       Ack *ACK=new Ack("Acked");
       ACK->setSTEI(tempData->getSTEI());
       for(int i=0;i<NumberOfNodes;i++)
         {
             sendDelayed(ACK->dup(), 53*Tbit2,"g$o",i); //47 bits for ACK and CRC and 6 bit carrier idle time 8us bit time
         }
         delete(msg);
         delete(ACK);
      isHeapAvailable=true;
      isContention=false;
      initialize(); //clean the heap
   }
   else
   {
      cMessage *busOccupied =new cMessage("busOccupied");
      int  a = msg->getArrivalGate()->getIndex();
      send(busOccupied,"g$o",a);
   }
   delete(msg);

}
