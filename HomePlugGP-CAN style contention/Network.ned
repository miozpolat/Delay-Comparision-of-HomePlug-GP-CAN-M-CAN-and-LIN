
package canbus;

//Definition of node of CAN. Each has single gate.
//Also, it has a signal type to measure access delay
simple Node
{
    parameters:
        @display("i=device/cpu_s");
        @signal[arrival](type="double");
        @statistic[AccessDelay](title="Access Delay"; source="arrival"; record=vector,stats; interpolationmode=none);
    gates:
        inout g;
}
//Definition of bus module of CAN. For 12-nodes case, it includes 12 gates.
simple Bus
{
    parameters:
        @display("p=500,300;b=2000,8,rectangle,blue;o=#408060");
    gates:
        inout g[4];
}

//The network module describes positioning of each node and bus. 
//Also it describes all connections.
network homecan
{
    parameters:

        @display("bgb=2500,1000,white");
    submodules:

        Node[4]: Node {
            parameters:
                @display("p=200,250,r,200");
        }
        Bus: Bus {
            @display("p=1250,500;b=2400,8,,,blue,2");
        }
    connections:
        Node[0].g <--> Bus.g[0];
        Node[1].g <--> Bus.g[1];
        Node[2].g <--> Bus.g[2];
       Node[3].g <--> Bus.g[3];
//        Node[4].g <--> Bus.g[4];
//        Node[5].g <--> Bus.g[5];
//        Node[6].g <--> Bus.g[6];
//        Node[7].g <--> Bus.g[7];
//        Node[8].g <--> Bus.g[8];
//        Node[9].g <--> Bus.g[9];
//        Node[10].g <--> Bus.g[10];
//        Node[11].g <--> Bus.g[11];
}
