#include <ndn-cxx/face.hpp>
#include <ndn-cxx/security/key-chain.hpp>
#include <ndn-cxx/mgmt/nfd/controller.hpp>

using namespace ndn;

int
main(int argc, char** argv)
{
  if (argc != 2) {
    std::cerr << "Usage: \n  " << argv[0] << " hub-host-or-ip";
    return 1;
  }

  KeyChain keyChain;
  Face face(argv[1]);
  nfd::Controller ctrl(face, keyChain);
  Scheduler scheduler(face.getIoService());

  nfd::ControlParameters params;
  params.setName("/test/prefix");
  params.setFlags(nfd::ROUTE_FLAG_CHILD_INHERIT);

  nfd::CommandOptions options;
  options.setPrefix("/localhop/nfd");

  ctrl.start<nfd::RibRegisterCommand>
    (params,
     [&] (const nfd::ControlParameters&) {
      std::cerr << "SUCCESS waiting" << std::endl;

      scheduler.scheduleEvent(time::seconds(100), [] {
          std::cerr << "DONE" << std::endl;
        });
    },
     [&] (const nfd::ControlResponse& resp) {
       std::cerr << "FAILURE: " << resp.getText() << std::endl;
     },
     options);

  face.processEvents();

  return 0;
}
