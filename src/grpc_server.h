#include "protodb2.grpc.pb.h"

using grpc::ServerContext;
using grpc::Status;

class GRPCServer : public PrototypeDB2::Service {
  Status Get(ServerContext *context, const GetRequest *request,
             GetResponse *response) {
    return Status::OK;
  }

  Status Set(ServerContext *context, const SetRequest *request,
             SetResponse *response) {
    return Status::OK;
  }

  Status Delete(ServerContext *context, const DeleteRequest *request,
                DeleteResponse *response) {
    return Status::OK;
  }

  Status GetRange(ServerContext *context, const GetRangeRequest *request,
                  GetRangeResponse *response) {
    return Status::OK;
  }
};
