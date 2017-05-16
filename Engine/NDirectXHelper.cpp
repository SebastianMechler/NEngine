#include "NDirectXHelper.h"

#include <Windows.h>

bool Nully::NDirectXFailed(long a_result)
{
  if (FAILED(a_result))
  {
    LPTSTR buffer;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, nullptr, (DWORD)a_result, LANG_USER_DEFAULT, (LPTSTR)&buffer, 0, nullptr);

    MessageBox(0, buffer, TEXT("Fatal error"), MB_OK | MB_ICONERROR);
    LocalFree(buffer);
    return true;
  }
  return false;
}
