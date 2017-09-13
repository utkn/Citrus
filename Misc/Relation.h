//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_RELATİON_H
#define CİTRUS_RELATİON_H


#include <functional>

class Relation {
public:
    using Function = std::function<int()>;

    Relation();

    Relation(Relation&& move) noexcept;

    Relation& operator=(Function&& function);

    int operator()() const;
private:
    Function m_function;
};



#endif //CİTRUS_RELATİON_H
