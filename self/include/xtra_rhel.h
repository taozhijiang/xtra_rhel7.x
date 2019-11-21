/*-
 * Copyright (c) 2018-2019 TAO Zhijiang<taozhijiang@gmail.com>
 *
 * Licensed under the BSD-3-Clause license, see LICENSE for full information.
 *
 */


#ifndef __XTRA_RHEL7x_H__
#define __XTRA_RHEL7x_H__

// GNU
#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x)       (x)
#define unlikely(x)     (x)
#endif


// USING NP_DEBUG to control SAFE_ASSERT expand
#include <boost/assert.hpp>
#undef NDEBUG  // needed by handler
#ifndef NP_DEBUG
// default, expand to ::assert, will abort
#else
// custom assert print but not abort, define your own assertion_failed
#define BOOST_ENABLE_ASSERT_HANDLER
#endif
#define SAFE_ASSERT(expr) BOOST_ASSERT(expr)


#include <cstdint>         // int64_t ...
#include <linux/limits.h>  // PATH_MAX


// or will get unique_future
#define BOOST_THREAD_PROVIDES_FUTURE
#define BOOST_THREAD_PROVIDES_FUTURE_CONTINUATION
#define BOOST_THREAD_PROVIDES_FUTURE_WHEN_ALL_WHEN_ANY

#include <boost/thread.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <functional>      // bind

// make_unqiue patch ...
#include <memory> 
template<typename T, typename... Ts>
std::unique_ptr<T> make_unique(Ts&&... params){
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
}

#if __cplusplus >= 201103L
#include <chrono>
using std::chrono::milliseconds;
using std::chrono::seconds;
#else
#include <boost/chrono.hpp>
using boost::chrono::milliseconds;
using boost::chrono::seconds;
#endif


template <typename T>
inline void ignore_unused(T const&) {}

#define __noncopyable__(class_name) \
    private:\
    class_name(const class_name&) = delete;\
    class_name& operator=(const class_name&) = delete;

#define __auto_lock__(lock_name) \
    std::lock_guard<std::mutex> __lock_##__FILE__##__LINE__ (lock_name);

// define these for RHEL-7.x
#define __XTRA_RHEL_VERSION__ 7

#endif //__XTRA_RHEL7x_H__
