//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>

class PlayerSlider;

using namespace std;

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;
    PlayerSlider *cur_slider;
    PlayerSlider *vol_slider;
    QTimer *TM;

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(30); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
        //setPosition();
        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between ...
        //mTimer->start();
        connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
        //
    }

    void   getslider(PlayerSlider* slid1,PlayerSlider* slid2);
    void   gertimer(QTimer* TIM);

    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);

private slots:

    // change the image and video for one button every one second
    void shuffle();
    void playStateChanged (QMediaPlayer::State ms);




public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void slider_clicked(); //函数类型 和 参数 未定
    void slider_clicked2();
    void progress_moved();
    void progress_released();
};

#endif //CW2_THE_PLAYER_H
