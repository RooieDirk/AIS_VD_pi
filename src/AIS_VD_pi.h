/*****************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  AIS_VD Plugin
 *
 ***************************************************************************
 *   Copyright (C) 2010 by 2014 by Dirk Smits                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************
 */

#ifndef _AISVDPI_H_
#define _AISVDPI_H_

#include "wx/wxprec.h"
#include "wx/valtext.h"
#include "wx/datectrl.h"
#include "wx/dateevt.h"
#include <wx/fileconf.h>
#include <wx/timectrl.h>

#include "ocpn_plugin.h"


#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#define     PLUGIN_VERSION_MAJOR    0
#define     PLUGIN_VERSION_MINOR    0

#define     MY_API_VERSION_MAJOR    1
#define     MY_API_VERSION_MINOR    9

//#include "nmea0183/nmea0183.h"
////@begin control identifiers
#define ID_T wxID_ANY
#define ID_PANEL wxID_ANY
#define ID_CHOICE wxID_ANY
#define ID_TEXTCTRL wxID_ANY
#define ID_TEXTCTRL1 wxID_ANY
#define ID_TEXTCTRL2 wxID_ANY
#define ID_DATECTRL wxID_ANY
#define ID_TIMECTR wxID_ANY
#define ID_BUTTON wxID_ANY
#define ID_BUTTON1 wxID_ANY
#define SYMBOL_T_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_T_TITLE _("t")
#define SYMBOL_T_IDNAME ID_T
#define SYMBOL_T_SIZE wxSize(500, 500)
#define SYMBOL_T_POSITION wxDefaultPosition
////@end control identifiers
class TimePickerCtrl;
class aisvd_pi;
class PreferenceDlg;
// An Event handler class to catch events from S63 UI dialog
class aisvd_pi_event_handler : public wxEvtHandler
{
public:

    aisvd_pi_event_handler(aisvd_pi *parent);
    ~aisvd_pi_event_handler();
	void OnSendBtnClick( wxCommandEvent &event );
    /*void OnImportPermitClick( wxCommandEvent &event );
    void OnRemovePermitClick( wxCommandEvent &event );
    void OnImportCellsClick( wxCommandEvent &event );
    void OnSelectPermit( wxListEvent& event );    
    void OnNewUserpermitClick( wxCommandEvent& event ); */   
    aisvd_pi  *m_parent;
};

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------


class aisvd_pi : public opencpn_plugin_19
{
public:
      aisvd_pi(void *ppimgr);
	~aisvd_pi();
//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
	  wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();

//    The optional method overrides
      void SetNMEASentence(wxString &sentence);

//    The override PlugIn Methods
      void ShowPreferencesDialog( wxWindow* parent );
      void SetPluginMessage(wxString &message_id, wxString &message_body);
	void OnSetupOptions();
    void OnCloseToolboxPanel(int page_sel, int ok_apply_cancel);
    bool SaveConfig( void );
	void UpdateDestVal();
	void UpdateDraught();
	void UpdatePersons();
	void UpdateEta();
	void SendSentence();
	PreferenceDlg *prefDlg;
	wxString AIS_type;
	wxString m_Destination;
    wxString m_Draught;
    wxString m_Persons;
    wxString m_EtaDate; //MMDD
    wxString m_EtaTime; //HHmm
	wxDateTime m_EtaDateTime;

private:
    bool LoadConfig( void );  
	wxWindow         *m_parent_window;
	wxBitmap          *m_pplugin_icon;
    wxScrolledWindow  *m_AIS_VoyDataWin;
	aisvd_pi_event_handler *m_event_handler;
	//wxString DestValid;
	

	wxChoice* StatusChoice;
	wxTextCtrl* m_DestTextCtrl;
	wxTextCtrl* DraughtTextCtrl;
	wxTextCtrl* PersonsTextCtrl;
	wxDatePickerCtrl* DatePicker;
	wxTimePickerCtrl* TimePickCtrl;
	
    //  int               m_show_id;
    //  int               m_hide_id;
	wxFileConfig        *m_pconfig;
	////@begin t member function declarations

    wxString GetDestination() const { return m_Destination ; }
    void SetDestination(wxString value) { m_Destination = value ; }

    wxString GetDraught() const { return m_Draught ; }
    void SetDraught(wxString value) { m_Draught = value ; }

    wxString GetPersons() const { return m_Persons ; }
    void SetPersons(wxString value) { m_Persons = value ; }

    wxString GetEtaDate() const { return m_EtaDate ; }
    void SetEtaDate(wxString value) { m_EtaDate = value ; }

    wxString GetEtaTime() const { return m_EtaTime ; }
    void SetEtaTime(wxString value) { m_EtaTime = value ; }
	unsigned char ComputeChecksum( wxString sentence ) const;
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end t member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();
	
};
///////////////////////////////////////////////////////////////////////////////
/// Class PreferenceDlg
///////////////////////////////////////////////////////////////////////////////
class PreferenceDlg : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
		wxButton* m_sdbSizer2Cancel;
	
	public:
		
		PreferenceDlg( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~PreferenceDlg();
		wxChoice* m_choice2;
		wxStringList m_AIS_type_list;
};

