local H = {}

hints = {
    "hint #1",
    "hint #2",
    "hint #3"
}

currentHint = 0

function showHint()
    print("--=== HERE IS A HINT FOR YOU ===--")
    print(getHint())
    print('\n')
end

function getHint()
    if currentHint < tablelength(hints) then
        currentHint = currentHint + 1
        return hints[currentHint]
    else
        return "no more hints available"
    end
end

function tablelength(T)
  local count = 0
  for _ in pairs(T) do count = count + 1 end
  return count
end

H.showHint = showHint

return H