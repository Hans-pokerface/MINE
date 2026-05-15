const GRID_SIZE = 8;
const NUM = 30;
const costDelete = [10, 40, 100, 200, 300];
const costReward = [5, 15, 40];
const costCombine = [5, 15, 40];

let boardState = [];
let mineGrid = [];
let existMine = NUM;
let allSpace = GRID_SIZE * GRID_SIZE;
let eco = 5;
let incre = 0;
let totalStep = 0;
let succStep = 0;
let failStep = 0;
let maxSucc = 0;
let maxFail = 0;
let failCode = 0;
let errorCode = -1;
let pDelete = 0;
let pReward = 0;
let pCombine = 0;
let history = [];
let gameOver = false;
let isPaused = false;
let showMines = false;

const board = document.getElementById('gameBoard');
const successRateEl = document.getElementById('successRate');
const currentStreakEl = document.getElementById('currentStreak');
const totalStepEl = document.getElementById('totalStep');
const economyEl = document.getElementById('economy');
const deleteLevelEl = document.getElementById('deleteLevel');
const rewardLevelEl = document.getElementById('rewardLevel');
const combineLevelEl = document.getElementById('combineLevel');
const priceDeleteEl = document.getElementById('priceDelete');
const priceRewardEl = document.getElementById('priceReward');
const priceCombineEl = document.getElementById('priceCombine');
const recentHistory = document.getElementById('recentHistory');
const maxSuccEl = document.getElementById('maxSucc');
const maxFailEl = document.getElementById('maxFail');
const gameMessage = document.getElementById('gameMessage');
const buyDeleteBtn = document.getElementById('buyDelete');
const buyRewardBtn = document.getElementById('buyReward');
const buyCombineBtn = document.getElementById('buyCombine');
const winOverlay = document.getElementById('winOverlay');
const finalTotalStepEl = document.getElementById('finalTotalStep');
const playerNameInput = document.getElementById('playerName');
const closeWinBtn = document.getElementById('closeWin');
const gotoResultBtn = document.getElementById('gotoResult');
const newGameNoSaveBtn = document.getElementById('newGameNoSave');

function createBoard() {
    if (!board) return;
    board.innerHTML = '';
    for (let row = 0; row < GRID_SIZE; row++) {
        for (let col = 0; col < GRID_SIZE; col++) {
            const cell = document.createElement('button');
            cell.className = 'cell';
            cell.type = 'button';
            cell.dataset.row = row;
            cell.dataset.col = col;
            cell.addEventListener('click', () => handleCellClick(row, col));
            board.appendChild(cell);
        }
    }
}

function initGrid() {
    boardState = Array.from({ length: GRID_SIZE }, () => Array(GRID_SIZE).fill('o'));
    mineGrid = Array.from({ length: GRID_SIZE }, () => Array(GRID_SIZE).fill(false));
}

function shuffleMines() {
    const positions = new Set();
    while (positions.size < existMine) {
        const index = Math.floor(Math.random() * GRID_SIZE * GRID_SIZE);
        positions.add(index);
    }

    mineGrid = Array.from({ length: GRID_SIZE }, () => Array(GRID_SIZE).fill(false));
    positions.forEach((index) => {
        const row = Math.floor(index / GRID_SIZE);
        const col = index % GRID_SIZE;
        mineGrid[row][col] = true;
    });
}

function getProbability() {
    return Math.max(0, Math.min(1, 1 - existMine / allSpace));
}

function formatHistory() {
    if (!history.length) {
        return '暂无记录';
    }
    return history.map((item) => item).join(' ');
}

function addHistory(symbol) {
    history.push(symbol);
    if (history.length > 10) {
        history.shift();
    }
}

function resetBoardState() {
    boardState = Array.from({ length: GRID_SIZE }, () => Array(GRID_SIZE).fill('o'));
}

