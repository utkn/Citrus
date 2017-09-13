//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_RELATİON_H
#define CİTRUS_RELATİON_H


#include <functional>

class Relation {
public:
    using Function = std::function<int()>;

    Relation() {
        m_function = []() -> int { return 0; };
    }

    Relation(Relation&& move) noexcept : m_function{std::move(move.m_function)} {
    }

    Relation& operator=(Function&& function) {
        m_function = std::move(function);
        return *this;
    }

    int operator()() const {
        return m_function();
    }
private:
    Function m_function;
};



#endif //CİTRUS_RELATİON_H
