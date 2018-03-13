// MainWndSettingsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TrafficMonitor.h"
#include "MainWndSettingsDlg.h"
#include "afxdialogex.h"


// CMainWndSettingsDlg �Ի���

IMPLEMENT_DYNAMIC(CMainWndSettingsDlg, CDialogEx)

CMainWndSettingsDlg::CMainWndSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MAIN_WND_SETTINGS_DIALOG, pParent)
{

}

CMainWndSettingsDlg::~CMainWndSettingsDlg()
{
}

void CMainWndSettingsDlg::DrawStaticColor()
{
	//CCommon::FillStaticColor(m_color_static, m_data.text_color);
	m_color_static.SetFillColor(m_data.text_color);
}

void CMainWndSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TEXT_COLOR_STATIC, m_color_static);
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HIDE_UNIT_CHECK, m_hide_unit_chk);
	DDX_Control(pDX, IDC_UNIT_COMBO, m_unit_combo);
}


BEGIN_MESSAGE_MAP(CMainWndSettingsDlg, CDialogEx)
	ON_EN_CHANGE(IDC_UPLOAD_EDIT, &CMainWndSettingsDlg::OnEnChangeUploadEdit)
	ON_EN_CHANGE(IDC_DOWNLOAD_EDIT, &CMainWndSettingsDlg::OnEnChangeDownloadEdit)
	ON_EN_CHANGE(IDC_CPU_EDIT, &CMainWndSettingsDlg::OnEnChangeCpuEdit)
	ON_EN_CHANGE(IDC_MEMORY_EDIT, &CMainWndSettingsDlg::OnEnChangeMemoryEdit)
	ON_BN_CLICKED(IDC_SET_COLOR_BUTTON1, &CMainWndSettingsDlg::OnBnClickedSetColorButton1)
	ON_BN_CLICKED(IDC_SET_DEFAULT_BUTTON, &CMainWndSettingsDlg::OnBnClickedSetDefaultButton)
	ON_BN_CLICKED(IDC_SET_FONT_BUTTON, &CMainWndSettingsDlg::OnBnClickedSetFontButton)
	ON_BN_CLICKED(IDC_SWITCH_UP_DOWN_CHECK, &CMainWndSettingsDlg::OnBnClickedSwitchUpDownCheck)
	ON_BN_CLICKED(IDC_FULLSCREEN_HIDE_CHECK, &CMainWndSettingsDlg::OnBnClickedFullscreenHideCheck)
	ON_BN_CLICKED(IDC_SPEED_SHORT_MODE_CHECK2, &CMainWndSettingsDlg::OnBnClickedSpeedShortModeCheck2)
	ON_CBN_SELCHANGE(IDC_UNIT_COMBO, &CMainWndSettingsDlg::OnCbnSelchangeUnitCombo)
	ON_BN_CLICKED(IDC_HIDE_UNIT_CHECK, &CMainWndSettingsDlg::OnBnClickedHideUnitCheck)
END_MESSAGE_MAP()


// CMainWndSettingsDlg ��Ϣ��������


BOOL CMainWndSettingsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	SetBackgroundColor(RGB(255, 255, 255));

	//��ʼ�����ؼ�״̬
	SetDlgItemText(IDC_FONT_NAME_EDIT, m_data.font_name);
	wchar_t buff[16];
	swprintf_s(buff, L"%d", m_data.font_size);
	SetDlgItemText(IDC_FONT_SIZE_EDIT, buff);

	SetDlgItemText(IDC_UPLOAD_EDIT, m_data.up_string.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT, m_data.down_string.c_str());
	SetDlgItemText(IDC_CPU_EDIT, m_data.cpu_string.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT, m_data.memory_string.c_str());

	((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->SetCheck(m_data.swap_up_down);
	((CButton*)GetDlgItem(IDC_FULLSCREEN_HIDE_CHECK))->SetCheck(m_data.hide_main_wnd_when_fullscreen);
	((CButton*)GetDlgItem(IDC_SPEED_SHORT_MODE_CHECK2))->SetCheck(m_data.speed_short_mode);

	//SetTimer(11, 50, NULL);
	DrawStaticColor();

	m_toolTip.Create(this);
	m_toolTip.SetMaxTipWidth(theApp.DPI(300));
	m_toolTip.AddTool(GetDlgItem(IDC_SPEED_SHORT_MODE_CHECK2), _T("��ѡ�󣬽�����������ʾ��С����λ�������ҵ�λ����ʾ��B��"));

	m_unit_combo.AddString(_T("�Զ�"));
	m_unit_combo.AddString(_T("�̶�Ϊ KB/s"));
	m_unit_combo.AddString(_T("�̶�Ϊ MB/s"));
	m_unit_combo.SetCurSel(static_cast<int>(m_data.m_speed_unit));

	m_hide_unit_chk.SetCheck(m_data.m_hide_unit);
	if (m_data.m_speed_unit == SpeedUnit::AUTO)
	{
		m_hide_unit_chk.SetCheck(FALSE);
		m_data.m_hide_unit = false;
		m_hide_unit_chk.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMainWndSettingsDlg::OnEnChangeUploadEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_UPLOAD_EDIT, tmp);
	m_data.up_string = tmp;
}


void CMainWndSettingsDlg::OnEnChangeDownloadEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_DOWNLOAD_EDIT, tmp);
	m_data.down_string = tmp;
}


