#pragma once

#include <iostream>
#include <unordered_set>

template<typename T>
class PositionList {
public:
    PositionList()
            : m_positions() {

    }

    PositionList(T *positions)
            : m_positions(positions) {

    }

    void add(T value) {
        this->m_positions.insert(value);
    }

    std::unordered_set<T> m_positions;
};