function updateDisplay() {
    if (successRateEl) {
        successRateEl.textContent = `${(getProbability() * 100).toFixed(2)}%`;
    }
    if (currentStreakEl) {
        currentStreakEl.textContent = succStep.toString();
    }
    if (economyEl) {
        economyEl.textContent = eco.toFixed(2);
    }
    if (deleteLevelEl) {
        deleteLevelEl.textContent = pDelete.toString();
    }
    if (rewardLevelEl) {
        rewardLevelEl.textContent = pReward.toString();
    }
    if (combineLevelEl) {
        combineLevelEl.textContent = pCombine.toString();
    }
    if (priceDeleteEl) {
        priceDeleteEl.textContent = costDelete[Math.min(pDelete, costDelete.length - 1)].toString();
    }
    if (priceRewardEl) {
        priceRewardEl.textContent = costReward[Math.min(pReward, costReward.length - 1)].toString();
    }
    if (priceCombineEl) {
        priceCombineEl.textContent = costCombine[Math.min(pCombine, costCombine.length - 1)].toString();
    }
    if (recentHistory) {
        recentHistory.textContent = formatHistory();
    }
    if (maxSuccEl) {
        maxSuccEl.textContent = maxSucc.toString();
    }
    if (maxFailEl) {
        maxFailEl.textContent = maxFail.toString();
    }
    if(totalStepEl) {
        totalStepEl.textContent=totalStep.toString();
    }
    if (gameMessage) {
        gameMessage.textContent = getMessage();
        gameMessage.classList.toggle('message-fail', errorCode === 5);
        gameMessage.classList.toggle('message-success', errorCode === 0);
    }

    if (buyDeleteBtn) {
        buyDeleteBtn.disabled = isPaused || pDelete >= 5 || parseFloat(eco.toFixed(2)) < costDelete[pDelete];
    }
    if (buyRewardBtn) {
        buyRewardBtn.disabled = isPaused || pReward >= 3 || parseFloat(eco.toFixed(2)) < costReward[pReward];
    }
    if (buyCombineBtn) {
        buyCombineBtn.disabled = isPaused || pCombine >= 3 || parseFloat(eco.toFixed(2)) < costCombine[pCombine];
    }

    updateBoardCells();
}

function updateBoardCells() {
    const cellButtons = board.querySelectorAll('.cell');
    cellButtons.forEach((cell) => {
        const row = Number(cell.dataset.row);
        const col = Number(cell.dataset.col);
        const state = boardState[row][col];
        const isMine = mineGrid[row][col];

        if (state === '+') {
            cell.textContent = 'O';
            cell.classList.add('cell-selected');
            cell.classList.remove('cell-mine');
            cell.disabled = true;
        } else if (showMines && isMine) {
            cell.textContent = 'X';
            cell.classList.add('cell-mine');
            cell.classList.remove('cell-selected');
            cell.disabled = true;
        } else {
            cell.textContent = '';
            cell.classList.remove('cell-selected');
            cell.classList.remove('cell-mine');
            cell.disabled = gameOver || isPaused;
        }
    });
}

function getMessage() {
    switch (errorCode) {
        case 0:
            return `成功！本次选择安全，获得 ${incre.toFixed(2)} 经济。`;
        case 1:
            return '道具已购买，效果已生效。';
        case 2:
            return '抱歉，当前经济不足或已达道具上限。';
        case 4:
            return '该格子已选择，请换一个位置。';
        case 5:
            return 'BOOM！踩中地雷，棋盘已重置，继续挑战。';
        case 6:
            return '恭喜你！已连续选中 8 个安全格子，取得胜利！';
        default:
            return '地雷已随机分布，请选择一个格子。';
    }
}

function resetMines() {
    existMine = NUM - 4 * pDelete;
    allSpace = GRID_SIZE * GRID_SIZE;
    shuffleMines();
}

