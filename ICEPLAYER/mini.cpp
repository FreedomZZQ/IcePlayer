#include "mini.h"

miniwindow::miniwindow(QWidget *parent):QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	//半透明
	this->setWindowOpacity(0.9);

	//窗口拖动
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);

	//固定大小
	this->setFixedSize(100, 100);

	playButton = new ICE_Ice_Button( this);
	playButton->setObjectName(QStringLiteral("playButton"));
	playButton->setGeometry(QRect(29, 29, 34, 34));

	pauseButton = new ICE_Ice_Button( this);
	pauseButton->setObjectName(QStringLiteral("pauseButton"));
	pauseButton->setGeometry(QRect(24, 29, 34, 34));
	pauseButton->setVisible(false);

	miniNextButton = new ICE_Ice_Button( this);
	miniNextButton->setObjectName(QStringLiteral("nextButton"));
	miniNextButton->setGeometry(QRect(61, 48, 34, 34));

	//设置图标
	QIcon icon_play, icon_play_focus;
	icon_play.addFile(QStringLiteral(":/IcePlayer/Resources/播放按钮mini.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_play_focus.addFile(QStringLiteral(":/IcePlayer/Resources/播放按钮mini.png"), QSize(), QIcon::Normal, QIcon::Off);
	playButton->ICE_Set_Button_Icons(icon_play, icon_play_focus);

	playButton->setIconSize(QSize(34,34));
	playButton->setFlat(true);
	playButton->setFocusPolicy(Qt::NoFocus);
	playButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_pause, icon_pause_focus;
	icon_pause.addFile(QStringLiteral(":/IcePlayer/Resources/暂停按钮mini.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_pause_focus.addFile(QStringLiteral(":/IcePlayer/Resources/暂停按钮mini.png"), QSize(), QIcon::Normal, QIcon::Off);
	pauseButton->ICE_Set_Button_Icons(icon_pause, icon_pause_focus);

	pauseButton->setIconSize(QSize(34,34));
	pauseButton->setFlat(true);
	pauseButton->setFocusPolicy(Qt::NoFocus);
	pauseButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_next, icon_next_focus;
	icon_next.addFile(QStringLiteral(":/IcePlayer/Resources/前进按钮mini.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_next_focus.addFile(QStringLiteral(":/IcePlayer/Resources/前进按钮mini.png"), QSize(), QIcon::Normal, QIcon::Off);
	miniNextButton->ICE_Set_Button_Icons(icon_next, icon_next_focus);

	miniNextButton->setIconSize(QSize(9,15));
	miniNextButton->setFlat(true);
	miniNextButton->setFocusPolicy(Qt::NoFocus);
	miniNextButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");
	
	ice_init_menu_actions();
	connect(playButton, SIGNAL(clicked()), this, SLOT(ice_play()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(ice_pause()));
	connect(miniNextButton, SIGNAL(clicked()), this, SLOT(ice_next_music()));
}
miniwindow::~miniwindow()
{

}

void miniwindow::ice_init_menu_actions()
{
	mode0 = new QAction(QString::fromLocal8Bit("单曲播放"), this);
	mode1 = new QAction(QString::fromLocal8Bit("列表循环"), this);
	mode2 = new QAction(QString::fromLocal8Bit("单曲循环"), this);
	mode3 = new QAction(QString::fromLocal8Bit("随机播放"), this);

	connect(mode0, SIGNAL(triggered()), this, SLOT(ice_set_mode()));
	connect(mode1, SIGNAL(triggered()), this, SLOT(ice_set_mode()));
	connect(mode2, SIGNAL(triggered()), this, SLOT(ice_set_mode()));
	connect(mode3, SIGNAL(triggered()), this, SLOT(ice_set_mode()));

	modeGroup = new QActionGroup(this);
	modeGroup->addAction(mode0);
	modeGroup->addAction(mode1);
	modeGroup->addAction(mode2);
	modeGroup->addAction(mode3);

	mode0->setCheckable(true);
	mode1->setCheckable(true);
	mode2->setCheckable(true);
	mode3->setCheckable(true);
	mode0->setChecked(true);


	mainForm = new QAction(QString::fromLocal8Bit("返回主界面"),this);
	exit = new QAction(QString::fromLocal8Bit("退出"),this);
	next = new QAction(QString::fromLocal8Bit("下一曲"),this);
	last = new QAction(QString::fromLocal8Bit("上一曲"),this);
	lyric = new QAction(QString::fromLocal8Bit("桌面歌词"), this);


	volSlider = new QSlider(Qt::Horizontal, this);
	volSlider->setRange(0, 100);
	volSlider->setGeometry(QRect(26,0,75,25));
	connect(volSlider, SIGNAL(valueChanged(int)), this, SIGNAL(volumeChanged(int)));

	volSlider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"  
		"QSlider::sub-page:horizontal{background:#0096ff;}"  
		"QSlider::add-page:horizontal{background:lightgray;} "
		"QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");

	setVolumn = new QWidgetAction(this);
	setVolumn->setDefaultWidget(volSlider);

	contextMenu = new QMenu(this);
	contextMenu->addAction(mainForm);
	contextMenu->addSeparator();
	contextMenu->addAction(setVolumn);
	contextMenu->addSeparator();
	contextMenu->addAction(next);
	contextMenu->addAction(last);
	contextMenu->addSeparator();
	contextMenu->addActions(modeGroup->actions());
	contextMenu->addSeparator();
	contextMenu->addAction(lyric);
	contextMenu->addSeparator();
	contextMenu->addAction(exit);


	contextMenu->setStyleSheet(
		"QMenu{padding:5px;background:white;border:1px solid gray;}"
		"QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
		"QMenu::item:selected:enabled{background:#0096ff;color:white;}"
		"QMenu::item:selected:!enabled{background:transparent;}"
		"QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");

	connect(exit, SIGNAL(triggered()), this, SLOT(ice_exit()));
	connect(mainForm, SIGNAL(triggered()), this, SLOT(ice_back_to_main()));
	connect(next, SIGNAL(triggered()), this, SLOT(ice_next_music()));
	connect(last, SIGNAL(triggered()), this, SLOT(ice_last_music()));
	connect(playButton, SIGNAL(clicked()), this, SLOT(ice_play()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(ice_pause()));
	connect(volSlider, SIGNAL(valueChanged(int)), this, SLOT(ice_update_vol(int)));
	connect(lyric, SIGNAL(triggered()), this, SLOT(ice_lyric_action()));

}

void miniwindow::ice_exit()
{
	parentForm->close();
	this->close();
}

void miniwindow::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0 , QPixmap(":/IcePlayer/Resources/mini.png"));
}

void miniwindow::contextMenuEvent(QContextMenuEvent *event)
{
	contextMenu->exec(QCursor::pos());
}

void miniwindow::ice_back_to_main()
{
	parentForm->show();
	this->hide();
}

void miniwindow::ICE_Set_Parent(IcePlayer *parent)
{
	parentForm = parent;
}

void miniwindow::ice_next_music()
{
	
	parentForm->ice_next_button_clicked();
}

void miniwindow::ice_last_music()
{
	parentForm->ice_last_button_clicked();
}

void miniwindow::ice_play()
{
	parentForm->ice_play_button_clicked();
	pauseButton->setVisible(true);
	playButton->setVisible(false);
}

void miniwindow::ice_pause()
{
	parentForm->ice_pause_button_clicked();
	pauseButton->setVisible(false);
	playButton->setVisible(true);
}

void miniwindow::ice_set_mode()
{
	if(mode0->isChecked()) {
		parentForm->ICE_set_mode_from_mini(0);
	}
	else if(mode1->isChecked()) {
		parentForm->ICE_set_mode_from_mini(1);
	}
	else if(mode2->isChecked()) {
		parentForm->ICE_set_mode_from_mini(2);
	}
	else if(mode3->isChecked()) {
		parentForm->ICE_set_mode_from_mini(3);
	}
}

void miniwindow::ICE_Init_Play_Mode(int vol)
{
	switch(parentForm->playMode){
	case 0:
		mode0->setChecked(true);
		break;
	case 1:
		mode1->setChecked(true);
		break;
	case 2:
		mode2->setChecked(true);
		break;
	case 3:
		mode3->setChecked(true);
		break;
	}

	if(parentForm->playButton->isVisible()){
		playButton->setVisible(true);
		pauseButton->setVisible(false);
	}
	else {
		playButton->setVisible(false);
		pauseButton->setVisible(true);
	}

	volSlider->setValue(vol);
}

void miniwindow::ice_update_vol(int a)
{
	parentForm->ICE_set_vol_from_mini(a);
}

void miniwindow::ice_lyric_action()
{
	parentForm->ice_lyric_button_clicked();
}