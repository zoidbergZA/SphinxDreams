module("hud_data", package.seeall)
local HUD = {}
alignment = { LEFT_TOP = 1, LEFT_CENTER = 2, LEFT_BOTTOM = 3, CENTER_TOP = 4, CENTER_CENTER = 5, CENTER_BOTTOM = 6, RIGHT_TOP = 7, RIGHT_CENTER = 8, RIGHT_BOTTOM = 9 }

-- BUTTONS AND BOXES PARAMETERS START --
display_riddle_at_start = 60

--[ProgressBar] ProgressBar 
progress_bar_xOffset = 0
progress_bar_yOffset = 50 
progress_bar_scaleX = 1
progress_bar_scaleY = 1
progress_bar_alignment = alignment.CENTER_TOP
progress_bar_texture = "HUD_ProgressBar_Sheet.png"

--[HintsButton] Button for Riddle / Hints 
hints_button_texture = "HUD_Hints_Sheet.png"

--[HelpButton] Button for Riddle / Hints 
help_button_xOffset = 30
help_button_yOffset = 30
help_button_scaleX = 0.65
help_button_scaleY = 0.65
help_button_alignment = alignment.RIGHT_TOP

--[HintButton1] Button for first hint
hint_button1_xOffset = 40
hint_button1_yOffset = 120
hint_button1_scaleX = 0.5
hint_button1_scaleY = 0.5
hint_button1_alignment = alignment.RIGHT_TOP

--[HintButton2] Button for second hint
hint_button2_xOffset = 40
hint_button2_yOffset = 190
hint_button2_scaleX = 0.5
hint_button2_scaleY = 0.5
hint_button2_alignment = alignment.RIGHT_TOP

--[HintButton3] Button for third hint
hint_button3_xOffset = 40
hint_button3_yOffset = 260
hint_button3_scaleX = 0.5
hint_button3_scaleY = 0.5
hint_button3_alignment = alignment.RIGHT_TOP

--[HelpBox] Label behind the hint buttons (helpbox)
help_box_xOffset = 32
help_box_yOffset = 14
help_box_scaleX = 0.155
help_box_scaleY = 0.155
help_box_alignment = alignment.RIGHT_TOP
help_box_texture = "HUD_Dropdown_Box.png"


------------- MENU START -------------------------- MENU START -------------
--[MenuBox] Label that shows menu container
menu_box_xOffset = 0
menu_box_yOffset = 0
menu_box_scaleX = 1
menu_box_scaleY = 1
menu_box_alignment = alignment.CENTER_CENTER
menu_box_texture = "MENU_Background.png"

--[MenuButton]
menu_button_texture = "MENU_Buttons_Sheet.png"

--[MenuButton: Resume]
resume_button_xOffset = 250
resume_button_yOffset = 500
resume_button_scaleX = 0.3
resume_button_scaleY = 0.3
resume_button_alignment = alignment.RIGHT_BOTTOM

--[MenuButton: Start]
start_button_xOffset = 250
start_button_yOffset = 320
start_button_scaleX = 0.3
start_button_scaleY = 0.3
start_button_alignment = alignment.RIGHT_BOTTOM

--[MenuButton: Exit]
exit_button_xOffset = 250
exit_button_yOffset = 140
exit_button_scaleX = 0.3
exit_button_scaleY = 0.3
exit_button_alignment = alignment.RIGHT_BOTTOM
-------------- MENU END ---------------------------- MENU END --------------

------------- BOOK START -------------------------- BOOK START -------------
--[StoryBook] Label that shows storybook container
story_book_xOffset = 0
story_book_yOffset = 0
story_book_scaleX = 1
story_book_scaleY = 1
story_book_alignment = alignment.CENTER_CENTER
story_book_texture = "BOOK_00.png"

--[StoryBookButton] Continue button in storybook container
story_book_button_xOffset = 0
story_book_button_yOffset = 80
story_book_button_scaleX = 0.15
story_book_button_scaleY = 0.15
story_book_button_alignment = alignment.CENTER_BOTTOM
story_book_button_texture = "BOOK_Continue_Button_Sheet.png"
-------------- BOOK END ---------------------------- BOOK END --------------

--[RiddleBox] Label that shows the riddle
riddle_box_xOffset = 0
riddle_box_yOffset = 0
riddle_box_font = 25
riddle_box_scaleX = 0.8
riddle_box_scaleY = 0.6
riddle_box_alignment = alignment.CENTER_BOTTOM
riddle_box_texture = "HUD_Riddle_Box.png"

--[HintsBox] Label that shows the actual hint
hints_box_xOffset = 0
hints_box_yOffset = 0
hints_box_font = 30
hints_box_scaleX = 0.8
hints_box_scaleY = 0.6
hints_box_alignment = alignment.CENTER_BOTTOM
hints_box_texture = "HUD_Riddle_Box.png"
-- BUTTONS AND BOXES PARAMETERS END --

--------------------------------------------------------------------------------
---||\--||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||---------
---||\\-||--||---||--||---||--||---||--||---||--||---||--||---||--||---||-------
---||-\\||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||--|||||||---------
--------------------------------------------------------------------------------

-- THIS PART SHOULD NOT BE TOUCHED --

