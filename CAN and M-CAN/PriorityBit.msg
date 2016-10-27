
// Message type to describe identifier field of CAN
//Eventually, it priortize some messages
message PriorityBit {
    
    int bit; // Stores bit value (0 and 1 or dominant and recessive)
    int bitIndex; // Stores index of current identifier. Its range is 11.
}