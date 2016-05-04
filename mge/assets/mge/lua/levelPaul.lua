gameHud = require "mge/lua/hud"
gameHud_Data = require "mge/lua/hud_data"

pieces = {  
    Game.PuzzleBlock("cube_flat.obj", "land.jpg", "piece1"),
    Game.PuzzleBlock("teapot_smooth.obj", "bricks.jpg", "piece2"),
    Game.PuzzleBlock("teapot_smooth.obj", "land.jpg", "piece3")
}

pieces[1]:setPosition(0,-1,0)
pieces[2]:setPosition(0,1,0)
pieces[3]:setPosition(0,3,0)

activePiece = 1

local hints = require("mge/lua/hintsystem")
testtt = true

function update()
    updateGameStatus()
    handleControl()

    -- handleControl(pieces[activePiece])

    -- -- test placement for placing prop
    -- handleControl(prop1)

    handleSelection()
    -- print(pieces[activePiece]:getName())
    -- if checkProgress() > 0.66 then print(checkProgress()) end

    if Game.getKeyDown(KeyCode.P) == true then
        printPuzzleBlocksStates()
    elseif Game.getKeyDown(KeyCode.H) == true then
        hints.showHint()
    end

    if Game.getKeyDown(KeyCode.F5) == true then
        refreshHud()
    end
end

function updateGUI()
    -- -- button test
    -- if Hud.button(50, 50, "lua button") == true then
    --     print("lua button clicked!")
    -- end 
    
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
    for i, v in ipairs(pieces) do 
        totalProgress = totalProgress + v:getProgress() 
    end   
    return totalProgress / #pieces
end

function handleControl()
    if Game.getKey(KeyCode.W) == true then
        pieces[activePiece]:pitch(1.5) 
    end
    if Game.getKey(KeyCode.S) == true then
        pieces[activePiece]:pitch(-1.5) 
    end

    if Game.getKey(KeyCode.D) == true then
        pieces[activePiece]:roll(1.5) 
    end
    if Game.getKey(KeyCode.A) == true then
        pieces[activePiece]:roll(-1.5) 
    end
end 

function handleSelection()
    if Game.getKey(KeyCode.Num1) == true then
        activePiece = 1
    end

    if Game.getKey(KeyCode.Num2) == true then
        activePiece = 2
    end

    if Game.getKey(KeyCode.Num3) == true then
        activePiece = 3
    end
end

function updateGameStatus()
    if checkProgress() < 0.66 and testtt == true then 
        print("level completed! proceeding to next level...")
        -- os.execute("CHOICE /n /d: /c: /t:3")
        -- cleanLevel()
        testtt = false
    end
end
        

