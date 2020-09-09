#pragma once
#include <optional>
#include <string>
#include <vector>

class StorageEngine {
 public:
  virtual ~StorageEngine() {}
  virtual std::optional<std::string> Get(const std::string &key) = 0;
  virtual void Set(const std::string &key, const std::string &value) = 0;
  virtual void Delete(const std::string &key) = 0;
  virtual std::vector<std::pair<std::string, std::string>> GetRange(
      const std::string &start_key, const std::string &stop_key) = 0;
};
