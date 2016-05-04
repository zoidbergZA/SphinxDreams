module("hud", package.seeall)
local data = require("mge/lua/hud_data")

MODE = { MENU = 1, BOOK = 2, LEVEL = 3 }
game_state = MODE.MENU
showHintsBox1 = false
showHintsBox2 = false
showHintsBox3 = false
showRiddleBox = true
showHelpBox = true           -- NOTE: SHOULD BE TRUE UPON START OF THE LEVEL FOR INITIAL RIDDLE SHOW-UP
initialRiddleCheck = false   -- NOTE: SHOULD BE FALSE FOR INITIAL RIDDLE SHOW-UP
firstMenuShown = false
firstBookShown = false
continueToNextPuzzle = false
showFinalMenu = false
restartGame = false
hint_1 = "hint_1"
hint_2 = "hint_2"
hint_3 = "hint_3"
riddle_text = "riddle text"
bookSoundPlayed = false
playFinalBookSound = false

progress = 0

hint1_spriteID = 2 
hint2_spriteID = 4 
hint3_spriteID = 6
exit_spriteID = 2 
resume_spriteID = 6 
start_spriteID = 0
story_book_button_spriteID = 0
soundPlayed = 0

function draw()
	if game_state == MODE.LEVEL then
        updateLevel()
    elseif game_state == MODE.BOOK then
        updateBook()
    elseif game_state == MODE.MENU then
        updateMenu()
    end
end

function updateBook()
    popStoryBook()
    handleStoryBookButtonClick()
end

function updateMenu()
    if Game.getKeyDown(KeyCode.M) == true and firstMenuShown == true then
        game_state = MODE.LEVEL
    end
	popMenu()
    handleMenuButtonsClick()
end

function updateLevel()
    updateHelpBox()
    updateHintsBox()
	
	if (showHelpBox) then handleHelpButtonClick(1) 	-- show pressed
	else handleHelpButtonClick(0) end				-- show unpressed
	
    inintialRiddleDisplay()
	
	updateProgressBar(data.progress_bar_xOffset, data.progress_bar_yOffset, data.progress_bar_alignment, data.progress_bar_scaleX, data.progress_bar_scaleY)
    if Game.getKeyDown(KeyCode.M) == true then
        game_state = MODE.MENU
    end
end

function handleHelpButtonClick(spriteID)
	--HelpButton
	if Hud.hintsButton(data.help_button_xOffset, data.help_button_yOffset, spriteID, 
				       data.help_button_alignment, data.help_button_scaleX, data.help_button_scaleY) == true then					
        if showHelpBox == false then
            showHelpBox = true
            showRiddleBox = true
            Audio.playSound("Riddle.wav")
        else
            showHelpBox = false
			hint1_spriteID = 2 --off
			hint2_spriteID = 4 --off
			hint3_spriteID = 6 --off
        end
        
		showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
    end
end

function handleHintButtonsClick()
    --HintButton1
	if Hud.hintsButton(data.hint_button1_xOffset, data.hint_button1_yOffset, 
        hint1_spriteID, data.hint_button1_alignment, data.hint_button1_scaleX, data.hint_button1_scaleY) == true then
        if showHintsBox1 == false then
            showHintsBox1 = true
			hint1_spriteID = 3 --on
			hint2_spriteID = 4 --off
			hint3_spriteID = 6 --off
			
            showHintsBox2 = false
            showHintsBox3 = false
            showRiddleBox = false
            Audio.playSound("Hint.wav")
        else
            showHintsBox1 = false
			showRiddleBox = true
			hint1_spriteID = 2 --off
        end
    end
    
	--HintButton2
	if Hud.hintsButton(data.hint_button2_xOffset, data.hint_button2_yOffset,
        hint2_spriteID, data.hint_button2_alignment, data.hint_button2_scaleX, data.hint_button2_scaleY) == true then
        if showHintsBox2 == false then
            showHintsBox2 = true
			hint1_spriteID = 2 --off
			hint2_spriteID = 5 --on
			hint3_spriteID = 6 --off
			
            showHintsBox1 = false
            showHintsBox3 = false
            showRiddleBox = false
            Audio.playSound("Hint.wav")
        else
            showHintsBox2 = false
			showRiddleBox = true
			hint2_spriteID = 4 --off
        end
    end
    
    --HintButton3
	if Hud.hintsButton(data.hint_button3_xOffset, data.hint_button3_yOffset, 
        hint3_spriteID, data.hint_button3_alignment, data.hint_button3_scaleX, data.hint_button3_scaleY) == true then
        if showHintsBox3 == false then
            showHintsBox3 = true
			hint1_spriteID = 2 --off
			hint2_spriteID = 4 --off
			hint3_spriteID = 7 --on
			
            showHintsBox2 = false
            showHintsBox1 = false
            showRiddleBox = false
            Audio.playSound("Hint.wav")
        elseif showHintsBox3 == true then
            showHintsBox3 = false
			showRiddleBox = true
			hint3_spriteID = 6 --off
        end
    end
