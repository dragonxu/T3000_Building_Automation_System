// AirQuality.cpp : implementation file
//

#include "stdafx.h"
#include "../T3000.h"
#include "AirQuality.h"
#include "../globle_function.h"
#include "../MainFrm.h"
static BOOL ifAQdb = TRUE;
static BOOL writedb = TRUE;

CString Str_Display[4]={_T("Scroll"),_T("Temperature"),_T("Humidity"),_T("AirQuanlity")};

#define  WM_AIRQUANITY_FRESH WM_USER + 98562
// CAirQuality
UINT CAirQuality_BackMainUIFresh(LPVOID pParam)
{
	CAirQuality* pdlg = (CAirQuality*)pParam;
	while(1)
	{
		Sleep(2000);
		if(pdlg->IsWindowVisible())
		{	 
			if (is_connect())
			{
				if (pdlg->m_fresh_data)
				{
					if (!pdlg->m_fresh_data)
					{
					    TRACE(_T(">>>>Fresh = 0\n"));
						continue;
					}
					TRACE(_T(">>>>Fresh = 1\n"));
					Read_Multi(g_tstat_id,&product_register_value[pdlg->MODBUS_TEMPRATURE_CHIP_F],pdlg->MODBUS_TEMPRATURE_CHIP_F,4,5);
					if (!pdlg->m_fresh_data)
					{
						continue;
					}
					Read_Multi(g_tstat_id,&product_register_value[pdlg->MODBUS_OUTPUT_RANGE],pdlg->MODBUS_OUTPUT_RANGE,4,5);
					if (!pdlg->m_fresh_data)
					{
						continue;
					}
					Read_Multi(g_tstat_id,&product_register_value[pdlg->MODBUS_TEMP_CURRENT_OUTPUT],pdlg->MODBUS_TEMP_CURRENT_OUTPUT,6,5);
					if (!pdlg->m_fresh_data)
					{
						continue;
					}
					::SendMessage(pdlg->m_hWnd,WM_AIRQUANITY_FRESH,0,0);

				}

			}
		}
	}
	return 0;
}
IMPLEMENT_DYNCREATE(CAirQuality, CFormView)

CAirQuality::CAirQuality()
	: CFormView(CAirQuality::IDD)
	 
{
	
	m_pFreshBackground=NULL;
	m_fresh_data=TRUE;


}

CAirQuality::~CAirQuality()
{
	 
}

void CAirQuality::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_edit_address);
	DDX_Control(pDX, IDC_EDIT_SN, m_edit_sn);
	DDX_Control(pDX, IDC_EDIT_AQ, m_edit_AQ);
	DDX_Control(pDX, IDC_EDIT_AR_FILTER, m_edit_aq_filter);
	DDX_Control(pDX, IDC_EDIT_BAUDRATE, m_edit_baudrate);
	DDX_Control(pDX, IDC_EDIT_FV, m_edit_fv);
	DDX_Control(pDX, IDC_EDIT_HUM, m_edit_hum);
	DDX_Control(pDX, IDC_EDIT_HUM_FILTER, m_edit_hum_filter);
	DDX_Control(pDX, IDC_EDIT_HV, m_edit_hv);
	DDX_Control(pDX, IDC_EDIT_TEMP_FILTER, m_edit_temp_filter);
	DDX_Control(pDX, IDC_EDIT_TEMPERATURE, m_edit_temperature);
	DDX_Control(pDX, IDC_EDIT_AQ_HIGH, m_edit_aq_high);
	DDX_Control(pDX, IDC_EDIT_AQ_LOW, m_edit_aq_low);
	DDX_Control(pDX, IDC_EDIT_AQ_OUTPUT, m_edit_aq_output);
	//  DDX_Control(pDX, IDC_EDIT_HUM_HIGH, m_edit_hum_low);
	DDX_Control(pDX, IDC_EDIT_HUM_HIGH, m_edit_hum_high);
	DDX_Control(pDX, IDC_EDIT_HUM_LOW, m_edit_hum_low);
	DDX_Control(pDX, IDC_EDIT_HUM_OUTPUT, m_edit_hum_output);
	DDX_Control(pDX, IDC_EDIT_OUTPUT_RANGE, m_edit_output_range);
	DDX_Control(pDX, IDC_EDIT_TEMP_HIGH, m_edit_temp_high);
	DDX_Control(pDX, IDC_EDIT_TEMP_LOW, m_edit_temp_low);
	DDX_Control(pDX, IDC_EDIT_TEMP_OUTPUT, m_edit_temp_output);
	DDX_Control(pDX, IDC_COMBO_UNITS, m_combox_units);
	DDX_Control(pDX, IDC_EDIT_MODEL, m_edit_model);
	DDX_Control(pDX, IDC_MSFLEXGRID1, m_sensor_calibrate_table);
	DDX_Control(pDX, IDC_COMBO_DISPLAY, m_combox_displayer);
	DDX_Control(pDX, IDC_EDIT_BACKLIGHT_TIME, m_edit_backlightTime);
}

BEGIN_MESSAGE_MAP(CAirQuality, CFormView)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMP_FILTER, &CAirQuality::OnEnKillfocustempfilter)
	ON_EN_KILLFOCUS(IDC_EDIT_BACKLIGHT_TIME, &CAirQuality::OnEnKillfocusBackLightTime)

	ON_EN_KILLFOCUS(IDC_EDIT_HUM_FILTER, &CAirQuality::OnEnKillfocushumfilter)
	ON_EN_KILLFOCUS(IDC_EDIT_AR_FILTER, &CAirQuality::OnEnKillfocusAQfilter)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPERATURE, &CAirQuality::OnEnKillfocustemp)
	ON_EN_KILLFOCUS(IDC_EDIT_HUM, &CAirQuality::OnEnKillfocushum)
	ON_EN_KILLFOCUS(IDC_EDIT_AQ, &CAirQuality::OnEnKillfocusAQ)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMP_LOW, &CAirQuality::OnEnKillfocustemplow)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMP_HIGH, &CAirQuality::OnEnKillfocustemphigh)
	ON_EN_KILLFOCUS(IDC_EDIT_HUM_LOW, &CAirQuality::OnEnKillfocushumlow)
	ON_EN_KILLFOCUS(IDC_EDIT_HUM_HIGH, &CAirQuality::OnEnKillfocushumhigh)
	ON_EN_KILLFOCUS(IDC_EDIT_AQ_LOW, &CAirQuality::OnEnKillfocusaqlow)
	ON_EN_KILLFOCUS(IDC_EDIT_AQ_HIGH, &CAirQuality::OnEnKillfocusaqhigh)
	ON_CBN_SELCHANGE(IDC_COMBO_UNITS, &CAirQuality::OnCbnCFUnits)

	ON_BN_CLICKED(IDC_CHANGE_ID, &CAirQuality::OnBnClickedButton_Change_ID)
	ON_EN_SETFOCUS(IDC_EDIT_TEMP_FILTER,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_TEMPERATURE,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_HUM_FILTER,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_HUM,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_AR_FILTER,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_AQ,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_TEMP_LOW,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_TEMP_HIGH,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_HUM_LOW,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_HUM_HIGH,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_AQ_LOW,&CAirQuality::OnSetFocusStopFresh)
	ON_EN_SETFOCUS(IDC_EDIT_AQ_HIGH,&CAirQuality::OnSetFocusStopFresh)
 
	ON_CBN_SELCHANGE(IDC_COMBO_DISPLAY, &CAirQuality::OnCbnSelchangeComboDisplay)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CAirQuality diagnostics

#ifdef _DEBUG
void CAirQuality::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAirQuality::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}


#endif
#endif //_DEBUG
// CAirQuality message handlers
void CAirQuality::Fresh()
{
g_NEED_MULTI_READ = FALSE;
	Initial_RegisterList();
	ShowAirqualityDialog();
	ShowInput();
	ShowOutput();
	ShowCalibrationPointTable();
	if (m_pFreshBackground==NULL)
	{
		m_pFreshBackground = AfxBeginThread(CAirQuality_BackMainUIFresh,this);
	}
}
void CAirQuality::OnSetFocusStopFresh(){
TRACE(_T(">>>>Set Focus Fresh = 0\n"));
m_fresh_data=false;
}

