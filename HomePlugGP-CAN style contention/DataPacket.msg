//Mesage type to send payload in CAN.
message DataPacket {
    
    int STEI; // Source Terminal Equipment Identifier
    int DTEI; // Destination Terminal Equipment Identifier
}