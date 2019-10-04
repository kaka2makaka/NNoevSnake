
// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Snake.h"
#endif

#include "SnakeDoc.h"
#include "SnakeView.h"
#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_START, &CSnakeView::OnSTART)
END_MESSAGE_MAP()

// CSnakeView construction/destruction

CSnakeView::CSnakeView()
{
	m_score = 0;
	m_died = TRUE;
}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	
	// Фон
	m_bg.LoadBitmap(IDB_BG);

	// Спрайты
	m_food.Load(_T("..\\Snake\\res\\apple.png"));

	// Шрифты
	m_font.CreatePointFont(180, L"Century Gothic"); 
	m_info_font.CreatePointFont(220, L"Arial");

	m_count = 0;

	return CView::PreCreateWindow(cs);
}

// CSnakeView drawing

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CDC m_cacheDC;
	CBitmap m_cacheCBitmap;

	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheCBitmap.CreateCompatibleBitmap(pDC, 620 + 120, 775 + 50);
	
	CBitmap *pOldBit = m_cacheDC.SelectObject(&m_cacheCBitmap);

	// Прорисовка окна
	SetRect(window_rect, 0, 0, 620 + 120, 775 + 120);
	m_cacheDC.FillRect(window_rect, &pDoc->current->bg);

	// Прорисовка фона
	CDC m_bgcDC;
	m_bgcDC.CreateCompatibleDC(NULL);
	m_bgcDC.SelectObject(&m_bg);
	m_cacheDC.BitBlt(BORDER, BORDER, WIDTH + BORDER, HEIGHT + BORDER, &m_bgcDC, 0, 0, SRCCOPY);
	
	if (!m_died)
	{
		// Рисуем еду
		SetRect(food_rect, snake.food.x - 10, snake.food.y - 10,
			snake.food.x + 10, snake.food.y + 10);
		m_cacheDC.FillRect(food_rect, &pDoc->current->food);

		for (int i = 0; i < POISON_NUM; ++i)
		{
			SetRect(poison_rect[i], snake.poison[i].x - 10, snake.poison[i].y - 10,
				snake.poison[i].x + 10, snake.poison[i].y + 10);
			m_cacheDC.FillRect(poison_rect[i], &pDoc->current->poison[i]);
		}

		// Рисуем игрока
		for (vector<CPoint>::iterator iter = snake.snake_list.begin();
			iter != snake.snake_list.end(); ++iter)
		{
			SetRect(snake_rect, (*iter).x - 10, (*iter).y - 10,
				(*iter).x + 10, (*iter).y + 10);
			if (iter == snake.snake_list.begin())
				m_cacheDC.FillRect(snake_rect, &pDoc->current->snake_head);
			else
				m_cacheDC.FillRect(snake_rect, &pDoc->current->snake);
		}
	}
	else
	{
		// Когда старт/змейка умерла
		SetRect(info_rect,80,200,640,350);
		info.Format(_T("START NEW GAME"));
		m_cacheDC.SelectObject(m_info_font);
		m_cacheDC.SetBkMode(TRANSPARENT);
		m_cacheDC.SetTextColor(RGB(255, 255, 255));
		m_cacheDC.DrawText(info, -1, info_rect, DT_CENTER | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);
	}

	m_score = -3 + snake.snake_list.size();
	
	// Прорисовка информации об игроке
	SetRect(score_rect, BORDER*1.5, 0, WIDTH/4, BORDER);
	SetRect(m_food_rect, BORDER, 5, BORDER+40, 50);
	m_food.Draw(m_cacheDC, m_food_rect);
	
	// Делаем фон текста прозрачным
	m_cacheDC.SetBkMode(TRANSPARENT);

	// Очки
	score.Format(_T("%d"), m_score);
	m_cacheDC.SelectObject(m_font);
	m_cacheDC.SetTextColor(RGB(255, 255, 255));
	m_cacheDC.DrawText(score, -1, score_rect, DT_CENTER | DT_SINGLELINE | DT_NOPREFIX | DT_VCENTER | DT_END_ELLIPSIS);

	
	// Передаем кэш в окно
	pDC->BitBlt(0, 0, 620 + 120, 775 + 120, &m_cacheDC, 0, 0, SRCCOPY);

}


// CSnakeView printing

BOOL CSnakeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSnakeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSnakeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG


// CSnakeView message handlers


void CSnakeView::OnUp()
{
	if (snake.getDirection() == LEFT || snake.getDirection() == RIGHT)
		snake.changeDirection(UP);
}

void CSnakeView::OnDown()
{
	if (snake.getDirection() == LEFT || snake.getDirection() == RIGHT)
		snake.changeDirection(DOWN);
}

void CSnakeView::OnLeft()
{
	if (snake.getDirection() == UP || snake.getDirection() == DOWN)
		snake.changeDirection(LEFT);
}

void CSnakeView::OnRight()
{
	if (snake.getDirection() == UP || snake.getDirection() == DOWN)
		snake.changeDirection(RIGHT);
}


void CSnakeView::OnSTART()
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_died = FALSE;

	SetTimer(1, snake.speed, NULL);
	srand(time(NULL));
	snake.generateFood();
	snake.snake_list = snake.default_state;
}


// Обработка нажатий клавиш
void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case 'W':
	case VK_UP:
		OnUp();
		break;
	case 'S':
	case VK_DOWN:
		OnDown();
		break;
	case 'A':
	case VK_LEFT:
		OnLeft();
		break;
	case 'D':
	case VK_RIGHT:
		OnRight();
		break;
	}
}


// Игра окончена
void CSnakeView::OnTimer(UINT_PTR nIDEvent)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (snake.move() != TRUE) 
	{
		KillTimer(nIDEvent);
		m_died = TRUE;
	}
	Invalidate(FALSE);

	CView::OnTimer(nIDEvent);
}