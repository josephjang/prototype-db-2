#include "cxxopts.hpp"
#include "spdlog/spdlog.h"

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

int main(int argc, char *argv[]) {
  ParseCommandlineArgs(argc, argv);

  spdlog::set_level(spdlog::level::info);

  return 0;
}
