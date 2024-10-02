
// MoveCircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MoveCircle.h"
#include "MoveCircleDlg.h"
#include "afxdialogex.h"
#include <iostream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_DESTROY()
ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMoveCircleDlg 대화 상자



CMoveCircleDlg::CMoveCircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOVECIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CMoveCircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nStartX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nStartY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nStartX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nStartY2);

}

BEGIN_MESSAGE_MAP(CMoveCircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMoveCircleDlg::OnBnClickedBtnDraw)
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMoveCircleDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMoveCircleDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CMoveCircleDlg::OnBnClickedBtnClear)
END_MESSAGE_MAP()


// CMoveCircleDlg 메시지 처리기

BOOL CMoveCircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CDlgwidth = 670;
	CDlgheight = 480;
	srand((unsigned int)time(NULL));
	// 높이가 너비보다 작으니까 높이의 나누기 2값을 
	// 넘어가지 않는 선에서 반지름 생성
	// m_nRadius = rand() % (CDlgheight / 2);
	MoveWindow(0, 0, 680, 680);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, CDlgwidth, CDlgheight);
	CWnd* pGroupBox = GetDlgItem(IDC_GROUP_BOX);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMoveCircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMoveCircleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMoveCircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMoveCircleDlg::callFunc(int n) {
	cout << n << endl;
}


void CMoveCircleDlg::OnBnClickedBtnDraw()
{
	// 10부터 100까지
	m_nRadius = rand() % 110 + 10;
	UpdateData(TRUE);
	InitBitmap();
	DrawBackground();
	UpdateData(FALSE);
}

CString g_strFileImage;
void CMoveCircleDlg::DrawBackground() {
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	m_pDlgImage->Invalidate();
	drawCircle(fm, m_nStartX1, m_nStartY1, m_nRadius, 0xff);
	g_strFileImage.Format(_T("images\\Circle_%d_%d.jpg"), m_nStartX1, m_nStartY1);
	m_pDlgImage->m_Image.Save(g_strFileImage);
}

void CMoveCircleDlg::drawCircle(unsigned char* fm, int x, int y, int nRadius, int white) {
	// 문제 요구사항이 x+radius가 아니라 x 자체를 중심으로 사용해야함
	int nCenterX = x;
	int nCenterY = y;
	if (nCenterX - nRadius < 0) {
		m_nStartX1 = nRadius;  // 왼쪽 경계를 벗어나면 중심을 오른쪽으로 이동
	}
	if (nCenterY - nRadius < 0) {
		m_nStartY1 = nRadius;  // 위쪽 경계를 벗어나면 중심을 아래로 이동
	}
	if (nCenterX + nRadius > CDlgwidth) {
		m_nStartX1 = CDlgwidth - 10 - nRadius; // 오른쪽 경계를 벗어나지 않게
	}
	if (nCenterY + nRadius > CDlgheight) {
		m_nStartY1 = CDlgheight - 10 - nRadius; // 아래쪽 경계를 벗어나지 않게
	}

	int nPitch = m_pDlgImage->m_Image.GetPitch();
	cout << "랜덤 반지름 크기: " << m_nRadius << endl;

	for (int j = m_nStartY1 - nRadius; j < m_nStartY1 + nRadius; j++) {
		for (int i = m_nStartX1 - nRadius; i < m_nStartX1 + nRadius; i++) {
			if (inInCircle(i, j, m_nStartX1, m_nStartY1, nRadius)) {
				fm[j * nPitch + i] = white;
			}
		}
	}
}

void CMoveCircleDlg::drawX(CDC& dc, int nCenterX, int nCenterY) {
	cout << nCenterX << nCenterX << endl;
	// 이미지의 비트맵 데이터에 접근
	HDC hdc = m_pDlgImage->m_Image.GetDC();  // 이미지의 HDC 가져오기
	CDC* pDC = CDC::FromHandle(hdc);  // HDC를 CDC로 변환

	CPen pen(PS_SOLID, 2, RGB(255, 0, 0));  // X 표시 색상 (빨간색)
	pDC->SelectObject(&pen);

	// X 표시 그리기
	pDC->MoveTo(nCenterX - 5, nCenterY - 5);  // 왼쪽 위에서 오른쪽 아래로 대각선
	pDC->LineTo(nCenterX + 5, nCenterY + 5);

	pDC->MoveTo(nCenterX - 5, nCenterY + 5);  // 왼쪽 아래에서 오른쪽 위로 대각선
	pDC->LineTo(nCenterX + 5, nCenterY - 5);

	CString strCoords;
	strCoords.Format(_T("(%d, %d)"), nCenterX, nCenterY);  // 좌표 텍스트 생성

	pDC->SetTextColor(RGB(0, 0, 255));  // 텍스트 색상 (파란색)
	pDC->TextOutW(nCenterX + 10, nCenterY + 10, strCoords);  // 좌표 텍스트 표시 (X 옆)

	m_pDlgImage->m_Image.ReleaseDC();  // HDC 해제
}

