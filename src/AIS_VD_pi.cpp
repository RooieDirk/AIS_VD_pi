/******************************************************************************
 * updated: 11-02-2014  
 * Project:  OpenCPN
 * Purpose:  AIS_VD Plugin
 * Author:   Dirk Smits
 *
 ***************************************************************************
 *   Copyright (C) 2014 by Dirk Smits                                      *
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


#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
  #include "wx/wx.h"
#endif //precompiled headers

#include "AIS_VD_pi.h"
#include "default_pi.xpm"
#include "wx/spinbutt.h"
#include "timepickerctrl.h"

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return new aisvd_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

aisvd_pi::aisvd_pi(void *ppimgr):opencpn_plugin_19(ppimgr)
{
      // Create the PlugIn icons
      m_pplugin_icon = new wxBitmap(default_pi);
	  
      m_event_handler = new aisvd_pi_event_handler(this);
      m_pconfig = GetOCPNConfigObject();
      LoadConfig();
}

aisvd_pi::~aisvd_pi()
{
      delete m_pplugin_icon;
}

int aisvd_pi::Init(void)
{
	  AddLocaleCatalog( _T("opencpn-AIS_VD_pi") );
	  prefDlg = NULL;
      return ( INSTALLS_TOOLBOX_PAGE | WANTS_PREFERENCES | WANTS_CONFIG );
}

bool aisvd_pi::DeInit(void)
{
	  SaveConfig();
      return true;
}

int aisvd_pi::GetAPIVersionMajor()
{
      return MY_API_VERSION_MAJOR;
}

int aisvd_pi::GetAPIVersionMinor()
{
      return MY_API_VERSION_MINOR;
}

int aisvd_pi::GetPlugInVersionMajor()
{
      return PLUGIN_VERSION_MAJOR;
}

int aisvd_pi::GetPlugInVersionMinor()
{
      return PLUGIN_VERSION_MINOR;
}

wxBitmap *aisvd_pi::GetPlugInBitmap()
{
      return m_pplugin_icon;
}

wxString aisvd_pi::GetCommonName()
{
      return _("AIS_VD");
}

wxString aisvd_pi::GetShortDescription()
{
      return _("AIS Voyage Data");
}

wxString aisvd_pi::GetLongDescription()
{
      return _("Set the static voyage data in the AIS class A tranceiver");
}

void aisvd_pi::SetNMEASentence(wxString &sentence)
{
}


void aisvd_pi::ShowPreferencesDialog( wxWindow* parent )
{
	if (!prefDlg) 
		prefDlg = new PreferenceDlg(parent);
	if ( prefDlg->ShowModal() == wxID_OK )
		AIS_type = prefDlg->m_choice2->GetString(prefDlg->m_choice2->GetSelection());
	prefDlg->~PreferenceDlg();
}

void aisvd_pi::SetPluginMessage(wxString &message_id, wxString &message_body)
{

}
//      Options Dialog Page management
void aisvd_pi::OnSetupOptions(){
   // Set validators
		const wxString AllowDest[] = { 
			wxT("a"), wxT("b"), wxT("c"), wxT("d"), wxT("e"), wxT("f"), wxT("g"), wxT("h"), wxT("i"), wxT("j"), wxT("k"), wxT("l"), wxT("m"), wxT("n"), wxT("o"), wxT("p"), wxT("q"), wxT("r"), wxT("s"), wxT("t"), wxT("u"), wxT("v"), wxT("w"), wxT("x"), wxT("y"), wxT("z"), wxT("A"), wxT("B"), wxT("C"), wxT("D"), wxT("E"), wxT("F"), wxT("G"), wxT("H"), wxT("I"), wxT("J"), wxT("K"), wxT("L"), wxT("M"), wxT("N"), wxT("O"), wxT("P"), wxT("Q"), wxT("R"), wxT("S"), wxT("T"), wxT("U"), wxT("V"), wxT("W"), wxT("X"), wxT("Y"), wxT("Z"),wxT(" "), wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT(":"), wxT(";"), wxT("<"), wxT(">"), wxT("?"), wxT("@"), wxT("["), wxT("]"), wxT("!"), wxT(","), wxT("."), wxT("-"), wxT("="), wxT("*"), wxT("#")};           
		wxArrayString* ArrayAllowDest = new wxArrayString(78, AllowDest);
		wxTextValidator DestVal( wxFILTER_INCLUDE_CHAR_LIST, & m_Destination);
		DestVal.SetIncludes(*ArrayAllowDest);
    //m_DestTextCtrl->SetValidator( DestVal);
	
		const wxString AllowDraught[] = { 
			wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT(".")};
		wxArrayString* ArrayAllowDraught = new wxArrayString(11, AllowDraught);
		wxTextValidator DraughtVal( wxFILTER_INCLUDE_CHAR_LIST, & m_Draught);
		DraughtVal.SetIncludes(*ArrayAllowDraught);	
    //DraughtTextCtrl->SetValidator( DraughtVal );
    
		const wxString AllowPersons[] = { 
			wxT("0"), wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9")};
		wxArrayString* ArrayAllowPersons = new wxArrayString(10, AllowPersons);
		wxTextValidator PersonsVal( wxFILTER_INCLUDE_CHAR_LIST, & m_Persons);
		PersonsVal.SetIncludes(*ArrayAllowPersons);		
	//PersonsTextCtrl->SetValidator( PersonsVal );
	
    //  Create the AISVD Options panel, and load it

    wxScrolledWindow *m_AIS_VoyDataWin = AddOptionsPage( PI_OPTIONS_PARENT_SHIPS, _("AIS static") );

    wxStaticBox* itemStaticBoxSizer3Static = new wxStaticBox(m_AIS_VoyDataWin, wxID_ANY, _("Set static voyage data to AIS"));
    wxStaticBoxSizer* itemStaticBoxSizer3 = new wxStaticBoxSizer(itemStaticBoxSizer3Static, wxVERTICAL);
    m_AIS_VoyDataWin->SetSizer(itemStaticBoxSizer3);

    wxFlexGridSizer* itemFlexGridSizer4 = new wxFlexGridSizer(0, 2, 10, 5);
    itemStaticBoxSizer3->Add(itemFlexGridSizer4, 0, wxGROW|wxALL, 20);

    wxStaticText* itemStaticText5 = new wxStaticText( m_AIS_VoyDataWin, wxID_STATIC, _("Navigational status"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText5, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxArrayString StatusChoiceStrings;

	StatusChoiceStrings.Add(_("At anchor"));
    StatusChoiceStrings.Add(_("Underway using engine"));
    StatusChoiceStrings.Add(_("Not under command"));
    StatusChoiceStrings.Add(_("Restricted manoeuverability"));
	StatusChoiceStrings.Add(_("Constrained by draught"));
    StatusChoiceStrings.Add(_("Moored"));
    StatusChoiceStrings.Add(_("Aground"));
    StatusChoiceStrings.Add(_("Engaged in Fishing"));
	StatusChoiceStrings.Add(_("Under way sailing"));
    StatusChoice = new wxChoice( m_AIS_VoyDataWin, ID_CHOICE, wxDefaultPosition, wxDefaultSize, StatusChoiceStrings, 0 );
    StatusChoice->SetStringSelection(_("1"));
    itemFlexGridSizer4->Add(StatusChoice, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText7 = new wxStaticText( m_AIS_VoyDataWin, wxID_STATIC, _("Destination"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_DestTextCtrl = new wxTextCtrl( m_AIS_VoyDataWin, ID_TEXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, DestVal );
	m_DestTextCtrl->SetMaxLength( 20 );
    itemFlexGridSizer4->Add(m_DestTextCtrl, 0, wxGROW|wxALIGN_CENTER_VERTICAL|wxALL, 5);
	
	
    wxStaticText* itemStaticText9 = new wxStaticText( m_AIS_VoyDataWin, wxID_STATIC, _("Draught (m)"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    DraughtTextCtrl = new wxTextCtrl( m_AIS_VoyDataWin, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, DraughtVal );
    itemFlexGridSizer4->Add(DraughtTextCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText11 = new wxStaticText( m_AIS_VoyDataWin, wxID_STATIC, _("No. of Persons onboard"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    PersonsTextCtrl = new wxTextCtrl( m_AIS_VoyDataWin, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, PersonsVal );
    itemFlexGridSizer4->Add(PersonsTextCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText13 = new wxStaticText( m_AIS_VoyDataWin, wxID_STATIC, _("eta date"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText13, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    DatePicker = new wxDatePickerCtrl( m_AIS_VoyDataWin, ID_DATECTRL, wxDateTime(), wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT );
    itemFlexGridSizer4->Add(DatePicker, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxStaticText* itemStaticText15 = new wxStaticText( m_AIS_VoyDataWin, wxID_STATIC, _("eta Time"), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(itemStaticText15, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    TimePickCtrl = new wxTimePickerCtrl( m_AIS_VoyDataWin, ID_TIMECTR, wxDateTime(), wxDefaultPosition, wxDefaultSize, 0 );
    itemFlexGridSizer4->Add(TimePickCtrl, 0, wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer17 = new wxBoxSizer(wxHORIZONTAL);
    itemStaticBoxSizer3->Add(itemBoxSizer17, 0, wxGROW|wxALL, 5);
/*
    wxButton* itemButton18 = new wxButton( m_AIS_VoyDataWin, ID_BUTTON, _("Read from AIS"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(itemButton18, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);
*/
    wxButton* SendBtn = new wxButton( m_AIS_VoyDataWin, ID_BUTTON1, _("Send to AIS"), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer17->Add(SendBtn, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

 
	
	//  Connect to Events
    SendBtn->Connect( wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(aisvd_pi_event_handler::OnSendBtnClick), NULL, m_event_handler );

////@end t content construction

    m_AIS_VoyDataWin->Layout();
	//Update values in Controls
	m_DestTextCtrl->SetValue(m_Destination);
	DraughtTextCtrl->SetValue(m_Draught);
	PersonsTextCtrl->SetValue(m_Persons);
	DatePicker->SetValue(m_EtaDateTime);
	TimePickCtrl->SetValue(m_EtaDateTime);
}

bool aisvd_pi::LoadConfig( void )
{
    wxFileConfig *pConf = (wxFileConfig *) m_pconfig;
    
    if( pConf ) {
		wxString temp;
        pConf->SetPath( _T("/PlugIns/AIS_VD") );       
        pConf->Read( _T("Destination"), &m_Destination );
        pConf->Read( _T("Draught"), &m_Draught );
        pConf->Read( _T("Persons"), &m_Persons);
		pConf->Read( _T("Eta"), &temp);
		m_EtaDateTime.ParseDateTime(temp);
    }        
     
    return true;
}

bool aisvd_pi::SaveConfig( void )
{
    wxFileConfig *pConf = (wxFileConfig *) m_pconfig;
    
    if( pConf ) {
        pConf->SetPath( _T("/PlugIns/AIS_VD") );        
        pConf->Write( _T("Destination"), m_Destination );
        pConf->Write( _T("Draught"), m_Draught );
        pConf->Write( _T("Persons"), m_Persons );
		pConf->Write( _T("Eta"), m_EtaDateTime.Format() );
    }

    return true;
}
void aisvd_pi::OnCloseToolboxPanel(int page_sel, int ok_apply_cancel)
{
    
}
void aisvd_pi::UpdateDestVal()
{
	m_Destination = m_DestTextCtrl->GetValue();
	m_Destination = m_Destination.MakeUpper();
	m_DestTextCtrl->SetValue( m_Destination );
}
void aisvd_pi::UpdateDraught()
{
	m_Draught = DraughtTextCtrl->GetValue();
	double temp;
	m_Draught.ToDouble(&temp);
	if ( temp >= 25.5 )
		temp = 25.5;
	m_Draught = wxString::Format(wxT("%2.1f"), temp);
	DraughtTextCtrl->SetValue(m_Draught);
}
void aisvd_pi::UpdatePersons()
{
	m_Persons = PersonsTextCtrl->GetValue();
	long temp;
	m_Persons.ToLong(&temp);
	if ( temp >= 8100 )
		temp = 8100;
	m_Persons = wxString::Format(wxT("%i"), temp);
	PersonsTextCtrl->SetValue(m_Persons);
}
void aisvd_pi::UpdateEta()
{
	m_EtaDateTime = DatePicker->GetValue();
	m_EtaDateTime.SetHour( TimePickCtrl->GetValue().GetHour() );
	m_EtaDateTime.SetMinute( TimePickCtrl->GetValue().GetMinute() );
}
void aisvd_pi::SendSentence()
{
	wxString S;
	S= _("$ECVSD,"); // EC for Electronic Chart
	
	S.Append( wxString::Format(_("%d,"), 37)); //TODO Type of ship and cargo category
	S.Append( m_Draught ); S.Append( _(",") );
	S.Append( m_Persons ); S.Append( _(",") );
	S.Append( m_Destination ); S.Append( _(",") );
	S.Append( wxString::Format(_("%02d%02d,"), m_EtaDateTime.GetHour(), m_EtaDateTime.GetMinute() )); //eta time HHmm
	S.Append( wxString::Format(_("%d,"), m_EtaDateTime.GetDay() )); // eta Day
	S.Append( wxString::Format(_("%d,"), m_EtaDateTime.GetMonth()+1 )); // eta Month
	S.Append( wxString::Format(_("%d,"), StatusChoice->GetSelection() )); //Navigation status
	S.Append( wxString::Format(_("%d"), 0 )); // TODO Regional application flags, 0 to 15
	S.Append( _("*")); // End data
	S.Append( wxString::Format(_("%02X"), ComputeChecksum(S) ));
	S += _T("\r\n");
	wxPuts(S);
	PushNMEABuffer(S); //finaly send NMEA string
}

unsigned char aisvd_pi::ComputeChecksum( wxString sentence ) const
{
    unsigned char calculated_checksum = 0;
    for(wxString::const_iterator i = sentence.begin()+1; i != sentence.end() && *i != '*'; ++i)
        calculated_checksum ^= static_cast<unsigned char> (*i);

   return( calculated_checksum );
}


//The preference dialog
PreferenceDlg::PreferenceDlg( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 0, 2, 0, 0 );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Type of AIS"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	gSizer2->Add( m_staticText2, 0, wxALL, 5 );
	
	wxString m_choice2Choices[] = { wxT("True Heading Carbon Pro") };
	int m_choice2NChoices = sizeof( m_choice2Choices ) / sizeof( wxString );
	m_choice2 = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2NChoices, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	gSizer2->Add( m_choice2, 0, wxALL, 5 );
	
	
	bSizer2->Add( gSizer2, 1, wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer2->AddButton( m_sdbSizer2Cancel );
	m_sdbSizer2->Realize();
	
	bSizer2->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );
	
	this->Centre( wxBOTH );
}

