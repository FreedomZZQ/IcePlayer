#include "iceplayer.h"

IcePlayer::IcePlayer(QWidget *parent)
	: QWidget(parent)
{
	ice_init_ui();
	ice_init_player();
	ice_init_connections();
	ice_init_windows();
	ice_init_menu_actions();
	ice_init_network();
	iceDir = QApplication::applicationDirPath();
	ice_read_list();
}

IcePlayer::~IcePlayer()
{
	
}

void IcePlayer::ice_init_windows()
{
	aboutForm = new ICE_About_Form(this);
	iceLrc = new ICE_Lrc(this);
	
	miniForm = new miniwindow();
	miniForm->ICE_Set_Parent(this);
	miniForm->hide();

}

void IcePlayer::ice_init_menu_actions()
{
	modeSingal = new QAction(QString::fromLocal8Bit("单曲播放"), this);
	modeListCircle = new QAction(QString::fromLocal8Bit("列表循环"), this);
	modeSingalCircle = new QAction(QString::fromLocal8Bit("单曲循环"), this);
	modeRandom = new QAction(QString::fromLocal8Bit("随机播放"), this);

	connect(modeSingal, SIGNAL(triggered()), this, SLOT(ice_set_play_mode()));
	connect(modeListCircle, SIGNAL(triggered()), this, SLOT(ice_set_play_mode()));
	connect(modeSingalCircle, SIGNAL(triggered()), this, SLOT(ice_set_play_mode()));
	connect(modeRandom, SIGNAL(triggered()), this, SLOT(ice_set_play_mode()));

	modeActionGroup = new QActionGroup(this);
	modeActionGroup->addAction(modeSingal);
	modeActionGroup->addAction(modeListCircle);
	modeActionGroup->addAction(modeSingalCircle);
	modeActionGroup->addAction(modeRandom);

	modeSingal->setCheckable(true);
	modeListCircle->setCheckable(true);
	modeSingalCircle->setCheckable(true);
	modeRandom->setCheckable(true);
	modeSingal->setChecked(true);

	playModeMenu = new QMenu(modeButton);
	playModeMenu->setStyleSheet(
		"QMenu{padding:5px;background:white;border:1px solid gray;}"
		"QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
		"QMenu::item:selected:enabled{background:#0096ff;color:white;}"
		"QMenu::item:selected:!enabled{background:transparent;}"
		"QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");
	playModeMenu->addActions(modeActionGroup->actions());


	contextMenuLess = new QMenu(playlistTable);
	contextMenuMore = new QMenu(playlistTable);
	addMusic = new QAction(QString::fromLocal8Bit("添加歌曲"),this);
	addFileDiv = new QAction(QString::fromLocal8Bit("添加目录"),this);
	removeCurr = new QAction(QString::fromLocal8Bit("移除本曲"),this);
	removeAll = new QAction(QString::fromLocal8Bit("移除所有"),this);

	connect(addMusic, SIGNAL(triggered()), this, SLOT(ice_open_music()));
	connect(addFileDiv, SIGNAL(triggered()), this, SLOT(ice_open_dir()));
	connect(removeCurr, SIGNAL(triggered()), this, SLOT(ice_remove_current_music()));
	connect(removeAll, SIGNAL(triggered()), this, SLOT(ice_clear_list()));

	contextMenuLess->addAction(addMusic);
	contextMenuLess->addAction(addFileDiv);
	contextMenuLess->addSeparator();
	contextMenuLess->addAction(removeAll);

	contextMenuMore->addAction(addMusic);
	contextMenuMore->addAction(addFileDiv);
	contextMenuMore->addSeparator();
	contextMenuMore->addAction(removeCurr);
	contextMenuMore->addAction(removeAll);

	contextMenuLess->setStyleSheet(
		"QMenu{padding:5px;background:white;border:1px solid gray;}"
		"QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
		"QMenu::item:selected:enabled{background:#0096ff;color:white;}"
		"QMenu::item:selected:!enabled{background:transparent;}"
		"QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");

	contextMenuMore->setStyleSheet(
		"QMenu{padding:5px;background:white;border:1px solid gray;}"
		"QMenu::item{padding:0px 40px 0px 30px;height:25px;}"
		"QMenu::item:selected:enabled{background:#0096ff;color:white;}"
		"QMenu::item:selected:!enabled{background:transparent;}"
		"QMenu::separator{height:1px;background:lightgray;margin:5px 0px 5px 0px;}");

}

void IcePlayer::ice_init_player()
{
	mediaPlayer = new QMediaPlayer(this);
	mediaList = new QMediaPlaylist(this);
	mediaPlayer->setPlaylist(mediaList);

	playMode = ICE_Play_Mode::SINGAL;
	preIndex = -1;
	currentIndex = 0;

	mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
}

