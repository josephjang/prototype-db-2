#include "std_map_storage_engine.h"

#include <algorithm>

StandardMapStorageEngine::StandardMapStorageEngine() {}

StandardMapStorageEngine::~StandardMapStorageEngine() {}

std::optional<std::string> StandardMapStorageEngine::Get(
    const std::string &key) {
  auto it = map_.find(key);
  if (it != map_.end()) {
    return {it->second};
  } else {
    return std::nullopt;
  }
}

void StandardMapStorageEngine::Set(const std::string &key,
                                   const std::string &value) {
  map_.insert_or_assign(key, value);
}

void StandardMapStorageEngine::Delete(const std::string &key) {
  map_.erase(key);
}

std::vector<std::pair<std::string, std::string>>
StandardMapStorageEngine::GetRange(const std::string &start_key,
                                   const std::string &stop_key) {
  auto start_it = map_.lower_bound(start_key);
  auto stop_it = map_.upper_bound(stop_key);

  std::vector<std::pair<std::string, std::string>> results;

  std::copy(start_it, stop_it, results.begin());

  return results;
}
