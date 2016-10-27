
#include "Slave.h"
Define_Module(Slave); // It is required to call to see this module in the simulation

Slave::Slave() {
    // TODO Auto-generated constructor stub

}

Slave::~Slave() {
    // TODO Auto-generated destructor stub
}

void Slave::initialize()
{
    ID=getId(); // Getting ID of this module
    arrivalSignal = registerSignal("arrival"); //Registering the signal
}
void Slave::handleMessage(cMessage *msg)
{
  if(!strcmp(msg->getName(), "Frame Request"))
  {
      Frame *tempFrame = check_and_cast<Frame *>(msg); // Cast the message to a frame
         WATCH(tempFrame);

        if(tempFrame->getSTEI()==ID)
        {
           DataPacket *data= new DataPacket("Data");
           data->setDTEI(tempFrame->getDTEI());

          frameRequestTime2=msg->getArrivalTime();
          double tempTimeDiffence=frameRequestTime2.dbl()-frameRequestTime1.dbl();
          if(tempTimeDiffence>0)
          {
              //Extracting last 134 bits because transmission was succesful
              tempTimeDiffence=tempTimeDiffence-108*Tbit1*1.4;
          }
          emit(arrivalSignal,tempTimeDiffence );

          frameRequestTime1=frameRequestTime2;
          //+1 is added in order to simulate checksum
           sendDelayed(data,Tbit1*74,1);

           bubble("Request Received");
        }

        delete(tempFrame);
  }
  else if(!strcmp(msg->getName(), "Data"))
  {
      DataPacket *tempData=check_and_cast<DataPacket *>(msg); //Casting to DataPacket class
      if(tempData->getDTEI()==ID)
             {
                 EV << "\t Message received by %d" << getFullName() << " node \n";
                 bubble("Packet Received");
             }
      delete(tempData);
  }

}
