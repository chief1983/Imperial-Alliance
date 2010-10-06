/*
 * Copyright (C) Volition, Inc. 1999.  All rights reserved.
 *
 * All source code herein is the property of Volition, Inc. You may not sell 
 * or otherwise commercially exploit the source or things you created based on the 
 * source.
 *
*/

/*
 * $Logfile: /Freespace2/code/Fred2/MissionNotesDlg.cpp $
 * $Revision: 1.18 $
 * $Date: 2004/04/29 03:49:14 $
 * $Author: wmcoolmon $
 *
 * Mission notes editor dialog box handling code
 *
 * $Log: MissionNotesDlg.cpp,v $
 * Revision 1.18  2004/04/29 03:49:14  wmcoolmon
 * Changed default subsys repair cap to 100% (Backwards compatibility)
 *
 * Revision 1.17  2004/04/29 03:35:18  wmcoolmon
 * Added Hull and Subsys repair ceiling fields to Mission Specs Dialog in FRED
 * Updated mission saving code to store both variables properly
 *
 * Revision 1.16  2004/03/15 12:14:46  randomtiger
 * Fixed a whole heap of problems with Fred introduced by changes to global vars.
 *
 * Revision 1.15  2004/01/14 06:28:39  Goober5000
 * made set-support-ship number align with general FS convention
 * --Goober5000
 *
 * Revision 1.14  2003/10/28 22:45:31  Goober5000
 * fixed some small bugs in the Mission Specs window where some things
 * stayed selected even after being cleared
 * --Goober5000
 *
 * Revision 1.13  2003/05/10 22:35:25  phreak
 * fixed minor save bug when dealing with custom loading screens
 *
 * Revision 1.12  2003/05/10 00:02:42  phreak
 * code to handle user interface when selecting custom loading screens
 *
 * Revision 1.11  2003/05/05 21:04:33  phreak
 * fixed bug where mission notes will be reverted to original
 * if the user tries to change the squad logo
 *
 * Revision 1.10  2003/03/19 22:49:59  Goober5000
 * yay mission flags :)
 * --Goober5000
 *
 * Revision 1.9  2003/01/19 07:02:15  Goober5000
 * fixed a bunch of bugs - "no-subspace-drive" should now work properly for
 * all ships, and all ships who have their departure anchor set to a capital ship
 * should exit to that ship when told to depart
 * --Goober5000
 *
 * Revision 1.8  2003/01/13 02:07:26  wmcoolmon
 * Removed the override checkbox + flag for ship trails and added a checkbox + flag to disable ship trails within the nebula, NO_NEB_TRAILS, to the Background dialog.
 *
 * Revision 1.7  2003/01/11 01:01:37  wmcoolmon
 * Added code for "Ship Trails override Nebula"
 *
 * Revision 1.6  2002/12/21 02:01:21  Goober5000
 * Added beam-free-all-by-default flag to FRED2
 * --Goober5000
 *
 * Revision 1.5  2002/08/15 04:35:44  penguin
 * Changes to build with fs2_open code.lib
 *
 * Revision 1.4  2002/08/15 01:06:34  penguin
 * Include filename reorg (to coordinate w/ fs2_open)
 *
 * Revision 1.3  2002/08/10 10:50:11  wmcoolmon
 * Added support ship hull repair code
 *
 * Revision 1.2  2002/07/16 02:48:54  wmcoolmon
 * Added code to toggle ship trails regardless of nebula
 *
 * Revision 1.1.1.1  2002/07/15 03:11:00  inquisitor
 * Initial FRED2 Checking
 *
 * 
 * 6     8/23/99 6:21p Jefff
 * added "no traitor" option to missions (and fred)
 * 
 * 5     8/23/99 5:04p Jefff
 * Added new mission flag to disable built-in messages from playing.
 * Added fred support as well.
 * 
 * 4     3/24/99 4:05p Dave
 * Put in support for assigning the player to a specific squadron with a
 * specific logo. Preliminary work for doing pos/orient checksumming in
 * multiplayer to reduce bandwidth.
 * 
 * 3     2/23/99 2:32p Dave
 * First run of oldschool dogfight mode.
 * 
 * 2     10/07/98 6:28p Dave
 * Initial checkin. Renamed all relevant stuff to be Fred2 instead of
 * Fred. Globalized mission and campaign file extensions. Removed Silent
 * Threat specific code.
 * 
 * 1     10/07/98 3:01p Dave
 * 
 * 1     10/07/98 3:00p Dave
 * 
 * 23    6/17/98 2:47p Hoffoss
 * Changed so missions are single, multi or training.  Not supporting
 * combos of the above anymore (in Fred).
 * 
 * 22    5/25/98 12:16p Hoffoss
 * Removed dogfight option from dialog.  No longer supported.
 * 
 * 21    5/18/98 1:56a Allender
 * respawn limit to 999 max
 * 
 * 20    5/05/98 11:05p Allender
 * ability to flag mission as "no promotion" where promotions and badges
 * are *not* granted even if they should be.  Slight fix to multiplayer
 * problem where locking_subsys is wrong for players current target
 * 
 * 19    4/03/98 12:17a Allender
 * new sexpression to detect departed or destroyed.  optionally disallow
 * support ships.  Allow docking with escape pods 
 * 
 * 18    3/26/98 5:24p Allender
 * put in respawn edit box into mission notes dialog.  Made loading of
 * missions/campaign happen when first entering the game setup screen.
 * 
 * 17    3/18/98 3:17p Allender
 * fix scramble checkbox
 * 
 * 16    3/18/98 10:27a Allender
 * fixed bug with missions always being tagged a single player regardless
 * of checkbox setting
 * 
 * 15    3/16/98 8:27p Allender
 * Fred support for two new AI flags -- kamikaze and no dynamic goals.
 * 
 * 14    3/09/98 4:30p Allender
 * multiplayer secondary weapon changes.  red-alert and cargo-known-delay
 * sexpressions.  Add time cargo revealed to ship structure
 * 
 * 13    2/09/98 9:25p Allender
 * team v team support.  multiple pools and breifings
 * 
 * 12    2/04/98 4:32p Allender
 * support for multiple briefings and debriefings.  Changes to mission
 * type (now a bitfield).  Bitfield defs for multiplayer modes
 * 
 * 11    1/02/98 4:55p Hoffoss
 * Added support for Mission_all_attack flag to Fred and loading/saving
 * code.
 * 
 * 10    9/30/97 5:56p Hoffoss
 * Added music selection combo boxes to Fred.
 * 
 * 9     8/11/97 3:19p Hoffoss
 * Implemented mission description.
 * 
 * 8     6/11/97 2:14p Hoffoss
 * Added game type (mission type) selection to Fred.
 * 
 * 7     5/20/97 2:28p Hoffoss
 * Added message box queries for close window operation on all modal
 * dialog boxes.
 * 
 * 6     5/06/97 2:43p Hoffoss
 * Fixed bug in Mission notes dialog, where window wasn't being destroyed.
 * 
 * 5     4/17/97 2:01p Hoffoss
 * All dialog box window states are saved between sessions now.
 * 
 * 4     2/21/97 5:34p Hoffoss
 * Added extensive modification detection and fixed a bug in initial
 * orders editor.
 * 
 * 3     2/17/97 5:28p Hoffoss
 * Checked RCS headers, added them were missing, changing description to
 * something better, etc where needed.
 *
 * $NoKeywords: $
 */

