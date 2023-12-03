#ifndef PLUGIN_INTERFACE_H
#define PLUGIN_INTERFACE_H

#include <cinttypes>

//==================================================================================================

namespace plugin
{
    template<class T>
    struct Array
    {
    // member functions
    public:
        explicit inline  Array(const uint64_t &size, T *data);
                 inline ~Array();

    // member data
    public:
        uint64_t size;
        T       *data;
    };

    //--------------------------------------------------------------------------------------------------

    template<class T> inline Array<T>::Array(const uint64_t &size_, T *data_):
    size(size_),
    data(data_)
    {}

    //--------------------------------------------------------------------------------------------------

    template<class T> inline Array<T>::~Array()
    {
        delete[] data;
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    enum class InterfaceType
    {
        Tool,
        Filter
    };

    struct Interface
    {
        virtual Array<const char *> get_param_names()                     = 0;
        virtual Array<double>       get_params     ()                     = 0;
        virtual void                set_params     (Array<double> params) = 0;
    };
}

#endif // PLUGIN_INTERFACE_H
