#pragma once
#include "protodb2.grpc.pb.h"

using grpc::ServerContext;
using grpc::Status;

class GRPCServer : public PrototypeDB2::Service {
 public:
  Status Get(ServerContext *context, const GetRequest *request,
             GetResponse *response);

  Status Set(ServerContext *context, const SetRequest *request,
             SetResponse *response);

  Status Delete(ServerContext *context, const DeleteRequest *request,
                DeleteResponse *response);

  Status GetRange(ServerContext *context, const GetRangeRequest *request,
                  GetRangeResponse *response);
};