#include "stdafx.h"
#include "FRED.h"
#include "FREDDoc.h"
#include "MissionNotesDlg.h"
#include "Management.h"
#include "gamesnd/eventmusic.h"
#include "cfile/cfile.h"
#include ".\missionnotesdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define NO_SQUAD				"<none>"

// module globals to hold button information
CButton *coop, *team, *dogfight;

/////////////////////////////////////////////////////////////////////////////
// CMissionNotesDlg dialog

CMissionNotesDlg::CMissionNotesDlg(CWnd* pParent /*=NULL*/) : CDialog(CMissionNotesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMissionNotesDlg)
	m_created = _T("");
	m_modified = _T("");
	m_mission_notes = _T("");
	m_designer_name = _T("");
	m_mission_title = _T("");
	m_mission_desc = _T("");
	m_squad_filename = _T("");
	m_loading_640 = _T("");
	m_loading_1024 = _T("");
	m_squad_name = _T(NO_SQUAD);
	m_music = -1;
	m_full_war = FALSE;
	m_red_alert = FALSE;
	m_scramble = FALSE;
	m_num_respawns = 0;
	m_disallow_support = 0;
	m_no_promotion = FALSE;
	m_no_builtin_msgs = FALSE;
	m_no_traitor = FALSE;
	m_ship_trails = FALSE;
	m_support_repairs_hull = FALSE;
	m_beam_free_all_by_default = FALSE;
