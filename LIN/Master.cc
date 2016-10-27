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

#include "Master.h"
#include <string.h>
Define_Module(Master); // It is required to call to see this module in the simulation

Master::Master() {
regenerateLDF(); // Forms the LDF file
}

Master::~Master() {
// TODO Auto-generated destructor stub
}

void Master::initialize()
{
arrivalSignal = registerSignal("arrival"); // Signal registering
// Sending the first frame to initialize transmission
frameSlot=new cMessage("Frame Slot");
scheduleAt(0,frameSlot);
ID=getId();
}

void Master::regenerateLDF()
{
// FrameRequest array is filled with Frame Requests with
// setting sender and receiver. Simply, generates LDF.
frameRequest[0]=new Frame("Frame Request");
frameRequest[0]->setSTEI(2);
frameRequest[0]->setDTEI(3);

frameRequest[1]=new Frame("Frame Request");
frameRequest[1]->setSTEI(3);
frameRequest[1]->setDTEI(4);

frameRequest[2]=new Frame("Frame Request");
frameRequest[2]->setSTEI(4);
frameRequest[2]->setDTEI(5);

frameRequest[3]=new Frame("Frame Request");
frameRequest[3]->setSTEI(5);
frameRequest[3]->setDTEI(2);

frameRequest[4]=new Frame("Frame Request");
frameRequest[4]->setSTEI(6);
frameRequest[4]->setDTEI(7);

frameRequest[5]=new Frame("Frame Request");
frameRequest[5]->setSTEI(7);
frameRequest[5]->setDTEI(8);

frameRequest[6]=new Frame("Frame Request");
frameRequest[6]->setSTEI(8);
frameRequest[6]->setDTEI(9);

frameRequest[7]=new Frame("Frame Request");
frameRequest[7]->setSTEI(9);
frameRequest[7]->setDTEI(2);

frameRequest[8]=new Frame("Frame Request");
frameRequest[8]->setSTEI(10);
frameRequest[8]->setDTEI(3);

frameRequest[9]=new Frame("Frame Request");
frameRequest[9]->setSTEI(11);
frameRequest[9]->setDTEI(4);

frameRequest[10]=new Frame("Frame Request");
frameRequest[10]->setSTEI(12);
frameRequest[10]->setDTEI(5);

frameRequest[11]=new Frame("Frame Request");
frameRequest[11]->setSTEI(13);
frameRequest[11]->setDTEI(2);
}
void Master::handleMessage(cMessage *msg)
{
// With the receipt of frameSlot message, master node sends the frame request specified in the LDF
if(msg==frameSlot)
{
// if LDF file is exceeded, new LDF file is generated
if(counter>(NumberOfNodes-1))
{
counter=0;
regenerateLDF();
}
bubble("Frame Start");
sendDelayed( frameRequest[counter],Tbit1*34,"g$o"); // 34 bit exist in frame header and 1.4 is used to simulate maximum frame slot time
counter++;
cancelEvent(frameSlot);
scheduleAt(simTime()+(Tbit1*34+Tbit1*74)*1.4,frameSlot); // maximum frame slot is added 40% is increased
}
else if(!strcmp(msg->getName(), "Frame Request"))
{
Frame *tempFrame = check_and_cast<Frame *>(msg); // Cast the message to a frame
WATCH(tempFrame);
if(tempFrame->getSTEI()==ID)
{
    frameRequestTime2=msg->getArrivalTime();
    double tempTimeDiffence=frameRequestTime2.dbl()-frameRequestTime1.dbl();
    if(tempTimeDiffence>0)
             {
                 tempTimeDiffence=tempTimeDiffence-108*Tbit1*1.4; // Extracting last 108 bits because tranmission is succesful
             }
    emit(arrivalSignal,tempTimeDiffence );
   frameRequestTime1=frameRequestTime2;
   DataPacket *data= new DataPacket("Data");
   data->setDTEI(tempFrame->getDTEI());
   bubble("Request Received");
   //74 bits reprsents frame response
   sendDelayed(data,Tbit1*74,1);
}

delete(tempFrame);
}

else if(!strcmp(msg->getName(), "Data"))
{
DataPacket *tempData=check_and_cast<DataPacket *>(msg);
if(tempData->getDTEI()==ID) // If this node is the receiver, bubble reception message
     {
         EV << "\t Message received by %d" << getFullName() << " node \n";
         bubble("Packet Received");
     }
delete(tempData);
}
//delete(msg);
}
