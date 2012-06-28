
// regexTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "regexTest.h"
#include "regexTestDlg.h"
#include <regex>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CregexTestDlg dialog




CregexTestDlg::CregexTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CregexTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CregexTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_EDIT, m_ctlEditSource);
	DDX_Control(pDX, IDC_REGEX_EDIT1, m_editREGEX1);
	DDX_Control(pDX, IDC_REGEX_EDIT2, m_editREGEX2);
	DDX_Control(pDX, IDC_LIST_FN_NAMES, m_listResults);
}

BEGIN_MESSAGE_MAP(CregexTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_GET_ALL, &CregexTestDlg::OnBnClickedGetAll)
	ON_BN_CLICKED(IDC_BTN_GET_ALL2, &CregexTestDlg::OnBnClickedBtnGetAll2)
END_MESSAGE_MAP()


// CregexTestDlg message handlers

BOOL CregexTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	SetDefault();
// 	m_editREGEX.SetWindowText(_T("(ppOnEvent[A-Za-z]*[ )]*)"));
// 	m_ctlEditSource.SetWindowText(_T("ppOnEventABC()\r\n	{\r\n		test=0;\r\n	} \r\n	ppNotOnEventDontdothisone()\r\n	{\r\n		dosomestuff = 5;\r\n		}\r\n	ppOnEventThisOneToo()\r\n	{\r\n		hi=0;\r\n	}\r\n	ppOnEventAndThisone   ()\r\n	{\r\n		h=0;\r\n	}\r\n	"));


//	m_ctlEditSource.SetWindowText(_T("abc abdef c d e f g"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CregexTestDlg::SetDefault()
{
	m_editREGEX1.SetWindowText(_T("(ppOnEvent[A-Za-z]*[ )]*)"));
	m_editREGEX2.SetWindowText(_T("([ a-zA-Z0-9,])*)"));
	m_ctlEditSource.SetWindowText(_T("ppOnEventABC()\r\n	{\r\n		test=0;\r\n	} \r\n	ppNotOnEventDontdothisone()\r\n	{\r\n		dosomestuff = 5;\r\n		}\r\n	ppOnEventThisOneToo()\r\n	{\r\n		hi=0;\r\n	}\r\n	ppOnEventAndThisone   ()\r\n	{\r\n		h=0;\r\n	}\r\n	"));

}
void CregexTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CregexTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CregexTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CregexTestDlg::OnBnClickedButton1()
{


	std::tr1::smatch smTest;
	//std::tr1::cmatch cmTest;
	std::string testChars = "function ppOnEventOne(){asdsd;} function ppOnEventTwo(){ assdfafsf;}";
	std::tr1::regex regTest("\b( ppOnEvent[a-zA-Z]*[\\(){};]* function \b");	
	//std::tr1::regex regTest("(abc)");
	std::tr1::regex_search(testChars, smTest, regTest );
// 	std::tr1::regex_match(testChars, cmTest, regTest );

	int numTestRes = smTest.size();
	std::string strOneT = smTest[0];
	std::string strTwoT = smTest[1];


	std::tr1::cmatch res;
	std::string str = "<h2>Egg prices</h2>";
	std::tr1::regex rx("<h(.)>([^<]+)");
	std::tr1::regex_search(str.c_str(), res, rx);
//	std::cout << res[1] << ". " << res[2] << "\n";


	std::string strOne = res[1];
	std::string strTwo = res[2];


	int numRes = res.size();


	int a = 0;

}

// bool regex_search(_BidIt _First, _BidIt _Last,
// 				  match_results<_BidIt, _Alloc>& _Matches,
// 				  const basic_regex<_Elem, _RxTraits>& _Re,
// 				  regex_constants::match_flag_type _Flgs =
// 				  regex_constants::match_default)
// {	// search for regular expression match in target text
// 	return (_Regex_search(_First, _Last, &_Matches, _Re, _Flgs, _First));