//	m_old_warp_effect = FALSE;
	m_no_briefing = FALSE;
	m_no_debriefing = FALSE;
	m_max_hull_repair_val = 0.0f;
	m_max_subsys_repair_val = 100.0f;
	//}}AFX_DATA_INIT
}

void CMissionNotesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMissionNotesDlg)
	DDX_Control(pDX, IDC_RESPAWN_SPIN, m_respawn_spin);
	DDX_Text(pDX, IDC_CREATED, m_created);
	DDX_Text(pDX, IDC_MODIFIED, m_modified);
	DDX_Text(pDX, IDC_MISSION_NOTES, m_mission_notes);
	DDX_Text(pDX, IDC_DESIGNER_NAME, m_designer_name);
	DDX_Text(pDX, IDC_MISSION_TITLE, m_mission_title);
	DDX_Text(pDX, IDC_MISSION_DESC, m_mission_desc);
	DDX_Text(pDX, IDC_SQUAD_LOGO, m_squad_filename);
	DDX_Text(pDX, IDC_SQUAD_NAME, m_squad_name);
	DDX_Text(pDX, IDC_LOADING_SCREEN640, m_loading_640);
	DDX_Text(pDX, IDC_LOADING_SCREEN1024, m_loading_1024);
	DDX_CBIndex(pDX, IDC_MUSIC, m_music);
	DDX_Check(pDX, IDC_FULL_WAR, m_full_war);
	DDX_Check(pDX, IDC_RED_ALERT, m_red_alert);
	DDX_Check(pDX, IDC_SCRAMBLE, m_scramble);
	DDX_Text(pDX, IDC_RESPAWNS, m_num_respawns);
	DDV_MinMaxUInt(pDX, m_num_respawns, 0, 999);
	DDX_Check(pDX, IDC_SUPPORT_ALLOWED, m_disallow_support);
	DDX_Check(pDX, IDC_NO_PROMOTION, m_no_promotion);
	DDX_Check(pDX, IDC_DISABLE_BUILTIN_MSGS, m_no_builtin_msgs);
	DDX_Check(pDX, IDC_NO_TRAITOR, m_no_traitor);
	DDX_Check(pDX, IDC_SHIP_TRAILS, m_ship_trails);
	DDX_Check(pDX, IDC_SUPPORT_REPAIRS_HULL, m_support_repairs_hull);
	DDX_Check(pDX, IDC_BEAM_FREE_ALL_BY_DEFAULT, m_beam_free_all_by_default);
	//DDX_Check(pDX, IDC_OLD_WARP_EFFECT, m_old_warp_effect);
	DDX_Check(pDX, IDC_NO_BRIEFING, m_no_briefing);
	DDX_Check(pDX, IDC_NO_DEBRIEFING, m_no_debriefing);
	DDX_Text(pDX, IDC_MAX_HULL_REPAIR_VAL, m_max_hull_repair_val);
	DDV_MinMaxFloat(pDX, m_max_hull_repair_val, 0, 100);
	DDX_Text(pDX, IDC_MAX_SUBSYS_REPAIR_VAL, m_max_subsys_repair_val);
	DDV_MinMaxFloat(pDX, m_max_subsys_repair_val, 0, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMissionNotesDlg, CDialog)
	//{{AFX_MSG_MAP(CMissionNotesDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_TRAINING, OnTraining)
	ON_BN_CLICKED(IDC_MULTI, OnMulti)
	ON_BN_CLICKED(IDC_SINGLE, OnSingle)
	ON_BN_CLICKED(IDC_SQUAD_LOGO_BUTTON, OnSquadLogo)
	ON_BN_CLICKED(IDC_LOADING_SCREEN_BUTTON640, OnLoad640)
	ON_BN_CLICKED(IDC_LOADING_SCREEN_BUTTON1024, OnLoad1024)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMissionNotesDlg message handlers

