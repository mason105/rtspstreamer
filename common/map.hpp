#ifndef __common_map_hpp__
#define __common_map_hpp__

#include <map>
#include <boost/thread/mutex.hpp>
#include "exception.hpp"

namespace common {

template <class Key, class Value>
class map {
    typedef std::map<Key, Value> map_t;
public:
    map() {}

    inline Value & operator[](Key const & key) {
        boost::mutex::scoped_lock sl(mtx);
        return map_[key];
    }
    inline Value const & operator[](Key const & key) const {
        boost::mutex::scoped_lock sl(const_cast<map*>(this)->mtx);
        typename map_t::const_iterator i = map_.find(key);
        if (i != map_.end()) {
            return i->second;
        }
        throw std::out_of_range("out of range"); 
    }
    inline size_t const count(Key const  & key) const {
        boost::mutex::scoped_lock sl(mtx);
        return map_.count(key);
    }
    inline void insert(Key const & key, Value const & value) {
        boost::mutex::scoped_lock sl(mtx);
        map_.insert(std::make_pair<Key, Value>(key, value));
    }
    inline void erase(Key const & key) {
        boost::mutex::scoped_lock sl(mtx);
        map_.erase(key);
    }
    inline void clear() {
        boost::mutex::scoped_lock sl(mtx);
        map_.clear();
    }   
    inline size_t const size() const {
        boost::mutex::scoped_lock sl(mtx);
        return map_.size();
    }
    inline bool const exists(Key const & key) const {
        boost::mutex::scoped_lock sl(mtx);
        return map_.count(key) > 0;
    }

private:
    boost::mutex mtx;
    map_t map_;
};

} // namespace common

#endif

