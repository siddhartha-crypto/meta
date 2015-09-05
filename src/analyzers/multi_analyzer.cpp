/**
 * @file multi_analyzer.cpp
 */

#include "analyzers/multi_analyzer.h"

namespace meta
{
namespace analyzers
{

template <class T>
multi_analyzer<T>::multi_analyzer(
    std::vector<std::unique_ptr<analyzer<T>>>&& toks)
    : analyzers_{std::move(toks)}
{
    /* nothing */
}

template <class T>
multi_analyzer<T>::multi_analyzer(const multi_analyzer& other)
{
    analyzers_.reserve(other.analyzers_.size());
    for (const auto& an : other.analyzers_)
        analyzers_.emplace_back(an->clone());
}

template <class T>
void multi_analyzer<T>::tokenize(corpus::document& doc)
{
    for (auto& tok : analyzers_)
        tok->tokenize(doc);
}

template class multi_analyzer<uint64_t>;
template class multi_analyzer<double>;
}
}