int CMissionNotesDlg::query_modified()
{
	if (m_mission_title != m_mission_title_orig){
		return 1;
	}
	if (m_designer_name != m_designer_name_orig){
		return 1;
	}
	if (m_mission_notes != m_mission_notes_orig){
		return 1;
	}
	if (m_mission_desc != m_mission_desc_orig){
		return 1;
	}
	if (Current_soundtrack_num != m_music - 1){
		return 1;
	}
	if (Mission_all_attack != m_full_war){
		return 1;
	}

	return 0;
}

void CMissionNotesDlg::OnOK()
{
	int new_m_type, flags, is_multi = 0, is_training = 0, is_single = 0;

	UpdateData();
	is_single = (((CButton *) GetDlgItem(IDC_SINGLE))->GetCheck() == 1);
	is_multi = (((CButton *) GetDlgItem(IDC_MULTI))->GetCheck() == 1);
	is_training = (((CButton *) GetDlgItem(IDC_TRAINING))->GetCheck() == 1);

	// deal with changing the mission type.  Code is done this way since training missions
	// just override anything else.
	new_m_type = 0;
	if (is_training) {
		new_m_type = MISSION_TYPE_TRAINING;
	} else {
		if (is_single){
			new_m_type = MISSION_TYPE_SINGLE;
		}

		if (is_multi) {
			new_m_type |= MISSION_TYPE_MULTI;
			if (coop->GetCheck()){
				new_m_type |= MISSION_TYPE_MULTI_COOP;
			} else if (team->GetCheck()){
				new_m_type |= MISSION_TYPE_MULTI_TEAMS;
			} else if(dogfight->GetCheck()){
				new_m_type |= MISSION_TYPE_MULTI_DOGFIGHT;
			} else {
				Int3();			// get allender -- multiplayer mode not set!!!
			}
		}
	}

	if (!new_m_type) {
		MessageBox("You must select the game type: training, single, or multiplayer", "Error");
		return;
	}

	MODIFY(The_mission.game_type, new_m_type );
	MODIFY(The_mission.red_alert, m_red_alert );
	MODIFY(The_mission.scramble, m_scramble );
	MODIFY(The_mission.num_respawns, (int)m_num_respawns );
	MODIFY(The_mission.support_ships.max_support_ships, (m_disallow_support) ? 0 : -1);
	MODIFY(The_mission.support_ships.max_hull_repair_val, m_max_hull_repair_val);
	MODIFY(The_mission.support_ships.max_subsys_repair_val, m_max_subsys_repair_val);

	// set the flags for no promotion
	flags = The_mission.flags;
	if ( m_no_promotion ) {
		The_mission.flags |= MISSION_FLAG_NO_PROMOTION;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_PROMOTION;
	}

	// set flags for no builtin messages
	if ( m_no_builtin_msgs ) {
		The_mission.flags |= MISSION_FLAG_NO_BUILTIN_MSGS;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_BUILTIN_MSGS;
	}

	// set no traitor flags
	if ( m_no_traitor ) {
		The_mission.flags |= MISSION_FLAG_NO_TRAITOR;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_TRAITOR;
	}

	//set ship trail flags
	if ( m_ship_trails ) {
		The_mission.flags |= MISSION_FLAG_SHIP_TRAILS;
	} else {
		The_mission.flags &= ~MISSION_FLAG_SHIP_TRAILS;
	}

	//set support ship repairing flags
	if ( m_support_repairs_hull ) {
		The_mission.flags |= MISSION_FLAG_SUPPORT_REPAIRS_HULL;
	} else {
		The_mission.flags &= ~MISSION_FLAG_SUPPORT_REPAIRS_HULL;
	}

	// set default beam free
	if ( m_beam_free_all_by_default ) {
		The_mission.flags |= MISSION_FLAG_BEAM_FREE_ALL_BY_DEFAULT;
	} else {
		The_mission.flags &= ~MISSION_FLAG_BEAM_FREE_ALL_BY_DEFAULT;
	}

	// set warp effect
	/*if ( m_old_warp_effect ) {
		The_mission.flags |= MISSION_FLAG_OLD_WARP_EFFECT;
	} else {
		The_mission.flags &= ~MISSION_FLAG_OLD_WARP_EFFECT;
	}*/

	// set briefing
	if ( m_no_briefing ) {
		The_mission.flags |= MISSION_FLAG_NO_BRIEFING;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_BRIEFING;
	}

	// set debriefing
	if ( m_no_debriefing ) {
		The_mission.flags |= MISSION_FLAG_NO_DEBRIEFING;
	} else {
		The_mission.flags &= ~MISSION_FLAG_NO_BRIEFING;
	}

	if ( flags != The_mission.flags ){
		set_modified();
	}

	string_copy(The_mission.name, m_mission_title, NAME_LENGTH, 1);
	string_copy(The_mission.author, m_designer_name, NAME_LENGTH, 1);
	string_copy(The_mission.loading_screen[GR_640], m_loading_640, NAME_LENGTH,1);
	string_copy(The_mission.loading_screen[GR_1024], m_loading_1024, NAME_LENGTH,1);
	deconvert_multiline_string(The_mission.notes, m_mission_notes, NOTES_LENGTH);
	deconvert_multiline_string(The_mission.mission_desc, m_mission_desc, MISSION_DESC_LENGTH);

	// copy squad stuff
	if(m_squad_name == CString(NO_SQUAD)){
		strcpy(The_mission.squad_name, "");
		strcpy(The_mission.squad_filename, "");
	} else {
		string_copy(The_mission.squad_name, m_squad_name, NAME_LENGTH);
		string_copy(The_mission.squad_filename, m_squad_filename, MAX_FILENAME_LEN);
	}

	MODIFY(Current_soundtrack_num, m_music - 1);
	MODIFY(Mission_all_attack, m_full_war);
	if (query_modified()){
		set_modified();
	}

	theApp.record_window_data(&Mission_notes_wnd_data, this);

	// update the Num_teams variable accoriding to mission types
	Num_teams = 1;
	if ( (The_mission.game_type & MISSION_TYPE_MULTI) && (The_mission.game_type & MISSION_TYPE_MULTI_TEAMS) ){
		Num_teams = 2;
	}

	CDialog::OnOK();
}

