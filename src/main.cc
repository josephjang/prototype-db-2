#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>

#include "cxxopts.hpp"
#include "grpc_server.h"
#include "spdlog/spdlog.h"
#include "std_map_storage_engine.h"

using grpc::Server;
using grpc::ServerBuilder;

const void ParseCommandlineArgs(int argc, char *argv[]) noexcept {
  try {
    cxxopts::Options options("protodb2", "prototype database #2");

    options.add_options()("h,help", "Print usage");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help() << std::endl;
      exit(0);
    }
  } catch (const cxxopts::OptionException &e) {
    spdlog::error("{}", e.what());
    exit(1);
  }
}

void RunServer() {
  std::string server_address("0.0.0.0:50051");

  StandardMapStorageEngine storage_engine;

  GRPCServer grpcServer(&storage_engine);

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&grpcServer);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char *argv[]) {
  ParseCommandlineArgs(argc, argv);

  spdlog::set_level(spdlog::level::info);

  RunServer();

  return 0;
}
