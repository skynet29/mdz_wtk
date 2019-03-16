// MdzSlider.h: interface for the MdzSlider class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZSLIDER_H__EA9FFD2E_46B0_4060_A4DF_F4D7F33095B1__INCLUDED_)
#define AFX_MDZSLIDER_H__EA9FFD2E_46B0_4060_A4DF_F4D7F33095B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzCbk1.h"

class MdzEvent;

class DllExport MdzSlider : public MdzCtrl  
{
public:
	MdzSlider();

	void
	SetValue(int iValue);
	
	void
	SetRange(int iMin, int iMax);
	
	void
	SetBorder(BOOL bHasBorder);
	
	void
	SetOnSelChange(MdzCbk1* lpFunc);

	int
	GetValue();

	virtual void
	Create();

	virtual ~MdzSlider();
private:
	void OnHScroll(MdzEvent& evt);
	int iMin;
	int iMax;
	int iValue;
	MdzCbk1* lpOnSelChange;

};

#endif // !defined(AFX_MDZSLIDER_H__EA9FFD2E_46B0_4060_A4DF_F4D7F33095B1__INCLUDED_)
