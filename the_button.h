//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H


#include <QtWidgets/QPushButton>


class TheButtonInfo {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display

    TheButtonInfo ( QUrl* url, QIcon* icon) : url (url), icon (icon) {}
};

class TheButton : public QPushButton {
    Q_OBJECT

public:
    TheButtonInfo* info;
    //构造函数在这里被定义和实现
     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));//这个设定了 死的高度和宽度  200 110最合适 图片虽然很大， 但是如果外层的button 自己很小会直接影响整个图片的大小
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below

         //他是发出者？？
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();

signals:
    void jumpTo(TheButtonInfo*);
    void clik(const QString &);

};

#endif //CW2_THE_BUTTON_H
