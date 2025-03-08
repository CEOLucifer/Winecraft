#pragma once

#include <memory>

template<typename T>
using Sp = std::shared_ptr<T>;

template<typename T>
using Wp = std::weak_ptr<T>;

template<typename T>
using Up = std::unique_ptr<T>;
