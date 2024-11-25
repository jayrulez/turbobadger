#include "platform/tb_file_interface.h"

#include <stdio.h>
#include <map>

namespace tb
{
    class TBFileInterfacePosix : public tb::TBFileInterface
    {
    public:
        tb::TBFileHandle Open(const char* filename, TBFileMode mode) override;
        void Close(tb::TBFileHandle file) override;

        long Size(tb::TBFileHandle file) override;
        size_t Read(tb::TBFileHandle file, void* buf, size_t elemSize, size_t count) override;

        std::map<size_t, FILE*> m_openFiles;
    };
}