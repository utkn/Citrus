//
// Created by Utkan on 13.09.2017.
//

#include "Relation.h"

Relation::Relation() {
    m_function = []() -> int { return 0; };
}

Relation::Relation(Relation &&move) noexcept : m_function{std::move(move.m_function)} {
}

Relation &Relation::operator=(Relation::Function &&function) {
    m_function = std::move(function);
    return *this;
}

int Relation::operator()() const {
    return m_function();
}
