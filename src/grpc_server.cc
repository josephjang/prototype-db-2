#include "grpc_server.h"

Status GRPCServer::Get(ServerContext *context, const GetRequest *request,
                       GetResponse *response) {
  return Status::OK;
}

Status GRPCServer::Set(ServerContext *context, const SetRequest *request,
                       SetResponse *response) {
  return Status::OK;
}

Status GRPCServer::Delete(ServerContext *context, const DeleteRequest *request,
                          DeleteResponse *response) {
  return Status::OK;
}

Status GRPCServer::GetRange(ServerContext *context,
                            const GetRangeRequest *request,
                            GetRangeResponse *response) {
  return Status::OK;
}
