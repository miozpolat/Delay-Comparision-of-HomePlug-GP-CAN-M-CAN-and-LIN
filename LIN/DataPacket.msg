//Message type to represent frame response of LIN
message DataPacket extends cMessage{
    int DTEI; // Destinations Terminal Equipment Identifier 
}