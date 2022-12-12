#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#define DEF_CMD(cmd, number_cmd, arg, ...)    \
        cmd = number_cmd,                     \

enum comand { 
    #include "config.hpp"
};

#undef DEF_CMD

#endif