end

function updateProgressBar(xOffset, yOffset, alignment, scaleX, scaleY)
	if 	   (progress > 0.92) then
        Hud.progressBar(xOffset, yOffset, 7, alignment, scaleX, scaleY) -- show 7
        if soundPlayed ~= 7 then
            Audio.playSound("Progression_8.wav")
            soundPlayed = 7
        end
	elseif (progress > 0.86) then
        Hud.progressBar(xOffset, yOffset, 6, alignment, scaleX, scaleY) -- show 6
        if soundPlayed ~= 6 then
            Audio.playSound("Progression_7.wav")
            soundPlayed = 6
        end
	elseif (progress > 0.80) then
        Hud.progressBar(xOffset, yOffset, 5, alignment, scaleX, scaleY) -- show 5
        if soundPlayed ~= 5 then
            Audio.playSound("Progression_6.wav")
            soundPlayed = 5
        end
	elseif (progress > 0.74) then
        Hud.progressBar(xOffset, yOffset, 4, alignment, scaleX, scaleY) -- show 4
        if soundPlayed ~= 4 then
            Audio.playSound("Progression_5.wav")
            soundPlayed = 4
        end
	elseif (progress > 0.68) then
        Hud.progressBar(xOffset, yOffset, 3, alignment, scaleX, scaleY) -- show 3
        if soundPlayed ~= 3 then
            Audio.playSound("Progression_4.wav")
            soundPlayed = 3
        end
	elseif (progress > 0.60) then
        Hud.progressBar(xOffset, yOffset, 2, alignment, scaleX, scaleY) -- show 2
        if soundPlayed ~= 2 then
            Audio.playSound("Progression_3.wav")
            soundPlayed = 2
        end
	elseif (progress > 0.50) then
        Hud.progressBar(xOffset, yOffset, 1, alignment, scaleX, scaleY) -- show 1
        if soundPlayed ~= 1 then
            Audio.playSound("Progression_2.wav")
            soundPlayed = 1
        end
	elseif (progress <= 0.50) then
        Hud.progressBar(xOffset, yOffset, 0, alignment, scaleX, scaleY) -- show 0
        if soundPlayed ~= 0 then
            Audio.playSound("Progression_1.wav")
            soundPlayed = 0
        end
	end
end

-- the box holding the hint buttons
function updateHelpBox()
    if showHelpBox == true then
        Hud.helpBox	 (data.help_box_xOffset, data.help_box_yOffset, data.help_box_alignment, data.help_box_scaleX, data.help_box_scaleY)
		if showRiddleBox == true then
            Hud.riddleBox(data.riddle_box_xOffset, data.riddle_box_yOffset, data.riddle_box_font, riddle_text, data.riddle_box_alignment, data.riddle_box_scaleX, data.riddle_box_scaleY)
        end
        handleHintButtonsClick()
    else
        showHintsBox1 = false
        showHintsBox2 = false
        showHintsBox3 = false
        showRiddleBox = false
    end
end