void CMissionNotesDlg::OnCancel()
{
	theApp.record_window_data(&Mission_notes_wnd_data, this);
	CDialog::OnCancel();
}

BOOL CMissionNotesDlg::OnInitDialog() 
{
	int i;
	CComboBox *box;
	

	// set up the radio box states
	coop = (CButton *)GetDlgItem(IDC_COOP);
	team = (CButton *)GetDlgItem(IDC_TEAMVTEAM);
	dogfight = (CButton *)GetDlgItem(IDC_DOGFIGHT);

	m_mission_title_orig = m_mission_title = _T(The_mission.name);
	m_designer_name_orig = m_designer_name = _T(The_mission.author);
	m_created = _T(The_mission.created);
	m_modified = _T(The_mission.modified);
	m_mission_notes_orig = m_mission_notes = convert_multiline_string(The_mission.notes);
	m_mission_desc_orig = m_mission_desc = convert_multiline_string(The_mission.mission_desc);
	m_red_alert = The_mission.red_alert;
	m_scramble = The_mission.scramble;
	m_disallow_support = (The_mission.support_ships.max_support_ships == 0) ? 1 : 0;
	m_no_promotion = (The_mission.flags & MISSION_FLAG_NO_PROMOTION) ? 1 : 0;
	m_no_builtin_msgs = (The_mission.flags & MISSION_FLAG_NO_BUILTIN_MSGS) ? 1 : 0;
	m_no_traitor = (The_mission.flags & MISSION_FLAG_NO_TRAITOR) ? 1 : 0;
	m_ship_trails = (The_mission.flags & MISSION_FLAG_SHIP_TRAILS) ? 1 : 0;
	m_support_repairs_hull = (The_mission.flags &MISSION_FLAG_SUPPORT_REPAIRS_HULL) ? 1 : 0;
	m_beam_free_all_by_default = (The_mission.flags & MISSION_FLAG_BEAM_FREE_ALL_BY_DEFAULT) ? 1 : 0;
//	m_old_warp_effect = (The_mission.flags & MISSION_FLAG_OLD_WARP_EFFECT) ? 1 : 0;
	m_no_briefing = (The_mission.flags & MISSION_FLAG_NO_BRIEFING) ? 1 : 0;
	m_no_debriefing = (The_mission.flags & MISSION_FLAG_NO_DEBRIEFING) ? 1 : 0;

	m_loading_640=_T(The_mission.loading_screen[GR_640]);
	m_loading_1024=_T(The_mission.loading_screen[GR_1024]);

	//CDialog::OnInitDialog();
//return TRUE;
	box = (CComboBox *) GetDlgItem(IDC_MUSIC);
	box->AddString("None");
	for (i=0; i<Num_soundtracks; i++){
		box->AddString(Soundtracks[i].name);		
	}

	// squad info
	if(strlen(The_mission.squad_name) > 0){
		m_squad_name = _T(The_mission.squad_name);
		m_squad_filename = _T(The_mission.squad_filename);
	} else {
		m_squad_name = _T(NO_SQUAD);
		m_squad_filename = _T("");
	}

	m_type = The_mission.game_type;
	m_music = Current_soundtrack_num + 1;
	m_full_war = Mission_all_attack;

	// set up the game type checkboxes accoring to m_type
	if ( m_type & MISSION_TYPE_SINGLE ){
		((CButton *) GetDlgItem(IDC_SINGLE))->SetCheck(1);
	}

	// for multiplayer -- be sure to assign a default type if not already assigned.
	if ( m_type & MISSION_TYPE_MULTI ){
		((CButton *) GetDlgItem(IDC_MULTI))->SetCheck(1);
	}

	if ( m_type & MISSION_TYPE_TRAINING ){
		((CButton *) GetDlgItem(IDC_TRAINING))->SetCheck(1);
	}

	// we need to set one of these three multiplayer modes so interface looks correct
	if ( !(m_type & (MISSION_TYPE_MULTI_COOP | MISSION_TYPE_MULTI_DOGFIGHT | MISSION_TYPE_MULTI_TEAMS)) ){
		m_type |= MISSION_TYPE_MULTI_COOP;
	}

	if ( m_type & MISSION_TYPE_MULTI_COOP ){
		coop->SetCheck(1);
	} else if ( m_type & MISSION_TYPE_MULTI_TEAMS ){
		team->SetCheck(1);
	} else if ( m_type & MISSION_TYPE_MULTI_DOGFIGHT ){
		dogfight->SetCheck(1);
	} else {
		Int3();			// get allender -- multiplayer mode not set!!!
	}

	m_respawn_spin.SetRange(0, 99);
	m_num_respawns = The_mission.num_respawns;
	m_max_hull_repair_val = The_mission.support_ships.max_hull_repair_val;
	m_max_subsys_repair_val = The_mission.support_ships.max_subsys_repair_val;

	set_types();
	UpdateData(FALSE);
	theApp.init_window(&Mission_notes_wnd_data, this);
	return TRUE;
}

