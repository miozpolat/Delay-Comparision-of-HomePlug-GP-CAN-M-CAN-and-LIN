
package newlin;
// Slave module of LIN with one gate and definition of access delay signal
simple Slave
{
    parameters:
        @display("i=device/cpu_s");
        @signal[arrival](type="double");
        @statistic[AccessDelay](title="Access Delay"; source="arrival"; record=vector,stats; interpolationmode=none);
    gates:
        inout g;
}
// Master module of LIN with one gate and definition of access delay signal
simple Master
{
    parameters:
        @display("i=device/cpu_l");
        @signal[arrival](type="double");
        @statistic[AccessDelay](title="Access Delay"; source="arrival"; record=vector,stats; interpolationmode=none);

    gates:
        inout g;
}
// Bus  module of LIN with 10 gates
simple Bus
{
    parameters:
        @display("p=500,300;b=1800,8,rectangle,blue;o=#408060");
    gates:
        inout g[10]; 
}


//Network connection of LIN with display properties
network newlin
{
    parameters:
        @display("bgb=2500,1000,white,black");
    submodules:
        Slave[9]: Slave {
            parameters:
                @display("p=200,250,r,200");
        }
        Master: Master {
            parameters:
                @display("p=1250,750");
        }
        Bus: Bus {
            @display("p=1250,500;b=2200,8,,,blue,2");

        }
    connections:
        Slave[0].g <--> Bus.g[0];
        Slave[1].g <--> Bus.g[1];
        Slave[2].g <--> Bus.g[2];
        Slave[3].g <--> Bus.g[3];
        Slave[4].g <--> Bus.g[4];
        Slave[5].g <--> Bus.g[5];
        Slave[6].g <--> Bus.g[6];
        Slave[7].g <--> Bus.g[7];
        Slave[8].g <--> Bus.g[8];
        Master.g <--> Bus.g[9];
}