bool CMoveCircleDlg::inInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius) {
	bool bRet = false;

	// 원래는 정사각형이 그려져야하는데 피타고라스 정리로
	// 원을 만듬
	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

void CMoveCircleDlg::OnBnClickedBtnAction()
{
	UpdateData(TRUE);
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	bool isMoving = true;
	drawCircle(fm, m_nStartX1, m_nStartY1, m_nRadius, 0);

	if (isMoving) {
		if (m_nStartX1 < m_nStartX2) {
			m_nStartX1++;
		}
		else if(m_nStartX1 > m_nStartX2){
			m_nStartX1--;
		}

		if (m_nStartY1 < m_nStartY2) {
			m_nStartY1++;
		}
		else if (m_nStartY1 > m_nStartY2) {
			m_nStartY1--;
		}
	}

	isMoving = m_nStartX1 == m_nStartX2 && m_nStartY1 == m_nStartY2 ? isMoving == false : isMoving;
	m_pDlgImage->Invalidate();
	drawCircle(fm, m_nStartX1, m_nStartY1, m_nRadius, 0xff);

	// 어차피 덮어써지니까 같은 이름 비교 필요x
	CString filename;
	filename.Format(_T("images\\Circle_%d_%d.jpg"), m_nStartX1, m_nStartY1);
	m_pDlgImage->m_Image.Save(filename);
	
	UpdateData(FALSE);
}


void CMoveCircleDlg::OnBnClickedBtnOpen()
{
	AfxMessageBox(_T("이미지 오픈 후 CLEAR 버튼을 눌러주세요."));
	CFileDialog dlg(TRUE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Image Files (*.bmp; *.jpg; *.png)|*.bmp;*.jpg;*.png||"), this);

	if (m_pDlgImage->m_Image != NULL) {
		m_pDlgImage->m_Image.Destroy();
	}

	if (dlg.DoModal() == IDOK) {
		g_strFileImage = dlg.GetPathName();
		CString fileName = dlg.GetFileTitle();
		CString subTextFileName = subCircleText(fileName);
		ParseInt result = parseIntXY(subTextFileName);
		CClientDC dc(this);
		m_pDlgImage-> m_Image.Load(g_strFileImage);
		drawX(dc, result.x, result.y);
		updateDisplay();
	}
}

// 탐색기를 통해 가져온 이미지 다이얼로그에 보이게
void CMoveCircleDlg::updateDisplay() {
	CClientDC dc(this);
	m_pDlgImage->m_Image.Draw(dc, 0, 0);
}

CString CMoveCircleDlg::subCircleText(CString fileName) {
	CString prefix = _T("Circle_");
	if (fileName.Find(prefix) == 0) {
		CString modifyFileName = fileName.Right(fileName.GetLength() - prefix.GetLength());
		return modifyFileName;
	}
}

CMoveCircleDlg::ParseInt CMoveCircleDlg::parseIntXY(CString fileName) {
	ParseInt resultXY;
	int underscore = fileName.Find('_');

	resultXY.x = _ttoi(fileName.Left(underscore));
	// underscore의 위치 index 1, 전체길이 4 - 1하면 3인데 _이후부터니까 -1 한번 더
	resultXY.y = _ttoi(fileName.Right(fileName.GetLength() - underscore - 1));
	return resultXY;
}

void CMoveCircleDlg::InitBitmap() {
	m_pDlgImage->m_Image.Destroy();
	m_pDlgImage->InitImage();
}

void CMoveCircleDlg::clearDlg() {
	UpdateData(TRUE);
	m_nStartX1 = 0;
	m_nStartY1 = 0;
	m_nStartX2 = 0;
	m_nStartY2 = 0;
	InitBitmap();
	updateDisplay();
	UpdateData(FALSE);
}


void CMoveCircleDlg::OnBnClickedBtnClear()
{
	clearDlg();
}
