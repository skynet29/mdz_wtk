// MdzToolTips.h: interface for the MdzToolTips class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZTOOLTIPS_H__FA5F06A6_EAC9_439E_8797_42370FADA782__INCLUDED_)
#define AFX_MDZTOOLTIPS_H__FA5F06A6_EAC9_439E_8797_42370FADA782__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzCtrl.h"
#include "MdzString.h"

class MdzToolTips : public MdzCtrl  
{
public:
	virtual void Create();
	MdzToolTips(MdzCtrl* lpParent, LPSTR lpText);
	virtual ~MdzToolTips();
private:
	MdzString strText;

};

#endif // !defined(AFX_MDZTOOLTIPS_H__FA5F06A6_EAC9_439E_8797_42370FADA782__INCLUDED_)
