// hash_pair.h


#pragma pmce
#include <functional>

namespace std {
    template <>
    struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& p) const {
            string s = to_string(p.first) + "@$" + to_string(p.second);
            auto string_hash = hash<string>{}(s);
            
            return string_hash;  
        }
    };
}