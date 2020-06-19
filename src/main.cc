#include "spdlog/spdlog.h"
#include "cxxopts.hpp"

const cxxopts::ParseResult& ParseCommandlineArgs(int argc, char *argv[]) noexcept {
  try {
    cxxopts::Options options("protodb2", "prototype database #2");

    return options.parse(argc, argv);
  } catch (const cxxopts::OptionException& e) {
    spdlog::error("{}", e.what());
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  const auto& result = ParseCommandlineArgs(argc, argv);

  spdlog::set_level(spdlog::level::info);

  return 0;
}
