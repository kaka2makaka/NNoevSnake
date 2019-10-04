
// SnakeDoc.cpp : implementation of the CSnakeDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif

#include "SnakeDoc.h"
#include "SnakeView.h"
#include "CSnake.h"
#include <propkey.h>

#include <windows.h>
#include <MsXml6.h>
#include <comutil.h>
#pragma comment(lib, "comsuppwd.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSnakeDoc

IMPLEMENT_DYNCREATE(CSnakeDoc, CDocument)

BEGIN_MESSAGE_MAP(CSnakeDoc, CDocument)
END_MESSAGE_MAP()


// CSnakeDoc construction/destruction

CSnakeDoc::CSnakeDoc()
{

	// Цвета
	theme.bg.CreateSolidBrush(RGB(40, 160, 40));
	theme.score.CreateSolidBrush(RGB(120, 160, 40));
	theme.food.CreateSolidBrush(RGB(255, 80, 80));
	for (int i = 0; i < POISON_NUM; ++i)
		theme.poison[i].CreateSolidBrush(RGB(50, 50, 50));
	theme.snake.CreateSolidBrush(RGB(255, 200, 40));
	theme.snake_head.CreateSolidBrush(RGB(255, 200, 40));
	theme.m_bg = "DEFAULT";

	current = &theme;

	speed = 75;
	speed_current = &speed;
	
}


CSnakeDoc::~CSnakeDoc()
{
}

BOOL CSnakeDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CSnakeDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CSnakeDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSnakeDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSnakeDoc diagnostics

#ifdef _DEBUG
void CSnakeDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSnakeDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG
