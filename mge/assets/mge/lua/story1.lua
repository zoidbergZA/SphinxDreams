story = {
    {
        wallImage = "1_MainWall_Base_Color.png",    --SHIPS (done)
        blocks = {  
            Game.PuzzleBlock("Ship.obj", "Ship_Base_Color.png", "piece1", -1.325238, 4.995407, 4.780406)
            --Game.PuzzleBlock("sphere_smooth.obj", "bricks.jpg", "piece2", 2, 0, 0)
        },
        tips = {
            "Not meant to submerge",
            "Used for transportation",
            "Ship"
        },
        riddle = {
            "Weight in my belly, trees on my back, \n    nails in my ribbon, feet I do lack."
        },
        bookImageIntro = "BOOK_00.png",
        bookImage = "BOOK_01.png",
        camPosition = {-5.809093, 5.566962, 6.267358},
        lightPosition = {-1.325238, 4.995407, 13.4},
        wallPosition = {4.169649, 0.326027, 5.563453}
    },
    {
        wallImage = "2_MainWall_Base_Color.png",    --EAGLE (done)
        blocks = {  
            Game.PuzzleBlock("Eagle.obj", "Eagle_Base_Color.png", "piece1", -1.620447, 1.626915, 5.364659)
        },
        tips = {
            "King of the sky",
            "Emblem of ancient Rome",
            "Eagle"
        },
        riddle = {
            "                         Hard when young, but soft when old. \nI cannot live with my food. Majestic in movement, in eating crude."
        },
        bookImage = "BOOK_02.png",
        camPosition = {-4.939028, 2.902665, 6.712973},
        lightPosition = {-1.847859, 1.815444, 9.814968}
    },
    {
        wallImage = "3_MainWall_Base_Color.png",    --KNIFE (done)
        blocks = {  
            Game.PuzzleBlock("Knife.obj", "Knife_Base_Color.png", "piece1", 0.843153, 0.834008, 5.276042)
        },
        tips = {
            "Brings deadly resolutions",
            "Very sharp",
            "Knife"
        },
        riddle = {
            "        I eat meat, but do not drink wine. \n    I am a means to an end or it's protector. \nI have committed many gruesome betrayals."
        },
        bookImage = "BOOK_03.png",
        camPosition = {-2.479640, 2.096649, 7.160201},
        lightPosition = {0.843153, 1.088349, 13.4},
        wallPosition = {1.148681, 4.441195, 4.885514}
    },
    {
        wallImage = "5_MainWall_Base_Color.png",    --PYRAMID
        blocks = {  
            Game.PuzzleBlock("Piramide_Base.obj", "Piramide_Base_Base_Color.png", "piece1", 3.800427, 1.652600, 6.775362),
            Game.PuzzleBlock("Piramide_Peak.obj", "Piramide_Peak_Base_Color.png", "piece2", 3.865358, 1.794074, 6.345235)
        
        },
        tips = {
            "God's achitecture",
            "Geometrical shape",
            "Pyramid"
        },
        riddle = {
            "       Young ones can only listen to the tales of \nthe elders on how we were brought into exiistence"
        },
        bookImage = "BOOK_05.png",
        camPosition = {0.119922, 2.905429, 8.183538},
        lightPosition = {3.067473, 1.827167, 11.252758},
        wallPosition = {-0.893377, 3.392399, 4.224762}
    },
    {
        wallImage = "7_MainWall_Base_Color.png",    --LIPS
        blocks = {  
            Game.PuzzleBlock("Lips_Top.obj", "LipsTop_Base_Color.png", "piece1", 1.234649, 1.748361, 5.219128),
            Game.PuzzleBlock("Lips_Bottom.obj", "LipsLow_Base_Color.png", "piece2", 1.234544, 1.485922, 6.059439)
        },
        tips = {
            "Influences a large crowd",
            "Words come from it",
            "Lips"
        },
        riddle = {
            "            My touch is soft, but my intensions can be stern. \nWith your faith I can be great, but defy me and we will both fall."
        },
        bookImage = "BOOK_07.png",
        camPosition = {-2.302407, 4.178253, 8.711177},
        lightPosition = {1.234649, 1.748361, 13.4}
    },
    {
        wallImage = "9_MainWall_Base_Color.png",    --CAMEL
        blocks = {  
            Game.PuzzleBlock("Camal_Body_1.obj", "CamelBody_Base_Color.png", "piece1", 3.885678, 3.796520, 7.469913),
            Game.PuzzleBlock("Camal_Body_2.obj", "CamelBody2_Base_Color.png", "piece2", 3.792888, 3.759524, 5.896533)
        },
        tips = {
            "Living transport",
            "Brother of Dromedaries",
            "Camel"
        },
        riddle = {
            "   My kind has been around for centuries. \n        We carry mountains or our backs. \nYet, we do not protest, for we cannot speak."
        },
        bookImage = "BOOK_09.png",
        camPosition = {-0.597847, 4.665985, 9.045502},
        lightPosition = {3.887234, 3.759524, 13.4}
    },
    {
        wallImage = "10_MainWall_Base_Color.png",   --POTION
        blocks = {  
            Game.PuzzleBlock("Potion_Base.obj", "Potion_Base_Color.png", "piece1", 7.023105, 2.647626, 7.452380),
            Game.PuzzleBlock("Potion_Top.obj", "PotionTop_Base_Color.png", "piece2", 7.023105, 3.134248, 8.381447)
        },
        tips = {
            "It is antidote",
            "Pot shaped",
            "Antidote"
        },
        riddle = {
            "The solution is the antiodote."
        },
        bookImage = "BOOK_10.png",
        camPosition = {2.702556, 3.736271, 10.554673},
        lightPosition = {7.023105, 2.647626, 13.4}
    },
    {
        wallImage = "12_MainWall_Base_Color.png",   --UFO 
        blocks = {  
            Game.PuzzleBlock("UFO_Part1.obj", "Potion_Base_Color.png", "piece1", 7.869242, 4.829529, 8.615430),
            Game.PuzzleBlock("UFO_Part2.obj", "PotionTop_Base_Color.png", "piece2", 7.830701, 5.109225, 10.125306),
            Game.PuzzleBlock("UFO_Part3.obj", "PotionTop_Base_Color.png", "piece3", 7.824039, 4.957216, 9.211638),
            Game.PuzzleBlock("UFO_Part4.obj", "PotionTop_Base_Color.png", "piece4", 7.430742, 5.011202, 8.167035)
        },
        tips = {
            "Difficult to explain",
            "Can fly",
            "U.F.O."
        },
        riddle = {
            "Unbelievable fussy organization."
        },
        bookImage = "BOOK_12.png",
        camPosition = {2.514137, 4.950314, 13.103568},
        lightPosition = {7.604338, 5.042066, 13.4}
    }
    --[[,
    ------------------------------------------------------------------------------------------------------------
                                                        
                                                        -- END HERE --

    ------------------------------------------------------------------------------------------------------------
    {
        wallImage = "9_MainWall_Base_Color.png",    --CAMEL
        blocks = {  
            Game.PuzzleBlock("Camal_Body_1.obj", "CamelBody_Base_Color.png", "piece1", 1.758, 0.729, 6.674),
            Game.PuzzleBlock("Camal_Body_2.obj", "CamelBody2_Base_Color.png", "piece2", 1.63, 0.686, 4.939)
        },
        tips = {
            "Living transport",
            "Brother of Dromedaries",
            "Camel"
        },
        riddle = {
            "   My kind has been around for centuries. \n        We carry mountains or our backs. \nYet, we do not protest, for we cannot speak."
        },
        bookImage = "BOOK_09.png",
        camPosition = {-5.53, 2.66, 7.02},
        lightPosition = {-1.6, 2.4, 13.4}
    },
    {
        wallImage = "10_MainWall_Base_Color.png",   --POTION
        blocks = {  
            Game.PuzzleBlock("Potion_Base.obj", "Potion_Base_Color.png", "piece1", 1.758, 0.729, 6.674),
            Game.PuzzleBlock("Potion_Top.obj", "PotionTop_Base_Color.png", "piece2", 1.765, 2.258, 4.816)
        },
        tips = {
            "It is antidote",
            "Pot shaped",
            "Antidote"
        },
        riddle = {
            "The solution is the antiodote."
        },
        bookImage = "BOOK_10.png",
        camPosition = {-5.53, 2.66, 7.02},
        lightPosition = {-1.6, 2.4, 13.4}
    },
    {
        wallImage = "11_MainWall_Base_Color.png",   --[PLACE HOLDER] ARKH
        blocks = {  
            Game.PuzzleBlock("Potion_Base.obj", "Potion_Base_Color.png", "piece1", 1.758, 0.729, 6.674),
            Game.PuzzleBlock("Potion_Top.obj", "PotionTop_Base_Color.png", "piece2", 1.765, 2.258, 4.816)
        },
        tips = {
            "Ancient key",
            "Looks like a cross",
            "Ankh"
        },
        riddle = {
            "          I am the gateway between two worlds. \nMy purpose is to send you back, not let you pass."
        },
        bookImage = "BOOK_11.png",
        camPosition = {-5.53, 2.66, 7.02},
        lightPosition = {-1.6, 2.4, 13.4}
    },
    {
        wallImage = "12_MainWall_Base_Color.png",   --UFO 
        blocks = {  
            Game.PuzzleBlock("UFO_Part1.obj", "Potion_Base_Color.png", "piece1", 1.758, 0.729, 6.674),
            Game.PuzzleBlock("UFO_Part2.obj", "PotionTop_Base_Color.png", "piece2", 1.758, 0.729, 6.674),
            Game.PuzzleBlock("UFO_Part3.obj", "PotionTop_Base_Color.png", "piece2", 1.758, 0.729, 6.674),
            Game.PuzzleBlock("UFO_Part4.obj", "PotionTop_Base_Color.png", "piece2", 1.758, 0.729, 6.674)
        },
        tips = {
            "Difficult to explain",
            "Can fly",
            "U.F.O."
        },
        riddle = {
            "Unbelievable fussy organization."
        },
        bookImage = "BOOK_12.png",
        camPosition = {-5.53, 2.66, 7.02},
        lightPosition = {-1.6, 2.4, 13.4}
    }
    ]]--
}

--Scales Puzzle pieces

story[1].blocks[1]:scale(0.08, 0.08, 0.08)

story[2].blocks[1]:scale(0.1, 0.1, 0.1)

story[3].blocks[1]:scale(0.08, 0.08, 0.08)

story[4].blocks[1]:scale(0.08, 0.08, 0.08)
story[4].blocks[2]:scale(0.08, 0.08, 0.08)

story[5].blocks[1]:scale(0.15, 0.15, 0.15)
story[5].blocks[2]:scale(0.14, 0.14, 0.14)

story[6].blocks[1]:scale(0.13, 0.13, 0.13)
story[6].blocks[2]:scale(0.18, 0.18, 0.18)

story[7].blocks[1]:scale(0.12, 0.12, 0.12)
story[7].blocks[2]:scale(0.1, 0.1, 0.1)

story[8].blocks[1]:scale(0.075, 0.075, 0.075)
story[8].blocks[2]:scale(0.055, 0.055, 0.055)
story[8].blocks[3]:scale(0.065, 0.065, 0.065)
story[8].blocks[4]:scale(0.085, 0.085, 0.085)

-- story[9].blocks[1]:scale(0.3, 0.3, 0.3)
-- story[9].blocks[2]:scale(0.3, 0.3, 0.3)

-- story[10].blocks[1]:scale(0.3, 0.3, 0.3)
-- story[10].blocks[2]:scale(0.3, 0.3, 0.3)

--story[11].blocks[1]:scale(0.3, 0.3, 0.3)
--story[11].blocks[2]:scale(0.3, 0.3, 0.3)
--story[11].blocks[3]:scale(0.3, 0.3, 0.3)

-- story[12].blocks[1]:scale(0.3, 0.3, 0.3)
-- story[12].blocks[2]:scale(0.3, 0.3, 0.3)
-- story[12].blocks[3]:scale(0.3, 0.3, 0.3)
-- story[12].blocks[4]:scale(0.3, 0.3, 0.3)