void CAirQuality::OnCbnSelchangeComboDisplay(){
	int sel=m_combox_displayer.GetCurSel();
	 

	if (product_register_value[MODBUS_SCROLL_MODE]==sel)
	{
	  return;
	}
	int ret=write_one(g_tstat_id,MODBUS_SCROLL_MODE,sel);
	if (ret>0)
	{
	 product_register_value[MODBUS_SCROLL_MODE]=sel;
	}
	else
	{
	AfxMessageBox(_T("Write Fail"));
	}

	m_combox_displayer.SetCurSel(product_register_value[MODBUS_SCROLL_MODE]);
}
void CAirQuality::Fresh_Window(){
	//ShowAirqualityDialog();
	//ShowInput();
	//ShowOutput();
	//ShowCalibrationPointTable();
	if (!m_fresh_data)
	{
		return;
	}
	CString strTemp;
	if (product_register_value[MODBUS_DEGC_OR_F]==0)
	{
		strTemp.Format(_T("%0.1f"),((float)((short)product_register_value[MODBUS_TEMPRATURE_CHIP]))/10.0);
		
	} 
	else
	{
		strTemp.Format(_T("%0.1f"),((float)((short)product_register_value[MODBUS_TEMPRATURE_CHIP_F]))/10.0);
		
	}
	m_edit_temperature.SetWindowTextW(strTemp);
	strTemp.Format(_T("%0.1f"),(float)(short)product_register_value[MODBUS_HUM]/10.0);
	m_edit_hum.SetWindowTextW(strTemp);


	if (product_register_value[7]!=PM_HUM_R)
	{
		strTemp.Format(_T("%d"),product_register_value[MODBUS_AQ]);
		m_edit_AQ.SetWindowTextW(strTemp);
	}

	int output_range=product_register_value[MODBUS_OUTPUT_RANGE];
	if (output_range==1){
		strTemp=_T("0-10v");
	}
	else if (output_range==2)
	{
		strTemp=_T("0-5v");
	}
	else if (output_range==3)
	{
		strTemp=_T("4-20mA");
	}
	else
	{
		strTemp=_T("");
	}
	m_edit_output_range.SetWindowTextW(strTemp);
	if (output_range==1||output_range==2)
	{
		strTemp.Format(_T("%0.2f V"),(float)(short)product_register_value[MODBUS_TEMP_VOLTAGE_OUTPUT]/100.0);
		m_edit_temp_output.SetWindowTextW(strTemp);
		strTemp.Format(_T("%0.2f V"),(float)(short)product_register_value[MODBUS_HUM_VOLTAGE_OUTPUT]/100.0);
		m_edit_hum_output.SetWindowTextW(strTemp);
		if (product_register_value[7]!=PM_HUM_R)
		{strTemp.Format(_T("%0.2f V"),(float)(short)product_register_value[MODBUS_AQ_VOLTAGE_OUTPUT]/100.0);
		m_edit_aq_output.SetWindowTextW(strTemp);}
		
	} 
	else
	{
		strTemp.Format(_T("%0.1f mA"),(float)(short)product_register_value[MODBUS_TEMP_CURRENT_OUTPUT]/10.0);
		m_edit_temp_output.SetWindowTextW(strTemp);
		strTemp.Format(_T("%0.1f mA"),(float)(short)product_register_value[MODBUS_HUM_CURRENT_OUTPUT]/10.0);
		m_edit_hum_output.SetWindowTextW(strTemp);
		if (product_register_value[7]!=PM_HUM_R)
		{
			strTemp.Format(_T("%0.1f mA"),(float)(short)product_register_value[MODBUS_AQ_CURRENT_OUTPUT]/10.0);
			m_edit_aq_output.SetWindowTextW(strTemp);
		}
		
	}



	 

}
void CAirQuality::OnDestroy()
{
	
	if (m_pFreshBackground!=NULL)
	{
		if (WaitForSingleObject(m_pFreshBackground->m_hThread, 1000) != WAIT_OBJECT_0)

			//Sleep(500);//wait for the end of the thread.
			if (m_pFreshBackground!=NULL) 

			{
				if (WaitForSingleObject(m_pFreshBackground->m_hThread, 3000) == WAIT_OBJECT_0)
				{

				}
				else
				{		
					BOOL bRet = TerminateThread(m_pFreshBackground->m_hThread,0);

					m_pFreshBackground=NULL;
				}

			}
	}
	CFormView::OnDestroy();
	// TODO: Add your message handler code here
}
void CAirQuality::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	 m_combox_units.ResetContent();
	 m_combox_units.AddString(_T("C"));
	 m_combox_units.AddString(_T("F"));

	 m_sensor_calibrate_table.put_Cols(3);
	 m_sensor_calibrate_table.put_Rows(11);
	 CString index;
	 for (int i=1;i<11;i++)
	 {
	 index.Format(_T("%d"),i);
	 m_sensor_calibrate_table.put_TextMatrix(i,0,index);
	 }
	 m_sensor_calibrate_table.put_TextMatrix(0,1,_T("Freqency"));
	 m_sensor_calibrate_table.put_TextMatrix(0,2,_T("Humidity(%)"));
}
void CAirQuality::ShowAirqualityDialog()
{
	CString strTemp;
	strTemp.Format(_T("%d"),product_register_value[MODBUS_ADDRESS]);
	m_edit_address.SetWindowTextW(strTemp);
	int SN=product_register_value[MODBUS_SERIALNUMBER_HIWORD+1]*256*256*256+product_register_value[MODBUS_SERIALNUMBER_HIWORD]*256*256+product_register_value[MODBUS_SERIALNUMBER_LOWORD+1]*256+product_register_value[MODBUS_SERIALNUMBER_LOWORD];
	strTemp.Format(_T("%d"),SN);
	m_edit_sn.SetWindowTextW(strTemp);
	strTemp=GetProductName(product_register_value[7]);
	m_edit_model.SetWindowTextW(strTemp);
	float fv=(float)(product_register_value[MODBUS_VERSION_NUMBER_HI]*256+product_register_value[MODBUS_VERSION_NUMBER_LO])/10.0;	
	strTemp.Format(_T("%0.1f"),fv);
	m_edit_fv.SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),product_register_value[MODBUS_HARDWARE_REV]);
	m_edit_hv.SetWindowTextW(strTemp);
	if (product_register_value[MODBUS_BAUDRATE]==0)
	{
		strTemp=_T("9600");

	} 
	else
	{
		strTemp=_T("19200");
	}
	m_edit_baudrate.SetWindowTextW(strTemp);


	m_combox_displayer.ResetContent();
	if (product_register_value[7]==PM_HUM_R)
	{
	     for (int i=0;i<3;i++)
	     {
		   m_combox_displayer.AddString(Str_Display[i]);
	     }
	} 
	else
	{
		for (int i=0;i<4;i++)
		{
			m_combox_displayer.AddString(Str_Display[i]);
		} 
	}

	if (product_register_value[MODBUS_SCROLL_MODE]>=0&&product_register_value[MODBUS_SCROLL_MODE]<4)
	{
	m_combox_displayer.SetCurSel(product_register_value[MODBUS_SCROLL_MODE]);
	}
	else{
	m_combox_displayer.SetCurSel(0);
	}

}
void CAirQuality::ShowCalibrationPointTable(){
CString strTemp;
for (int row=1;row<=7;row++)
{
	strTemp.Format(_T("%d"), (short)product_register_value[MODBUS_HUMCOUNT1_H+2*(row-1)]);
	m_sensor_calibrate_table.put_TextMatrix(row,1,strTemp);
	strTemp.Format(_T("%d"), (short)product_register_value[MODBUS_HUMCOUNT1_H+2*row-1]);
	m_sensor_calibrate_table.put_TextMatrix(row,2,strTemp);
}
}
void CAirQuality::ShowInput(){

	CString strTemp;
	strTemp.Format(_T("%d"),product_register_value[MODBUS_OVERRIDE_TIMER_LEFT]);
	m_edit_temp_filter.SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),product_register_value[MODBUS_HUM_FILTER]);
	m_edit_hum_filter.SetWindowTextW(strTemp);
	if (product_register_value[MODBUS_DEGC_OR_F]==0)
	{
		strTemp.Format(_T("%0.1f"),((float)((short)product_register_value[MODBUS_TEMPRATURE_CHIP]))/10.0);
		m_combox_units.SetCurSel(0);
	} 
	else
	{
		strTemp.Format(_T("%0.1f"),((float)((short)product_register_value[MODBUS_TEMPRATURE_CHIP_F]))/10.0);
		m_combox_units.SetCurSel(1);
	}
	m_edit_temperature.SetWindowTextW(strTemp);
	strTemp.Format(_T("%0.1f"),(float)(short)product_register_value[MODBUS_HUM]/10.0);
	m_edit_hum.SetWindowTextW(strTemp);

	if (product_register_value[361]==0)
	{
		//strTemp.Format(_T("%d"),(short)product_register_value[361]);
		strTemp=_T("OFF");
		 
	}
	else if (product_register_value[361]==255)
	{
		strTemp=_T("ON");
		 
	}
	else if(product_register_value[361]>0&&product_register_value[361]<255)
	{
	strTemp.Format(_T("%d"),(short)product_register_value[361]);
	}
	
	m_edit_backlightTime.SetWindowTextW(strTemp);
