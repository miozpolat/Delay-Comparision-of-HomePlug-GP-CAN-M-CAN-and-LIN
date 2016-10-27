//Message type to represent frame request of LIN
message Frame extends cMessage
{
    int STEI; // Source Terminal Equipment Identifier
    int DTEI; // Destinations Terminal Equipment Identifier 
}