// class WXDLLEXPORT wxSpinButton;
// class WXDLLEXPORT wxTextCtrl;
// 
// enum wxTimeField {TIME_FIELD_HOUR, TIME_FIELD_MINUTE}; //, TIME_FIELD_SECOND, TIME_FIELD_AM_PM};
// 
// class TimePickerCtrl : public wxControl
// {
// public:
//     TimePickerCtrl() { Init(); }
// 	TimePickerCtrl(wxWindow *parent,
// 				wxWindowID id = wxID_ANY,
// 				const wxString& value = wxEmptyString,
// 				const wxPoint& pos = wxDefaultPosition,
// 				const wxSize& size = wxDefaultSize,
// 				long style = wxSP_ARROW_KEYS,
// 				const wxDateTime time = wxDefaultDateTime,
// 				const wxString& name = _("TimePickerCtrl"))
//     {
//         Init();
//         Create(parent, id, value, pos, size, style, time, name);
//     }
// 
// 	bool Create(wxWindow *parent,
// 				wxWindowID id = wxID_ANY,
// 				const wxString& value = wxEmptyString,
// 				const wxPoint& pos = wxDefaultPosition,
// 				const wxSize& size = wxDefaultSize,
// 				long style = wxSP_ARROW_KEYS,
// 				const wxDateTime time = wxDefaultDateTime,
// 				const wxString& name = _("TimePickerCtrl"));
// 
// 	virtual ~TimePickerCtrl();
// 
// 	//	operations
// 	/// This function sets the currently selected field
// 	void SetValue(int val);
// 
// 	/// This function sets the TimePickerCtrl's wxDateTime to the given wxDateTime
// 	void SetValue(wxDateTime dt);
// 
// 	/// This function sets the minimum and maximum values allowed in the currently selected field
// 	void SetRange(int min, int max);
// 
// 	/// This function highlights the text in the TimePickerCtrl's associated wxTextCtrl between the given indices
// 	void SetSelection(long from, long to) const {m_text->SetSelection(from,to);}
// 
//     // accessors
//     /// This function returns the value of the currently selected field
//     int GetValue() const;
// 
//     /// This function returns the minimum value allowed in the currently selected field
//     int GetMin() const;
// 
//     /// This function returns the maximum value allowed in the currently selected field
//     int GetMax() const;
// 
//     /// This function returns the wxDateTime currently entered in the TimePickerCtrl
//     wxDateTime GetDateTime() const {return m_time;}
// 
//     // implementation from now on
// 
//     // forward these functions to all subcontrols
//     virtual bool Enable(bool enable = true);
// 	virtual bool Show(bool show = true);
// 	virtual bool Reparent(wxWindow *newParent);
// 
//     // get the subcontrols
//     wxTextCtrl *GetText() const { return m_text; }
//     wxSpinButton *GetSpinButton() const { return m_btn; }
// 
// 	unsigned short GetHour() const;
// 	unsigned short GetMinute() const {return m_time.GetMinute();}
// 	unsigned short GetSecond() const {return m_time.GetSecond();}
//    /// Returns true if the time contained in the control falls between noon and just before midnight
// 	bool pmQ() const {return m_time.GetHour()>=12;}
// 
// 	bool SetHour(unsigned short h);
// 	bool SetMinute(unsigned short m);
// 	bool SetSecond(unsigned short s);
// 
// 	/// Get which field is currently selected
// 	wxTimeField GetTimeField() const {return m_timeField;}
// 
//    /// Set which field is currently selected
// 	bool SetTimeField(wxTimeField f);
// 
//     /// Put the time value of the string in the text control into time and return
//     /// true or return false if the text ctrl doesn't contain a valid time.
//     bool GetTextValue(wxDateTime* const time) const;
// 
// protected:
//     /// Override the base class virtuals involved into geometry calculations.
// 	wxSize DoGetBestSize() const;
// 	void DoMoveWindow(int x, int y, int width, int height);
// 
//     /// Common part of all constructors
//     void Init();
// 
// private:
//     // the subcontrols
// 	wxTextCtrl *m_text;
// 	wxSpinButton *m_btn;
// 	wxTimeField m_timeField;
// 	wxDateTime m_time;
// 	wxString m_format;
// 
// private:
//     DECLARE_DYNAMIC_CLASS(TimePickerCtrl)
// };
// 
// class TimePickerEvent : public wxEvent
// {
// public:
// 	TimePickerEvent(wxWindow* win = (wxWindow*)NULL);
// 	wxEvent* Clone() const {return new TimePickerEvent(*this);}
// 
// 	DECLARE_DYNAMIC_CLASS(TimePickerEvent)
// };
// 
// typedef void (wxEvtHandler::*TimePickerEventFunction)(TimePickerEvent&);
// 
// BEGIN_DECLARE_EVENT_TYPES()
// 	DECLARE_EVENT_TYPE(ptb3EVT_TIMEPICKEREVENT,1)
// END_DECLARE_EVENT_TYPES()
// 
// #define EVT_TIMEPICKER(func)                              \
// 	DECLARE_EVENT_TABLE_ENTRY( ptb3EVT_TIMEPICKEREVENT,      \
// 		-1,                                    \
// 		-1,                                    \
// 		(wxObjectEventFunction)                \
// 		(TimePickerEventFunction) & func,              \
// 		(wxObject *) NULL ),


#endif



