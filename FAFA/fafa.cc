#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/csma-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

// Structure to represent a STA
struct STA {
  uint32_t id;
  double tht;
  double agg_size;
  uint8_t app_type; // 0 for UDP, 1 for TCP
};

// Function to compute the FI value
double ComputeFI(std::vector<STA> &stas) {
  double sum1 = 0.0;
  double sum2 = 0.0;
  for (auto &sta : stas) {
    sum1 += sta.tht;
    sum2 += sta.tht * sta.tht;
  }
  return (sum1 * sum1) / (stas.size() * sum2);
  //NS_LOG_INFO("FI value: " << ComputeFI(stas));
}

// Function to compute the Net_THT value
double ComputeNetTHT(std::vector<STA> &stas) {
  double net_tht = 0.0;
  for (auto &sta : stas) {
    net_tht += sta.tht;
  }
  return net_tht;
}

// Function to update AGG_SIZE values based on APP_TYPE and FI value
void UpdateAggSizes(std::vector<STA> &stas, double fi, double past_tht) {
  double net_tht = ComputeNetTHT(stas);
  if (fi > 0.7) {
    // No changes to AGG_SIZE
  } else {
    if (net_tht >= past_tht) {
      for (auto &sta : stas) {
        if (sta.app_type == 0) {
          sta.agg_size *= 0.8;
        } else if (sta.app_type == 1) {
          sta.agg_size *= 0.9;
        }
      }
    } else {
      for (auto &sta : stas) {
        if (sta.app_type == 0) {
          sta.agg_size *= 1.05;
        } else if (sta.app_type == 1) {
          sta.agg_size *= 1.1;
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  // Set up the simulation environment
  CommandLine cmd;
  cmd.Parse(argc, argv);

  // Create nodes
  NodeContainer nodes;
  nodes.Create(2);

  // Create point-to-point link
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
  pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));
  //pointToPoint.EnablePcap("my-pcap-file", devices);
  NetDeviceContainer devices = pointToPoint.Install(nodes);

  // Install internet stack
  InternetStackHelper stack;
  stack.Install(nodes);

  // Assign IP addresses
  Ipv4AddressHelper ipv4;
  ipv4.SetBase("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer interfaces = ipv4.Assign(devices);

  // Create applications
  UdpEchoServerHelper server(9);
  ApplicationContainer serverApps = server.Install(nodes.Get(1));
  serverApps.Start(Seconds(1.0));
  serverApps.Stop(Seconds(10.0));

  UdpEchoClientHelper client(interfaces.GetAddress(1), 9);
  client.SetAttribute("MaxPackets", UintegerValue(100));
  client.SetAttribute("Interval", TimeValue(Seconds(1.0)));
  client.SetAttribute("PacketSize", UintegerValue(1024));
  ApplicationContainer clientApps = client.Install(nodes.Get(0));
  clientApps.Start(Seconds(2.0));
  clientApps.Stop(Seconds(10.0));
  
  //NetAnim
  AnimationInterface anim("fafa.xml");
  
  //ASCIImetrics
  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll(ascii.CreateFileStream("fafa.tr"));
  pointToPoint.EnablePcapAll("fafa");
  
  // Set up the simulation
  Simulator::Stop(Seconds(10.0));

  // Run the simulation
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