void CregexTestDlg::OnBnClickedGetAll()
{
	std::tr1::smatch smTest;
	//std::tr1::cmatch cmTest;
 	//std::string testChars("abc abdef c d e f g");
	
//	std::tr1::regex regTest("(ab[a-z]* )");


	m_listResults.ResetContent();
	const std::tr1::sregex_iterator End;
	//Expression.assign("rel=\"nofollow\">(.*?)</a>");
	CString strSource,strRegex1,strRegex2, strRegexFull;
	m_ctlEditSource.GetWindowText(strSource);
	
	m_editREGEX1.GetWindowText(strRegex1);
	m_editREGEX2.GetWindowText(strRegex2);
	strRegexFull = strRegex1 + strRegex2;

	std::string testChars;
	CStringA strASource(strSource);

	testChars = strASource;


	std::tr1::regex regTest;//("(ab[a-z]* )");
	//std::string testChars;
	CStringA strARegex(strRegexFull);

	regTest = strARegex;


	for (std::tr1::sregex_iterator i(testChars.begin(), testChars.end(), regTest); i != End; ++i)
	{
		//	std::cout << (*i)[1] << std::endl; // first submatch, same as above.
		std::string strFound =  (*i)[1]; // first submatch, same as above.

		const char* szFound = strFound.c_str();

		CString csStrFound(szFound);
		CString csNum;
		csNum.Format(_T("%d"),csStrFound.GetLength());
		csStrFound += csNum;

		m_listResults.InsertString(-1,csStrFound);

	}


// 	for (std::tr1::sregex_iterator i(testChars.begin(), testChars.end(), regTest); i != End; ++i)
// 	{
// 	//	std::cout << (*i)[1] << std::endl; // first submatch, same as above.
// 		std::string strFound =  (*i)[1]; // first submatch, same as above.
// 
// 		
// 		int n = 0;
// 	}


// 	std::tr1::cmatch cmTest;
// 	const char *first = "abcd zxyaghe";
// 	const char *last = first + strlen(first);
// 	std::tr1::regex regTestABCD("(abc)|(zxy)");


// 	std::tr1::regex rx("c(a*)|(b)"); 
// 	std::tr1::cmatch mr; 

//	std::tr1::regex_search("xcaaabbby", mr, rx); 

//	std::string stringMatch = cmTest.str();
//	std::tr1::match_results<std::string::const_iterator> matcher;
//	std::tr1::match_results<std::string.const_iterator> iter;


// 	for (size_t n = 0; n < mr.size(); ++n) 
// 	{ 
// 		std::string str = mr[n];
// 		int nff = 994;
// 	} 
	
// 	std::tr1::regex_search(testChars, smTest, regTest,);

//	std::tr1::regex_search(testChars,smTest,regTest); 
	
// 	bool bResult = false;
// //	do
// 	{
// 
// 		//bResult = std::tr1::regex_search(testChars,smTest,regTest);
// 		bResult = std::tr1::regex_search(first, last, cmTest, regTestABCD);
// 		//int numTestRes = smTest.size();
// 		//smTest++;// 2 of 6
// 
// 	}	//while(bResult == true);

// 	std::string stringMatch = cmTest.str();
// 	cmTest.position(0);
// 	int n = cmTest.size();
// 	for (size_t n = 0; n < cmTest.size(); ++n) 
// 	{ 
// 		std::string str = cmTest[n];
// 		int a =0;
// 	}
	//std::string::const_iterator iter = smTest.begin();

//	std::tr1::regex_token_iterator()
	//(smTest.begin(), smTest.end(), testChars, smTest, regTest,);
// 	// 	std::tr1::regex_match(testChars, cmTest, regTest );
// 


//	std::string strZero = smTest.str(0);
//	std::string strOne = smTest.str(1);
// 	std::string strOne = *iter;
// 	iter++;
// 	std::string strTwo = *smTest;
	//int numTestRes = smTest.size();
//	const_iterator iter = smTest.begin();
	
//	std::string strTwo = *iter;

//	std::string strOneT = smTest[0];
//	std::string strTwoT = smTest[1];


//	int a = 0;
}
void CregexTestDlg::OnBnClickedBtnGetAll2()
{
	SetDefault();
}