if (product_register_value[7]==PM_HUM_R)
{
GetDlgItem(IDC_STATIC_AQ_FILTER)->ShowWindow(FALSE);
GetDlgItem(IDC_EDIT_AR_FILTER)->ShowWindow(FALSE);
GetDlgItem(IDC_STATIC_AQ)->ShowWindow(FALSE);
GetDlgItem(IDC_EDIT_AQ)->ShowWindow(FALSE);


} 
else
{
GetDlgItem(IDC_STATIC_AQ_FILTER)->ShowWindow(TRUE);
GetDlgItem(IDC_EDIT_AR_FILTER)->ShowWindow(TRUE);
GetDlgItem(IDC_STATIC_AQ)->ShowWindow(TRUE);
GetDlgItem(IDC_EDIT_AQ)->ShowWindow(TRUE);
strTemp.Format(_T("%d"),product_register_value[MODBUS_AQ_FILTER]);
m_edit_aq_filter.SetWindowTextW(strTemp);
strTemp.Format(_T("%d"),product_register_value[MODBUS_AQ]);
m_edit_AQ.SetWindowTextW(strTemp);
}


}
void CAirQuality::ShowOutput(){
	CString strTemp;
	strTemp.Format(_T("%0.1f"),(float)(short)product_register_value[MODBUS_TEM_RANGE_LOWER]/10.0);
	m_edit_temp_low.SetWindowTextW(strTemp);
	strTemp.Format(_T("%0.1f"),(float)(short)product_register_value[MODBUS_TEM_RANGE_UPPER]/10.0);
	m_edit_temp_high.SetWindowTextW(strTemp);
	strTemp.Format(_T("%0.1f"),(float)(short)product_register_value[MODBUS_HUM_RANGE_LOWER]/10.0);
	m_edit_hum_low.SetWindowTextW(strTemp);
	strTemp.Format(_T("%0.1f"),(float)(short)product_register_value[MODBUS_HUM_RANGE_UPPER]/10.0);
	m_edit_hum_high.SetWindowTextW(strTemp);

	int output_range=product_register_value[MODBUS_OUTPUT_RANGE];
	if (output_range==1){
	strTemp=_T("0-10v");
	}
    else if (output_range==2)
    {
	strTemp=_T("0-5v");
    }
	else if (output_range==3)
	{
	strTemp=_T("4-20mA");
	}
	else
	{
	strTemp=_T("");
	}
	m_edit_output_range.SetWindowTextW(strTemp);
	if (output_range==1||output_range==2)
	{
		strTemp.Format(_T("%0.2f V"),(float)(short)product_register_value[MODBUS_TEMP_VOLTAGE_OUTPUT]/100.0);
		m_edit_temp_output.SetWindowTextW(strTemp);
		strTemp.Format(_T("%0.2f V"),(float)(short)product_register_value[MODBUS_HUM_VOLTAGE_OUTPUT]/100.0);
		m_edit_hum_output.SetWindowTextW(strTemp);

	} 
	else
	{
		strTemp.Format(_T("%0.1f mA"),(float)(short)product_register_value[MODBUS_TEMP_CURRENT_OUTPUT]/10.0);
		m_edit_temp_output.SetWindowTextW(strTemp);
		strTemp.Format(_T("%0.1f mA"),(float)(short)product_register_value[MODBUS_HUM_CURRENT_OUTPUT]/10.0);
		m_edit_hum_output.SetWindowTextW(strTemp);
		
	}

	if (product_register_value[7]==PM_HUM_R)
	{
		GetDlgItem(IDC_STATIC_GROUP_AQ_OUTPUT)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AQ_LOW)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_AQ_LOW)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AQ_HIGH)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_AQ_HIGH)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_AQ_OUTPUT)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_AQ_OUTPUT)->ShowWindow(FALSE);
	}
	else
	{
	GetDlgItem(IDC_STATIC_GROUP_AQ_OUTPUT)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_AQ_LOW)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_AQ_LOW)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_AQ_HIGH)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_AQ_HIGH)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC_AQ_OUTPUT)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT_AQ_OUTPUT)->ShowWindow(TRUE);
	
	strTemp.Format(_T("%d"),product_register_value[MODBUS_AQ_RANGE_LOWER]);
	m_edit_aq_low.SetWindowTextW(strTemp);
	strTemp.Format(_T("%d"),product_register_value[MODBUS_AQ_RANGE_UPPER]);
	m_edit_aq_high.SetWindowTextW(strTemp);
	if (output_range==1||output_range==2)
	{
		strTemp.Format(_T("%0.2f V"),(float)(short)product_register_value[MODBUS_AQ_VOLTAGE_OUTPUT]/100.0);
		m_edit_aq_output.SetWindowTextW(strTemp);
	}
	else
	{
		strTemp.Format(_T("%0.1f mA"),(float)(short)product_register_value[MODBUS_AQ_CURRENT_OUTPUT]/10.0);
		m_edit_aq_output.SetWindowTextW(strTemp);
	}
	}
}
void CAirQuality::Initial_RegisterList(){
#if 1
	MODBUS_SERIALNUMBER_LOWORD	=	0	;
	MODBUS_SERIALNUMBER_HIWORD	=	2	;
	MODBUS_VERSION_NUMBER_LO	=	4	;
	MODBUS_VERSION_NUMBER_HI	=	5	;
	MODBUS_ADDRESS	=	6	;
	MODBUS_PRODUCT_MODEL	=	7	;
	MODBUS_HARDWARE_REV	=	8	;
	MODBUS_PIC_VERSION	=	9	;
	MODBUS_HUM_PIC_VERSION	=	10	;
	MODBUS_ADDRESS_PLUG_N_PLAY	=	11	;
	MODBUS_BASE_ADDRESS 	=	15	;
	MODBUS_UPDATE_STATUS	=	16	;
	MODBUS_UPDATE_PTR_HI	=	17	;
	MODBUS_UPDATE_PTR_LO	=	18	;
	MODBUS_SCRATCHPAD_ADDRESS	=	19	;
	MODBUS_TEMPRATURE_CHIP_F	=	100	;
	MODBUS_TEMPRATURE_CHIP 	=	101	;
	MODBUS_HUM            	=	102	;
	MODBUS_AQ            	=	103	;
	MODBUS_CALIBRATION_TEMP    	=	104	;
	MODBUS_CALIBRATION_AQ 	=	105	;
	MODBUS_CALIBRATION_HUM 	=	106	;
	MODBUS_TEMP_SELECT	=	111	;
	MODBUS_DAC_OFFSET	=	112	;
	MODBUS_DELAY	=	113	;
	MODBUS_SEQUENCE	=	114	;
	MODBUS_DEGC_OR_F 	=	121	;
	MODBUS_POWERUP_MODE  	=	122	;
	MODBUS_AUTO_ONLY 	=	123	;
	MODBUS_OUTPUT_RANGE	=	180	;
	MODBUS_FACTORY_DEFAULTS     	=	181	;
	MODBUS_EXTERNAL_SENSOR_0	=	182	;
	MODBUS_EXTERNAL_SENSOR_1	=	183	;
	MODBUS_INFO_BYTE	=	184	;
	MODBUS_BAUDRATE    	=	185	;
	MODBUS_HUM_FILTER	=	186	;
	MODBUS_AQ_FILTER	=	187	;
	MODBUS_DIGITAL_IN1	=	188	;
	MODBUS_CYCLING_DELAY 	=	190	;
	MODBUS_CHANGOVER_DELAY	=	191	;
	MODBUS_OVERRIDE_TIMER	=	192	;
	MODBUS_OVERRIDE_TIMER_LEFT	=	193	;
	MODBUS_FILTER	=	194	;
	MODBUS_HEAT_COOL_CONFIG	=	195	;
	MODBUS_INTERNAL_TEMP_IC	=	196	;
	MODBUS_INTERNAL_THERMISTOR	=	197	;
	MODBUS_CALIBRATION_INTERNAL_THERMISTOR	=	217	;
	MODBUS_CALIBRATION_ANALOG_IN2	=	218	;
	MODBUS_INPUT1_SELECT                          	=	219	;
	MODBUS_UNIVERSAL_NIGHTSET                  	=	220	;
	MODBUS_HEAT_ORIGINAL_TABLE                 	=	221	;
	MODBUS_COOL_ORIGINAL_TABLE                 	=	222	;
	MODBUS_PID2_MODE_OPERATION	=	223	;
	MODBUS_VALVE_TRAVEL_TIME 	=	224	;
	MODBUS_VALVE_PERCENT	=	225	;
	MODBUS_INTERLOCK_OUTPUT1	=	226	;
	MODBUS_INTERLOCK_OUTPUT2	=	227	;
	MODBUS_INTERLOCK_OUTPUT3	=	228	;
	MODBUS_INTERLOCK_OUTPUT4	=	229	;
	MODBUS_INTERLOCK_OUTPUT5	=	230	;
	MODBUS_INTERLOCK_OUTPUT6	=	231	;
	MODBUS_INTERLOCK_OUTPUT7	=	232	;
	MODBUS_SETPOINT_INCREASE	=	233	;
	MODBUS_FREEZE_TEMP_SETPOINT	=	234	;
	MODBUS_FREEZE_DELAY_ON	=	235	;
	MODBUS_FREEZE_DELAY_OFF	=	236	;
	MODBUS_ANALOG1_FUNCTION	=	237	;
	MODBUS_ANALOG2_FUNCTION	=	238	;
	MODBUS_DIGITAL1_FUNCTION	=	239	;
	MODBUS_DISPLAY_HUNDRED	=	240	;
	MODBUS_DISPLAY_TEN	=	241	;
	MODBUS_DISPLAY_DIGITAL	=	242	;
	MODBUS_DISPLAY_STATUS	=	243	;
	MODBUS_INPUT_MANU_ENABLE	=	244	;
	MODBUS_OUTPUT_MANU_ENABLE	=	245	;
	MODBUS_DIGITAL_INPUT	=	246	;
	MODBUS_DEAD_MASTER	=	247	;
	MODBUS_ROUND_DISPLAY	=	248	;
	MODBUS_MIN_ADDRESS 	=	249	;
	MODBUS_MAX_ADDRESS	=	250	;
	MODBUS_FAN_GRIDPOINT	=	251	;
	MODBUS_MODE_GRIDPOINT	=	252	;
	MODBUS_HOLD_GRIDPOINT	=	253	;
	MODBUS_CONFIGURATION	=	254	;
	MODBUS_UTIL_MODE	=	255	;
	MODBUS_EEPROM_SIZE	=	256	;
	MODBUS_TIMER_SELECT	=	257	;
	MODBUS_OUTPUT1_FUNCTION	=	258	;
	MODBUS_ROTATION_OUT2	=	259	;
	MODBUS_ROTATION_OUT3	=	260	;
	MODBUS_ROTATION_OUT4	=	261	;
	MODBUS_ROTATION_OUT5	=	262	;
	MODBUS_OUTPUT2_FUNCTION	=	263	;
	MODBUS_OUTPUT3_FUNCTION	=	264	;
	MODBUS_OUTPUT4_FUNCTION	=	265	;
	MODBUS_OUTPUT5_FUNCTION	=	266	;
	MODBUS_PIR_STAGE	=	267	;
	MODBUS_AIR_CALIBRATION_POINT4	=	300	;
	MODBUS_AIR_CALIBRATION_POINT1	=	301	;
	MODBUS_AIR_CALIBRATION_POINT2	=	302	;
	MODBUS_AIR_CALIBRATION_POINT3	=	303	;
	MODUBS_HUMIDITY_RH 	=	304	;
	MODBUS_HUMIDITY_FREQUENCY	=	305	;
	MODBUS_HUM_PIC_UPDATE	=	306	;
	MODBUS_HUM_CAL_NUM 	=	307	;
	MODBUS_HUM_CAL_EREASE 	=	308	;
	MODBUS_HUM_CURRENT_DEFAULT 	=	309	;
	MODBUS_HUM_PICDATAOK 	=	310	;
	MODBUS_HUM_OFFSETFLAG  	=	311	;
	MODBUS_HUMCOUNT1_H   	=	312	;
	MODBUS_HUMRH1_H	=	313	;
	MODBUS_HUMCOUNT2_H 	=	314	;
	MODBUS_HUMRH2_H	=	315	;
	MODBUS_HUMCOUNT3_H 	=	316	;
	MODBUS_HUMRH3_H	=	317	;
	MODBUS_HUMCOUNT4_H 	=	318	;
	MODBUS_HUMRH4_H	=	319	;
	MODBUS_HUMCOUNT5_H 	=	320	;
	MODBUS_HUMRH5_H	=	321	;
	MODBUS_HUMCOUNT6_H 	=	322	;
	MODBUS_HUMRH6_H	=	323	;
	MODBUS_HUMCOUNT7_H 	=	324	;
	MODBUS_HUMRH7_H	=	325	;
	MODBUS_HUMCOUNT8_H 	=	326	;
	MODBUS_HUMRH8_H	=	327	;
	MODBUS_HUMCOUNT9_H 	=	328	;
	MODBUS_HUMRH9_H	=	329	;
	MODBUS_HUMCOUNT10_H 	=	330	;
	MODBUS_HUMRH10_H	=	331	;
	MODBUS_TEM_RANGE_LOWER  	=	332	;
	MODBUS_TEM_RANGE_UPPER	=	333	;
	MODBUS_HUM_RANGE_LOWER	=	334	;
	MODBUS_HUM_RANGE_UPPER	=	335	;
	MODBUS_AQ_RANGE_LOWER	=	336	;
	MODBUS_AQ_RANGE_UPPER 	=	337	;
	MODBUS_TEMP_CURRENT_OUTPUT      	=	338	;
	MODBUS_HUM_CURRENT_OUTPUT	=	339	;
	MODBUS_AQ_CURRENT_OUTPUT	=	340	;
	MODBUS_TEMP_VOLTAGE_OUTPUT	=	341	;
	MODBUS_HUM_VOLTAGE_OUTPUT	=	342	;
	MODBUS_AQ_VOLTAGE_OUTPUT  	=	343	;
	MODBUS_CALIBRATION_MODE  	=	344	;
	MODBUS_SCROLL_MODE	=	345	;
	MODBUS_AQ_LEVEL0	=	346	;
	MODBUS_AQ_LEVEL1	=	347	;
	MODBUS_AQ_LEVEL2	=	348	;
	MODBUS_OUTPUT_MODE	=	349	;
	MODBUS_TEMP_MANU_OUTPUT	=	350	;
	MODBUS_HUM_MANU_OUTPUT	=	351	;
	MODBUS_AQ_MANU_OUTPUT	=	352	;
	MODBUS_HUM_CALIBRATION_LOCKX    	=	353	;
	MODBUS_HUM_CALIBRATION_LOCKY 	=	354	;
#endif

	T3Register temp;
	CADO m_ado;
	m_ado.OnInitADOConn();
#if 1
if (!m_ado.IsHaveTable(m_ado,_T("AirQuanlity_Reglist")))
{
return;
}
	CString SQL = _T("select * from AirQuanlity_Reglist");
	m_ado.m_pRecordset = m_ado.OpenRecordset(SQL);
	_variant_t vartemp;
	while(!m_ado.m_pRecordset->EndOfFile)
	{
		temp.regID=m_ado.m_pRecordset->GetCollect(_T("RegID"));
		vartemp =m_ado.m_pRecordset->GetCollect(_T("RegName"));
		if (vartemp.vt==VT_NULL)
			temp.regName=_T("");
		else
			temp.regName =vartemp;
		m_ado.m_pRecordset->MoveNext();
		m_vecT3Register.push_back(temp);
	}
	m_ado.CloseRecordset();
	m_ado.CloseConn();
#endif 

	MODBUS_SERIALNUMBER_LOWORD	=	Get_RegID(_T("	MODBUS_SERIALNUMBER_LOWORD	"))	;
	MODBUS_SERIALNUMBER_HIWORD	=	Get_RegID(_T("	MODBUS_SERIALNUMBER_HIWORD	"))	;
	MODBUS_VERSION_NUMBER_LO	=	Get_RegID(_T("	MODBUS_VERSION_NUMBER_LO	"))	;
	MODBUS_VERSION_NUMBER_HI	=	Get_RegID(_T("	MODBUS_VERSION_NUMBER_HI	"))	;
	MODBUS_ADDRESS	=	Get_RegID(_T("	MODBUS_ADDRESS	"))	;
	MODBUS_PRODUCT_MODEL	=	Get_RegID(_T("	MODBUS_PRODUCT_MODEL	"))	;
	MODBUS_HARDWARE_REV	=	Get_RegID(_T("	MODBUS_HARDWARE_REV	"))	;
	MODBUS_PIC_VERSION	=	Get_RegID(_T("	MODBUS_PIC_VERSION	"))	;
	MODBUS_HUM_PIC_VERSION	=	Get_RegID(_T("	MODBUS_HUM_PIC_VERSION	"))	;
	MODBUS_ADDRESS_PLUG_N_PLAY	=	Get_RegID(_T("	MODBUS_ADDRESS_PLUG_N_PLAY	"))	;
	MODBUS_BASE_ADDRESS 	=	Get_RegID(_T("	MODBUS_BASE_ADDRESS 	"))	;
	MODBUS_UPDATE_STATUS	=	Get_RegID(_T("	MODBUS_UPDATE_STATUS	"))	;
	MODBUS_UPDATE_PTR_HI	=	Get_RegID(_T("	MODBUS_UPDATE_PTR_HI	"))	;
	MODBUS_UPDATE_PTR_LO	=	Get_RegID(_T("	MODBUS_UPDATE_PTR_LO	"))	;
	MODBUS_SCRATCHPAD_ADDRESS	=	Get_RegID(_T("	MODBUS_SCRATCHPAD_ADDRESS	"))	;
	MODBUS_TEMPRATURE_CHIP_F	=	Get_RegID(_T("	MODBUS_TEMPRATURE_CHIP_F	"))	;
	MODBUS_TEMPRATURE_CHIP 	=	Get_RegID(_T("	MODBUS_TEMPRATURE_CHIP 	"))	;
	MODBUS_HUM            	=	Get_RegID(_T("	MODBUS_HUM            	"))	;
	MODBUS_AQ            	=	Get_RegID(_T("	MODBUS_AQ            	"))	;
	MODBUS_CALIBRATION_TEMP    	=	Get_RegID(_T("	MODBUS_CALIBRATION_TEMP    	"))	;
	MODBUS_CALIBRATION_AQ 	=	Get_RegID(_T("	MODBUS_CALIBRATION_AQ 	"))	;
	MODBUS_CALIBRATION_HUM 	=	Get_RegID(_T("	MODBUS_CALIBRATION_HUM 	"))	;
	MODBUS_TEMP_SELECT	=	Get_RegID(_T("	MODBUS_TEMP_SELECT	"))	;
	MODBUS_DAC_OFFSET	=	Get_RegID(_T("	MODBUS_DAC_OFFSET	"))	;
	MODBUS_DELAY	=	Get_RegID(_T("	MODBUS_DELAY	"))	;
	MODBUS_SEQUENCE	=	Get_RegID(_T("	MODBUS_SEQUENCE	"))	;
	MODBUS_DEGC_OR_F 	=	Get_RegID(_T("	MODBUS_DEGC_OR_F 	"))	;
	MODBUS_POWERUP_MODE  	=	Get_RegID(_T("	MODBUS_POWERUP_MODE  	"))	;
	MODBUS_AUTO_ONLY 	=	Get_RegID(_T("	MODBUS_AUTO_ONLY 	"))	;
	MODBUS_OUTPUT_RANGE	=	Get_RegID(_T("	MODBUS_OUTPUT_RANGE	"))	;
	MODBUS_FACTORY_DEFAULTS     	=	Get_RegID(_T("	MODBUS_FACTORY_DEFAULTS     	"))	;
	MODBUS_EXTERNAL_SENSOR_0	=	Get_RegID(_T("	MODBUS_EXTERNAL_SENSOR_0	"))	;
	MODBUS_EXTERNAL_SENSOR_1	=	Get_RegID(_T("	MODBUS_EXTERNAL_SENSOR_1	"))	;
	MODBUS_INFO_BYTE	=	Get_RegID(_T("	MODBUS_INFO_BYTE	"))	;
	MODBUS_BAUDRATE    	=	Get_RegID(_T("	MODBUS_BAUDRATE    	"))	;
	MODBUS_HUM_FILTER	=	Get_RegID(_T("	MODBUS_HUM_FILTER	"))	;
	MODBUS_AQ_FILTER	=	Get_RegID(_T("	MODBUS_AQ_FILTER	"))	;
	MODBUS_DIGITAL_IN1	=	Get_RegID(_T("	MODBUS_DIGITAL_IN1	"))	;
	MODBUS_CYCLING_DELAY 	=	Get_RegID(_T("	MODBUS_CYCLING_DELAY 	"))	;
	MODBUS_CHANGOVER_DELAY	=	Get_RegID(_T("	MODBUS_CHANGOVER_DELAY	"))	;
	MODBUS_OVERRIDE_TIMER	=	Get_RegID(_T("	MODBUS_OVERRIDE_TIMER	"))	;
	MODBUS_OVERRIDE_TIMER_LEFT	=	Get_RegID(_T("	MODBUS_OVERRIDE_TIMER_LEFT	"))	;
	MODBUS_FILTER	=	Get_RegID(_T("	MODBUS_FILTER	"))	;
	MODBUS_HEAT_COOL_CONFIG	=	Get_RegID(_T("	MODBUS_HEAT_COOL_CONFIG	"))	;
	MODBUS_INTERNAL_TEMP_IC	=	Get_RegID(_T("	MODBUS_INTERNAL_TEMP_IC	"))	;
	MODBUS_INTERNAL_THERMISTOR	=	Get_RegID(_T("	MODBUS_INTERNAL_THERMISTOR	"))	;
	MODBUS_CALIBRATION_INTERNAL_THERMISTOR	=	Get_RegID(_T("	MODBUS_CALIBRATION_INTERNAL_THERMISTOR	"))	;
	MODBUS_CALIBRATION_ANALOG_IN2	=	Get_RegID(_T("	MODBUS_CALIBRATION_ANALOG_IN2	"))	;
	MODBUS_INPUT1_SELECT                          	=	Get_RegID(_T("	MODBUS_INPUT1_SELECT                          	"))	;
	MODBUS_UNIVERSAL_NIGHTSET                  	=	Get_RegID(_T("	MODBUS_UNIVERSAL_NIGHTSET                  	"))	;
	MODBUS_HEAT_ORIGINAL_TABLE                 	=	Get_RegID(_T("	MODBUS_HEAT_ORIGINAL_TABLE                 	"))	;
	MODBUS_COOL_ORIGINAL_TABLE                 	=	Get_RegID(_T("	MODBUS_COOL_ORIGINAL_TABLE                 	"))	;
	MODBUS_PID2_MODE_OPERATION	=	Get_RegID(_T("	MODBUS_PID2_MODE_OPERATION	"))	;
	MODBUS_VALVE_TRAVEL_TIME 	=	Get_RegID(_T("	MODBUS_VALVE_TRAVEL_TIME 	"))	;
	MODBUS_VALVE_PERCENT	=	Get_RegID(_T("	MODBUS_VALVE_PERCENT	"))	;
	MODBUS_INTERLOCK_OUTPUT1	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT1	"))	;
	MODBUS_INTERLOCK_OUTPUT2	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT2	"))	;
	MODBUS_INTERLOCK_OUTPUT3	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT3	"))	;
	MODBUS_INTERLOCK_OUTPUT4	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT4	"))	;
	MODBUS_INTERLOCK_OUTPUT5	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT5	"))	;
	MODBUS_INTERLOCK_OUTPUT6	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT6	"))	;
	MODBUS_INTERLOCK_OUTPUT7	=	Get_RegID(_T("	MODBUS_INTERLOCK_OUTPUT7	"))	;
	MODBUS_SETPOINT_INCREASE	=	Get_RegID(_T("	MODBUS_SETPOINT_INCREASE	"))	;
	MODBUS_FREEZE_TEMP_SETPOINT	=	Get_RegID(_T("	MODBUS_FREEZE_TEMP_SETPOINT	"))	;
	MODBUS_FREEZE_DELAY_ON	=	Get_RegID(_T("	MODBUS_FREEZE_DELAY_ON	"))	;
	MODBUS_FREEZE_DELAY_OFF	=	Get_RegID(_T("	MODBUS_FREEZE_DELAY_OFF	"))	;
	MODBUS_ANALOG1_FUNCTION	=	Get_RegID(_T("	MODBUS_ANALOG1_FUNCTION	"))	;
	MODBUS_ANALOG2_FUNCTION	=	Get_RegID(_T("	MODBUS_ANALOG2_FUNCTION	"))	;
	MODBUS_DIGITAL1_FUNCTION	=	Get_RegID(_T("	MODBUS_DIGITAL1_FUNCTION	"))	;
	MODBUS_DISPLAY_HUNDRED	=	Get_RegID(_T("	MODBUS_DISPLAY_HUNDRED	"))	;
	MODBUS_DISPLAY_TEN	=	Get_RegID(_T("	MODBUS_DISPLAY_TEN	"))	;
	MODBUS_DISPLAY_DIGITAL	=	Get_RegID(_T("	MODBUS_DISPLAY_DIGITAL	"))	;
	MODBUS_DISPLAY_STATUS	=	Get_RegID(_T("	MODBUS_DISPLAY_STATUS	"))	;
	MODBUS_INPUT_MANU_ENABLE	=	Get_RegID(_T("	MODBUS_INPUT_MANU_ENABLE	"))	;
	MODBUS_OUTPUT_MANU_ENABLE	=	Get_RegID(_T("	MODBUS_OUTPUT_MANU_ENABLE	"))	;
	MODBUS_DIGITAL_INPUT	=	Get_RegID(_T("	MODBUS_DIGITAL_INPUT	"))	;
	MODBUS_DEAD_MASTER	=	Get_RegID(_T("	MODBUS_DEAD_MASTER	"))	;
	MODBUS_ROUND_DISPLAY	=	Get_RegID(_T("	MODBUS_ROUND_DISPLAY	"))	;
	MODBUS_MIN_ADDRESS 	=	Get_RegID(_T("	MODBUS_MIN_ADDRESS 	"))	;
	MODBUS_MAX_ADDRESS	=	Get_RegID(_T("	MODBUS_MAX_ADDRESS	"))	;
	MODBUS_FAN_GRIDPOINT	=	Get_RegID(_T("	MODBUS_FAN_GRIDPOINT	"))	;
	MODBUS_MODE_GRIDPOINT	=	Get_RegID(_T("	MODBUS_MODE_GRIDPOINT	"))	;
	MODBUS_HOLD_GRIDPOINT	=	Get_RegID(_T("	MODBUS_HOLD_GRIDPOINT	"))	;
	MODBUS_CONFIGURATION	=	Get_RegID(_T("	MODBUS_CONFIGURATION	"))	;
	MODBUS_UTIL_MODE	=	Get_RegID(_T("	MODBUS_UTIL_MODE	"))	;
	MODBUS_EEPROM_SIZE	=	Get_RegID(_T("	MODBUS_EEPROM_SIZE	"))	;
	MODBUS_TIMER_SELECT	=	Get_RegID(_T("	MODBUS_TIMER_SELECT	"))	;
	MODBUS_OUTPUT1_FUNCTION	=	Get_RegID(_T("	MODBUS_OUTPUT1_FUNCTION	"))	;
	MODBUS_ROTATION_OUT2	=	Get_RegID(_T("	MODBUS_ROTATION_OUT2	"))	;
	MODBUS_ROTATION_OUT3	=	Get_RegID(_T("	MODBUS_ROTATION_OUT3	"))	;
	MODBUS_ROTATION_OUT4	=	Get_RegID(_T("	MODBUS_ROTATION_OUT4	"))	;
	MODBUS_ROTATION_OUT5	=	Get_RegID(_T("	MODBUS_ROTATION_OUT5	"))	;
	MODBUS_OUTPUT2_FUNCTION	=	Get_RegID(_T("	MODBUS_OUTPUT2_FUNCTION	"))	;
	MODBUS_OUTPUT3_FUNCTION	=	Get_RegID(_T("	MODBUS_OUTPUT3_FUNCTION	"))	;
	MODBUS_OUTPUT4_FUNCTION	=	Get_RegID(_T("	MODBUS_OUTPUT4_FUNCTION	"))	;
	MODBUS_OUTPUT5_FUNCTION	=	Get_RegID(_T("	MODBUS_OUTPUT5_FUNCTION	"))	;
	MODBUS_PIR_STAGE	=	Get_RegID(_T("	MODBUS_PIR_STAGE	"))	;
	MODBUS_AIR_CALIBRATION_POINT4	=	Get_RegID(_T("	MODBUS_AIR_CALIBRATION_POINT4	"))	;
	MODBUS_AIR_CALIBRATION_POINT1	=	Get_RegID(_T("	MODBUS_AIR_CALIBRATION_POINT1	"))	;
	MODBUS_AIR_CALIBRATION_POINT2	=	Get_RegID(_T("	MODBUS_AIR_CALIBRATION_POINT2	"))	;
	MODBUS_AIR_CALIBRATION_POINT3	=	Get_RegID(_T("	MODBUS_AIR_CALIBRATION_POINT3	"))	;
	MODUBS_HUMIDITY_RH 	=	Get_RegID(_T("	MODUBS_HUMIDITY_RH 	"))	;
	MODBUS_HUMIDITY_FREQUENCY	=	Get_RegID(_T("	MODBUS_HUMIDITY_FREQUENCY	"))	;
	MODBUS_HUM_PIC_UPDATE	=	Get_RegID(_T("	MODBUS_HUM_PIC_UPDATE	"))	;
	MODBUS_HUM_CAL_NUM 	=	Get_RegID(_T("	MODBUS_HUM_CAL_NUM 	"))	;
	MODBUS_HUM_CAL_EREASE 	=	Get_RegID(_T("	MODBUS_HUM_CAL_EREASE 	"))	;
	MODBUS_HUM_CURRENT_DEFAULT 	=	Get_RegID(_T("	MODBUS_HUM_CURRENT_DEFAULT 	"))	;
	MODBUS_HUM_PICDATAOK 	=	Get_RegID(_T("	MODBUS_HUM_PICDATAOK 	"))	;
	MODBUS_HUM_OFFSETFLAG  	=	Get_RegID(_T("	MODBUS_HUM_OFFSETFLAG  	"))	;
	MODBUS_HUMCOUNT1_H   	=	Get_RegID(_T("	MODBUS_HUMCOUNT1_H   	"))	;
	MODBUS_HUMRH1_H	=	Get_RegID(_T("	MODBUS_HUMRH1_H	"))	;
	MODBUS_HUMCOUNT2_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT2_H 	"))	;
	MODBUS_HUMRH2_H	=	Get_RegID(_T("	MODBUS_HUMRH2_H	"))	;
	MODBUS_HUMCOUNT3_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT3_H 	"))	;
	MODBUS_HUMRH3_H	=	Get_RegID(_T("	MODBUS_HUMRH3_H	"))	;
	MODBUS_HUMCOUNT4_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT4_H 	"))	;
	MODBUS_HUMRH4_H	=	Get_RegID(_T("	MODBUS_HUMRH4_H	"))	;
	MODBUS_HUMCOUNT5_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT5_H 	"))	;
	MODBUS_HUMRH5_H	=	Get_RegID(_T("	MODBUS_HUMRH5_H	"))	;
	MODBUS_HUMCOUNT6_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT6_H 	"))	;
	MODBUS_HUMRH6_H	=	Get_RegID(_T("	MODBUS_HUMRH6_H	"))	;
	MODBUS_HUMCOUNT7_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT7_H 	"))	;
	MODBUS_HUMRH7_H	=	Get_RegID(_T("	MODBUS_HUMRH7_H	"))	;
	MODBUS_HUMCOUNT8_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT8_H 	"))	;
	MODBUS_HUMRH8_H	=	Get_RegID(_T("	MODBUS_HUMRH8_H	"))	;
	MODBUS_HUMCOUNT9_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT9_H 	"))	;
	MODBUS_HUMRH9_H	=	Get_RegID(_T("	MODBUS_HUMRH9_H	"))	;
	MODBUS_HUMCOUNT10_H 	=	Get_RegID(_T("	MODBUS_HUMCOUNT10_H 	"))	;
	MODBUS_HUMRH10_H	=	Get_RegID(_T("	MODBUS_HUMRH10_H	"))	;
	MODBUS_TEM_RANGE_LOWER  	=	Get_RegID(_T("	MODBUS_TEM_RANGE_LOWER  	"))	;
	MODBUS_TEM_RANGE_UPPER	=	Get_RegID(_T("	MODBUS_TEM_RANGE_UPPER	"))	;
	MODBUS_HUM_RANGE_LOWER	=	Get_RegID(_T("	MODBUS_HUM_RANGE_LOWER	"))	;
	MODBUS_HUM_RANGE_UPPER	=	Get_RegID(_T("	MODBUS_HUM_RANGE_UPPER	"))	;
	MODBUS_AQ_RANGE_LOWER	=	Get_RegID(_T("	MODBUS_AQ_RANGE_LOWER	"))	;
	MODBUS_AQ_RANGE_UPPER 	=	Get_RegID(_T("	MODBUS_AQ_RANGE_UPPER 	"))	;
	MODBUS_TEMP_CURRENT_OUTPUT      	=	Get_RegID(_T("	MODBUS_TEMP_CURRENT_OUTPUT      	"))	;
	MODBUS_HUM_CURRENT_OUTPUT	=	Get_RegID(_T("	MODBUS_HUM_CURRENT_OUTPUT	"))	;
	MODBUS_AQ_CURRENT_OUTPUT	=	Get_RegID(_T("	MODBUS_AQ_CURRENT_OUTPUT	"))	;
	MODBUS_TEMP_VOLTAGE_OUTPUT	=	Get_RegID(_T("	MODBUS_TEMP_VOLTAGE_OUTPUT	"))	;
	MODBUS_HUM_VOLTAGE_OUTPUT	=	Get_RegID(_T("	MODBUS_HUM_VOLTAGE_OUTPUT	"))	;
	MODBUS_AQ_VOLTAGE_OUTPUT  	=	Get_RegID(_T("	MODBUS_AQ_VOLTAGE_OUTPUT  	"))	;
	MODBUS_CALIBRATION_MODE  	=	Get_RegID(_T("	MODBUS_CALIBRATION_MODE  	"))	;
	MODBUS_SCROLL_MODE	=	Get_RegID(_T("	MODBUS_SCROLL_MODE	"))	;
	MODBUS_AQ_LEVEL0	=	Get_RegID(_T("	MODBUS_AQ_LEVEL0	"))	;
	MODBUS_AQ_LEVEL1	=	Get_RegID(_T("	MODBUS_AQ_LEVEL1	"))	;
	MODBUS_AQ_LEVEL2	=	Get_RegID(_T("	MODBUS_AQ_LEVEL2	"))	;
	MODBUS_OUTPUT_MODE	=	Get_RegID(_T("	MODBUS_OUTPUT_MODE	"))	;
	MODBUS_TEMP_MANU_OUTPUT	=	Get_RegID(_T("	MODBUS_TEMP_MANU_OUTPUT	"))	;
	MODBUS_HUM_MANU_OUTPUT	=	Get_RegID(_T("	MODBUS_HUM_MANU_OUTPUT	"))	;
	MODBUS_AQ_MANU_OUTPUT	=	Get_RegID(_T("	MODBUS_AQ_MANU_OUTPUT	"))	;
	MODBUS_HUM_CALIBRATION_LOCKX    	=	Get_RegID(_T("	MODBUS_HUM_CALIBRATION_LOCKX    	"))	;
	MODBUS_HUM_CALIBRATION_LOCKY 	=	Get_RegID(_T("	MODBUS_HUM_CALIBRATION_LOCKY 	"))	;
}	  
int  CAirQuality::Get_RegID(CString Name)
 {
	 Name.TrimLeft();
	 Name.TrimRight();
	 int regid=-1;
	 vector<T3Register>::iterator iter;
	 for (iter=m_vecT3Register.begin();iter!=m_vecT3Register.end();iter++)
	 {
		 if (iter->regName==Name)
		 {
			 regid=iter->regID;
			 break;
		 }
	 }
	 return regid;
 }


