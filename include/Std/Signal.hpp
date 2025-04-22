#pragma once

#include "boost/signals2.hpp"
#include <boost/signals2/connection.hpp>

template <typename T>
using Signal = boost::signals2::signal<T>;

using Connection = boost::signals2::connection;