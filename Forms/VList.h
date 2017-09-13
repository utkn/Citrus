//
// Created by Utkan on 12.09.2017.
//

#ifndef CİTRUS_VLİST_H
#define CİTRUS_VLİST_H


#include "Form.h"

class VList : public Form {
public:
    explicit VList(Window& window);

    void add_element(Form& form);

private:
    Form& m_first;
    int m_max_width = 0;
};



#endif //CİTRUS_VLİST_H