void CAirQuality::OnEnKillfocustempfilter(){
     m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_temp_filter.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}
	  
	  if(product_register_value[MODBUS_OVERRIDE_TIMER_LEFT]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
		{ m_fresh_data=TRUE; return;}
 
		 unsigned short TempShort=(unsigned short)_wtoi(strTemp);
		  int ret=write_one(g_tstat_id,MODBUS_OVERRIDE_TIMER_LEFT,TempShort);
		  if (ret>0)
		  {
		    product_register_value[MODBUS_OVERRIDE_TIMER_LEFT]=TempShort;
			ShowInput();
		  }
		  else
		  {
		    AfxMessageBox(_T("Write Fail!"));
		  }
		  m_fresh_data=TRUE;
  }

void CAirQuality::OnEnKillfocusBackLightTime(){
	m_fresh_data=FALSE;
	CString strTemp;
	m_edit_backlightTime.GetWindowText(strTemp);
	if(strTemp.IsEmpty())
	{m_fresh_data=TRUE;  return;}
	int backlighttime=-1;
	if (strTemp.CompareNoCase(_T("off"))==0)
	{
	backlighttime=0;
	}
	else if(strTemp.CompareNoCase(_T("on"))==0){
	backlighttime=255;
	}
	else {
	backlighttime=_wtoi(strTemp);
	}
	if (backlighttime>=0&&backlighttime<=255)
	{

	}
	else
	{
	  AfxMessageBox(_T("Please input the value>=0&&<=255"));
	  return;
	}
	if(product_register_value[361]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
	{ m_fresh_data=TRUE; return;}

	unsigned short TempShort=(unsigned short)_wtoi(strTemp);
	int ret=write_one(g_tstat_id,361,TempShort);
	if (ret>0)
	{
		product_register_value[361]=TempShort;
		ShowInput();
	}
	else
	{
		AfxMessageBox(_T("Write Fail!"));
	}
	m_fresh_data=TRUE;
}

void CAirQuality::OnEnKillfocushumfilter(){
m_fresh_data=FALSE;

	  CString strTemp;
	  m_edit_hum_filter.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return  ;}

	  if(product_register_value[MODBUS_HUM_FILTER]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;}

// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_HUM_FILTER,_wtoi(strTemp),
// 		  product_register_value[MODBUS_HUM_FILTER],this->m_hWnd,IDC_EDIT_HUM_FILTER,_T("Hum Filter"));
	  unsigned short TempShort=(unsigned short)_wtoi(strTemp);
	  int ret=write_one(g_tstat_id,MODBUS_HUM_FILTER,TempShort);
	  if (ret>0)
	  {
		  product_register_value[MODBUS_HUM_FILTER]=TempShort;
		  ShowInput();
	  }
	  else
	  {
		  AfxMessageBox(_T("Write Fail!"));
	  }
	  m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocusAQfilter(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_aq_filter.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		 {m_fresh_data=TRUE; return;}

	  if(product_register_value[MODBUS_AQ_FILTER]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
		  {m_fresh_data=TRUE;return;}


	  unsigned short TempShort=(unsigned short)_wtoi(strTemp);
	  int ret=write_one(g_tstat_id,MODBUS_AQ_FILTER,TempShort);
	  if (ret>0)
	  {
		  product_register_value[MODBUS_AQ_FILTER]=TempShort;
		  ShowInput();
	  }
	  else
	  {
		  AfxMessageBox(_T("Write Fail!"));
	  }
	  m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocustemp(){
    m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_temperature.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		 {m_fresh_data=TRUE; return;}
		 unsigned short TempShort=(unsigned short)_wtof(strTemp)*10.0;

		 if(product_register_value[MODBUS_DEGC_OR_F]==0)
		 {

			 if(product_register_value[MODBUS_TEMPRATURE_CHIP]==TempShort)	//Add this to judge weather this value need to change.
				{m_fresh_data=TRUE; return;}
		 

// 			 Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_TEMPRATURE_CHIP,TempShort,
// 				 product_register_value[MODBUS_TEMPRATURE_CHIP],this->m_hWnd,IDC_EDIT_TEMPERATURE,_T("Temp"));
			 //unsigned short TempShort=(unsigned short)_wtoi(strTemp);
			 int ret=write_one(g_tstat_id,MODBUS_TEMPRATURE_CHIP,TempShort);
			 if (ret>0)
			 {
				 product_register_value[MODBUS_TEMPRATURE_CHIP]=TempShort;
				 ShowInput();
			 }
			 else
			 {
				 AfxMessageBox(_T("Write Fail!"));
			 }
			 m_fresh_data=TRUE;
		 } 
		 else
		 {
		 

			 if(product_register_value[MODBUS_TEMPRATURE_CHIP_F]==TempShort)	//Add this to judge weather this value need to change.
				{m_fresh_data=TRUE; return;}


// 			 Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_TEMPRATURE_CHIP_F,TempShort,
// 				 product_register_value[MODBUS_TEMPRATURE_CHIP_F],this->m_hWnd,IDC_EDIT_TEMPERATURE,_T("Temp Filter"));
int ret=write_one(g_tstat_id,MODBUS_TEMPRATURE_CHIP_F,TempShort);
if (ret>0)
{
	product_register_value[MODBUS_TEMPRATURE_CHIP_F]=TempShort;
	ShowInput();
}
else
{
	AfxMessageBox(_T("Write Fail!"));
}
m_fresh_data=TRUE;
}
		  

  }
void CAirQuality::OnEnKillfocushum(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_hum.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}
		   unsigned short TempShort=(unsigned short)_wtof(strTemp)*10.0;

	  if(product_register_value[MODBUS_HUM]==TempShort)	//Add this to judge weather this value need to change.
		 {m_fresh_data=TRUE; return;}

	  //Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_HUM,TempShort,
		 // product_register_value[MODBUS_HUM],this->m_hWnd,IDC_EDIT_HUM,_T("Humidity"));
		int ret= write_one(g_tstat_id,MODBUS_HUM,TempShort);
		 if (ret>0)
		 {
			 product_register_value[MODBUS_HUM]=TempShort;
			 ShowInput();
		 }
		 else
		 {
			 AfxMessageBox(_T("Write Fail!"));
		 }
		 m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocusAQ(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_AQ.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}

	  if(product_register_value[MODBUS_AQ]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;}

// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_AQ,_wtoi(strTemp),
// 		  product_register_value[MODBUS_AQ],this->m_hWnd,IDC_EDIT_AQ,_T("Air Quanlity"));
unsigned short TempShort=(unsigned short)_wtoi(strTemp);
int ret=write_one(g_tstat_id,MODBUS_AQ,TempShort);
if (ret>0)
{
	product_register_value[MODBUS_AQ]=TempShort;
	ShowInput();
}
else
{
	AfxMessageBox(_T("Write Fail!"));
}
m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocustemplow(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_temp_low.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		 {m_fresh_data=TRUE; return;}
		   unsigned short TempShort=(unsigned short)_wtof(strTemp)*10.0;
	  if(product_register_value[MODBUS_TEM_RANGE_LOWER]==TempShort)	//Add this to judge weather this value need to change.
		 {m_fresh_data=TRUE; return;}
// 
// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_TEM_RANGE_LOWER,TempShort,
// 		  product_register_value[MODBUS_TEM_RANGE_LOWER],this->m_hWnd,IDC_EDIT_TEMP_LOW,_T("Temp Low"));
int ret=write_one(g_tstat_id,MODBUS_TEM_RANGE_LOWER,TempShort);
if (ret>0)
{
	product_register_value[MODBUS_TEM_RANGE_LOWER]=TempShort;
	ShowOutput();
}
else
{
	AfxMessageBox(_T("Write Fail!"));
}
m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocustemphigh(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_temp_high.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}
		  unsigned short TempShort=(unsigned short)_wtof(strTemp)*10.0;
	  if(product_register_value[MODBUS_TEM_RANGE_UPPER]==TempShort)	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;}

	  //Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_TEM_RANGE_UPPER,TempShort,
		 // product_register_value[MODBUS_TEM_RANGE_UPPER],this->m_hWnd,IDC_EDIT_TEMP_HIGH,_T("Temp High"));
		 int ret=write_one(g_tstat_id,MODBUS_TEM_RANGE_UPPER,TempShort);
		 if (ret>0)
		 {
			 product_register_value[MODBUS_TEM_RANGE_UPPER]=TempShort;
			 ShowOutput();
		 }
		 else
		 {
			 AfxMessageBox(_T("Write Fail!"));
		 }
		 m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocushumlow(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_hum_low.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}
		   unsigned short TempShort=(unsigned short)_wtof(strTemp)*10.0;
	  if(product_register_value[MODBUS_HUM_RANGE_LOWER]==TempShort)	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;}

// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_HUM_RANGE_LOWER,TempShort,
// 		  product_register_value[MODBUS_HUM_RANGE_LOWER],this->m_hWnd,IDC_EDIT_HUM_LOW,_T("Hum Low"));
 int ret=write_one(g_tstat_id,MODBUS_HUM_RANGE_LOWER,TempShort);
 if (ret>0)
 {
	 product_register_value[MODBUS_HUM_RANGE_LOWER]=TempShort;
	 ShowOutput();
 }
 else
 {
	 AfxMessageBox(_T("Write Fail!"));
 }
 m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocushumhigh(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_hum_high.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}
		  unsigned short TempShort=(unsigned short)_wtof(strTemp)*10.0;
	  if(product_register_value[MODBUS_HUM_RANGE_UPPER]==TempShort)	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;
		}
// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_HUM_RANGE_UPPER,TempShort,
// 		  product_register_value[MODBUS_HUM_RANGE_UPPER],this->m_hWnd,IDC_EDIT_HUM_HIGH,_T("Hum High"));
int ret=write_one(g_tstat_id,MODBUS_HUM_RANGE_UPPER,TempShort);
if (ret>0)
{
	product_register_value[MODBUS_HUM_RANGE_UPPER]=TempShort;
	ShowOutput();
}
else
{
	AfxMessageBox(_T("Write Fail!"));
}
m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocusaqlow(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_aq_low.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}

	  if(product_register_value[MODBUS_AQ_RANGE_LOWER]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;}
		   unsigned short TempShort=(unsigned short)_wtoi(strTemp);
// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_AQ_RANGE_LOWER,_wtoi(strTemp),
// 		  product_register_value[MODBUS_AQ_RANGE_LOWER],this->m_hWnd,IDC_EDIT_AQ_LOW,_T("Temp Filter"));
       int ret=write_one(g_tstat_id,MODBUS_AQ_RANGE_LOWER,TempShort);
	   if (ret>0)
	   {
		   product_register_value[MODBUS_AQ_RANGE_LOWER]=TempShort;
		   ShowOutput();
	   }
	   else
	   {
		   AfxMessageBox(_T("Write Fail!"));
	   }
	   m_fresh_data=TRUE;
  }