void CMainWndSettingsDlg::OnEnChangeCpuEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_CPU_EDIT, tmp);
	m_data.cpu_string = tmp;
}


void CMainWndSettingsDlg::OnEnChangeMemoryEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ����ӿؼ�֪ͨ�����������
	CString tmp;
	GetDlgItemText(IDC_MEMORY_EDIT, tmp);
	m_data.memory_string = tmp;
}


void CMainWndSettingsDlg::OnBnClickedSetColorButton1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CColorDialog colorDlg(m_data.text_color, 0, this);
	if (colorDlg.DoModal() == IDOK)
	{
		m_data.text_color = colorDlg.GetColor();
		DrawStaticColor();
	}
}


void CMainWndSettingsDlg::OnBnClickedSetDefaultButton()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.up_string = L"�ϴ�: ";
	m_data.down_string = L"����: ";
	m_data.cpu_string = L"CPU: ";
	m_data.memory_string = L"�ڴ�: ";
	SetDlgItemText(IDC_UPLOAD_EDIT, m_data.up_string.c_str());
	SetDlgItemText(IDC_DOWNLOAD_EDIT, m_data.down_string.c_str());
	SetDlgItemText(IDC_CPU_EDIT, m_data.cpu_string.c_str());
	SetDlgItemText(IDC_MEMORY_EDIT, m_data.memory_string.c_str());
}


void CMainWndSettingsDlg::OnBnClickedSetFontButton()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	CFont font;
	font.CreatePointFont(m_data.font_size * 10, m_data.font_name);
	LOGFONT lf{};             //LOGFONT����
	font.GetLogFont(&lf);
	CFontDialog fontDlg(&lf);	//��������Ի��򣬳�ʼѡ������Ϊ֮ǰ����
	if (IDOK == fontDlg.DoModal())     // ��ʾ����Ի���
	{
		//��ȡ������Ϣ
		m_data.font_name = fontDlg.GetFaceName();
		m_data.font_size = fontDlg.GetSize() / 10;
		//��������Ϣ��ʾ����
		SetDlgItemText(IDC_FONT_NAME_EDIT, m_data.font_name);
		wchar_t buff[16];
		swprintf_s(buff, L"%d", m_data.font_size);
		SetDlgItemText(IDC_FONT_SIZE_EDIT, buff);
	}
}


void CMainWndSettingsDlg::OnBnClickedSwitchUpDownCheck()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.swap_up_down = (((CButton*)GetDlgItem(IDC_SWITCH_UP_DOWN_CHECK))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnBnClickedFullscreenHideCheck()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.hide_main_wnd_when_fullscreen = (((CButton*)GetDlgItem(IDC_FULLSCREEN_HIDE_CHECK))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnBnClickedSpeedShortModeCheck2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.speed_short_mode = (((CButton*)GetDlgItem(IDC_SPEED_SHORT_MODE_CHECK2))->GetCheck() != 0);
}


void CMainWndSettingsDlg::OnCbnSelchangeUnitCombo()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.m_speed_unit = static_cast<SpeedUnit>(m_unit_combo.GetCurSel());
	if (m_data.m_speed_unit == SpeedUnit::AUTO)
	{
		m_hide_unit_chk.SetCheck(FALSE);
		m_data.m_hide_unit = false;
		m_hide_unit_chk.EnableWindow(FALSE);
	}
	else
	{
		m_hide_unit_chk.EnableWindow(TRUE);
	}
}


void CMainWndSettingsDlg::OnBnClickedHideUnitCheck()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	m_data.m_hide_unit = (m_hide_unit_chk.GetCheck() != 0);
}


BOOL CMainWndSettingsDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ�����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
		m_toolTip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}