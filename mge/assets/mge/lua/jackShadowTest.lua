gameHud = require "mge/lua/hud"
gameHud_Data = require "mge/lua/hud_data"

dofile("mge/lua/story1.lua")

storyWall = Game.StoryWall("Wall_side.obj", "bricks.jpg", "StoryWall")
storyWall:changeTexture("land.jpg")

-- getSomething()
-- print(story[1].wallImage)
-- print(story[1].blocks[1]:getName())
-- story[1].blocks[1]:setActive(false)
-- story[1].blocks[2]:setActive(false)
-- story[2].blocks[1]:setActive(false)
-- story[2].blocks[2]:setActive(false)
-- story[1].blocks[1]:setActive(true)

-- pieces = {  
--     Game.PuzzleBlock("Ship.obj", "bricks.jpg", "piece1", 2, 2, 4)
-- }

-- -- pieces[1]:setPosition(2,2,4)
-- pieces[1]:scale(0.3,0.3,0.3)

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
        else
            puzzleSetActive(counter, false)
        end
        counter = counter + 1
    end

    activePuzzle = puzzleIndex
    selectBlock(activePuzzle, 1)
end

function nextPuzzle()
    nextPuzzleIndex = activePuzzle + 1
    if nextPuzzleIndex > #story then
        storyCompleted = true
        print("completed!!")
    else
        selectPuzzle(nextPuzzleIndex)
    end
end

storyCompleted = false
activePuzzle = 1
activePiece = 1
solvedThreshold = 0.7

selectPuzzle(activePuzzle)

-- puzzleSetActive(2, false)

-- pieces[activePiece]:flash(1.6)


-- wall:setPosition(0,1,-3)
-- wall:scale(5,5,1)

function update()
    if storyCompleted then
        return
    else
        if Game.getKeyDown(KeyCode.T) == true then
            handleSelection()
        end

        if Game.getKeyDown(KeyCode.Y) == true then
            nextPuzzle()
        end

        handleControl()

        print(checkProgress())

        if checkProgress() >= solvedThreshold then
            nextPuzzle()
        end

        -- updateGameStatus()
        -- handleControl()

        -- if checkProgress() > 0.9 then
        --     if solved == false then
        --         solved = true
        --         Audio.playSound("door.wav")
        --     end
        -- end

        -- handleControl(pieces[activePiece])

        -- -- test placement for placing prop
        -- handleControl(prop1)

        
        -- print(pieces[activePiece]:getName())
        -- if checkProgress() > 0.66 then print(checkProgress()) end

        -- if Game.getKeyDown(KeyCode.P) == true then
        --     printPuzzleBlocksStates()
        -- elseif Game.getKeyDown(KeyCode.H) == true then
        --     hints.showHint()
        -- end

        -- if Game.getKeyDown(KeyCode.F5) == true then
        --     refreshHud()
        -- end
    end
end

function updateGUI()
    hud.draw()
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
        totalProgress = totalProgress + story[activePuzzle].blocks[activePiece]:getProgress() 
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

    -- if Game.getKey(KeyCode.Num1) == true then
    --     activePiece = 1
    -- end

    -- if Game.getKey(KeyCode.Num2) == true then
    --     activePiece = 2
    -- end

    -- if Game.getKey(KeyCode.Num3) == true then
    --     activePiece = 3
    -- end
end

function updateGameStatus()
    if checkProgress() < 0.66 and testtt == true then 
        print("level completed! proceeding to next level...")
        -- os.execute("CHOICE /n /d: /c: /t:3")
        -- cleanLevel()
        testtt = false
    end
end
        

