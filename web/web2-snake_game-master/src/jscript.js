// GAME_PIXEL_COUNT is the pixels on horizontal or vertical axis of the game board (SQUARE).
const GAME_PIXEL_COUNT = 40;
const SQUARE_OF_GAME_PIXEL_COUNT = Math.pow(GAME_PIXEL_COUNT, 2);

let totalFoodAte = 0;
let totalDistanceTravelled = 0;

/// THE GAME BOARD:
const gameContainer = document.getElementById("gameContainer");
document.addEventListener("keydown", (e) => {
  if (e.key === "F12") {
    e.preventDefault();
    return false;
  }
});

// Disable Ctrl+U (View Source)
document.addEventListener("keydown", (e) => {
  if (e.ctrlKey && (e.key === "u" || e.key === "s")) {
    e.preventDefault();
    return false;
  }
});

// Disable right-click context menu
document.addEventListener("contextmenu", (e) => {
  e.preventDefault();
});

const createGameBoardPixels = () => {
  let gamePixelDivs = '';
  for (let i = 1; i <= SQUARE_OF_GAME_PIXEL_COUNT; ++i) {
    gamePixelDivs = `${gamePixelDivs} <div class="gameBoardPixel" id="pixel${i}"></div>`;
  }
  // Populate the [#gameContainer] div with small div's representing game pixels
  gameContainer.innerHTML = `${gameContainer.innerHTML} ${gamePixelDivs}`;
};

// This variable always holds the updated array of game pixels created by createGameBoardPixels() :
const gameBoardPixels = document.getElementsByClassName("gameBoardPixel");

/// THE FOOD:
let currentFoodPostion = 0;
const createFood = () => {
  // Remove previous food;
  gameBoardPixels[currentFoodPostion].classList.remove("food");

  // Create new food
  currentFoodPostion = Math.random();
  currentFoodPostion = Math.floor(
    currentFoodPostion * SQUARE_OF_GAME_PIXEL_COUNT
  );
  gameBoardPixels[currentFoodPostion].classList.add("food");
};

/// THE SNAKE:

// Direction codes (Keyboard key codes for arrow keys):
const LEFT_DIR = 37;
const UP_DIR = 38;
const RIGHT_DIR = 39;
const DOWN_DIR = 40;

// Set snake direction initially to right
let snakeCurrentDirection = RIGHT_DIR;

const changeDirection = (newDirectionCode) => {
  // Change the direction of the snake
  if (newDirectionCode == snakeCurrentDirection) return;

  if (newDirectionCode == LEFT_DIR && snakeCurrentDirection != RIGHT_DIR) {
    snakeCurrentDirection = newDirectionCode;
  } else if (newDirectionCode == UP_DIR && snakeCurrentDirection != DOWN_DIR) {
    snakeCurrentDirection = newDirectionCode;
  } else if (
    newDirectionCode == RIGHT_DIR &&
    snakeCurrentDirection != LEFT_DIR
  ) {
    snakeCurrentDirection = newDirectionCode;
  } else if (newDirectionCode == DOWN_DIR && snakeCurrentDirection != UP_DIR) {
    snakeCurrentDirection = newDirectionCode;
  }
};

// Let the starting position of the snake be at the middle of game board
let currentSnakeHeadPosition = SQUARE_OF_GAME_PIXEL_COUNT / 2;

// Initial snake length
let snakeLength = 1000;
// 向后端发送请求的函数，并处理响应
const notifyBackend = async (foodCount, length) => {
  try {
    // 更新 URL 为后端的完整地址
    const response = await fetch('http://127.0.0.1:3000/notify', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({ totalFoodAte: foodCount, snakeLength: length }),
    });

    if (response.ok) {
      const data = await response.json();
      if (data.check === 1) {
        console.log(data.flag);
      }
      else {
        console.log('Sorry', data.flag);
      }
    } else {
      console.error('Request failed with status:', response.status);
    }
  } catch (error) {
    console.error('Error:', error);
  }
};


