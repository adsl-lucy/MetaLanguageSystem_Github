#include "ColorMetrics.h"
#pragma execution_character_set("utf-8")

ColorMetrics* ColorMetrics::m_instance = nullptr;

ColorMetrics::ColorMetrics()
{
	
}

ColorMetrics* ColorMetrics::instance()
{
	if (m_instance == nullptr)
	{
		m_instance = new ColorMetrics();
	}
	return m_instance;
}

void ColorMetrics::QRgbToLabD65(const QColor& QCr, ST_LABPoint& LabPt, bool GammaExist)
{
	ST_sRgbPoint sRgb, sRgb_gamma;
	ST_xyzPoint  xyzPt;

	QColorTosRgb(QCr, sRgb);
	if (GammaExist)
	{		
		sRgbToGammaSRGB(sRgb, sRgb_gamma);
		sRgbToXYZ(sRgb_gamma, xyzPt);
		XYZToLabD65(xyzPt, LabPt);
	}
	else
	{
		sRgbToXYZ(sRgb, xyzPt);
		XYZToLabD65(xyzPt, LabPt);
	}
}

bool ColorMetrics::LabD65ToQRgb(const ST_LABPoint& LabPt, QColor& QCr, bool GammaExist)
{
	ST_xyzPoint  xyzPt;
	ST_sRgbPoint sRgb, sRgb_gamma;
	LabD65ToXYZ(LabPt, xyzPt);
	if (GammaExist)
	{	
		XYZTosRgb(xyzPt, sRgb_gamma);		
		bool sRgbValid = checkSRgbValid(sRgb_gamma);
		if (!sRgbValid)
		{
			return false;
		}
		GammaSRGBToSRgb(sRgb_gamma, sRgb);
		sRgbToQColor(sRgb, QCr);
		return true;
	}
	else
	{
		XYZTosRgb(xyzPt, sRgb);
		bool sRgbValid = checkSRgbValid(sRgb);
		if (!sRgbValid)
		{
			return false;
		}

		sRgbToQColor(sRgb, QCr);
		return true;
	}

}

void ColorMetrics::QColorTosRgb(const QColor& Cr, ST_sRgbPoint& sRgb)
{
	sRgb.r = (double)Cr.red()	/ (double)255.0;
	sRgb.g = (double)Cr.green() / (double)255.0;
	sRgb.b = (double)Cr.blue()	/ (double)255.0;
}

void ColorMetrics::sRgbToQColor(const ST_sRgbPoint& sRgb, QColor& Cr)
{
	Cr.setRed(	sRgb.r * 255.0);
	Cr.setGreen(sRgb.g * 255.0);
	Cr.setBlue(	sRgb.b * 255.0);
}

void ColorMetrics::sRgbToGammaSRGB(const ST_sRgbPoint& sRgb, ST_sRgbPoint& sRgbGamma)
{
	auto Gamma = [](double floatVal)->double
		{
			if (floatVal <= 0.04045)
			{
				return floatVal / 12.92;
			}
			else
			{
				return pow(((floatVal + 0.055) / 1.055), 2.4);
			}
		};

	sRgbGamma.r = Gamma(sRgb.r);
	sRgbGamma.g = Gamma(sRgb.g);
	sRgbGamma.b = Gamma(sRgb.b);
}

void ColorMetrics::GammaSRGBToSRgb(const ST_sRgbPoint& sRgbGamma, ST_sRgbPoint& sRgb)
{
	auto Gamma_Inverse = [](double floatVal)->double
		{
			if (floatVal <= 0.0031308)
			{
				return 12.92 * floatVal;
			}
			else
			{
				return (1.055 * pow(floatVal, 1.0 / 2.4)) - 0.055;
			}
		};

	sRgb.r = Gamma_Inverse(sRgbGamma.r);
	sRgb.g = Gamma_Inverse(sRgbGamma.g);
	sRgb.b = Gamma_Inverse(sRgbGamma.b);
}

void ColorMetrics::sRgbToXYZ(const ST_sRgbPoint& sRgb, ST_xyzPoint& xyzPt)
{
	xyzPt.x = 0.412453 * sRgb.r + 0.357580 * sRgb.g + 0.180423 * sRgb.b;
	xyzPt.y = 0.212671 * sRgb.r + 0.715160 * sRgb.g + 0.072169 * sRgb.b;
	xyzPt.z = 0.019334 * sRgb.r + 0.119193 * sRgb.g + 0.950227 * sRgb.b;
}

void ColorMetrics::XYZTosRgb(const ST_xyzPoint& xyzPt, ST_sRgbPoint& sRgb)
{
	sRgb.r =  3.2406255 * xyzPt.x - 1.5372080 * xyzPt.y - 0.4986286 * xyzPt.z;
	sRgb.g = -0.9689307 * xyzPt.x + 1.8757561 * xyzPt.y + 0.0415175 * xyzPt.z;
	sRgb.b =  0.0557101 * xyzPt.x - 0.2040211 * xyzPt.y + 1.0569959 * xyzPt.z;
}

