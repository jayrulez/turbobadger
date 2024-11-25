#include "platform/tb_file_interface.h"

#include <stdio.h>
#include <map>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/configuration.h>

namespace tb
{
    class TBFileInterfaceAndroid : public tb::TBFileInterface
    {
    public:
        TBFileInterfaceAndroid();
        virtual ~TBFileInterfaceAndroid();
    
        tb::TBFileHandle Open(const char* filename, TBFileMode mode) override;
        void Close(tb::TBFileHandle file) override;

        long Size(tb::TBFileHandle file) override;
        size_t Read(tb::TBFileHandle file, void* buf, size_t elemSize, size_t count) override;

        std::map<size_t, AAsset*> m_openFiles;
    };
}