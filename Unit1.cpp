//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "ComObj.hpp"   // ����� ��� ������������� OLE
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerTimer(TObject *Sender)
{
        // ������ ������������� ��������� ����� ������ ���
        // ���� ��� ����� ������� - �������� ������� ��������������
        // ������ � 1�
        // �������� ��������� �����
TDateTime RealTime = Time();
AnsiString RealTimeStr = (TimeToStr(RealTime)).SubString(1,5);
        // ���� ��� 16.00 - ��������� 1� � ������������� ������
//if(RealTimeStr=="9:51:" || RealTimeStr=="10:02" || RealTimeStr=="16:00") {
if(RealTimeStr=="16:00") {
        // �������� ����
        ShowWindow(Application->Handle, SW_SHOW);
        Application->MainForm->Visible = true;
        Form1->Repaint();
        Form1->Refresh();
        // ������ ������ 1�
        Variant v7 = CreateOleObject("V77.Application");
        // ���������������� ���
        v7.Exec(Procedure("Initialize") << (v7.Exec(Procedure("RMTrade"))) << "ENTERPRISE /D\"C:\\Program Files\\1cbase\\DB\" /Nnikita /M" << "NO_SPLASH_SHOW");
        // ��������� �� ���������� ����� ������������ � ��������� (����� ������ ��������������� �������������)
        v7.Exec(Procedure("EvalExpr") << "OpenForm(\"���������.������������\",\"1\")");
        // ����� ������ �����
        ShowWindow(Application->Handle, SW_HIDE);
        Application->MainForm->Visible = false;
        }
}
//---------------------------------------------------------------------------
