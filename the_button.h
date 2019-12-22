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
    //���캯�������ﱻ�����ʵ��
     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));//����趨�� ���ĸ߶ȺͿ��  200 110����� ͼƬ��Ȼ�ܴ� �����������button �Լ���С��ֱ��Ӱ������ͼƬ�Ĵ�С
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below

         //���Ƿ����ߣ���
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();

signals:
    void jumpTo(TheButtonInfo*);
    void clik(const QString &);

};

#endif //CW2_THE_BUTTON_H
