
#include <Node.h>
Define_Module(Node); // It is required to see this object in simulation window

Node::Node()
{
    // TODO Auto-generated constructor stub
}

Node::~Node()
{
    // TODO Auto-generated destructor stub
}

void Node::initialize()
{
    // Signal Registering to emit access delay
    arrivalSignal = registerSignal("arrival");
    // This message initiates first tranmission attempt with a random time.
    cMessage *first =new cMessage("first");
    scheduleAt(RandomAccessTime(),first);
}
void Node::handleMessage(cMessage *msg)
{

    if (!strcmp(msg->getName(), "lostContention")||!strcmp(msg->getName(), "busOccupied"))
         {
           isLostContention=true;
           LostContentionTime=msg->getArrivalTime();
           cancelEvent(msg);
           bubble("Lost Contention");

         }

    if(!strcmp(msg->getName(), "Acked")|| !strcmp(msg->getName(), "first"))
    {

        if (!strcmp(msg->getName(), "Acked"))
        {
           Ack *temp = check_and_cast<Ack *>(msg); // Cast the message to a Ack
           if(temp->getSTEI()==getId())
           {
               AccessDelay=temp->getArrivalTime().dbl()-InitialBusCheckTime.dbl()-entireCanFrameSize*Tbit2; //136 bit last frame extraction
               emit(arrivalSignal,AccessDelay );
               InitialBusCheckTime=0;
               AccessDelay=0;
               resetAccesDelay=true;
           }
           else
           {
               resetAccesDelay=false;
           }
        }

       cMessage *test =new cMessage("busCheck");
       sendDelayed(test,Tbit2,"g$o"); //start bit of new transmision
       if(resetAccesDelay==true)
       {
           InitialBusCheckTime=test->getSendingTime();
       }
       cancelEvent(msg);
    }
    if(!strcmp(msg->getName(), "bit"))
    {
        if(isLostContention==true)
        {
            cancelEvent(msg);
        }
        else
        {
            send(msg,1);
        }
    }

     if (!strcmp(msg->getName(), "busEmpty"))
    {
         priorityBits.clear();
         priorityBits=priorityGenerator();
         isLostContention=false;
         //Scheduling 11 self*messages for 11 bit identifier
        for(int i=0;i<identifierLength;i++)
        {
         PriorityBit *temp = new PriorityBit("bit");
         temp->setBit(priorityBits[i]);
         temp->setBitIndex(i);
         scheduleAt(simTime()+Tbit2*(i+1),temp);
       }
    }
     if(!strcmp(msg->getName(), "wonContention"))
    {
     cMessage *rtrAndControl=new cMessage("RtrAndControlBits");
     sendDelayed(rtrAndControl,7*Tbit2,1); //6 bit control and 1 bit rtr in total 7 bit.
     DataPacket *data=new DataPacket("data");
     data->setSTEI(getId());
     scheduleAt(simTime()+(64+7)*Tbit2,data); //64 bit data and 7 bit Checksum size
     cancelEvent(msg);
     bubble("Won Contention");

    }
     if(!strcmp(msg->getName(), "data"))
     {
         send(msg,1); // 64 bit- 8byte data send  for 10us bit time
     }

}

//Creates identifer field with random bits
std::vector<int> Node::priorityGenerator()
{
  std::vector<int> temp;
  int a;
  for(int i=0;i<identifierLength;i++)
  {
      a=(int)rand()%2;
      temp.push_back(a);
  }
  return temp;
}

//Generates random access time to send initial "first" message to the bus
simtime_t Node::  RandomAccessTime()
{
    simtime_t time = simTime()+ intuniform(0, 50)/100;
    return time;
}
