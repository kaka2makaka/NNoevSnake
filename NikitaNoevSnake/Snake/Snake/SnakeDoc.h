
// SnakeDoc.h : interface of the CSnakeDoc class
//


#pragma once
#include "CSnake.h"
#include <vector>

using namespace std;


class CSnakeDoc : public CDocument
{
protected: // create from serialization only
	CSnakeDoc();
	DECLARE_DYNCREATE(CSnakeDoc)

// Attributes
public:
	struct m_theme
	{
		CBrush bg;
		CBrush score;
		CBrush food;
		CBrush poison[POISON_NUM];
		CBrush snake;
		CBrush snake_head;
		CString m_bg;
	}; // theme structure
	m_theme theme;
	m_theme *current;
	// All the theme attributes
	UINT speed;
	UINT *speed_current;

// Overrides
public:
	virtual BOOL OnNewDocument();
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CSnakeDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
