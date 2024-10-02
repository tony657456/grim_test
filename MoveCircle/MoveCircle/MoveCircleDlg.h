
// MoveCircleDlg.h: 헤더 파일
//

#pragma once
#include "CDlgImage.h"


// CMoveCircleDlg 대화 상자
class CMoveCircleDlg : public CDialogEx
{
// 생성입니다.
public:
	CMoveCircleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CDlgImage* m_pDlgImage;
	struct ParseInt {
		int x;
		int y;
	};

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOVECIRCLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_nStartX1;
	int m_nStartY1;
	int m_nStartX2;
	int m_nStartY2;
	int m_nRadius;
	int CDlgwidth;
	int CDlgheight;
//	afx_msg void OnDestroy();

	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	void callFunc(int n);
	void drawCircle(unsigned char* fm, int x, int y, int nRadius, int nGray);
	bool inInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	void drawX(CDC& dc, int centerX, int centerY);
	void DrawBackground();
	void updateDisplay();
	void InitBitmap();
	void clearDlg();
	CString subCircleText(CString fileName);
	ParseInt parseIntXY(CString fileName);
	afx_msg void OnBnClickedBtnClear();
};
