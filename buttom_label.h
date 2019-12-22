//
// Created by ÂÞÈðµÑ on 2019/12/22.
//

#ifndef CWK2_BUTTOM_LABEL_H
#define CWK2_BUTTOM_LABEL_H

#include <QLabel>
#include "the_button.h"
#include <QtCore/QObject>

//
// Created by ÂÞÈðµÑ on 2019/12/22.
//
class buttomlabel : public QLabel {
Q_OBJECT
public slots:
    void setbutText(TheButtonInfo* buttonInfo);

private:
    TheButton   *button;


};



#endif //CWK2_BUTTOM_LABEL_H
