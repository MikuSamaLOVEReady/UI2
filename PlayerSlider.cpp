//
// Created by ����� on 2019/12/21.
//

#include "playerslider.h"

PlayerSlider::PlayerSlider(QWidget * parent) : QSlider(parent)
{
    setOrientation(Qt::Horizontal);
    setRange(0,1000);



    m_bPressed = false;
}

void PlayerSlider::getplayer(ThePlayer* play){
    player=play;
    printf("getget");

}

void PlayerSlider::onTimerOut(){

    setValue( player->position()*1000/player->duration());
    
}
//������
/*
void PlayerSlider::mousePress(QMouseEvent *e)
{
    m_bPressed = true;
    QSlider::mousePressEvent(e);//��������䣬�����ֶ������ƶ�����


}

void PlayerSlider::mouseMove(QMouseEvent *e)
{
    QSlider::mouseMoveEvent(e);//��������䣬�����ֶ������ƶ�����
}

void PlayerSlider::mouseRelease(QMouseEvent *e)
{
    m_bPressed = false;
    qint64 i64Pos = value();
    emit sigProgress(i64Pos);

    QSlider::mouseReleaseEvent(e);//��������䣬�����ֶ������ƶ�����
}
*/
void PlayerSlider::setProgress(qint64 i64Progress) {
    if (!m_bPressed)
        setValue(i64Progress);
}


