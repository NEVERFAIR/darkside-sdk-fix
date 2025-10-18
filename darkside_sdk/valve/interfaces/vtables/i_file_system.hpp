#include "../../../sdk/vfunc/vfunc.hpp"

class i_file_system
{
public:
    bool exists( const char* file_name, const char* a3 )
    {
        return vmt::call_virtual<bool>( this, 21, file_name, a3 );
    }
};
