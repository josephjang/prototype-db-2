#pragma once
#include <map>
#include <shared_mutex>

#include "storage_engine.h"

class StandardMapStorageEngine : public StorageEngine {
public:
  StandardMapStorageEngine();
  ~StandardMapStorageEngine();

  std::optional<std::string> Get(const std::string &key);

  void Set(const std::string &key, const std::string &value);

  void Delete(const std::string &key);

  std::vector<std::pair<std::string, std::string>>
  GetRange(const std::string &start_key, const std::string &stop_key);

private:
  std::map<std::string, std::string> map_;
  std::shared_mutex mutex_;
};
