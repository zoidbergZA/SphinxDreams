gameHud = require "mge/lua/hud"
gameHud_Data = require "mge/lua/hud_data"

dofile("mge/lua/story1.lua")

game_state = 1
storyCompleted = false
activePuzzle = 1
activePiece = 1
solvedThreshold = 0.94

---- initial scene setup ----
storyWall = Game.StoryWall("Main_wall_OBJ.obj", "1_MainWall_Base_Color.png", "StoryWall")
storyWall:rotateAroundAxis(240, 0, 1, 0)
storyWall:scale(0.7, 0.7, 0.7)
storyWall:setPosition (3.1, 2.3, 3.3)

sideWall = Game.StoryWall("Side_wall_OBJ.obj", "SideWall_Base_Color.png", "SideWall")
sideWall:rotateAroundAxis(240, 0, 1, 0)
sideWall:scale(0.7, 0.7, 0.7)
sideWall:setPosition (3.1, 2.3, 3.3)

backWall = Game.StoryWall("BackScreen.obj", "Backwall_Base_Color.png", "BackWall")
backWall:rotateAroundAxis(240, 0, 1, 0)
backWall:scale(0.7, 0.7, 0.7)
backWall:setPosition (3.1, 2.3, 3.3)

spotlight = Game.getSpotlight()
camera = Game.getCameraObject()

camera:setPosition(-5.809093, 5.566962, 6.267358)
camera:rotateAroundAxis(-23, 0, 1, 0)

spotlight:setIntensity(0.78)
spotlight:setInnerCone(7)
spotlight:setOuterCone(18)
spotlight:setColor(0.9, 0.94, 0.62)

----------------------------

function getActiveBlock()
    return story[activePuzzle].blocks[activePiece]
end

function puzzleSetActive(puzzleIndex, active)
    for i, v in ipairs(story[puzzleIndex].blocks) do 
        v:setActive(active)
    end
end

function selectBlock(puzzleIndex, blockIndex)
    activePiece = blockIndex
    story[puzzleIndex].blocks[activePiece]:flash(1.8)
end

function selectPuzzle(puzzleIndex)
    counter = 1
    for i, v in ipairs(story) do 
        if counter == puzzleIndex then
            puzzleSetActive(counter, true)
            -- camera:setPosition(story[puzzleIndex].camPosition[1], story[puzzleIndex].camPosition[2], story[puzzleIndex].camPosition[3])
            camera:moveTo(story[puzzleIndex].camPosition[1], story[puzzleIndex].camPosition[2], story[puzzleIndex].camPosition[3], 10)
            spotlight:moveTo(story[puzzleIndex].lightPosition[1], story[puzzleIndex].lightPosition[2], story[puzzleIndex].lightPosition[3], 7)
        else
            puzzleSetActive(counter, false)
        end
        counter = counter + 1
    end

    activePuzzle = puzzleIndex
    storyWall:changeTexture(story[puzzleIndex].wallImage)
    selectBlock(activePuzzle, 1)
    print("Current Puzzel is: " .. activePuzzle) 
end

function nextPuzzle()
    nextPuzzleIndex = activePuzzle + 1
    if nextPuzzleIndex == #story then
        hud.playFinalBookSound = true
    end
    if nextPuzzleIndex > #story then
        storyCompleted = true
        hud.showFinalMenu = true
        hud.game_state = hud.MODE.MENU
        hud.showHelpBox = false
        print("completed!!")
    else
        selectPuzzle(nextPuzzleIndex)
        Hud.setBookTexture(activePuzzle)
        hud.showHelpBox = false
    end
end

function handlePlacement(gameObject)
    if Game.getKey(KeyCode.Up) == true then
        gameObject:move(0, 0, -1) 
    end
    if Game.getKey(KeyCode.Down) == true then
        gameObject:move(0, 0, 1) 
    end
    if Game.getKey(KeyCode.Left) == true then
        gameObject:move(-1, 0, 0) 
    end
    if Game.getKey(KeyCode.Right) == true then
        gameObject:move(1, 0, 0) 
    end
    if Game.getKey(KeyCode.RShift) == true then
        gameObject:move(0, 1, 0) 
    end
    if Game.getKey(KeyCode.RControl) == true then
        gameObject:move(0, -1, 0) 
    end
end

selectPuzzle(activePuzzle)

function update()
    if game_state == hud.MODE.LEVEL then
        updateLevel()
    end
end

function updateLevel()
    if storyCompleted then
        return
    else
        if Game.getKeyDown(KeyCode.T) == true then
            handleSelection()
        end

        if Game.getKeyDown(KeyCode.Y) == true then -- THIS BLOCK SHOULD BE REMOVED IN RELEASE VERSION
            nextPuzzle()
        end

        if Game.getKeyDown(KeyCode.P) == true then
            ---- print status calls ----  ==> uncomment a line to print status for different types of objects
            -- camera:printStatus()
            -- story[activePuzzle].blocks[activePiece]:printStatus()

            ----------------------------
        end

        handleControl()

        ---- object placement calls ----  ==> uncomment a line to place different types of objects

        -- handlePlacement(storyWall)
        -- handlePlacement(camera)
        -- handlePlacement(story[activePuzzle].blocks[activePiece])
        
        --------------------------------

        if checkProgress() >= solvedThreshold then
            hud.game_state = hud.MODE.BOOK
            hud.bookSoundPlayed = false
        end
        
        if hud.continueToNextPuzzle == true then
            hud.game_state = hud.MODE.LEVEL
            nextPuzzle()
            hud.continueToNextPuzzle = false
        end
    end
