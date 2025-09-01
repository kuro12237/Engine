Data = {
    hp = 1,
    attack = 190.0,
    state ="string move",
    num = 4,
}


function GetStageFileName(index)
    local string = {
        [0] = "string : error",
        [1] = "string : 1 num",
        [2] = "string : 2",
        [3] = "string : 3",
        [4] = "string : call 4",
        [5] = "string : 5"
    }

    return string[index] or "string : error" --これは関数のreturn
end

--[[
複数データがある場合は
以下のようにまとめてreturnの中に入れる

return {
    Data1 = Data1,
    Data2 = Data2,
    Data3 = Data3,
    Data4 = Data4
}
]]