#pragma once
#include "stdafx.h"
typedef struct T3_Register
{
	int regID;
	CString regName;
}T3Register;
//////////////////////////////////////////////////////////////////////////
// for setting file
const TCHAR c_strCfgTstatSection[] = _T("[Tstat]");
const TCHAR c_strCfgDefaultInstalldirItem[] = _T("Installdir : ");
const TCHAR c_strCfgLastFlashFileItem[] = _T("LastFlashFile : ");
const TCHAR c_strCfgLastFlashMethodItem[] = _T("LastFlashMethod : ");
const TCHAR c_strCfgDefaultAddrItem[] = _T("Default address : ");
const TCHAR c_strCfgDefaultComItem[] = _T("Default COM port : ");

const TCHAR c_strCfgNCSection[] = _T("[NC]");
const TCHAR c_strCfgDefaultIPItem[] = _T("Default IP : ");
const TCHAR c_strCfgDefaultIPPortItem[] = _T("Default IP Port : ");
const TCHAR c_strCfgDefaultBaudrateItem[] = _T("Default baudrate : ");//
const TCHAR c_strCfgLastFlashTypePageItem[] = _T("LastFlashPage : ");

const TCHAR c_strCfgLightCtrlSection[] = _T("[Lighting Controller]");
const TCHAR c_strCfgLastFlashLCTypeItem[] = _T("LastFlashType : ");
const TCHAR c_strCfgLastFlashLCTypeMain[] = _T("Main board");
const TCHAR c_strCfgLastFlashLCTypeInput[] = _T("Input board");
const TCHAR c_strCfgLastFlashLCTypeOutput[] = _T("Output board");

const TCHAR c_strCfgLastFlashMDBIDItem[] = _T("Default address : ");

const TCHAR c_strCfgNote[] = _T("Default Note : ");
const TCHAR c_strCfgSubID[] = _T("Default SubID : ");


//
const TCHAR c_strFlashMethodEthernet[] = _T("Ethernet");
const TCHAR c_strFlashMethodCom[] = _T("COM");
struct ALL_LOCAL_SUBNET_NODE{
	CString StrIP;
	CString StrMask;
	CString StrGetway;
	int NetworkCardType;
};
 
//struct Reg_Infor{
//BOOL Reg_Property;
//int regAddress;
//int RegValue;
//CString StrValue;
//};
class Reg_Infor{
public:
Reg_Infor(){
Reg_Property=1;
regAddress = -1;
RegValue = -1;
StrValue = _T("N/A");
}
	BOOL Reg_Property;
	int regAddress;
	int RegValue;
	CString StrValue;
};


struct Tstat_Input_Struct{
	Reg_Infor InputName;
	Reg_Infor AM;
	Reg_Infor Value;
	Reg_Infor Unit;
	Reg_Infor Filter;
	Reg_Infor Range;
	Reg_Infor Function;
	Reg_Infor CustomTable;
};

struct Tstat_Output_Struct{
	Reg_Infor  OutputName;
	Reg_Infor  Value;
	Reg_Infor  Unit;
	Reg_Infor  AM;
	Reg_Infor  Range;
	Reg_Infor  Function;
	Reg_Infor  Interlock;
	Reg_Infor  OFFON_Delay;
	Reg_Infor  ONOFF_Delay;
	Reg_Infor  Signal_Type;
};
 

typedef struct RegPoint{
	double Time_offset;
	double Value_offset;
};
typedef struct Registers_Infor
{
	vector<RegPoint> Reg_Point;
	COLORREF Point_Color;
	CString Reg_Name;
	int address;
};