end

function updateGUI()
    hud.progress = checkProgress()
    hud.draw()
    game_state = hud.game_state
    restartGame()
    hud.hint_1 = story[activePuzzle].tips[1]
    hud.hint_2 = story[activePuzzle].tips[2]
    hud.hint_3 = story[activePuzzle].tips[3]
    hud.riddle_text = story[activePuzzle].riddle[1]
end

function refreshHud()
    package.loaded["mge/lua/hud"] = nil
    gameHud = require "mge/lua/hud"
    print("hud reloaded!")
	package.loaded["mge/lua/hud_data"] = nil
	gameHud_Data = require "mge/lua/hud"
	print("hud_data reloaded!")
end

function printPuzzleBlocksStates()
    for i, v in ipairs(pieces) do 
        v:printStatus() 
    end
end

-- checks the total progress of the puzzle between 0 and 1
function checkProgress()
    totalProgress = 0
    for i, v in ipairs(story[activePuzzle].blocks) do 
        totalProgress = totalProgress + story[activePuzzle].blocks[i]:getProgress() 
    end   
    return totalProgress / #story[activePuzzle].blocks
end

function handleControl()
    if Game.getKey(KeyCode.W) == true then
        story[activePuzzle].blocks[activePiece]:pitch(1.5) 
    end
    if Game.getKey(KeyCode.S) == true then
        story[activePuzzle].blocks[activePiece]:pitch(-1.5) 
    end
    if Game.getKey(KeyCode.D) == true then
        story[activePuzzle].blocks[activePiece]:roll(1.5) 
    end
    if Game.getKey(KeyCode.A) == true then
        story[activePuzzle].blocks[activePiece]:roll(-1.5) 
    end
    if Game.getKey(KeyCode.Q) == true then
        story[activePuzzle].blocks[activePiece]:yaw(1.5) 
    end
    if Game.getKey(KeyCode.E) == true then
        story[activePuzzle].blocks[activePiece]:yaw(-1.5) 
    end
end 

function handleSelection()

    blockCount = #story[activePuzzle].blocks

    activePiece = activePiece + 1

    if activePiece > blockCount then
       activePiece = 1
    end

    story[activePuzzle].blocks[activePiece]:flash(1.8)
end

function restartGame()
    if hud.restartGame == true then
        hud.game_state = hud.MODE.LEVEL
        activePuzzle = 1
        activePiece = 1
        selectPuzzle(activePuzzle)
        hud.restartGame = false
    end
end

-- TEXTURE NAMES FOR C++ START --
display_riddle_at_start = gameHud_Data.display_riddle_at_start
hints_button_texture 	  = gameHud_Data.hints_button_texture
menu_button_texture 	  = gameHud_Data.menu_button_texture 			--spritesheet with all menubuttons
help_box_texture = gameHud_Data.help_box_texture
riddle_box_texture = gameHud_Data.riddle_box_texture
hints_box_texture = gameHud_Data.hints_box_texture
menu_box_texture = gameHud_Data.menu_box_texture
progress_bar_texture = gameHud_Data.progress_bar_texture
story_book_texture = gameHud_Data.story_book_texture
story_book_button_texture = gameHud_Data.story_book_button_texture

book_texture_intro = story[1].bookImageIntro
book_texture_1 = story[1].bookImage
book_texture_2 = story[2].bookImage
book_texture_3 = story[3].bookImage
book_texture_5 = story[4].bookImage
book_texture_7 = story[5].bookImage
book_texture_9 = story[6].bookImage
book_texture_10 = story[7].bookImage
book_texture_final = story[8].bookImage

--[[book_texture_intro = story[1].bookImageIntro
book_texture_1 = story[1].bookImage
book_texture_2 = story[2].bookImage
book_texture_3 = story[3].bookImage
book_texture_4 = story[4].bookImage
book_texture_5 = story[5].bookImage
book_texture_6 = story[6].bookImage
book_texture_7 = story[7].bookImage
book_texture_8 = story[8].bookImage
book_texture_9 = story[9].bookImage
book_texture_10 = story[10].bookImage
book_texture_11 = story[11].bookImage
book_texture_final = story[12].bookImage]]--
-- TEXTURE NAMES FOR C++ END --

-- PRE-CACHING STORY-WALL IMAGES STARTS HERE
function cacheWallTextures()
    for i, v in ipairs(story) do 
        storyWall:changeTexture(story[i].wallImage)
    end
    storyWall:changeTexture(story[1].wallImage)
end
cacheWallTextures()
-- PRE-CACHING STORY-WALL IMAGES ENDS HERE