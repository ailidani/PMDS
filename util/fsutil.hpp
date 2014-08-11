
#ifndef FSUTIL_HPP
#define FSUTIL_HPP

#include <cassert>
#include <string>
#include <vector>
#include <errno.h>
#include <pwd.h>

namespace fsutil {

std::string get_os_type()
{
    char *ostype;

    ostype = getenv("OSTYPE");
    if (ostype == NULL)
        return "unknown";

    return ostype;
}

std::string get_home()
{
    char *path;

    path = getenv("HOME");
    if (path == NULL)
        return "";

    return path;
}

std::string get_full_name()
{
    struct passwd *pw = getpwuid(getuid());

    // XXX: Error handling
    assert(pw != NULL);

    if (pw->pw_gecos != NULL)
        return std::string(pw->pw_gecos);
    else
        return "";
}

std::vector<std::string> path_to_vector(const std::string &path)
{
    size_t pos = 0;
    std::vector<std::string> rval;

    if (path[0] == '/')
        pos = 1;

    while (pos < path.length()) {
        size_t end = path.find('/', pos);
        if (end == path.npos) {
            rval.push_back(path.substr(pos));
            break;
        }

        rval.push_back(path.substr(pos, end - pos));
        pos = end + 1;
    }

    return rval;
}

}


#endif
