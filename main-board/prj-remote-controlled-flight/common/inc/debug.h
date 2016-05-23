/*
 *-----------------------------------------------------------------------------
 *  Filename:    debug.cpp
 *  Arquivo que implementa a funcao DEBUG() para mensagens de depuracao.
 *-----------------------------------------------------------------------------
 *     ___                           _
 *    / _ \_ __ ___/\   /\__ _ _ __ | |_
 *   / /_)/ '__/ _ \ \ / / _` | '_ \| __|
 *  / ___/| | | (_) \ V / (_| | | | | |_
 *  \/    |_|  \___/ \_/ \__,_|_| |_|\__|
 *
 *-----------------------------------------------------------------------------
 *
 */

#ifndef DEBUG_H
#define DEBUG_H

#include <ostream>
#include <iostream>

#define DEBUG_ENABLED 1

#define LEVEL_INFO      "INFO"
#define LEVEL_WARNING   "WARNING"

#define DEBUG(level, msg) if (!DEBUG_ENABLED) {} \
                   else dbglog() << __FILE__ << ":" << __LINE__ << " [ " << level << " ] " << msg

struct dbglog {
    std::ostream &os_;
    mutable bool has_endl_;
    dbglog (std::ostream &os = std::cerr) : os_(os), has_endl_(false) {}
    ~dbglog () { if (!has_endl_) os_ << std::endl; }
    template <typename T> static bool has_endl (const T &) { return false; }
    static bool has_endl (char c) { return (c == '\n'); }
    static bool has_endl (std::string s) { return has_endl(*s.rbegin()); }
    static bool has_endl (const char *s) { return has_endl(std::string(s)); }
    template <typename T>
    static bool same_manip (T & (*m)(T &), T & (*e)(T &)) { return (m == e); }
    const dbglog & operator << (std::ostream & (*m)(std::ostream &)) const {
        has_endl_ = same_manip(m, std::endl);
        os_ << m;
        return *this;
    }
    template <typename T>
    const dbglog & operator << (const T &v) const {
        has_endl_ = has_endl(v);
        os_ << v;
        return *this;
    }
};

#endif // DEBUG_H
