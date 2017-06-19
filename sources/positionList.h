#pragma once

#include <iostream>
#include <vector>

template <typename T>
class PositionList {
  public:
    PositionList()
            : m_positions() {

    }

    PositionList(T *positions)
            : m_positions(positions) {

    }

    void add(T value) {
        this->m_positions.push_back(value);
    }
    
    int32_t count()
    {
        return m_positions.size();
    }

    void print()
    {
        for (auto it = m_positions.begin(); it != m_positions.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    std::vector<T> m_positions;
};