//const double const_sRgb_R_x = 0.64;
//const double const_sRgb_R_y = 0.33;
//const double const_sRgb_R_Y = 0.2126;
//
//const double const_sRgb_G_x = 0.3;
//const double const_sRgb_G_y = 0.6;
//const double const_sRgb_G_Y = 0.7152;
//
//const double const_sRgb_B_x = 0.15;
//const double const_sRgb_B_y = 0.06;
//const double const_sRgb_B_Y = 0.0722;
//
//// White Color
//const double const_sRgb_W_x = 0.3127;
//const double const_sRgb_W_y = 0.3290;
//const double const_sRgb_W_Y = 1.0000;

bool ColorMetrics::checkSRgbValid(const ST_sRgbPoint& sRgbPt)
{
	if (sRgbPt.r < 0 || sRgbPt.r > 1)
	{
		return false;
	}

	if (sRgbPt.g < 0 || sRgbPt.g > 1)
	{
		return false;
	}

	if (sRgbPt.b < 0 || sRgbPt.b > 1)
	{
		return false;
	}

	return true;
}

const double LabD65_Xn = 95.0489;
const double LabD65_Yn = 100.0;
const double LabD65_Zn = 108.8840;

const double LabD65_Delta = 6.0 / 29.0;

const double XYZToLab_FunT_Range = pow(LabD65_Delta, 3);
const double XYZToLab_FunT_ParaA = (1.0 / 3.0) * pow(LabD65_Delta, -2);
const double XYZToLab_FunT_ParaB = 4.0 / 29;



void ColorMetrics::XYZToLabD65(const ST_xyzPoint& xyzPt, ST_LABPoint& LabPt)
{
	auto XYZToLab_FunT = [](double refVal)->double
		{
			if (refVal > XYZToLab_FunT_Range)
			{
				return pow(refVal, 0.3333);
			}
			else
			{
				return XYZToLab_FunT_ParaA * refVal + XYZToLab_FunT_ParaB;
			}
		};

	//输入的xyz范围是(0-1 ) 但是这里XYZ是(0-100)
	double RelvanceX_f = XYZToLab_FunT(xyzPt.x * 100 / LabD65_Xn);
	double RelvanceY_f = XYZToLab_FunT(xyzPt.y * 100 / LabD65_Yn);
	double RelvanceZ_f = XYZToLab_FunT(xyzPt.z * 100 / LabD65_Zn);

	LabPt.L = 116.0 *  RelvanceY_f - 16;
	LabPt.A = 500.0 * (RelvanceX_f - RelvanceY_f);
	LabPt.B = 200.0 * (RelvanceY_f - RelvanceZ_f);
}

const double XYZToLab_FunTInverse_Range = LabD65_Delta;
const double XYZToLab_FunTInverse_ParaA = 3 * pow(LabD65_Delta, 2);
const double XYZToLab_FunTInverse_ParaB = -4.0 / 29;

void ColorMetrics::LabD65ToXYZ(const ST_LABPoint& LabPt, ST_xyzPoint& xyzPt)
{
	auto XYZToLab_FunT_Inverse = [](double Val)->double
		{
			if (Val > XYZToLab_FunTInverse_Range)
			{
				return pow(Val,3);
			}
			else
			{
				return XYZToLab_FunTInverse_ParaA * (Val + XYZToLab_FunTInverse_ParaB);
			}
		};

	double X = LabD65_Xn * XYZToLab_FunT_Inverse(((LabPt.L + 16) / 116) + (LabPt.A / 500));
	double Y = LabD65_Yn * XYZToLab_FunT_Inverse( (LabPt.L + 16) / 116);
	double Z = LabD65_Zn * XYZToLab_FunT_Inverse(((LabPt.L + 16) / 116) - (LabPt.B / 200));

	xyzPt.x = X / 100.0;
	xyzPt.y = Y / 100.0;
	xyzPt.z = Z / 100.0;

}


double ColorMetrics::getMetric_RGB255(const QColor& pos1, const QColor& pos2)
{
	double RDisPow2 = pow(pos1.red()	- pos2.red(), 2);
	double GDisPow2 = pow(pos1.green()	- pos2.green(), 2);
	double BDisPow2 = pow(pos1.blue()	- pos2.blue(), 2);

	return sqrt(RDisPow2 + GDisPow2 + BDisPow2);
}

double ColorMetrics::getMetric_LAB(const EN_LAB_Metric_Type metricType, const ST_LABPoint& LAB1, const ST_LABPoint& LAB2)
{
	switch (metricType)
	{
		case EN_LAB_Metric_Type::CIE_1976:return getMetric_LAB_1976(LAB1, LAB2); break;
		case EN_LAB_Metric_Type::CIE_1984:return getMetric_LAB_1984(LAB1, LAB2); break;
		case EN_LAB_Metric_Type::CIE_1994:return getMetric_LAB_1994(LAB1, LAB2); break;
		case EN_LAB_Metric_Type::CIE_2000:return getMetric_LAB_2000(LAB1, LAB2); break;
	}
	return -1;
}