void CAirQuality::OnEnKillfocusaqhigh(){m_fresh_data=FALSE;
	  CString strTemp;
	  m_edit_aq_high.GetWindowText(strTemp);
	  if(strTemp.IsEmpty())
		{m_fresh_data=TRUE;  return;}

	  if(product_register_value[MODBUS_AQ_RANGE_UPPER]==_wtoi(strTemp))	//Add this to judge weather this value need to change.
		{m_fresh_data=TRUE;  return;}
// 
// 	  Post_Thread_Message(MY_WRITE_ONE,g_tstat_id,MODBUS_AQ_RANGE_UPPER,_wtoi(strTemp),
// 		  product_register_value[MODBUS_AQ_RANGE_UPPER],this->m_hWnd,IDC_EDIT_AQ_HIGH,_T("Temp Filter"));
	  unsigned short TempShort=(unsigned short)_wtoi(strTemp);
	  int ret=write_one(g_tstat_id,MODBUS_AQ_RANGE_UPPER,TempShort);
	  if (ret>0)
	  {
		  product_register_value[MODBUS_AQ_RANGE_UPPER]=TempShort;
		  ShowOutput();
	  }
	  else
	  {
		  AfxMessageBox(_T("Write Fail!"));
	  }
	  m_fresh_data=TRUE;
  }