void CMissionNotesDlg::OnClose() 
{
	int z;

	if (query_modified()) {
		z = MessageBox("Do you want to keep your changes?", "Close", MB_ICONQUESTION | MB_YESNOCANCEL);
		if (z == IDCANCEL){
			return;
		}

		if (z == IDYES) {
			OnOK();
			return;
		}
	}

	CDialog::OnClose();
}

// when training button is set, we need to disable all other buttons
void CMissionNotesDlg::OnTraining() 
{
	UpdateData(TRUE);
	set_types();
}

void CMissionNotesDlg::OnMulti() 
{
	UpdateData(TRUE);
	set_types();
}

void CMissionNotesDlg::OnSingle() 
{
	UpdateData(TRUE);
	set_types();
}

void CMissionNotesDlg::set_types()
{
	int enable = 0;

	// when training is checked, no other type is active
	if (((CButton *) GetDlgItem(IDC_MULTI))->GetCheck() == 1){
		enable = 1;
	}

	coop->EnableWindow(enable);
	team->EnableWindow(enable);
	dogfight->EnableWindow(enable);
	GetDlgItem(IDC_RESPAWNS)->EnableWindow(enable);
	GetDlgItem(IDC_RESPAWN_SPIN)->EnableWindow(enable);
}

void CMissionNotesDlg::OnSquadLogo()
{	
	CString pcx_filename;
	int z;


	//phreak 05/05/2003
	//this needs to be here or else the data in the mission notes dialog will revert 
	//to what it was before it was opened.
	UpdateData(TRUE);

	// get list of squad images
	z = cfile_push_chdir(CF_TYPE_SQUAD_IMAGES_MAIN);
	CFileDialog dlg(TRUE, "pcx", pcx_filename, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR, "Pcx Files (*.pcx)|*.pcx");

	// if we have a result
	if (dlg.DoModal() == IDOK) {
		m_squad_filename = dlg.GetFileName();		
	} else {
		m_squad_filename = _T("");
	}
	UpdateData(FALSE);		

	// restore directory
	if (!z){
		cfile_pop_dir();
	}	
}

