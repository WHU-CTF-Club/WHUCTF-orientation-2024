const express = require('express');
const app = express();
const cors = require('cors'); // 引入 cors 中间件
// 使用 cors 中间件
app.use(cors());

// 解析 JSON 请求体
app.use(express.json());

app.post('/notify', (req, res) => {
    const { totalFoodAte, snakeLength } = req.body;
    if (totalFoodAte >= 2024) {
        if (snakeLength >= 203400) {
            const flag = 'Congratulations! WHUCTF{Plz_Strt_y0ur_w3b_joun3y!}';
            res.json({ flag: flag, check: 1 });
        } else {
            res.status(200).json({ flag: "Your snake is too short", check: 0 });
        }
    } else {
        res.status(200).json({ flag: "Your snake eats so few food", check: 0 });
    }
});
port = 3000
app.listen(port, () => {
    console.log(`Server is running on http://127.0.0.1:${port}`);
});