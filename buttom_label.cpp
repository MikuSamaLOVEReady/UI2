//
// Created by twak on 14/10/2019.
//

#include <QFrame>
#include "buttom_label.h"
#include <QUrl>

void buttomlabel::setbutText(TheButtonInfo *buttonInfo) {


    QString st1;
    st1 = buttonInfo->url->toEncoded();
    setText( st1 );
}