#pragma once

#include "../../protocol/protocol_vision.h"


class ColorMetrics : public QObject
{
	Q_OBJECT
public:
	static ColorMetrics* instance();
protected:
	ColorMetrics();
	static ColorMetrics* m_instance;

public:
	//QColor(0-255) -> LAB D65 
	void	QRgbToLabD65(const QColor&		QCr, ST_LABPoint& LabPt, bool GammaExist);
	//LAB D65 -> QColor(0-255) ���������ɫʱ����Ч ��������ʾ��Χ�ͱ��ã�
	bool    LabD65ToQRgb(const ST_LABPoint& LabPt,  QColor& QCr ,bool GammaExist);

	//RGB(0-255) <-> sRgb(0-1)
	void	QColorTosRgb(const QColor& Cr, ST_sRgbPoint& sRgb);
	void	sRgbToQColor(const ST_sRgbPoint& sRgb, QColor& Cr);

	//sRgb(0-1) <-> gamma(sRgb)
	// sRgb����Ļ�ϵ�ǿ�ȱ���ͷ����� �����ڼ���ǿ������һ���ֶ�
	void	sRgbToGammaSRGB(const ST_sRgbPoint& sRgb		,ST_sRgbPoint& sRgbGamma);
	void	GammaSRGBToSRgb(const ST_sRgbPoint& sRgbGamma	,ST_sRgbPoint& sRgb);;

	//sRgb(0-1) <-> CIE xyz(0-1)
	void	sRgbToXYZ(const ST_sRgbPoint&	sRgb, ST_xyzPoint&	XYZPt );
	void	XYZTosRgb(const ST_xyzPoint&	XYZPt,ST_sRgbPoint& sRgb);

	//���һ��xyz���Ƿ�λ��sRgb��Χ�ڣ������߽磩
	//��ô����xyzת����Ľ�����鿴rgb��Χ�Ƿ����[0-1]
	bool	checkSRgbValid(const ST_sRgbPoint& sRgbPt);
	
	//CIE xyz(0-1) <-> CIE LAB D65(1976)
	void	XYZToLabD65(const ST_xyzPoint& XYZPt , ST_LABPoint& LabPt);
	void	LabD65ToXYZ(const ST_LABPoint& LabPt , ST_xyzPoint& XYZPt);

	double getMetric_RGB255(const QColor& pos1, const QColor& pos2);
	double getMetric_LAB(const EN_LAB_Metric_Type metricType, const ST_LABPoint& LAB1, const ST_LABPoint& LAB2);

protected:
	double getMetric_LAB_1976(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2);
	double getMetric_LAB_1984(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2);
	double getMetric_LAB_1994(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2);
	double getMetric_LAB_2000(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2);

	//��LABת�������� C�ǰ뾶 H�ǽǶ�
	// ����H�õ��ǽǶȶ��ǻ�����Ϊ��ʽ���ǽǶ�
	void   getLAB_HC(const ST_LABPoint& LABpt, double& C, double& H);
	//����һ������ɫ���ƽ����ֵ�����κܼ򵥣������ܳ���
	double getDisH_Pow2(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2, const double C1, const double C2);

};

