const fs = require("fs");
const SECRET_COOKIE = process.env.SECRET_COOKIE || "test_cookie"

const flag1 = fs.readFileSync("/flag1")
const flag2 = fs.readFileSync("/flag2")


function Login(req, res) {
    try {
        const username = req.body.username
        const password = req.body.password
        if (username !== "admin" || password !== Math.random().toString()) {
            res.status(401).type("text/html").send("Login Failed")
        } else {
            res.cookie("user", SECRET_COOKIE)
            res.redirect("/flag1")
        }
    } catch (__) { }
}

function FakeCheck(req, res) {
    res.sendFile("check.html", { root: "static" })

}

function CheckCode(req, res) {
    let yourcode = req.body.checkcode ? req.body.checkcode : 1111;
    console.log(req.body)
    if (yourcode.length === 18) {
        try {
            yourcode = yourcode.toLowerCase()
            if (yourcode !== "WHUCTF{Just_a_Web}") {
                res.status(403).json({ "msg": "Invalid code2:" + yourcode })
            }
        } catch (__) { }
        res.status(200).type("text/html").json({ "msg": "You Got Another Part Of Flag: " + flag2.toString().trim() })
    } else {
        res.status(403).type("text/html").json({ "msg": "Invalid code:" + yourcode })
    }
}

function Secret1Controller(req, res) {
    try {
        if (req.cookies.user === SECRET_COOKIE) {
            res.setHeader("Your_first_Flag", flag1.toString().trim())
            res.setHeader("Your_The_second_Flag", flag2.toString().trim())
            res.status(200).type("text/html").send("Login success. Welcome,admin!")
        }
        if (req.cookies.user === "WHUCTFer") {
            res.setHeader("This_Is_Your_Flag1", flag1.toString().trim())
            res.status(200).type("text/html").send("You Got One Part Of Flag! Try To Get Another Part of Flag!")
        } else {
            res.status(401).type("text/html").send("Unauthorized")
        }
    } catch (__) { }
}



module.exports = {
    LoginController: Login,
    CheckInternalController: FakeCheck,
    Flag1Controller: Secret1Controller,
    CheckController: CheckCode
}