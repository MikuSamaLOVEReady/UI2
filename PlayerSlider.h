//
// Created by ����� on 2019/12/21.
//

#ifndef CWK2_PLAYERSLIDER_H
#define CWK2_PLAYERSLIDER_H

#include <QSlider>
#include <QMouseEvent>
#include "the_player.h"


class PlayerSlider : public QSlider
{
    Q_OBJECT
public:
    PlayerSlider(QWidget * parent = 0);
    void        getplayer(ThePlayer* play);
    void        setProgress(qint64);
    signals:
    void        sigProgress(qint64);
private:
    bool        m_bPressed;
    int         curren;
    ThePlayer   *player;

public slots:
    void onTimerOut();
/*
signals:
    void        AA(QMouseEvent *);  //�Լ��Ķ�������
    void        VV(QMouseEvent *);   //�Ǽ̳ж���
    void        CC(QMouseEvent *); //��Ӧ����
*/
};



#endif //CWK2_PLAYERSLIDER_H
