// Doxygen documentation follows:
/** @mainpage TimePickerCtrl
*
* @version 0.2
*
* @authors Paul Breen (greenbreen@yahoo.com); adapted from the generic wxSpinCtrl by Vadim Zeitlin
*
* @date January 3, 2011
* <hr>
* @section intro Introduction
TimePickerCtrl is a wxWidgets control for entering and displaying time information.  It's a composite control made up of a wxTextCtrl and a wxSpinButton.  The time is displayed in 12 hour format like 9:30:00 AM.  The user can change the time by selecting the field (hours, minutes, seconds, or AM/PM) they want to change and using the wxSpinCtrl's arrow buttons.  For anyone familiar with MFC, this control is similar to a CDateTimeCtrl with the DTS_TIMEFORMAT style.
* <hr>
* @section notes Release Notes
This control is still in a beta stage of development.  There are no known bugs yet, but it is not extensively tested.  The control was developed on 32-bit i386 Ubuntu 10.04 LTS Desktop version using wxWidgets 2.8.11.  It is also known to build on Windows Vista with wxWidgets 2.8.  I would appreciate any feedback on experiences with this control on other platforms, or any suggestions for improvement, etc.  If you do email me, please include the string "timepickerctrl" in the subject line so I can filter the message to the appropriate folder.  I can't promise I'll provide fixes or implement suggestions or even respond to email messages, but I'll try to be as responsive as I can with the time I have available, and it can't hurt to ask.

Currently the time format is fixed.  Depending on public interest and my available time, I may implement customization.
* <hr>
* @section requirements Requirements
wxWidgets 2.8 or higher.  May work with lower versions of wxWidgets, but this has not been tested.  Please email me with your experiences using this control in other versions of wxWidgets.
* <hr>
*
* @section license License
TimePickerCtrl is released under the wxWindows license.  Please see http://www.opensource.org/licenses/wxwindows.php for details.
*/ // End doxygen documentation


/////////////////////////////////////////////////////////////////////////////
// Name:        timepickerctrl.h
// Purpose:     generic TimePickerCtrl class
// Author:      Paul Breen; adapted from generic wxSpinCtrl by Vadim Zeitlin
// Modified by:
// Created:     January 3, 2011
// Copyright:   (c) Paul Breen
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef TIMEPICKERCTRL_H_INCLUDED
#define TIMEPICKERCTRL_H_INCLUDED


#endif // TIMEPICKERCTRL_H_INCLUDED