PreferenceDlg::~PreferenceDlg()
{
}

// An Event handler class to catch events from S63 UI dialog
//      Implementation

aisvd_pi_event_handler::aisvd_pi_event_handler(aisvd_pi *parent)
{
    m_parent = parent;
}

aisvd_pi_event_handler::~aisvd_pi_event_handler()
{
}


void aisvd_pi_event_handler::OnSendBtnClick( wxCommandEvent &event )
{
    m_parent->UpdateDestVal();
	m_parent->UpdateDraught();
	m_parent->UpdatePersons();
	m_parent->UpdateEta();
	m_parent->SaveConfig();
	m_parent->SendSentence();
}


// ----------------------------------------------------------------------------
// constants
// ----------------------------------------------------------------------------

// the margin between the text control and the spin
static const wxCoord MARGIN = 2;

// // ----------------------------------------------------------------------------
// // TimePickerCtrlText: text control used by spin control
// // ----------------------------------------------------------------------------
// 
// class TimePickerCtrlText : public wxTextCtrl
// {
// public:
//     TimePickerCtrlText(TimePickerCtrl *timepicker, const wxString& value)
//         : wxTextCtrl(timepicker->GetParent(), wxID_ANY, value)
//     {
//         m_timepicker = timepicker;
//         m_keyPressedQ = false;
// 
//         // remove the default minsize, the spinctrl will have one instead
//         SetSizeHints(wxDefaultCoord,wxDefaultCoord);
//     }
// 
// protected:
//     void OnTextChange(wxCommandEvent& event)
//     {
//       wxWindow* p = m_timepicker->GetParent();
// 		TimePickerEvent tpEvent(p);
// 		p->AddPendingEvent(tpEvent);
// 
//         event.Skip();
//     }
// 
//     void OnMouse(wxMouseEvent& event)
//     {
//     	if(event.GetEventType()==wxEVT_LEFT_DOWN)
//     	{
// 			wxString s = GetValue();
// 			long int pos1 = s.Find(':');
// 			int w,h;
// 			GetTextExtent(s.SubString(0,pos1),&w,&h);
// 			int hr_min_boundary = w;
// 			GetTextExtent(s,&w,&h);
// 			int min_sec_boundary = w;
// 			int x, y;
//     		m_keyPressedQ = false;
//     		SetFocus();
//     		event.GetPosition(&x,&y);
//     		if(x>hr_min_boundary&&x<min_sec_boundary)
// 				m_timepicker->SetTimeField(TIME_FIELD_MINUTE);
// 			else
// 				m_timepicker->SetTimeField(TIME_FIELD_HOUR);
// 		}
//     	//event.Skip();
//     }
// 
//     bool ProcessEvent(wxEvent &event)
//     {
//         // Hand button down events to TimePickerCtrl. Doesn't work.
//         if (event.GetEventType() == wxEVT_LEFT_DOWN && m_timepicker->ProcessEvent( event ))
//             return true;
// 
//         return wxTextCtrl::ProcessEvent( event );
//     }
// 
//     void OnChar(wxKeyEvent& event)
//     {
//     	int keycode = event.GetKeyCode();
//     	if(keycode>=(int)'0'&&keycode<=(int)'9')
//     	{
//     		int val = atoi((char*)(&keycode));
//     		if(!m_keyPressedQ)
//     		{
//     			if(m_timepicker->pmQ()&&m_timepicker->GetTimeField()==TIME_FIELD_HOUR)
// 					val += 12;
//     			m_timepicker->SetValue(val);
// 				m_keyPressedQ = true;
//     		}
// 			else // m_keyPressedQ
// 			{
// 				int oldHour;
// 				switch(m_timepicker->GetTimeField())
// 				{
// 				case TIME_FIELD_HOUR:
// 					oldHour = (m_timepicker->pmQ())?m_timepicker->GetHour()-12:m_timepicker->GetHour();
// 					val += 10*oldHour;
// 					break;
// 				case TIME_FIELD_MINUTE:
// 					val += 10*(m_timepicker->GetMinute()%10);
// 					break;
// 				
// 				}
// 				m_timepicker->SetValue(val);
// 				m_keyPressedQ = false;
// 			}
//     	}
//     	
//     	else if(keycode==WXK_LEFT)
//     	{
//     		m_keyPressedQ = false;
//     		switch(m_timepicker->GetTimeField())
//     		{
// 			case TIME_FIELD_HOUR:
// 				m_timepicker->SetSelection(0,2);
// 				break;
// 			case TIME_FIELD_MINUTE:
// 				m_timepicker->SetTimeField(TIME_FIELD_HOUR);
// 				break;
// 			
//     		}
//     	}
//     	else if(keycode==WXK_RIGHT)
//     	{
//     		m_keyPressedQ = false;
//     		switch(m_timepicker->GetTimeField())
//     		{
// 			case TIME_FIELD_HOUR:
// 				m_timepicker->SetTimeField(TIME_FIELD_MINUTE);
// 				break;
// 			case TIME_FIELD_MINUTE:
// 				m_timepicker->SetTimeField(TIME_FIELD_HOUR);
// 				break;
// 			
//     		}
//     	}
//     	else if(keycode==WXK_UP)
//     	{
//     		m_keyPressedQ = false;
//     		switch(m_timepicker->GetTimeField())
//     		{
// 			case TIME_FIELD_HOUR:
// 				m_timepicker->SetValue(m_timepicker->GetHour()+1);
// 				break;
// 			case TIME_FIELD_MINUTE:
// 				m_timepicker->SetValue(m_timepicker->GetMinute()+1);
// 				break;
// 			
//     		}
//     	}
//     	else if(keycode==WXK_DOWN)
//     	{
//     		m_keyPressedQ = false;
//     		switch(m_timepicker->GetTimeField())
//     		{
// 			case TIME_FIELD_HOUR:
// 				m_timepicker->SetValue(m_timepicker->GetHour()-1);
// 				break;
// 			case TIME_FIELD_MINUTE:
// 				m_timepicker->SetValue(m_timepicker->GetMinute()-1);
// 				break;
// 			
//     		}
//     	}
//     }
// 
// private:
//     TimePickerCtrl *m_timepicker;
//     bool m_keyPressedQ;
// 
//     DECLARE_EVENT_TABLE()
// };
// 
// BEGIN_EVENT_TABLE(TimePickerCtrlText, wxTextCtrl)
//     EVT_TEXT(wxID_ANY, TimePickerCtrlText::OnTextChange)
//     EVT_MOUSE_EVENTS(TimePickerCtrlText::OnMouse)
//     EVT_CHAR(TimePickerCtrlText::OnChar)
// END_EVENT_TABLE()
// 
// // ----------------------------------------------------------------------------
// // TimePickerCtrlButton: spin button used by time picker control
// // ----------------------------------------------------------------------------
// 
// class TimePickerCtrlButton : public wxSpinButton
// {
// public:
//     TimePickerCtrlButton(TimePickerCtrl *timepicker, int style)
//         : wxSpinButton(timepicker->GetParent())
//     {
//         m_timepicker = timepicker;
// 
//         SetWindowStyle(style | wxSP_VERTICAL);
// 
//         // remove the default minsize, the spinctrl will have one instead
//         SetSizeHints(wxDefaultCoord,wxDefaultCoord);
//     }
// 
// protected:
//     void OnSpinButton(wxSpinEvent& eventSpin)
//     {
//     	m_timepicker->GetText()->SetFocus();
//     	m_timepicker->SetValue(eventSpin.GetPosition());
//         wxCommandEvent event(wxEVT_COMMAND_SPINCTRL_UPDATED, m_timepicker->GetId());
//         event.SetEventObject(m_timepicker);
//         event.SetInt(eventSpin.GetPosition());
// 
//         m_timepicker->GetEventHandler()->ProcessEvent(event);
// 
//         eventSpin.Skip();
//     }
// 
// private:
//     TimePickerCtrl *m_timepicker;
// 
//     DECLARE_EVENT_TABLE()
// };
// 
// BEGIN_EVENT_TABLE(TimePickerCtrlButton, wxSpinButton)
//     EVT_SPIN(wxID_ANY, TimePickerCtrlButton::OnSpinButton)
// END_EVENT_TABLE()
// 
// IMPLEMENT_DYNAMIC_CLASS(TimePickerCtrl, wxControl)
// 
// void TimePickerCtrl::Init()
// {
//     m_text = NULL;
//     m_btn = NULL;
//     m_timeField = TIME_FIELD_HOUR;
// }
// 
// bool TimePickerCtrl::Create(	wxWindow *parent,
// 								wxWindowID id,
// 								const wxString& value,
// 								const wxPoint& pos,
// 								const wxSize& size,
// 								long style,
// 								const wxDateTime time,
// 								const wxString& name)
// {
//     if ( !wxControl::Create(parent, id, wxDefaultPosition, wxDefaultSize, style,
//                             wxDefaultValidator, name) )
//     {
//         return false;
//     }
// 
// 	m_text = new TimePickerCtrlText(this,value);
// 	m_btn = new TimePickerCtrlButton(this,style);
// 
// 	if(!value.empty())
// 	{
// 		m_text->ChangeValue(value);
// 		if(time!=wxInvalidDateTime)
// 			m_time = time;
// 		else
// 			if(!m_time.ParseTime(value))
// 				m_time.Set((unsigned short)24);
// 	}
// 	else
// 	{
// 		if(time!=wxInvalidDateTime)
// 			m_time = time;
// 		else
// 			m_time.Set((unsigned short)24);
// 	}
// 	switch(m_timeField)
// 	{
// 	case TIME_FIELD_HOUR:
// 		m_btn->SetRange(0, 23);
// 		m_btn->SetValue(m_time.GetHour());
// 		break;
// 	case TIME_FIELD_MINUTE:
// 		m_btn->SetRange(0,59);
// 		m_btn->SetValue(m_time.GetMinute());
// 		break;
// 	}
//     SetInitialSize(size);
//     Move(pos);
//     if(!value.empty())
// 		m_text->ChangeValue(value);
//     else
// 		m_text->ChangeValue(wxString::Format(_("%02d:%02d"),GetHour(),GetMinute()));
// 
// 	// have to disable this window to avoid interfering it with message
//     // processing to the text and the button... but pretend it is enabled to
//     // make IsEnabled() return true
//     wxControl::Enable(false); // don't use non virtual Disable() here!
//     m_isEnabled = true;
// 
//     // we don't even need to show this window itself - and not doing it avoids
//     // that it overwrites the text control
//     wxControl::Show(false);
//     m_isShown = true;
//     return true;
// }
// 
// TimePickerCtrl::~TimePickerCtrl()
// {
// 	delete m_text;
// 	m_text = NULL;
// 	delete m_btn;
// 	m_btn = NULL;
// }
// 
// void TimePickerCtrl::DoMoveWindow(int x, int y, int width, int height)
// {
//     wxControl::DoMoveWindow(x, y, width, height);
// 
//     // position the subcontrols inside the client area
//     wxSize sizeBtn = m_btn->GetSize();
// 
//     wxCoord wText = width - sizeBtn.x;
//     m_text->SetSize(x, y, wText, height);
//     m_btn->SetSize(x + wText + MARGIN, y, wxDefaultCoord, height);
// }
// 
// void TimePickerCtrl::SetValue(int val)
// {
//     wxCHECK_RET( m_btn, _T("invalid call to TimePickerCtrl::SetValue") );
//     switch(m_timeField)
//     {
// 	case TIME_FIELD_HOUR:
// 		if(val>=0&&val<=23)
// 		{
// 			m_btn->SetValue(val);
// 			m_time.SetHour(val);
// 		}
// 		break;
// 	case TIME_FIELD_MINUTE:
// 		if(val>=0&&val<=59)
// 		{
// 			m_btn->SetValue(val);
// 			m_time.SetMinute(val);
// 		}
// 			break;
//     }
// 	m_text->SetValue(wxString::Format(_("%02d:%02d"),GetHour(),GetMinute()));
// 	switch(m_timeField)
// 	{
// 	case TIME_FIELD_HOUR:
// 		SetSelection(0,2);
// 		break;
// 	case TIME_FIELD_MINUTE:
// 		SetSelection(3,5);
// 		break;
// 	}
// }
// 
// void TimePickerCtrl::SetValue(wxDateTime dt)
// {
// 	m_time = dt;
// 	//int val;
//     switch(m_timeField)
//     {
// 	case TIME_FIELD_HOUR:
// 		m_btn->SetValue(m_time.GetHour());
// 		break;
// 	case TIME_FIELD_MINUTE:
// 		m_btn->SetValue(m_time.GetMinute());
// 		break;	
//     }
// 	m_text->SetValue(wxString::Format(_("%02d:%02d"),GetHour(),GetMinute()));
// 	switch(m_timeField)
// 	{
// 	case TIME_FIELD_HOUR:
// 		SetSelection(0,2);
// 		break;
// 	case TIME_FIELD_MINUTE:
// 		SetSelection(3,5);
// 		break;	
// 	}
// }
// 
// void TimePickerCtrl::SetRange(int min, int max)
// {
//     wxCHECK_RET( m_btn, _T("invalid call to wxSpinCtrlg::SetRange") );
// 
//     m_btn->SetRange(min, max);
// }
// 
// wxSize TimePickerCtrl::DoGetBestSize() const
// {
//     wxSize sizeBtn = m_btn->GetBestSize(),
//            sizeText = m_text->GetBestSize();
// 
//     return wxSize(sizeBtn.x + sizeText.x + MARGIN, sizeText.y);
// }
// 
// // ----------------------------------------------------------------------------
// // value and range access
// // ----------------------------------------------------------------------------
// 
// bool TimePickerCtrl::GetTextValue(wxDateTime* const time) const
// {
// 	if(m_time.IsValid())
// 	{
// 		*time = m_time;
// 		return true;
// 	}
//     return false;
// }
// 
// int TimePickerCtrl::GetValue() const
// {
//     return m_btn ? m_btn->GetValue() : 0;
// }
// 
// int TimePickerCtrl::GetMin() const
// {
//     return m_btn ? m_btn->GetMin() : 0;
// }
// 
// int TimePickerCtrl::GetMax() const
// {
//     return m_btn ? m_btn->GetMax() : 0;
// }
// 
// // ----------------------------------------------------------------------------
// // operations forwarded to the subcontrols
// // ----------------------------------------------------------------------------
// 
// bool TimePickerCtrl::Enable(bool enable)
// {
//     if ( !wxControl::Enable(enable) )
//         return false;
// 
//     m_btn->Enable(enable);
//     m_text->Enable(enable);
// 
//     return true;
// }
// 
// bool TimePickerCtrl::Show(bool show)
// {
//     if ( !wxControl::Show(show) )
//         return false;
// 
//     // under GTK Show() is called the first time before we are fully
//     // constructed
//     if ( m_btn )
//     {
//         m_btn->Show(show);
//         m_text->Show(show);
//     }
// 
//     return true;
// }
// 
// bool TimePickerCtrl::Reparent(wxWindow *newParent)
// {
//     if ( m_btn )
//     {
//         m_btn->Reparent(newParent);
//         m_text->Reparent(newParent);
//     }
// 
//     return true;
// }
// 
// bool TimePickerCtrl::SetHour(unsigned short h)
// {
// 	if(h<24)
// 	{
// 		m_time.SetHour(h);
// 		return true;
// 	}
// 	else
// 		return false;
// }
// 
// bool TimePickerCtrl::SetMinute(unsigned short m)
// {
// 	if(m<60)
// 	{
// 		m_time.SetMinute(m);
// 		return true;
// 	}
// 	else
// 		return false;
// }
// 
// bool TimePickerCtrl::SetSecond(unsigned short s)
// {
// 	if(s<60)
// 	{
// 		m_time.SetSecond(s);
// 		return true;
// 	}
// 	else
// 		return false;
// }
// 
// bool TimePickerCtrl::SetTimeField(wxTimeField f)
// {
// 	switch(f)
// 	{
// 	case TIME_FIELD_HOUR:
// 		m_btn->SetRange(0,23);
// 		m_btn->SetValue(GetHour());
// 		m_timeField = f;
// 		SetSelection(0,2);
// 		return true;
// 	case TIME_FIELD_MINUTE:
// 		m_btn->SetRange(0,59);
// 		m_btn->SetValue(GetMinute());
// 		m_timeField = f;
// 		SetSelection(3,5);
// 		return true;
// 	
// 	default:
// 		return false;
// 	}
// }
// 
// unsigned short TimePickerCtrl::GetHour() const
// {
// 	unsigned short h = m_time.GetHour();
// 	
// 		return h;
// }
// 
// IMPLEMENT_DYNAMIC_CLASS(TimePickerEvent, wxEvent)
// DEFINE_EVENT_TYPE(ptb3EVT_TIMEPICKEREVENT)
// 
// TimePickerEvent::TimePickerEvent(wxWindow* win)
// {
// 	SetEventType(ptb3EVT_TIMEPICKEREVENT);
// 	SetEventObject(win);
// }