void CAirQuality::OnCbnCFUnits()
{
	 
	 m_fresh_data=FALSE;
	 int sel=m_combox_units.GetCurSel();
	 int ret= write_one(g_tstat_id,MODBUS_DEGC_OR_F,sel);
	 if (ret>0)
	 {
		 product_register_value[MODBUS_DEGC_OR_F]=sel;
		 ShowInput();
	 }
	 else
	 {
		 AfxMessageBox(_T("Write Fail!"));
	 }
	 m_fresh_data=TRUE;
}
#include "../EreaseDlg.h"
void CAirQuality::OnBnClickedButton_Change_ID(){
	CEreaseDlg Dlg;
	Dlg.DoModal();
}
LRESULT CAirQuality::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{


	if(WM_AIRQUANITY_FRESH==message){
		Fresh_Window();
	}
	return CFormView::WindowProc(message, wParam, lParam);
}
//afx_msg void OnEnKillfocustempfilter();
//afx_msg void OnEnKillfocushumfilter();
//afx_msg void OnEnKillfocusAQfilter();
//afx_msg void OnEnKillfocustemp();
//afx_msg void OnEnKillfocushum();
//afx_msg void OnEnKillfocusAQ();
//afx_msg void OnEnKillfocustemplow();
//afx_msg void OnEnKillfocustemphigh();
//afx_msg void OnEnKillfocushumlow();
//afx_msg void OnEnKillfocushumhigh();
//afx_msg void OnEnKillfocusaqlow();
//afx_msg void OnEnKillfocusaqhigh();
BOOL CAirQuality::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN  )
	{
		if(pMsg->wParam == VK_RETURN)
		{
			//CWnd *temp_focus=GetFocus();	//Maurice require ,click enter and the cursor still in this edit or combobox.
			////GetDlgItem(IDC_REFRESHBUTTON)->SetFocus();
			//temp_focus->OnKillFocus();
			CWnd *temp_focus=GetFocus();	//Maurice require ,click enter and the cursor still in this edit or combobox.
			GetDlgItem(IDC_EDIT1_TEST)->SetFocus();
			temp_focus->SetFocus();


			#if 0
			CWnd *temp_focus=GetFocus();
			int CONTROL_ID=temp_focus->GetDlgCtrlID();
			switch (CONTROL_ID)
			{
			case IDC_EDIT_TEMP_FILTER:
				OnEnKillfocustempfilter();
				break;
			case IDC_EDIT_HUM_FILTER:
				OnEnKillfocushumfilter();
				break;
			case IDC_EDIT_AR_FILTER:
				OnEnKillfocusAQfilter();
				break;
			case IDC_EDIT_TEMPERATURE:
				OnEnKillfocustemp();
				break;
			case IDC_EDIT_HUM:
				OnEnKillfocushum();
				break;
			case IDC_EDIT_AQ:
				OnEnKillfocusAQ();
				break;
			case IDC_EDIT_TEMP_LOW:
				OnEnKillfocustemplow();
				break;
			case IDC_EDIT_TEMP_HIGH:
				OnEnKillfocustemphigh();
				break;
			case IDC_EDIT_HUM_LOW:
				OnEnKillfocushumlow();
				break;
			case IDC_EDIT_HUM_HIGH:
				OnEnKillfocushumhigh();
				break;
			case IDC_EDIT_AQ_LOW:
				OnEnKillfocusaqlow();
				break;
			case IDC_EDIT_AQ_HIGH:
				OnEnKillfocusaqhigh();
				break;

			}
           #endif
			

			return 1;
		}
	}

	return CFormView::PreTranslateMessage(pMsg);
}