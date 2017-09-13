//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_HLİST_H
#define CİTRUS_HLİST_H


#include "Form.h"

class HList : public Form {
public:
    explicit HList(Window& window);

    void add_element(Form& form);

private:
    Form& m_first;
    int m_max_height = 0;
};



#endif //CİTRUS_HLİST_H
