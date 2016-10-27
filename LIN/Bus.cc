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
Define_Module(Bus); // It is required to this object to see in the simulation

Bus::Bus() {
    // TODO Auto-generated constructor stub
}

Bus::~Bus() {
    // TODO Auto-generated destructor stub
}
void Bus::initialize()
{
    //Gets the ID of this module and assigns.
    ID=getId();
}
void Bus::handleMessage(cMessage *msg)
{
   //Sends a copy of received message to every node
  for(int i=0;i<NumberOfNodes;i++)
  {
      send(msg->dup(), "g$o",i);
  }
  delete(msg);
}
