pieces = {  
    Game.PuzzleBlock("cube_flat.obj", "land.jpg"),
    Game.PuzzleBlock("teapot_smooth.obj", "bricks.jpg"),
    Game.PuzzleBlock("teapot_smooth.obj", "land.jpg")
}

pieces[1]:setPosition(0,-1,0)
pieces[2]:setPosition(0,1,0)
pieces[3]:setPosition(0,3,0)

activePiece = 1

function update()
    handleControl()

    handleSelection()

    -- print(checkProgress())
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