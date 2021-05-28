//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

#include "ComObj.hpp"   // Нужно для использования OLE
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
        // Таймер просматривает системное время каждый час
        // Если оно равно нужному - вызывает команду импортирования
        // заявок в 1С
        // получить системное время
TDateTime RealTime = Time();
AnsiString RealTimeStr = (TimeToStr(RealTime)).SubString(1,5);
        // если это 16.00 - запустить 1С и импортировать данные
//if(RealTimeStr=="9:51:" || RealTimeStr=="10:02" || RealTimeStr=="16:00") {
if(RealTimeStr=="16:00") {
        // Показать окно
        ShowWindow(Application->Handle, SW_SHOW);
        Application->MainForm->Visible = true;
        Form1->Repaint();
        Form1->Refresh();
        // оздать объект 1С
        Variant v7 = CreateOleObject("V77.Application");
        // Инициализировать его
        v7.Exec(Procedure("Initialize") << (v7.Exec(Procedure("RMTrade"))) << "ENTERPRISE /D\"C:\\Program Files\\1cbase\\DB\" /Nnikita /M" << "NO_SPLASH_SHOW");
        // Запустить на выполнение форму ИмпортЗаявок с парамтром (чтобы заявки импортировались автоматически)
        v7.Exec(Procedure("EvalExpr") << "OpenForm(\"Обработка.ИмпортЗаявок\",\"1\")");
        // Снова скрыть форму
        ShowWindow(Application->Handle, SW_HIDE);
        Application->MainForm->Visible = false;
        }
}
//---------------------------------------------------------------------------
