//
// Created by twak on 11/11/2019.
//

#include "the_player.h"
#include <PlayerSlider.h>

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i){
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info); //��һ��������ʱ��
}

// change the image and video for one button every one second ??�������ݣ�
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}


void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    //printf("receive signal\n");
    switch (ms) {
        case QMediaPlayer::State::StoppedState:// ��ֹͣ�ˡ�
            // play some other video
            // setMedia( *infos -> at (rand() % infos->size() ).url); //������ţ�
            //printf("AA\n");

            play(); // starting playing again
    }
}


void ThePlayer::slider_clicked(){

   this->setPosition(cur_slider->value()*this->duration()/100);
}

void ThePlayer::slider_clicked2(){
    this->setVolume(vol_slider->value());
    //printf("%d\n",vol_slider->value());
}

void ThePlayer::progress_moved(){
    TM->stop();
    this->setPosition(cur_slider->value()*this->duration()/100);
    //printf("dKMKMKM");
}


void ThePlayer::progress_released(){
    TM->start();
}

void ThePlayer::getslider(PlayerSlider* slid1,PlayerSlider* slid2){
    cur_slider=slid1;
    vol_slider=slid2;
};

void ThePlayer::gertimer(QTimer* TIM){
    TM=TIM;
}


void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url); //�л���Ƶ
    play();
}