void CMissionNotesDlg::OnLoad1024()
{
	CString filename;
	int z;

	UpdateData(TRUE);

	// get list of
	z = cfile_push_chdir(CF_TYPE_DATA);
	CFileDialog dlg(TRUE, "pcx", filename, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR, "Pcx Files (*.pcx)|*.pcx");

	// if we have a result
	if (dlg.DoModal() == IDOK) {
		m_loading_1024 = dlg.GetFileName();		
	} else {
		m_loading_1024 = _T("");
	}
	UpdateData(FALSE);		

	// restore directory
	if (!z){
		cfile_pop_dir();
	}	
}

void CMissionNotesDlg::OnLoad640()
{
	CString filename;
	int z;

	UpdateData(TRUE);

	// get list of
	z = cfile_push_chdir(CF_TYPE_DATA);
	CFileDialog dlg(TRUE, "pcx", filename, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR, "Pcx Files (*.pcx)|*.pcx");

	// if we have a result
	if (dlg.DoModal() == IDOK) {
		m_loading_640 = dlg.GetFileName();		
	} else {
		m_loading_640 = _T("");
	}
	UpdateData(FALSE);		

	// restore directory
	if (!z){
		cfile_pop_dir();
	}	
}



void CMissionNotesDlg::OnEnChangeLoadingScreen641()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
