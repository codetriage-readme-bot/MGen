// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#ifndef _MEMDC_H_
#define _MEMDC_H_
 
//////////////////////////////////////////////////
// CMemDC2 - memory DC
//
// Author: Keith Rule
// Email:  keithr@europa.com
// Copyright 1996-1997, Keith Rule
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
// History - 10/3/97 Fixed scrolling bug.
//                   Added print support.
//
// This class implements a memory Device Context
 
class CMemDC2 : public CDC {
private:
	CBitmap m_bitmap; // Offscreen bitmap
	CBitmap* m_oldBitmap; // bitmap originally found in CMemDC2
	CDC* m_pDC; // Saves CDC passed in constructor
	CRect m_rect; // Rectangle of drawing area.
	BOOL m_bMemDC; // TRUE if CDC really is a Memory DC.
public:
	CMemDC2(CDC* pDC) : CDC(), m_oldBitmap(NULL), m_pDC(pDC)
	{
		ASSERT(m_pDC != NULL); // If you asserted here, you passed in a NULL CDC.
		
		m_bMemDC = !pDC->IsPrinting();
		
		if (m_bMemDC){
			// Create a Memory DC
			CreateCompatibleDC(pDC);
			pDC->GetClipBox(&m_rect);
			m_bitmap.CreateCompatibleBitmap(pDC, m_rect.Width(), m_rect.Height());
			m_oldBitmap = SelectObject(&m_bitmap);
			SetWindowOrg(m_rect.left, m_rect.top);
			//pDC->DPtoLP(&m_rect);
			//SetBrushOrg(-(m_rect.left % 8), -(m_rect.top % 8));
		} else {
			// Make a copy of the relevent parts of the current DC for printing
			m_bPrinting = pDC->m_bPrinting;
			m_hDC = pDC->m_hDC;
			m_hAttribDC = pDC->m_hAttribDC;
		}
	}
	
	~CMemDC2()
	{
		if (m_bMemDC) {
			// Copy the offscreen bitmap onto the screen.
			m_pDC->BitBlt(m_rect.left, m_rect.top, m_rect.Width(), m_rect.Height(),
				this, m_rect.left, m_rect.top, SRCCOPY);
			//Swap back the original bitmap.
			SelectObject(m_oldBitmap);
		} else {
			// All we need to do is replace the DC with an illegal value,
			// this keeps us from accidently deleting the handles associated with
			// the CDC that was passed to the constructor.
			m_hDC = m_hAttribDC = NULL;
		}
	}
	
	// Allow usage as a pointer
	CMemDC2* operator->() {return this;}
	
	// Allow usage as a pointer
	operator CMemDC2*() {return this;}
};
 
#endif