HUD.alignment = alignment
HUD.display_riddle_at_start = display_riddle_at_start

HUD.progress_bar_xOffset = progress_bar_xOffset
HUD.progress_bar_yOffset = progress_bar_yOffset
HUD.progress_bar_scaleX = progress_bar_scaleX
HUD.progress_bar_scaleY = progress_bar_scaleY
HUD.progress_bar_alignment = progress_bar_alignment
HUD.progress_bar_texture = progress_bar_texture

-- riddle / hint / help button texture
HUD.hints_button_texture 	= hints_button_texture

-- riddle / hint / help button
HUD.help_button_xOffset = help_button_xOffset
HUD.help_button_yOffset = help_button_yOffset
HUD.help_button_scaleX = help_button_scaleX
HUD.help_button_scaleY = help_button_scaleY
HUD.help_button_alignment = help_button_alignment

--Button for first hint
HUD.hint_button1_xOffset = hint_button1_xOffset
HUD.hint_button1_yOffset = hint_button1_yOffset
HUD.hint_button1_scaleX = hint_button1_scaleX
HUD.hint_button1_scaleY = hint_button1_scaleY
HUD.hint_button1_alignment = hint_button1_alignment

--Button for second hint
HUD.hint_button2_xOffset = hint_button2_xOffset
HUD.hint_button2_yOffset = hint_button2_yOffset
HUD.hint_button2_scaleX = hint_button2_scaleX
HUD.hint_button2_scaleY = hint_button2_scaleY
HUD.hint_button2_alignment = hint_button2_alignment

--Button for third hint
HUD.hint_button3_xOffset = hint_button3_xOffset
HUD.hint_button3_yOffset = hint_button3_yOffset
HUD.hint_button3_scaleX = hint_button3_scaleX
HUD.hint_button3_scaleY = hint_button3_scaleY
HUD.hint_button3_alignment = hint_button3_alignment

--[MenuButton]
HUD.menu_button_texture = menu_button_texture

--Exit button in menu
HUD.exit_button_xOffset = exit_button_xOffset
HUD.exit_button_yOffset = exit_button_yOffset
HUD.exit_button_scaleX = exit_button_scaleX
HUD.exit_button_scaleY = exit_button_scaleY
HUD.exit_button_alignment = exit_button_alignment

--Resume button in menu
HUD.resume_button_xOffset = resume_button_xOffset
HUD.resume_button_yOffset = resume_button_yOffset
HUD.resume_button_scaleX = resume_button_scaleX
HUD.resume_button_scaleY = resume_button_scaleY
HUD.resume_button_alignment = resume_button_alignment

--Start button in menu
HUD.start_button_xOffset = start_button_xOffset
HUD.start_button_yOffset = start_button_yOffset
HUD.start_button_scaleX = start_button_scaleX
HUD.start_button_scaleY = start_button_scaleY
HUD.start_button_alignment = start_button_alignment

--Continue button in storybook container
HUD.story_book_button_xOffset = story_book_button_xOffset
HUD.story_book_button_yOffset = story_book_button_yOffset
HUD.story_book_button_scaleX = story_book_button_scaleX
HUD.story_book_button_scaleY = story_book_button_scaleY
HUD.story_book_button_alignment = story_book_button_alignment
HUD.story_book_button_texture = story_book_button_texture

-- background of the hintbuttons
HUD.help_box_xOffset = help_box_xOffset
HUD.help_box_yOffset = help_box_yOffset
HUD.help_box_scaleX = help_box_scaleX
HUD.help_box_scaleY = help_box_scaleY
HUD.help_box_alignment = help_box_alignment
HUD.help_box_texture = help_box_texture

-- actual riddle
HUD.riddle_box_xOffset = riddle_box_xOffset
HUD.riddle_box_yOffset = riddle_box_yOffset
HUD.riddle_box_font = riddle_box_font
HUD.riddle_box_scaleX = riddle_box_scaleX
HUD.riddle_box_scaleY = riddle_box_scaleY
HUD.riddle_box_alignment = riddle_box_alignment
HUD.riddle_box_texture = riddle_box_texture

-- actual menu container
HUD.menu_box_xOffset = menu_box_xOffset
HUD.menu_box_yOffset = menu_box_yOffset
HUD.menu_box_alignment = menu_box_alignment
HUD.menu_box_texture = menu_box_texture
HUD.menu_box_scaleX = menu_box_scaleX
HUD.menu_box_scaleY = menu_box_scaleY

-- actual story book container
HUD.story_book_xOffset = story_book_xOffset
HUD.story_book_yOffset = story_book_yOffset
HUD.story_book_scaleX = story_book_scaleX
HUD.story_book_scaleY = story_book_scaleY
HUD.story_book_alignment = story_book_alignment
HUD.story_book_texture = story_book_texture

-- actual hint
HUD.hints_box_xOffset = hints_box_xOffset
HUD.hints_box_yOffset = hints_box_yOffset
HUD.hints_box_font = hints_box_font
HUD.hints_box_scaleX = hints_box_scaleX
HUD.hints_box_scaleY = hints_box_scaleY
HUD.hints_box_alignment = hints_box_alignment
HUD.hints_box_texture = hints_box_texture

return HUD