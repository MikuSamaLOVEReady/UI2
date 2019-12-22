//
// Created by 罗瑞笛 on 2019/12/21.
//

#include "playerslider.h"

PlayerSlider::PlayerSlider(QWidget * parent) : QSlider(parent)
{
    //setOrientation(Qt::Horizontal);
    //setRange(0,100);
    //printf("MMMMMMM");



    m_bPressed = false;
}

void PlayerSlider::getplayer(ThePlayer* play){
    player=play;
   // printf("getget");

}

void PlayerSlider::onTimerOut(){

    setValue( player->position()*100/player->duration());

}




void PlayerSlider::mousePressEvent(QMouseEvent *e)
{
    QSlider::mousePressEvent(e);
    double pos = e->pos().x() / (double)width();
    setValue(pos * (100 - 0) + 0);
    emit sliderPressed();
}


/*
void PlayerSlider::mouseMove(QMouseEvent *e)
{
    QSlider::mouseMoveEvent(e);//必须有这句，否则手动不能移动滑块
}

void PlayerSlider::mouseRelease(QMouseEvent *e)
{
    m_bPressed = false;
    qint64 i64Pos = value();
    emit sigProgress(i64Pos);

    QSlider::mouseReleaseEvent(e);//必须有这句，否则手动不能移动滑块
}
*/
void PlayerSlider::setProgress(qint64 i64Progress) {
    if (!m_bPressed)
        setValue(i64Progress);
}


