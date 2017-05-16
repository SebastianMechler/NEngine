#pragma once

namespace Nully
{
  enum class NResult
  {
    Success,
    Nullptr,

    FileOpenError,
    FileWriteError,
    FileReadError,
    FileReadLineError,

    ProcessWriteError,
    ProcessWriteErrorSize,
    ProcessOpenError,
    ProcessReadError,
    ProcessReadErrorSize,
    ProcessAllocateError,
    ProcessProtectError,

    RemoteThreadCreationFailed,
    RemoteThreadAlreadyExists,
  };
}