void IcePlayer::ice_init_connections()
{
	connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(ice_update_position(qint64)));
	connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(ice_update_duration(qint64)));
	connect(mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)),this, SLOT(ice_update_state(QMediaPlayer::State)));
	connect(mediaPlayer, SIGNAL(metaDataChanged()), this, SLOT(ice_update_meta_data()));
	connect(playSlider, SIGNAL(sliderMoved(int)), this, SLOT(ice_set_play_position(int)));
	connect(playSlider, SIGNAL(sliderReleased()), this, SLOT(ice_set_position()));
	connect(volButton, SIGNAL(ICE_Volume_Changed(int)), mediaPlayer, SLOT(setVolume(int)));

	connect(playlistTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(ice_playlisttable_cell_double_clicked(int, int)));
	connect(playlistTable, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ice_playlisttable_menu_requested(const QPoint &)));
	
	connect(addButton, SIGNAL(clicked()), this, SLOT(ice_open_music()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(playButton, SIGNAL(clicked()), this, SLOT(ice_play_button_clicked()));
	connect(lyricButton, SIGNAL(clicked()), this, SLOT(ice_lyric_button_clicked()));
	connect(logoButton, SIGNAL(clicked()), this, SLOT(ice_logo_button_clicked()));
	connect(modeButton, SIGNAL(clicked()), this, SLOT(ice_mode_button_clicked()));
	connect(nextButton, SIGNAL(clicked()), this, SLOT(ice_next_button_clicked()));
	connect(lastButton, SIGNAL(clicked()), this, SLOT(ice_last_button_clicked()));
	connect(pauseButton, SIGNAL(clicked()), this, SLOT(ice_pause_button_clicked()));
	connect(minButton, SIGNAL(clicked()), this, SLOT(ice_min_button_clicked()));
	connect(mminButton, SIGNAL(clicked()), this, SLOT(showMinimized()));

	//connect(this, SIGNAL(destroyed()), this, SLOT(ice_close()));
	//connect(mediaList, SIGNAL(mediaInserted()), this, SLOT(ice_write_list()));
}

void IcePlayer::ice_init_ui()
{
	picLabel = new QLabel( this);
	picLabel->setGeometry(QRect(40, 45, 100, 100));
	picLabel->setScaledContents(true);
	picLabel->setPixmap(QPixmap(":/IcePlayer/Resources/default_album.jpg"));
	
	nameLabel = new IceLabel(this);
	nameLabel->setGeometry(QRect(150, 55, 220, 20));

	musicianLabel = new QLabel(this);
	musicianLabel->setGeometry(QRect(150, 85, 220, 15));

	albumLabel = new QLabel(this);
	albumLabel->setGeometry(QRect(150, 115, 220, 15));

	playSlider = new QSlider( this);
	playSlider->setObjectName(QStringLiteral("playSlider"));
	playSlider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"  
		"QSlider::sub-page:horizontal{background:#0096ff;}"  
		"QSlider::add-page:horizontal{background:lightgray;} "
		"QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");
	playSlider->setGeometry(QRect(40, 150, 290, 20));
	playSlider->setOrientation(Qt::Horizontal);

	timeLabel = new QLabel( this);
	timeLabel->setObjectName(QStringLiteral("timeLabel"));
	timeLabel->setGeometry(QRect(340, 150, 51, 16));

	playlistTable = new QTableWidget( this);
	playlistTable->setObjectName(QStringLiteral("playlistTable"));
	playlistTable->setGeometry(QRect(25, 240, 350, 320));
	playlistTable->setItemDelegate(new NoFocusDelegate());

	addButton = new ICE_Ice_Button( this);
	addButton->setObjectName(QStringLiteral("addButton"));
	addButton->setGeometry(QRect(40, 190, 31, 31));
	modeButton = new ICE_Ice_Button( this);
	modeButton->setObjectName(QStringLiteral("modeButton"));
	modeButton->setGeometry(QRect(290, 190, 31, 31));
	lastButton = new ICE_Ice_Button( this);
	lastButton->setObjectName(QStringLiteral("lastButton"));
	lastButton->setGeometry(QRect(120, 185, 41, 41));
	nextButton = new ICE_Ice_Button( this);
	nextButton->setObjectName(QStringLiteral("nextButton"));
	nextButton->setGeometry(QRect(240, 185, 41, 41));
	lyricButton = new ICE_Ice_Button( this);
	lyricButton->setObjectName(QStringLiteral("lyricButton"));
	lyricButton->setGeometry(QRect(80, 190, 31, 31));
	playButton = new ICE_Ice_Button( this);
	playButton->setObjectName(QStringLiteral("playButton"));
	playButton->setGeometry(QRect(170, 175, 61, 61));
	pauseButton = new ICE_Ice_Button( this);
	pauseButton->setObjectName(QStringLiteral("pauseButton"));
	pauseButton->setGeometry(QRect(170, 175, 61, 61));
	pauseButton->setVisible(false);

	volButton = new ICE_Vol_Button( this);
	volButton->setObjectName(QStringLiteral("volButton"));
	volButton->setGeometry(QRect(333, 193, 31, 31));
	volButton->ICE_Set_Volume(100);

	mminButton = new ICE_Ice_Button( this);
	mminButton->setObjectName(QStringLiteral("mminButton"));
	mminButton->setGeometry(QRect(307, 3, 29, 31));
	minButton = new ICE_Ice_Button( this);
	minButton->setObjectName(QStringLiteral("minButton"));
	minButton->setGeometry(QRect(337, 3, 29, 31));
	exitButton = new ICE_Ice_Button( this);
	exitButton->setObjectName(QStringLiteral("exitButton"));
	exitButton->setGeometry(QRect(364, 3, 29, 31));
	logoButton = new ICE_Ice_Button( this);
	logoButton->setObjectName(QStringLiteral("logoButton"));
	logoButton->setGeometry(QRect(8, 3, 120, 48));

	logoButton->raise();
	picLabel->raise();
	playSlider->raise();
	timeLabel->raise();
	playlistTable->raise();
	addButton->raise();
	modeButton->raise();
	nextButton->raise();
	lyricButton->raise();
	playButton->raise();
	volButton->raise();
	mminButton->raise();
	minButton->raise();
	exitButton->raise();

	timeLabel->setText(tr("00:00"));
	nameLabel->setText(tr("Name " ));
	musicianLabel->setText(tr("Musician" ));
	albumLabel->setText(tr("Album" ));

	//设置图标
	QIcon icon_play, icon_play_focus;
	icon_play.addFile(QStringLiteral(":/IcePlayer/Resources/播放按钮-主界面.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_play_focus.addFile(QStringLiteral(":/IcePlayer/Resources/播放按钮-主界面2.png"), QSize(), QIcon::Normal, QIcon::Off);
	playButton->ICE_Set_Button_Icons(icon_play, icon_play_focus);
	playButton->setIconSize(QSize(60,60));
	playButton->setFlat(true);
	playButton->setFocusPolicy(Qt::NoFocus);
	playButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_pause, icon_pause_focus;
	icon_pause.addFile(QStringLiteral(":/IcePlayer/Resources/暂停按钮-主界面.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_pause_focus.addFile(QStringLiteral(":/IcePlayer/Resources/暂停按钮-主界面2.png"), QSize(), QIcon::Normal, QIcon::Off);
	pauseButton->ICE_Set_Button_Icons(icon_pause, icon_pause_focus);
	pauseButton->setIconSize(QSize(60,60));
	pauseButton->setFlat(true);
	pauseButton->setFocusPolicy(Qt::NoFocus);
	pauseButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");


	QIcon icon_lyric, icon_lyric_focus;
	icon_lyric.addFile(QStringLiteral(":/IcePlayer/Resources/歌词按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_lyric_focus.addFile(QStringLiteral(":/IcePlayer/Resources/歌词按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
	lyricButton->ICE_Set_Button_Icons(icon_lyric, icon_lyric_focus);
	lyricButton->setIconSize(QSize(25,25));
	lyricButton->setFlat(true);
	lyricButton->setFocusPolicy(Qt::NoFocus);
	lyricButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_exit, icon_exit_focus;
	icon_exit.addFile(QStringLiteral(":/IcePlayer/Resources/关闭按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_exit_focus.addFile(QStringLiteral(":/IcePlayer/Resources/关闭按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
	exitButton->ICE_Set_Button_Icons(icon_exit, icon_exit_focus);
	exitButton->setIconSize(QSize(20,20));
	exitButton->setFlat(true);
	exitButton->setFocusPolicy(Qt::NoFocus);
	exitButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_min, icon_min_focus;
	icon_min.addFile(QStringLiteral(":/IcePlayer/Resources/迷你模式按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_min_focus.addFile(QStringLiteral(":/IcePlayer/Resources/迷你模式按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
	minButton->ICE_Set_Button_Icons(icon_min, icon_min_focus);
	minButton->setIconSize(QSize(20,20));
	minButton->setFlat(true);
	minButton->setFocusPolicy(Qt::NoFocus);
	minButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_mmin, icon_mmin_focus;
	icon_mmin.addFile(QStringLiteral(":/IcePlayer/Resources/缩小按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_mmin_focus.addFile(QStringLiteral(":/IcePlayer/Resources/缩小按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
	mminButton->ICE_Set_Button_Icons(icon_mmin, icon_mmin_focus);
	mminButton->setIconSize(QSize(20,20));
	mminButton->setFlat(true);
	mminButton->setFocusPolicy(Qt::NoFocus);
	mminButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_logo, icon_logo_focus;
	icon_logo.addFile(QStringLiteral(":/IcePlayer/Resources/左上角logo按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_logo_focus.addFile(QStringLiteral(":/IcePlayer/Resources/左上角logo按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
	logoButton->ICE_Set_Button_Icons(icon_logo, icon_logo_focus);
	logoButton->setIconSize(QSize(120, 48));
	logoButton->setFlat(true);
	logoButton->setFocusPolicy(Qt::NoFocus);
	logoButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_next, icon_next_focus;
	icon_next.addFile(QStringLiteral(":/IcePlayer/Resources/下一曲.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_next_focus.addFile(QStringLiteral(":/IcePlayer/Resources/下一曲2.png"), QSize(), QIcon::Normal, QIcon::Off);
	nextButton->ICE_Set_Button_Icons(icon_next, icon_next_focus);
	nextButton->setIconSize(QSize(40,40));
	nextButton->setFlat(true);
	nextButton->setFocusPolicy(Qt::NoFocus);
	nextButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_last, icon_last_focus;
	icon_last.addFile(QStringLiteral(":/IcePlayer/Resources/上一曲.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_last_focus.addFile(QStringLiteral(":/IcePlayer/Resources/上一曲2.png"), QSize(), QIcon::Normal, QIcon::Off);
	lastButton->ICE_Set_Button_Icons(icon_last, icon_last_focus);
	lastButton->setIconSize(QSize(40,40));
	lastButton->setFlat(true);
	lastButton->setFocusPolicy(Qt::NoFocus);
	lastButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	QIcon icon_mode, icon_mode_focus;
	icon_mode.addFile(QStringLiteral(":/IcePlayer/Resources/播放模式.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_mode_focus.addFile(QStringLiteral(":/IcePlayer/Resources/播放模式2.png"), QSize(), QIcon::Normal, QIcon::Off);
	modeButton->ICE_Set_Button_Icons(icon_mode, icon_mode_focus);
	modeButton->setIconSize(QSize(25,25));
	modeButton->setFlat(true);
	modeButton->setFocusPolicy(Qt::NoFocus);
	modeButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");
	
	QIcon icon_add, icon_add_focus;
	icon_add.addFile(QStringLiteral(":/IcePlayer/Resources/添加歌曲.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_add_focus.addFile(QStringLiteral(":/IcePlayer/Resources/添加歌曲2.png"), QSize(), QIcon::Normal, QIcon::Off);
	addButton->ICE_Set_Button_Icons(icon_add, icon_add_focus);
	addButton->setIconSize(QSize(25,25));
	addButton->setFlat(true);
	addButton->setFocusPolicy(Qt::NoFocus);
	addButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");

	//去除标题栏
	this->setWindowFlags(Qt::FramelessWindowHint);
	//半透明
	this->setWindowOpacity(0.9);
	setAttribute(Qt::WA_TranslucentBackground);
	//窗口拖动
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);
	//固定大小
	this->setFixedSize(400, 600);

	//设置音乐信息字体颜色
	QColor fontcolor(1, 149, 255);
	QPalette fontPalette;
	fontPalette.setColor(QPalette::WindowText, fontcolor);
	nameLabel->setPalette(fontPalette);
	musicianLabel->setPalette(fontPalette);
	albumLabel->setPalette(fontPalette);

	QColor timeColor(106, 182, 240);
	QPalette timePalette;
	timePalette.setColor(QPalette::WindowText, timeColor);
	timeLabel->setPalette(timePalette);

	nameLabel->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 12));

	QFont othersfont(QString::fromLocal8Bit("微软雅黑"), 9);
	musicianLabel->setFont(othersfont);
	albumLabel->setFont(othersfont);
	timeLabel->setFont(othersfont);

	volSlider = new QSlider(volButton);
	volSlider->setObjectName(QStringLiteral("volSlider"));
	volSlider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"  
		"QSlider::sub-page:horizontal{background:#0096ff;}"  
		"QSlider::add-page:horizontal{background:lightgray;} "
		"QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");
	volSlider->setGeometry(QRect(40, 150, 290, 20));
	volSlider->setOrientation(Qt::Horizontal);

	if (playlistTable->columnCount() < 1)
		playlistTable->setColumnCount(2);
	QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
	playlistTable->setHorizontalHeaderItem(0, __qtablewidgetitem);

	//设置列宽
	playlistTable->setColumnWidth(0,300);
	playlistTable->setColumnWidth(1,45);
	//禁止编辑单元格内容
	playlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers); 
	//选中一行
	playlistTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//去掉水平滚动条
	playlistTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//垂直滚动条按项移动
	playlistTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);
	//去除水平表头
	playlistTable->horizontalHeader()->setFixedHeight(0);
	//去除垂直表头
	playlistTable->verticalHeader()->setFixedWidth(0);
	//设置无边框
	playlistTable->setFrameShape(QFrame::NoFrame); 
	//设置不显示格子线
	playlistTable->setShowGrid(false); 
	//设置右键菜单
	playlistTable->setContextMenuPolicy(Qt::CustomContextMenu);
	//设置背景颜色
	QPalette pal;
	pal.setBrush(QPalette::Base, QBrush(QColor(255, 255, 255)));
	playlistTable->setPalette(pal);
	//设置竖直滚动条样式
	playlistTable->setStyleSheet("QScrollBar{background:transparent; width: 5px;}"
		"QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
		"QScrollBar::handle:hover{background:gray;}"
		"QScrollBar::sub-line{background:transparent;}"
		"QScrollBar::add-line{background:transparent;}");
	//使拖动操作生效
	playlistTable->setAcceptDrops(true);
	setAcceptDrops(true);

}

void IcePlayer::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if(urls.isEmpty())
		return;

	QStringList dropfilename;
	foreach(QUrl u, urls){
		if (u.toString().right(4) == QString(".mp3")){
			dropfilename.append(u.toLocalFile());
		}
	}

	if(!dropfilename.isEmpty()){
		ice_add_list(dropfilename);
	}
}

void IcePlayer::dragEnterEvent(QDragEnterEvent *event)
{
	if(event->mimeData()->hasFormat("text/uri-list"))
		event->acceptProposedAction();
}

void IcePlayer::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0 , QPixmap(":/IcePlayer/Resources/background.png"));
}

void IcePlayer::ice_playlisttable_cell_double_clicked(int row, int ) 
{
	QFile file(playList.at(row));
	if (!file.open(QIODevice::ReadOnly)) {
		playlistTable->item(row,1)->setText(QString::fromLocal8Bit("失效"));
		return ;
	}
	file.close();
	mediaList->setCurrentIndex(row);
	mediaPlayer->play();
	playlistTable->item(row, 1)->setText(QString::fromLocal8Bit(""));
}

void IcePlayer::ice_remove_current_music()   
{
	playList.removeAt(currentIndex);
	playlistTable->removeRow(currentIndex);
	mediaList->removeMedia(currentIndex);
	
	ice_color_table();
}

void IcePlayer::ice_open_music()  
{
	QStringList fileList = QFileDialog::getOpenFileNames(this,QString::fromLocal8Bit("添加音乐"),QString(),QString("MP3 (*.mp3)"));
	ice_add_list(fileList);
}

void IcePlayer::ice_open_dir()     
{
	QString dirPath = QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("选择目录"));
	if(dirPath.size() == 0)
		return;
	//if(QFileDialog::Reject) return;
	QDir dir(dirPath);
	QStringList fileList = dir.entryList(QStringList()<<"*.mp3",QDir::Files);
	for(int i = 0;i < fileList.size();i ++)
		fileList[i] = dir.absoluteFilePath(fileList.at(i));
	ice_add_list(fileList);
}

void IcePlayer::ice_clear_list()  
{
	mediaPlayer->stop();
	playList.clear();
	mediaList->clear();
	while(playlistTable->rowCount())
		playlistTable->removeRow(0);

	timeLabel->setText(tr("00:00"));
	nameLabel->setText(tr("Name " ));
	nameLabel->ICE_Stop();
	musicianLabel->setText(tr("Musician" ));
	albumLabel->setText(tr("Album" ));
}

void IcePlayer::ice_add_list(QStringList list)
{

	foreach(QString fileName,list)
	{
		if(playList.contains(fileName))
			continue;
		playList.append(fileName);

		mediaList->addMedia(QUrl::fromLocalFile(fileName));
		playlistTable->insertRow(playlistTable->rowCount());

		for(int i = 0;i < playlistTable->columnCount();i ++){
			QTableWidgetItem *item  = new QTableWidgetItem;
			item->setFont(QFont(QString::fromLocal8Bit("微软雅黑"), 10));

			playlistTable->setItem(playlistTable->rowCount() - 1,i,item);
			
		}
		playlistTable->item(playlistTable->rowCount() - 1,0)->setText(QFileInfo(fileName).baseName());

	}
	ice_color_table();
	ice_write_list();
}

void IcePlayer::ice_playlisttable_menu_requested(const QPoint &pos)  
{
	if(playlistTable->itemAt(pos))
	{
		currentIndex = playlistTable->rowAt(pos.y());
		contextMenuMore->exec(QCursor::pos());
	}
	else contextMenuLess->exec(QCursor::pos());
}

void IcePlayer::ice_set_position(/*int position*/)
{
	int pos = ice_get_play_position();
	int state = mediaPlayer->state();
/*	if (qAbs(mediaPlayer->position() - pos) > 99)*/
	mediaPlayer->setPosition(pos);

	mediaPlayer->play();
	playButton->setVisible(false);
	pauseButton->setVisible(true);
	
// 	if (state == QMediaPlayer::PlayingState)
// 		mediaPlayer->play();
// 	else
// 		mediaPlayer->pause();


}

void IcePlayer::ice_update_position(qint64 position)
{
	if (!playSlider->isSliderDown()){
		playSlider->setValue(position);
	}

	//获取该音频文件的总时长参数，单位为毫秒
	qint64 total_time_value = mediaPlayer->duration();

	//这3个参数分别代表了时，分，秒；60000毫秒为1分钟，所以分钟第二个参数是先除6000,第3个参数是直接除1s
	QTime total_time(0, (total_time_value/60000)%60, (total_time_value/1000)%60);

	//传进来的time参数代表了当前的时间
	QTime current_time(0, (position/60000)%60, (position/1000)%60);
	timeLabel->setText(current_time.toString(tr("mm:ss")));

	// 获取当期时间对应的歌词
	if(!lrcMap.isEmpty()) {

		// 获取当前时间在歌词中的前后两个时间点
		qint64 previous = 0;
		qint64 later = 0;

		//keys()方法返回lrc_map列表
		foreach (qint64 value1, lrcMap.keys()) {
			if (position >= value1) {
				previous = value1;
			} else {
				later = value1;
				break;
			}
		}

		// 达到最后一行,将later设置为歌曲总时间的值
		if (later == 0)
			later = total_time_value;

		// 获取当前时间所对应的歌词内容
		QString current_lrc = lrcMap.value(previous);

		// 如果是新的一行歌词，那么重新开始显示歌词遮罩
		QString tmp = iceLrc->text();
		if(current_lrc != tmp) {
			iceLrc->setText(current_lrc);
			tmp = iceLrc->text();
			qint64 interval_time = later - previous;
			iceLrc->ICE_Start_Lrc_Mask(interval_time);
		}
	}
}

void IcePlayer::ice_update_duration(qint64 duration)
{
	playSlider->setRange(0, duration);
	playSlider->setEnabled(duration > 0);
	playSlider->setPageStep(duration / 10);
}

void IcePlayer::ice_update_meta_data()
{
	currentIndex = mediaList->currentIndex();
	playingFile = playList.at(currentIndex);

	songName.clear();
	songArtist.clear();
	lrcMap.clear();
	picLabel->setPixmap(QPixmap(":/IcePlayer/Resources/default_album.jpg"));


	songName = mediaPlayer->metaData(QMediaMetaData::Title).toString();
	if (songName.size() > 28)
		nameLabel->ICE_Set_Text(songName, TEXT_SPEED);
	else{
		nameLabel->ICE_Stop();
		nameLabel->setText(songName);
	}

	songArtist = mediaPlayer->metaData(QMediaMetaData::Author).toString();
	musicianLabel->setText(songArtist);
	albumLabel->setText(mediaPlayer->metaData(QMediaMetaData::AlbumTitle).toString());

	iceLrc->setText(songName);
	
	if (!songName.isEmpty()){
		bool pic = ice_get_pic_from_file();
		bool lrc = ice_resolve_lrc(playingFile);
		if (!(pic && lrc)){
			receiveState = RECEIVE_INFO;
			ice_fetch_data();
		}
		
	}

	if(nameLabel->text() == "")
		nameLabel->setText(QString::fromLocal8Bit("未知歌曲"));
	if(musicianLabel->text() == "")
		musicianLabel->setText(QString::fromLocal8Bit("未知音乐家"));
	if(albumLabel->text() == "")
		albumLabel->setText(QString::fromLocal8Bit("未知专辑"));
	
	if(playlistTable->rowCount() == 0){
		timeLabel->setText(tr("00:00"));
		nameLabel->setText(tr("Name " ));
		musicianLabel->setText(tr("Musician" ));
		albumLabel->setText(tr("Album" ));
	}

}

void IcePlayer::ice_update_state(QMediaPlayer::State state)
{
	if (state == QMediaPlayer::PlayingState) {
		playButton->setVisible(false);
		pauseButton->setVisible(true);
		
	} else {
		playButton->setVisible(true);
		pauseButton->setVisible(false);
	}

	if (state != QMediaPlayer::StoppedState){
		playingFile = playList.at(mediaList->currentIndex());
		ice_resolve_lrc(playingFile);
	} 
}

void IcePlayer::ice_play_button_clicked()
{
	if(mediaPlayer->state() == QMediaPlayer::PausedState){
		mediaPlayer->play();
	}
}

void IcePlayer::ice_pause_button_clicked()
{
	
	if(mediaPlayer->state() == QMediaPlayer::PlayingState){
		mediaPlayer->pause();
	}
}

void IcePlayer::ice_next_button_clicked()
{
	mediaList->setPlaybackMode(QMediaPlaylist::Loop);

	if (mediaList->currentIndex() != mediaList->nextIndex())
		mediaList->setCurrentIndex(mediaList->nextIndex());
	else if (mediaList->currentIndex() != mediaList->previousIndex())
		mediaList->setCurrentIndex(mediaList->previousIndex());

	mediaPlayer->play();
	playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromLocal8Bit(""));
	ice_set_play_mode();
}

void IcePlayer::ice_last_button_clicked()
{
	
	mediaList->setPlaybackMode(QMediaPlaylist::Loop);

	if(mediaList->currentIndex() != mediaList->previousIndex())
		mediaList->setCurrentIndex(mediaList->previousIndex());
	else
		mediaList->setCurrentIndex(mediaList->nextIndex());

	if (!mediaPlayer->isAudioAvailable()){
		playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromLocal8Bit("失效"));
	}
	
	mediaPlayer->play();
	playlistTable->item(mediaList->currentIndex(), 1)->setText(QString::fromLocal8Bit(""));
	ice_set_play_mode();
}

void IcePlayer::ice_lyric_button_clicked()
{
	if(iceLrc->isHidden()) iceLrc->show();
	else iceLrc->hide();
}

void IcePlayer::ice_logo_button_clicked()
{
	aboutForm->show();
}

void IcePlayer::ice_mode_button_clicked()
{
	playModeMenu->exec(QCursor::pos());
}

void IcePlayer::ice_min_button_clicked()
{
	miniForm->show();
	miniForm->ICE_Init_Play_Mode(volButton->ICE_Get_Volume());
	this->hide();
}

void IcePlayer::ice_set_play_mode()
{
	if(modeSingal->isChecked()) {
		playMode = ICE_Play_Mode::SINGAL;
		mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
	}
	else if(modeListCircle->isChecked()) {
		playMode = ICE_Play_Mode::LISTCIRCLE;
		mediaList->setPlaybackMode(QMediaPlaylist::Loop);
	}
	else if(modeSingalCircle->isChecked()) {
		playMode = ICE_Play_Mode::SINGALCIRCLE;
		mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	}
	else if(modeRandom->isChecked()) {
		playMode = ICE_Play_Mode::RANDOM;
		mediaList->setPlaybackMode(QMediaPlaylist::Random);
	}
}

void IcePlayer::ICE_set_mode_from_mini(int m)
{
	switch(m){
	case 0:
		playMode = ICE_Play_Mode::SINGAL;
		mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
		modeSingal->setChecked(true);
		break;
	case 1:
		playMode = ICE_Play_Mode::LISTCIRCLE;
		mediaList->setPlaybackMode(QMediaPlaylist::Loop);
		modeListCircle->setChecked(true);
		break;
	case 2:
		playMode = ICE_Play_Mode::SINGALCIRCLE;
		mediaList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
		modeSingalCircle->setChecked(true);
		break;
	case 3:
		playMode = ICE_Play_Mode::RANDOM;
		mediaList->setPlaybackMode(QMediaPlaylist::Random);
		modeRandom->setChecked(true);
		break;

	}
}

bool IcePlayer::ice_resolve_lrc(const QString &source_file_name)
{
	lrcMap.clear();
	if(source_file_name.isEmpty()) return false;
	QString file_name = source_file_name;
	QString lrc_file_name = file_name.remove(file_name.right(3)) + "lrc";//把音频文件的后缀改成lrc后缀

	// 打开歌词文件
	QFile file(lrc_file_name);
	if (!file.open(QIODevice::ReadOnly)) return false;

	QByteArray temp = file.readAll();

	QByteArray hehe;
	for (int i = 0; i < temp.size(); i++){
		if (temp.at(i) != 0)
			hehe.append(temp.at(i));
	}

	QString all_text;
	all_text = QString::fromUtf8(hehe);

	file.close();
	// 将歌词按行分解为歌词列表
	QStringList lines = all_text.split("\n");

	//这个是时间标签的格式[00:05.54]
	//正则表达式d{2}表示匹配2个数字
	QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
	foreach(QString oneline, lines) {
		QString temp = oneline;
		temp.replace(rx, "");//用空字符串替换正则表达式中所匹配的地方,这样就获得了歌词文本
		// 然后依次获取当前行中的所有时间标签，并分别与歌词文本存入QMap中
		//indexIn()为返回第一个匹配的位置，如果返回为-1，则表示没有匹配成功
		//正常情况下pos后面应该对应的是歌词文件
		int pos = rx.indexIn(oneline, 0);
		while (pos != -1) { //表示匹配成功
			QString cap = rx.cap(0);//返回第0个表达式匹配的内容
			// 将时间标签转换为时间数值，以毫秒为单位
			QRegExp regexp;
			regexp.setPattern("\\d{2}(?=:)");
			regexp.indexIn(cap);
			int minute = regexp.cap(0).toInt();
			regexp.setPattern("\\d{2}(?=\\.)");
			regexp.indexIn(cap);
			int second = regexp.cap(0).toInt();
			regexp.setPattern("\\d{2}(?=\\])");
			regexp.indexIn(cap);
			int millisecond = regexp.cap(0).toInt();
			qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;
			// 插入到lrc_map中
			lrcMap.insert(totalTime, temp);
			pos += rx.matchedLength();
			pos = rx.indexIn(oneline, pos);//匹配全部
		}
	}
	// 如果lrc_map为空
	if (lrcMap.isEmpty()) {
		iceLrc->setText(mediaPlayer->metaData(QMediaMetaData::Title).toString());
		return false;
	}

	return true;
}

void IcePlayer::ICE_goback_to_main()
{
	this->show();
}

void IcePlayer::ICE_set_vol_from_mini(int a)
{
	volButton->ICE_Set_Volume(a);
}

void IcePlayer::ice_read_list()
{
	QFile text(iceDir + "/IceList.ilst");
	QStringList inList;

	if(text.open(QIODevice::ReadOnly)){
		QDataStream in(&text);
		in.setVersion(QDataStream::Qt_5_2);
		in >> inList;
		ice_add_list(inList);
		text.close();
	}

}

void IcePlayer::ice_write_list()
{
	QFile text(iceDir + "/IceList.ilst");
	QStringList outList = playList;

	if (text.open(QIODevice::WriteOnly)){
		QDataStream out(&text);
		out.setVersion(QDataStream::Qt_5_2);
		out << outList;
		text.close();
	}

	
}

void IcePlayer::ICE_Open_Music(const QString& filePath)
{
	QStringList name;
	name.append(filePath);

	ice_add_list(name);

	if (playList.contains(filePath)){
		mediaList->setCurrentIndex(playList.indexOf(filePath));
		mediaPlayer->play();
	}

}

void IcePlayer::ice_color_table()
{
	for (int i = 0; i < playlistTable->rowCount(); i++){
		for (int j = 0; j < playlistTable->columnCount(); j++){
			QTableWidgetItem *item = playlistTable->item(i, j);
			if (item){
				const QColor color = QColor(255, 255, 255);
				item->setBackgroundColor(color);
			}
		}
		if (i % 2 == 0){
			for (int j = 0; j < playlistTable->columnCount(); j++){
				QTableWidgetItem *item = playlistTable->item(i, j);
				if (item){
					const QColor color = QColor(213, 228, 242);
					item->setBackgroundColor(color);
				}
			}
		}
	}
}

void IcePlayer::ice_init_network()
{
	networker = NetWorker::instance();
	receiveState = RECEIVE_INFO;

	connect(networker, &NetWorker::finished, [=](QNetworkReply *reply) {
		switch (receiveState){
		case RECEIVE_INFO:
			ice_rece_info(reply);
			ice_fetch_data();
			break;
		case RECEIVE_LINK:
			ice_rece_link(reply);
			ice_fetch_data();
			break;
		case RECEIVE_PIC:
			ice_rece_pic(reply);
			ice_fetch_data();
			break;
		case RECEIVE_LRC:
			ice_rece_lrc(reply);
			receiveState = RECEIVE_INFO;
			break;
		default:
			break;
		}

		//buggy there!!
		//这里应该删除上次的reply
		//reply->deleteLater();
		reply->abort();
	});
}

void IcePlayer::ice_fetch_data()
{
	QString query = QUrl::toPercentEncoding(songName + " " + songArtist);
	switch (receiveState){
	case RECEIVE_INFO:
		networker->get(
			QString("http://tingapi.ting.baidu.com/v1/restserver/ting?from=webapp_music&method=baidu.ting.search.catalogSug&format=json&callback=&query=" +
			query +
			"&_=1413017198449")
			);
		break;
	case RECEIVE_LINK:
		networker->get(QString("http://ting.baidu.com/data/music/links?songIds=" + songId));
		break;
	case RECEIVE_PIC:
		networker->get(picUrl);
		break;
	case RECEIVE_LRC:
		lrcUrl = QString("http://qukufile2.qianqian.com") + lrcUrl;
		networker->get(lrcUrl);
		break;
	default:
		break;
	}
}

void IcePlayer::ice_rece_info(QNetworkReply *reply)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
			QVariantMap data = jsonDocument.toVariant().toMap();

			song_info song;
			song.set_order(data[QLatin1String("order")].toString());
			song.set_error_code(data[QLatin1String("error_code")].toString());

			QVariantList result_list = data[QLatin1String("song")].toList();
			QVariantList album_list = data[QLatin1String("album")].toList();

			if (result_list.size() == 0){
				return;
			}

			QList<song_result *> results;
			foreach(QVariant s, result_list){
				QVariantMap sm = s.toMap();
				song_result *result = new song_result;
				result->set_songid(sm[QLatin1String("songid")].toString());
				result->set_songname(sm[QLatin1String("songname")].toString());
				result->set_has_mv(sm[QLatin1String("has_mv")].toInt());
				result->set_yyr_artist(sm[QLatin1String("yyr_artist")].toInt());
				result->set_artistname(sm[QLatin1String("artistname")].toString());
				results.append(result);
			}

			song.set_song_results(results);

			QList<album_info *> album_infos;
			foreach(QVariant a, album_list){
				QVariantMap ai = a.toMap();
				album_info *info = new album_info;
				info->set_albumid(ai[QLatin1String("albumid")].toString());
				info->set_albumname(ai[QLatin1String("albumname")].toString());
				info->set_artistname(ai[QLatin1String("artistname")].toString());
				info->set_artistpic(ai[QLatin1String("artistpic")].toString());
				album_infos.append(info);
			}

			song.set_album_infos(album_infos);

			if (results.count() > 0){
				song_result *temp = new song_result;
				temp = results[0];

				songId = temp->get_songid();
			}
			receiveState = RECEIVE_LINK;

		}
	}
	reply->deleteLater();
}

void IcePlayer::ice_rece_link(QNetworkReply *reply)
{
	QJsonParseError error;
	QJsonDocument jsonDocument = QJsonDocument::fromJson(reply->readAll(), &error);
	if (error.error == QJsonParseError::NoError) {
		if (!(jsonDocument.isNull() || jsonDocument.isEmpty()) && jsonDocument.isObject()) {
			QVariantMap data = jsonDocument.toVariant().toMap();

			song_link link;
			link.set_errorcode(data[QLatin1String("errorCode")].toString());

			QVariantMap song_data_map = data[QLatin1String("data")].toMap();

			song_data sdata;
			sdata.set_xcode(song_data_map[QLatin1String("xcode")].toString());

			QVariantList slist = song_data_map[QLatin1String("songList")].toList();
			QList<song_list *> slists;
			foreach(QVariant s, slist){
				QVariantMap sl = s.toMap();
				song_list *list = new song_list;
				list->set_songpic_radio(sl[QLatin1String("songPicRadio")].toString());
				list->set_lrclink(sl[QLatin1String("lrcLink")].toString());
				slists.append(list);
			}
			sdata.set_song_lists(slists);
			link.set_song_data(sdata);


			song_data temp2 = link.get_song_data();
			QList<song_list *> temp3 = temp2.get_song_lists();
			if (temp3.count() > 0){
				song_list *templist = temp3[0];

				picUrl = templist->get_songpic_radio();
				lrcUrl = templist->get_lrclick();
			}
			receiveState = RECEIVE_PIC;
		}
	}
	reply->deleteLater();
}

void IcePlayer::ice_rece_lrc(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError){
		QByteArray data = reply->readAll();
		QString fileName;

		QString temp = playingFile;
		fileName = temp.remove(temp.right(3)) + "lrc";

		QFile *file = new QFile(fileName);
		if (!file->open(QIODevice::WriteOnly)) {
			delete file;
			file = 0;
			return;
		}

		QDataStream out(file);
		out << data;
		file->close();
		delete file;
		file = 0;


	}
	reply->deleteLater();

	ice_resolve_lrc(playingFile);
}

void IcePlayer::ice_rece_pic(QNetworkReply *reply)
{
	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray data = reply->readAll();
		if (data.size() < 50){
			receiveState = RECEIVE_LRC;
			return;
		}
		QPixmap currentPicture;

		if (currentPicture.loadFromData(data)){
			picLabel->setPixmap(currentPicture);
		}

		receiveState = RECEIVE_LRC;

		QString fileName;
		QString temp = playingFile;
		fileName = temp.remove(temp.right(3)) + "jpg";

		QFile *file = new QFile(fileName);
		if (!file->open(QIODevice::WriteOnly)) {
			delete file;
			file = 0;
			return;
		}

		QImage image;
		QBuffer buffer(&data);
		buffer.open(QIODevice::WriteOnly);
		image.save(&buffer, "JPG");//把图片以流方式写入文件缓存流中
		file->write(data);
		file->close();
		delete file;
		file = 0;
	}
	reply->deleteLater();
}

bool IcePlayer::ice_get_pic_from_file()
{
	if (playingFile.isEmpty()) return false;
	QString file_name = playingFile;
	QString pic_file_name = file_name.remove(file_name.right(3)) + "jpg";//把音频文件的后缀改成lrc后缀

	// 打开歌词文件
	QFile file(pic_file_name);
	if (!file.open(QIODevice::ReadOnly)) return false;

	QByteArray temp = file.readAll();
	QPixmap currentPicture;

	if (currentPicture.loadFromData(temp)){
		picLabel->setPixmap(currentPicture);
	}
	
	file.close();

	return true;
}

void IcePlayer::ice_close()
{
	ice_write_list();

	ICE_SAFE_RELEASE(iceLrc);

	ICE_SAFE_RELEASE(minButton);
	ICE_SAFE_RELEASE(exitButton);
	ICE_SAFE_RELEASE(addButton);
	ICE_SAFE_RELEASE(lyricButton);
	ICE_SAFE_RELEASE(lastButton);
	ICE_SAFE_RELEASE(nextButton);
	ICE_SAFE_RELEASE(playButton);
	ICE_SAFE_RELEASE(pauseButton);
	ICE_SAFE_RELEASE(modeButton);
	ICE_SAFE_RELEASE(mminButton);
	ICE_SAFE_RELEASE(logoButton);

	ICE_SAFE_RELEASE(nameLabel);
	ICE_SAFE_RELEASE(musicianLabel);
	ICE_SAFE_RELEASE(albumLabel);
	ICE_SAFE_RELEASE(timeLabel);
	ICE_SAFE_RELEASE(picLabel);

	ICE_SAFE_RELEASE(playSlider);
	ICE_SAFE_RELEASE(volSlider);

	ICE_SAFE_RELEASE(playlistTable);
	ICE_SAFE_RELEASE(mediaPlayer);
	ICE_SAFE_RELEASE(mediaList);
	ICE_SAFE_RELEASE(contextMenuLess);
	ICE_SAFE_RELEASE(contextMenuMore);

	ICE_SAFE_RELEASE(modeSingal);
	ICE_SAFE_RELEASE(modeListCircle);
	ICE_SAFE_RELEASE(modeSingalCircle);
	ICE_SAFE_RELEASE(modeRandom);
	ICE_SAFE_RELEASE(addMusic);
	ICE_SAFE_RELEASE(addFileDiv);
	ICE_SAFE_RELEASE(removeCurr);
	ICE_SAFE_RELEASE(removeAll);
	ICE_SAFE_RELEASE(modeActionGroup);

	ICE_SAFE_RELEASE(volButton);
	ICE_SAFE_RELEASE(miniForm);
	ICE_SAFE_RELEASE(aboutForm);

}

void IcePlayer::ice_set_play_position(int pos)
{
	playPosition = pos;
}

int IcePlayer::ice_get_play_position()
{
	return playPosition;
}