double ColorMetrics::getMetric_LAB_1976(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2)
{
	double LDisPow2 = pow(LAB1.L - LAB2.L, 2);
	double ADisPow2 = pow(LAB1.A - LAB2.A, 2);
	double BDisPow2 = pow(LAB1.B - LAB2.B, 2);

	return sqrt(LDisPow2 + ADisPow2 + BDisPow2);
}

double ColorMetrics::getMetric_LAB_1984(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2)
{

	auto get_lSL = [](const ST_LABPoint& LABpt_Ref, const bool Imperctpt_Threshold)->double
		{
			double SL,l;
			if (LABpt_Ref.L < 16)
			{
				SL = 0.511;
			}
			else
			{
				SL = (0.040975 * LABpt_Ref.L) / (1 + 0.01765 * LABpt_Ref.L);
			}

			if (Imperctpt_Threshold)
			{
				l = 1;
			}
			else
			{
				l = 2;
			}

			return l * SL;

		};

	auto get_cSC = [](const double LABpt_Ref_C,double &SC,double& CSC)
		{
			SC = 0.0638 * LABpt_Ref_C / (1 + 0.0131 * LABpt_Ref_C) + 0.638;
			CSC = 1 * SC;
		};

	auto get_SH = [](const double LABpt_Ref_C, const double LABpt_Ref_H,const double SC)
		{
			double C1_P4 = pow(LABpt_Ref_C, 4);
			double F = sqrt(C1_P4 / (C1_P4 + 1900));
			double T;
			if (LABpt_Ref_H >= 164 && LABpt_Ref_H <= 345)
			{
				T = 0.56 + abs(0.2 * cos(VisionProtocol::DegreeToArc(LABpt_Ref_H + 168)));
			}
			else
			{
				T = 0.36 + abs(0.4 * cos(VisionProtocol::DegreeToArc(LABpt_Ref_H + 35)));
			}
			double SH = SC * (F * T + 1 - F);
			return SH;

		};

	double C1, H1, C2, H2;

	getLAB_HC(LAB1, C1, H1);
	getLAB_HC(LAB2, C2, H2);

	double DisL_Pow2 = pow(LAB1.L - LAB2.L, 2);
	double lSl = get_lSL(LAB1, true);

	double DisC_Pow2 = pow(C1 - C2, 2);
	double SC, cSC;
	get_cSC(C1, SC, cSC);

	double DisH_Pow2 = getDisH_Pow2(LAB1, LAB2, C1,C2);
	double SH = get_SH(C1, H1, SC);

	double Delta_E_CMC = sqrt((DisL_Pow2 / pow(lSl, 2)) + (DisC_Pow2 / pow(cSC, 2)) + (DisH_Pow2 / pow(SH, 2)));
	return Delta_E_CMC;

}

double ColorMetrics::getMetric_LAB_1994(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2)
{

	auto getCIE94Constanct = [](double& KL, double& K1, double& K2,const bool graphic)
		{
			if (graphic)
			{
				KL = 1;
				K1 = 0.045;
				K2 = 0.015;
			}
			else
			{
				KL = 2;
				K1 = 0.048;
				K2 = 0.014;
			}
		};

	double C1, H1, C2, H2;
	double KL, K1, K2;
	double KC, KH;
	KC = KH = 1;

	getLAB_HC(LAB1, C1, H1);
	getLAB_HC(LAB2, C2, H2);
	getCIE94Constanct(KL, K1, K2,true);

	double DisL_Pow2 = pow(LAB1.L - LAB2.L, 2);
	double SL = 1;

	double DisC_Pow2 = pow(C1 - C2, 2);
	double SC = 1 + K1 * C1;

	double DisH_Pow2 = getDisH_Pow2(LAB1, LAB2, C1, C2);
	double SH = 1 + K2 * C1;

	double Delta_E_94 = sqrt((DisL_Pow2 / pow(SL * KL, 2)) + (DisC_Pow2 / pow(SC * KC, 2)) + (DisH_Pow2 / pow(KH * SH, 2)));
	return Delta_E_94;

}

double ColorMetrics::getMetric_LAB_2000(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2)
{
	return 0.0;
}

void ColorMetrics::getLAB_HC(const ST_LABPoint& LABpt, double& C, double& H)
{
	C = sqrt(pow(LABpt.A, 2) + pow(LABpt.B, 2));
	H = VisionProtocol::ArcToDegree(atan(LABpt.B / LABpt.A));
}

double ColorMetrics::getDisH_Pow2(const ST_LABPoint& LAB1, const ST_LABPoint& LAB2, const double C1, const double C2)
{
	double DisH_Pow2 = pow(LAB1.A - LAB2.A, 2) + pow(LAB1.B - LAB2.B, 2) - pow(C1 - C2, 2);
	return DisH_Pow2;
}