const moveSnake = () => {
  switch (snakeCurrentDirection) {
    case LEFT_DIR:
      --currentSnakeHeadPosition;
      const isSnakeHeadAtLastGameBoardPixelTowardsLeft =
        currentSnakeHeadPosition % GAME_PIXEL_COUNT == GAME_PIXEL_COUNT - 1 ||
        currentSnakeHeadPosition < 0;
      if (isSnakeHeadAtLastGameBoardPixelTowardsLeft) {
        currentSnakeHeadPosition = currentSnakeHeadPosition + GAME_PIXEL_COUNT;
      }
      break;
    case UP_DIR:
      currentSnakeHeadPosition = currentSnakeHeadPosition - GAME_PIXEL_COUNT;
      const isSnakeHeadAtLastGameBoardPixelTowardsUp =
        currentSnakeHeadPosition < 0;
      if (isSnakeHeadAtLastGameBoardPixelTowardsUp) {
        currentSnakeHeadPosition =
          currentSnakeHeadPosition + SQUARE_OF_GAME_PIXEL_COUNT;
      }
      break;
    case RIGHT_DIR:
      ++currentSnakeHeadPosition;
      const isSnakeHeadAtLastGameBoardPixelTowardsRight =
        currentSnakeHeadPosition % GAME_PIXEL_COUNT == 0;
      if (isSnakeHeadAtLastGameBoardPixelTowardsRight) {
        currentSnakeHeadPosition = currentSnakeHeadPosition - GAME_PIXEL_COUNT;
      }
      break;
    case DOWN_DIR:
      currentSnakeHeadPosition = currentSnakeHeadPosition + GAME_PIXEL_COUNT;
      const isSnakeHeadAtLastGameBoardPixelTowardsDown =
        currentSnakeHeadPosition > SQUARE_OF_GAME_PIXEL_COUNT - 1;
      if (isSnakeHeadAtLastGameBoardPixelTowardsDown) {
        currentSnakeHeadPosition =
          currentSnakeHeadPosition - SQUARE_OF_GAME_PIXEL_COUNT;
      }
      break;
    default:
      break;
  }

  let nextSnakeHeadPixel = gameBoardPixels[currentSnakeHeadPosition];

  // 游戏结束
  if (nextSnakeHeadPixel.classList.contains("snakeBodyPixel")) {
    // 停止移动蛇
    clearInterval(moveSnakeInterval);
    if (
      !alert(
        `你已经吃了 ${totalFoodAte} 份食物，旅行了 ${totalDistanceTravelled} 格子。`
      )
    )
      window.location.reload();
  }

  nextSnakeHeadPixel.classList.add("snakeBodyPixel");

  setTimeout(() => {
    nextSnakeHeadPixel.classList.remove("snakeBodyPixel");
  }, snakeLength);

  // 更新总距离
  totalDistanceTravelled++;
  // 更新 UI:
  document.getElementById("blocksTravelled").innerHTML = totalDistanceTravelled;

  if (currentSnakeHeadPosition == currentFoodPostion) {
    totalFoodAte++;
    document.getElementById("pointsEarned").innerHTML = totalFoodAte;

    if (totalFoodAte >= 2024) {
      notifyBackend(totalFoodAte, snakeLength);
    }

    snakeLength = snakeLength + 100;
    createFood();
  }
};

/// CALL THE FOLLOWING FUNCTIONS TO RUN THE GAME:

// Create game board pixels:
createGameBoardPixels();

// Create initial food:
createFood();

// Move snake:
var moveSnakeInterval = setInterval(moveSnake, 80);

// Call change direction function on keyboard key-down event:
addEventListener("keydown", (e) => changeDirection(e.keyCode));

// ON SCREEN CONTROLLERS:
const leftButton = document.getElementById("leftButton");
const rightButton = document.getElementById("rightButton");
const upButton = document.getElementById("upButton");
const downButton = document.getElementById("downButton");

leftButton.onclick = () => changeDirection(LEFT_DIR);
rightButton.onclick = () => changeDirection(RIGHT_DIR);
upButton.onclick = () => changeDirection(UP_DIR);
downButton.onclick = () => changeDirection(DOWN_DIR);
