// MdzLayoutEx.cpp: implementation of the MdzLayoutEx class.
//
//////////////////////////////////////////////////////////////////////

#include "MdzLayout.h"
#include "MdzContainer.h"
#include "MdzBorder.h"
#include "MdzLabel.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MdzLayout::MdzLayout(MdzContainer* parent, int x, int y)
{
	xStart = x; yStart = y;
	this->parent = parent;
	pCtrl = NULL;
	pSaveCtrl = NULL;
}

MdzLayout::~MdzLayout()
{

}

void MdzLayout::Add(MdzCtrl &ctrl, int width, int height, int flag, int spacing)
{
	ctrls.Add(&ctrl);

	if (!pCtrl)
	{
		MdzBounds bds(xStart, yStart, width, height);
		parent->Add(ctrl, bds);
		pCtrl = &ctrl;
		rect = bds;
		return;
	}

	int x, y;
	MdzBounds bds = pCtrl->GetBounds();

	switch (flag)
	{
	case K_RIGHT:
		x = bds.left + bds.width + spacing;
		y = bds.top;
		break;

	case K_LEFT:
		x = bds.left - width - spacing;
		y = bds.top;
		break;

	case K_BOTTOM_LEFT:
		x = bds.left;
		y = bds.top + bds.height + spacing;
		break;

	case K_BOTTOM_RIGHT:
		x = bds.left + max(0, bds.width - width);
		y = bds.top + bds.height + spacing;
		break;

	case K_NEXT_LINE:
		x = xStart;
		y = rect.bottom + spacing;
		SetRectEmpty(&rect);
		break;

	default:
		return;
	}

	pCtrl = &ctrl;
	bds = MdzBounds(x, y, width, height);
	parent->Add(ctrl, bds);
	bds = pCtrl->GetBounds();
	rect += bds;

}





void MdzLayout::Save()
{
	pSaveCtrl = pCtrl;
}

void MdzLayout::Restore()
{
	if (pSaveCtrl)
	{
		pCtrl = pSaveCtrl;
	}
}

void MdzLayout::AddLabel(LPSTR strText, int width, int height, int flag, int spacing)
{
	MdzLabel* pLabel = new MdzLabel;
	pLabel->SetAutoDelete(TRUE);
	pLabel->SetText(strText);
	Add(*pLabel, width, height, flag, spacing);
}


void MdzLayout::AddBorder(int spacing, LPSTR strTitle)
{
	if (ctrls.GetCount() == 0)
		return;

	UINT iStartIdx = 0;
	UINT i;
	for(i = 0; i < ctrls.GetCount(); i++)
	{
		if (&ctrls[i] == pSaveCtrl)
		{
			iStartIdx = i;
			break;
		}
	}

	MdzRect rc;
	for(i = iStartIdx; i < ctrls.GetCount(); i++)
	{
		rc += ctrls[i].GetBounds();
	}

	rc.Inflate(spacing, spacing);
	rc.top -= spacing / 2;
	MdzBorder* pBorder = new MdzBorder;
	if (strTitle)
		pBorder->SetTitle(strTitle);
	pBorder->SetAutoDelete(TRUE);
	MdzBounds bds(rc.left, rc.top, rc.Width(), rc.Height());
	parent->Add(*pBorder, bds);

}

MdzRect MdzLayout::GetBoundaryRect()
{
	MdzRect rc;
	for(UINT i = 0; i < ctrls.GetCount(); i++)
	{
		rc += ctrls[i].GetBounds();
	}
	return rc;

}