function handleCellClick(row, col) {
    if (gameOver || isPaused) {
        return;
    }
    if (boardState[row][col] === '+') {
        errorCode = 4;
        updateDisplay();
        return;
    }

    totalStep += 1;

    if (mineGrid[row][col]) {
        addHistory('F');
        if (failCode === 1) {
            failStep += 1;
        } else {
            failStep = 1;
        }
        maxFail = Math.max(maxFail, failStep);
        errorCode = 5;
        failCode = 1;
        succStep = 0;
        resetBoardState();
        showMines = true;
        isPaused = true;
        updateDisplay();

        setTimeout(() => {
            showMines = false;
            isPaused = false;
            resetMines();
            errorCode = -1;
            updateDisplay();
        }, 1200);
    } else {
        addHistory('S');
        failCode = 0;
        errorCode = 0;
        succStep += 1;
        failStep = 0;
        maxSucc = Math.max(maxSucc, succStep);
        allSpace -= 1;
        incre = (1 + (succStep - 1) * 0.4 * (pCombine + 1)) * (pReward + 1);
        eco += incre;
        boardState[row][col] = '+';

        if (succStep === 8) {
            gameOver = true;
            errorCode = 6;
                // show win modal
                setTimeout(() => {
                    showWinModal();
                }, 180);
        }
    }

    updateDisplay();
}

function purchaseUpgrade(type) {
    if (gameOver || isPaused) {
        return;
    }

    if (type === 'delete') {
        if (pDelete >= 5 || parseFloat(eco.toFixed(2)) < costDelete[pDelete]) {
            errorCode = 2;
            updateDisplay();
            return;
        }
        errorCode = 1;
        eco -= costDelete[pDelete];
        pDelete += 1;
        for (let i = 0; i < 4; i += 1) {
            deleteOneMine();
        }
        existMine -= 4;
    } else if (type === 'reward') {
        if (pReward >= 3 || parseFloat(eco.toFixed(2)) < costReward[pReward]) {
            errorCode = 2;
            updateDisplay();
            return;
        }
        errorCode = 1;
        eco -= costReward[pReward];
        pReward += 1;
    } else if (type === 'combine') {
        if (pCombine >= 3 || parseFloat(eco.toFixed(2)) < costCombine[pCombine]) {
            errorCode = 2;
            updateDisplay();
            return;
        }
        errorCode = 1;
        eco -= costCombine[pCombine];
        pCombine += 1;
    }

    updateDisplay();
}

function deleteOneMine() {
    for (let row = 0; row < GRID_SIZE; row += 1) {
        for (let col = 0; col < GRID_SIZE; col += 1) {
            if (mineGrid[row][col]) {
                mineGrid[row][col] = false;
                return;
            }
        }
    }
}

function initGame() {
    initGrid();
    resetMines();
    createBoard();
    buyDeleteBtn?.addEventListener('click', () => purchaseUpgrade('delete'));
    buyRewardBtn?.addEventListener('click', () => purchaseUpgrade('reward'));
    buyCombineBtn?.addEventListener('click', () => purchaseUpgrade('combine'));
    initWinModalHandlers();
    updateDisplay();
}

initGame();

function initWinModalHandlers() {
    closeWinBtn?.addEventListener('click', hideWinModal);
    gotoResultBtn?.addEventListener('click', handleGotoResult);
    newGameNoSaveBtn?.addEventListener('click', () => {
        hideWinModal();
        startNewGame();
    });
}

function handleGotoResult() {
    const name = playerNameInput ? playerNameInput.value.trim() : '';
    if (name) {
        saveGameLog(name, totalStep);
    }
    window.location.href = 'result.html';
}

function showWinModal() {
    if (!winOverlay) return;
    if (finalTotalStepEl) finalTotalStepEl.textContent = totalStep.toString();
    if (playerNameInput) playerNameInput.value = '';
    winOverlay.classList.remove('hidden');
    playerNameInput?.focus();
}

function hideWinModal() {
    if (!winOverlay) return;
    winOverlay.classList.add('hidden');
}

function startNewGame() {
    // reset relevant state like original init
    gameOver = false;
    isPaused = false;
    history = [];
    totalStep = 0;
    succStep = 0;
    failStep = 0;
    maxSucc = 0;
    maxFail = 0;
    errorCode = -1;
    pDelete = 0; pReward = 0; pCombine = 0;
    eco = 5; incre = 0;
    initGrid();
    resetMines();
    resetBoardState();
    updateDisplay();
}