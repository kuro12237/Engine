PlayerMove = {
    -- 入力スティックのデッドゾーン
    LStickDeadZone = 0.15,

    -- 最大移動速度
    maxSpeed = 0.35,

    -- 慣性
    inertiaFactor = 1.0,

    -- 方向転換時の最低速度スケール
    minSpeedScale = 1.0,

    -- 姿勢補間率（回転角補間用）
    rotateLerp = 0.5,
}

return {
    PlayerMove = PlayerMove,
}
