#pragma once
#include "protodb2.grpc.pb.h"
#include "storage_engine.h"

using grpc::ServerContext;
using grpc::Status;

class GRPCServer : public PrototypeDB2::Service {
public:
  GRPCServer(StorageEngine *storage_engine);

  ~GRPCServer();

  Status Get(ServerContext *context, const GetRequest *request,
             GetResponse *response);

  Status Set(ServerContext *context, const SetRequest *request,
             SetResponse *response);

  Status Delete(ServerContext *context, const DeleteRequest *request,
                DeleteResponse *response);

  Status GetRange(ServerContext *context, const GetRangeRequest *request,
                  GetRangeResponse *response);

private:
  StorageEngine *storage_engine_;
};