-- the box showing the actual hint
function updateHintsBox()
    if showHintsBox1 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_font, hint_1, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    elseif showHintsBox2 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_font, hint_2, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    elseif showHintsBox3 == true then
        Hud.hintsBox(data.hints_box_xOffset, data.hints_box_yOffset, data.hints_box_font, hint_3, data.hints_box_alignment, data.hints_box_scaleX, data.hints_box_scaleY)
    end
end

function inintialRiddleDisplay()
    if Hud.displayRiddleAtStart() == true and initialRiddleCheck == false then 
        showHelpBox = false
        showRiddleBox = false
        hint1_spriteID = 2 --off
        hint2_spriteID = 4 --off
        hint3_spriteID = 6 --off
        initialRiddleCheck = true
    end
end

function popMenu()
    Hud.menuBox(data.menu_box_xOffset, data.menu_box_yOffset, data.menu_box_alignment, data.menu_box_scaleX, data.menu_box_scaleY)
end

function handleMenuButtonsClick()

    if firstMenuShown == false then
		--StartButton
		if Hud.menuButton(data.start_button_xOffset, data.start_button_yOffset, start_spriteID, 
						   data.start_button_alignment, data.start_button_scaleX, data.start_button_scaleY) == true then
            game_state = MODE.BOOK
            firstMenuShown = true
			start_spriteID = 4 --Switch to RestartButtonSprite
            Audio.playSound("Start.wav")
        end
    end
    
    if firstMenuShown == true then
        --RestartButton
		if Hud.menuButton(data.start_button_xOffset, data.start_button_yOffset, start_spriteID, 
						   data.start_button_alignment, data.start_button_scaleX, data.start_button_scaleY) == true then
            restartGame = true
            Audio.playSound("Start.wav")
            print("RESTART!")
        end

		if showFinalMenu == false then 
		--ResumeButton
			if Hud.menuButton(data.resume_button_xOffset, data.resume_button_yOffset, resume_spriteID, 
							data.resume_button_alignment, data.resume_button_scaleX, data.resume_button_scaleY) == true then
				game_state = MODE.LEVEL
                Audio.playSound("Button.wav")
			end
		end
    end
	--ExitButton
	if Hud.menuButton(data.exit_button_xOffset, data.exit_button_yOffset, exit_spriteID, 
				  data.exit_button_alignment, data.exit_button_scaleX, data.exit_button_scaleY) == true then
		Audio.playSound("Exit.wav")
        Hud.handleExit()
	end
end
	
function popStoryBook()
    Hud.storyBook(data.story_book_xOffset, data.story_book_yOffset, data.story_book_alignment, data.story_book_scaleX, data.story_book_scaleY)
    if bookSoundPlayed == false then
        if playFinalBookSound == false then
            Audio.playSound("Book.wav")
        else
            Audio.playSound("Pages.wav")
        end
        bookSoundPlayed = true
    end
end

function handleStoryBookButtonClick()
    if firstBookShown == false then
        if Hud.storyBookButton(data.story_book_button_xOffset, data.story_book_button_yOffset, story_book_button_spriteID, 
            data.story_book_button_alignment, data.story_book_button_scaleX, data.story_book_button_scaleY) == true then
            game_state = MODE.LEVEL
            firstBookShown = true
            Audio.playSound("Button.wav")
			Hud.setBookTexture(activePuzzle)
        end
    else
        if Hud.storyBookButton(data.story_book_button_xOffset, data.story_book_button_yOffset, story_book_button_spriteID, 
            data.story_book_button_alignment, data.story_book_button_scaleX, data.story_book_button_scaleY) == true then
            game_state = MODE.LEVEL
            continueToNextPuzzle = true
            Audio.playSound("Button.wav")
        end
    end
end

--MAIN GAME AMBIENT THEME START--
function playAmbientSound()
    if playFinalBookSound == false then
        Audio.playMusic("Cleo_ThemeIngame.ogg", true)
    else
        Audio.stopMusic("Cleo_ThemeIngame.ogg", true)
        Audio.playMusic("Opening_Ending_Theme.ogg", true)
    end
end

playAmbientSound()
--MAIN GAME AMBIENT THEME END--