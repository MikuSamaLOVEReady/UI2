/*
 *
 *    ______
 *   /_  __/___  ____ ___  ___  ____
 *    / / / __ \/ __ `__ \/ _ \/ __ \
 *   / / / /_/ / / / / / /  __/ /_/ /
 *  /_/  \____/_/ /_/ /_/\___/\____/
 *              video for no reason
 *
 * 2811 cw2 November 2019 by twak
 */

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QImageReader>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QLabel>
#include <QScrollArea>
#include <QSlider>
#include "the_player.h"
#include "the_button.h"
#include "PlayerSlider.h"


using namespace std;

// read in videos and thumbnails to this directory
vector<TheButtonInfo> getInfoIn (string loc) {

    vector<TheButtonInfo> out =  vector<TheButtonInfo>(); // container list for all the information
    //int a =0;

    QDirIterator it(QString::fromStdString(loc), QDir::Files);

    while (it.hasNext()) { // for all files 搜索全部文件 当遇到视频文件 则直接查找是否存在相对应的 缩略图，找到后立刻创建成按钮信息存入list

		QString f = it.next();

        if (!f.contains(".png")) { // if it isn't an image
            QString thumb = f.left( f .length() - 3) +"png";
            if (QFile(thumb).exists()) { // but a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb); // 从名字读取 对应 缩略图的信息
                    QImage sprite = imageReader->read(); // 把读取出来的内容 赋给图片
					if (!sprite.isNull()) {  //如果这个图片 被加载出来的话。
						QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // 读取到图片成为了 按钮的图标。什么图对应什么什么连接
						QUrl* url = new QUrl(QUrl::fromLocalFile(f)); //将文件路径转换成URL convert the file location to a generic url
						out.push_back(TheButtonInfo(url, ico)); // add to the output list
						//++;
						//也就是说些按钮信息包含了缩略图 和所转向的的位置 并且这些信息最终被放到 一个list中 其中
					}
					else
						qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb ;
            }
            else
				qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb;
        }
        //printf("%d",a);

    }

    return out;
}


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
	qDebug() << "Qt version: " << QT_VERSION_STR;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    vector<TheButtonInfo> videos = getInfoIn("/Users/luoruidi/Desktop/cwk2/Resources/2811_videos");

    if (videos.size() == 0) {
		qDebug() << "no videos found";
        exit(-1);
    }

    // the widget that will show the video  播放区域
    QVideoWidget *videoWidget = new QVideoWidget;
	//videoWidget -> setBaseSize(600, 300);

	//
    // the QMediaPlayer which controls the playback   在 player文件里有详细 信息
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(videoWidget); //

    //float persentage;
    //persentage = player->position()/player->duration();





    // a row of buttons
    QWidget *buttonWidget = new QWidget();

    // a list of the buttons
    std::vector<TheButton*> buttons;   //创建了一个 指针型的数组？ 里面全是 TheButton（继承与pushbutton 即可以按按钮

    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);


    QLabel *lab1 = new QLabel();

   // TheButton::connect(this,SIGNAL(released()),lab1,SLOT(setText(QString*) ) );


    // create the four buttons
    for ( int i = 0; i < 7; i++ ) {
        TheButton *button = new TheButton(buttonWidget);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), player, SLOT (jumpTo(TheButtonInfo* ))); // when clicked, tell the player to play.
        //button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), lab1, SLOT (setText(TheButtonInfo*)));
        button->setMaximumWidth(210);
        button->setMaximumHeight(140);
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&videos.at(i)); //在这个地方把之前存放好的 按钮信息赋值给真实的button
    }

    // tell the player what buttons and videos are available
    player->setContent(&buttons, & videos);



    //scrollarea
   // QLabel* lewy = new QLabel();
    QScrollArea* scroll = new QScrollArea();
   // QWidget* area = new QWidget();
    buttonWidget->setGeometry(0, 0,1500,140);  //内容的大小直接影响整个滚动区
    //buttonWidget->setMaximumHeight(200);
    /*buttonWidget->setMaximumSize(wd,100);*/
    //scroll->setGeometry(0, 0, 100, 1000);
    scroll->setWidget(buttonWidget);
    /*QHBoxLayout* Scrolllayout = new QHBoxLayout();
    Scrolllayout->addWidget(scroll);
    area->setMinimumSize(QSize(wd, 110));
    area->setLayout(Scrolllayout);*/



    // create the main window and layout
    QWidget window;
    QVBoxLayout *top = new QVBoxLayout();
    window.setLayout(top);

    window.setWindowTitle("tomeo");
    PlayerSlider *slider = new PlayerSlider();



    QTimer *SlideTimer = new QTimer(player);
    SlideTimer->setInterval(1000); // 1000ms is one second between ...
    SlideTimer->start();
    //float persentage;
    //persentage = player->position()/player->duration();
    slider->getplayer(player);
    QTimer::connect(SlideTimer, SIGNAL(timeout()), slider, SLOT(onTimerOut()));



    //PlayerSlider::connect(slider,SIGNAL(sliderPressed()),player,SLOT(slider_clicked()));
    //slider 被按下时 激活函数 然后



    // add the video and the buttons to the top level widget
	top->addWidget(videoWidget);
    top->addWidget(slider);
    top->addWidget(scroll);
    top->setStretchFactor(videoWidget, 3);
    //top->setStretchFactor(scroll);

	window.setMinimumSize(800, 680);
	window.setGeometry(40, 40, 800, 680);

    // showtime!
    window.show();

    // wait for the app to terminate
    return app.exec();
}
