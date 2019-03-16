// MdzLayoutEx.h: interface for the MdzLayoutEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MDZLAYOUTEX_H__A5BC4209_44EF_496D_A172_CBFBCF1FD9E7__INCLUDED_)
#define AFX_MDZLAYOUTEX_H__A5BC4209_44EF_496D_A172_CBFBCF1FD9E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MdzBounds.h"
#include "MdzVector.h"
#include "MdzRect.h"	// Added by ClassView

class MdzCtrl;
class MdzContainer;

class DllExport MdzLayout  
{
public:
	MdzRect GetBoundaryRect();
	void AddBorder(int spacing = 10, LPSTR strTitle = NULL);
	void Restore();
	void Save();
	MdzLayout(MdzContainer* parent, int x, int y);
	virtual ~MdzLayout();
	void AddLabel(LPSTR strText, int width, int height, int flag = K_RIGHT, int spacing = 10);
	void Add(MdzCtrl& ctrl, int width, int height, int flag = K_RIGHT, int spacing = 10);

	enum {
		K_RIGHT,
		K_LEFT,
		K_BOTTOM_LEFT,
		K_BOTTOM_RIGHT,
		K_NEXT_LINE
	};
private:
	int xStart, yStart;
	MdzCtrl* pCtrl;
	MdzVectorT<MdzCtrl> ctrls;
	MdzCtrl* pSaveCtrl;
	MdzContainer* parent;
	MdzRect rect;
};

#endif // !defined(AFX_MDZLAYOUTEX_H__A5BC4209_44EF_496D_A172_CBFBCF1FD9E7__INCLUDED_)
