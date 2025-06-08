#pragma once

#include <QObject>
#include <QMap>
#include "../../Audio/protocol/protocol_audio.h"
#include "../../Vision/protocol/protocol_vision.h"

//数据中心数据类型
enum class EN_DataCenterAudioDataType :int
{
	AudioModuleSignal,
	WavDoubleData,
	STFTOutputData,
	WndSpecConstrain,
	BDSNR,
	Diff,
	FreqDoub,
	VibState,
};

enum class EN_DataCenterVisualDataType :int
{
	QImage,
	VisualImg,
};

//存储数据用的，没啥特别的功能
class DataCenterManager : public  QObject
{
	Q_OBJECT
public:
	static DataCenterManager* instance();
protected:
	DataCenterManager();
	static DataCenterManager* m_instance;

#pragma region audio Data
public:
	bool checkDataExist(EN_DataCenterAudioDataType dataType, QString Key);
	int  getDaraFrameCount(EN_DataCenterAudioDataType dataType, QString Key);


	const QMap<QString, ST_AudioModuleSignal>&				getGenSigMap()					{ return m_map_GenSig; };
	const QMap<QString, ST_WavDoubleData>&					getWavSigMap()					{ return m_map_WavSig; };

	const QMap<QString, ST_STFTOutputData>&					getSTFTOutputMap()				{ return m_map_STFTOutput; };
	const QMap<QString, ST_WndSpecConstrainResult>&			getWndSpecConstrainOutputMap()	{ return m_mapWndSpecConstrain; };
	const QMap<QString, ST_BandWidthSNRConstrainData>&		getBDSNROutputMap()				{ return m_mapBDSNR;};
	const QMap<QString, ST_VibrateStateNetworkNetworkData>&	getVibStateOutputMap()   { return m_mapVibState; };

	const QMap<QString, ST_DiffNetOutput>&					getDiffOutputMap()				{ return m_mapDiff; };
	const QMap<QString, ST_FreqDoubleNetworkOutput>&		getFreqDoubeOutputMap()			{ return m_mapFreqDoub;};


public:signals:

	void sgn_WavDoubleDataSaved(QString dataKey);

	//通知其他对象存储了新的数据
	//调用存储接口的对象不要接这个信号，不然直接递归爆炸
	void sgn_STFTDataSaved(QString dataKey);
	void sgn_WndConstrainDataSaved(QString dataKey);
	void sgn_BDSNRDataSaved(QString dataKey);
	void sgn_VibStateRelDataSaved(QString dataKey);

	void sgn_DiffDataSaved(QString dataKey);
	void sgn_FreqDoubDataSaved(QString dataKey);


public slots:
	void slot_saveGenerateSignal(ST_AudioModuleSignal& data,bool& saveState);
	void slot_saveWavData(ST_WavDoubleData& data, bool& saveState);

	//这个数据很大(2-5G)，所以生成之后会立刻删除输入数据，然后返回存储数据的key
	QString slot_saveSTFTData(ST_STFTOutputData& STFTOutputData, bool& saveState);
	void slot_saveWndSpecConstrainData(QString key, ST_WndSpecConstrainResult& tempData);
	void slot_saveBDSNRData(QString key, ST_BandWidthSNRConstrainData& tempData);	
	void slot_saveVibStateData(QString key, ST_VibrateStateNetworkNetworkData& tempData);
	void slot_saveDiffData(QString key, ST_DiffNetOutput& tempData);
	void slot_saveFreqDoubData(QString key, ST_FreqDoubleNetworkOutput& tempData);

private:
	QMap<QString, ST_AudioModuleSignal>				m_map_GenSig;
	QMap<QString, ST_WavDoubleData>					m_map_WavSig;
	QMap<QString, ST_STFTOutputData>				m_map_STFTOutput;
	QMap<QString, ST_WndSpecConstrainResult>		m_mapWndSpecConstrain;
	QMap<QString, ST_BandWidthSNRConstrainData>		m_mapBDSNR;
	QMap<QString, ST_VibrateStateNetworkNetworkData> m_mapVibState;

	QMap<QString, ST_DiffNetOutput>					m_mapDiff;
	QMap<QString, ST_FreqDoubleNetworkOutput>		m_mapFreqDoub;
#pragma endregion


#pragma region visual Data
public:
	bool checkImageExist(EN_DataCenterVisualDataType dataType ,QString Key);
	const QMap<QString, QImage>&			getQImageMap() { return m_map_QImage; };
	const QMap<QString, ST_VisualImage>&	getVisualMap() { return m_map_VisualImage; };
public:signals:
	void sgn_QImgDataSaved(QString dataKey);
	void sgn_VisualImgDataSaved(QString dataKey);
public slots:
	void slot_saveQImg(QString Key,QImage& data, bool& saveState);
	void slot_saveVisualImg(ST_VisualImage& data, bool& saveState);
private:
	QMap<QString, QImage>						m_map_QImage;
	QMap<QString, ST_VisualImage>				m_map_VisualImage;
#pragma endregion
};

