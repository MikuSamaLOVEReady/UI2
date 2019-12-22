//
// Created by twak on 11/11/2019.
//

#include "the_player.h"

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i){
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info); //第一次启动的时候
}

// change the image and video for one button every one second ??脑子有泡？
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}


void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    //printf("receive signal\n");
    switch (ms) {
        case QMediaPlayer::State::StoppedState:// 被停止了。
            // play some other video
            // setMedia( *infos -> at (rand() % infos->size() ).url); //随机播放？
            //printf("AA\n");

            play(); // starting playing again
    }
}

void ThePlayer::slider_clicked(){
    printf("AAA");
 //   setPosition();
}



void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url); //切换视频
    play();
}
