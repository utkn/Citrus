//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_SLOT_H
#define CİTRUS_SLOT_H

#include <functional>
#include <vector>

template <typename... Args>
class Slot {
public:
    using Callback = std::function<void(Args...)>;
    void add(Callback&& callback) {
        m_callbacks.emplace_back(std::move(callback));
    }
    void invoke(Args... args) {
        for(auto& callback : m_callbacks) {
            callback(args...);
        }
    }
private:
    std::vector<Callback> m_callbacks;
};


#endif //CİTRUS_SLOT_H
