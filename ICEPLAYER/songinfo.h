#ifndef SONG_INFO_H
#define SONG_INFO_H

#include <QString>
#include <QList>

class song_result{
public:
	song_result(){}
	~song_result(){}

	void set_songid(QString songid){
		_songid = songid;
	}

	QString get_songid(){
		return _songid;
	}

	void set_songname(QString songname){
		_songname = songname;
	}

	QString get_songname(){
		return _songname;
	}

	void set_has_mv(int has_mv){
		_has_mv = has_mv;
	}

	int get_has_mv(){
		return _has_mv;
	}

	void set_yyr_artist(int yyr_artist){
		_yyr_artist = yyr_artist;
	}

	int get_yyr_artist(){
		return _yyr_artist;
	}

	void set_artistname(QString artistname){
		_artistname = artistname;
	}

	QString get_artistname(){
		return _artistname;
	}

private:
	QString _songid;
	QString _songname;
	QString _encrypted_songid;
	int _has_mv;
	int _yyr_artist;
	QString _artistname;
};

class album_info{
public:
	album_info(){}
	~album_info(){}

	void set_albumid(QString albumid){
		_albumid = albumid;
	}

	QString get_albumid(){
		return _albumid;
	}

	void set_albumname(QString albumname){
		_albumname = albumname;
	}

	QString get_albumname(){
		return _albumname;
	}

	void set_artistname(QString artistname){
		_artistname = artistname;
	}

	QString get_artistname(){
		return _artistname;
	}

	void set_artistpic(QString artistpic){
		_artistpic = artistpic;
	}

	QString get_artistpic(){
		return _artistpic;
	}

private:
	QString _albumid;
	QString _albumname;
	QString _artistname;
	QString _artistpic;
};

class song_info{
public:
	song_info(){}
	~song_info(){}

	void set_order(QString order){
		_order = order;
	}

	QString get_order(){
		return _order;
	}

	void set_error_code(QString error_code){
		_error_code = error_code;
	}

	QString get_error_code(){
		return _error_code;
	}

	void set_song_results(QList<song_result *> song_results){
		_song_results = song_results;
	}

	QList<song_result *> get_song_results(){
		return _song_results;
	}

	void set_album_infos(QList<album_info *> album_infos){
		_album_infos = album_infos;
	}

	QList<album_info *> get_album_infos(){
		return _album_infos;
	}

private:
	QString _order;
	QString _error_code;

	QList<song_result *> _song_results;
	QList<album_info *> _album_infos;
};

class song_list;
class song_link;

class song_data{
public:
	song_data(){}
	~song_data(){}

	void set_xcode(QString xcode){
		_xcode = xcode;
	}

	QString get_xcode(){
		return _xcode;
	}

	void set_song_lists(QList<song_list *> song_lists){
		_song_lists = song_lists;
	}

	QList<song_list *> get_song_lists(){
		return _song_lists;
	}

private:
	QString _xcode;
	QList<song_list *> _song_lists;
};

class song_list{
public:
	song_list(){}
	~song_list(){}

	void set_songpic_radio(QString songpic_radio){
		_songpic_radio = songpic_radio;
	}

	QString get_songpic_radio(){
		return _songpic_radio;
	}

	void set_lrclink(QString lrclink){
		_lrclick = lrclink;
	}

	QString get_lrclick(){
		return _lrclick;
	}

private:
	QString _queryid;
	QString _songid;
	QString _songname;
	QString _artistid;
	QString _artistname;
	QString _albumid;
	QString _songpic_small;
	QString _songpic_big;
	QString _songpic_radio;
	QString _lrclick;
	QString _version;
	QString _copytype;
	QString _time;
	QString _linkcode;
	QString _songlink;
	QString _format;
	QString _rate;
	QString _size;
	QString _relatestatus;
	QString _resourcetype;

};

class song_link{
public:
	song_link(){}
	~song_link(){}

	void set_errorcode(QString errorcode){
		_errorcode = errorcode;
	}

	QString get_errorcode(){
		return _errorcode;
	}

	void set_song_data(song_data sdata){
		_song_datas = sdata;
	}

	song_data get_song_data(){
		return _song_datas;
	}


private:

	QString _errorcode;
	song_data _song_datas;

};

#endif //SONG_INFO_H