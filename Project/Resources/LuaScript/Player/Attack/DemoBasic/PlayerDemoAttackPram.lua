function GetParam(index)
    local params = {
        [1] = {
            horizontalCurve = 0.5,
            verticalCurve = 0.0,
            curveDistance = 5.0,
            useDistance = true,
            curveTime = 1.0,
            curveType = "SinWave"
        },
        [2] = {
            horizontalCurve = -0.5,
            verticalCurve = 0.0,
            curveDistance = 8.0,
            useDistance = true,
            curveTime = 1.0,
            curveType = "Linear"
        },
        [3] = {
            horizontalCurve = 0.0,
            verticalCurve = 0.3,
            curveDistance = 4.0,
            useDistance = true,
            curveTime = 0.8,
            curveType = "EaseInOut"
        }
    }

    return params[index]
end
