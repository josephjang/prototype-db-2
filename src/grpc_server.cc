#include "grpc_server.h"
#include "spdlog/spdlog.h"

using grpc::StatusCode;

GRPCServer::GRPCServer(StorageEngine *storage_engine) {
  storage_engine_ = storage_engine;
}

GRPCServer::~GRPCServer() {}

Status GRPCServer::Get(ServerContext *context, const GetRequest *request,
                       GetResponse *response) {
  spdlog::info("GetRequest: key={}", request->key());
  auto result = storage_engine_->Get(request->key());
  if (!result.has_value()) {
    return Status(StatusCode::NOT_FOUND,
                  "the value is not found for the given key");
  }

  response->set_value(result.value());
  spdlog::info("GetResponse: value={}", response->value());
  return Status::OK;
}

Status GRPCServer::Set(ServerContext *context, const SetRequest *request,
                       SetResponse *response) {
  spdlog::info("SetRequest: key={}, value={}", request->key(),
               request->value());
  storage_engine_->Set(request->key(), request->value());
  return Status::OK;
}

Status GRPCServer::Delete(ServerContext *context, const DeleteRequest *request,
                          DeleteResponse *response) {
  spdlog::info("DeleteRequest: key={}", request->key());
  storage_engine_->Delete(request->key());
  return Status::OK;
}

Status GRPCServer::GetRange(ServerContext *context,
                            const GetRangeRequest *request,
                            GetRangeResponse *response) {
  spdlog::info("GetRangeRequest: startkey={}, stopkey={}", request->startkey(),
               request->stopkey());
  auto results =
      storage_engine_->GetRange(request->startkey(), request->stopkey());

  for (auto result : results) {
    response->add_values(result.second);
  }

  return Status::OK;
}
